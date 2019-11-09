//
//  cast.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef cast_hpp 
#define cast_hpp 

#include <queue>
#include "../basic.hpp"
#include "deterministic_finite_automaton.hpp"
#include "nondeterministic_finite_automaton.hpp"
#include "closure.hpp"
#include "merge.hpp"
using std::queue;

namespace atl {

    struct MinimizeImpl {
        template <typename DeterministicFiniteAutomaton>
        static bool is_equal(const DeterministicFiniteAutomaton& dfa,
                             typename DeterministicFiniteAutomaton::State s1,
                             typename DeterministicFiniteAutomaton::State s2,
                             typename DeterministicFiniteAutomaton::State2Map const& state2_map) {
            const auto& transition_map = dfa.transition_map();
            if (atl::get_property(dfa, s1) != atl::get_property(dfa, s2)) return false;
            ID count1 = transition_map.count(s1), count2 = transition_map.count(s2);
            if (count1 == 0 && count2 == 0) return true;
            if ((count1 & count2) == 0) return false;
            auto &map1 = transition_map.at(s1);
            auto &map2 = transition_map.at(s2);
            if (map1.size() != map2.size()) return false;
            for (auto& map_pair : map1) {
                if (map2.count(map_pair.first) == 0) return false;
                else if (state2_map.at(map_pair.second) != state2_map.at(map2.at(map_pair.first)))
                    return false;
            }
            return true;
        }

        template <typename DeterministicFiniteAutomaton>
        static void get_equivalences(const DeterministicFiniteAutomaton& dfa_in, 
                                     DeterministicFiniteAutomaton& dfa_out,
                                     queue<typename DeterministicFiniteAutomaton::States>&
                                     equivalences, 
                                     typename DeterministicFiniteAutomaton::State2Map&
                                     state2_map) {
            typedef typename DeterministicFiniteAutomaton::State State;
            typedef typename DeterministicFiniteAutomaton::States States;
            typedef typename DeterministicFiniteAutomaton::State2Map State2_map;
            ID cur_size = equivalences.size(), last_size = 0;
            while (cur_size != last_size) {
                for (ID i = 0; i < cur_size; ++i) {
                    States& set = equivalences.front();
                    if (set.size() == 0) continue;
                    while (set.size() > 0) {
                        State state = *(set.begin());
                        States new_equivalence;
                        new_equivalence.insert(state);
                        set.erase(state);
                        States delStates;
                        for (const auto& new_state : set) {
                            if (is_equal(dfa_in, state, new_state, state2_map)) {
                                new_equivalence.insert(new_state);
                                delStates.insert(new_state);
                            }
                        }
                        for (auto delState : delStates) {
                            set.erase(delState);
                        }
                        equivalences.push(new_equivalence);
                        State newMapState = atl::add_state(dfa_out,
                                atl::get_property(dfa_in, *(new_equivalence.begin())));
                        for (auto new_state : new_equivalence) {
                            state2_map[new_state] = newMapState;
                        }
                    }
                    equivalences.pop();
                }
                last_size = cur_size;
                cur_size = equivalences.size();
            }
        }

        template <typename DeterministicFiniteAutomaton>
        static void apply(const DeterministicFiniteAutomaton& dfa_in,
                          DeterministicFiniteAutomaton& dfa_out) {
            typedef typename DeterministicFiniteAutomaton::State State;
            typedef typename DeterministicFiniteAutomaton::States States;
            typedef typename DeterministicFiniteAutomaton::State2Map State2Map;
            typedef typename DeterministicFiniteAutomaton::TransitionMap TransitionMap;
            dfa_out.clear();
            dfa_out.set_alphabet(dfa_in.alphabet());
            atl::set_property(dfa_out, atl::get_property(dfa_in));
            States reachable_states, unfinal_states, final_states;
            atl::reachable_closure(dfa_in, reachable_states);
            State2Map state2_map;
            const auto& prop = atl::get_property(dfa_in, dfa_in.initial_state());
            State unfinal_state = add_state(dfa_out, prop),
                  final_state = add_state(dfa_out, prop);
            for (auto state : reachable_states) {
                if (is_final_state(dfa_in, state)) {
                    final_states.insert(state);
                    state2_map[state] = final_state;
                } else {
                    unfinal_states.insert(state);
                    state2_map[state] = unfinal_state;
                }
            }

            std::queue<States> equivalences({final_states});
            if (unfinal_states.size() > 0) equivalences.push(unfinal_states);
            get_equivalences(dfa_in, dfa_out, equivalences, state2_map);

            atl::clear_states(dfa_out);

            State initial_state = add_initial_state(dfa_out,
                                      atl::get_property(dfa_in, dfa_in.initial_state()));
            State2Map new_state2_map({{dfa_in.initial_state(), initial_state}}),
                      map({{state2_map[dfa_in.initial_state()], initial_state}});
            for (auto& map_pair : state2_map) {
                State state = map_pair.second;
                if (map.count(state) == 0) {
                    State new_state = add_state(dfa_out,
                                        atl::get_property(dfa_in, map_pair.first));
                    if (is_final_state(dfa_in, map_pair.first)) 
                        dfa_out.set_final_state(new_state);
                    new_state2_map[map_pair.first] = new_state;
                    map[state] = new_state;
                } else {
                    new_state2_map[map_pair.first] = map[state];
                }
            }

            const auto& transition_map = dfa_in.transition_map();
            for (auto& map_pair : new_state2_map) {
                if (map_pair.first == -1 || map_pair.second == -1) continue;
                ID count1 = transition_map.count(map_pair.first), 
                   count2 = dfa_out.transition_map().count(map_pair.second);
                if (count1 > 0 && count2 == 0) {
                    auto &map = transition_map.at(map_pair.first);
                    for (auto& map_pair1 : map) {
                        add_transition(dfa_out,
                                       map_pair.second, 
                                       new_state2_map[map_pair1.second], 
                                       map_pair1.first);
                    }
                }
            }
        }
    };

