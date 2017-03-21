#include "Type.hpp"
#include "../CompileError.hpp"

/* begin variablemap section */
void typedefs_define(std::string alias, Type type);
bool typedefs_exists(std::string alias);
Type typedefs_get(std::string alias);
/* end variablemap section */

Type::Type() : pointer_depth(0) {}

Type::Type(std::vector<std::string> specifiers, int pointer_depth) : pointer_depth(pointer_depth) {
	set_specifiers(specifiers);
}

Type::Type(std::string specifier, int pointer_depth) : pointer_depth(pointer_depth) {
	std::vector<std::string> spec_vector;
	spec_vector.push_back(specifier);
	set_specifiers(spec_vector);
}

void Type::set_specifiers(std::vector<std::string> s) {
	if(s.size() == 1) {
		std::string first = s.at(0);
		if(typedefs_exists(first)) {
			Type aliased = typedefs_get(first);
			pointer_depth += aliased.pointer_depth;
			specifiers = aliased.specifiers;
			return;
		}
	}
	specifiers = s;
	bytes(); // check if type string is valid
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

bool Type::is_integer() const {
	if(is_pointer()) return false;

	std::string last = specifiers.at(specifiers.size() - 1);
	if(last == "char" || last == "short" || last == "long" || last == "int") {
		return true;
	}

	if(is_enum()) return true;

	return false;
}

bool Type::is_float() const {
	if(is_pointer()) return false;

	std::string last = specifiers.at(specifiers.size() - 1);
	if(last == "float" || last == "double") {
		return true;
	}

	return false;
}

bool Type::is_struct() const {
	if(is_pointer()) return false;

	if(specifiers.at(0).substr(0, 7) == "struct " || specifiers.at(0).substr(0, 6) == "union ") {
		return true;
	}

	return false;
}

bool Type::is_enum() const {
	if(is_pointer()) return false;
	if(specifiers.at(0).substr(0, 5) == "enum ") {
		return true;
	}
	return false;
}

std::string Type::struct_name() const {
	std::string s = specifiers.at(0);
	if(s.substr(0, 7) == "struct ") {
		return s.substr(7);
	} else if (s.substr(0, 6) == "union ") {
		return s.substr(6);
	} else {
		return "";
	}
}

unsigned struct_total_size(std::string name);

unsigned Type::bytes() const {
	/*  TYPE		SIZE (bytes)
		char		1
		short		2
		int			4
		long		4
		float		4
		double		8
		long double	8
	*/

	if(is_pointer()) return 4;

	if(specifiers.size() == 1) {
		std::string s = specifiers[0];
		if(s == "void") {
			return 0;
		} else if(s == "char") {
			return 1;
		} else if(s == "short") {
			return 2;
		} else if(s == "int") {
			return 4;
		} else if(s == "long") {
			return 4;
		} else if(s == "float") {
			return 4;
		} else if(s == "double") {
			return 8;
		} else if(s.substr(0, 7) == "struct ") {
			return struct_total_size(s.substr(7));
		} else if (s.substr(0, 6) == "union ") {
			return struct_total_size(s.substr(6));
		} else if (s.substr(0, 5) == "enum ") {
			return 4;
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
				return 4;
			}
		} else if(first == "long") {
			if(second == "int") {
				return 4;
			} else if(second == "double") {
				return 8;
			}
		}
	} else if(specifiers.size() == 3) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		std::string third = specifiers.at(2);
		if(first == "unsigned" && second == "long" && third == "int") {
			return 4;
		} else if(first == "signed" && second == "long" && third == "int") {
			return 4;
		}
	}

	std::string msg;
	msg = "invalid type: ";
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
