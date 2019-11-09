//
//  item.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef item_hpp 
#define item_hpp

#include "../object.hpp"
#include "logic.hpp"

namespace atl {
    namespace logic {

        class Item : public Object {
        public:
            virtual const string& to_string() const = 0;
            virtual string type() const = 0;
        private:
        };

        typedef std::shared_ptr<Item> ItemPtr;
        typedef std::list<ItemPtr> ItemPtrs;
    }
}

#endif /* item_hpp */
