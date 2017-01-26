#include "Statement.hpp"

Statement::Statement() : sourceLine(currentSourceLine), sourceFile(currentSourceFile) {
}

void Statement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Statement";
}
