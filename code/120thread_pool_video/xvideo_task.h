#pragma once
#ifndef XVIDEO_TASK_H
#define XVIDEO_TASK_H

#include "xthread_pool.h"

class XVideoTask :public XTask
{
public:
	std::string in_path{}, out_path{};

	int width{}, height{};

private:
	int Run() override;
};

#endif

