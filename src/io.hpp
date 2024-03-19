// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Input/Output
//
// This module defines the file format for storing partial results.
// The .mps file is plain text with key value data.

// Standard libs
#include <iostream>
#include <string>
#include <map>

// Internal libs
#include "main.hpp"   // APP_VERSION
#include "mp.hpp"     // MP_Int

#ifndef _MPS_IO_
#define _MPS_IO_


class MP_File {
public:

	MP_File();
	MP_File(const std::string& filepath);

	friend std::ostream& operator<<(std::ostream& some_stream, const MP_File& some_file);
};


static const char* FORMAT_EXAMPLE = R"FORMAT(
VERSION
    MPS v0.1.0
TEST
    Lucas-Lehmer
STARTED
	2024-03-18 00:12:32.123-04:00
ELAPSED
	3-00:12:31.123
I-VALUE
	2890347
P-VALUE
    90587203495
)FORMAT";


#endif

