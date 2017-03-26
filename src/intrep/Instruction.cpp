#include "Instruction.hpp"
#include "Conversions.hpp"
#include "UniqueNames.hpp"

#include <iomanip>
#include <sstream>

void Instruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	out << "    undefined\n";
}

// *******************************************

LabelInstruction::LabelInstruction(std::string name) : label_name(name) {}

void LabelInstruction::Debug(std::ostream &dst) const {
	dst << "  " << label_name << ":" << std::endl;
}

void LabelInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	out << "  " << label_name << ":\n";
}

// *******************************************

GotoInstruction::GotoInstruction(std::string name) : label_name(name) {}

void GotoInstruction::Debug(std::ostream &dst) const {
	dst << "    goto " << label_name << std::endl;
}

void GotoInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	out << "    j       " << label_name << "\n";
	out << "    nop\n";
}

// *******************************************

GotoIfEqualInstruction::GotoIfEqualInstruction(std::string name, std::string variable, int32_t value) : label_name(name), variable(variable), value(value) {}

void GotoIfEqualInstruction::Debug(std::ostream &dst) const {
	dst << "    beq " << variable << ", " << value << ", " << label_name << std::endl;
}

void GotoIfEqualInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	std::string skip_label = unique("$L");
	context.load_variable(out, variable, 8);
	convert_type(out, 8, context.get_type(variable), 10, Type("int", 0));
	if(value == 0) {
		out << "    bne     $10, $0, " << skip_label << "\n";
	} else {
		out << "    li      $11, " << value << "\n";
		out << "    bne     $10, $11, " << skip_label << "\n";
	}
	out << "    nop\n";
	out << "    j       " << label_name << "\n";
	out << "    nop\n";
	out << "   " << skip_label << ":\n";
}

// *******************************************

ReturnInstruction::ReturnInstruction() : return_variable("") {}
ReturnInstruction::ReturnInstruction(std::string return_variable) : return_variable(return_variable) {}

void ReturnInstruction::Debug(std::ostream &dst) const {
	dst << "    return " << return_variable << std::endl;
}

void ReturnInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(return_variable != "") {
		if(context.get_return_type().is_struct()) {
			// make sure the structs are equal
			if(!context.get_return_type().equals(context.get_type(return_variable))) {
				throw compile_error((std::string)"type mismatch: cannot return a variable of type '" + context.get_type(return_variable).name() + "' in a function of type '" + context.get_return_type().name() + "'");
			}
			// get the base address of the struct
			out << "    lw      $3, " << context.get_return_struct_offset() << "($fp)\n";
			out << "    nop\n";
			// copy the struct into the address
			context.copy(out, return_variable, "", context.get_return_type().bytes());
		} else {
			// populate register $2 with return value
			context.load_variable(out, return_variable, 8);
			convert_type(out, 8, context.get_type(return_variable), 2, context.get_return_type());
		}
	}
	out << "    j       " << context.get_return_label() << "\n";
	out << "    nop\n";
}

// *******************************************

ConstantInstruction::ConstantInstruction(std::string destination, Type type, uint32_t dataLo, uint32_t dataHi)
: destination(destination), type(type), dataLo(dataLo), dataHi(dataHi) {}

void ConstantInstruction::Debug(std::ostream &dst) const {
	dst << "    constant " << destination
	<< " "
	<< std::hex << std::setfill('0') << std::setw(8) << dataHi
	<< " "
	<< std::hex << std::setfill('0') << std::setw(8) << dataLo
	<< std::dec << std::endl;
}

void ConstantInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(type.bytes() == 8) {
		out << "    li      $8, " << dataHi <<"\n";
		out << "    li      $9, " << dataLo <<"\n";
	} else {
		if(dataLo == 0) {
			out << "    move    $8, $0\n";
		} else {
			out << "    li      $8, " << dataLo <<"\n";
		}
	}
	context.store_variable(out, destination, 8);
}

std::string very_conservative_escape(std::string src) {
	std::stringstream ss;
	for(unsigned i = 0; i < src.size(); i++) {
		char c = src[i];
		if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ') {
			ss << c;
		} else {
			ss << "\\" << std::setfill('0') << std::setw(3) << std::oct << (int)c;
		}
	}
	return ss.str();
}

StringInstruction::StringInstruction(std::string destination, std::string data)
: destination(destination), data(data) {}

