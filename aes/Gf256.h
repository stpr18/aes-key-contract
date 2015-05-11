#pragma once
#include <cstdint>

template <size_t POLYNOMIAL>
class Gf256
{
	static_assert((POLYNOMIAL & 0x80) == 0x80, "(pp & 0x80) == 0x80");

private:
	uint8_t ltable[256];
	uint8_t atable[256];

public:
	Gf256()
	{
		uint8_t a = 1;
		for (uint8_t i = 0; i < 255; ++i) {
			atable[i] = a;
			bool bitup = (a & 0x80) == 0x80; // 0x80 = 0b10000000
			a <<= 1;
			if (bitup) {
				a ^= POLYNOMIAL & 0x7f;
			}
			a ^= atable[i];
			ltable[atable[i]] = i;
		}
		atable[255] = atable[0];
		ltable[0] = 0;
	}

	~Gf256() {}

	static uint8_t add(uint8_t a, uint8_t b)
	{
		return a ^ b;
	}

	static uint8_t sub(uint8_t a, uint8_t b)
	{
		return a ^ b;
	}

	uint8_t mul(uint8_t a, uint8_t b)
	{
		if (a == 0 || b == 0)
			return 0;
		return atable[(ltable[a] + ltable[b]) % 255];
	}

	uint8_t inv(uint8_t a)
	{
		if (a == 0)
			return 0;
		return atable[255 - ltable[a]];
	}
};
