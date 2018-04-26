#include "../inet_address.hpp"
#include "../utils.hpp"

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/tcp.h>

#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#include "../platform_error.hpp"

using namespace std;

namespace {
#ifdef HAVE_GAI_STRERROR_R
    static std::string addrinfo_errstr(int errcode) {
        char buf[0xff];
        memset(&buf[0], 0, sizeof(buf));
        gai_strerror_r(errcode, &buf[0], sizeof(buf));
        return string(&buf[0]);
    }
#else
    static std::string addrinfo_errstr(int errcode) {
        return string(gai_strerror(errcode));
    }
#endif
}

namespace httpproxy {

    struct inet_address::impl_data {
        impl_data() :_M_addrlen(sizeof(_M_addr)) { memset(&_M_addr, 0, sizeof(_M_addr)); }
        impl_data(sockaddr const* pAddr, size_t addr_len) :_M_addrlen(addr_len) { memcpy(&_M_addr, pAddr, addr_len); }

        void assign(sockaddr const* pAddr, size_t addr_len) {
            memcpy(&_M_addr, pAddr, addr_len);
            _M_addrlen = addr_len;
        }
        void assign(addrinfo const *pAddrInfo) {
            memcpy(&_M_addr, pAddrInfo->ai_addr, pAddrInfo->ai_addrlen);
            _M_addrlen = pAddrInfo->ai_addrlen;
        }

        sockaddr _M_addr;
        size_t _M_addrlen;
    };

    inet_address::inet_address() :_M_data(new impl_data()) { }
    inet_address::inet_address(void const* raw_addr, size_t addr_len)
        :_M_data(new impl_data(reinterpret_cast<sockaddr const*>(raw_addr), addr_len)) {
    }

    int inet_address::lookup(string const &node_name, string const &service_name,
            vector<inet_address> &addrs) {
        int error;
        addrinfo hint = {0}, *pAddrInfo = 0;
        hint.ai_family = PF_UNSPEC;
        hint.ai_flags = AI_PASSIVE;
        if((error = ::getaddrinfo(node_name.c_str(), service_name.c_str(), &hint, &pAddrInfo))) {
            cerr << platform_error(error, addrinfo_errstr(error)).what() << endl;
            return -1;
        }
        int cnt = 0;
        for(addrinfo* pAddr = pAddrInfo; pAddr; pAddr = pAddr->ai_next) {
            inet_address addr;
            addr._M_data->assign(pAddr);
            addrs.push_back(addr);
            ++cnt;
        }
        if(pAddrInfo)
            ::freeaddrinfo(pAddrInfo);
        return cnt;
    }

    void const* inet_address::raw_addr() const { return &(_M_data->_M_addr); }
    void * inet_address::raw_addr() { return &(_M_data->_M_addr); }

    size_t const& inet_address::raw_addr_len() const { return _M_data->_M_addrlen; }
    size_t& inet_address::raw_addr_len() { return _M_data->_M_addrlen; }

    ostream& operator << (ostream &os, inet_address const& addr) {
        char host_buf[NI_MAXHOST];
        char service_buf[NI_MAXHOST];
        int retcode = ::getnameinfo(&(addr._M_data->_M_addr), addr._M_data->_M_addrlen,
                &host_buf[0], NI_MAXHOST,
                &service_buf[0], NI_MAXSERV,
                NI_NUMERICHOST | NI_NUMERICSERV);
        if(retcode != 0) {
            cerr << platform_error(retcode, addrinfo_errstr(retcode)).what() << endl;
            return os;
        }
        return os << &host_buf[0] << ':' << &service_buf[0];
    }
}
