//
//  int_value.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef int_value_hpp 
#define int_value_hpp

#include "../value.hpp"

namespace atl {
    namespace logic {
        class IntValue : public Value {
        public:
            IntValue()
                :value_(0) {}

            IntValue(int value)
                :value_(std::to_string(value)) {}

            const string& to_string() const {
                return value_;
            }

            string type() const {
                return "integer";
            }
        private:
            string value_;
        };
        typedef std::shared_ptr<IntValue> IntValuePtr;
        typedef std::list<IntValuePtr> IntValuePtrs;
    }
}

#endif /* int_value_hpp */
