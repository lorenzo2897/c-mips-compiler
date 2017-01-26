#include "Variable.hpp"

Variable::Variable(std::string id) {
	identifier = id;
}

void Variable::Debug(std::ostream& dst, int indent) const {
	dst << identifier;
}
