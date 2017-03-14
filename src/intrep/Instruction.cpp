#include "Instruction.hpp"

// *******************************************

SimpleInstruction::SimpleInstruction(std::string name, std::string arg1) : name(name), arg1(arg1) {
}

SimpleInstruction::SimpleInstruction(std::string name, std::string arg1, std::string arg2) : name(name), arg1(arg1), arg2(arg2) {
}

SimpleInstruction::SimpleInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3) : name(name), arg1(arg1), arg2(arg2), arg3(arg3) {
}

void SimpleInstruction::Debug(std::ostream &dst) const {
	dst << "    " << name << " " << arg1;
	if(arg2 != "") {
		dst << ", " << arg2;
	}
	if(arg3 != "") {
		dst << ", " << arg3;
	}
}

// *******************************************

LabelInstruction::LabelInstruction(std::string name) : label_name(name) {}

void LabelInstruction::Debug(std::ostream &dst) const {
	dst << "  lbl_" << label_name << ":" << std::endl;
}

// *******************************************

GotoInstruction::GotoInstruction(std::string name) : label_name(name) {}

void GotoInstruction::Debug(std::ostream &dst) const {
	dst << "    goto lbl_" << label_name << std::endl;
}

// *******************************************

ReturnInstruction::ReturnInstruction(std::string return_variable) : return_variable(return_variable) {}

void ReturnInstruction::Debug(std::ostream &dst) const {
	dst << "    return " << return_variable << std::endl;
}

// *******************************************

ConstantInstruction::ConstantInstruction(std::string destination, Type type, uint32_t dataLo, uint32_t dataHi)
: destination(destination), type(type), dataLo(dataLo), dataHi(dataHi) {}

void ConstantInstruction::Debug(std::ostream &dst) const {
	dst << "    constant " << destination << " " << dataHi << " " << dataLo << std::endl;
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
