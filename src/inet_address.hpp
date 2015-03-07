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
			/**
			 * Lookup network address.
			 *
			 * @param node_name standards for the host name, such as
			 * www.google.com
			 * @param service_name standards for the port. such as "mysql" which
			 * means 3306 as it is the default port for MySQL service.
			 * @param addrs results will be added to this container.
			 *
			 * @return As the human readable address may be mapped to more than
			 * one addresses, the result value is the count of the found ones.
			 */
            static int lookup(std::string const &node_name,
					std::string const &service_name,
					std::vector<inet_address> &addrs);

        private:
            void const* raw_addr() const;
            void* raw_addr();
            std::size_t const& raw_addr_len() const;
            std::size_t& raw_addr_len();

            struct impl_data;
            std::shared_ptr<impl_data> _M_data;

            friend class socket;
            friend std::ostream& operator << (std::ostream&, inet_address const&);
    };

    extern std::ostream& operator << (std::ostream&, inet_address const&);

}

#endif //HTTPPROXY_INET_ADDRESS_HPP_INCLUDED
