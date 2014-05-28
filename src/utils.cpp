#include "utils.hpp"

#include <cstdlib>
#include <string>

#include <cxxabi.h>

using namespace std;

namespace httpproxy {

    string const demangle(string const& mangled_name) {
        string origin_name;
        int status = 0;
        char *s = abi::__cxa_demangle(mangled_name.c_str(), NULL, 0, &status);
        if(s)
            origin_name.assign(s);
        free(s);
        return origin_name;
    }

}
