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

Type UnaryExpression::GetType(VariableMap& bindings) const {
	if(op == op_sizeof) {
		return Type("int", 0);
	} else {
		return expression->GetType(bindings);
	}
}
