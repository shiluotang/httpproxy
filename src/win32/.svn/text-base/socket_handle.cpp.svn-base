#include "../socket_handle.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

using namespace std;

namespace httpproxy {

    socket_handle::socket_handle() :m_data(INVALID_SOCKET) {
        m_data = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    socket_handle::socket_handle(int handle) :m_data(handle) {}
    socket_handle::socket_handle(int address_family, int socket_type,
            int protocol_type) :m_data(INVALID_SOCKET) {
        m_data = ::socket(address_family, socket_type, protocol_type);
    }
    socket_handle::~socket_handle() { close(); }


    void socket_handle::close() {
        if(m_data != INVALID_SOCKET) {
            int retcode;
            retcode = ::shutdown(static_cast<SOCKET>(m_data), SD_BOTH);
            clog << "shutdown retcode is " << retcode << endl;
            retcode = ::closesocket(static_cast<SOCKET>(m_data));
            clog << "closesocket retcode is " << retcode << endl;
            if(retcode == 0)
                m_data = INVALID_SOCKET;
        }
    }

    socket_handle::operator bool() const { return m_data != INVALID_SOCKET; }

}
