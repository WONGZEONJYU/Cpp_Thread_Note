#pragma once
#ifndef XMUTEX_H
#define XMUTEX_H

#include <mutex>

/*RAII*/
class XMutex
{
	XMutex(const XMutex&) = delete;
	XMutex& operator =(const XMutex&) = delete;

public:
	explicit XMutex(std::mutex& mux);
	~XMutex() noexcept;
private:
	std::mutex& mux_;
};

#endif // XMUTEX_H

