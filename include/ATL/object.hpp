//
//  Object.hpp
//  ATL 
//
//  Created by Jinlong He on 2019/9/12.
//  Copyright © 2019年 Ruting-Team. All rights reserved.
//

#ifndef Object_hpp 
#define Object_hpp
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/graph_utility.hpp>
#include "../Util/Util.hpp"
using std::string;
using std::cout;
using std::ostream;
using std::endl;
using std::pair;
using boost::adjacency_list;
using boost::listS;
using boost::vecS;
using boost::bidirectionalS;
using boost::graph_traits;
using boost::no_property;
using boost::unordered_map;
using boost::unordered_set;
using boost::scoped_ptr;
using boost::graph_bundle_t;
using boost::tie;

namespace boost {
    template <class K, class C, class A>
    std::size_t hash_value(const unordered_set<K, C, A>& v) {
        return hash_range(v.begin(), v.end());
    }
}

namespace atl {

    typedef std::size_t Flag;
    typedef std::size_t ID;

        class Object {
    };

}

#endif /* Object_hpp */
