#include "Instruction.hpp"
#include "Conversions.hpp"

#include <iomanip>

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

StringInstruction::StringInstruction(std::string destination, std::string data)
: destination(destination), data(data) {}

void StringInstruction::Debug(std::ostream &dst) const {
	dst << "    ascii " << destination << " " << data << std::endl;
}

// *******************************************

MoveInstruction::MoveInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void MoveInstruction::Debug(std::ostream &dst) const {
	dst << "    move " << destination << ", " << source << std::endl;
}

AssignInstruction::AssignInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void AssignInstruction::Debug(std::ostream &dst) const {
	dst << "    assign *" << destination << ", " << source << std::endl;
}

// *******************************************

AddressOfInstruction::AddressOfInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void AddressOfInstruction::Debug(std::ostream &dst) const {
	dst << "    addressOf " << destination << ", &" << source << std::endl;
}

DereferenceInstruction::DereferenceInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void DereferenceInstruction::Debug(std::ostream &dst) const {
	dst << "    dereference " << destination << ", *" << source << std::endl;
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

// *******************************************

NegativeInstruction::NegativeInstruction(std::string destination, std::string source)
: destination(destination), source(source) {}

void NegativeInstruction::Debug(std::ostream &dst) const {
	dst << "    negative " << destination << ", " << source << std::endl;
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
