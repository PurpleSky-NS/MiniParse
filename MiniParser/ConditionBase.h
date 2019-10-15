#pragma once

#include "Statement.h"

/*有逻辑条件的语句的基类，应实现短路运算*/
class LogicalBase :public Statement
{
protected:

	//a+b>0|b-a<0&a=5
	//(a=5|b=6)&c=s
	//!(4=5&(a=5|s=4))|a=5&a!=9

	/*条件运算符*/
	enum ConditionOperator : char
	{
		Equal,
		NotEqual,
		Less,
		Grate,
		LessEqual,
		GrateEqual
	};
	/*逻辑运算符*/
	enum LogicalOperator : char
	{
		Not,
		And,
		Or
	};

	/*逻辑表达式基类*/
	struct ConditionExpressionBase
	{
		enum ConditionExpressionType :char
		{
			Expression,
			Group
		};
		virtual ~ConditionExpressionBase() = default;
	protected:
		ConditionExpressionBase(ConditionExpressionType type) :
			m_type(type) {}
	private:
		ConditionExpressionType m_type;
	};

	/*逻辑表达式*/
	struct ConditionExpression : public ConditionExpressionBase
	{
		ConditionOperator conditionOperator;
		SuffixExpression* leftValue;
		SuffixExpression* rightValue;
		ConditionExpression() :
			ConditionExpressionBase(Expression) {}
		~ConditionExpression()
		{
			if (leftValue != nullptr)
				delete leftValue;
			if (rightValue != nullptr)
				delete rightValue;
		}
	};

	/*逻辑表达式组*/
	struct ConditionExpressionGroup :public ConditionExpressionBase
	{
		bool isNot;//是否取反
		std::vector<ConditionExpressionBase*> expresions;
		std::vector<LogicalOperator> logicalOperators;
		ConditionExpressionGroup() :
			ConditionExpressionBase(Group) {}
		~ConditionExpressionGroup()
		{
			for (auto& i : expresions)
				if (i != nullptr)
					delete i;
		}
	};

	/*转化表达式，new出来的，若不成功则返回空指针*/
	inline ConditionExpressionGroup* ParseConditdionExpression(const std::string& conditionExp)const;

	/*释放表达式*/
	inline void FreeConditdionExpression(ConditionExpressionGroup* group)const;

	/*执行逻辑表达式，返回是否执行成功，若不成功直接异常*/
	inline bool ExecuteConditdionExpression(ConditionExpressionGroup* group, bool& exeRes)const;

	/*检查逻辑表达式组*/
	inline bool CheckConditdionExpression(ConditionExpressionGroup* group)const;

};
inline void LogicalBase::FreeConditdionExpression(ConditionExpressionGroup* group) const
{
	if (group == nullptr)
		return;
	for (auto& i : group->expresions)
		if (i != nullptr)
			delete i;
	delete group;
}
