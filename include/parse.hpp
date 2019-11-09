//
//  parse.hpp
//
//  Created by Jinlong He on 2019/11/06.
//  Copyright © 2019年 Jinlong He. All rights reserved.
//

#ifndef parse_hpp 
#define parse_hpp
#include <fstream>
#include "incra.hpp"

class Parse {
public:
    static void parse_file(const string& file_name, vector<string>& strs1,
                           vector<string>& strs2);
    static void parse_constrain(const vector<string>& strs, 
                                string& var_str, string& fomular_str, int k);
    static void parse_incra(const vector<string>& strs, INCRA& incra);
    static void parse_incras(const vector<string>& strs, INCRAs& incras);
    static void parse_incras_list(const vector<string>& strs, INCRAsList& incras_list);
};


#endif /* parse_hpp */
