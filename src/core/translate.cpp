#include "translate.hpp"
PropositionalFomularPtr 
Translate::translate_to_fa(const INCRA& incra, const string& name, FA& fa,
                           PropositionalFomularPtr init_fomular, int k) {
    typename INCRA::StateIter first, last;
    typedef typename INCRA::State State;
    /// make state value
    EnumValuePtrs values;
    EnumValuePtr init_value = nullptr;
    for (tie(first, last) = atl::states(incra);
         first != last; first++) {
        auto value = make_enum_value("v" + std::to_string(*first));
        add_state(fa, value);
        values.push_back(value);
        if (*first == incra.initial_state()) init_value = value;
    }
    auto value_true = make_true_proposition(); 
    auto value_trap = make_enum_value("t");
    values.push_back(value_trap);
    State trap_state = add_state(fa, value_trap);

    auto value_i = make_enum_value("i");
    values.push_back(value_i);

    /// make state var
    auto var = make_enum_variable(name, values);
    auto ap = make_atomic_proposition(var, value_i);
    auto neg_init_fomular = make_negtive_fomular(init_fomular);
    State state = add_control_state(fa, var, ap);
    add_transition(fa, state, state, 
                   make_conjunctive_fomular({neg_init_fomular, ap}));
    add_transition(fa, state, incra.initial_state(), 
                   make_conjunctive_fomular({init_fomular, ap}));

    /// make register var
    auto reg_init_value = make_int_value(0);
    auto reg_max_value = make_int_value(k);
    if (atl::get_property(incra) != nullptr) {
        for (auto& reg_name : atl::get_property(incra) -> names()) {
            auto reg_var = make_int_variable(reg_name, reg_init_value, reg_max_value);
            auto reg_var_1 = make_int_variable(reg_name + " + 1");
            auto reg_var_local = make_bool_variable(reg_name + "_l");
            auto reg_ap = make_atomic_proposition(reg_var, reg_init_value);
            add_control_state(fa, reg_var, reg_ap);
            add_state(fa, reg_var_1);
            add_volatile_state(fa, reg_var_local);
        }
    }
    
    /// make symbol var
    //auto min_value = make_int_value(min);
    //auto max_value = make_int_value(max);
    auto char_var = make_int_variable("c");
    //add_volatile_state(fa, char_var);
    
    /// make trans
    typename INCRA::OutTransitionIter t_first, t_last;
    for (tie(first, last) = atl::states(incra);
         first != last; first++) {
        for (tie(t_first, t_last) = atl::out_transitions(incra, *first);
             t_first != t_last; t_first++) {
            const auto& label = atl::get_property(incra, *t_first);
            auto min_value_label = make_int_value(label.min());
            auto max_value_label = make_int_value(label.max());
            auto state_value = atl::get_property(fa, *first);

            auto min_ap = make_atomic_proposition(char_var, min_value_label, GEQ);
            auto max_ap = make_atomic_proposition(char_var, max_value_label, LEQ);
            auto state_ap = make_atomic_proposition(var, state_value);
            auto con = make_conjunctive_fomular({min_ap, max_ap, state_ap});

            if (atl::get_property(incra) == nullptr) 
                add_transition(fa, state, atl::target(incra, *t_first), con);

            /// local register
            if (atl::get_property(incra) != nullptr) {
                auto bool_true_value = make_bool_value(1);
                auto bool_false_value = make_bool_value(0);
                const auto& nums = label.registers() -> nums();
                PropositionalFomularPtrs local_aps;
                for (size_t i = 0; i < nums.size(); i++) {
                    State local_state = state + 3 * i + 3;
                    auto local_var = atl::get_property(fa, local_state);
                    if (nums[i] == 1) {
                        local_aps.push_back(make_atomic_proposition(
                                            local_var, bool_true_value));
                    } else {
                        local_aps.push_back(make_atomic_proposition(
                                            local_var, bool_false_value));
                    }
                }
                auto local_fomular = make_conjunctive_fomular(local_aps.begin(), 
                                                              local_aps.end());
                add_transition(fa, state, atl::target(incra, *t_first), 
                               make_conjunctive_fomular({con, local_fomular}));

                for (size_t i = 0; i < nums.size(); i++) {
                    State reg_state = state + 3 * i + 1;
                    auto reg_state_var = atl::get_property(fa, reg_state);
                    auto max_ap_reg = make_atomic_proposition(reg_state_var, reg_max_value, LSS);
                    auto max_ap_reg_1 = make_atomic_proposition(reg_state_var, reg_max_value, LEQ);
                    auto con_reg = make_conjunctive_fomular({min_ap, max_ap, state_ap,
                                                             max_ap_reg, local_fomular});
                    auto con_reg_1 = make_conjunctive_fomular({min_ap, max_ap, state_ap,
                                                               max_ap_reg_1, local_fomular});
                    if (nums[i] == 0) {
                        add_transition(fa, reg_state, reg_state, con_reg_1);
                    } else {
                        add_transition(fa, reg_state, reg_state + 1, con_reg);
                    }
                }
            }
        }   
    }
    add_transition(fa, state, trap_state, value_true);
    if (atl::get_property(incra) != nullptr) {
        for (size_t i = 0; i < atl::get_property(incra) -> names().size(); i++) {
            State reg_state = state + 3 * i + 1;
            add_transition(fa, reg_state, reg_state, value_true);
        }
    }
    PropositionalFomularPtrs list;
    for (auto s : incra.final_states()) {
        list.push_back(make_atomic_proposition(var, atl::get_property(fa, s)));
    }
    return make_disjunctive_fomular(list.begin(), list.end());
}

PropositionalFomularPtr 
Translate::translate_to_fa(const INCRAs& incras, const string& name, FAs& fas,
                    PropositionalFomularPtr init_fomular, int k) {
    int i = 0;
    PropositionalFomularPtrs list;
    for (auto incra : incras) {
        FA* fa = new FA();
        list.push_back(translate_to_fa(*incra, name + "_" + std::to_string(i++), 
                                       *fa, init_fomular, k));
        fas.push_back(fa);
    }
    return make_conjunctive_fomular(list.begin(), list.end());
}

PropositionalFomularPtr 
Translate::translate_to_fa(const INCRAsList& incras_list, const string& name, FAs& fas,
                    PropositionalFomularPtr init_fomular, int k) {
    int i = 0;
    for (auto& incras : incras_list) {
        init_fomular = translate_to_fa(incras, name + "_" + std::to_string(i++), 
                                       fas, init_fomular, k);
    }
    return init_fomular;
}

