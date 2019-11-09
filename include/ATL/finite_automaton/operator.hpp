//
//  operator.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef operator_hpp 
#define operator_hpp 
#include "cast.hpp"

namespace atl {
    struct IntersectFaImpl {
        template <typename DeterministicFiniteAutomatonLhs,
                  typename DeterministicFiniteAutomatonRhs,
                  typename Symbol2StatePairMap>
        static void 
        make_pair_map(const DeterministicFiniteAutomatonLhs& a_lhs,
                      const DeterministicFiniteAutomatonRhs& a_rhs,
                      typename DeterministicFiniteAutomatonLhs::State state_lhs,
                      typename DeterministicFiniteAutomatonRhs::State state_rhs,
                      Symbol2StatePairMap& map) {
            typedef typename DeterministicFiniteAutomatonLhs::StatePair StatePair;
            const auto& lhs_transition_map = a_lhs.transition_map();
            const auto& rhs_transition_map = a_rhs.transition_map();
            const auto lhs_iter = lhs_transition_map.find(state_lhs);
            const auto rhs_iter = lhs_transition_map.find(state_rhs);
            if (lhs_iter != lhs_transition_map.end() && rhs_iter != rhs_transition_map.end()) {
                const auto& lhs_map = lhs_iter -> second;
                const auto& rhs_map = rhs_iter -> second;
                if (lhs_map.size() <= rhs_map.size()) {
                    for (const auto& map_pair : lhs_map) {
                        const auto map_iter = rhs_map.find(map_pair.first);
                        if (map_iter != rhs_map.end()) {
                            map[map_pair.first] = StatePair(map_pair.second, map_iter -> second);
                        }
                    }
                } else {
                    for (const auto& map_pair : rhs_map) {
                        const auto map_iter = lhs_map.find(map_pair.first);
                        if (map_iter != lhs_map.end()) {
                            map[map_pair.first] = StatePair(map_iter -> second, map_pair.second);
                        }
                    }
                }
            }
        }

        template <typename DeterministicFiniteAutomatonLhs,
                  typename DeterministicFiniteAutomatonRhs,
                  typename DeterministicFiniteAutomatonOut,
                  typename Merge>
        static void 
        do_intersect(const DeterministicFiniteAutomatonLhs& a_lhs,
                     const DeterministicFiniteAutomatonRhs& a_rhs,
                     DeterministicFiniteAutomatonOut& a_out,
                     typename DeterministicFiniteAutomatonLhs::State state_lhs,
                     typename DeterministicFiniteAutomatonRhs::State state_rhs,
                     typename DeterministicFiniteAutomatonOut::State state_out,
                     typename DeterministicFiniteAutomatonOut::StatePairMap pair_map,
                     Merge merge) {
            typedef typename DeterministicFiniteAutomatonOut::State State;
            if (is_final_state(a_lhs, state_lhs) && is_final_state(a_rhs, state_rhs)) 
                a_out.set_final_state(state_out);
            const auto& lhs_map = a_lhs.transition_map();
            const auto& rhs_map = a_rhs.transition_map();
            const auto lhs_iter = lhs_map.find(state_lhs);
            const auto rhs_iter = lhs_map.find(state_rhs);
            typename DeterministicFiniteAutomatonOut::Symbol2StatePairMap map;
            make_pair_map(a_lhs, a_rhs, state_lhs, state_rhs, map);
            for (auto& map_pair : map) {
                auto& symbol = map_pair.first;
                auto& state_pair = map_pair.second;
                auto pair_iter = pair_map.find(state_pair);
                State target = -1;
                if (pair_iter == pair_map.end()) {
                    State new_state_lhs = state_pair.first;
                    State new_state_rhs = state_pair.second;
                    target = add_state(a_out, 
                                      merge(atl::get_property(a_lhs, new_state_lhs), 
                                            atl::get_property(a_rhs, new_state_rhs)));
                    pair_map[state_pair] = target;
                    do_intersect(a_lhs, a_rhs, a_out, 
                                 new_state_lhs, new_state_rhs, target,
                                 pair_map, merge);
                } else {
                    target = pair_iter -> second;
                }
                add_transition(a_out, state_out, target, symbol);
            }
        }

