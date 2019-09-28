#pragma once

#include <functional>
#include "VariousTable.h"
#include "Statement.h"

/*基础的赋值语句*/
class AssignStatement :public Statement
{
public:

	inline AssignStatement(const std::string& variousName, SuffixExpression* expression);
	inline AssignStatement(const std::string& arrayName, size_t pos, SuffixExpression* expression);
	AssignStatement(const AssignStatement&) = delete;
	AssignStatement(AssignStatement&&) = delete;
	~AssignStatement();

	inline virtual bool Excuse() override;

private:

	VariousBase::VariousType m_LType;

	std::string m_arrayName;
	size_t m_arrayPos;

	std::string m_variousName;

	SuffixExpression* m_expression;
};

AssignStatement::AssignStatement(const std::string& variousName, SuffixExpression* expression)
{
	m_LType = VariousBase::Various;
	m_variousName = variousName;
	m_expression = expression;
}

AssignStatement::AssignStatement(const std::string& arrayName, size_t pos, SuffixExpression* expression)
{
	m_LType = VariousBase::Array;
	m_arrayName = arrayName;
	m_arrayPos = pos;
	m_expression = expression;
}

bool AssignStatement::Excuse()
{
	return true;
}
