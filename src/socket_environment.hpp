#ifndef HTTPPROXY_SOCKET_ENVIRONMENT_HPP_INCLUDED
#define HTTPPROXY_SOCKET_ENVIRONMENT_HPP_INCLUDED

namespace httpproxy {
    class socket_environment {
        public:
            socket_environment();
            ~socket_environment();

        private:
            class impl_data;
            impl_data *m_data;
    };
}

#endif //HTTPPROXY_SOCKET_ENVIRONMENT_HPP_INCLUDED
