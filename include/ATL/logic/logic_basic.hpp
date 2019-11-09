//
//  logic_basic.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef logic_basic_hpp 
#define logic_basic_hpp

#include "variable/enum_variable/enum_variable.hpp"
#include "variable/int_variable/int_variable.hpp"
#include "variable/bool_variable/bool_variable.hpp"
#include "value/enum_value/enum_value.hpp"
#include "value/int_value/int_value.hpp"
#include "value/bool_value/bool_value.hpp"

namespace atl {
    namespace logic {

        inline EnumValuePtr make_enum_value(const string& name) {
            return std::make_shared<EnumValue>(name);
        }

        inline IntValuePtr make_int_value(int value) {
            return std::make_shared<IntValue>(value);
        }

        inline BoolValuePtr make_bool_value(bool value) {
            return std::make_shared<BoolValue>(value);
        }

        inline EnumVariablePtr make_enum_variable(const string& name, 
                                                  const EnumValuePtrs& range_values) {
            return std::make_shared<EnumVariable>(name, range_values);
        }

        inline IntVariablePtr make_int_variable(const string& name) {
            return std::make_shared<IntVariable>(name);
        }

        inline IntVariablePtr make_int_variable(const string& name, 
                                                IntValuePtr min, IntValuePtr max) {
            return std::make_shared<IntVariable>(name, min, max);
        }

        inline BoolVariablePtr make_bool_variable(const string& name) {
            return std::make_shared<BoolVariable>(name);
        }
    }
}

#endif /* logic_basic_hpp */
