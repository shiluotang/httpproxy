#ifndef HTTPPROXY_SOCKET_HANDLE_HPP_INCLUDED
#define HTTPPROXY_SOCKET_HANDLE_HPP_INCLUDED

namespace httpproxy {

    class socket_handle {
        public:
            socket_handle();
            explicit socket_handle(int handle);
            socket_handle(int address_family, int socket_type, int protocol_type);
            ~socket_handle();

            void close();

            operator bool() const;
        private:
            int m_data;

            friend class socket;
    };

}

#endif //HTTPPROXY_SOCKET_HANDLE_HPP_INCLUDED
