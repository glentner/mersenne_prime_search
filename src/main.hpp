// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Metadata and usage text
//


#ifndef _MPS_MAIN_
#define _MPS_MAIN_

#define APP_NAME "mps"
#define APP_VERSION "0.1.0"


enum Status {
	OK            = 0,  // Everything ran as expected
	ERR_USAGE     = 1,  // Usage or help text printed
	ERR_ARG       = 2,  // Wrong command-line invocation
	ERR_CFG       = 3,  // Configuration error
	ERR_FILE      = 4,  // File I/O or formatting error
	ERR_RUN       = 5,  // Generic runtime error
	ERR_UNKNOWN   = 6,  // Unexpected internal failure
};


static const char* APP_USAGE = R"USAGE(Usage:
  mps [-hv] PVAL [-t NAME] [-f PATH]
  Check if number is Mersenne prime.
)USAGE";


static const char* APP_HELP = R"HELP(Usage:
  mps [-hv] PVAL [-t NAME] [-f PATH]
  Check if number is Mersenne prime.

Arguments:
  NUM                  P-value to check.

Options:
  -t, --test     NAME  Which test to run.
  -f, --file     PATH  File path for check-point.
  -v, --version        Show version and exit.
  -h, --help           Show this message and exit.
)HELP";


#endif

