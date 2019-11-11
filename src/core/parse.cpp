#include "parse.hpp"
using namespace atl;
void Parse::parse_file(const string& file_name, vector<string>& strs1,
                           vector<string>& strs2) {
    std::fstream fs;
    fs.open (file_name, std::fstream::in);
    if (fs.is_open()) {
        string str;
        int i = 0;
        while(getline(fs, str)) {
            if (i < 3) {
                strs1.push_back(str);
            } else {
                strs2.push_back(str);
            }
            i++;
        }
        fs.close();
    }
}

void Parse::parse_constrain(const vector<string>& strs, 
                            string& var_str, string& fomular_str, int k) {
    size_t pos = strs[0].find_first_of("(") + 1,
           length = strs[0].find_first_of(")") - pos;
    vector<string> var_strs;
    boost::split(var_strs, strs[0].substr(pos, length), boost::is_any_of(","));
    cout << strs[0].substr(pos, length) << endl;
    if (length > 0) {
        for (auto& s : var_strs) {
            //cout << s << endl;
            var_str += s + ": 0.." + std::to_string(k) + ";\n";
        }
    }
    fomular_str = strs[2];
}

void Parse::parse_incra(const vector<string>& strs, 
                        INCRA& incra) { 
    vector<string> states_strs, init_strs, final_strs, final_num_strs, trans_strs, reg_strs, reg_name_strs;
    unordered_set<int> final_nums;
    boost::split(states_strs, strs[0], boost::is_any_of(":"));
    boost::split(init_strs, strs[1], boost::is_any_of(":"));
    boost::split(final_strs, strs[2], boost::is_any_of(":"));
    boost::split(reg_name_strs, strs[strs.size() - 1], boost::is_any_of(":"));
    size_t length = final_strs[1].find_last_of(",");
    boost::split(final_num_strs, final_strs[1].substr(0,length), boost::is_any_of(","));
    int states_num = atoi(states_strs[1].c_str());
    int init_num = atoi(init_strs[1].c_str());
    cout << "final" << final_strs[1].substr(0,length) << endl;
    for (auto& str : final_num_strs) {
        cout <<  atoi(str.c_str())<< endl;
        final_nums.insert(atoi(str.c_str()));
    }
    for (int i = 0; i < states_num; i++) {
        add_state(incra);
        if (i == init_num) {
            incra.set_initial_state(i);
        } 
        if (final_nums.count(i) > 0) {
            incra.set_final_state(i);
        }
    }
    size_t reg_length = reg_name_strs[1].find_last_of(";") - 1;
    RegisterNamesPtr register_names = std::make_shared<RegisterNames>(reg_name_strs[1].substr(1,reg_length));
    if (reg_name_strs[1].length() > 2) {
    cout << "name: " << reg_name_strs[1].substr(1, reg_length) <<endl;
        atl::set_property(incra, register_names);
    }
    for (ID i = 4; i < strs.size() - 1; i++) {
        trans_strs.clear();
        reg_strs.clear();
        boost::split(trans_strs, strs[i], boost::is_any_of(";"));
        boost::split(reg_strs, trans_strs[4].substr(5, trans_strs[4].length() - 6), boost::is_any_of(","));
        int source = atoi(trans_strs[0].c_str());
        int target = atoi(trans_strs[1].c_str());
        int min = atoi(trans_strs[2].c_str());
        int max = atoi(trans_strs[3].c_str());
        vector<int> nums;
        for (auto& reg : reg_strs) {
            nums.push_back(atoi(reg.c_str()));
        }
        RegistersPtr registers = std::make_shared<Registers>(nums);
        if (reg_name_strs[1].size() > 2) {
            atl::add_transition(incra, source, target, Label(min, max, registers));
        } else {
            atl::add_transition(incra, source, target, Label(min, max));
        }
    }
}

void Parse::parse_incras(const vector<string>& strs, INCRAs& incras) {
    vector<string> incra_strs;
    for (auto& str : strs) {
        if (str.find("#automata:") != string::npos) {
            incra_strs.clear();
            continue;
        }
        if (str.find("#end") != string::npos) {
            INCRA* incra = new INCRA();
            parse_incra(incra_strs, *incra);
            incras.push_back(incra);
            continue;
        }
        incra_strs.push_back(str);
    }
}

void Parse::parse_incras_list(const vector<string>& strs, INCRAsList& incras_list) {
    vector<string> incras_strs;
    bool flag = true;
    for (auto& str : strs) {
        if (str.find("$") != string::npos && flag) {
            incras_strs.clear();
            flag = false;
            continue;
        }
        if (str.find("$") != string::npos && !flag) {
            INCRAs incras;
            parse_incras(incras_strs, incras);
            incras_list.push_back(incras);
            flag = true;
            continue;
        }
        incras_strs.push_back(str);
    }
}


