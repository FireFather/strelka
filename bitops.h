#pragma once
#include <intrin.h>
#include "types.h"

inline int popcnt(const uint64 b)
{
	return (int)_mm_popcnt_u64(b);
}

inline int lsb(const uint64 b)
{
	unsigned long y;
	_BitScanForward64(&y, b);
	return (int)y;
}

inline int msb(const uint64 b)
{
	unsigned long y;
	_BitScanReverse64(&y, b);
	return (int)y;
}
