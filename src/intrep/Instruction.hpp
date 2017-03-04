#ifndef IR_INSTRUCTION_H
#define IR_INSTRUCTION_H

#include <string>
#include <iostream>
#include <vector>

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

#endif
