// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3

// Standard libs
#include <iostream>
#include <string>

// Internal libs
#include "main.hpp"
#include "log.hpp"
#include "mp.hpp"


int main(const int argc, const char **argv) {

	init_console();

    if (argc == 1) {
        std::cout << APP_USAGE;
        return ERR_USAGE;
    }

	MP_Int num = MP_Int();
	num.load(std::string(argv[1]));

	log::debug(num);
	log::info(num);
	log::warn(num);
	log::err(num);
	log::critical(num);

    return OK;
}


