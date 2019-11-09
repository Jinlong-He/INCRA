//
//  enum_value.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef enum_value_hpp 
#define enum_value_hpp

#include "../value.hpp"

namespace atl {
    namespace logic {
        class EnumValue : public Value {
        public:
            EnumValue() 
                : value_("") {}

            EnumValue(const string& value) 
                : value_(value) {}

            const string& to_string() const {
                return value_;
            }

            string type() const {
                return "enum";
            }
        private:
            string value_;
        };
        typedef std::shared_ptr<EnumValue> EnumValuePtr;
        typedef std::list<EnumValuePtr> EnumValuePtrs;
    }
}

#endif /* enum_value_hpp */
