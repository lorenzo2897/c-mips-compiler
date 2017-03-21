#include "MemberAccess.hpp"

#include <algorithm>

MemberAccess::MemberAccess(Expression* base, std::string member, bool dereference) : Expression(), base(base), member(member), dereference(dereference) {}

void MemberAccess::Debug(std::ostream& dst, int indent) const {
	base->Debug(dst, indent);
	dst << (dereference ? "->" : ".");
	dst << member;
}

Type MemberAccess::GetType(VariableMap const& bindings) const {
	// dereference if need be
	Type base_type = base->GetType(bindings);
	if(dereference) {
		if(base_type.is_pointer()) {
			base_type = base_type.dereference();
		} else {
			throw compile_error((std::string)"base type '" + base->GetType(bindings).name() + "' is not a pointer; did you mean to use '.' instead?", sourceFile, sourceLine);
		}
	}

	// check if the base type is indeed a struct
	if(!base_type.is_struct()) {
		if(base_type.is_pointer()) {
			if(base_type.dereference().is_struct()) {
				throw compile_error((std::string)"base type '" + base->GetType(bindings).name() + "' is a pointer; did you mean to use '->' instead?", sourceFile, sourceLine);
			}
		}
		throw compile_error((std::string)"member reference base type '" + base->GetType(bindings).name() + "' is not a struct or union", sourceFile, sourceLine);
	}

	// check if the struct exists
	std::string name = base_type.struct_name();
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
	std::string name;
	if(dereference) {
		name = base->GetType(bindings).dereference().struct_name();
	} else {
		name = base->GetType(bindings).struct_name();
	}
	StructureType s = structures().at(name);

	// get address of structure
	std::string b = base->MakeIR(bindings, stack, out);
	std::string addr;
	if(dereference) {
		addr = b;
	} else {
		addr = unique("struct_addr");
		stack[addr] = base->GetType(bindings).addressof();
		out.push_back(new AddressOfInstruction(addr, b));
	}
	// add the member's byte offset
	std::string m_addr = unique("member_addr");
	stack[m_addr] = GetType(bindings).addressof();
	unsigned offset = s.get_member_offset(member);
	out.push_back(new MemberAccessInstruction(m_addr, addr, offset));

	return m_addr;
}
