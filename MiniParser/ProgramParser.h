#pragma once

#include <regex>
#include "ArrayInitStatement.h"
#include "AssignStatement.h"
#include "ReturnStatement.h"

class ProgramParser
{
public:

	/*编译,返回一定不为空*/
	static Program* Compile(const std::string& name, std::istream& in);

private:

	static StatementBase* Compile(const std::string& data, Program* cxt, unsigned line);

};
