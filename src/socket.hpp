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
        virtual ~socket();
        int send(void const* buf, std::size_t num);
        int receive(void* buf, std::size_t buf_size);
        operator bool() const;

		bool connect(inet_address const&);
        socket accept();
        bool bind(inet_address const&);
        bool listen(int backlog);
	public:
		socket& write(char);
		socket& write(short);
		socket& write(int);
		socket& write(long);
		socket& write(long long);
		socket& write(float);
		socket& write(double);
		socket& write(long double);

		socket& write(signed char);

		socket& write(unsigned char);
		socket& write(unsigned short);
		socket& write(unsigned int);
		socket& write(unsigned long);
		socket& write(unsigned long long);

		socket& write(char const*);
		socket& write(signed char const*);
		socket& write(unsigned char const*);
		socket& write(void const*);
		socket& write(std::string const&);
		socket& write(bool);

    private:
        std::shared_ptr<socket_handle> _M_handle_ptr;
};

}

#endif //HTTPPROXY_SOCKET_HPP_INCLUDED
