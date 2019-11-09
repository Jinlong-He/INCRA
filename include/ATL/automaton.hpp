//
//  automaton.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/10/27.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef automaton_hpp 
#define automaton_hpp

#include "object.hpp"
#include "copy.hpp"

namespace atl {
    template <class TransitionProp, 
              class StateProp, 
              class AutomatonProp>
    class Automaton : public Object {
    public:
        typedef StateProp StatePropType;
        typedef AutomatonProp AutomatonPropType;
        typedef TransitionProp TransitionPropType;

        typedef adjacency_list<listS, vecS, bidirectionalS, StateProp, TransitionProp, AutomatonProp> BoostGraph;
        typedef typename graph_traits<BoostGraph>::edge_descriptor Transition;
        typedef typename graph_traits<BoostGraph>::edge_iterator TransitionIter;
        typedef typename graph_traits<BoostGraph>::in_edge_iterator InTransitionIter;
        typedef typename graph_traits<BoostGraph>::out_edge_iterator OutTransitionIter;
        typedef typename graph_traits<BoostGraph>::vertex_descriptor State;
        typedef typename graph_traits<BoostGraph>::vertex_iterator StateIter;

        typedef unordered_map<State, State> State2Map;

    public:

        Automaton() 
            : graph_(new BoostGraph()),
              flag_(0) {}

        Automaton(const AutomatonProp& graph_prop)
            : graph_(new BoostGraph(graph_prop)),
              flag_(0) {}

        Automaton(const Automaton& automaton) 
            : graph_(new BoostGraph()) {
            atl::copy(automaton, *this);
        }

        Automaton& operator=(const Automaton& automaton) {
            if (&automaton != this) {
                BoostGraphPtr ptr(new BoostGraph());
                graph_.swap(ptr);
                atl::copy(automaton, *this);
            }
            return *this;
        }

        virtual void clear() {
            if (flag_ == 0) return;
            graph_ -> clear();
            flag_ = 0;
        }

        virtual void clear_states() {
        }

        virtual Transition add_transition(State source, State target) {
            return atl::add_edge(*this, source, target);
        }

        virtual Transition add_transition(State source, State target,
                                          const TransitionProp& prop) {
            return atl::add_edge(*this, source, target, prop);
        }

        BoostGraph& graph() {
            return *graph_;
        } 

        const BoostGraph& graph() const {
            return *graph_;
        }

        Flag flag() const {
            return flag_;
        }

        bool flag(ID i) const {
            return (flag_ & (1 << i)) == (1 << i);
        }

        void set_flag(Flag flag) {
            flag_ = flag;
        }

        void set_flag(ID i, bool b) {
            flag_ = b ? (flag_ | (1 << i)) : (flag_ & ~(1 << i));
        }
    private:
        typedef scoped_ptr<BoostGraph> BoostGraphPtr;
        BoostGraphPtr graph_;
        Flag flag_;
    };


}

#endif /* automaton_hpp */
