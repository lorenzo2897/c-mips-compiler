#ifndef AST_PROGRAMROOT_H
#define AST_PROGRAMROOT_H

#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Scope.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

class ProgramRoot : public Scope {

	void populate_declarations(VariableMap& bindings, ArrayMap& arrays) const;
	void populate_functions(VariableMap& bindings) const;

protected:
	std::vector<Function*> functions;
	std::vector<Function*> function_prototypes;

public:
	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
	void add(Node* node);

	void CompileIR(std::ostream& dst) const;
	void CompileMIPS(std::ostream& dst) const;
};

#endif
