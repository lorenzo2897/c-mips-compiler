#include "Declaration.hpp"

Declaration::Declaration() : pointer_depth(0), initialiser(NULL) {}

void Declaration::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Declaration : " << identifier;

	dst << std::endl << spaces(indent) << "  Specifiers:";
	for(std::vector<std::string>::const_iterator itr = specifiers.begin(); itr != specifiers.end(); ++itr) {
		dst << " " << (*itr);
	}
	for(int i = 0; i < pointer_depth; ++i) {
		dst << " *";
	}
	dst << std::endl << spaces(indent);

	if(initialiser) {
		dst << "  Initialiser: ";
		initialiser->Debug(dst, indent);
	} else {
		dst << "  Initialiser: null" << std::endl;
	}
	dst << std::endl;
}
