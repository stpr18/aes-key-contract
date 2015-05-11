#pragma once
#include "AesSbox.h"

class Aes
{
private:
	static AesSbox sbox_;

public:
	static const unsigned int NB = 4; //const
	static const unsigned int NK = 4; //4, 6, or 8
	static const unsigned int NR = NK + 6;

	static const unsigned int SECRET_KEY_SIZE = NK;
	static const unsigned int ROUND_KEY_SIZE = NB * (NR + 1);

	Aes();
	~Aes();

	static uint8_t sbox(uint8_t x)
	{
		return sbox_[x];
	}

	static uint8_t inv_sbox(uint8_t x)
	{
		return sbox_.inv(x);
	}

	static uint32_t sub_word(uint32_t x)
	{
		return
			sbox(x & 0xff) |
			(sbox((x >> 8) & 0xff) << 8) |
			(sbox((x >> 16) & 0xff) << 16) |
			(sbox((x >> 24) & 0xff) << 24);
	}

	static uint32_t inv_sub_word(uint32_t x)
	{
		return
			inv_sbox(x & 0xff) |
			(inv_sbox((x >> 8) & 0xff) << 8) |
			(inv_sbox((x >> 16) & 0xff) << 16) |
			(inv_sbox((x >> 24) & 0xff) << 24);
	}

	static uint8_t rcon(uint8_t x)
	{
		return sbox_.rcon(x);
	}

	static void key_expansion(uint32_t key[], uint32_t w[]);
	static void Aes::key_contraction(uint32_t w[], int num, uint32_t key[]);
};
