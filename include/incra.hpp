//
//  incra.hpp
//
//  Created by Jinlong He on 2019/11/06.
//  Copyright © 2019年 Jinlong He. All rights reserved.
//

#ifndef incra_hpp 
#define incra_hpp
#include <vector>
#include <boost/algorithm/string.hpp>
#include "ATL/finite_automaton/nondeterministic_finite_automaton.hpp"
using std::vector;

class RegisterNames {
public:
    typedef vector<string> strings;
    RegisterNames() {}

    RegisterNames(const string& names) {
        boost::split(names_, names, boost::is_any_of(";"));
    }

    const strings& names() const {
        return names_;
    }
private:
    strings names_;
};

typedef std::shared_ptr<RegisterNames> RegisterNamesPtr;

class Registers {
public:
    typedef vector<int> ints;
    Registers() {}

    Registers(const ints& nums)
        : nums_(nums) {}

    const ints& nums() const {
        return nums_;
    }
private:
    ints nums_;
};

typedef std::shared_ptr<Registers> RegistersPtr;


class Label {
public:
    Label()
        : min_(0),
          max_(0),
          registers_(nullptr) {}

    Label(int min, int max)
        : min_(min),
          max_(max),
          registers_(nullptr) {}

    Label(int min, int max, RegistersPtr registers)
        : min_(min),
          max_(max),
          registers_(registers) {}

    atl::ID hash_value() const {
        return ((boost::hash<int>()(min_)) ^
                (boost::hash<int>()(max_)) ^
                ((atl::ID)registers_.get()));
    }

    int min() const {
        return min_;
    }

    int max() const {
        return max_;
    }

    RegistersPtr registers() const {
        return registers_;
    }

    bool operator==(const Label& label) const {
        return min_ == label.min_ && 
               max_ == label.max_ &&
               registers_ == label.registers_;
    }
    
private:
    int min_;
    int max_;
    RegistersPtr registers_;
};

namespace boost {
    template <>
    struct hash<Label> {
        std::size_t operator()(const Label& l) const {
            return l.hash_value();
        }
    };
}

//typedef std::shared_ptr<Label> LabelPtr;

typedef atl::NondeterministicFiniteAutomaton<Label, -1, boost::no_property, RegisterNamesPtr> INCRA;
typedef vector<INCRA*> INCRAs;
typedef std::list<INCRAs> INCRAsList;

#endif /* incra_hpp */
