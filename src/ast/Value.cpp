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

Type Value::GetType(VariableMap const& bindings) const {
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

uint32_t reinterpret(char x) {
	return x;
}
uint32_t reinterpret(unsigned int x) {
	return x;
}
uint32_t reinterpret(float x) {
	return *((uint32_t*) &x);
}
uint32_t reinterpret_lo(double x) {
	uint64_t i = *((uint64_t*) &x);
	return (uint32_t) i;
}
uint32_t reinterpret_hi(double x) {
	uint64_t i = *((uint64_t*) &x);
	return (uint32_t) (i >> 32);
}

std::string Value::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string name;
	switch (type) {
		case V_STRING:
			name = unique("string");
			stack[name] = GetType(bindings);
			out.push_back(new StringInstruction(name, strval));
			return name;
		case V_CHAR:
			name = unique("char");
			stack[name] = GetType(bindings);
			out.push_back(new ConstantInstruction(name, GetType(bindings), reinterpret(val.c)));
			return name;
		case V_INT:
			name = unique("int");
			stack[name] = GetType(bindings);
			out.push_back(new ConstantInstruction(name, GetType(bindings), reinterpret(val.i)));
			return name;
		case V_FLOAT:
			name = unique("float");
			stack[name] = GetType(bindings);
			out.push_back(new ConstantInstruction(name, GetType(bindings), reinterpret(val.f)));
			return name;
		case V_DOUBLE:
			name = unique("double");
			stack[name] = GetType(bindings);
			out.push_back(new ConstantInstruction(name, GetType(bindings), reinterpret_lo(val.d), reinterpret_hi(val.d)));
			return name;
		default:
			throw compile_error("invalid type");
	}
}

int32_t Value::evaluate_int(VariableMap const& bindings) const {
	switch (type) {
		case V_STRING:
			throw compile_error("cannot use a string as an integer expression");
		case V_CHAR:
			return val.c;
		case V_INT:
			return val.i;
		case V_FLOAT:
			throw compile_error("cannot use a float as an integer expression");
		case V_DOUBLE:
			throw compile_error("cannot use a double as an integer expression");
		default:
			throw compile_error("invalid type");
	}
}

bool Value::is_string_literal() const {
	return type == V_STRING;
}

std::string Value::get_string_literal() const {
	if(type != V_STRING) {
		throw compile_error("not a string literal");
	}
	return strval;
}
