#include "MemberAccess.hpp"

#include <algorithm>

MemberAccess::MemberAccess(Expression* base, std::string member, bool dereference) : Expression(), base(base), member(member), dereference(dereference) {}

void MemberAccess::Debug(std::ostream& dst, int indent) const {
	base->Debug(dst, indent);
	dst << (dereference ? "->" : ".");
	dst << member;
}

Type MemberAccess::GetType(VariableMap const& bindings) const {
	// check if the base type is indeed a struct
	if(!base->GetType(bindings).is_struct()) {
		throw compile_error((std::string)"member reference base type '" + base->GetType(bindings).name() + "' is not a struct or union", sourceFile, sourceLine);
	}

	// check if the struct exists
	std::string name = base->GetType(bindings).struct_name();
	if(!structures().count(name)) {
		throw compile_error((std::string)"struct or union '" + name + "' does not exist", sourceFile, sourceLine);
	}

	// check if the member exists
	StructureType s = structures().at(name);
	if (!s.member_exists(member)) {
		s.Debug(std::cerr);
		throw compile_error((std::string)"struct or union '" + name + "' does not have a member named '" + member + "'", sourceFile, sourceLine);
	}

	return s.get_member_type(member);
}

std::string MemberAccess::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string addr = MakeIR_lvalue(bindings, stack, out);
	std::string deref = unique("member");
	stack[deref] = GetType(bindings);
	out.push_back(new DereferenceInstruction(deref, addr));
	return deref;
}

std::string MemberAccess::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// gettype already performs all the necessary checks. delegate! :)
	GetType(bindings);
	std::string name = base->GetType(bindings).struct_name();
	StructureType s = structures().at(name);

	// get address of structure
	std::string b = base->MakeIR(bindings, stack, out);
	std::string addr = unique("struct_addr");
	stack[addr] = base->GetType(bindings).addressof();
	out.push_back(new AddressOfInstruction(addr, b));
	// cast the address to a void pointer (for unit pointer arithmetic)
	std::string m_addr = unique("offset_addr");
	stack[m_addr] = Type("void", 1);
	out.push_back(new CastInstruction(m_addr, addr, Type("void", 1)));
	// add the member's byte offset
	unsigned offset = s.get_member_offset(member);
	out.push_back(new MemberAccessInstruction(m_addr, m_addr, offset));
	// cast the address into a pointer of the type of the member
	std::string cast_addr = unique("member_addr");
	stack[cast_addr] = GetType(bindings).addressof();
	out.push_back(new CastInstruction(cast_addr, m_addr, GetType(bindings).addressof()));

	return cast_addr;
}
