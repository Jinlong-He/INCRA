//
//  conjunctive_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef conjunctive_fomular_hpp 
#define conjunctive_fomular_hpp

#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        class ConjunctiveFomular : public PropositionalFomular {
        public:
            ConjunctiveFomular()
                : PropositionalFomular() {}

            ConjunctiveFomular(const std::initializer_list<PropositionalFomularPtr>& list)
                : fomulars_(list) {}

            template <class InputIterator>
            ConjunctiveFomular(InputIterator first, InputIterator last)
                : fomulars_(first, last) {}

            ConjunctiveFomular(const ConjunctiveFomular& con_fomular) 
                : PropositionalFomular(),
                  fomulars_(con_fomular.fomulars()) {}

            ConjunctiveFomular& operator=(const ConjunctiveFomular& con_fomular) {
                if (this != &con_fomular) {
                    PropositionalFomular::operator=(con_fomular);
                    fomulars_.assign(con_fomular.fomulars().begin(), 
                                     con_fomular.fomulars().end());
                }
                return *this;
            }

            const PropositionalFomularPtrs fomulars() const {
                return fomulars_;
            }

            string to_string() const {
                string res = "(";
                for (auto fomular : fomulars_) {
                    res += " " + fomular -> to_string() + " &";
                }
                res[res.length() - 1] = ')';
                return res;
            }

        private:
            PropositionalFomularPtrs fomulars_;
        };
        typedef std::shared_ptr<ConjunctiveFomular> ConjunctiveFomularPtr;
    }
}

#endif /* conjunctive_fomular_hpp */
