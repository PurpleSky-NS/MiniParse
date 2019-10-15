#pragma once
#pragma once

#include <functional>
#include "Statement.h"
#include "SuffixExpression.h"
#include "Calculator.h"
#include "CalculatorParser.h"

/*条件语句*/
class ConditionStatement :public Statement
{
public:

	ConditionStatement() = default;
	ConditionStatement(const ConditionStatement&) = delete;
	ConditionStatement(ConditionStatement&&) = delete;
	~ConditionStatement() = default;

	inline bool SetStatement(const std::string& leftStr, const std::string& rightStr);

	inline virtual bool Check() override;

	inline virtual bool Execute() override;

	inline virtual void Clear();

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream& out)const;

	inline virtual void Load(std::istream& in);

private:


	SuffixExpression m_leftExp;
	SuffixExpression m_rightExp;
};

bool ConditionStatement::SetStatement(const std::string& leftStr, const std::string& rightStr)
{
	return true;
}

bool ConditionStatement::Check()
{
	return true;
}

bool ConditionStatement::Execute()
{
	return true;
}

void ConditionStatement::Clear()
{
}

ConditionStatement::StatementType ConditionStatement::GetType() const
{
	return StatementType::ConditionStatement;
}

void ConditionStatement::Save(std::ostream& out) const
{
}

void ConditionStatement::Load(std::istream& in)
{
}
