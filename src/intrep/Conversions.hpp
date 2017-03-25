#ifndef IR_CONVERSIONS_H
#define IR_CONVERSIONS_H

#include "Type.hpp"

Type arithmetic_conversion(Type a, Type b);

void convert_type(std::ostream &out, unsigned s_reg, Type s_type, unsigned d_reg, Type d_type);

#endif
