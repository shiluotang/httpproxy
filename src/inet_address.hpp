#ifndef HTTPPROXY_INET_ADDRESS_HPP_INCLUDED
#define HTTPPROXY_INET_ADDRESS_HPP_INCLUDED

#include <cstddef>
#include <iosfwd>
#include <vector>
#include <memory>

namespace httpproxy {

    class inet_address {
        private:
            inet_address();
            inet_address(void const* raw_addr, std::size_t addrlen);
        public:
            static int lookup(std::string const&, std::string const&, std::vector<inet_address>&);

        private:
            void const* raw_addr() const;
            void* raw_addr();
            std::size_t const& raw_addr_len() const;
            std::size_t& raw_addr_len();

            struct impl_data;
            std::shared_ptr<impl_data> m_data;

            friend class socket;
            friend std::ostream& operator << (std::ostream&, inet_address const&);
    };

    extern std::ostream& operator << (std::ostream&, inet_address const&);

}

#endif //HTTPPROXY_INET_ADDRESS_HPP_INCLUDED
