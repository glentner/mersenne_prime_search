# SPDX-FileCopyrightText: 2024 Geoffrey Lentner
# SPDX-License-Identifier: GPLv3

CXX      := clang++
CXXFLAGS := -Ofast -std=c++20 -I src

EXE      := bin/mps
MODULES  := ansi log cli io mp math

SOURCES  := $(addsuffix .cpp,$(addprefix src/,$(MODULES)))
OBJECTS  := $(subst src/,lib/,$(SOURCES:.cpp=.o))

$(EXE): src/main.cpp src/main.hpp $(OBJECTS)
	$(CXX) $(<) $(OBJECTS) -o $(@) $(CXXFLAGS)

lib/%.o: src/%.cpp src/%.hpp
	$(CXX) $(<) -c -o $(@) $(CXXFLAGS)

