#pragma once

#include <cobalt/assertions.hpp>
#include <cobalt/macros.hpp>
#include <cobalt/containers/smartpointers.hpp>

namespace cobalt
{
	template<typename T>
	class CbFunction;

	template<typename ReturnType, typename ... ArgumentTypes>
	class CbFunction<ReturnType(ArgumentTypes...)>
	{
		public:
			CbFunction();
			CbFunction(const CbFunction& func);
			CbFunction(CbFunction&& func) noexcept;

			template<typename T>
			CbFunction(T t);

			~CbFunction();

			CbFunction& operator= (const CbFunction& func);
			CbFunction& operator= (CbFunction&& func) noexcept;

			CbFunction& operator= (std::nullptr_t) noexcept;

			explicit operator bool() const;

			ReturnType operator() (ArgumentTypes ... args);

		private:
			class ICallable
			{
				public:
					ICallable() = default;
					virtual ~ICallable() = default;
					virtual ReturnType invoke(ArgumentTypes ... args) = 0;

					COBALT_NO_COPY_MOVE(ICallable)
			};

			template<typename Type>
			class Callable : public ICallable
			{
				public:
					Callable(const Type& type)
						: _type(type)
					{
					}

					~Callable() override = default;

					COBALT_NO_COPY_MOVE(Callable)

					ReturnType invoke(ArgumentTypes ... args) override
					{
						return _type(args...);
					}

				private:
					Type _type;
			};

			SharedPtr<ICallable> _func;
	};

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>::CbFunction()
	{
		_func = nullptr;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>::CbFunction(const CbFunction& func)
	{
		_func = func._func;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>::CbFunction(CbFunction&& func) noexcept
	{
		_func = func._func;
		func._func = nullptr;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>::~CbFunction()
	{
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>& CbFunction<ReturnType(ArgumentTypes...)>::operator=(const CbFunction& func)
	{
		_func = func._func;
		return *this;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>& CbFunction<ReturnType(ArgumentTypes...)>::operator=(CbFunction&& func) noexcept
	{
		_func = func._func;
		func._func = nullptr;
		return *this;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>& CbFunction<ReturnType(ArgumentTypes...)>::operator=(std::nullptr_t) noexcept
	{
		_func = nullptr;
		return *this;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	CbFunction<ReturnType(ArgumentTypes...)>::operator bool() const
	{
		return _func != nullptr;
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	ReturnType CbFunction<ReturnType(ArgumentTypes...)>::operator()(ArgumentTypes ...args)
	{
#if defined(_DEBUG)
		Require(_func.get() != nullptr);
#endif
		return _func->invoke(args...);
	}

	template<typename ReturnType, typename ...ArgumentTypes>
	template<typename T>
	CbFunction<ReturnType(ArgumentTypes...)>::CbFunction(T t)
	{
		_func = SharedPtr<ICallable>((ICallable*)new Callable<T>(t));
	}
}
