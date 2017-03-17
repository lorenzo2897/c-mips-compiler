#include "ArrayAccess.hpp"

ArrayAccess::ArrayAccess(Expression* base, Expression* index) : Expression(), array_base(base), array_index(index) {}

void ArrayAccess::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	array_base->Debug(dst, indent);
	dst << ") [";
	array_index->Debug(dst, indent);
	dst << "]";
}

Type ArrayAccess::GetType(VariableMap const& bindings) const {
	return array_base->GetType(bindings).dereference();
}

std::string ArrayAccess::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// take base address of array, add the offset, and return the value at the new address
	std::string addr = MakeIR_lvalue(bindings, stack, out);
	std::string dst = unique("element");
	stack[dst] = array_base->GetType(bindings).dereference();
	out.push_back(new DereferenceInstruction(dst, addr));
	return dst;
}

std::string ArrayAccess::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// take base address of array, add the offset, and return new address
	if(!array_base->GetType(bindings).is_pointer()) {
		throw compile_error("trying to access array element of a non-pointer", sourceFile, sourceLine);
	}
	if(array_index->GetType(bindings).is_pointer()) {
		throw compile_error("cannot use pointer as array index", sourceFile, sourceLine);
	}
	std::string base = array_base->MakeIR(bindings, stack, out);
	std::string offs = array_index->MakeIR(bindings, stack, out);
	std::string dst = unique("addr");
	stack[dst] = array_base->GetType(bindings);
	out.push_back(new AddInstruction(dst, base, offs));
	return dst;
}
