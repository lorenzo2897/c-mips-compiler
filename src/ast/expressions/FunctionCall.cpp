#include "FunctionCall.hpp"

FunctionCall::FunctionCall(std::string function_name) : function_name(function_name) {}
FunctionCall::FunctionCall(std::string function_name, std::vector<Expression*> args) : function_name(function_name), args(args) {}

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
