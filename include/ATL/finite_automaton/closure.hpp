//
//  closure.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef closure_hpp 
#define closure_hpp 

#include "finite_automaton.hpp"
//#include "deterministic_finite_automaton.hpp"

namespace atl {
    struct ReachableClosureImpl {
        template <typename FiniteAutomaton>
        static void apply(const FiniteAutomaton& fa,
                          typename FiniteAutomaton::States const& states_in,
                          typename FiniteAutomaton::States& states_out,
                          Direction direction = forward) {
            typedef typename FiniteAutomaton::State State;
            typedef typename FiniteAutomaton::States States;
            typedef typename FiniteAutomaton::InTransitionIter InTransitionIter;
            typedef typename FiniteAutomaton::OutTransitionIter OutTransitionIter;
            states_out.insert(states_in.begin(), states_in.end());
            States work(states_in), new_work;
            while (work.size() > 0) {
                for (auto state : work) {
                    if (direction == forward) {
                        OutTransitionIter first, last;
                        tie(first, last) = out_transitions(fa, state);
                        for (; first != last; first++) {
                            State new_state = target(fa, *first);
                            if (states_out.insert(new_state).second) {
                                new_work.insert(new_state);
                            }
                        }
                    } else {
                        InTransitionIter first, last;
                        tie(first, last) = in_transitions(fa, state);
                        for (; first != last; first++) {
                            State new_state = source(fa, *first);
                            if (states_out.insert(new_state).second) {
                                new_work.insert(new_state);
                            }
                        }
                    }
                }
                work.clear();
                if (new_work.size() > 0) {
                    work.insert(new_work.begin(), new_work.end());
                    new_work.clear();
                }
            }
        }
    };

    template <typename FiniteAutomaton>
    inline void
    reachable_closure(const FiniteAutomaton& fa,
                     typename FiniteAutomaton::States const& states_in,
                     typename FiniteAutomaton::States& states_out,
                     Direction direction = forward) {
        ReachableClosureImpl::apply(fa, states_in, states_out, direction);
    }

    template <typename FiniteAutomaton>
    inline void
    reachable_closure(const FiniteAutomaton& fa,
                     typename FiniteAutomaton::States& reachable_states) {
            typename FiniteAutomaton::States forward_states({fa.initial_state()}),
                                             backward_states(fa.final_states());
            atl::reachable_closure(fa, forward_states, forward_states, forward);
            atl::reachable_closure(fa, backward_states, backward_states, backward);
            util::set_intersection(forward_states, backward_states, reachable_states);
    }

    struct EpsilonClosureImpl {
        template <typename NondeterministicFiniteAutomaton>
        static void apply(const NondeterministicFiniteAutomaton& nfa,
                          typename NondeterministicFiniteAutomaton::States const& states_in,
                          typename NondeterministicFiniteAutomaton::States& states_out) {
            typedef typename NondeterministicFiniteAutomaton::States States;
            states_out.insert(states_in.begin(), states_in.end());
            if (!has_epsilon_transition(nfa)) return;
            States work(states_in), new_work, targets;
            while (work.size()) {
                targets.clear();
                get_targets_in_map(nfa, work, nfa.epsilon(), targets);
                for (auto new_state : targets) {
                    if (states_out.insert(new_state).second) {
                        new_work.insert(new_state);
                    }
                }
                work.clear();
                if (new_work.size()) {
                    work.insert(new_work.begin(), new_work.end());
                    new_work.clear();
                }
            }
        }
    };

    template <typename NondeterministicFiniteAutomaton>
    inline void
    epsilon_closure(const NondeterministicFiniteAutomaton& fa,
                    typename NondeterministicFiniteAutomaton::States const& states_in,
                    typename NondeterministicFiniteAutomaton::States& states_out) {
        EpsilonClosureImpl::apply(fa, states_in, states_out);
    }

    template <typename NondeterministicFiniteAutomaton>
    inline void
    epsilon_closure(const NondeterministicFiniteAutomaton& fa,
                    typename NondeterministicFiniteAutomaton::States& closure) {
            typename NondeterministicFiniteAutomaton::States states({fa.initial_state()});
            epsilon_closure(fa, states, closure);
    }
}

#endif /* closure_hpp */
