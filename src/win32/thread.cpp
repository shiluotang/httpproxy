#include "../thread.hpp"

#include <windows.h>

using namespace std;

namespace httpproxy {

	thread::id::id(native_handle_type handle) {}

	struct thread::id::impl { };

	void swap(thread &a, thread &b) noexcept { }

	thread::thread() noexcept {}
	thread::~thread() { }

	thread::id thread::get_id() const noexcept { return id(-1L); }
	thread::native_handle_type thread::native_handle() { return 0L; }
	void thread::detach() {}
	void thread::join() {}
	bool thread::joinable() const noexcept { return true; }
	unsigned thread::hardware_concurrency() noexcept { return 0L; }
}
