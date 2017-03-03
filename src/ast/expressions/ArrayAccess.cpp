#include "ArrayAccess.hpp"

ArrayAccess::ArrayAccess(Expression* base, Expression* index) : array_base(base), array_index(index) {}

void ArrayAccess::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	array_base->Debug(dst, indent);
	dst << ") [";
	array_index->Debug(dst, indent);
	dst << "]";
}

Type ArrayAccess::GetType(VariableMap& bindings) const {
	return array_base->GetType(bindings).dereference();
}
