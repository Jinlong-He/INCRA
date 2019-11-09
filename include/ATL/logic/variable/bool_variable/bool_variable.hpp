//
//  bool_variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef bool_variable_hpp 
#define bool_variable_hpp

#include "../variable.hpp"
#include "../../value/bool_value/bool_value.hpp"

namespace atl {
    namespace logic {
        class BoolVariable : public Variable {
        public:
            BoolVariable()
                : Variable() {}

            BoolVariable(const string& name)
                : Variable(name) {}

            BoolVariable(const BoolVariable& variable)
                : Variable(variable) {}

            BoolVariable& operator=(const BoolVariable& variable) {
                if (this != &variable) {
                    Variable::operator=(variable);
                }
                return *this;
            }

            string type() const {
                return "boolean";
            }

        private:
        };
        typedef std::shared_ptr<BoolVariable> BoolVariablePtr;
    }
}

#endif /* bool_variable_hpp */
