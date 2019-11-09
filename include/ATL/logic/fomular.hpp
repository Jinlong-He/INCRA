//
//  fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef fomular_hpp 
#define fomular_hpp

#include "../object.hpp"
#include "logic.hpp"

namespace atl {
    namespace logic {
        class Fomular : public Object {
        public:
            virtual string to_string() const = 0;
        private:
        };
    }
}

#endif /* fomular_hpp */
