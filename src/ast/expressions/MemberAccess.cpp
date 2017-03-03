#include "MemberAccess.hpp"

MemberAccess::MemberAccess(Expression* base, std::string member, bool dereference) : base(base), member(member), dereference(dereference) {}

void MemberAccess::Debug(std::ostream& dst, int indent) const {
	base->Debug(dst, indent);
	dst << (dereference ? "->" : ".");
	dst << member;
}

Type MemberAccess::GetType(VariableMap& bindings) const {
	return base->GetType(bindings);
}
