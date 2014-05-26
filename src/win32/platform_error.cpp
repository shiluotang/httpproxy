#include "../platform_error.hpp"

#include <windows.h>

using namespace std;

namespace {
    string win32_error_msg(DWORD code) {
        string msg = "Unknown Error";
        LPSTR text = 0;
        DWORD ret = ::FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                0,
                code,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPSTR>(&text),
                0,
                0);
        if(ret < 0 || !text)
            return msg;
        msg.assign(text, ret);
        ::LocalFree(text);
        return msg;
    }
}

namespace httpproxy {

    platform_error::platform_error(int error_code, string const& msg)
        :runtime_error(msg.c_str()), m_err(error_code) {
    }

    platform_error::platform_error(int error_code)
        :runtime_error(win32_error_msg(error_code)), m_err(error_code) {
    }

}
