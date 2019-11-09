#include "solve.hpp"
using boost::no_property;
namespace boost {
no_property operator& (const no_property& lhs, const no_property& rhs) {
        return no_property();
    }

    no_property operator| (const no_property& lhs, const no_property& rhs) {
        return no_property();
    }

    bool operator!= (const no_property& lhs, const no_property& rhs) {
        return 0;
    }

    bool operator== (const no_property& lhs, const no_property& rhs) {
        return 1;
    }

    std::ostream &operator<< (std::ostream& os, const no_property& prop) {
        os << "";
        return os;
    }
}
std::ostream& operator<<(std::ostream& os, const Label& label) {
    os << label.min() << " , " << label.max() << " list(";
    for (auto r : label.registers() -> nums()) {
        os << r << ",";
    }
    os << ")";
    return os;
}

int main(int argc, char* argv[]) {
    if (argc == 2)
        Solve::solve(argv[1], 20);
    if (argc == 3)
        Solve::solve(argv[1], atoi(argv[2]));
    return 0;
}
