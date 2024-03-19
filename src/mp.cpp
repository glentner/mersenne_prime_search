// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Multiple-Precision
//

// Standard libs
#include <iostream>
#include <string>
#include <vector>

// Internal libs
#include "mp.hpp"


MP_Int::MP_Int() {}

MP_Int::MP_Int(std::vector<uint16_t> const& digits) {
	this -> digits = digits;
}

// Load digits from existing string into MP_Int
void MP_Int::load(const std::string& other) {
	digits.clear();
	digits.reserve(other.size());
	for (const char& c: other) {
		digits.push_back(c - '0');
	}
}

// The size is just the size of the vector
size_t MP_Int::size() {
	return digits.size();
}

// Printing MP_Int to stream prints digits
std::ostream& operator<<(std::ostream& s, const MP_Int& m) {
	for (const uint16_t& n: m.digits) {
		s << n;
	}
	return s;
}

