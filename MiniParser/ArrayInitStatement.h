#pragma once

#include "Statement.h"
#include "Array.h"

/*数组初始化语句*/
class ArrayInitStatement :public Statement
{

public:

	ArrayInitStatement() = default;
	ArrayInitStatement(const ArrayInitStatement&) = delete;
	ArrayInitStatement(ArrayInitStatement&&) = delete;
	~ArrayInitStatement() = default;

	inline bool SetStatement(const std::string& varStr, const std::string& capacityStr, const std::string& initListStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual void Clear() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream& out)const;

	inline virtual void Load(std::istream& in);

private:

	std::string m_varName;
	SuffixExpression m_capacityExp;
	std::vector<SuffixExpression> m_initExps;
};
bool ArrayInitStatement::SetStatement(const std::string& varStr, const std::string& capacityStr, const std::string& initListStr)
{
	/*
	a[]=[]
	a[]=[1.2]
	a[2]=[]
	a[s+2]=[]
	a[5]=[1.3,5,5,5]*/
	Clear();
	InfixExpression inf;
	if (!(inf.ParseExpression(varStr)//转换成功
		&& inf.GetExpression().size() == 1//数量为1
		&& inf.GetExpression()[0]->GetType() == ItemBase::Identification //是标识符
		&& ((IdentificationItem*)inf.GetExpression()[0])->GetIdentificationType() == IdentificationItem::VariousIDF))//该元素是个变量
	{
		CompileError("[" + varStr + "]这不是个合法的标识符...");
		return false;
	}
	m_varName = varStr;


	if (!capacityStr.empty() && !(inf.ParseExpression(capacityStr) && m_capacityExp.ParseExpression(inf)))
	{
		CompileError("[" + capacityStr + "]括号里的这堆容量表达式有问题，你再看看");
		Clear();
		return false;
	}

	/*放初始化列表*/
	for (size_t beg = 0, end = initListStr.find(',', 0);; beg = end + 1, end = initListStr.find(',', beg))
	{
		std::string initExp = initListStr.substr(beg, (end == initListStr.npos ? initListStr.size() : end) - beg);
		m_initExps.push_back(SuffixExpression());
		if (!(inf.ParseExpression(initExp) && m_initExps.back().ParseExpression(inf)))
		{
			CompileError("[" + initExp + "]初始化的参数表达式有问题...");
			return false;
		}
		if (end == initListStr.npos)
			break;
	}

	return true;
}

inline bool ArrayInitStatement::Check()
{
	if (!Calculator::CheckExpression(m_capacityExp.GetExpression()))
		return false;
	for (auto& i : m_initExps)
		if (!Calculator::CheckExpression(i.GetExpression()))
			return false;
	return true;
}

inline bool ArrayInitStatement::DynamicCheck()
{
	if (!Statement::DynamicCheck(m_capacityExp.GetExpression()))
		return false;
	for (auto& i : m_initExps)
		if (!Statement::DynamicCheck(i.GetExpression()))
			return false;
	return true;
}

inline bool ArrayInitStatement::Execute()
{
	std::vector<double> initList;
	double val;
	initList.reserve(m_initExps.size());
	/*转换参数列表*/
	for (auto& i : m_initExps)
		if(i.GetExpression().empty())
			initList.push_back(0);
		else if (!CalculateExpression(i.GetExpression(), val))
			return false;
		else
			initList.push_back(val);

	unsigned capacity = 0;

	if (!m_capacityExp.GetExpression().empty())//如果指定了容量
		if (!CalculateToDigit(m_capacityExp.GetExpression(), capacity))
			return false;

	Array* arr = m_program->arr_pool.GetObject();

	if (initList.empty())//用指定容量构造
		arr->Replace(capacity);//如果没设置容量，默认为0，空数组
	else if (capacity == 0)//如果容量为空，初始化列表不为空
		arr->Replace(initList);
	else //都不为空
		arr->Replace(capacity, initList);

	VariousBase* varBase = m_program->var_table.GetVarious(m_varName);
	if (varBase != nullptr)
		FreeVarious(varBase);
	m_program->var_table.UpdateVarious(m_varName, arr);
	return true;
}

inline void ArrayInitStatement::Clear()
{
	m_varName.clear();
	m_capacityExp.Clear();
	for (auto& i : m_initExps)
		i.Clear();
	m_initExps.clear();
}

inline StatementBase::StatementType ArrayInitStatement::GetType() const
{
	return StatementType::ArrayInitStatement;
}

inline void ArrayInitStatement::Save(std::ostream& out) const
{
}

inline void ArrayInitStatement::Load(std::istream& in)
{
}