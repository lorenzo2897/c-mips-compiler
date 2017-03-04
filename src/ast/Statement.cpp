#include "Statement.hpp"

Statement::Statement() : sourceLine(currentSourceLine), sourceFile(currentSourceFile) {
}

void Statement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Statement";
}

void Statement::MakeIR(VariableMap const& bindings,std::map<std::string, Type>& stack, std::vector<Instruction>& out) const {
	throw compile_error("assembly generation not implemented for this statement", sourceFile, sourceLine);
}
