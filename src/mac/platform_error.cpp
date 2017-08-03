#include "../platform_error.hpp"

#include <string>

using namespace std;

namespace {
#ifdef HAVE_STRERROR_R
    std::string posix_error_msg(int err) {
        char buf[0xff];
        memset(&buf[0], 0, sizeof(buf));
        strerror_r(err, &buf[0], sizeof(buf));
        return std::string(&buf[0]);
    }
#else
    std::string posix_error_msg(int err) {
        return std::string(strerror(err));
    }
#endif
}

namespace httpproxy {

    platform_error::platform_error(int error_code, string const& msg)
        :runtime_error(msg.c_str()), _M_err(error_code) {
    }

    platform_error::platform_error(int error_code)
        :runtime_error(posix_error_msg(error_code)), _M_err(error_code) {
    }

}