void StringInstruction::Debug(std::ostream &dst) const {
	dst << "    ascii " << destination << " " << data << std::endl;
}

void StringInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	out << "    string_data_" << destination << ":\n";
	out << "    .ascii \"" << very_conservative_escape(data) << "\\000\"\n";
	out << "    li      $8, string_data_" << destination << "\n";
	context.store_variable(out, destination, 8);
}

// *******************************************

MoveInstruction::MoveInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void MoveInstruction::Debug(std::ostream &dst) const {
	dst << "    move " << destination << ", " << source << std::endl;
}

void MoveInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(context.get_type(destination).is_struct() && context.get_type(destination).equals(context.get_type(source))) {
		// do a byte-wise copy
		context.copy(out, source, destination, context.get_type(destination).bytes());
	} else {
		// do a conversion
		context.load_variable(out, source, 8);
		convert_type(out, 8, context.get_type(source), 10, context.get_type(destination));
		context.store_variable(out, destination, 10);
	}
}

AssignInstruction::AssignInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void AssignInstruction::Debug(std::ostream &dst) const {
	dst << "    assign *" << destination << ", " << source << std::endl;
}

void AssignInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	// get the address of the destination to assign
	context.load_variable(out, destination, 3);

	if(context.get_type(destination).dereference().is_struct() && context.get_type(destination).dereference().equals(context.get_type(source))) {
		// do a byte-wise copy
		context.copy(out, source, "", context.get_type(destination).dereference().bytes());
	} else {
		// do a conversion
		context.load_variable(out, source, 8);
		convert_type(out, 8, context.get_type(source), 10, context.get_type(destination).dereference());
		switch (context.get_type(destination).dereference().bytes()) {
			case 1:
				out << "    sb      $10, 0($3)\n"; break;
			case 2:
				out << "    sh      $10, 0($3)\n"; break;
			case 4:
				out << "    sw      $10, 0($3)\n"; break;
			case 8:
				out << "    sw      $10, 9($3)\n";
				out << "    sw      $11, 4($3)\n";
				break;
		}
		out << "    nop\n";
	}
}

// *******************************************

AddressOfInstruction::AddressOfInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void AddressOfInstruction::Debug(std::ostream &dst) const {
	dst << "    addressOf " << destination << ", &" << source << std::endl;
}

void AddressOfInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(context.is_global(source)) {
		out << "    li      $8, " << source << "\n";
	} else {
		out << "    addiu   $8, $fp, " << context.get_stack_offset(source) << "\n";
	}
	context.store_variable(out, destination, 8);
}

DereferenceInstruction::DereferenceInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void DereferenceInstruction::Debug(std::ostream &dst) const {
	dst << "    dereference " << destination << ", *" << source << std::endl;
}

void DereferenceInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(context.is_global(source)) {
		out << "    li      $2, " << source << "\n";
		out << "    lw      $2, 0($2)\n";
	} else {
		out << "    lw      $2, " << context.get_stack_offset(source) << "($fp)\n";
	}
	out << "    nop\n";
	context.copy(out, "", destination, context.get_type(destination).bytes());
}

// *******************************************

LogicalInstruction::LogicalInstruction(std::string destination, std::string source1, std::string source2, char logicalType)
: destination(destination), source1(source1), source2(source2), logicalType(logicalType) {}

void LogicalInstruction::Debug(std::ostream &dst) const {
	switch (logicalType) {
		case '&':
			dst << "    logicalAnd " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '|':
			dst << "    logicalOr " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '!':
			dst << "    logicalNot " << destination << ", " << source1 << std::endl;
			break;
		default:
			throw compile_error("unsupported type of boolean operator in LogicalInstruction");
	}
}

void LogicalInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	// load and convert to ints: in $10 and $13
	context.load_variable(out, source1, 8);
	convert_type(out, 8, context.get_type(source1), 10, Type("int", 0));
	if(logicalType != '!') {
		context.load_variable(out, source2, 11);
		convert_type(out, 11, context.get_type(source2), 13, Type("int", 0));
	}
	std::string skip_label1 = unique("$L");
	std::string skip_label2 = unique("$L");
	switch (logicalType) {
		case '&':
			// if either is zero, return 0
			out << "    li      $14, 1\n";
			out << "    bne     $10, $0, " << skip_label1 << "\n";
			out << "    nop\n";
			out << "    li      $14, 0\n";
			out << "   " << skip_label1 << ":\n";
			out << "    bne     $13, $0, " << skip_label2 << "\n";
			out << "    nop\n";
			out << "    li      $14, 0\n";
			out << "   " << skip_label2 << ":\n";
			break;
		case '|':
			// if either is non-zero, return 1
			out << "    li      $14, 0\n";
			out << "    beq     $10, $0, " << skip_label1 << "\n";
			out << "    nop\n";
			out << "    li      $14, 1\n";
			out << "   " << skip_label1 << ":\n";
			out << "    beq     $13, $0, " << skip_label2 << "\n";
			out << "    nop\n";
			out << "    li      $14, 1\n";
			out << "   " << skip_label2 << ":\n";
			break;
		case '!':
			// if source is zero, return 1, else return 0
			out << "    li      $14, 0\n";
			out << "    bne     $10, $0, " << skip_label1 << "\n";
			out << "    nop\n";
			out << "    li      $14, 1\n";
			out << "   " << skip_label1 << ":\n";
			break;
		default:
			throw compile_error("unsupported type of boolean operator in LogicalInstruction");
	}
	context.store_variable(out, destination, 14);
}

// *******************************************

BitwiseInstruction::BitwiseInstruction(std::string destination, std::string source1, std::string source2, char operatorType)
: destination(destination), source1(source1), source2(source2), operatorType(operatorType) {}

void BitwiseInstruction::Debug(std::ostream &dst) const {
	switch (operatorType) {
		case '&':
			dst << "    bitwiseAnd " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '|':
			dst << "    bitwiseOr " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '^':
			dst << "    bitwiseXor " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '~':
			dst << "    bitwiseNot " << destination << ", " << source1 << std::endl;
			break;
		default:
			throw compile_error("unsupported type of boolean operator in BitwiseInstruction");
	}
}

void BitwiseInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(!context.get_type(source1).is_integer()) {
		throw compile_error("cannot perform a bitwise operation on structs, unions, or floats");
	}
	if(operatorType != '~') {
		if(!context.get_type(source2).is_integer()) {
			throw compile_error("cannot perform a bitwise operation on structs, unions, or floats");
		}
	}
	// load up our integers
	context.load_variable(out, source1, 8);
	if(operatorType != '~') context.load_variable(out, source2, 9);
	// perform the bitwise operation and store into $10
	switch (operatorType) {
		case '&':
			out << "    and     $10, $8, $9\n";
			break;
		case '|':
			out << "    or      $10, $8, $9\n";
			break;
		case '^':
			out << "    xor     $10, $8, $9\n";
			break;
		case '~':
			out << "    not     $10, $8\n";
			break;
		default:
			throw compile_error("unsupported type of boolean operator in BitwiseInstruction");
	}
	// store back into memory
	context.store_variable(out, destination, 10);
}

// *******************************************

EqualityInstruction::EqualityInstruction(std::string destination, std::string source1, std::string source2, char equalityType)
: destination(destination), source1(source1), source2(source2), equalityType(equalityType) {}

void EqualityInstruction::Debug(std::ostream &dst) const {
	switch (equalityType) {
		case '=':
			dst << "    equals " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '!':
			dst << "    notEquals " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '<':
			dst << "    lessThan " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case '>':
			dst << "    greaterThan " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case 'l':
			dst << "    lessOrEq " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		case 'g':
			dst << "    greaterOrEq " << destination << ", " << source1 << ", " << source2 << std::endl;
			break;
		default:
			throw compile_error("unsupported type of relational operator in EqualityInstruction");
	}
}

// *******************************************

ShiftInstruction::ShiftInstruction(std::string destination, std::string source1, std::string source2, bool doRightShift)
: destination(destination), source1(source1), source2(source2), doRightShift(doRightShift) {}

void ShiftInstruction::Debug(std::ostream &dst) const {
	if(doRightShift) {
		dst << "    rightshift " << destination << ", " << source1 << ", " << source2 << std::endl;
	} else {
		dst << "    leftshift " << destination << ", " << source1 << ", " << source2 << std::endl;
	}
}

void ShiftInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(!context.get_type(source1).is_integer() || !context.get_type(source1).is_integer()) {
		throw compile_error("cannot perform a shift operation on structs, unions, or floats");
	}
	context.load_variable(out, source1, 8);
	context.load_variable(out, source2, 9);
	if(doRightShift) {
		if(context.get_type(source1).is_signed()) {
			out << "    srav    $10, $8, $9\n";
		} else {
			out << "    srlv    $10, $8, $9\n";
		}
	} else {
		out << "    sllv    $10, $8, $9\n";
	}
	context.store_variable(out, destination, 10);
}

