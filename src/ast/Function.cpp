#include "Function.hpp"

Function::Function() : Scope(), prototype_only(false) {}

void Function::merge_parameters(Scope *scope) {
	parameters.insert(parameters.end(), scope->declarations.begin(), scope->declarations.end());
}

void Function::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Function (" << function_name << ") type:";
	dst << return_type.name();

	dst << std::endl << spaces(indent) << "Parameters:" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = parameters.begin(); itr != parameters.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}

	dst << std::endl << spaces(indent) << "Declarations:" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}

	if(statements.size() > 0) {
		dst << spaces(indent) << "Body: ";
		for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
			(*itr)->Debug(dst, indent+2);
		}
	} else {
		dst << spaces(indent) << "Body: empty";
	}
	dst << std::endl << spaces(indent) << "End function " << function_name << std::endl;
}

void Function::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Function id=\"" << function_name << "\">" << std::endl;

	for(std::vector<Declaration*>::const_iterator itr = parameters.begin(); itr != parameters.end(); ++itr) {
		dst << spaces(indent+2) << "<Parameter id=\"" << (*itr)->identifier << "\" />" << std::endl;
	}

	dst << spaces(indent+2) << "<Scope>" << std::endl;

	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+4);
	}
	for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+4);
	}
	dst << spaces(indent+2) << "</Scope>" << std::endl;

	dst << spaces(indent) << "</Function>" << std::endl;
}

void Function::make_instructions(VariableMap& bindings, FunctionStack& stack, IRVector& out) const {
	// populate the bindings with the function parameters and declarations
	bindings.add_bindings(parameters);
	bindings.add_bindings(declarations);
	stack.add_variables(bindings, declarations);

	// generate instructions for initialisers
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->MakeIR_initialisers(bindings, stack, out);
	}

	// generate instructions from statements
	for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
		(*itr)->MakeIR(bindings, stack, out);
	}
}

void Function::CompileIR(VariableMap bindings, std::ostream &dst) const {
	FunctionStack stack;
	IRVector out;
	make_instructions(bindings, stack, out);

	// print IR in text form
	dst << function_name << ":" << std::endl;

	dst << "    # arrays" << std::endl;
	for(ArrayMap::const_iterator itr = stack.arrays.begin(); itr != stack.arrays.end(); ++itr) {
		dst << "    " << (*itr).first << " (" << (*itr).second.total_size() << ") " << (*itr).second.type.name() << " [" << (*itr).second.elements << "]" << std::endl;
	}
	dst << "    # stack" << std::endl;
	for(FunctionStack::const_iterator itr = stack.begin(); itr != stack.end(); ++itr) {
		dst << "    " << (*itr).first << " (" << (*itr).second.bytes() << ") " << (*itr).second.name() << std::endl;
	}

	dst << "    # code" << std::endl;
	for(IRVector::const_iterator itr = out.begin(); itr != out.end(); ++itr) {
		(*itr)->Debug(dst);
	}

	dst << "    # end " << function_name << std::endl;
	dst << std::endl;
}

void debug_stack_allocations(std::map<std::string, unsigned> const& array_addresses,
							std::map<std::string, unsigned> const& stack_offsets,
							unsigned stack_size,
							unsigned param_stack)
							{
	for(unsigned addr = 0; addr < param_stack; addr++) {
		if(addr == stack_size) {
			std::cerr << "#  -----\n";
		}
		std::cerr << "# " << addr << ": ";
		for(std::map<std::string, unsigned>::const_iterator itr = array_addresses.begin(); itr != array_addresses.end(); ++itr) {
			if(itr->second == addr) {
				std::cerr << "array data " << itr->first;
			}
		}
		for(std::map<std::string, unsigned>::const_iterator itr = stack_offsets.begin(); itr != stack_offsets.end(); ++itr) {
			if(itr->second == addr) {
				std::cerr << itr->first;
			}
		}
		if(addr == stack_size - 4) {
			std::cerr << " frame pointer";
		}
		if(addr == stack_size - 8) {
			std::cerr << " return address";
		}
		std::cerr << "\n";
	}
}

