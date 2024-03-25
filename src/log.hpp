// SPDX-FileCopyrightText: 2024 Geoffrey Lentner
// SPDX-License-Identifier: GPLv3
//
// Logging
//

#pragma once


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


namespace log {


	inline void print(std::ostream& s){
		s << std::endl;
	}


	template<typename Arg0, typename... Args>
	inline void print(std::ostream& s, Arg0&& arg0, Args&&... args) {
		s << arg0;
		print(s, std::forward<Args>(args)...);
	}


	enum Style {
		DEFAULT,
		DETAILED,
	};


	enum Level {
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		CRITICAL
	};


	static std::map<std::string, Style>
	style_by_name {
		{"default",   DEFAULT},
		{"detailed",  DETAILED},
	};


	static std::map<std::string, Level>
	level_by_name {
		{"debug",    DEBUG},
		{"info",     INFO},
		{"warning",  WARNING},
		{"error",    ERROR},
		{"critical", CRITICAL},
	};


	static std::map<Level, std::string>
	name_by_level {
		{DEBUG,    "debug"},
		{INFO,     "info"},
		{WARNING,  "warning"},
		{ERROR,    "error"},
		{CRITICAL, "critical"},
	};


	static std::map<Level, std::function<std::string(std::string)>>
	color_by_level {
		{DEBUG,    blue},
		{INFO,     green},
		{WARNING,  yellow},
		{ERROR,    red},
		{CRITICAL, magenta}
	};


	static Style style;
	static Level level;

	static std::string hostname;
	static std::string task_id;
	static std::string name;


	inline void set_hostname() {
		char h[1024];
		gethostname(h, 1024);
		hostname = h;
	}


	inline void set_style(const std::string &name) {
		if (style_by_name.find(name) != style_by_name.end()) {
			style = style_by_name[name];
		} else {
			throw std::runtime_error("Unrecognized log::style, \"" + name + "\"");
		}
	}


	inline void set_level(const std::string &name) {
		if (level_by_name.find(name) != level_by_name.end()) {
			level = level_by_name[name];
		} else {
			throw std::runtime_error("Unrecognized log::level, \"" + name + "\"");
		}
	}


	inline void set_task_id() {
		if (const char* _task_id = std::getenv("TASK_ID")) {
			task_id = _task_id;
		}
	}


	inline void init() {
		init_tty();
		set_hostname();
		set_task_id();
	}


	inline std::string timestamp() {
		std::time_t time = std::time(nullptr);
		char time_chars[100];
		std::strftime(time_chars,
					  sizeof(time_chars),
					  "%Y-%m-%d %H:%M:%S",
					  std::localtime(&time));
		return time_chars;
	}


	template <typename... Args>
	inline void log_default(Level level, Args&&... args) {
		std::string name = name_by_level[level];
		name.insert(name.begin(), 8 - name.size(), ' ');
		print(
			std::cerr,
			bold(color_by_level[level](name)),
			faint(" ["), faint(APP_NAME), faint("] "),
			std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void log_detailed(Level level, Args&&... args) {
		std::string name = name_by_level[level];
		name.insert(name.begin(), 8 - name.size(), ' ');
		std::string task_id_part = "";
		if (not task_id.empty() ) {
			task_id_part = "[" + task_id + "] ";
		}
		print(
			std::cerr,
			faint(timestamp()), " ",
			faint(hostname), " ",
			faint(task_id_part),
			bold(color_by_level[level](name)),
			faint(" ["), faint(APP_NAME), faint("] "),
			std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void log(Level _level, Args&&... args) {
		if (level > _level)
			return;
		switch (style) {
			case DEFAULT:
				log_default(_level, std::forward<Args>(args)...);
				break;
			case DETAILED:
				log_detailed(_level, std::forward<Args>(args)...);
				break;
		}
	}


	template <typename... Args>
	inline void debug(Args&&... args) {
		log(DEBUG, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void info(Args&&... args) {
		log(INFO, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void warn(Args&&... args) {
		log(WARNING, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void warning(Args&&... args) {
		log(WARNING, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void err(Args&&... args) {
		log(ERROR, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void error(Args&&... args) {
		log(ERROR, std::forward<Args>(args)...);
	}


	template <typename... Args>
	inline void critical(Args&&... args) {
		log(CRITICAL, std::forward<Args>(args)...);
	}

}

