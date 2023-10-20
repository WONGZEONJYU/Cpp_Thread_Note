#include "XMutex.h"

XMutex::XMutex(std::mutex& mux) :mux_{ mux } {
	//std::cout << "Lock\n";
	mux.lock();
}

XMutex::~XMutex() noexcept {
	//cout << "Unlock\n";
	mux_.unlock();
}
