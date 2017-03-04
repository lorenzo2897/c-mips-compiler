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
