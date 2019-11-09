//
//  fomula_automaton.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/05.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef fomula_automaton_hpp 
#define fomula_automaton_hpp

#include "../automaton.hpp"
#include "../logic/propositional_logic/propositional_logic.hpp"
#include "../logic/logic_basic.hpp"


namespace atl {

    template <class AutomatonProp = no_property>
    class FomularAutomaton 
        : public Automaton<logic::PropositionalFomularPtr, 
                           logic::ItemPtr, AutomatonProp> {
    public:
        typedef Automaton<logic::PropositionalFomularPtr, logic::ItemPtr, AutomatonProp> Base;
        typedef typename Base::State State;
        typedef typename Base::StateIter StateIter;
        typedef typename Base::OutTransitionIter OutTransitionIter;

        typedef unordered_set<State> States;

        FomularAutomaton()
            : Base() {}

        FomularAutomaton(const AutomatonProp& prop)
            : Base(prop) {}

        FomularAutomaton(const FomularAutomaton& automaton)
            : Base(atl::get_property(automaton)) {
            atl::copy_foa(automaton, *this);
        }
        
        FomularAutomaton& operator=(const FomularAutomaton& automaton) {
            if (this == &automaton) {
                typename Base::BoostGraphPtr ptr(new typename Base::BoostGraph());
                this -> graph().swap(ptr);
                atl::copy_foa(automaton, *this);
            }
            return *this;
        }

        const States& control_states() const {
            return control_states_;
        }

        void set_control_states(const State& states) {
            control_states_.assign(states.begin(), states.end());
        }

        void set_control_state(State state) {
            control_states_.insert(state);
        }

        const States& volatile_states() const {
            return volatile_states_;
        }

        void set_volatile_states(const State& states) {
            volatile_states_.assign(states.begin(), states.end());
        }

        void set_volatile_state(State state) {
            volatile_states_.insert(state);
        }

        const logic::AtomicPropositionPtrs& initial_values() const {
            return initial_values_;
        }

        void set_initial_values(logic::AtomicPropositionPtrs aps) {
            initial_values_.assign(aps.begin(), aps.end());
        }

        void set_initial_value(logic::AtomicPropositionPtr ap) {
            initial_values_.push_back(ap);
        }

    private:
        States control_states_;
        States volatile_states_;
        logic::AtomicPropositionPtrs initial_values_;
    };

    template <typename FomularAutomaton>
    inline typename FomularAutomaton::State 
    add_volatile_state(FomularAutomaton& automaton, 
                      logic::VariablePtr variable) {
        typedef typename FomularAutomaton::State State;
        State state = add_state(automaton, variable);
        automaton.set_volatile_state(state);
        return state;
    }

    template <typename FomularAutomaton>
    inline typename FomularAutomaton::State 
    add_control_state(FomularAutomaton& automaton, 
                      logic::VariablePtr variable,
                      logic::AtomicPropositionPtr ap) {
        typedef typename FomularAutomaton::State State;
        State state = add_state(automaton, variable);
        automaton.set_control_state(state);
        automaton.set_initial_value(ap);
        return state;
    }

}

#endif /* fomula_automaton_hpp */
