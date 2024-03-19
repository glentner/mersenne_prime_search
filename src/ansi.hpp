// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// String methods
//

// Standard libs
#include <map>
#include <string>
#include <regex>

#ifndef _MPS_STR_
#define _MPS_STR_


static bool NO_COLOR = false;
static bool FORCE_COLOR = false;
static bool STDOUT_COLOR = true;
static bool STDERR_COLOR = true;


void init_console();


enum Ansi {
    RESET     = 0,
    BOLD      = 1,
    FAINT     = 2,
    ITALIC    = 3,
    UNDERLINE = 4,
    BLACK     = 30,
    RED       = 31,
    GREEN     = 32,
    YELLOW    = 33,
    BLUE      = 34,
    MAGENTA   = 35,
    CYAN      = 36,
    WHITE     = 37
};


static std::map<Ansi, std::string>
ansi_by_id {
	{RESET,     "\033[0m"},
	{BOLD,      "\033[1m"},
	{FAINT,     "\033[2m"},
	{ITALIC,    "\033[3m"},
	{UNDERLINE, "\033[4m"},
	{BLACK,     "\033[30m"},
	{RED,       "\033[31m"},
	{GREEN,     "\033[32m"},
	{YELLOW,    "\033[33m"},
	{BLUE,      "\033[34m"},
	{MAGENTA,   "\033[35m"},
	{CYAN,      "\033[36m"},
	{WHITE,     "\033[37m"}
};


std::string format_ansi(Ansi ansi, const std::string& str);
std::string bold(const std::string& str);
std::string faint(const std::string& str);
std::string italic(const std::string& str);
std::string underline(const std::string& str);
std::string black(const std::string& str);
std::string red(const std::string& str);
std::string green(const std::string& str);
std::string yellow(const std::string& str);
std::string blue(const std::string& str);
std::string magenta(const std::string& str);
std::string cyan(const std::string& str);
std::string white(const std::string& str);


#endif

