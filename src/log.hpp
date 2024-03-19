// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Logging
//

// Standard libs
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <ctime>       // localtime
#include <iterator>
#include <locale>
#include <functional>
#include <unistd.h>    // gethostname

// Internal libs
#include "main.hpp"
#include "ansi.hpp"


#ifndef _MPS_LOG_
#define _MPS_LOG_


namespace log {

	enum Style {
		LOG_DEFAULT,
		LOG_DETAILED,
	};

	static std::map<std::string, Style>
	style_by_name {
		{"default",   LOG_DEFAULT},
		{"detailed",  LOG_DETAILED},
	};

	static Style style = LOG_DEFAULT;

	inline void set_style(const std::string& str) {
		if (style_by_name.find(str) != style_by_name.end()) {
			style = style_by_name[str];
		} else {
			throw std::runtime_error("Invalid log::style '" + str + "'");
		}
	}

	enum Level : uint8_t {
		DEBUG = 0,
		INFO = 1,
		WARNING = 2,
		ERROR = 3,
		CRITICAL = 4
	};

	static std::map<Level, std::string>
	name_by_level {
		{DEBUG,    "DEBUG"},
		{INFO,     "INFO"},
		{WARNING,  "WARNING"},
		{ERROR,    "ERROR"},
		{CRITICAL, "CRITICAL"}
	};

	static std::map<Level, std::function<std::string(std::string)>>
	color_by_level {
		{DEBUG,    blue},
		{INFO,     green},
		{WARNING,  yellow},
		{ERROR,    red},
		{CRITICAL, magenta}
	};

	inline std::string timestamp() {
		std::time_t time = std::time(nullptr);
		char time_chars[100];
		std::strftime(time_chars,
				      sizeof(time_chars),
					  "%Y-%m-%d %H:%M:%S",
					  std::localtime(&time));
		return time_chars;
	}

	class Logger {
	public:
		Level level = WARNING;
		std::string hostname;

		static Logger& get() {
			static Logger instance;
			return instance;
		}

		void set_level(Level level) {
			this -> level = level;
		}

	private:
		Logger(){
			char hostname[1024];
			gethostname(hostname, 1024);
			this -> hostname = hostname;
		}

	public:
		Logger(Logger const&)          = delete;
		void operator=(Logger const&)  = delete;
	};

	inline Logger& get() { return Logger::get(); }

	inline void __print(std::ostream& s){
		s << std::endl;
		s << std::flush;
	}

	template<typename Arg0, typename... Args>
	inline void __print(std::ostream& s, Arg0&& arg0, Args&&... args) {
		s << arg0;
		__print(s, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void print_default(Level level, Args&&... args) {
		std::string name = name_by_level[level];
		name.insert(name.begin(), 8 - name.size(), ' ');
		__print(
			std::cerr,
			bold(color_by_level[level](name)),
			faint(" ["), faint(APP_NAME), faint("] "),
			std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void print_detailed(Level level, Args&&... args) {
		std::string name = name_by_level[level];
		name.insert(name.begin(), 8 - name.size(), ' ');
		__print(
			std::cerr,
			faint(timestamp()), " ",
			faint(get().hostname), " ",
			bold(color_by_level[level](name)),
			faint(" ["), faint(APP_NAME), faint("] "),
			std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void print(Level level, Args&&... args) {
		if (get().level > level) {
			return;
		} else {
			switch (style) {
				case LOG_DEFAULT:
					print_default(level, std::forward<Args>(args)...);
					break;
				case LOG_DETAILED:
					print_detailed(level, std::forward<Args>(args)...);
					break;
			}
		}
	}


	template <typename... Args>
	inline void debug(Args&&... args) {
		print(DEBUG,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void info(Args&&... args) {
		print(INFO,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void warn(Args&&... args) {
		print(WARNING,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void warning(Args&&... args) {
		print(WARNING,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void err(Args&&... args) {
		print(ERROR,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void error(Args&&... args) {
		print(ERROR,
			  std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void critical(Args&&... args) {
		print(CRITICAL,
			  std::forward<Args>(args)...);
	}
}

#endif

