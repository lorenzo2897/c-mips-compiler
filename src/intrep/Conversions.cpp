#include "Conversions.hpp"

#include "../CompileError.hpp"

Type arithmetic_conversion(Type l, Type r) {
	if(l.is_struct() || r.is_struct()) {
		throw compile_error("cannot perform arithmetic operations on a struct");
	}

	if(l.is_float() || r.is_float()) {
		if(l.bytes() > r.bytes()) {
			return l;
		} else {
			return r;
		}
	}
	return l;
}


void convert_type(std::ostream &out, unsigned s_reg, Type s_type, unsigned d_reg, Type d_type) {
	if(s_type.equals(d_type)) {
		out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		if(s_type.bytes() == 8)
			out << "    move    $" << (d_reg+1) << ", $" << (s_reg+1) << "\n";
		return;
	}

	throw compile_error((std::string)"type mismatch: '" + s_type.name() + "' is not compatible with '" + d_type.name() + "'");
}
