#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Expression* l, Expression* r, BinaryOperator op) : left(l), right(r), op(op) {}

void BinaryExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	left->Debug(dst, indent);
	switch (op) {
		case op_logicalor:
			dst << " || ";
			break;
		case op_logicaland:
			dst << " && ";
			break;
		case op_bitwiseor:
			dst << " | ";
			break;
		case op_bitwisexor:
			dst << " ^ ";
			break;
		case op_bitwiseand:
			dst << " & ";
			break;
		case op_equals:
			dst << " == ";
			break;
		case op_notequals:
			dst << " != ";
			break;
		case op_lessthan:
			dst << " < ";
			break;
		case op_morethan:
			dst << " > ";
			break;
		case op_lessequal:
			dst << " <= ";
			break;
		case op_moreequal:
			dst << " >= ";
			break;
		case op_leftshift:
			dst << " << ";
			break;
		case op_rightshift:
			dst << " >> ";
			break;
		case op_add:
			dst << " + ";
			break;
		case op_subtract:
			dst << " - ";
			break;
		case op_multiply:
			dst << " * ";
			break;
		case op_divide:
			dst << " / ";
			break;
		case op_modulo:
			dst << " % ";
			break;
	}
	right->Debug(dst, indent);
	dst << ")";
}

Type BinaryExpression::GetType(VariableMap const& bindings) const {
	return left->GetType(bindings);
}


std::string BinaryExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(op == op_add) {
		std::string src1 = left->MakeIR(bindings, stack, out);
		std::string src2 = right->MakeIR(bindings, stack, out);
		std::string dst = unique("add");
		stack[dst] = GetType(bindings);
		out.push_back(new AddInstruction(dst, src1, src2));
		return dst;
	} else if(op == op_subtract) {
		std::string src1 = left->MakeIR(bindings, stack, out);
		std::string src2 = right->MakeIR(bindings, stack, out);
		std::string dst = unique("sub");
		stack[dst] = GetType(bindings);
		out.push_back(new SubInstruction(dst, src1, src2));
		return dst;
	} else if(op == op_multiply) {
		std::string src1 = left->MakeIR(bindings, stack, out);
		std::string src2 = right->MakeIR(bindings, stack, out);
		std::string dst = unique("mul");
		stack[dst] = GetType(bindings);
		out.push_back(new MulInstruction(dst, src1, src2));
		return dst;
	} else if(op == op_divide) {
		std::string src1 = left->MakeIR(bindings, stack, out);
		std::string src2 = right->MakeIR(bindings, stack, out);
		std::string dst = unique("div");
		stack[dst] = GetType(bindings);
		out.push_back(new DivInstruction(dst, src1, src2));
		return dst;
	} else if(op == op_modulo) {
		std::string src1 = left->MakeIR(bindings, stack, out);
		std::string src2 = right->MakeIR(bindings, stack, out);
		std::string dst = unique("mod");
		stack[dst] = GetType(bindings);
		out.push_back(new ModInstruction(dst, src1, src2));
		return dst;
	} else {
		// TODO: implemented binary operators
		throw compile_error("assembly generation of BinaryExpression not fully implemented");
	}
}

std::string BinaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use binary operators within an l-value");
}
