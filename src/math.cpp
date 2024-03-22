// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Mathematical operations and tests.
//


// Standard libs
#include <iostream>
#include <cstdint>
#include <vector>

// Internal libs
#include "math.hpp"
#include "log.hpp"


std::vector<bool> prime_sieve(size_t n) {

	size_t i, j;
	std::vector<bool> is_prime(n, true);

	// All even are composite
	for (i = 0; i < n; i += 2)
		is_prime[i] = false;

	// Special case
	is_prime[2] = true;

	i = 3;
	while (i * i < n) {
		if (is_prime[i])
			for (j = i * i; j < n; j += 2 * i)
				is_prime[j] = false;
		i += 2;
	}

	return is_prime;
}


void display_primes(size_t n) {

	std::vector<bool> is_prime = prime_sieve(n);

	for (size_t i = 3; i < n; i += 2)
		if (is_prime[i])
			std::cout << i << std::endl;
}


