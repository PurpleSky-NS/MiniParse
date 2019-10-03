#pragma once

#include "Statement.h"

/*数组初始化语句*/
class ArrayInitStatement :public Statement
{

public:

	ArrayInitStatement() = default;
	ArrayInitStatement(const ArrayInitStatement&) = delete;
	ArrayInitStatement(ArrayInitStatement&&) = delete;
	~ArrayInitStatement() = default;

	inline bool SetStatement(const std::string& leftStr, const std::string& rightStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream& out)const;

	inline virtual bool Load(std::istream& in);

private:

	bool m_isFixed;
	std::string m_varName;
	SuffixExpression m_capacityExp;
	std::vector<SuffixExpression> m_initExps;
};
bool ArrayInitStatement::SetStatement(const std::string& leftStr, const std::string& rightStr)
{
	/*a[]=[1.2]
	a[2]=[]
	a[s+2]=[]
	a[5]=[1.3,5,5,5]
	a[?]=[1.5]
	a[?]=[]*/
	InfixExpression inf;
	size_t fdLeftBrk = leftStr.find('[');
	size_t fdRightBrk = leftStr.rfind(']');
	if (!(fdLeftBrk != leftStr.npos && fdRightBrk != rightStr.npos && fdLeftBrk < fdRightBrk && fdLeftBrk>0))
	{
		CompileError("[" + leftStr + "]这玩意你确定像是个数组吗?");
		return false;
	}
	m_varName = leftStr.substr(0, fdLeftBrk);//取出数组名
	std::string inBrk = leftStr.substr(fdLeftBrk + 1, fdRightBrk - fdLeftBrk - 1);//取出括号里的东西
	if (inBrk.empty())//空的，说明是静态数组
		m_isFixed = true;
	else if (inBrk == "?")//'?'，说明是动态数组
		m_isFixed = false;
	else //其余情况都是静态数组
	{
		m_isFixed = true;
		if (!(inf.ParseExpression(inBrk) && m_capacityExp.ParseExpression(inf)))
		{
			CompileError("[" + inBrk + "]括号里的这堆表达式有问题，你再看看");
			return false;
		}
	}

	/*获取初始化列表*/
	size_t fdLeftBrk = rightStr.find('[');
	size_t fdRightBrk = rightStr.rfind(']');
	if (!(fdLeftBrk != rightStr.npos && fdRightBrk != rightStr.npos && fdLeftBrk < fdRightBrk && fdLeftBrk>0))
	{
		CompileError("[" + rightStr + "]这个初始化列表很有问题...");
		return false;
	}
	inBrk = rightStr.substr(fdLeftBrk + 1, fdRightBrk - fdLeftBrk - 1);//取出括号里的东西
	/*放初始化列表*/
	for (size_t beg = 0, end = rightStr.find(',', 0); beg != rightStr.npos; beg = end + 1, end = rightStr.find(',', beg))
	{
		std::string initExp = rightStr.substr(beg, (end == rightStr.npos ? rightStr.size() : end) - beg);
		m_initExps.push_back(SuffixExpression());
		if (!(inf.ParseExpression(initExp) && m_initExps.back().ParseExpression(inf)))
		{
			CompileError("[" + initExp + "]初始化的参数表达式有问题...");
			return false;
		}
	}
	if (m_isFixed && m_capacityExp.GetExpression().empty())//自动推断静态数组长度
		m_capacityExp.AddItem(new ValueItem(m_initExps.size()));
}

inline bool ArrayInitStatement::Check()
{
	if (!Calculator::CheckExpression(m_capacityExp.GetExpression()))
		return false;
	for (auto i : m_initExps)
		if (!Calculator::CheckExpression(i.GetExpression()))
			return false;
	return true;
}

inline bool ArrayInitStatement::DynamicCheck()
{
	if (!Statement::DynamicCheck(m_capacityExp.GetExpression()))
		return false;
	for (auto i : m_initExps)
		if (!Statement::DynamicCheck(i.GetExpression()))
			return false;
	return true;
}

inline bool ArrayInitStatement::Execute()
{
	return false;
}

inline StatementBase::StatementType ArrayInitStatement::GetType() const
{
	return StatementType::ArrayInitStatement;
}

inline void ArrayInitStatement::Save(std::ostream& out) const
{
}

inline bool ArrayInitStatement::Load(std::istream& in)
{
	return false;
}
