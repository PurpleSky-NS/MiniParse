#pragma once

#include <functional>
#include "VariousTable.h"
#include "Statement.h"

/*基础的赋值语句*/
class AssignStatement :public Statement
{
public:

	inline AssignStatement(const std::string &variousName,PostfixExpression *expression);
	inline AssignStatement(const std::string &arrayName,unsigned pos,PostfixExpression *expression);
	AssignStatement(const AssignStatement&)=delete;
	AssignStatement(AssignStatement&&)=delete;
	~AssignStatement();
	
	inline virtual bool Excuse() override;

	virtual void Save(std::ostream &out) override;

	virtual void Load(std::istream &in) override;

	inline virtual void Free() override;

private:
	
	VariousBase::VariousType m_LType;
	union
	{
		struct
		{
			std::string arrayName;
			unsigned arrayPos;
		}arrayValue;
		struct
		{
			std::string variousName;
		}variousValue;
	}m_value;
	PostfixExpression *m_expression;
};

AssignStatement::AssignStatement(const std::string &variousName,PostfixExpression *expression)
{
	m_LType=VariousBase::Various;
	m_value.variousValue.variousName=variousName;
	m_expression=expression;
}

AssignStatement::AssignStatement(const std::string &arrayName,unsigned pos,PostfixExpression *expression)
{
	m_LType=VariousBase::Array;
	m_value.arrayValue.arrayName=arrayName;
	m_value.arrayValue.arrayPos=pos;
	m_expression=expression;
}

bool AssignStatement::Excuse()
{
}

void AssignStatement::Free()
{
}