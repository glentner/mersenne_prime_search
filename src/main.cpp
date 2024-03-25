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
#include "math.hpp"
#include "mp.hpp"


int main(const int argc, const char **argv) {

	log::init();

	try {
		auto opt = cli::parse_args(argc, argv);

		if (opt.debug_mode) {
			log::set_level(log::DEBUG);
		}

		if (opt.detailed_mode) {
			log::set_style(log::DETAILED);
		}

		auto num = BigInt();
		num.load(opt.pval);

		if (opt.show_primes) {
			display_primes(std::stoi(opt.pval));
			return OK;
		}

		log::info("Starting test: ", num);

	} catch (cli::show_info const& error) {
		std::cout << error.what() << std::endl;
		return OK;

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


