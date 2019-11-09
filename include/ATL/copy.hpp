//
//  copy.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef copy_hpp 
#define copy_hpp 
#include "basic.hpp"

namespace atl {

    struct CopyStatesImpl {
        template <typename AutomatonIn, typename AutomatonOut>
        static void apply(const AutomatonIn& a_in, AutomatonOut& a_out,
                          typename AutomatonIn::State2Map& state2_map) {
            typename AutomatonIn::StateIter first, last;
            for (tie(first, last) = states(a_in); first != last; first++) {
                state2_map[*first] = add_state(a_out, atl::get_property(a_in, *first));
            }
        }
    };

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_states(const AutomatonIn& a_in, AutomatonOut& a_out,
                typename AutomatonIn::State2Map& state2_map) {
        CopyStatesImpl::apply(a_in, a_out, state2_map);
    }

    struct CopyTransitionsImpl {
        template <typename AutomatonIn, typename AutomatonOut>
        static void apply(const AutomatonIn& a_in, AutomatonOut& a_out,
                          typename AutomatonIn::State2Map& state2_map) {
            typename AutomatonIn::TransitionIter first, last;
            for (tie(first, last) = transitions(a_in); first != last; first++) {
                add_transition(a_out,
                               state2_map[atl::source(a_in, *first)], 
                               state2_map[atl::target(a_in, *first)],
                               atl::get_property(a_in, *first));
            }
        }
    };

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_transitions(const AutomatonIn& a_in, AutomatonOut& a_out,
                     typename AutomatonIn::State2Map& state2_map) {
        CopyTransitionsImpl::apply(a_in, a_out, state2_map);
    }

    struct CopyImpl {
        template <typename AutomatonIn, typename AutomatonOut>
        static void apply(const AutomatonIn& a_in, 
                          AutomatonOut& a_out,
                          typename AutomatonIn::State2Map& state2_map) {
            atl::set_property(a_out, atl::get_property(a_in));
            a_out.set_flag(a_in.flag());
            copy_states(a_in, a_out, state2_map);
            copy_transitions(a_in, a_out, state2_map);
        }

        template <typename AutomatonIn, typename AutomatonOut>
        static void apply(const AutomatonIn& a_in, 
                          AutomatonOut& a_out) {
            typename AutomatonIn::State2Map state2_map;
            apply(a_in, a_out, state2_map);
        }
    };

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy(const AutomatonIn& a_in, AutomatonOut& a_out) {
        CopyImpl::apply(a_in, a_out);
    }

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy(const AutomatonIn& a_in, AutomatonOut& a_out,
         typename AutomatonIn::State2Map& state2_map) {
        CopyImpl::apply(a_in, a_out, state2_map);
    }

    struct CopyFaImpl {
        template <typename FiniteAutomatonIn, typename FiniteAutomatonOut>
        static void apply(const FiniteAutomatonIn& a_in, 
                          FiniteAutomatonOut& a_out,
                          typename FiniteAutomatonIn::State2Map& state2_map) {
            atl::copy(a_in, a_out, state2_map);
            a_out.set_alphabet(a_in.alphabet());
            a_out.set_initial_state(state2_map.at(a_in.initial_state()));
            for (const auto state : a_in.final_states()) {
                a_out.set_final_state(state2_map.at(state));
            }
        }

        template <typename FiniteAutomatonIn, typename FiniteAutomatonOut>
        static void apply(const FiniteAutomatonIn& a_in, 
                          FiniteAutomatonOut& a_out) {
            typename FiniteAutomatonIn::State2Map state2_map;
            apply(a_in, a_out, state2_map);
        }
    };

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_fa(const AutomatonIn& a_in, AutomatonOut& a_out) {
        CopyFaImpl::apply(a_in, a_out);
    }

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_fa(const AutomatonIn& a_in, AutomatonOut& a_out,
         typename AutomatonIn::State2Map& state2_map) {
        CopyFaImpl(a_in, a_out, state2_map);
    }

    struct CopyFoaImpl {
        template <typename FiniteAutomatonIn, typename FiniteAutomatonOut>
        static void apply(const FiniteAutomatonIn& a_in, 
                          FiniteAutomatonOut& a_out,
                          typename FiniteAutomatonIn::State2Map& state2_map) {
            atl::copy(a_in, a_out, state2_map);
            for (const auto state : a_in.control_states()) {
                a_out.set_control_state(state2_map.at(state));
            }
        }

        template <typename FiniteAutomatonIn, typename FiniteAutomatonOut>
        static void apply(const FiniteAutomatonIn& a_in, 
                          FiniteAutomatonOut& a_out) {
            typename FiniteAutomatonIn::State2Map state2_map;
            apply(a_in, a_out, state2_map);
        }
    };

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_foa(const AutomatonIn& a_in, AutomatonOut& a_out) {
        CopyFoaImpl::apply(a_in, a_out);
    }

    template <typename AutomatonIn, typename AutomatonOut>
    inline void
    copy_foa(const AutomatonIn& a_in, AutomatonOut& a_out,
         typename AutomatonIn::State2Map& state2_map) {
        CopyFoaImpl(a_in, a_out, state2_map);
    }
}

#endif /* copy_hpp */

