//
//  disjunctive_fomular.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/5.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef disjunctive_fomular_hpp 
#define disjunctive_fomular_hpp

#include "propositional_fomular.hpp"

namespace atl {
    namespace logic {
        class DisjunctiveFomular : public PropositionalFomular {
        public:
            DisjunctiveFomular()
                : PropositionalFomular() {}

            DisjunctiveFomular(const std::initializer_list<PropositionalFomularPtr>& list)
                : fomulars_(list) {}

            template <class InputIterator>
            DisjunctiveFomular(InputIterator first, InputIterator last)
                : fomulars_(first, last) {}

            DisjunctiveFomular(const DisjunctiveFomular& con_fomular) 
                : PropositionalFomular(),
                  fomulars_(con_fomular.fomulars()) {}

            DisjunctiveFomular& operator=(const DisjunctiveFomular& con_fomular) {
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
                    res += " " + fomular -> to_string() + " |";
                }
                res[res.length() - 1] = ')';
                return res;
            }

        private:
            PropositionalFomularPtrs fomulars_;
        };
        typedef std::shared_ptr<DisjunctiveFomular> DisjunctiveFomularPtr;
    }
}

#endif /* disjunctive_fomular_hpp */
