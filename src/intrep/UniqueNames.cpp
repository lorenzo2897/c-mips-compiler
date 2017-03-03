#include "UniqueNames.hpp"

#include <map>
#include <sstream>

std::map<std::string, unsigned> unique_names;

std::string unique(std::string base) {
	if(unique_names.count(base) == 0) {
		// does not exist, create
		unique_names[base] = 1;
	} else {
		// already exists, increment and use
		unique_names[base]++;
	}

	std::stringstream ss;
	ss << base << unique_names[base];
	return ss.str();
}
