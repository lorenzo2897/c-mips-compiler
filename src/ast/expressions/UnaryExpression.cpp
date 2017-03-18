#include "UnaryExpression.hpp"

#include "../../intrep/Type.hpp"

// external declaration
void yyerror(const char *);

Node* UnaryExpression::compute_sizeof_type(std::vector<std::string> *specifiers) {
	try {
		Type t(*specifiers, 0);
		return new Value(t.bytes());
	} catch(compile_error e) {
		yyerror("error: attempting sizeof on invalid type");
		return NULL;
	}
}

UnaryExpression::UnaryExpression(Expression* expression, UnaryOperator op) : Expression(), expression(expression), op(op) {}

UnaryExpression::UnaryExpression(Expression* expression, char opchar) : Expression(), expression(expression) {
	switch (opchar) {
		case '+':
			op = op_positive;
			break;
		case '-':
			op = op_negative;
			break;
		case '&':
			op = op_addressof;
			break;
		case '*':
			op = op_dereference;
			break;
		case '~':
			op = op_bitwisenot;
			break;
		case '!':
			op = op_logicalnot;
			break;
		default:
			op = op_positive;
	}
}

void UnaryExpression::Debug(std::ostream& dst, int indent) const {
	if(op == op_preincrement) {
		dst << "++("; expression->Debug(dst, indent); dst << ")";
	} else if(op == op_postincrement) {
		dst << "("; expression->Debug(dst, indent); dst << ")++";
	} else if(op == op_predecrement) {
		dst << "--("; expression->Debug(dst, indent); dst << ")";
	} else if(op == op_postdecrement) {
		dst << "("; expression->Debug(dst, indent); dst << ")--";

	} else if(op == op_positive) {
		dst << "+("; expression->Debug(dst, indent); dst << ")";
	} else if(op == op_negative) {
		dst << "-("; expression->Debug(dst, indent); dst << ")";

	} else if(op == op_addressof) {
		dst << "&("; expression->Debug(dst, indent); dst << ")";
	} else if(op == op_dereference) {
		dst << "*("; expression->Debug(dst, indent); dst << ")";

	} else if(op == op_bitwisenot) {
		dst << "~("; expression->Debug(dst, indent); dst << ")";
	} else if(op == op_logicalnot) {
		dst << "!("; expression->Debug(dst, indent); dst << ")";

	} else if(op == op_sizeof) {
		dst << "sizeof("; expression->Debug(dst, indent); dst << ")";
	}
}

Type UnaryExpression::GetType(VariableMap const& bindings) const {
	if(op == op_sizeof) {
		return Type("int", 0);
	} else if(op == op_logicalnot) {
		return Type("int", 0);
	} else if(op == op_addressof) {
		return expression->GetType(bindings).addressof();
	} else if(op == op_dereference) {
		return expression->GetType(bindings).dereference();
	} else {
		return expression->GetType(bindings);
	}
}

std::string UnaryExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(op == op_preincrement || op == op_predecrement) { // equivalent to (expr = expr + 1)
		// do the increment
		std::string src = expression->MakeIR(bindings, stack, out);
		std::string increment_dst = unique("incr");
		stack[increment_dst] = GetType(bindings);
		out.push_back(new IncrementInstruction(increment_dst, src, op == op_predecrement));
		// assign incremented value to original variable
		std::string assign_dst = expression->MakeIR_lvalue(bindings, stack, out);
		out.push_back(new AssignInstruction(assign_dst, increment_dst));
		// return variable
		return src;

	} else if(op == op_postincrement || op == op_postdecrement) {
		// make a copy of the variable
		std::string src = expression->MakeIR(bindings, stack, out);
		std::string var_copy = unique("postfix_copy");
		stack[var_copy] = GetType(bindings);
		out.push_back(new MoveInstruction(var_copy, src));
		// do the increment
		std::string increment_dst = unique("incr");
		stack[increment_dst] = GetType(bindings);
		out.push_back(new IncrementInstruction(increment_dst, src, op == op_postdecrement));
		// assign incremented value to original variable
		std::string assign_dst = expression->MakeIR_lvalue(bindings, stack, out);
		out.push_back(new AssignInstruction(assign_dst, increment_dst));
		// return old value of variable
		return var_copy;

	} else if(op == op_positive) {
		return expression->MakeIR(bindings, stack, out);

	} else if(op == op_negative) {
		std::string src = expression->MakeIR(bindings, stack, out);
		std::string dst = unique("neg");
		stack[dst] = GetType(bindings);
		out.push_back(new NegativeInstruction(dst, src));
		return dst;

	} else if(op == op_addressof) {
		return expression->MakeIR_lvalue(bindings, stack, out);

	} else if(op == op_dereference) {
		std::string s = expression->MakeIR(bindings, stack, out);
		std::string r = unique("deref");
		stack[r] = GetType(bindings);
		out.push_back(new DereferenceInstruction(r, s));
		return r;

	} else if(op == op_bitwisenot) {
		std::string src = expression->MakeIR(bindings, stack, out);
		std::string dst = unique("bw_not");
		stack[dst] = GetType(bindings);
		out.push_back(new BitwiseInstruction(dst, src, "", '~'));
		return dst;

	} else if(op == op_logicalnot) {
		std::string src = expression->MakeIR(bindings, stack, out);
		std::string dst = unique("lgnot");
		stack[dst] = GetType(bindings);
		out.push_back(new LogicalInstruction(dst, src, "", '!'));
		return dst;

	} else if(op == op_sizeof) {
		std::string dst = unique("sizeof");
		stack[dst] = GetType(bindings);
		out.push_back(new ConstantInstruction(dst, Type("int", 0), expression->GetType(bindings).bytes()));
		return dst;

	} else {
		throw compile_error("UnaryExpression operator not implemented", sourceFile, sourceLine);
	}
}

std::string UnaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(op == op_addressof) {
		throw compile_error("a memory address is not an l-value", sourceFile, sourceLine);
	} else if(op == op_dereference) {
		return expression->MakeIR(bindings, stack, out);
	} else {
		throw compile_error("cannot use unary operators within an l-value", sourceFile, sourceLine);
	}
}

int32_t UnaryExpression::evaluate_int(VariableMap const& bindings) const {
	int32_t e = expression->evaluate_int(bindings);
	switch (op) {
		case op_bitwisenot:
			return ~e;
		case op_logicalnot:
			return !e;
		case op_positive:
			return e;
		case op_negative:
			return -e;
		case op_sizeof:
			return expression->GetType(bindings).bytes();
		default:
			throw compile_error("cannot use this unary operator in a constant expression", sourceFile, sourceLine);
	}
}
