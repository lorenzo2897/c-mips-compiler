#include "Scope.hpp"

void Scope::declare(Declaration* d) {
	declarations.push_back(d);
}

void Scope::add_statement(Statement *s) {
	statements.push_back(s);
}

void Scope::merge_declarations(Scope *scope) {
	declarations.insert(declarations.end(), scope->declarations.begin(), scope->declarations.end());
}

void Scope::merge_statements(Scope *scope) {
	statements.insert(statements.end(), scope->statements.begin(), scope->statements.end());
}

Scope::Scope() {}

void Scope::Debug(std::ostream &dst, int indent) const {
	dst << " (scope)";
}
