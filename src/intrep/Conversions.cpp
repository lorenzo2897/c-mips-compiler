#include "Conversions.hpp"

#include "../CompileError.hpp"

Type arithmetic_conversion(Type l, Type r) {
	/* Section 6.2.1 of the C89 standard */

	if(l.is_struct() || r.is_struct()) {
		throw compile_error("cannot perform arithmetic operations on a struct");
	}

	// pointer arithmetic
	if(l.is_pointer()) {
		if(r.is_integer() || r.equals(l)) {
			return l;
		} else {
			throw compile_error((std::string)"cannot perform pointer arithmetic with type '" + r.name() + "'");
		}
	}

	// floating point wins
	if(l.is_float() || r.is_float()) {
		if(l.bytes() > r.bytes()) {
			return l;
		} else {
			return r;
		}
	}

	// integral promotion is performed on both operands
	if(l.bytes() < 4) {
		l = Type("int", 0);
	}
	if(r.bytes() < 4) {
		r = Type("int", 0);
	}

	// deal with sign
	if(l.is_signed() || r.is_signed()) {
		r = Type("unsigned", 0);
	}

	return Type("int", 0);;
}


void convert_type(std::ostream &out, unsigned s_reg, Type s_type, unsigned d_reg, Type d_type) {
	if(s_type.is_enum()) {
		s_type = Type("int", 0);
	}
	if(d_type.is_enum()) {
		d_type = Type("int", 0);
	}
	if(s_type.is_struct() || d_type.is_struct()) {
		throw compile_error("cannot convert structs to anything. also why is a struct even in a register at this point?");
	}

	if(s_type.equals(d_type)) {
		out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		if(s_type.bytes() == 8)
			out << "    move    $" << (d_reg+1) << ", $" << (s_reg+1) << "\n";
		return;
	}

	throw compile_error((std::string)"type mismatch: '" + s_type.name() + "' cannot be converted to '" + d_type.name() + "'");
}
