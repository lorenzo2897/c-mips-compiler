#include "UnaryExpression.hpp"

// external declaration
void yyerror(const char *);

Node* UnaryExpression::compute_sizeof_type(std::vector<std::string> *specifiers) {
	/*  TYPE		SIZE (bytes)
		char		1
		short		2
		int			4
		long		8
		long long	8
		float		4
		double		8
		long double	8
	*/
	if(specifiers->size() == 1) {
		std::string spec = specifiers->at(0);
		if(spec == "char") {
			return new Value(1);
		} else if(spec == "short") {
			return new Value(2);
		} else if(spec == "int") {
			return new Value(4);
		} else if(spec == "long") {
			return new Value(8);
		} else if(spec == "float") {
			return new Value(4);
		} else if(spec == "double") {
			return new Value(8);
		} else if(spec == "void") {
			return new Value(1);
		}
	} else if(specifiers->size() == 2) {
		std::string first = specifiers->at(0);
		std::string second = specifiers->at(1);
		if(first == "unsigned" || first == "signed") {
			if(second == "char") {
				return new Value(1);
			} else if(second == "short") {
				return new Value(2);
			} else if(second == "int") {
				return new Value(4);
			} else if(second == "long") {
				return new Value(8);
			}
		} else if(first == "long") {
			if(second == "long") {
				return new Value(8);
			} else if(second == "int") {
				return new Value(8);
			} else if(second == "double") {
				return new Value(8);
			}
		}
	} else if(specifiers->size() == 3) {
		if(specifiers->at(0) == "long" && specifiers->at(1) == "long" && specifiers->at(2) == "int") {
			return new Value(8);
		} else if(specifiers->at(0) == "unsigned" && specifiers->at(1) == "long" && specifiers->at(2) == "int") {
			return new Value(8);
		} else if(specifiers->at(0) == "unsigned" && specifiers->at(1) == "long" && specifiers->at(2) == "long") {
			return new Value(8);
		} else if(specifiers->at(0) == "signed" && specifiers->at(1) == "long" && specifiers->at(2) == "int") {
			return new Value(8);
		} else if(specifiers->at(0) == "signed" && specifiers->at(1) == "long" && specifiers->at(2) == "long") {
			return new Value(8);
		}
	} else if(specifiers->size() == 4) {
		if(specifiers->at(0) == "unsigned" && specifiers->at(1) == "long" && specifiers->at(2) == "long" && specifiers->at(3) == "int") {
			return new Value(8);
		} else if(specifiers->at(0) == "signed" && specifiers->at(1) == "long" && specifiers->at(2) == "long" && specifiers->at(3) == "int") {
			return new Value(8);
		}
	}

	yyerror("error: attempting sizeof on invalid type");
	return NULL;
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
