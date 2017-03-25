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
			set_specifiers(aliased.specifiers);
			return;
		}
	}
	specifiers = s;

	// turn the string into a machine-friendly version
	if(specifiers.size() == 1) {
		std::string s = specifiers[0];
		if(s == "void") {
			builtin_type = Void; return;
		} else if(s == "char") {
			builtin_type = SignedChar; return;
		} else if(s == "short") {
			builtin_type = SignedShort; return;
		} else if(s == "int") {
			builtin_type = SignedInt; return;
		} else if(s == "long") {
			builtin_type = SignedLong; return;
		} else if(s == "float") {
			builtin_type = SingleFloat; return;
		} else if(s == "double") {
			builtin_type = DoubleFloat; return;
		} else if(s.substr(0, 7) == "struct ") {
			builtin_type = Struct; return;
		} else if (s.substr(0, 6) == "union ") {
			builtin_type = Struct; return;
		} else if (s.substr(0, 5) == "enum ") {
			builtin_type = Enum; return;
		}
	} else if(specifiers.size() == 2) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		if(first == "unsigned" || first == "signed") {
			if(second == "char") {
				builtin_type = first == "unsigned" ? UnsignedChar : SignedChar; return;
			} else if(second == "short") {
				builtin_type = first == "unsigned" ? UnsignedShort : SignedShort; return;
			} else if(second == "int") {
				builtin_type = first == "unsigned" ? UnsignedInt : SignedInt; return;
			} else if(second == "long") {
				builtin_type = first == "unsigned" ? UnsignedLong : SignedLong; return;
			}
		} else if(first == "long") {
			if(second == "int") {
				builtin_type = SignedLong; return;
			} else if(second == "double") {
				builtin_type = DoubleFloat; return;
			}
		}
	} else if(specifiers.size() == 3) {
		std::string first = specifiers.at(0);
		std::string second = specifiers.at(1);
		std::string third = specifiers.at(2);
		if(first == "unsigned" && second == "long" && third == "int") {
			builtin_type = UnsignedLong; return;
		} else if(first == "signed" && second == "long" && third == "int") {
			builtin_type = SignedLong; return;
		}
	}

	std::string msg;
	msg = "invalid type: ";
	msg += name();
	throw compile_error(msg);
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
	return Type(specifiers, pointer_depth + 1);
}

Type Type::dereference() const {
	if(!is_pointer()) {
		std::string msg;
		msg = "cannot dereference type ";
		msg += name();
		throw compile_error(msg);
	}
	return Type(specifiers, pointer_depth - 1);
}

bool Type::is_pointer() const {
	return pointer_depth > 0;
}

bool Type::is_integer() const {
	if(is_pointer()) return false;

	switch (builtin_type) {
		case SignedChar:
		case UnsignedChar:
		case SignedShort:
		case UnsignedShort:
		case SignedInt:
		case UnsignedInt:
		case SignedLong:
		case UnsignedLong:
		case Enum:
			return true;
		default:
			return false;
	}
}

bool Type::is_float() const {
	if(is_pointer()) return false;
	return builtin_type == SingleFloat || builtin_type == DoubleFloat;
}

bool Type::is_struct() const {
	if(is_pointer()) return false;
	return builtin_type == Struct;
}

bool Type::is_enum() const {
	if(is_pointer()) return false;
	return builtin_type == Enum;
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

	switch (builtin_type) {
		case Void:
			return 0;
		case SignedChar:
		case UnsignedChar:
			return 1;
		case SignedShort:
		case UnsignedShort:
			return 2;
		case SignedInt:
		case UnsignedInt:
		case SignedLong:
		case UnsignedLong:
			return 4;
		case SingleFloat:
			return 4;
		case DoubleFloat:
			return 8;
		case Struct:
			if(specifiers.at(0).substr(0, 7) == "struct ") {
				return struct_total_size(specifiers.at(0).substr(7));
			} else {
				return struct_total_size(specifiers.at(0).substr(6));
			}
		case Enum:
			return 4;
	}
}

bool Type::equals(Type t) const {
	if(builtin_type != t.builtin_type) {
		return false;
	}

	if(builtin_type == Struct) {
		if(struct_name() != t.struct_name()) return false;
	} else if(builtin_type == Enum) {
		if(specifiers.at(0) != t.specifiers.at(0)) return false;
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

#include <iostream>

void align_address(unsigned& address, unsigned alignment, unsigned max_alignment) {
	if(alignment > max_alignment) {
		alignment = max_alignment;
	}

	//std::cerr << "asked to align " << address << " by " << alignment << '\n';

	int extra_bytes = address % alignment;

	if(extra_bytes) {
		//std::cerr << "aligning " << address << " by " << alignment << " to " << (address + alignment - extra_bytes) << '\n';
		address += alignment - extra_bytes;
	}
}
