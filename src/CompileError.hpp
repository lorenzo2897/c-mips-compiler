#ifndef COMPILE_ERROR_H
#define COMPILE_ERROR_H

#include <stdexcept>
#include <sstream>
#include <cstdio>
#include <cstdlib>

class compile_error : public std::runtime_error {

private:

static std::string buildstr(std::string what_msg, std::string filename, unsigned lineno) {
	std::string s;

	if(lineno != 0) {
		char buf[10];
		sprintf(buf, "%d", lineno);
		s = filename + ":" + buf + ": ";
	}

	s += "error: ";
	s += what_msg;

	return s;
}

public:

	compile_error(std::string what_msg) : runtime_error(what_msg)
	{}

	compile_error(std::string what_msg, std::string filename, unsigned lineno) : runtime_error(buildstr(what_msg, filename, lineno))
	{}

	~compile_error() throw() {

	}
};

#endif
