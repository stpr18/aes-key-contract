#pragma once
#include <cstdint>

class Aes;

namespace test
{
	void aes_sbox();
	void aes_inv_sbox();
	void aes_rcon();
	void aes_make_rand_key(uint32_t key[]);
	void aes_key_contraction(uint32_t key[]);
}
