//
//  equivalence_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef equivalence_fomular_hpp 
#define equivalence_fomular_hpp

#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        class EquivalenceFomular : public PropositionalFomular {
        public:
            EquivalenceFomular()
                : PropositionalFomular(),
                  fomular_lhs_(nullptr),
                  fomular_rhs_(nullptr) {}

            EquivalenceFomular(PropositionalFomularPtr fomular)
                : fomular_lhs_(fomular),
                  fomular_rhs_(nullptr) {}

            EquivalenceFomular(PropositionalFomularPtr lhs, PropositionalFomularPtr rhs)
                : fomular_lhs_(lhs),
                  fomular_rhs_(rhs) {}

            EquivalenceFomular(const EquivalenceFomular& equ_fomular) 
                : PropositionalFomular(),
                  fomular_lhs_(equ_fomular.fomular_lhs_),
                  fomular_rhs_(equ_fomular.fomular_rhs_) {}

            EquivalenceFomular& operator=(const EquivalenceFomular& equ_fomular) {
                if (this != &equ_fomular) {
                    PropositionalFomular::operator=(equ_fomular);
                    fomular_lhs_ = equ_fomular.fomular_lhs_;
                    fomular_rhs_ = equ_fomular.fomular_rhs_;
                }
                return *this;
            }

            PropositionalFomularPtr fomular_lhs() const {
                return fomular_lhs_;
            }

            PropositionalFomularPtr fomular_rhs() const {
                return fomular_rhs_;
            }

            string to_string() const {
                string res = "(" + fomular_lhs_ -> to_string() + " = " +
                            fomular_rhs_ -> to_string() + ")";    
                return res;
            }
        private:
            PropositionalFomularPtr fomular_lhs_;
            PropositionalFomularPtr fomular_rhs_;
        };
    }
}

#endif /* equivalence_fomular_hpp */
