#ifndef _XTHREAD_POOL_H
#define _XTHREAD_POOL_H
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include "xtask.h"

class XThreadPool
{
	XThreadPool(const XThreadPool&) = delete;
	XThreadPool& operator=(const XThreadPool&) = delete;

public:
	explicit XThreadPool() = default;
	/*@parm num thread_num*/
	void Init(int num);
	/*Call init before calling start*/
	void Start();
	/*Add Task @parm task pointer */
	void AddTask(XTask* task);

private:
	XTask* GetTask();
	void Run();
	int thread_num_{};
	std::mutex mux_;
	std::vector<std::thread*> threads_;
	std::list<XTask*> tasks_;
	std::condition_variable cv_;
};

#endif
