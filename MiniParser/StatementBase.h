#pragma once

#include <iostream>
#include "Calculator.h"

class Program;
class StatementBase
{
public:

	enum StatementType :char
	{
		Blocks,
		BeginStatement,
		ArrayInitStatement,
		AssignStatement,
		ReturnStatement,
		ConditionStatement
	};

	virtual ~StatementBase() = default;

	inline void SetContext(Program* program);

	inline void SetLine(unsigned line);

	inline unsigned GetLine()const;

	/*编译检查，查表达式，查变量（动态）*/
	virtual bool Check() = 0;

	virtual bool Execute() = 0;

	virtual void Clear() = 0;

	virtual StatementType GetType()const = 0;

	virtual void Save(std::ostream& out)const = 0;

	virtual void Load(std::istream& in) = 0;

protected:

	Program* m_program;
	unsigned m_line;

};
void StatementBase::SetContext(Program* program)
{
	m_program = program;
}

void StatementBase::SetLine(unsigned line)
{
	m_line = line;
}

unsigned StatementBase::GetLine() const
{
	return m_line;
}
