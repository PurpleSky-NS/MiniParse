#pragma once

#include <functional>
#include "Statement.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"
#include "Calculator.h"
#include "CalculatorParser.h"
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

	inline virtual void Save(std::ostream& out)const;

	inline virtual bool Load(std::istream& in);

private:

	VariousIDF m_leftVar;
	SuffixExpression m_rightExpression;
};

bool AssignStatement::SetStatement(const std::string& leftStr, const std::string& rightStr)
{
	/*a=12
	a[5]=4+568-sd*/
	InfixExpression infExp;
	if (!(infExp.ParseExpression(leftStr)//转化成功
		&& infExp.GetExpression().size() == 1//转化后只有一个元素
		&& infExp.GetExpression()[0]->GetType() == ItemBase::Identification//该元素是个标识符
		&& ((IdentificationItem*)infExp.GetExpression()[0])->GetIdentificationType() == IdentificationItem::VariousIDF))//该元素是个变量
	{
		CompileError("[" + leftStr + "]这好像不是一个变量吧...");
		return false;
	}
	VariousIDF& left_vidf = *(VariousIDF*)infExp.GetExpression()[0];
	m_leftVar.GetName() = left_vidf.GetName();
	m_leftVar.NegSigned() = left_vidf.NegSigned();
	m_leftVar.SetToArrayItem(left_vidf.IsArrayItem());
	m_leftVar.ArrayPosExpression() = std::move(left_vidf.ArrayPosExpression());

	if (!(infExp.ParseExpression(rightStr) && m_rightExpression.ParseExpression(infExp)))
	{
		CompileError("右边的表达式有点问题吧...");
		return false;
	}
	return true;
}

bool AssignStatement::Check()
{
	if (m_leftVar.IsArrayItem() && !Calculator::CheckExpression(m_leftVar.ArrayPosExpression()))
		return false;
	return Calculator::CheckExpression(m_rightExpression);
}

bool AssignStatement::DynamicCheck()
{
	if (m_leftVar.IsArrayItem() && !Statement::DynamicCheck(m_leftVar.ArrayPosExpression()))
		return false;
	return Statement::DynamicCheck(m_rightExpression.GetExpression());
}

bool AssignStatement::Execute()
{
	return true;
}

AssignStatement::StatementType AssignStatement::GetType() const
{
	return StatementType::AssignStatement;
}

void AssignStatement::Save(std::ostream& out) const
{
	CalculatorParser::Save(out, m_leftVar);
	CalculatorParser::Save(out, m_rightExpression.GetExpression());
}

bool AssignStatement::Load(std::istream& in)
{
	CalculatorParser::Load(in, m_leftVar);
	CalculatorParser::Load(in, m_rightExpression.GetExpression());
}
