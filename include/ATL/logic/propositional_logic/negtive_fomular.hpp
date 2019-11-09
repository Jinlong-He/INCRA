//
//  negtive_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef negtive_fomular_hpp 
#define negtive_fomular_hpp

#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        class NegtiveFomular : public PropositionalFomular {
        public:
            NegtiveFomular()
                : PropositionalFomular(),
                  fomular_(nullptr) {}

            NegtiveFomular(PropositionalFomularPtr fomular)
                : fomular_(fomular) {}

            NegtiveFomular(const NegtiveFomular& neg_fomular) 
                : PropositionalFomular(neg_fomular),
                  fomular_(neg_fomular.fomular_) {}

            NegtiveFomular& operator=(const NegtiveFomular& neg_fomular) {
                if (this != &neg_fomular) {
                    PropositionalFomular::operator=(neg_fomular);
                    fomular_ = neg_fomular.fomular_;
                }
                return *this;
            }

            PropositionalFomularPtr fomular() const {
                return fomular_;
            }

            string to_string() const {
                string res = "!" + fomular_ -> to_string() + "";
                return res;
            }
        private:
            PropositionalFomularPtr fomular_;
        };
        typedef std::shared_ptr<NegtiveFomular> NegtiveFomularPtr;
    }
}

#endif /* negtive_fomular_hpp */
