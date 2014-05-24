#include "../socket_environment.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <stdexcept>

using namespace std;

namespace httpproxy {

    class socket_environment::impl_data {
        public:
            impl_data() {
                int const MAJOR_VERSION = 2;
                int const MINOR_VERSION = 2;
                int status = ::WSAStartup(MAKEWORD(MAJOR_VERSION, MINOR_VERSION), &m_wsaData);
                if(status != 0)
                    throw runtime_error("failed to initialize socket environment.");
                clog << "socket environment successfully initialize" << endl;
            }
            ~impl_data() {
                int status = ::WSACleanup();
                if(status != 0)
                    cerr << "failed to cleanup socket environment." << endl;
                else
                    clog << "socket environment successfully cleaned up." << endl;
            }
        private:
            WSADATA m_wsaData;
    };

    socket_environment::socket_environment() {
        m_data = new impl_data();
    }
    socket_environment::~socket_environment() {
        if(m_data) {
            delete m_data;
            m_data = NULL;
        }
    }

}
