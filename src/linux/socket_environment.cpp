#include "../socket_environment.hpp"

#include <iostream>
#include <stdexcept>

#include "../platform_error.hpp"

using namespace std;

namespace httpproxy {

    class socket_environment::impl_data {};

    socket_environment::socket_environment() {
        _M_data = new impl_data();
    }
    socket_environment::~socket_environment() {
        if(_M_data) {
            delete _M_data;
            _M_data = NULL;
        }
    }

}
