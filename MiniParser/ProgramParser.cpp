#include "ProgramParser.h"
Program* ProgramParser::Compile(const std::string& name, std::istream& in)
{
	std::string data;
	unsigned line = 1;
	Program* cxt = new Program;
	cxt->m_name = name;
	StatementBase* statement;
	while (std::getline(in, data))
	{
		if ((statement = Compile(data, cxt, line++)) == nullptr)
			return cxt;
		cxt->m_baseBlocks->Add(statement);
	}
	cxt->m_isValid=true;
	return cxt;
}

StatementBase* ProgramParser::Compile(const std::string& data, Program* cxt, unsigned line)
{
	const std::regex arrayInitRegex("(.*)\\[(.*)\\]=\\[((?:.*,)*(?:.*))\\]");
	const std::regex assignRegex("(.*)=(.*)");
	const std::regex returnRegex("@(.*)");
	std::smatch match;
	StatementBase* statement = nullptr;

	if (std::regex_match(data, match, arrayInitRegex))
		statement = new ArrayInitStatement;
	else if (std::regex_match(data, match, assignRegex))
		statement = new AssignStatement;
	else if (std::regex_match(data, match, returnRegex))
		statement = new ReturnStatement;
	else
	{
		cxt->err_log.AddCompileError("无法识别的语句...", line);
		return nullptr;
	}

	/*SetStatement方法内部调用了err_log，需要cxt和line*/
	statement->SetContext(cxt);
	statement->SetLine(line);

	bool res = false;
	switch (statement->GetType())
	{
	case StatementBase::ArrayInitStatement:
		res = ((ArrayInitStatement*)statement)->SetStatement(match[1], match[2], match[3]);
		break;
	case StatementBase::AssignStatement:
		res = ((AssignStatement*)statement)->SetStatement(match[1], match[2]);
		break;
	case StatementBase::ReturnStatement:
		res = ((ReturnStatement*)statement)->SetStatement(match[1]);
		break;
	}
	if (!res)
	{
		delete statement;
		return nullptr;
	}
	return statement;
}