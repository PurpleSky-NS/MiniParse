#pragma once

#include <functional>
#include "Statement.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"
#include "Calculator.h"
#include "Various.h"

/*基础的赋值语句*/
const class AssignStatement :public Statement
{
public:

	AssignStatement() = default;
	AssignStatement(const AssignStatement&) = delete;
	AssignStatement(AssignStatement&&) = delete;
	~AssignStatement() = default;

	inline bool SetStatement(const std::string& leftStr, const std::string& rightStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream* o)const;

	inline virtual bool Load(std::istream* o);

private:

	VariousIDF m_leftVar;
	SuffixExpression m_rightExpression;
};

bool AssignStatement::Check()
{
	if (!CheckExpression(m_rightExpression.GetExpression()))
		return false;
	if (m_leftVar.IsArrayItem() && !CheckExpression(m_leftVar.ArrayPosExpression()))
		return false;
	return true;
}

bool AssignStatement::DynamicCheck()
{
	return true;
}

bool AssignStatement::Execute()
{
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
