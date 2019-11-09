//
//  implication_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef implication_fomular_hpp 
#define implication_fomular_hpp

#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        class ImplicationFomular : public PropositionalFomular {
        public:
            ImplicationFomular()
                : PropositionalFomular(),
                  fomular_lhs_(nullptr),
                  fomular_rhs_(nullptr) {}

            ImplicationFomular(PropositionalFomularPtr fomular)
                : fomular_lhs_(fomular),
                  fomular_rhs_(nullptr) {}

            ImplicationFomular(PropositionalFomularPtr lhs, PropositionalFomularPtr rhs)
                : fomular_lhs_(lhs),
                  fomular_rhs_(rhs) {}

            ImplicationFomular(const ImplicationFomular& imp_fomular) 
                : PropositionalFomular(),
                  fomular_lhs_(imp_fomular.fomular_lhs_),
                  fomular_rhs_(imp_fomular.fomular_rhs_) {}

            ImplicationFomular& operator=(const ImplicationFomular& imp_fomular) {
                if (this != &imp_fomular) {
                    PropositionalFomular::operator=(imp_fomular);
                    fomular_lhs_ = imp_fomular.fomular_lhs_;
                    fomular_rhs_ = imp_fomular.fomular_rhs_;
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
                string res = "(" + fomular_lhs_ -> to_string() + " -> " +
                            fomular_rhs_ -> to_string() + ")";    
                return res;
            }
        private:
            PropositionalFomularPtr fomular_lhs_;
            PropositionalFomularPtr fomular_rhs_;
        };
    }
}

#endif /* implication_fomular_hpp */
