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
                private:
                    explicit id(native_handle_type);
				public:
                    id() noexcept;
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
		extern thread::id get_id();
		extern void yield();
	}
}

#endif //HTTPPROXY_THREAD_HPP_INCLUDED
