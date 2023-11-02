#ifndef XTASK_H
#define XTASK_H
#include <functional>
#include <iostream>
#include <future>

class XTask
{
	XTask(const XTask&) = delete;
	XTask& operator=(const XTask&) = delete;

public:
	XTask(XTask&& o) noexcept :
		p_{ std::move(o.p_) }, is_exit { std::move(o.is_exit) } {}

	virtual ~XTask() { 
		//std:: cout << __FUNCTION__ << " destroy\n"; 
	}

	std::function<bool()> is_exit{};

	void SetValue(int v){
		p_.set_value(v);
	}

	auto GetReturn(){
		/*阻塞等待 SetValue*/
		return p_.get_future().get();
	}

protected:
	explicit XTask(){
		//std::cout << __FUNCTION__ << " construction\n"; 
	}

	virtual int Run() = 0;

private:
	/*用来接收返回值*/
	std::promise<int> p_{};
};

#endif
