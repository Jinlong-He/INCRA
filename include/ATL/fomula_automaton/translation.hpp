//
//  translation.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/06.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef translation_hpp 
#define translation_hpp
#include "fomula_automaton.hpp"
#include "../basic.hpp"

namespace atl {
    struct Translate2NuXmvImpl {
        template <typename FomularAutomaton>
        static string
        declare(const FomularAutomaton& automaton) {
            string res = "";
            for (auto state : automaton.control_states()) {
                auto variable = atl::get_property(automaton, state);
                res += variable -> to_string() + " : " + 
                       variable -> type() + ";\n";
            }
            for (auto state : automaton.volatile_states()) {
                auto variable = atl::get_property(automaton, state);
                res += variable -> to_string() + " : " + 
                       variable -> type() + ";\n";
            }
            return res;
        }

        template <typename FomularAutomaton>
        static string
        init(const FomularAutomaton& automaton) {
            string res = "";
            for (auto ap : automaton.initial_values()) {
                res += "INIT\n" + ap -> to_string() + "\n";
            }
            return res;
        }

        template <typename FomularAutomaton>
        static string
        next(const FomularAutomaton& automaton) {
            string res = "";
            for (auto state : automaton.control_states()) {
                auto variable = atl::get_property(automaton, state);
                string state_str = "next(" + variable -> to_string() + ") := case\n";
                typename FomularAutomaton::OutTransitionIter first, last;
                for (tie(first, last) = out_transitions(automaton, state); 
                     first != last; first++) {
                    auto fomular = atl::get_property(automaton, *first);
                    auto item = atl::get_property(automaton, atl::target(automaton, *first));
                    state_str += fomular -> to_string() + " : " + item -> to_string() + ";\n";
                }
                res += state_str + "esac;\n";
            }
            return res;
        }

        template <typename FomularAutomaton>
        static string
        apply(const FomularAutomaton& automaton) {
            string res = "VAR\n" + declare(automaton) +
                         init(automaton) +
                         "ASSIGN\n" + next(automaton);
            return res;
        }
    };

    template <typename FomularAutomaton>
    inline string
    translate_to_nuxmv(const FomularAutomaton& automaton) {
        return Translate2NuXmvImpl::apply(automaton);
    }
}

#endif /* translation_hpp */
