#ifndef AST_MEMBER_ACCESS_H
#define AST_MEMBER_ACCESS_H

#include <iostream>
#include <string>

#include "../Expression.hpp"

class MemberAccess : public Expression {
public:
	Expression* base;
	std::string member;
	bool dereference;

	MemberAccess(Expression* base, std::string member, bool dereference);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;
};

#endif
