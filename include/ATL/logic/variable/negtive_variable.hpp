//
//  negtive_variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef negtive_variable_hpp 
#define negtive_variable_hpp

#include "variable.hpp"

namespace atl {
    namespace logic {
        class NegtiveVariable : public Variable {
            NegtiveVariable() 
                : variable_(nullptr) {}

            NegtiveVariable(VariablePtr variable)
                : variable_(variable) {}

            NegtiveVariable(const NegtiveVariable& neg_variable)
                : variable_(neg_variable.variable_) {}

            NegtiveVariable& operator=(const NegtiveVariable& neg_variable) {
                if (this != &neg_variable) {
                    variable_ = neg_variable.variable_;
                }
                return *this;
            }

            VariablePtr variable() const {
                return variable_;
            }
        private:
            VariablePtr variable_;
        };
    }
}

#endif /* negtive_variable_hpp */
