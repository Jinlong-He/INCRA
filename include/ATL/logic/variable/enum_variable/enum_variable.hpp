//
//  enum_variable.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef enum_variable_hpp 
#define enum_variable_hpp

#include "../variable.hpp"
#include "../../value/enum_value/enum_value.hpp"

namespace atl {
    namespace logic {
        class EnumVariable : public Variable {
        public:
            EnumVariable()
                : Variable() {}

            EnumVariable(const string& name, const EnumValuePtrs& range_values)
                : Variable(name),
                  range_values_(range_values) {}

            EnumVariable(const EnumVariable& variable)
                : Variable(variable),
                  range_values_(variable.range_values_) {}

            EnumVariable& operator=(const EnumVariable& variable) {
                if (this != &variable) {
                    Variable::operator=(variable);
                    range_values_.assign(variable.range_values_.begin(),
                                         variable.range_values_.end());
                }
                return *this;
            }

            const EnumValuePtrs& range_values() const {
                return range_values_;
            }

            string type() const {
                string res = "{";
                for (auto value : range_values_) {
                    res += value -> to_string() + ",";
                }
                res[res.length() - 1] = '}';
                return res;
            }

        private:
            EnumValuePtrs range_values_;
        };
        typedef std::shared_ptr<EnumVariable> EnumVariablePtr;

    }
}

#endif /* enum_variable_hpp */
