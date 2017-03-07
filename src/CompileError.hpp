#include <stdexcept>
#include <sstream>
#include <cstdio>
#include <cstdlib>

class compile_error : public std::runtime_error {

private:
	std::string filename;
	unsigned lineno;

public:

	compile_error(std::string what_msg) : runtime_error(what_msg), filename(""), lineno(0)
	{}

	compile_error(std::string what_msg, std::string filename, unsigned lineno) : runtime_error(what_msg), filename(filename), lineno(lineno)
	{}

	~compile_error() throw() {

	}

	virtual const char* what() const throw() {
		std::string s = "error: ";

		if(lineno != 0) {
			char buf[10];
			sprintf(buf, "%d", lineno);
			s += filename + ":" + buf + ": ";
		}

		s += runtime_error::what();

		return s.c_str();
	}
};
