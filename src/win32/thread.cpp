#include "../thread.hpp"

#include <windows.h>
#include <ostream>

#include "../platform_error.hpp"

using namespace std;

namespace {
    /**
     * copied from GCC thread.cc in libstdc++-v3
     */
    extern "C" DWORD WINAPI thread_proc(LPVOID arg) {
        using namespace httpproxy;
        thread::callable_impl_base *callable = static_cast<thread::callable_impl_base*>(arg);
        thread::shared_callable_base_type local;
        local.swap(callable->m_self);
        try {
            callable->run();
        } catch(...) {
            std::terminate();
        }
        return 0;
    }
}

namespace httpproxy {

    thread::id::id() noexcept :m_handle() {}
    thread::id::id(native_handle_type nativeHandle) :m_handle(nativeHandle) { }
    ostream& operator << (ostream &os, thread::id id) { return os << id.m_handle << endl; }
    bool operator == (thread::id a, thread::id b) noexcept { return a.m_handle == b.m_handle; }
    bool operator != (thread::id a, thread::id b) noexcept { return a.m_handle != b.m_handle; }
    bool operator >= (thread::id a, thread::id b) noexcept { return a.m_handle >= b.m_handle; }
    bool operator <= (thread::id a, thread::id b) noexcept { return a.m_handle <= b.m_handle; }
    bool operator >  (thread::id a, thread::id b) noexcept { return a.m_handle > b.m_handle; }
    bool operator <  (thread::id a, thread::id b) noexcept { return a.m_handle < b.m_handle; }

	void swap(thread &a, thread &b) noexcept { }

	thread::thread() noexcept { }
	thread::~thread() {
        if(joinable())
            std::terminate();
    }

	thread::id thread::get_id() const noexcept { return m_id; }
	thread::native_handle_type thread::native_handle() { return m_id.m_handle; }
	void thread::detach() {
        //TODO: not implemented
    }
	void thread::join() {
        if(joinable()) {
            if(::WaitForSingleObject(reinterpret_cast<HANDLE>(m_id.m_handle),
                        INFINITE)
                    != WAIT_OBJECT_0)
                throw platform_error(::GetLastError());
        }
        m_id = id();
    }
	bool thread::joinable() const noexcept { return m_id != id(); }
	unsigned thread::hardware_concurrency() noexcept { return 0L; }

    void thread::start_thread(shared_callable_base_type shared_callable_base) {
        shared_callable_base->m_self = shared_callable_base;
        DWORD threadId;
        HANDLE handle = ::CreateThread(NULL, 0, &thread_proc, shared_callable_base.get(), 0, &threadId);
        m_id = id(reinterpret_cast<native_handle_type>(handle));
        if(handle == NULL) {
            shared_callable_base->m_self.reset();
            throw platform_error(::GetLastError());
        }
    }

    namespace this_thread {
        thread::id get_id() noexcept { return thread::id(reinterpret_cast<thread::native_handle_type>(::GetCurrentThread())); }
        void yield() noexcept { ::SleepEx(0, TRUE); }
        void sleep_for(chrono::milliseconds msecs, chrono::nanoseconds nsecs) { ::SleepEx(msecs.count(), TRUE); }
    }
}
