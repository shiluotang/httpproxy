#ifndef HTTPPROXY_SOCKET_HPP_INCLUDED
#define HTTPPROXY_SOCKET_HPP_INCLUDED

#include <cstddef>
#include <iosfwd>
#include <memory>

namespace httpproxy {

class socket_handle;
class inet_address;
class socket {
    private:
        explicit socket(int handle);
    public:
        socket();
        socket(int address_family, int socket_type, int protocol_type);
        ~socket();
        int send(void const* buf, std::size_t num);
        int receive(void* buf, std::size_t buf_size);
        operator bool() const;

        socket accept();
        bool bind(inet_address const&);
        bool listen(int backlog);
    private:
        std::shared_ptr<socket_handle> _M_handle_ptr;
};

}

#endif //HTTPPROXY_SOCKET_HPP_INCLUDED
