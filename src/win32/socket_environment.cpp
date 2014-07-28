#include "../socket_environment.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <stdexcept>

#include "../platform_error.hpp"

using namespace std;

namespace httpproxy {

    class socket_environment::impl_data {
        public:
            impl_data() {
                int const MAJOR_VERSION = 2;
                int const MINOR_VERSION = 2;
                int status = ::WSAStartup(MAKEWORD(MAJOR_VERSION, MINOR_VERSION), &_M_wsaData);
                if(status != 0) {
                    cerr << "failed to initialize socket environment." << endl;
                    throw platform_error(::GetLastError());
                }
                clog << "socket environment successfully initialize" << endl;
            }
            ~impl_data() {
                int status = ::WSACleanup();
                if(status != 0) {
                    cerr << platform_error(::GetLastError()).what();
                    //cerr << "failed to cleanup socket environment." << endl;
                } else
                    clog << "socket environment successfully cleaned up." << endl;
            }
        private:
            ::WSADATA _M_wsaData;
    };

    socket_environment::socket_environment() {
        _M_data = new impl_data();
    }
    socket_environment::~socket_environment() {
        if(_M_data) {
            delete _M_data;
            _M_data = NULL;
        }
    }

}
