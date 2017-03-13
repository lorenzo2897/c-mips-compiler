#ifndef IR_INSTRUCTION_H
#define IR_INSTRUCTION_H

#include <string>
#include <iostream>
#include <vector>
#include <stdint.h>

#include "Type.hpp"

// *******************************************

class Instruction {
public:
	virtual void Debug(std::ostream& dst) const = 0;
};

// *******************************************

typedef std::vector<Instruction*> IRVector;

// *******************************************

class SimpleInstruction : public Instruction {

private:
	std::string name;
	std::string arg1, arg2, arg3;

public:
	SimpleInstruction(std::string name, std::string arg1);
	SimpleInstruction(std::string name, std::string arg1, std::string arg2);
	SimpleInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3);

	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class LabelInstruction : public Instruction {
private:
	std::string label_name;
public:
	LabelInstruction(std::string name);
	virtual void Debug(std::ostream& dst) const;
};

class GotoInstruction : public Instruction {
private:
	std::string label_name;
public:
	GotoInstruction(std::string name);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class ReturnInstruction : public Instruction {
private:
	std::string return_variable;
public:
	ReturnInstruction(std::string return_variable);
	virtual void Debug(std::ostream& dst) const;
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
};

class StringInstruction : public Instruction {
private:
	std::string destination;
	std::string data;
public:
	StringInstruction(std::string destination, std::string data);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class MoveInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	MoveInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
};

class AssignInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	AssignInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
};

// *******************************************

class AddressOfInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	AddressOfInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
};

class DereferenceInstruction : public Instruction {
private:
	std::string destination;
	std::string source;
public:
	DereferenceInstruction(std::string destination, std::string source);
	virtual void Debug(std::ostream& dst) const;
};

#endif
