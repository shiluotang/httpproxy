#include "utils.hpp"

#include <cstdlib>
#include <string>
#include <ostream>

#include <cxxabi.h>

using namespace std;

namespace httpproxy {

    string const demangle(string const& mangled_name) {
        string origin_name;
        int status = 0;
        char *s = abi::__cxa_demangle(mangled_name.c_str(), NULL, 0, &status);
        if(s)
            origin_name.assign(s);
        free(s);
        return origin_name;
    }

	stop_watch::stop_watch()
		:_M_start(time_point::min()),
		_M_duration(duration::zero()),
		_M_running(false) {}

	void stop_watch::start() {
		if (_M_running)
			return;
		_M_start = clock_type::now();
		_M_running = true;
	}

	void stop_watch::stop() {
		if (!_M_running)
			return;
		_M_duration += clock_type::now() - _M_start;
		_M_running = false;
	}

	void stop_watch::reset() {
		_M_start = time_point::min();
		_M_duration = duration::zero();
		_M_running = false;
	}

	double stop_watch::elapsedMillis() const {
		if (!_M_running)
			return chrono::duration_cast<double_milli>(_M_duration).count();
		return chrono::duration_cast<double_milli>((clock_type::now() - _M_start) + _M_duration).count();
	}

	ostream& operator << (ostream &os, stop_watch const &watch) {
		return os << watch.elapsedMillis() << " ms";
	}

}
