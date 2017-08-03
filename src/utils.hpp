#ifndef HTTPPROXY_UTILS_HPP_INCLUDED
#define HTTPPROXY_UTILS_HPP_INCLUDED

#include <cstddef>
#include <sstream>
#include <iosfwd>
#include <chrono>

namespace httpproxy {

    template<typename T, std::size_t N>
    std::size_t countof(T const (&a)[N]) {
        return N;
    }

    template<typename U, typename V>
    U sstream_cast(V const &val) {
        std::stringstream ss;
        ss << val;
        U converted;
        ss >> converted;
        return converted;
    }

    extern std::string const demangle(std::string const& mangled_name);

	class stop_watch {
		protected:
			typedef std::chrono::high_resolution_clock clock_type;
			typedef clock_type::time_point time_point;
			typedef clock_type::duration duration;
			typedef std::chrono::duration<double, std::milli> double_milli;
		public:
			stop_watch();
			void start();
			void stop();
			void reset();
			double elapsedMillis() const;
		private:
			time_point _M_start;
			duration _M_duration;
			bool _M_running;
	};

	std::ostream& operator << (std::ostream&, stop_watch const&);
}
#define DEMANGLE(X) ::httpproxy::demangle(typeid(X).name())

#endif //HTTPPROXY_UTILS_HPP_INCLUDED
