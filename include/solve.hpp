//
//  solve.hpp
//
//  Created by Jinlong He on 2019/11/06.
//  Copyright © 2019年 Jinlong He. All rights reserved.
//

#ifndef solve_hpp 
#define solve_hpp
#include "parse.hpp"
#include "translate.hpp"

class Solve {
public:
    static string smv(const string& file_name, int k);
    static void solve(const string& file_name, int k);
};


#endif /* solve_hpp */
