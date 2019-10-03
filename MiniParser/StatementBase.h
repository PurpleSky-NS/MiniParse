#pragma once

#include <iostream>
#include "Calculator.h"

class Program;
class StatementBase
{
public:

	enum StatementType :char
	{
		ArrayInitStatement,
		AssignStatement
	};

	inline void SetContext(Program* program);

	inline void SetLine(unsigned line);

	inline unsigned GetLine()const;

	virtual bool Check() = 0;

	/*动态检查(假运行)，主要检查变量的作用域以及调用函数是否存在*/
	virtual bool DynamicCheck() = 0;

	virtual bool Execute() = 0;

	virtual StatementType GetType()const = 0;

	virtual void Save(std::ostream& out)const = 0;

	virtual bool Load(std::istream& in) = 0;

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
