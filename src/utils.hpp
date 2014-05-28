#ifndef HTTPPROXY_UTILS_HPP_INCLUDED
#define HTTPPROXY_UTILS_HPP_INCLUDED

#include <cstddef>
#include <sstream>
#include <iosfwd>

namespace httpproxy {

    template<typename T, std::size_t N> std::size_t countof(T const (&a)[N]) { return N; }

    template<typename U, typename V> U sstream_cast(V val) {
        std::stringstream ss;
        ss << val;
        U converted;
        ss >> converted;
        return converted;
    }

    extern std::string const demangle(std::string const& mangled_name);

}
#define DEMANGLE(X) ::httpproxy::demangle(typeid(X).name())

#endif //HTTPPROXY_UTILS_HPP_INCLUDED
