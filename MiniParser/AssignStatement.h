#pragma once

#include <functional>
#include "VariousTable.h"
#include "Statement.h"

/*基础的赋值语句*/
class AssignStatement :public Statement
{
public:

	inline virtual bool Excuse() override;

	virtual void Save(std::ostream &out) override;

	virtual void Load(std::istream &in) override;

	inline virtual void Free() override;

private:
	
	friend class Parser;
	
	VariousBase::VariousType m_LType;
	union
	{
		struct
		{
			std::string m_arrayName;
			unsigned m_arrayPos;
		}arrayValue;
		struct
		{
			std::string m_variousName;
		}variousValue;
	}m_value;
	PostfixExpression *m_expression;
	
	inline AssignStatement(const std::string &variousName,PostfixExpression *expression);
	inline AssignStatement(const std::string &arrayName,unsigned pos,PostfixExpression *expression);
	AssignStatement(const AssignStatement&)=delete;
	AssignStatement(AssignStatement&&)=delete;
	~AssignStatement();
};

bool AssignStatement::Excuse()
{
}

void AssignStatement::Free()
{
}