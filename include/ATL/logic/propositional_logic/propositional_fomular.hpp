//
//  propositional_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef propositional_fomular_hpp 
#define propositional_fomular_hpp

#include "../fomular.hpp"

namespace atl {
    namespace logic {
        enum Predicate {EQU, NEQ, LSS, LEQ, GTR, GEQ};
        class PropositionalFomular : public Fomular {
        public:
            PropositionalFomular()
                : Fomular() {}

            PropositionalFomular(const PropositionalFomular& pro_fomular) 
                : Fomular(pro_fomular) {}

            PropositionalFomular& operator=(const PropositionalFomular& pro_fomular) {
                if (this != &pro_fomular) {
                    Fomular::operator=(pro_fomular);
                }
                return *this;
            }

            virtual string to_string() const = 0;

        private:
        };
        typedef std::shared_ptr<PropositionalFomular> PropositionalFomularPtr;
        typedef std::list<PropositionalFomularPtr> PropositionalFomularPtrs;
    }
}

#endif /* propositional_fomular_hpp */
