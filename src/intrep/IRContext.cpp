#include "IRContext.hpp"
#include "../CompileError.hpp"

#include <sstream>

IRContext::IRContext(VariableMap const& globals,
	FunctionStack const& stack,
	std::map<std::string, unsigned> const& stack_offsets,
	std::string func_name,
	Type return_type,
	unsigned return_struct_offset)
: globals(globals),
stack(stack),
stack_offsets(stack_offsets),
func_name(func_name),
return_type(return_type),
return_struct_offset(return_struct_offset) {}

bool IRContext::is_global(std::string name) const {
	return (globals.count(name));
}

unsigned IRContext::get_stack_offset(std::string name) const {
	if(stack_offsets.count(name)) {
		return stack_offsets.at(name);
	} else {
		throw compile_error((std::string)"IR: variable " + name + " not found in stack mapping");
	}
}

Type IRContext::get_type(std::string name) const {
	if(stack.count(name)) {
		return stack.at(name);
	} else if(globals.count(name)) {
		return globals.at(name).type;
	} else {
		throw compile_error((std::string)"IR: variable " + name + " not found in stack or globals");
	}
}

std::string IRContext::get_variable_address(std::string name) const {
	if(is_global(name)) {
		return name;
	} else {
		std::stringstream ss;
		ss << get_stack_offset(name) << "($fp)";
		return ss.str();
	}
}

std::string IRContext::get_return_label() const {
	return (std::string)"fnc_" + func_name + "_return";
}

Type IRContext::get_return_type() const {
	return return_type;
}

unsigned IRContext::get_return_struct_offset() const {
	return return_struct_offset;
}

/* ******************************************* */

void IRContext::load_variable(std::ostream &out, std::string source, unsigned reg_number) const {
	Type src_type = get_type(source);
	if(src_type.bytes() > 4) {
		throw compile_error((std::string)"cannot load variable '" + source + "' of type '" + src_type.name() + "' into a register");
	}
	// how large is it?
	std::string load_instr;
	switch (src_type.bytes()) {
	case 1:
		load_instr = "lb";
		break;
	case 2:
		load_instr = "lh";
		break;
	default:
		load_instr = "lw";
		break;
	}
	// is it a labeled variable or local?
	if(is_global(source)) {
		out << "    lui     $2, %hi(" << source << ")\n";
		out << "    " << load_instr << "      $" << reg_number << ", %lo(" << source << ")($2)\n";
	} else {
		out << "    " << load_instr << "      $" << reg_number << ", " << get_stack_offset(source) << "($fp)\n";
	}
}

void IRContext::store_variable(std::ostream &out, std::string destination, unsigned reg_number) const {
	Type dst_type = get_type(destination);
	if(dst_type.bytes() > 4) {
		throw compile_error((std::string)"cannot store a register into variable '" + destination + "' of type '" + dst_type.name() + "'");
	}
	// how large is it?
	std::string store_instr;
	switch (dst_type.bytes()) {
	case 1:
		store_instr = "sb";
		break;
	case 2:
		store_instr = "sh";
		break;
	default:
		store_instr = "sw";
		break;
	}
	// is it a labeled variable or local?
	if(is_global(destination)) {
		out << "    lui     $2, %hi(" << destination << ")\n";
		out << "    " << store_instr << "      $" << reg_number << ", %lo(" << destination << ")($2)\n";
	} else {
		out << "    " << store_instr << "      $" << reg_number << ", " << get_stack_offset(destination) << "($fp)\n";
	}
}

void IRContext::convert(std::ostream &out, unsigned s_reg, Type s_type, unsigned d_reg, Type d_type) const {
	if(s_type.equals(d_type)) {
		out << "    move    $" << d_reg << ", $" << s_reg << "\n";
		return;
	}

	throw compile_error((std::string)"type mismatch: '" + s_type.name() + "' is not compatible with '" + d_type.name() + "'");
}

void IRContext::copy(std::ostream &out, std::string source, std::string destination, unsigned total_bytes) const {

	// load addresses of any variable in global
	if(source != "") {
		if(is_global(source)) {
			out << "    li      $2, " << source << "\n";
		} else {
			out << "    addiu   $2, $fp, " << get_stack_offset(source) << "\n";
		}
	}
	if(destination != "") {
		if(is_global(destination)) {
			out << "    li      $3, " << destination << "\n";
		} else {
			out << "    addiu   $3, $fp, " << get_stack_offset(destination) << "\n";
		}
	}

	// copy byte by byte

	unsigned words = total_bytes / 4;
	for(unsigned i = 0; i < words; i++) {
		out << "    lw      $8, " << (i * 4) << "($2)\n";
		out << "    sw      $8, " << (i * 4) << "($3)\n";
	}

	unsigned leftover_bytes = total_bytes % 4;
	for(unsigned i = 0; i < leftover_bytes; i++) {
		out << "    lb      $8, " << (words * 4 + i) << "($2)\n";
		out << "    sb      $8, " << (words * 4 + i) << "($3)\n";
	}
}
