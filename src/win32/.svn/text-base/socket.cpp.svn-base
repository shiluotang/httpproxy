#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x501
#elif _WIN32_WINNT < 0x501
#   undef _WIN32_WINNT
#   define  _WIN32_WINNT 0x501
#endif

#include "../inet_address.hpp"
#include "../socket_handle.hpp"
#include "../socket.hpp"
#include "../utils.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdexcept>
#include <iostream>

using namespace std;

namespace httpproxy {

    socket::socket() :m_handle_ptr(new socket_handle()) {}
    socket::socket(int handle) :m_handle_ptr(new socket_handle(handle)) {}
    socket::socket(int address_family, int socket_type, int protocol_type)
        :m_handle_ptr(new socket_handle(address_family, socket_type, protocol_type))
    {}
    socket::~socket() {}

    int socket::send(void const* buf, size_t num) {
        return ::send(static_cast<SOCKET>(m_handle_ptr->m_data),
                reinterpret_cast<char const*>(buf), num,
                0);
    }
    int socket::receive(void *buf, size_t buf_size) {
        return ::recv(static_cast<SOCKET>(m_handle_ptr->m_data),
                reinterpret_cast<char*>(buf), buf_size,
                0);
    }

    socket::operator bool() const { return m_handle_ptr->operator bool(); }

    socket socket::accept() {
        sockaddr addr = {0};
        int addrlen = sizeof(addr);
        SOCKET s = ::accept(static_cast<SOCKET>(m_handle_ptr->m_data), 
                &addr, &addrlen);
        clog << "received connection from " << inet_address(&addr, addrlen) << endl;
        return socket(s);
    }

    bool socket::bind(inet_address const& addr) {
        return ::bind(static_cast<SOCKET>(m_handle_ptr->m_data),
                reinterpret_cast<sockaddr const*>(addr.raw_addr()),
                addr.raw_addr_len()) == 0;
    }
    bool socket::listen(int backlog) {
        return ::listen(static_cast<SOCKET>(m_handle_ptr->m_data), backlog) == 0;
    }
}
