#pragma once

#include <regex>
#include "ArrayInitStatement.h"
#include "AssignStatement.h"

class ProgramParser
{
public:

	/*编译*/
	static Program* Compile(const std::string& name, std::istream& in);

private:

	static StatementBase* Compile(const std::string& data, Program* cxt, unsigned line);

};
