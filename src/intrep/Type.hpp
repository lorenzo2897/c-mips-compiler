#ifndef IR_TYPE_H
#define IR_TYPE_H

#include <vector>
#include <string>

class Type {
	std::vector<std::string> specifiers;

public:
	int pointer_depth;

	Type();
	Type(std::string specifier, int pointer_depth);
	Type(std::vector<std::string> specifiers, int pointer_depth);

	void set_specifiers(std::vector<std::string> s);


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

void align_address(unsigned& address, unsigned alignment, unsigned max_alignment = 4);

#endif
