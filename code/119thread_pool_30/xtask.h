#ifndef XTASK_H
#define XTASK_H
#include <functional>
#include <iostream>
#include <future>

class XTask
{
public:
	explicit XTask() { 
		std::cout << __FUNCTION__ << " construction\n"; 
	}

	XTask(const XTask& o) :is_exit{ o.is_exit } {

		const_cast<XTask&>(o).is_exit = nullptr;
		std::cout << __FUNCTION__ << " copy construction\n";
	}

	XTask(XTask&& o)  :is_exit{ o.is_exit } {
		o.is_exit = nullptr;
		std::cout << __FUNCTION__ << " copy construction\n";
	}

	virtual ~XTask() { 
		std:: cout << __FUNCTION__ << " destroy\n"; 
	}

	virtual int Run() = 0;
	std::function<bool()> is_exit {};

	void SetValue(int v)
	{
		p_.set_value(v);
	}

	auto GetReturn()
	{
		/*�����ȴ� SetValue*/
		return p_.get_future().get();
	}

private:
	/*�������շ���ֵ*/
	std::promise<int> p_;
};

#endif
