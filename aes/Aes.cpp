#include <iostream>
#include <iomanip>
#include "Aes.h"
#include "utils.h"

AesSbox::AesGf256 AesSbox::gf_;
AesSbox Aes::sbox_;

Aes::Aes()
{
}

Aes::~Aes()
{
}

void Aes::key_expansion(uint32_t key[], uint32_t w[])
{
	int i;

	for (i = 0; i < NK; ++i) {
		w[i] = key[i];
	}

	uint32_t temp;
	for (; i < NB * (NR + 1); ++i) {
		temp = w[i - 1];
		if (i % NK == 0)
			temp = sub_word(utils::rotr32(temp, 8)) ^ rcon(i / NK);
		else if ((NK == 8) && (i % NK == 4))
			temp = sub_word(temp);
		w[i] = w[i - NK] ^ temp;
	}

	if (true) {
		for (i = 0; i < NB * (NR + 1); ++i) {
			std::cout << std::hex << std::setfill('0') << std::setw(8) << w[i];
			if (i % 8 == 7)
				std::cout << std::endl;
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void Aes::key_contraction(uint32_t w[], int num, uint32_t key[])
{
	uint32_t full_w[ROUND_KEY_SIZE];
	int i;

	for (i = 0; i < NB; ++i) {
		full_w[NB * num + i] = w[i];
	}

	uint32_t temp;
	for (i = NB * num - 1; i >= 0; --i) {
		temp = full_w[i + NK - 1];
		if (i % NK == 0)
			temp = sub_word(utils::rotr32(temp, 8)) ^ rcon(i / NK + 1);
		else if ((NK == 8) && (i % NK == 4))
			temp = sub_word(temp);
		full_w[i] = full_w[i + NK] ^ temp;
	}

	for (i = 0; i < NK; ++i) {
		key[i] = full_w[i];
	}

	if (true) {
		for (i = 0; i < NB * (NR + 1); ++i) {
			std::cout << std::hex << std::setfill('0') << std::setw(8) << full_w[i];
			if (i % 8 == 7)
				std::cout << std::endl;
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}
