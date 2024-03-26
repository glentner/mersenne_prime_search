// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Mathematical operations and tests.
//

#pragma once


// Standard libs
#include <vector>

// Internal libs
#include "mp.hpp"


std::vector<bool> prime_sieve(size_t n);
void display_primes(size_t n);


bool test_quick_factor(BigInt p);
bool test_p_minus_one(BigInt p);
bool test_lucas_lehmer(BigInt p);
bool test_all(BigInt p);

