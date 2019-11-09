#include <stdlib.h>
#include <stdio.h>
#include "solve.hpp"
string Solve::smv(const string& file_name, int k) {
    vector<string> strs, constrain_strs;
    Parse::parse_file(file_name, constrain_strs, strs);
    string var_str, fomular_str, res = "MODULE main\nIVAR\nc : 0..127;\n";
    Parse::parse_constrain(constrain_strs, var_str, fomular_str, k);
    INCRAsList incras_list;
    FAs fas;
    Parse::parse_incras_list(strs, incras_list);
    string final_str = 
        Translate::translate_to_fa(incras_list, "s", fas, 
                                   make_true_proposition(), k) -> to_string();
    for (auto fa : fas) {
        res += atl::translate_to_nuxmv(*fa);
        delete fa;
    }
    for (auto& incras : incras_list) {
        for (auto incra : incras)
            delete incra;
    }
    //string spec_str = "INVARSPEC !(" + fomular_str + " & " + final_str + ")";
    string spec_str = "INVARSPEC !(" + final_str + " & " + fomular_str ;
    //spec_str[spec_str.length() - 1] = ')';
    res += "VAR\n" + var_str + spec_str + ")";
    return res;
}

void Solve::solve(const string& file_name, int k) {
    string smv_str = smv(file_name, k);
    std::fstream fs;
    fs.open ("out.smv", std::fstream::out);
    if (fs.is_open()) {
        fs << smv_str;
    }
    fs.close();
    system("nuXmv out.smv");
}
