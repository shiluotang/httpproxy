#include "../socket_handle.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

using namespace std;

namespace httpproxy {

    socket_handle::socket_handle() :_M_data(INVALID_SOCKET) {
        _M_data = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    socket_handle::socket_handle(int handle) :_M_data(handle) {}
    socket_handle::socket_handle(int address_family, int socket_type,
            int protocol_type) :_M_data(INVALID_SOCKET) {
        _M_data = ::socket(address_family, socket_type, protocol_type);
    }
    socket_handle::~socket_handle() { close(); }


    void socket_handle::close() {
        if(_M_data != INVALID_SOCKET) {
            int retcode;
            retcode = ::shutdown(static_cast<SOCKET>(_M_data), SD_BOTH);
            clog << "shutdown retcode is " << retcode << endl;
            retcode = ::closesocket(static_cast<SOCKET>(_M_data));
            clog << "closesocket retcode is " << retcode << endl;
            if(retcode == 0)
                _M_data = INVALID_SOCKET;
        }
    }

    socket_handle::operator bool() const { return _M_data != INVALID_SOCKET; }

}
