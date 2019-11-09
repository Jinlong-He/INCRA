//
//  variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef variable_hpp 
#define variable_hpp

#include "../item.hpp"
#include "../value/value.hpp"

namespace atl {
    namespace logic {
        class Variable : public Item {
        public:
            Variable() 
                : name_("") {}

            Variable(const string& name)
                : name_(name){}

            Variable(const Variable& variable)
                : name_(variable.name_) {}

            Variable& operator=(const Variable& variable) {
                if (this != &variable) {
                    name_ = variable.name_;
                }
                return *this;
            }

            virtual const string& to_string() const {
                return name_;
            }

            virtual string type() const {
                return "";
            }

        private:
            string name_;
        };
        typedef std::shared_ptr<Variable> VariablePtr;
    }
}

#endif /* variable_hpp */
