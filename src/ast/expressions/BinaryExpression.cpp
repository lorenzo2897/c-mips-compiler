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
	switch (op) {
		case op_equals:
		case op_notequals:
		case op_lessequal:
		case op_moreequal:
		case op_lessthan:
		case op_morethan:
		case op_logicaland:
		case op_logicalor:
			return Type("int", 0);
		default:
			return left->GetType(bindings);
	}
}


std::string BinaryExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {

	std::string src1 = left->MakeIR(bindings, stack, out);
	std::string src2 = right->MakeIR(bindings, stack, out);
	std::string dst;
	Instruction* instr = NULL;

	if(op == op_logicaland) {
		dst = unique("lgand");
		instr = new LogicalInstruction(dst, src1, src2, '&');
	} else if(op == op_logicalor) {
		dst = unique("lgor");
		instr = new LogicalInstruction(dst, src1, src2, '|');

	} else if(op == op_bitwiseand) {
		dst = unique("bw_and");
		instr = new BitwiseInstruction(dst, src1, src2, '&');
	} else if(op == op_bitwiseor) {
		dst = unique("bw_or");
		instr = new BitwiseInstruction(dst, src1, src2, '|');
	} else if(op == op_bitwisexor) {
		dst = unique("bw_xor");
		instr = new BitwiseInstruction(dst, src1, src2, '^');

	} else if(op == op_equals) {
		dst = unique("eq");
		instr = new EqualityInstruction(dst, src1, src2, '=');
	} else if(op == op_notequals) {
		dst = unique("neq");
		instr = new EqualityInstruction(dst, src1, src2, '!');
	} else if(op == op_lessthan) {
		dst = unique("lt");
		instr = new EqualityInstruction(dst, src1, src2, '<');
	} else if(op == op_morethan) {
		dst = unique("gt");
		instr = new EqualityInstruction(dst, src1, src2, '>');
	} else if(op == op_lessequal) {
		dst = unique("lte");
		instr = new EqualityInstruction(dst, src1, src2, 'l');
	} else if(op == op_moreequal) {
		dst = unique("gte");
		instr = new EqualityInstruction(dst, src1, src2, 'g');

	} else if(op == op_leftshift) {
		dst = unique("lshift");
		instr = new ShiftInstruction(dst, src1, src2, false);
	} else if(op == op_rightshift) {
		dst = unique("rshift");
		instr = new ShiftInstruction(dst, src1, src2, true);

	} else if(op == op_add) {
		dst = unique("add");
		instr = new AddInstruction(dst, src1, src2);
	} else if(op == op_subtract) {
		dst = unique("sub");
		instr = new SubInstruction(dst, src1, src2);
	} else if(op == op_multiply) {
		dst = unique("mul");
		instr = new MulInstruction(dst, src1, src2);
	} else if(op == op_divide) {
		dst = unique("div");
		instr = new DivInstruction(dst, src1, src2);
	} else if(op == op_modulo) {
		dst = unique("mod");
		instr = new ModInstruction(dst, src1, src2);
	}

	if(instr) {
		stack[dst] = GetType(bindings);
		out.push_back(instr);
		return dst;
	} else {
		throw compile_error("assembly generation of BinaryExpression not implemented for this operator", sourceFile, sourceLine);
	}
}

std::string BinaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use binary operators within an l-value", sourceFile, sourceLine);
}

int32_t BinaryExpression::evaluate_int(VariableMap const& bindings) const {
	int32_t l = left->evaluate_int(bindings);
	int32_t r = right->evaluate_int(bindings);

	switch (op) {
		case op_logicalor:
			return l || r;
		case op_logicaland:
			return l && r;
		case op_bitwiseor:
			return l | r;
		case op_bitwisexor:
			return l ^ r;
		case op_bitwiseand:
			return l & r;
		case op_equals:
			return l == r;
		case op_notequals:
			return l != r;
		case op_lessthan:
			return l < r;
		case op_morethan:
			return l > r;
		case op_lessequal:
			return l <= r;
		case op_moreequal:
			return l >= r;
		case op_leftshift:
			return l << r;
		case op_rightshift:
			return l >> r;
		case op_add:
			return l + r;
		case op_subtract:
			return l - r;
		case op_multiply:
			return l * r;
		case op_divide:
			return l / r;
		case op_modulo:
			return l % r;
	}
	throw compile_error("constant evaluation of BinaryExpression not implemented for this operator", sourceFile, sourceLine);
}
