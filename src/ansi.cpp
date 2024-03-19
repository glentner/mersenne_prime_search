// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// String methods
//


// Standard libs
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>    // getenv
#include <unistd.h>   // isatty, fileno

// Internal libs
#include "ansi.hpp"


void init_tty() {
	// Check environment variables and I/O context to decide if we should
	// be printing characters with ansi color sequences or suppress them.
	//
	// NOTE: This should be called by main() once at startup.

	if (not isatty(fileno(stdout))) {
		STDOUT_COLOR = false;
	}

	if (not isatty(fileno(stderr))) {
		STDERR_COLOR = false;
	}

	if (std::getenv("NO_COLOR")) {
		NO_COLOR = true;
		STDOUT_COLOR = false;
		STDERR_COLOR = false;
	}

	if (std::getenv("FORCE_COLOR")) {
		FORCE_COLOR = true;
		STDOUT_COLOR = true;
		STDERR_COLOR = true;
	}
}


std::string format_ansi(Ansi ansi, const std::string& str) {
	// Wrap `str` with given `ansi` escape sequence and RESET (if necessary).
	//
	// This method considers NO_COLOR or FORCE_COLOR to implicitly
	// suppress applying ansi color escape sequences.
	//
	// TODO: We need a better way to deal with <stdout> vs <stderr>.
	//       Right now `log` methods are only used here so we'll assume
	//       only <stderr> for now.

    if (NO_COLOR and not FORCE_COLOR) {
        return str;
	}
	if (not STDERR_COLOR) {
		return str;
	}
	if (str.ends_with(ansi_by_id[RESET])) {
		return ansi_by_id[ansi] + str;
	}
	return ansi_by_id[ansi] + str + ansi_by_id[RESET];
}


std::string bold(const std::string& str) {
	return format_ansi(BOLD, str);
}

std::string faint(const std::string& str) {
	return format_ansi(FAINT, str);
}

std::string italic(const std::string& str) {
	return format_ansi(ITALIC, str);
}

std::string underline(const std::string& str) {
	return format_ansi(UNDERLINE, str);
}

std::string black(const std::string& str) {
	return format_ansi(BLACK, str);
}

std::string red(const std::string& str) {
	return format_ansi(RED, str);
}

std::string green(const std::string& str) {
	return format_ansi(GREEN, str);
}

std::string yellow(const std::string& str) {
	return format_ansi(YELLOW, str);
}

std::string blue(const std::string& str) {
	return format_ansi(BLUE, str);
}

std::string magenta(const std::string& str) {
	return format_ansi(MAGENTA, str);
}

std::string cyan(const std::string& str) {
	return format_ansi(CYAN, str);
}

std::string white(const std::string& str) {
	return format_ansi(WHITE, str);
}

