//
//  nondeterministic_finite_automaton.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/31.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef nondeterministic_finite_automaton_hpp 
#define nondeterministic_finite_automaton_hpp

#include "finite_automaton.hpp"

namespace atl {
    template <class Symbol = char, 
              long epsilon_ = 0,
              class StateProp = no_property, 
              class AutomatonProp = no_property>
    class NondeterministicFiniteAutomaton 
        : public FiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp> {
    public:
        typedef StateProp StatePropType;
        typedef AutomatonProp AutomatonPropType;
        typedef Symbol SymbolType;
        typedef DeterministicFiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp>
            DeterministicFiniteAutomatonType;

        typedef atl::FiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp> Base;

        typedef typename Base::Transition Transition;
        typedef typename Base::State State;

        typedef unordered_set<State> States;

        typedef unordered_map<State, State> State2Map;
        typedef unordered_map<States, State> StatesMap;
        typedef unordered_map<Symbol, States> Symbol2StatesMap;
        typedef unordered_map<State, unordered_map<Symbol, States> > TransitionMap;

    public:

        NondeterministicFiniteAutomaton(const AutomatonProp& graph_prop = AutomatonProp())
            : Base(graph_prop) {}

        NondeterministicFiniteAutomaton(const NondeterministicFiniteAutomaton& automaton) 
            : Base(automaton) {}

        NondeterministicFiniteAutomaton& operator=(
                const NondeterministicFiniteAutomaton& automaton) {
            if (&automaton != this) {
                Base::operator=(automaton);
            }
            return *this;
        }

        ~NondeterministicFiniteAutomaton() {
            //cout << "delete nfa" << endl;
        }

        void clear() {
            Base::clear();
            transition_map_.clear();
        }

        const TransitionMap& transition_map() const {
            return transition_map_;
        }

        Transition add_transition(State source, State target,
                                  const Symbol& prop) {
            States& targets = transition_map_[source][prop];
            targets.insert(target);
            if (targets.size()) set_undeterministic_flag(*this);
            return Base::add_transition(source, target, prop);
        }

    private:
        TransitionMap transition_map_;
    };

    template <typename NondeterministicFiniteAutomaton>
    inline typename NondeterministicFiniteAutomaton::Transition
    add_epsilon_transition(NondeterministicFiniteAutomaton& nfa,
                           typename NondeterministicFiniteAutomaton::State source, 
                           typename NondeterministicFiniteAutomaton::State target) {
        set_epsilon_flag(nfa);
        return add_transition(nfa, source, target, nfa.epsilon());
    }

    template <typename NondeterministicFiniteAutomaton>
    inline void 
    get_targets_in_map(const NondeterministicFiniteAutomaton& nfa,
                             typename NondeterministicFiniteAutomaton::State source,
                             typename NondeterministicFiniteAutomaton::SymbolType symbol,
                             typename NondeterministicFiniteAutomaton::States& targets) {
        auto transition_map_iter = nfa.transition_map().find(source);
        if (transition_map_iter != nfa.transition_map().end()) {
            const auto& map = transition_map_iter -> second;
            auto map_iter = map.find(symbol);
            if (map_iter != map.end()) {
                targets.insert(map_iter -> second.begin(), map_iter -> second.end());
            }
        }
    }

    template <typename NondeterministicFiniteAutomaton>
    inline void 
    get_targets_in_map(const NondeterministicFiniteAutomaton& nfa,
                             typename NondeterministicFiniteAutomaton::States const& sources,
                             typename NondeterministicFiniteAutomaton::SymbolType symbol,
                             typename NondeterministicFiniteAutomaton::States& targets) {
        for (auto source : sources) {
            get_targets_in_map(nfa, source, symbol, targets);
        }
    }
}

#endif /* nondeterministic_finite_automaton_hpp */
