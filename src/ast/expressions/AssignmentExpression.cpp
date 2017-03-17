#include "AssignmentExpression.hpp"

AssignmentExpression::AssignmentExpression(Expression* l, Expression* r, char assignment_type) : Expression(), lvalue(l), rvalue(r), assignment_type(assignment_type) {}

void AssignmentExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	lvalue->Debug(dst, indent);
	if(assignment_type == '=') {
		dst << " = ";
	} else {
		dst << " " << assignment_type << "= ";
	}
	rvalue->Debug(dst, indent);
	dst << ")";
}

Type AssignmentExpression::GetType(VariableMap const& bindings) const {
	return lvalue->GetType(bindings);
}

std::string AssignmentExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(assignment_type == '=') {
		// evaluate the left hand side to get a pointer to the location to assign to
		std::string dst = lvalue->MakeIR_lvalue(bindings, stack, out);
		// evaluate the right hand side to get the value to assign
		std::string src = rvalue->MakeIR(bindings, stack, out);
		// output the assignment operation
		out.push_back(new AssignInstruction(dst, src));
		return src;
	} else {
		// evaluate the left hand side to get the value to assign
		std::string src_l = lvalue->MakeIR(bindings, stack, out);
		// evaluate the right hand side to get the value to assign
		std::string src_r = rvalue->MakeIR(bindings, stack, out);

		std::string res;
		Instruction* instr = NULL;

		switch (assignment_type) {
			case '+':
				res = unique("add");
				instr = new AddInstruction(res, src_l, src_r);
				break;
			case '-':
				res = unique("sub");
				instr = new SubInstruction(res, src_l, src_r);
				break;
			case '*':
				res = unique("mul");
				instr = new MulInstruction(res, src_l, src_r);
				break;
			case '/':
				res = unique("div");
				instr = new DivInstruction(res, src_l, src_r);
				break;
			case '%':
				res = unique("mod");
				instr = new ModInstruction(res, src_l, src_r);
				break;
			case '&':
				res = unique("bw_and");
				instr = new BitwiseInstruction(res, src_l, src_r, '&');
				break;
			case '|':
				res = unique("bw_or");
				instr = new BitwiseInstruction(res, src_l, src_r, '|');
				break;
			case '^':
				res = unique("bw_xor");
				instr = new BitwiseInstruction(res, src_l, src_r, '^');
				break;
			case '<':
				res = unique("lshift");
				instr = new ShiftInstruction(res, src_l, src_r, false);
				break;
			case '>':
				res = unique("rshift");
				instr = new ShiftInstruction(res, src_l, src_r, true);
				break;
			default:
				throw compile_error("unary assignment expression not implemented", sourceFile, sourceLine);
		}

		// output the binary operation
		stack[res] = GetType(bindings);
		out.push_back(instr);

		// evaluate the left hand side to get a pointer to the location to assign to
		std::string dst = lvalue->MakeIR_lvalue(bindings, stack, out);

		// output the assignment operation
		out.push_back(new AssignInstruction(dst, res));
		return dst;
	}
}

std::string AssignmentExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use an assignment expression within an l-value", sourceFile, sourceLine);
}
