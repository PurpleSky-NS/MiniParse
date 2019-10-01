#pragma once

#include <iostream>

class Statement
{
public:

	enum StatementType :char
	{
		AssignStatement
	};

	inline void SetContext(Program* program);

	inline void SetLine(unsigned line);

	inline unsigned GetLine()const;

	virtual bool Check() = 0;

	/*动态检查(假运行)，主要检查变量的作用域以及调用函数是否存在*/
	virtual bool DynamicCheck() = 0;

	virtual bool Excuse() = 0;

	virtual StatementType GetType()const = 0;

	virtual void Save(std::ostream* o)const = 0;

	virtual bool Load(std::istream* o) = 0;

protected:

	Program* m_program;
	unsigned m_line;

};
void Statement::SetContext(Program* program)
{
	m_program = program;
}

void Statement::SetLine(unsigned line)
{
	m_line = line;
}

unsigned Statement::GetLine() const
{
	return m_line;
}
