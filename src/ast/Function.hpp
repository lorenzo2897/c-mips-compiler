#ifndef AST_FUNCTION_H
#define AST_FUNCTION_H

#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Scope.hpp"

#include "../intrep/Type.hpp"

class Function : public Scope {

	void make_instructions(VariableMap& bindings, FunctionStack& stack, IRVector& out) const;

protected:

public:
	Function();

	std::string function_name;
	Type return_type;
	std::vector<Declaration*> parameters;
	bool prototype_only;

	void merge_parameters(Scope* scope);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;

	virtual void CompileIR(VariableMap globals, std::ostream& dst) const;
	virtual void CompileMIPS(VariableMap globals, std::ostream& dst, std::ostream& buff) const;
};

#endif
