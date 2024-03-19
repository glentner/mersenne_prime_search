// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3

// Standard libs
#include <iostream>
#include <string>
#include <exception>

// Internal libs
#include "main.hpp"
#include "log.hpp"
#include "mp.hpp"


int main(const int argc, const char **argv) {

	log::init();
	log::set_level("debug");

    if (argc == 1) {
        std::cout << APP_USAGE;
        return ERR_USAGE;
    }

	std::vector<std::string> args {argv + 1, argv + argc};
	try {
		while (true) {
			break;
			throw std::invalid_argument(args[0]);
		}

		log::debug("Called log::set_style(\"detailed\")");
		log::set_style("detailed");

		BigInt num = BigInt();
		num.load(std::string(argv[1]));

		log::debug(num);
		log::info(num);
		log::warn(num);
		log::err(num);
		log::critical(num);

	} catch (std::invalid_argument const& error) {

		log::critical("Invalid argument: ", error.what());
		return ERR_ARG;

	} catch (std::runtime_error const& error) {

		log::critical(error.what());
		return ERR_RUN;

	} catch (std::exception const& error) {

		log::critical("Uncaught exception: ", error.what());
		return ERR_UNKNOWN;
	}

    return OK;
}


