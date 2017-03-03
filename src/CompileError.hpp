#include <stdexcept>
#include <sstream>

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
		std::stringstream s;
		if(lineno == 0) {
			s << "error: " << runtime_error::what();
		} else {
			s << "error: " << filename << ":" << lineno << ": " << runtime_error::what();
		}

		return s.str().c_str();
	}
};
