//
//  deterministic_finite_automaton.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/31.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef deterministic_finite_automaton_hpp 
#define deterministic_finite_automaton_hpp

#include "finite_automaton.hpp"

namespace atl {
    template <class Symbol, long epsilon, class StateProp, class AutomatonProp> 
        class NondeterministicFiniteAutomaton;
    template <class Symbol = char, 
              long epsilon_ = Symbol(),
              class StateProp = no_property, 
              class AutomatonProp = no_property>
    class DeterministicFiniteAutomaton 
        : public FiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp> {
    public:
        typedef StateProp StatePropType;
        typedef AutomatonProp AutomatonPropType;
        typedef Symbol SymbolType;
        typedef DeterministicFiniteAutomaton DeterministicFiniteAutomatonType;

        typedef atl::FiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp> Base;

        typedef typename Base::Transition Transition;
        typedef typename Base::State State;

        typedef pair<State, State> StatePair;

        typedef unordered_map<State, State> State2Map;
        typedef unordered_map<State, unordered_map<Symbol, State> > TransitionMap;
        typedef unordered_map<StatePair, State> StatePairMap;
        typedef unordered_map<Symbol, StatePair> Symbol2StatePairMap;

    public:
        DeterministicFiniteAutomaton(const AutomatonProp& graph_prop = AutomatonProp())
            : Base(graph_prop) {}

        DeterministicFiniteAutomaton(const DeterministicFiniteAutomaton& automaton) 
            : Base(automaton) {
        }

        DeterministicFiniteAutomaton& operator=(
                const DeterministicFiniteAutomaton& automaton) {
            if (&automaton != this) {
                Base::operator=(automaton);
            }
            return *this;
        }

        ~DeterministicFiniteAutomaton() {
            //cout << "delete dfa" << endl;
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
            transition_map_[source][prop] = target;
            return Base::add_transition(source, target, prop);
        }

    private:
        TransitionMap transition_map_;
    };
}

#endif /* deterministic_finite_automaton_hpp */
