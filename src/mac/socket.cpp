#include "../inet_address.hpp"
#include "../socket_handle.hpp"
#include "../socket.hpp"
#include "../utils.hpp"
#include "../platform_error.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdexcept>
#include <iostream>

using namespace std;

namespace {
    using namespace httpproxy;

    int const SOCKET_ERROR = -1;

    typedef int SOCKET;
}

namespace httpproxy {

    socket::socket() :_M_handle_ptr(new socket_handle()) {}
    socket::socket(int handle) :_M_handle_ptr(new socket_handle(handle)) {}
    socket::socket(protocol_family pf, socket_type st, transport_protocol tp)
        :_M_handle_ptr(new socket_handle(pf, st, tp))
    {}
    socket::~socket() {}

    int socket::send(void const* buf, size_t num) {
        return ::send(static_cast<SOCKET>(_M_handle_ptr->_M_data),
                reinterpret_cast<char const*>(buf), num,
                0);
    }
    int socket::receive(void *buf, size_t buf_size) {
        return ::recv(static_cast<SOCKET>(_M_handle_ptr->_M_data),
                reinterpret_cast<char*>(buf), buf_size,
                0);
    }

    socket::operator bool() const { return _M_handle_ptr->operator bool(); }

    bool socket::connect(inet_address const &addr) {
        clog << "connecting to " << addr << " ..."<< endl;
        if (::connect(_M_handle_ptr->_M_data,
                reinterpret_cast<sockaddr const*>(addr.raw_addr()),
                addr.raw_addr_len()) == SOCKET_ERROR) {
            cerr << platform_error(errno).what() << endl;
            return false;
        }
        clog << "connected to " << addr << endl;
        return true;
    }

    socket socket::accept() {
        sockaddr addr = {0};
        socklen_t addrlen = sizeof(addr);
        SOCKET s = ::accept(static_cast<SOCKET>(_M_handle_ptr->_M_data),
                &addr, &addrlen);
        clog << "received connection from " << inet_address(&addr, addrlen) << endl;
        return socket(s);
    }

    bool socket::bind(inet_address const& addr) {
        return ::bind(static_cast<SOCKET>(_M_handle_ptr->_M_data),
                reinterpret_cast<sockaddr const*>(addr.raw_addr()),
                addr.raw_addr_len()) == 0;
    }
    bool socket::listen(int backlog) {
        return ::listen(static_cast<SOCKET>(_M_handle_ptr->_M_data), backlog) == 0;
    }
}