        template <typename FiniteAutomatonLhs,
                  typename FiniteAutomatonRhs,
                  typename DeterministicFiniteAutomaton,
                  typename Merge>
        static void 
        apply(const FiniteAutomatonLhs& a_lhs,
              const FiniteAutomatonRhs& a_rhs,
              DeterministicFiniteAutomaton& a_out,
              Merge merge) {
            typedef typename FiniteAutomatonLhs::DeterministicFiniteAutomatonType DfaLhs;
            typedef typename FiniteAutomatonRhs::DeterministicFiniteAutomatonType DfaRhs;
            typedef typename DeterministicFiniteAutomaton::StatePair StatePair;
            typedef typename DeterministicFiniteAutomaton::StatePairMap StatePairMap;
            typedef typename DeterministicFiniteAutomaton::State State;
            std::shared_ptr<const DfaLhs> dfa_lhs = nullptr;
            std::shared_ptr<const DfaRhs> dfa_rhs = nullptr;
            minimize(a_lhs, dfa_lhs);
            minimize(a_rhs, dfa_rhs);
            
            State initial_state_lhs = dfa_lhs -> initial_state(),
                  initial_state_rhs = dfa_rhs -> initial_state(),
                  initial_state_out = 
                      add_initial_state(a_out, 
                                        merge(atl::get_property(*dfa_lhs, initial_state_lhs),
                                              atl::get_property(*dfa_rhs, initial_state_rhs)));
            StatePairMap pair_map({{StatePair(initial_state_lhs, initial_state_lhs),
                                    initial_state_out}}); 
            do_intersect(*dfa_lhs, *dfa_rhs, a_out, 
                         initial_state_lhs, initial_state_rhs, 
                         a_out.initial_state(), pair_map, merge);
        }
    };

    template <typename FiniteAutomatonLhs,
              typename FiniteAutomatonRhs,
              typename DeterministicFiniteAutomaton,
              typename Merge = IntersectMerge<
                               typename DeterministicFiniteAutomaton::StatePropType> >
    inline void
    intersect_fa(const FiniteAutomatonLhs& a_lhs,
                 const FiniteAutomatonRhs& a_rhs,
                 DeterministicFiniteAutomaton& a_out,
                 Merge merge = Merge()) {
        IntersectFaImpl::apply(a_lhs, a_rhs, a_out, merge);
    }

    struct UnionFaImpl {
        template <typename FiniteAutomatonLhs,
                  typename FiniteAutomatonRhs,
                  typename DeterministicFiniteAutomaton,
                  typename Merge>
        static void
        apply(const FiniteAutomatonLhs& a_lhs,
              const FiniteAutomatonRhs& a_rhs,
              DeterministicFiniteAutomaton& a_out,
              Merge merge) {
            typedef typename FiniteAutomatonLhs::DeterministicFiniteAutomatonType DfaLhs;
            typedef typename FiniteAutomatonRhs::DeterministicFiniteAutomatonType DfaRhs;
            typedef typename DeterministicFiniteAutomaton::NondeterministicFiniteAutomatonType
                NFA;
            typedef typename DeterministicFiniteAutomaton::StatePair StatePair;
            typedef typename DeterministicFiniteAutomaton::StatePairMap StatePairMap;
            typedef typename DeterministicFiniteAutomaton::State State;
            std::shared_ptr<const DfaLhs> dfa_lhs = nullptr;
            std::shared_ptr<const DfaRhs> dfa_rhs = nullptr;
            minimize(a_lhs, dfa_lhs);
            minimize(a_rhs, dfa_rhs);
            NFA nfa;
            State inital_state = add_initial_state(nfa),
                  inital_state_lhs = dfa_lhs -> inital_state(),
                  inital_state_rhs = dfa_rhs -> inital_state();
        }

    };

}

#endif /* operator_hpp */

