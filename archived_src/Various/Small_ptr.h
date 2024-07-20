//# Title: Small ptr
//# Description: Yoinked from kactl. A 32-bit pointer that points into BumpAllocator memory.

#include "Bump_allocator.h"

template<class T> struct ptr {
	unsigned ind;
	ptr(T* p = 0) : ind(p ? unsigned((char*)p - buf) : 0) {
		assert(ind < sizeof buf);
	}
	T& operator*() const { return *(T*)(buf + ind); }
	T* operator->() const { return &**this; }
	T& operator[](int a) const { return (&**this)[a]; }
	explicit operator bool() const { return ind; }
};
