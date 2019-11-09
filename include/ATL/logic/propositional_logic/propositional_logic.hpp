//
//  propositional_logic.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef propositional_logic_hpp 
#define propositional_logic_hpp

#include "atomic_proposition.hpp"
#include "conjunctive_fomular.hpp"
#include "disjunctive_fomular.hpp"
#include "negtive_fomular.hpp"
#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        
        inline AtomicPropositionPtr
        make_atomic_proposition(ItemPtr lhs, ItemPtr rhs, Predicate predicate = EQU) {
            return std::make_shared<AtomicProposition>(lhs, rhs, predicate);
        }

        inline TruePropositionPtr
        make_true_proposition() {
            return std::make_shared<TrueProposition>();
        }

        inline FalsePropositionPtr
        make_flase_proposition() {
            return std::make_shared<FalseProposition>();
        }

        inline ConjunctiveFomularPtr 
        make_conjunctive_fomular(const std::initializer_list<PropositionalFomularPtr>& list) {
            return std::make_shared<ConjunctiveFomular>(list);
        }

        template <class InputIterator>
        inline ConjunctiveFomularPtr 
        make_conjunctive_fomular(InputIterator first, InputIterator last) {
            return std::make_shared<ConjunctiveFomular>(first, last);
        }

        inline DisjunctiveFomularPtr 
        make_disjunctive_fomular(const std::initializer_list<PropositionalFomularPtr>& list) {
            return std::make_shared<DisjunctiveFomular>(list);
        }

        template <class InputIterator>
        inline DisjunctiveFomularPtr 
        make_disjunctive_fomular(InputIterator first, InputIterator last) {
            return std::make_shared<DisjunctiveFomular>(first, last);
        }

        inline NegtiveFomularPtr 
        make_negtive_fomular(PropositionalFomularPtr fomular) {
            return std::make_shared<NegtiveFomular>(fomular);
        }
        
    }
}

#endif /* propositional_logic_hpp */
