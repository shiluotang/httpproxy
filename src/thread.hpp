#ifndef HTTPPROXY_THREAD_HPP_INCLUDED
#define HTTPPROXY_THREAD_HPP_INCLUDED

#include <functional>
#include <memory>
#include <chrono>
#include <iosfwd>

namespace httpproxy {

	/**
	 * use C++11 standard library thread definition here.
	 */
	class thread {
		public:
			typedef long native_handle_type;

			class id {
				public:
                    id() noexcept;
                    explicit id(native_handle_type);
				private:
                    native_handle_type m_handle;

                    friend class thread;
                    friend std::ostream& operator << (std::ostream&, id);
                    friend bool operator == (thread::id, thread::id) noexcept;
                    friend bool operator != (thread::id, thread::id) noexcept;
                    friend bool operator >= (thread::id, thread::id) noexcept;
                    friend bool operator <= (thread::id, thread::id) noexcept;
                    friend bool operator >  (thread::id, thread::id) noexcept;
                    friend bool operator <  (thread::id, thread::id) noexcept;

			};
        public:
            struct callable_impl_base;
            typedef std::shared_ptr<callable_impl_base> shared_callable_base_type;
            struct callable_impl_base {
                shared_callable_base_type m_self;
                virtual ~callable_impl_base() {};
                virtual void run() = 0;
            };
            
            template<typename Callable> struct template_callable_impl : public callable_impl_base {
                Callable m_callable;
                explicit template_callable_impl(Callable&& func) :m_callable(std::forward<Callable>(func)) {}
                virtual void run() { m_callable(); }
            };
		public:
			thread() noexcept;
			template<typename Fn, typename... Args> thread(Fn &&fn, Args&&... args) {
                start_thread(make_routine(std::bind(fn, args...)));
            }
			thread(thread const&) = delete;
			thread(thread&& x) noexcept;
			~thread();

			thread& operator = (thread&& rhs);
			thread& operator = (thread const&) = delete;

			bool joinable() const noexcept;
			void join();
			void detach();
			void swap(thread&) noexcept;

			id get_id() const noexcept;
			native_handle_type native_handle();

			static unsigned hardware_concurrency() noexcept;
        private:
            void start_thread(shared_callable_base_type);
            template<typename Callable>
            std::shared_ptr<template_callable_impl<Callable>> make_routine(Callable && callable) {
                return std::make_shared<template_callable_impl<Callable>>(std::forward<Callable>(callable));
            }
        private:
            id m_id;
	};
    extern std::ostream& operator << (std::ostream&, thread::id);
    extern bool operator == (thread::id, thread::id) noexcept;
    extern bool operator != (thread::id, thread::id) noexcept;
    extern bool operator >= (thread::id, thread::id) noexcept;
    extern bool operator <= (thread::id, thread::id) noexcept;
    extern bool operator >  (thread::id, thread::id) noexcept;
    extern bool operator <  (thread::id, thread::id) noexcept;

	extern void swap(thread&, thread&) noexcept;

	namespace this_thread {
		extern thread::id get_id() noexcept;
		extern void yield() noexcept;
		/**
		 * This is not part of standard C++11.
		 * As template functions need implementations defined along with
		 * declarations, we can't use template functions as prototypes
		 * which will encapsulate platform implementations. And we are
		 * not going to use inheritance for abstraction which can result
		 * in bad performance. We use this function for separate
		 * compilation to accomplish implementation encapsulation.
		 */
        extern void sleep_for(std::chrono::milliseconds, std::chrono::nanoseconds);
        template<typename _Rep, typename _Period>
        void sleep_for(std::chrono::duration<_Rep, _Period> const &rtime) {
            std::chrono::milliseconds msecs = std::chrono::duration_cast<std::chrono::milliseconds>(rtime);
            std::chrono::nanoseconds nsecs = std::chrono::duration_cast<std::chrono::nanoseconds>(rtime - msecs);
            sleep_for(msecs, nsecs);
        }
        template<typename _Clock, typename _Duration>
        void sleep_until(std::chrono::time_point<_Clock, _Duration> const &atime) {
            sleep_for(atime - _Clock::now());
        }
	}
}

#endif //HTTPPROXY_THREAD_HPP_INCLUDED
