#include <cstdlib>
#include <iostream>
#include "Aes.h"
#include "test.h"

int main(int argc, char **argv)
{
	//basic test
	test::aes_sbox();
	test::aes_inv_sbox();
	test::aes_rcon();

	//key contraction
	uint32_t key[Aes::SECRET_KEY_SIZE];
	test::aes_make_rand_key(key);
	test::aes_key_contraction(key);

	std::system("pause");

	return EXIT_SUCCESS;
}
