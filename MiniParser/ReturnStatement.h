#pragma once

#include "Statement.h"

/*返回语句*/
class ReturnStatement :public Statement
{

public:

	ReturnStatement() = default;
	ReturnStatement(const ReturnStatement&) = delete;
	ReturnStatement(ReturnStatement&&) = delete;
	~ReturnStatement() = default;

	inline bool SetStatement(const std::string& returnStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual void Clear() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream& out)const;

	inline virtual void Load(std::istream& in);

private:
	SuffixExpression m_returnExp;
};
bool ReturnStatement::SetStatement(const std::string& returnStr)
{
	/*
	@a+15/2
	@a[2]+1
	*/
	InfixExpression inf;
	if (!(inf.ParseExpression(returnStr) && m_returnExp.ParseExpression(inf)))
	{
		CompileError("[" + returnStr + "]返回表达式有问题呀");
		return false;
	}
	if (m_returnExp.GetExpression().empty())
	{
		CompileError("返回值表达式不能为空...");
		return false;
	}
	return true;
}

inline bool ReturnStatement::Check()
{
	return CheckExpression(m_returnExp);
}

inline bool ReturnStatement::DynamicCheck()
{
	return Statement::DynamicCheck(m_returnExp.GetExpression());
}

inline bool ReturnStatement::Execute()
{
	double ret;
	if (!CalculateExpression(m_returnExp.GetExpression(), ret))
		return false;
	m_program->OnFinish(ret);
	return true;
}

inline void ReturnStatement::Clear()
{
	m_returnExp.Clear();
}

inline StatementBase::StatementType ReturnStatement::GetType() const
{
	return StatementType::ReturnStatement;
}

inline void ReturnStatement::Save(std::ostream& out) const
{
}

inline void ReturnStatement::Load(std::istream& in)
{
}
