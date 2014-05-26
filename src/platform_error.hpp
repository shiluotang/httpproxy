#ifndef HTTPPROXY_PLATFORM_ERROR_HPP_INCLUDED
#define HTTPPROXY_PLATFORM_ERROR_HPP_INCLUDED

#include <stdexcept>
#include <iosfwd>

namespace httpproxy {

    class platform_error : std::runtime_error {
        public:
            platform_error(int, std::string const&);
            explicit platform_error(int);
            int const error_no() const { return m_err; }
        private:
            int m_err;
    };
}

#endif //HTTPPROXY_PLATFORM_ERROR_HPP_INCLUDED
