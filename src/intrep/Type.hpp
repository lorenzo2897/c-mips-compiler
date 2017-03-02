#ifndef IR_TYPE_H
#define IR_TYPE_H

#include <vector>
#include <string>

class Type {

private:
	std::vector<std::string> specifiers;
	int pointer_depth;

public:
	bool is_pointer() const;
	Type dereference() const;
	Type addressof() const;

};

#endif
