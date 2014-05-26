#ifndef HTTPPROXY_THREAD_HPP_INCLUDED
#define HTTPPROXY_THREAD_HPP_INCLUDED

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
					id();
					explicit id(native_handle_type);
				public:
					bool operator == (id const&) const;
					bool operator != (id const&) const;
				private:
					struct impl;
					impl *m_data;
					friend class thread;
					friend std::ostream& operator << (std::ostream&, id const&);
			};
		public:
			thread() noexcept;
			template<typename Fn, typename... Args>
				thread(Fn &&fn, Args&&... args) {}
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
	};
	extern std::ostream& operator << (std::ostream&, thread::id const&);

	extern void swap(thread&, thread&) noexcept;

	namespace this_thread {
		thread::id get_id();
		void yield();
	}
}

#endif //HTTPPROXY_THREAD_HPP_INCLUDED
