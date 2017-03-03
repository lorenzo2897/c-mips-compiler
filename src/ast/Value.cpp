#include "Value.hpp"

Value::Value(std::string s) {
	type = V_STRING;
	strval = s;
}

Value::Value(unsigned int i) {
	type = V_INT;
	val.i = i;
}

Value::Value(int i) {
	type = V_INT;
	val.i = i;
}

Value::Value(float f) {
	type = V_FLOAT;
	val.f = f;
}

Value::Value(double d) {
	type = V_DOUBLE;
	val.d = d;
}

Value::Value(char c) {
	type = V_CHAR;
	val.c = c;
}

void Value::Debug(std::ostream &dst, int indent) const {

	switch (type) {
		case V_STRING:
			dst << "(string: " << strval << ")";
			break;
		case V_CHAR:
			dst << "(char: " << val.c << ")";
			break;
		case V_INT:
			dst << "(int: " << val.i << ")";
			break;
		case V_FLOAT:
			dst << "(float: " << val.f << ")";
			break;
		case V_DOUBLE:
			dst << "(double: " << val.d << ")";
			break;
		default:
			dst << "(unknown value: " << debug_extras << ")";
			break;
	}
}

Type Value::GetType(VariableMap& bindings) const {
	switch (type) {
		case V_STRING:
			return Type("char", 1);
		case V_CHAR:
			return Type("char", 0);
		case V_INT:
			return Type("int", 0);
		case V_FLOAT:
			return Type("float", 0);
		case V_DOUBLE:
			return Type("double", 0);
		default:
			throw compile_error("invalid type");
	}
}
