#include "Statement.hpp"

#include <typeinfo>

Statement::Statement() : sourceLine(currentSourceLine), sourceFile(currentSourceFile) {
}

void Statement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Statement";
}

void Statement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error((std::string)"assembly generation not implemented for " + typeid(*this).name(), sourceFile, sourceLine);
}
