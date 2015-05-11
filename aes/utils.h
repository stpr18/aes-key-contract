#pragma once
#include <cstdint>
#include <intrin.h>

#pragma intrinsic(_rotl8, _rotr8, _rotl, _rotr)


namespace utils
{
	inline uint8_t rotl8(uint8_t value, unsigned char shift) {
		return _rotl8(value, shift);
	}

	inline uint8_t rotr8(uint8_t value, unsigned char shift) {
		return _rotr8(value, shift);
	}

	inline uint32_t rotl32(uint32_t value, unsigned char shift) {
		return _rotl(value, shift);
	}

	inline uint32_t rotr32(uint32_t value, unsigned char shift) {
		return _rotr(value, shift);
	}
}
