#include "FunctionCall.hpp"

FunctionCall::FunctionCall(std::string function_name) : Expression(), function_name(function_name) {}
FunctionCall::FunctionCall(std::string function_name, std::vector<Expression*> args) : Expression(), function_name(function_name), args(args) {}

void FunctionCall::Debug(std::ostream& dst, int indent) const {
	dst << function_name << "(";
	for(std::vector<Expression*>::const_iterator itr = args.begin(); itr != args.end(); ++itr) {
		if(itr != args.begin()) {
			dst << ", ";
		}
		(*itr)->Debug(dst, indent);
	}
	dst << ")";
}

Type FunctionCall::GetType(VariableMap const& bindings) const {
	if(bindings.count(function_name)) {
		if(bindings.at(function_name).is_function) {
			return bindings.at(function_name).type;
	} else {
		throw compile_error("variable " + function_name + " is not a function", sourceFile, sourceLine);
	}
	} else {
		throw compile_error("function " + function_name + " is not declared", sourceFile, sourceLine);
	}
}

std::string FunctionCall::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string return_result = unique((std::string)"fn_ret");
	stack[return_result] = GetType(bindings);
	std::vector<std::string> arg_registers;
	// evaluate all of the arguments
	for(std::vector<Expression*>::const_iterator itr = args.begin(); itr != args.end(); ++itr) {
		std::string res = (*itr)->MakeIR(bindings, stack, out);
		arg_registers.push_back(res);
	}
	// emit function call
	out.push_back(new FunctionCallInstruction(return_result, function_name, arg_registers));
	return return_result;
}

std::string FunctionCall::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use function call as an l-value", sourceFile, sourceLine);
}
