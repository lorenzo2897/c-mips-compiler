#include "Declaration.hpp"
#include "expressions/InitialiserList.hpp"
#include "Value.hpp"

Declaration::Declaration() : initialiser(NULL), array_elements(0) {}

bool Declaration::is_array() const {
	return array_elements > 0;
}

void Declaration::MakeIR_initialisers(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(initialiser) {
		if(is_array()) {
			// must be initialiser list or string literal
			InitialiserList* il = dynamic_cast<InitialiserList*>(initialiser);
			if(il) {
				// loop through items and assign them to the array
				std::string looper = unique("init");
				stack[looper] = bindings.at(identifier).type;
				out.push_back(new MoveInstruction(looper, bindings.at(identifier).alias));
				for(unsigned i = 0; i < il->list.size(); ++i) {
					// evaluate the expression
					std::string src = il->list.at(i)->MakeIR(bindings, stack, out);
					// assign it
					out.push_back(new AssignInstruction(looper, src));
					// increment looper
					out.push_back(new IncrementInstruction(looper, looper, false));
				}
			} else {
				Value* v = dynamic_cast<Value*>(initialiser);
				if(v) {
					if(v->is_string_literal()) {
						if(var_type.dereference().is_integer() && var_type.dereference().bytes() == 1) {
							// loop through characters and assign them to the array
							std::string looper = unique("init");
							stack[looper] = bindings.at(identifier).type;
							out.push_back(new MoveInstruction(looper, bindings.at(identifier).alias));
							for(unsigned i = 0; i < v->get_string_literal().size(); ++i) {
								// evaluate the character
								std::string src = unique("strchar");
								stack[src] = Type("char", 0);
								out.push_back(new ConstantInstruction(src, Type("char", 0), v->get_string_literal().at(i)));
								// assign it
								out.push_back(new AssignInstruction(looper, src));
								// increment looper
								out.push_back(new IncrementInstruction(looper, looper, false));
							}
						} else {
							throw compile_error("array initialiser must be an initialiser list", initialiser->sourceFile, initialiser->sourceLine);
						}
					} else {
						throw compile_error("array initialiser must be an initialiser list or string literal", initialiser->sourceFile, initialiser->sourceLine);
					}
				} else {
					throw compile_error("array initialiser must be an initialiser list or string literal", initialiser->sourceFile, initialiser->sourceLine);
				}
			}
		} else {
			std::string src = initialiser->MakeIR(bindings, stack, out);
			std::string dst = unique((std::string)"addr_" + identifier + "_");
			stack[dst] = bindings.at(identifier).type.addressof();
			out.push_back(new AddressOfInstruction(dst, bindings.at(identifier).alias));
			out.push_back(new AssignInstruction(dst, src));
		}
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
