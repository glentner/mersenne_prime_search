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
	OK            = 0,  // Everything ran as expected
	ERR_USAGE     = 1,  // Usage or help text printed
	ERR_ARG       = 2,  // Wrong command-line invocation
	ERR_CFG       = 3,  // Configuration error
	ERR_FILE      = 4,  // File I/O or formatting error
	ERR_RUN       = 5,  // Generic runtime error
	ERR_UNKNOWN   = 6,  // Unexpected internal failure
};


static const std::string APP_USAGE = R"USAGE(Usage:
  mps [-hv] PVAL [-t NAME] [-f PATH]
  Check if number is Mersenne prime.)USAGE";


static const std::string APP_HELP = R"HELP(Usage:
  mps [-hv] PVAL [-t TEST] [-f PATH] [-s | -p]
  Check if number is Mersenne prime.

Arguments:
  NUM                     P-value to check.

Options:
  -p, --ptest             Only test if PVAL is prime.
  -s, --skip-ptest        Suppress initial test on PVAL.
  -t, --test        NAME  One of 'tf', 'p1', 'll' (default: 'all').
  -f, --file        PATH  File path for check-pointing.
  -v, --version           Show version and exit.
  -h, --help              Show this message and exit.)HELP";


#endif

