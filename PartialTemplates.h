#pragma once
#include <tuple>
template <typename F>
struct Function;

template <typename R>
struct Function<R()> {
	typedef R Result;
	typedef std::tuple ArgumentTuple;
};

template <typename R, typename A1>
struct Function<R(A1)>
	: Function<R()> {
	typedef A1 Argument1;
	typedef std::tuple<A1> ArgumentTuple;
};

template <typename R, typename A1,  typename A2>
struct Function<R(A1,A2)>
	: Function<R(A1)> {
	typedef A2 Argument2;
	typedef std::tuple<A1,A2> ArgumentTuple;
};

template <typename F>
class FunctionMockerBase
{
public:
	typedef typename Function<F>::Result Result;
	typedef typename Function<F>::ArgumentTuple ArgumentTuple;

	const void* MockObject() {
		return mock_obj_;
	}

protected:
	Result InvokeWith(const ArgumentTuple& args)
	{
		return Result();
	}

private:
	const void* mock_obj_; 
	const char* name_;  
};

template <typename F>
class FunctionMocker;

template <typename R>
class FunctionMocker<R()> : public FunctionMockerBase<R()> {
public:
	typedef R F();
	typedef typename Function<F>::ArgumentTuple ArgumentTuple;
	R Invoke() {
		return this->InvokeWith(ArgumentTuple());
	}
};

template <typename R, typename A1>
class FunctionMocker<R(A1)> : public FunctionMockerBase<R(A1)> {
public:
	typedef R F(A1);
	typedef typename Function<F>::ArgumentTuple ArgumentTuple;

	R Invoke(A1 a1) {
		
		return this->InvokeWith(ArgumentTuple(a1));
	}
};

template <typename R, typename A1, typename A2>
class FunctionMocker<R(A1, A2)> : public FunctionMockerBase<R(A1, A2)> {
public:
	typedef R F(A1, A2);
	typedef typename Function<F>::ArgumentTuple ArgumentTuple;

	R Invoke(A1 a1, A2 a2) {
	
		return this->InvokeWith(ArgumentTuple(a1, a2));
	}
};
