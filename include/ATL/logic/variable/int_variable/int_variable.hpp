//
//  int_variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef int_variable_hpp 
#define int_variable_hpp

#include "../variable.hpp"
#include "../../value/int_value/int_value.hpp"

namespace atl {
    namespace logic {
        class IntVariable : public Variable {
        public:
            IntVariable()
                : Variable(),
                  min_(nullptr),
                  max_(nullptr) {}

            IntVariable(const string& name)
                : Variable(name),
                  min_(nullptr),
                  max_(nullptr) {}

            IntVariable(const string& name, IntValuePtr min, IntValuePtr max)
                : Variable(name),
                  min_(min),
                  max_(max) {}

            IntVariable(const string& name, const IntValuePtrs& range_values)
                : Variable(name),
                  range_values_(range_values),
                  min_(nullptr),
                  max_(nullptr) {}

            IntVariable(const IntVariable& variable)
                : Variable(variable),
                  range_values_(variable.range_values_) {}

            IntVariable& operator=(const IntVariable& variable) {
                if (this != &variable) {
                    Variable::operator=(variable);
                    range_values_.assign(variable.range_values_.begin(),
                                         variable.range_values_.end());
                }
                return *this;
            }

            const IntValuePtrs& range_values() const {
                return range_values_;
            }

            virtual const string& to_string() const {
                return Variable::to_string();
            }

            string type() const {
                if (min_ != nullptr && max_ != nullptr) 
                    return min_ -> to_string() + ".." + max_ -> to_string();
                if (range_values_.size() == 0) return "integer";
                return "";
            }

        private:
            IntValuePtrs range_values_;
            IntValuePtr min_;
            IntValuePtr max_;
        };
        typedef std::shared_ptr<IntVariable> IntVariablePtr;
    }
}

#endif /* int_variable_hpp */
