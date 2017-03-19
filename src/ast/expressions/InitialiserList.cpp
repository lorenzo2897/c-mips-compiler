#include "InitialiserList.hpp"

void InitialiserList::add(Expression* e) {
	list.push_back(e);
}

void InitialiserList::Debug(std::ostream& dst, int indent) const {
	dst << "{";
	for(std::vector<Expression*>::const_iterator itr = list.begin(); itr != list.end(); ++itr) {
		if(itr != list.begin()) {
			dst << ", ";
		}
		(*itr)->Debug(dst, indent);
	}
	dst << "}";
}

Type InitialiserList::GetType(VariableMap const& bindings) const {
	return Type("int", 1);
}

std::string InitialiserList::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// this happens in the context of scalar variables with an initialiser list.
	// for some reason gcc allows this.
	//throw compile_error("cannot use an initialiser list on a scalar variable", sourceFile, sourceLine);
	return list.at(0)->MakeIR(bindings, stack, out);
}

std::string InitialiserList::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use an initialiser list within an l-value. how did this even parse?", sourceFile, sourceLine);
}
