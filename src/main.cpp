// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3

// Standard libs
#include <iostream>
#include <string>
#include <exception>
#include <regex>

// Internal libs
#include "main.hpp"
#include "log.hpp"
#include "cli.hpp"
#include "mp.hpp"


int main(const int argc, const char **argv) {

	log::init();
	log::set_level("debug");

	try {
		cli::Interface opt {argc, argv};
		opt.parse_args();

		BigInt num = BigInt();
		num.load(opt.pval);

		log::info("Starting (", num, ")");

	} catch (cli::show_info const& error) {
		std::cout << error.what() << std::endl;
		return ERR_USAGE;

	} catch (cli::argument_error const& error) {
		log::critical(error.what());
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


