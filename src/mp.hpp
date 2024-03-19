// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Multiple-Precision
//
// Types allowing for arbitrary precision arithmetic.
// The `BigInt` implements large integer methods.
//

// Standard libs
#include <iostream>
#include <string>
#include <vector>

#ifndef _MPS_MP_
#define _MPS_MP_

class BigInt {
private:
	std::vector<uint16_t> digits {};

public:

	BigInt();
	BigInt(std::vector<uint16_t> const& digits);
	void load(const std::string& other);

	size_t size();
	friend std::ostream& operator<<(std::ostream& s, const BigInt& m);
};


#endif

