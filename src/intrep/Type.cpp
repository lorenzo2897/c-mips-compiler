#include "Type.hpp"
#include "../CompileError.hpp"

Type::Type() : pointer_depth(0) {}

Type::Type(std::vector<std::string> specifiers, int pointer_depth) : specifiers(specifiers), pointer_depth(pointer_depth) {

}

Type::Type(std::string specifier, int pointer_depth) : pointer_depth(pointer_depth) {
	specifiers.push_back(specifier);
}

std::string Type::name() const {
	std::string n = "";
	for(unsigned i = 0; i < specifiers.size(); i++) {
		if(i > 0)
			n += " ";
		n += specifiers[i];
	}
	for(int i = 0; i < pointer_depth; i++) {
		n += " *";
	}
	return n;
}

Type Type::addressof() const {
	Type t;
	t.pointer_depth = pointer_depth + 1;
	t.specifiers = specifiers;
	return t;
}

Type Type::dereference() const {
	if(!is_pointer()) {
		std::string msg;
		msg = "cannot dereference type ";
		msg += name();
		throw compile_error(msg);
	}
	Type t;
	t.pointer_depth = pointer_depth - 1;
	t.specifiers = specifiers;
	return t;
}

bool Type::is_pointer() const {
	return pointer_depth > 0;
}

unsigned Type::bytes() const {
	/*  TYPE		SIZE (bytes)
		char		1
		short		2
		int			4
		long		8
		long long	8
		float		4
		double		8
		long double	8
	*/

	if(is_pointer()) return 4;

	if(specifiers.size() == 1) {
		std::string s = specifiers[0];
		if(s == "void") {
			return 1;
		} else if(s == "char") {
			return 1;
		} else if(s == "short") {
			return 2;
		} else if(s == "int") {
			return 4;
		} else if(s == "long") {
			return 8;
		} else if(s == "float") {
			return 4;
		} else if(s == "double") {
			return 8;
		}
	} else if(specifiers.size() == 2) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		if(first == "unsigned" || first == "signed") {
			if(second == "char") {
				return 1;
			} else if(second == "short") {
				return 2;
			} else if(second == "int") {
				return 4;
			} else if(second == "long") {
				return 8;
			}
		} else if(first == "long") {
			if(second == "long") {
				return 8;
			} else if(second == "int") {
				return 8;
			} else if(second == "double") {
				return 8;
			}
		}
	} else if(specifiers.size() == 3) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		std::string third = specifiers.at(2);
		if(first == "long" && second == "long" && third == "int") {
			return 8;
		} else if(first == "unsigned" && second == "long" && third == "int") {
			return 8;
		} else if(first == "unsigned" && second == "long" && third == "long") {
			return 8;
		} else if(first == "signed" && second == "long" && third == "int") {
			return 8;
		} else if(first == "signed" && second == "long" && third == "long") {
			return 8;
		}
	} else if(specifiers.size() == 4) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		std::string third = specifiers.at(2);
		std::string fourth = specifiers.at(3);
		if(first == "unsigned" && second == "long" && third == "long" && fourth == "int") {
			return 8;
		} else if(first == "signed" && second == "long" && third == "long" && fourth == "int") {
			return 8;
		}
	}

	std::string msg;
	msg = "invalid type ";
	msg += name();
	throw compile_error(msg);
	return 0;
}

bool Type::equals(Type t) const {
	if(specifiers.size() != t.specifiers.size()) {
		return false;
	}

	for(unsigned i = 0; i < specifiers.size(); i++) {
		if(specifiers[i] != t.specifiers[i]) {
			return false;
		}
	}

	if(pointer_depth != t.pointer_depth) {
		return false;
	}

	return true;
}

bool Type::is_compatible(Type t) const {
	// both are pointers
	if(is_pointer() && t.is_pointer()) {
		return pointer_depth == t.pointer_depth;
	// only one is pointer
	} else if(is_pointer() || t.is_pointer()) {
		return false;
	}
	// neither are pointers
	return bytes() == t.bytes();
}
