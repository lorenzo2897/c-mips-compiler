#ifndef IR_INSTRUCTION_H
#define IR_INSTRUCTION_H

#include <string>
#include <iostream>
#include <vector>
#include <stdint.h>

#include "Type.hpp"
#include "VariableMap.hpp"
#include "IRContext.hpp"
#include "../CompileError.hpp"

// *******************************************

class Instruction {
public:
	virtual void Debug(std::ostream& dst) const = 0;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

typedef std::vector<Instruction*> IRVector;

// *******************************************

class LabelInstruction : public Instruction {
private:
	std::string label_name;
public:
	LabelInstruction(std::string name);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class GotoInstruction : public Instruction {
private:
	std::string label_name;
public:
	GotoInstruction(std::string name);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class GotoIfEqualInstruction : public Instruction {
private:
	std::string label_name;
	std::string variable;
	int32_t value;
public:
	GotoIfEqualInstruction(std::string name, std::string variable, int32_t value);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class ReturnInstruction : public Instruction {
private:
	std::string return_variable;
public:
	ReturnInstruction();
	ReturnInstruction(std::string return_variable);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class ConstantInstruction : public Instruction {
private:
	std::string destination;
	Type type;
	uint32_t dataLo;
	uint32_t dataHi;
public:
	ConstantInstruction(std::string destination, Type type, uint32_t dataLo, uint32_t dataHi = 0);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class StringInstruction : public Instruction {
private:
	std::string destination;
	std::string data;
public:
	StringInstruction(std::string destination, std::string data);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class MoveInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	MoveInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class AssignInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	AssignInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class AddressOfInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	AddressOfInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class DereferenceInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	DereferenceInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class LogicalInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
	char logicalType;
public:
	LogicalInstruction(std::string destination, std::string source1, std::string source2, char logicalType);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class BitwiseInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
	char operatorType;
public:
	BitwiseInstruction(std::string destination, std::string source1, std::string source2, char operatorType);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

class EqualityInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
	char equalityType;
public:
	EqualityInstruction(std::string destination, std::string source1, std::string source2, char equalityType);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class ShiftInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
	bool doRightShift;
public:
	ShiftInstruction(std::string destination, std::string source1, std::string source2, bool doRightShift);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class NegativeInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	NegativeInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class IncrementInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
	bool decrement;
public:
	IncrementInstruction(std::string destination, std::string source, bool decrement);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class AddInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
public:
	AddInstruction(std::string destination, std::string source1, std::string source2);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class SubInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
public:
	SubInstruction(std::string destination, std::string source1, std::string source2);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class MulInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
public:
	MulInstruction(std::string destination, std::string source1, std::string source2);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class DivInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
public:
	DivInstruction(std::string destination, std::string source1, std::string source2);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class ModInstruction : public Instruction {
private:
	std::string destination;
	std::string source1;
	std::string source2;
public:
	ModInstruction(std::string destination, std::string source1, std::string source2);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class CastInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
	Type cast_type;
public:
	CastInstruction(std::string destination, std::string source, Type cast_type);
	virtual void Debug(std::ostream& dst) const;
	virtual void PrintMIPS(std::ostream& out, IRContext const& context) const;
};

// *******************************************

class FunctionCallInstruction : public Instruction {
private:
	std::string return_result;
	std::string function_name;
	std::vector<std::string> arguments;
public:
	FunctionCallInstruction(std::string return_result, std::string function_name, std::vector<std::string> arguments);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class MemberAccessInstruction : public Instruction {
private:
	std::string destination;
	std::string base;
	unsigned offset;
public:
	MemberAccessInstruction(std::string destination, std::string base, unsigned offset);
	virtual void Debug(std::ostream& dst) const;
};

#endif
