#ifndef IR_TYPE_H
#define IR_TYPE_H

#include <vector>
#include <string>

class Type {

public:
	std::vector<std::string> specifiers;
	int pointer_depth;

	Type();
	Type(std::string specifier, int pointer_depth);
	Type(std::vector<std::string> specifiers, int pointer_depth);


	std::string name() const;
	bool is_pointer() const;
	bool is_integer() const;
	bool is_float() const;
	bool is_struct() const;
	bool is_enum() const;

	std::string struct_name() const;

	unsigned bytes() const;
	bool equals(Type t) const;
	bool is_compatible(Type t) const;

	Type dereference() const;
	Type addressof() const;

};

#endif
