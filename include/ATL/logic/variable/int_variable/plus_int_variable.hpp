//
//  plus_int_variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef plus_int_variable_hpp 
#define plus_int_variable_hpp

#include "int_variable.hpp"

namespace atl {
    namespace logic {
        class PlusIntVariable : public IntVariable {
            PlusIntVariable() 
                : variable_(nullptr),
                  item_(nullptr) {}

            PlusIntVariable(VariablePtr variable)
                : variable_(variable),
                  item_(nullptr) {}

            PlusIntVariable(VariablePtr variable, ItemPtr item)
                : variable_(variable),
                  item_(item),
                  str(variable -> to_string() + "+" + item -> to_string()) {}

            PlusIntVariable(const PlusIntVariable& plus_variable)
                : variable_(plus_variable.variable_),
                  item_(plus_variable.item_) {}

            PlusIntVariable& operator=(const PlusIntVariable& plus_variable) {
                if (this != &plus_variable) {
                    variable_ = plus_variable.variable_;
                    item_ = plus_variable.item_;
                }
                return *this;
            }

            VariablePtr variable() const {
                return variable_;
            }

            ItemPtr item() const {
                return item_;
            }

            const string& to_string() const {
                return str;
            }
        private:
            VariablePtr variable_;
            ItemPtr item_;
            string str;
        };
    }
}

#endif /* plus_int_variable_hpp */
