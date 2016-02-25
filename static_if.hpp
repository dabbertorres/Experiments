#ifndef DBR_STATIC_IF_HPP
#define DBR_STATIC_IF_HPP

namespace dbr
{
	namespace impl
	{
		template<typename Exp>
		struct static_if;
	}

	template<typename Exp>
	constexpr auto static_if(Exp) noexcept
	{
		return impl::static_if<Exp::type>{};
	}

	namespace impl
	{
		template<>
		struct static_if<std::true_type>
		{
			template<typename Func>
			auto then(Func&& func) noexcept
			{
				func();
				return *this;
			}

			template<typename Func>
			auto static_else(Func&&) noexcept
			{
				// result is true, don't go to else branch
				return *this;
			}

			template<typename Exp>
			auto static_else_if() noexcept
			{
				// result is true, don't go to else if branch
				return *this;
			}
		};

		template<>
		struct static_if<std::false_type>
		{
			template<typename Func>
			auto then(Func&&) noexcept
			{
				// result is false, don't execute
				return *this;
			}

			template<typename Func>
			auto static_else(Func&& func) noexcept
			{
				// result is false, execute else
				func();
				return *this;
			}

			template<typename Exp>
			auto static_else_if(Exp) noexcept
			{
				// result is false, go to else if branch
				return static_if<Exp::type>{};
			}
		};
	}
}

#endif
