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

UnaryExpression::UnaryExpression(Expression* expression, UnaryOperator op) : expression(expression), op(op) {}

UnaryExpression::UnaryExpression(Expression* expression, char opchar) : expression(expression) {
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
	} else if(op == op_addressof) {
		return expression->GetType(bindings).addressof();
	} else if(op == op_dereference) {
		return expression->GetType(bindings).dereference();
	} else {
		return expression->GetType(bindings);
	}
}

std::string UnaryExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(op == op_addressof) {
		return expression->MakeIR_lvalue(bindings, stack, out);
	} else if(op == op_dereference) {
		std::string s = expression->MakeIR(bindings, stack, out);
		std::string r = unique("deref");
		stack[r] = expression->GetType(bindings).dereference();
		out.push_back(new DereferenceInstruction(r, s));
		return r;
	} else {
		// TODO: implement unary expressions
		throw compile_error("UnaryExpression operator not implemented");
	}
}

std::string UnaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(op == op_addressof) {
		throw compile_error("a memory address is not an l-value");
	} else if(op == op_dereference) {
		return expression->MakeIR(bindings, stack, out);
	} else {
		throw compile_error("cannot use unary operators within an l-value");
	}
}
