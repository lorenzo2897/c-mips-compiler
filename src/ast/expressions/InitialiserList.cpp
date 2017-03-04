#include "InitialiserList.hpp"

void InitialiserList::add(Expression* e) {
	list.push_back(e);
}

void InitialiserList::Debug(std::ostream& dst, int indent) const {
	dst << "{";
	for(std::vector<Expression*>::const_iterator itr = list.begin(); itr != list.end(); ++itr) {
		if(itr != list.begin()) {
			dst << ", ";
		}
		(*itr)->Debug(dst, indent);
	}
	dst << "}";
}

Type InitialiserList::GetType(VariableMap const& bindings) const {
	return Type("int", 1);
}
