//
//  atomic_proposition.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/11/1.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef atomic_proposition_hpp 
#define atomic_proposition_hpp

#include "propositional_fomular.hpp"
#include "../item.hpp"

namespace atl {
    namespace logic {

        class AtomicProposition : public PropositionalFomular {
        public:

            AtomicProposition()
                : PropositionalFomular(),
                  item_lhs_(nullptr),
                  item_rhs_(nullptr),
                  predicate_(EQU) {}

            AtomicProposition(ItemPtr lhs, ItemPtr rhs, Predicate predicate = EQU) 
                : item_lhs_(lhs),
                  item_rhs_(rhs),
                  predicate_(predicate) {}

            AtomicProposition(const AtomicProposition& ap)
                : PropositionalFomular(),
                  item_lhs_(ap.item_lhs_),
                  item_rhs_(ap.item_rhs_),
                  predicate_(ap.predicate_) {}

            AtomicProposition& operator=(const AtomicProposition& ap) {
                if (this != &ap) {
                    PropositionalFomular::operator=(ap);
                    item_lhs_ = ap.item_lhs_;
                    item_rhs_ = ap.item_rhs_;
                    predicate_ = ap.predicate_;
                }
                return *this;
            }

            ItemPtr item_lhs() const {
                return item_lhs_;
            }

            ItemPtr item_rhs() const {
                return item_rhs_;
            }

            Predicate predicate() const {
                return predicate_;
            }

            virtual string to_string() const {
                string res = item_lhs_ -> to_string();
                string opt = "";
                switch(predicate_) {
                    case EQU : 
                        opt = " = ";
                        break;
                    case NEQ : 
                        opt = " != ";
                        break;
                    case LSS : 
                        opt = " < ";
                        break;
                    case LEQ : 
                        opt = " <= ";
                        break;
                    case GTR : 
                        opt = " > ";
                        break;
                    case GEQ : 
                        opt = " >= ";
                        break;
                }
                res += opt + item_rhs_ -> to_string();
                return res;
            }
        private:
            ItemPtr item_lhs_;
            ItemPtr item_rhs_;
            Predicate predicate_;
        };
        typedef std::shared_ptr<AtomicProposition> AtomicPropositionPtr;
        typedef std::list<AtomicPropositionPtr> AtomicPropositionPtrs;

        class TrueProposition : public AtomicProposition {
        public:
            string to_string() const {
                return "TRUE";
            }
        };
        typedef std::shared_ptr<TrueProposition> TruePropositionPtr;

        class FalseProposition : public AtomicProposition {
        public:
            string to_string() const {
                return "FALSE";
            }
        };
        typedef std::shared_ptr<FalseProposition> FalsePropositionPtr;
    }
}

#endif /* atomic_proposition_hpp */
