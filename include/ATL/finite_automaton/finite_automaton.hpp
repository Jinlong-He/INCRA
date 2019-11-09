//
//  finite_automaton.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef finite_automaton_hpp 
#define finite_automaton_hpp

#include "../automaton.hpp"


namespace atl {
    enum Direction {forward, backward};

    template <class Symbol, long epsilon, class StateProp, class AutomatonProp> 
        class DeterministicFiniteAutomaton;
    template <class Symbol, long epsilon, class StateProp, class AutomatonProp> 
        class NondeterministicFiniteAutomaton;

    template <class Symbol, 
              long epsilon_,
              class StateProp, 
              class AutomatonProp>
    class FiniteAutomaton 
        : public Automaton<Symbol, StateProp, AutomatonProp> {
    public:
        typedef StateProp StatePropType;
        typedef AutomatonProp AutomatonPropType;
        typedef Symbol SymbolType;
        typedef DeterministicFiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp>
            DeterministicFiniteAutomatonType;

        typedef NondeterministicFiniteAutomaton<Symbol, epsilon_, StateProp, AutomatonProp>
            NondeterministicFiniteAutomatonType;
        typedef atl::Automaton<Symbol, StateProp, AutomatonProp> Base;

        typedef typename Base::Transition Transition;
        typedef typename Base::State State;

        typedef unordered_set<State> States;
        typedef unordered_set<Symbol> Symbols;

        typedef unordered_map<State, State> State2Map;

    public:

        FiniteAutomaton() 
            : Base() {}

        FiniteAutomaton(const AutomatonProp& graph_prop)
            : Base(graph_prop), 
              initial_state_(-1) {}

        FiniteAutomaton(const FiniteAutomaton& automaton) 
            : Base(atl::get_property(automaton)) {
            atl::copy_fa(automaton, *this);
        }

        FiniteAutomaton& operator=(const FiniteAutomaton& automaton) {
            if (&automaton != this) {
                typename Base::BoostGraphPtr ptr(new typename Base::BoostGraph());
                this -> graph().swap(ptr);
                atl::copy_fa(automaton, *this);
            }
            return *this;
        }

        virtual void clear() {
            Base::clear();
            initial_state_ = -1;
            final_states_.clear();
            alphabet_.clear();
        }

        void clear_states() {
            final_states_.clear();
            initial_state_ = -1;
        }

        Transition add_transition(State source, State target) {
            return Base::add_transition(source, target);
        }

        virtual Transition add_transition(State source, State target,
                                          const Symbol& prop) {
            return Base::add_transition(source, target, prop);
        }

        const Symbols& alphabet() const {
            return alphabet_;
        }

        void set_alphabet(const Symbols& alphabet) {
            alphabet_.insert(alphabet.begin(), alphabet.end());
        }

        State initial_state() const {
            return initial_state_;
        }

        void set_initial_state(State state) {
            initial_state_ = state;
        }

        const States& final_states() const {
            return final_states_;
        }

        void set_final_states(const States& states) {
            final_states_.insert(states.begin(), states.end());
        }

        void set_final_state(State state) {
            final_states_.insert(state);
        }

        Symbol epsilon() const {
            return Symbol(epsilon_);
        }
    private:
        Symbols alphabet_;
        State initial_state_;
        States final_states_;
    };

    template <typename FiniteAutomaton>
    inline typename FiniteAutomaton::State
    add_initial_state(FiniteAutomaton& automaton,
            typename FiniteAutomaton::StatePropType prop) {
        typename FiniteAutomaton::State state = add_state(automaton, prop);
        automaton.set_initial_state(state);
        return state;
    }

    template <typename FiniteAutomaton>
    inline typename FiniteAutomaton::State
    add_initial_state(FiniteAutomaton& automaton) {
        typename FiniteAutomaton::State state = add_state(automaton);
        automaton.set_initial_state(state);
        return state;
    }

    template <typename FiniteAutomaton>
    inline typename FiniteAutomaton::State
    add_final_state(FiniteAutomaton& automaton,
                    typename FiniteAutomaton::StatePropType prop) {
        typename FiniteAutomaton::State state = add_state(automaton, prop);
        automaton.set_final_state(state);
        return state;
    }

    template <typename FiniteAutomaton>
    inline typename FiniteAutomaton::State
    add_final_state(FiniteAutomaton& automaton) {
        typename FiniteAutomaton::State state = add_state(automaton);
        automaton.set_final_state(state);
        return state;
    }

    template <typename FiniteAutomaton>
    inline bool
    is_final_state(const FiniteAutomaton& automaton,
                   typename FiniteAutomaton::State state) {
        return automaton.final_states().count(state);
    }

    template <typename FiniteAutomaton>
    inline bool
    has_final_state(const FiniteAutomaton& automaton,
                    typename FiniteAutomaton::States states) {
        typename FiniteAutomaton::States res;
        util::set_intersection(states, automaton.final_states(), res);
        return res.size();
    }

    template <typename FiniteAutomaton>
    inline void 
    set_forwar_reachable_flag(FiniteAutomaton& automaton, bool b = true) {
        automaton.set_flag(1, b);
        automaton.set_flag(0, 0);
    }

    template <typename FiniteAutomaton>
    inline bool
    is_forward_reachable(const FiniteAutomaton& automaton) {
        return (automaton.flag(1) & automaton.flag(0));
    }

    template <typename FiniteAutomaton>
    inline void 
    set_minimal_flag(FiniteAutomaton& automaton, bool b = true) {
        automaton.set_flag(2, b);
        automaton.set_flag(1, 1);
        automaton.set_flag(0, 0);
    }

    template <typename FiniteAutomaton>
    inline bool
    is_minimal(const FiniteAutomaton& automaton) {
        return (automaton.flag(2) & automaton.flag(0));
    }

    template <typename FiniteAutomaton>
    inline void 
    set_undeterministic_flag(FiniteAutomaton& automaton, bool b = true) {
        automaton.set_flag(3, b);
    }

    template <typename FiniteAutomaton>
    inline bool
    is_undeterministic(const FiniteAutomaton& automaton) {
        return (automaton.flag(3) | automaton.flag(4));
    }

    template <typename FiniteAutomaton>
    inline void 
    set_epsilon_flag(FiniteAutomaton& automaton, bool b = true) {
        automaton.set_flag(4, b);
    }

    template <typename FiniteAutomaton>
    inline bool
    has_epsilon_transition(const FiniteAutomaton& automaton) {
        return automaton.flag(4);
    }
}

#endif /* finite_automaton_hpp */
