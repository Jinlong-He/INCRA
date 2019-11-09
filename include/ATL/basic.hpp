//
//  basic.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef basic_hpp 
#define basic_hpp

#include "object.hpp"
namespace atl {
    template <typename Automaton, typename Property>
    inline void set_property(Automaton& automaton,
                             const Property& prop) {
        automaton.graph()[graph_bundle_t()] = prop;
    }

    template <typename Automaton, typename Tag, typename Property>
    inline void set_property(Automaton& automaton,
                             Tag tag, const Property& prop) {
        automaton.graph()[tag] = prop;
    }

    template <typename Automaton>
    inline typename Automaton::AutomatonPropType const& 
    get_property(const Automaton& automaton) {
        return automaton.graph()[graph_bundle_t()];
    }

    template <typename Automaton>
    inline typename Automaton::StatePropType const& 
    get_property(const Automaton& automaton,
                 typename Automaton::State state) {
        return automaton.graph()[state];
    }

    template <typename Automaton>
    inline typename Automaton::TransitionPropType const& 
    get_property(const Automaton& automaton,
                 typename Automaton::Transition transition) {
        return automaton.graph()[transition];
    }

    template <typename Automaton>
    inline typename Automaton::State
    add_state(Automaton& automaton) {
        set_modified_flag(automaton);
        return boost::add_vertex(automaton.graph());
    }

    template <typename Automaton>
    inline typename Automaton::State
    add_state(Automaton& automaton,
              typename Automaton::StatePropType const& prop) {
        set_modified_flag(automaton);
        return boost::add_vertex(prop, automaton.graph());
    }

    template <typename Automaton>
    inline typename Automaton::Transition
    add_edge(Automaton& automaton,
             typename Automaton::State source, 
             typename Automaton::State target) {
        set_modified_flag(automaton);
        return boost::add_edge(source, target, automaton.graph()).first;
    }

    template <typename Automaton>
    inline typename Automaton::Transition
    add_edge(Automaton& automaton,
             typename Automaton::State source, 
             typename Automaton::State target,
             typename Automaton::TransitionPropType const& prop) {
        set_modified_flag(automaton);
        return boost::add_edge(source, target, prop, automaton.graph()).first;
    }

    template <typename Automaton>
    inline typename Automaton::Transition
    add_transition(Automaton& automaton,
                   typename Automaton::State source, 
                   typename Automaton::State target) {
        return automaton.add_transition(source, target);
    }

    template <typename Automaton>
    inline typename Automaton::Transition
    add_transition(Automaton& automaton,
                   typename Automaton::State source, 
                   typename Automaton::State target,
                   typename Automaton::TransitionPropType const& prop) {
        return automaton.add_transition(source, target, prop);
    }

    template <typename Automaton>
    inline pair<typename Automaton::StateIter, 
                typename Automaton::StateIter>
    states(const Automaton& automaton) {
        return boost::vertices(automaton.graph());
    }

    template <typename Automaton>
    inline pair<typename Automaton::TransitionIter, 
                typename Automaton::TransitionIter>
    transitions(const Automaton& automaton) {
        return boost::edges(automaton.graph());
    }

    template <typename Automaton>
    inline typename Automaton::State
    source(const Automaton& automaton,
           typename Automaton::Transition transition) {
        return boost::source(transition, automaton.graph());
    }

    template <typename Automaton>
    inline typename Automaton::State
    target(const Automaton& automaton,
           typename Automaton::Transition transition) {
        return boost::target(transition, automaton.graph());
    }

    template <typename Automaton>
    inline pair<typename Automaton::InTransitionIter, 
                typename Automaton::InTransitionIter>
    in_transitions(const Automaton& automaton,
                   typename Automaton::State state) {
        return boost::in_edges(state, automaton.graph());
    }

    template <typename Automaton>
    inline pair<typename Automaton::OutTransitionIter, 
                typename Automaton::OutTransitionIter>
    out_transitions(const Automaton& automaton,
                    typename Automaton::State state) {
        return boost::out_edges(state, automaton.graph());
    }

    template <typename Automaton>
    inline void
    remove_state(Automaton& automaton,
                 typename Automaton::State state) {
        boost::remove_vertex(state, automaton.graph());
    }

    template <typename Automaton>
    inline void
    clear_state(Automaton& automaton,
                typename Automaton::State state) {
        boost::clear_vertex(state, automaton.graph());
    }

    template <typename Automaton>
    inline void
    clear_states(Automaton& automaton) {
        typename Automaton::StateIter first, last;
        tie(first, last) = states(automaton);
        last--;
        for (; first != last; last--) {
            clear_state(automaton, *last);
            remove_state(automaton, *last);
        }
        remove_state(automaton, *first);
        automaton.clear_states();
    }

    template <typename FiniteAutomaton>
    inline void 
    set_modified_flag(FiniteAutomaton& automaton, bool b = true) {
        automaton.set_flag(0, b);
    }

    template <typename FiniteAutomaton>
    inline bool
    is_modified(const FiniteAutomaton& automaton) {
        return automaton.flag(0);
    }

    template <typename Automaton>
    inline void
    print(const Automaton& automaton) {
        typename Automaton::StateIter first, last;
        for (tie(first, last) = states(automaton); first != last; first++) {
            cout << *first << "{" << atl::get_property(automaton, *first) << "}: " << endl;
            typename Automaton::OutTransitionIter ei, end;
            for (tie(ei, end) = out_transitions(automaton, *first); ei != end; ei++) {
                cout << *first << "->" << atl::target(automaton, *ei) << "{" << atl::get_property(automaton, *ei) << "}" << endl;
            }
        }
    }
}

#endif /* basic_hpp */
