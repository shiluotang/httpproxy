#include "../socket_handle.hpp"

#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <net/if.h>
#include <unistd.h>
#include <strings.h>

#include <iostream>

using namespace std;

namespace {
    const int INVALID_SOCKET = 0;
    typedef int SOCKET;
}

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
            retcode = ::shutdown(static_cast<SOCKET>(_M_data), SHUT_RDWR);
            clog << "shutdown retcode is " << retcode << endl;
            retcode = ::close(static_cast<SOCKET>(_M_data));
            clog << "close retcode is " << retcode << endl;
            if(retcode == 0)
                _M_data = INVALID_SOCKET;
        }
    }

    socket_handle::operator bool() const { return _M_data != INVALID_SOCKET; }

}
