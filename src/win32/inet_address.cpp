#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x501
#elif _WIN32_WINNT < 0x501
#   undef _WIN32_WINNT
#   define  _WIN32_WINNT 0x501
#endif

#include "../inet_address.hpp"
#include "../utils.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

namespace httpproxy {

    struct inet_address::impl_data {
        impl_data() :m_addrlen(sizeof(m_addr)) { memset(&m_addr, 0, sizeof(m_addr)); }
        impl_data(sockaddr const* pAddr, size_t addr_len) :m_addrlen(addr_len) { memcpy(&m_addr, pAddr, addr_len); }

        void assign(sockaddr const* pAddr, size_t addr_len) {
            memcpy(&m_addr, pAddr, addr_len);
            m_addrlen = addr_len;
        }
        void assign(addrinfo const *pAddrInfo) {
            memcpy(&m_addr, pAddrInfo->ai_addr, pAddrInfo->ai_addrlen);
            m_addrlen = pAddrInfo->ai_addrlen;
        }

        sockaddr m_addr;
        size_t m_addrlen;
    };

    inet_address::inet_address() :m_data(new impl_data()) { }
    inet_address::inet_address(void const* raw_addr, size_t addr_len)
        :m_data(new impl_data(reinterpret_cast<sockaddr const*>(raw_addr), addr_len)) {
    }

    int inet_address::lookup(string const &node_name, string const &service_name,
            vector<inet_address> &addrs) {
        addrinfo hint = {0}, *pAddrInfo = 0;
        hint.ai_family = PF_UNSPEC;
        hint.ai_flags = AI_PASSIVE;
        if(::getaddrinfo(node_name.c_str(), service_name.c_str(), &hint, &pAddrInfo) != 0)
            return -1;
        int cnt = 0;
        for(addrinfo* pAddr = pAddrInfo; pAddr; pAddr = pAddr->ai_next) {
            inet_address addr;
            addr.m_data->assign(pAddr);
            addrs.push_back(addr);
            ++cnt;
        }
        if(pAddrInfo)
            ::freeaddrinfo(pAddrInfo);
        return cnt;
    }

    void const* inet_address::raw_addr() const { return &(m_data->m_addr); }
    void * inet_address::raw_addr() { return &(m_data->m_addr); }

    size_t const& inet_address::raw_addr_len() const { return m_data->m_addrlen; }
    size_t& inet_address::raw_addr_len() { return m_data->m_addrlen; }

    ostream& operator << (ostream &os, inet_address const& addr) {
        char host_buf[NI_MAXHOST];
        char service_buf[NI_MAXHOST];
        int retcode = ::getnameinfo(&(addr.m_data->m_addr), addr.m_data->m_addrlen,
                &host_buf[0], NI_MAXHOST,
                &service_buf[0], NI_MAXSERV,
                NI_NUMERICHOST | NI_NUMERICSERV);
        if(retcode != 0)
            return os;
        return os << &host_buf[0] << ':' << &service_buf[0];
    }
}