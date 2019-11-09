//
//  value.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef value_hpp 
#define value_hpp

#include "../item.hpp"

namespace atl {
    namespace logic {
        class Value : public Item {
        public:
            virtual const string& to_string() const = 0;
            virtual string type() const = 0;
        private:
        };
        typedef std::shared_ptr<Value> ValuePtr;
    }
}

#endif /* value_hpp */