// *******************************************

NegativeInstruction::NegativeInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void NegativeInstruction::Debug(std::ostream &dst) const {
	dst << "    negative " << destination << ", " << source << std::endl;
}

void NegativeInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(context.get_type(source).is_struct()) {
		throw compile_error("cannot make structs or unions negative");
	}
	if(context.get_type(source).is_integer()) {
		context.load_variable(out, source, 8);
		out << "    subu    $10, $0, $8\n";
		context.store_variable(out, destination, 10);
	} else {
		// TODO: implement floats here
	}
}

// *******************************************

IncrementInstruction::IncrementInstruction(std::string destination, std::string source, bool decrement)
: destination(destination), source(source), decrement(decrement) {}

void IncrementInstruction::Debug(std::ostream &dst) const {
	if(decrement) {
		dst << "    decrement " << destination << ", " << source << std::endl;
	} else {
		dst << "    increment " << destination << ", " << source << std::endl;
	}
}

// *******************************************

AddInstruction::AddInstruction(std::string destination, std::string source1, std::string source2)
: destination(destination), source1(source1), source2(source2) {}

void AddInstruction::Debug(std::ostream &dst) const {
	dst << "    add " << destination << ", " << source1 << ", " << source2 << std::endl;
}

// *******************************************

SubInstruction::SubInstruction(std::string destination, std::string source1, std::string source2)
: destination(destination), source1(source1), source2(source2) {}

void SubInstruction::Debug(std::ostream &dst) const {
	dst << "    sub " << destination << ", " << source1 << ", " << source2 << std::endl;
}

// *******************************************

MulInstruction::MulInstruction(std::string destination, std::string source1, std::string source2)
: destination(destination), source1(source1), source2(source2) {}

void MulInstruction::Debug(std::ostream &dst) const {
	dst << "    mul " << destination << ", " << source1 << ", " << source2 << std::endl;
}

// *******************************************

DivInstruction::DivInstruction(std::string destination, std::string source1, std::string source2)
: destination(destination), source1(source1), source2(source2) {}

void DivInstruction::Debug(std::ostream &dst) const {
	dst << "    div " << destination << ", " << source1 << ", " << source2 << std::endl;
}

// *******************************************

ModInstruction::ModInstruction(std::string destination, std::string source1, std::string source2)
: destination(destination), source1(source1), source2(source2) {}

void ModInstruction::Debug(std::ostream &dst) const {
	dst << "    mod " << destination << ", " << source1 << ", " << source2 << std::endl;
}

// *******************************************

CastInstruction::CastInstruction(std::string destination, std::string source, Type cast_type)
: destination(destination), source(source), cast_type(cast_type) {}

void CastInstruction::Debug(std::ostream &dst) const {
	dst << "    cast " << destination << ", " << source << ", " << cast_type.name() << std::endl;
}

void CastInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	if(context.get_type(source).is_struct() || cast_type.is_struct()) {
		throw compile_error("cannot cast structs");
	}
	context.load_variable(out, source, 8);
	convert_type(out, 8, context.get_type(source), 10, cast_type);
	context.store_variable(out, destination, 10);
}

// *******************************************

FunctionCallInstruction::FunctionCallInstruction(std::string return_result, std::string function_name, std::vector<std::string> arguments)
: return_result(return_result), function_name(function_name), arguments(arguments) {}

void FunctionCallInstruction::Debug(std::ostream &dst) const {
	dst << "    call " << function_name << ", returns " << return_result << std::endl;
	for(std::vector<std::string>::const_iterator itr = arguments.begin(); itr != arguments.end(); ++itr) {
		dst << "      arg " << *itr << std::endl;
	}
}

// *******************************************

MemberAccessInstruction::MemberAccessInstruction(std::string destination, std::string base, unsigned offset)
: destination(destination), base(base), offset(offset) {}

void MemberAccessInstruction::Debug(std::ostream &dst) const {
	dst << "    member " << destination << ", " << base << " + " << offset << std::endl;
}

void MemberAccessInstruction::PrintMIPS(std::ostream& out, IRContext const& context) const {
	context.load_variable(out, base, 8);
	out << "    addiu   $8, $8, " << offset << "\n";
	context.store_variable(out, destination, 8);
}
