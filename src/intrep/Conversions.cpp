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
	if(!l.is_signed() || !r.is_signed()) {
		r = Type("unsigned", 0);
	}

	return Type("int", 0);
}


void convert_type(std::ostream &out, unsigned s_reg, Type s_type, unsigned d_reg, Type d_type) {
	// convert enums to ints
	if(s_type.is_enum()) {
		s_type = Type("int", 0);
	}
	if(d_type.is_enum()) {
		d_type = Type("int", 0);
	}

	// cannot convert structs
	if(s_type.is_struct() || d_type.is_struct()) {
		throw compile_error("cannot convert structs to anything. also why is a struct even in a register at this point?");
	}

	// same type? perfect, no conversion necessary
	if(s_type.equals(d_type)) {
		out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		if(s_type.bytes() == 8)
			out << "    move    $" << (d_reg+1) << ", $" << (s_reg+1) << "\n";
		return;
	}

	// convert two pointers
	if(s_type.is_pointer() && d_type.is_pointer()) {
		out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		return;
	}

	// conversions involving floats
	if(d_type.is_float()) {
		if(s_type.is_integer() && d_type.bytes() == 4) {
			// INT TO FLOAT
			out << "    mtc1    $" << s_reg << ", $f0\n";
			out << "    cvt.s.w $f0, $f0\n";
			out << "    swc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    lw      $" << d_reg << ", 0($fp)\n";
			out << "    nop\n";
			return;
		} else if(s_type.is_integer() && d_type.bytes() == 8) {
			// INT TO DOUBLE
			out << "    mtc1    $" << s_reg << ", $f0\n";
			out << "    cvt.d.w $f0, $f0\n";
			out << "    sdc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    lw      $" << d_reg << ", 0($fp)\n";
			out << "    lw      $" << (d_reg+1) << ", 4($fp)\n";
			out << "    nop\n";
			return;
		} else if(s_type.is_float() && s_type.bytes() == 4) {
			// FLOAT TO DOUBLE
			out << "    sw      $" << s_reg << ", 0($fp)\n";
			out << "    nop\n";
			out << "    lwc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    cvt.d.s $f0, $f0\n";
			out << "    sdc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    lw      $" << d_reg << ", 0($fp)\n";
			out << "    lw      $" << (d_reg+1) << ", 4($fp)\n";
			out << "    nop\n";
			return;
		} else if(s_type.is_float() && s_type.bytes() == 8) {
			// DOUBLE TO FLOAT
			out << "    sw      $" << s_reg << ", 0($fp)\n";
			out << "    sw      $" << (s_reg+1) << ", 4($fp)\n";
			out << "    nop\n";
			out << "    ldc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    cvt.s.d $f0, $f0\n";
			out << "    swc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    lw      $" << d_reg << ", 0($fp)\n";
			out << "    nop\n";
			return;
		}
	}
	if(s_type.is_float() && d_type.is_integer()) {
		if(s_type.bytes() == 4) {
			// FLOAT TO INT
			out << "    sw      $" << s_reg << ", 0($fp)\n";
			out << "    nop\n";
			out << "    lwc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    trunc.w.s $f0, $f0\n";
			out << "    mfc1    $" << d_reg << ", $f0\n";
			return;
		} else if(s_type.bytes() == 8) {
			// DOUBLE TO INT
			out << "    sw      $" << s_reg << ", 0($fp)\n";
			out << "    sw      $" << (s_reg+1) << ", 4($fp)\n";
			out << "    nop\n";
			out << "    ldc1    $f0, 0($fp)\n";
			out << "    nop\n";
			out << "    trunc.w.d $f0, $f0\n";
			out << "    mfc1    $" << d_reg << ", $f0\n";
			return;
		}
	}

	// convert between integral types
	if(s_type.is_integer() && d_type.is_integer()) {
		if(d_type.builtin_type == Type::SignedChar) {
			out << "    sb      $" << s_reg << ", 4($fp)\n";
			out << "    nop\n";
			out << "    lb      $" << d_reg << ", 4($fp)\n";
		} else if(d_type.builtin_type == Type::UnsignedChar) {
			out << "    sb      $" << s_reg << ", 4($fp)\n";
			out << "    nop\n";
			out << "    lbu     $" << d_reg << ", 4($fp)\n";
		} else if(d_type.builtin_type == Type::SignedShort) {
			out << "    sh      $" << s_reg << ", 4($fp)\n";
			out << "    nop\n";
			out << "    lh      $" << d_reg << ", 4($fp)\n";
		} else if(d_type.builtin_type == Type::UnsignedShort) {
			out << "    sh      $" << s_reg << ", 4($fp)\n";
			out << "    nop\n";
			out << "    lhu     $" << d_reg << ", 4($fp)\n";
		} else if(d_type.builtin_type == Type::SignedInt || d_type.builtin_type == Type::SignedLong || d_type.builtin_type == Type::Enum) {
			out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		} else if(d_type.builtin_type == Type::UnsignedInt || d_type.builtin_type == Type::UnsignedLong) {
			out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		}
		return;
	}

	// no conversion is possible
	throw compile_error((std::string)"type mismatch: '" + s_type.name() + "' cannot be converted to '" + d_type.name() + "'");
}
