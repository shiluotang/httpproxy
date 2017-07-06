#include "../platform_error.hpp"

#include <string.h>

using namespace std;

namespace {
    string linux_error_msg(int code) {
        return string(strerror(code));
    }
}

namespace httpproxy {

    platform_error::platform_error(int error_code, string const& msg)
        :runtime_error(msg.c_str()), _M_err(error_code) {
    }

    platform_error::platform_error(int error_code)
        :runtime_error(linux_error_msg(error_code)), _M_err(error_code) {
    }

}