void Function::CompileMIPS(VariableMap globals, std::ostream &dst) const {
	VariableMap bindings = globals;
	FunctionStack stack;
	IRVector out;
	make_instructions(bindings, stack, out);

	// figure out where things are going to be on the stack
	std::map<std::string, unsigned> array_addresses;
	std::map<std::string, unsigned> stack_offsets;
	unsigned stack_size = 8;
	for(ArrayMap::const_iterator itr = stack.arrays.begin(); itr != stack.arrays.end(); ++itr) {
		align_address(stack_size, 4);
		array_addresses[(*itr).first] = stack_size;
		stack_size += (*itr).second.total_size();
	}
	for(FunctionStack::const_iterator itr = stack.begin(); itr != stack.end(); ++itr) {
		align_address(stack_size, (*itr).second.bytes());
		stack_offsets[(*itr).first] = stack_size;
		stack_size += (*itr).second.bytes();
	}
	stack_size += 8;

	// stack must be 8-byte aligned
	align_address(stack_size, 8, 8);

	// assign locations in the stack to function parameters
	unsigned parameters_stack = stack_size;

	// if we return a struct, space will have been allocated for us, and its address will be in $4
	if(return_type.is_struct()) {
		parameters_stack += 4;
	}

	// assign addresses to incoming parameters
	for(std::vector<Declaration*>::const_iterator itr = parameters.begin(); itr != parameters.end(); ++itr) {
		std::string param_alias = bindings.at((*itr)->identifier).alias;
		align_address(parameters_stack, (*itr)->var_type.is_float() ? (*itr)->var_type.bytes() : 4, 8);
		if((*itr)->var_type.bytes() == 1) parameters_stack += 3;
		if((*itr)->var_type.bytes() == 2) parameters_stack += 2;
		stack_offsets[param_alias] = parameters_stack;
		parameters_stack += (*itr)->var_type.bytes();
	}

	// create a context for the IR language to run in
	stack.add_variables(bindings, parameters);
	IRContext context(globals, stack, stack_offsets, function_name, return_type, stack_size);
	/* */
	//debug_stack_allocations(array_addresses, stack_offsets, stack_size, parameters_stack);

	// print MIPS assembly code
	dst << "    .globl " << function_name << "\n    .align 4\n";
	dst << function_name << ":\n";

	// function header
	dst << "    addiu   $sp, $sp, -" << stack_size << "\n"; // allocate stack
	dst << "    sw      $fp, " << (stack_size - 4) << "($sp)" << "\n"; // store previous frame pointer on stack
	dst << "    sw      $31, " << (stack_size - 8) << "($sp)" << "\n"; // store return address on stack
	dst << "    move    $fp, $sp\n"; // create new frame pointer

	// bring parameters onto the stack
	dst << "    sw      $4, " << stack_size << "($fp)\n";
	dst << "    sw      $5, " << (stack_size+4) << "($fp)\n";
	dst << "    sw      $6, " << (stack_size+8) << "($fp)\n";
	dst << "    sw      $7, " << (stack_size+12) << "($fp)\n";

	// being floating point parameters onto the stack
	if(parameters.size() > 0 && parameters.at(0)->var_type.is_float()) {
		if(parameters.at(0)->var_type.bytes() == 4) {
			dst << "    swc1    $f12, " << stack_size << "($fp)\n";
		} else {
			dst << "    sdc1    $f12, " << stack_size << "($fp)\n";
		}
		if(parameters.size() > 1 && parameters.at(1)->var_type.is_float()) {
			if(parameters.at(0)->var_type.bytes() == 4) {
				dst << "    swc1    $f14, " << (stack_size + parameters.at(0)->var_type.bytes()) << "($fp)\n";
			} else {
				dst << "    sdc1    $f14, " << (stack_size + parameters.at(0)->var_type.bytes()) << "($fp)\n";
			}
		}
	}

	// assign addresses to array pointers
	for(std::map<std::string, unsigned>::const_iterator itr = array_addresses.begin(); itr != array_addresses.end(); ++itr) {
		dst << "    addiu   $8, $fp, " << itr->second << "\n";
		dst << "    sw      $8, " << stack_offsets.at(itr->first) << "($fp)\n";
	}

	// emit code
	dst << "  fnc_" << function_name << "_code:\n";
	for(IRVector::const_iterator itr = out.begin(); itr != out.end(); ++itr) {
		(*itr)->PrintMIPS(dst, context);
	}

	dst << "  fnc_" << function_name << "_return:\n";
	dst << "    move    $sp, $fp\n"; // get back the base stack pointer
	dst << "    lw      $31, " << (stack_size - 8) << "($sp)" << "\n"; // load return address
	dst << "    lw      $fp, " << (stack_size - 4) << "($sp)" << "\n"; // load previous frame pointer
	dst << "    addiu   $sp, $sp, " << stack_size << "\n"; // release allocated stack
	dst << "    j       $31\n"; // jump to return address
	dst << "    nop\n"; // delay slot

	dst << "\n";
}
