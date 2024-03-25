// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Metadata and usage text
//


// Standard libs
#include <string>


#ifndef _MPS_MAIN_
#define _MPS_MAIN_


static const std::string APP_NAME = "mps";
static const std::string APP_VERSION = "0.1.0";


enum Status {
	OK            = 0,   // Everything ran as expected
	ERR_ARG       = 1,   // Wrong command-line invocation
	ERR_CFG       = 2,   // Configuration error
	ERR_FILE      = 10,  // File I/O or formatting error
	ERR_RUN       = 20,  // Generic runtime error
	ERR_UNKNOWN   = 30,  // Unexpected internal failure
};


static const std::string APP_USAGE = R"USAGE(Usage:
  mps [-hv] [-p] PVAL [-s] [-t NAME] [-f PATH]
  Check if number is Mersenne prime.)USAGE";


static const std::string APP_HELP = R"HELP(Usage:
  mps [-hv] [-p] PVAL [-s] [-t NAME] [-f PATH]
  Check if number is Mersenne prime.

Arguments:
  NUM                     P-value to check.

Options:
  -p, --primes            Print primes up to PVAL.
  -s, --skip-ptest        Suppress initial prime test on PVAL.
  -t, --test        NAME  One of 'tf', 'p1', 'll' (default: 'all').
  -f, --file        PATH  File path for check-pointing.
  -v, --version           Show version and exit.
  -h, --help              Show this message and exit.)HELP";


#endif