    template <typename FiniteAutomaton,
              typename DeterministicFiniteAutomaton>
    inline void
    minimize(const FiniteAutomaton& a_in, 
             DeterministicFiniteAutomaton& a_out) {
        if (is_minimal(a_in)) {
            copy_fa(a_in, a_out);
        } else {
            if (typeid(a_in) != typeid(DeterministicFiniteAutomaton)) {
                DeterministicFiniteAutomaton dfa;
                determinize(dynamic_cast< 
                            typename FiniteAutomaton::NondeterministicFiniteAutomatonType const&>
                            (a_in), dfa);
                MinimizeImpl::apply(dfa, a_out);
            } else {
                MinimizeImpl::apply(dynamic_cast<const DeterministicFiniteAutomaton&>(a_in),
                                    a_out);
            }
            set_minimal_flag(a_out);
        }
    }

    template <typename FiniteAutomaton,
              typename DeterministicFiniteAutomaton>
    inline void
    minimize(const FiniteAutomaton& a_in, 
             std::shared_ptr<const DeterministicFiniteAutomaton>& a_out) {
        if (!is_minimal(a_in)) {
            std::shared_ptr<DeterministicFiniteAutomaton> dfa_ptr = nullptr;
            dfa_ptr = std::make_shared<DeterministicFiniteAutomaton>();
            minimize(a_in, *dfa_ptr);
            a_out = dfa_ptr;
        } else {
            std::shared_ptr<const DeterministicFiniteAutomaton> 
            ptr(dynamic_cast<const DeterministicFiniteAutomaton*>(&a_in));
            a_out = ptr;
        }
    }

    struct DeterminizeImpl {
        template <typename NondeterministicFiniteAutomaton>
        static void 
        make_set_map(const NondeterministicFiniteAutomaton& nfa,
                      typename NondeterministicFiniteAutomaton::States const& states, 
                      typename NondeterministicFiniteAutomaton::Symbol2StatesMap& map) {
            typename NondeterministicFiniteAutomaton::States new_states;
            for (const auto& state : states) {
                if (nfa.transition_map().count(state) == 0) continue;
                for (auto& mapPair : nfa.transition_map().at(state)) {
                    const auto& symbol = mapPair.first;
                    if (symbol == nfa.epsilon()) continue;
                    new_states.clear();
                    get_targets_in_map(nfa, state, symbol, new_states);
                    if (new_states.size() > 0) {
                        epsilon_closure(nfa, new_states, new_states);
                        map[symbol].insert(new_states.begin(), new_states.end());
                    }
                }
            }
        }

        template <typename NondeterministicFiniteAutomaton, 
                  typename DeterministicFiniteAutomaton,
                  typename Merge>
        static void 
        do_determinize(const NondeterministicFiniteAutomaton& nfa,
                       DeterministicFiniteAutomaton& dfa,
                       typename DeterministicFiniteAutomaton::State source,
                       typename NondeterministicFiniteAutomaton::States states,
                       typename NondeterministicFiniteAutomaton::StatesMap states_map,
                       Merge merge) {
            if (has_final_state(nfa, states)) dfa.set_final_state(source);
            typename NondeterministicFiniteAutomaton::Symbol2StatesMap map;
            typedef typename NondeterministicFiniteAutomaton::StatePropType StateProp;
            typedef typename NondeterministicFiniteAutomaton::State State;
            make_set_map(nfa, states, map);
            std::vector<StateProp> props;
            for (auto& map_pair : map) {
                State target = -1;
                auto states_map_iter = states_map.find(map_pair.second);
                if (states_map_iter == states_map.end()) {
                    props.clear();
                    for (const auto& s : map_pair.second)
                        props.push_back(atl::get_property(nfa, s));
                    target = add_state(dfa, merge(props.begin(), props.end()));
                    states_map[map_pair.second] = target;
                    do_determinize(nfa, dfa, target, map_pair.second, states_map, merge);
                } else {
                    target = states_map_iter -> second;
                }
                add_transition(dfa, source, target, map_pair.first);
            }
        }

        template <typename NondeterministicFiniteAutomaton, 
                  typename DeterministicFiniteAutomaton,
                  typename Merge>
        static void apply(const NondeterministicFiniteAutomaton& nfa,
                          DeterministicFiniteAutomaton& dfa,
                          Merge merge) {
            typename NondeterministicFiniteAutomaton::States states;
            epsilon_closure(nfa, states);
            std::vector<typename NondeterministicFiniteAutomaton::StatePropType> props;
            for (const auto& s : states) 
                props.push_back(atl::get_property(nfa, s));
            typename NondeterministicFiniteAutomaton::StatesMap 
                states_map({{states, 
                            add_initial_state(dfa, merge(props.begin(), props.end()))}});
            do_determinize(nfa, dfa, dfa.initial_state(), states, states_map, merge);
        }
    };

    template <typename NondeterministicFiniteAutomaton,
              typename DeterministicFiniteAutomaton,
              typename Merge = UnionMerge<
                               typename NondeterministicFiniteAutomaton::StatePropType> >
    inline void
    determinize(const NondeterministicFiniteAutomaton& a_in, 
                DeterministicFiniteAutomaton& a_out,
                Merge merge = Merge()) {
        if (!is_undeterministic(a_in)) {
            copy_fa(a_in, a_out);
        } else {
            DeterminizeImpl::apply(a_in, a_out, merge);
            set_forwar_reachable_flag(a_out);
        }
    }
}

#endif /* cast_hpp */

