#include "Declaration.hpp"

Declaration::Declaration() : initialiser(NULL), array_elements(0) {}

bool Declaration::is_array() const {
	return array_elements > 0;
}

void Declaration::MakeIR_initialisers(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(initialiser) {
		std::string src = initialiser->MakeIR(bindings, stack, out);
		std::string dst = unique((std::string)"addr_" + identifier + "_");
		stack[dst] = bindings.at(identifier).type.addressof();
		out.push_back(new AddressOfInstruction(dst, bindings.at(identifier).alias));
		out.push_back(new AssignInstruction(dst, src));
	}
}

void Declaration::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Declaration : " << identifier;

	dst << std::endl << spaces(indent) << "  Specifiers: ";
	dst << var_type.name();
	if(is_array()) {
		dst << std::endl << spaces(indent) << "  Array elements: ";
		dst << array_elements;
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

void Declaration::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Variable id=\"" << identifier << "\" />" << std::endl;
}
