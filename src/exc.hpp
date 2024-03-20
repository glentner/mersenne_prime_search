// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Command-line Interface
//

// Standard libs
#include <string>
#include <exception>


class mps_error: public std::exception {
public:
	std::string msg;
	mps_error(const std::string& msg = ""): msg(msg) {}

	virtual const char* what() const noexcept {
		return msg.c_str();
    }
};

