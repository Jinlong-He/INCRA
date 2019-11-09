//
//  bool_value.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef bool_value_hpp 
#define bool_value_hpp

#include "../value.hpp"

namespace atl {
    namespace logic {
        class BoolValue : public Value {
        public:
            BoolValue() {}

            BoolValue(bool value) {
                if (value) {
                    value_ = "TRUE";
                } else {
                    value_ = "FALSE";
                }
            }

            string type() const {
                return "boolean";
            }
            
            const string& to_string() const {
                return value_;
            }

        private:
            string value_;
        };
        typedef std::shared_ptr<BoolValue> BoolValuePtr;
    }
}

#endif /* bool_value_hpp */
