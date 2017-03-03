#include "Instruction.hpp"

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
