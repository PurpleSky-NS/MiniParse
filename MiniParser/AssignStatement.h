#pragma once

#include <functional>
#include "VariousTable.h"
#include "Statement.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"

/*基础的赋值语句*/
class AssignStatement :public Statement
{
public:

	inline AssignStatement();
	AssignStatement(const AssignStatement&) = delete;
	AssignStatement(AssignStatement&&) = delete;
	inline ~AssignStatement();

	inline bool SetStatement(const std::string& variousName, const InfixExpression& expression);
	inline bool SetStatement(const std::string& arrayName, size_t pos, const InfixExpression& expression);
	inline bool SetStatement(const std::string& variousName, const SuffixExpression& expression);
	inline bool SetStatement(const std::string& arrayName, size_t pos, const SuffixExpression& expression);

	inline virtual bool Excuse() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream* o)const;

	inline virtual bool Load(std::istream* o);

private:

	VariousBase::VariousType m_LType = VariousBase::Various;

	std::string m_variousName;

	std::string m_arrayName;
	size_t m_arrayPos = 0;

	SuffixExpression* m_expression;

	inline bool ParseExpression(const InfixExpression& expression);

	/*设置变量的值*/
	inline void Excuse(VariousIDF* item);
	/*设置变量的值/执行函数*/
	inline void Excuse(FunctionIDF* item);

};

AssignStatement::AssignStatement()
{
	m_expression = new SuffixExpression;
}

AssignStatement::~AssignStatement()
{
	if (m_expression != nullptr)
		delete m_expression;
}

bool AssignStatement::SetStatement(const std::string& variousName, const InfixExpression& expression)
{
	m_LType = VariousBase::Various;
	m_variousName = variousName;
	return ParseExpression(expression);
}

bool AssignStatement::SetStatement(const std::string& arrayName, size_t pos, const InfixExpression& expression)
{
	m_LType = VariousBase::Array;
	m_arrayName = arrayName;
	m_arrayPos = pos;
	return ParseExpression(expression);
}

bool AssignStatement::SetStatement(const std::string& variousName, const SuffixExpression& expression)
{
	m_LType = VariousBase::Various;
	m_variousName = variousName;
	m_expression->GetExpression() = expression.GetExpression();
}

bool AssignStatement::SetStatement(const std::string& arrayName, size_t pos, const SuffixExpression& expression)
{
	m_LType = VariousBase::Array;
	m_arrayName = arrayName;
	m_arrayPos = pos;
	m_expression->GetExpression() = expression.GetExpression();
}

bool AssignStatement::Excuse()
{
	SuffixExpression exp(*m_expression);
	for (size_t i = 0; i < exp.GetExpression().size(); ++i)
	{
		if (exp.GetExpression()[i]->GetType() == ItemBase::Identification)
		{

		}
	}
	return true;
}

AssignStatement::StatementType AssignStatement::GetType() const
{
	return StatementType::AssignStatement;
}

void AssignStatement::Save(std::ostream* o) const
{
}

bool AssignStatement::Load(std::istream* o)
{
}

bool AssignStatement::ParseExpression(const InfixExpression& expression)
{
	if (!m_expression->ParseExpression(expression))
	{
		SetErrorMsg("表达式不合规范");
		return false;
	}
	return true;
}
