#pragma once
#include "utils.h"
#include "Gf256.h"

class AesSbox
{
private:
	using AesGf256 = Gf256 < (0x80 | 0x1b) >;
	static AesGf256 gf_;
	uint8_t sbox_[256];
	uint8_t inv_sbox_[256];

public:

	AesSbox()
	{
		uint8_t x = 0;
		uint8_t value;
		do {
			value = at(x);
			sbox_[x] = value;
			inv_sbox_[value] = x;
		} while (++x != 0);
	}

	~AesSbox()
	{
	}

	uint8_t at(uint8_t x)
	{
		uint8_t sft;
		x = sft = gf_.inv(x);
		for (int i = 0; i < 4; ++i) {
			sft = utils::rotl8(sft, 1);
			x ^= sft;
		}
		x ^= 0x63; // 0b01100011 
		return x;
	}

	uint8_t operator[](uint8_t x)
	{
		return sbox_[x];
	}

	uint8_t inv(uint8_t x)
	{
		return inv_sbox_[x];
	}

	uint8_t rcon(uint8_t x)
	{
		if (x == 0)
			return 0;
		uint8_t c = 1;
		for (; x != 1; --x)
			c = gf_.mul(c, 2);
		return c;
	}
};
