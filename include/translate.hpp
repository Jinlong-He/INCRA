//
//  translate.hpp
//
//  Created by Jinlong He on 2019/11/06.
//  Copyright © 2019年 Jinlong He. All rights reserved.
//

#ifndef translate_hpp 
#define translate_hpp
#include "incra.hpp"
#include "ATL/fomula_automaton/fomula_automaton.hpp"
#include "ATL/fomula_automaton/translation.hpp"
#include "ATL/logic/logic_basic.hpp"
#include "ATL/logic/propositional_logic/propositional_logic.hpp"

typedef atl::FomularAutomaton<> FA;
typedef vector<FA*> FAs;

using namespace atl::logic;

class Translate {
public:
    static PropositionalFomularPtr 
        translate_to_fa(const INCRA& incra, const string& name, FA& fa,
                        PropositionalFomularPtr init_fomular = make_true_proposition(),
                        int k = 500);

    static PropositionalFomularPtr 
        translate_to_fa(const INCRAs& incras, const string& name, FAs& fas,
                        PropositionalFomularPtr init_fomular = make_true_proposition(),
                        int k = 500);

    static PropositionalFomularPtr 
        translate_to_fa(const INCRAsList& incras_list, const string& name, FAs& fas,
                        PropositionalFomularPtr init_fomular = make_true_proposition(),
                        int k = 500);
private:
};


#endif /* translate_hpp */
