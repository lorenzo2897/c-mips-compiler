#include "Declaration.hpp"

Declaration::Declaration() : initialiser(NULL) {}

void Declaration::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Declaration : " << identifier;

	dst << std::endl << spaces(indent) << "  Specifiers: ";
	dst << var_type.name();
	dst << std::endl << spaces(indent);

	if(initialiser) {
		dst << "  Initialiser: ";
		initialiser->Debug(dst, indent);
	} else {
		dst << "  Initialiser: null" << std::endl;
	}
	dst << std::endl;
}

void Declaration::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Variable id=\"" << identifier << "\" />" << std::endl;
}
