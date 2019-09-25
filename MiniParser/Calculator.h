#pragma once

#include "SuffixExpression.h"

class Calculator
{
public:
	
	enum CalculateResult
	{
		Succeed,
		ExpressionError
	};
	
	Calculator()=delete;
	Calculator(const Calculator &)=delete;
	Calculator(Calculator&&)=delete;
	~Calculator()=default;
	
	inline CalculateResult Calculate(const std::string &expression);
	
	inline CalculateResult Calculate(const InfixExpression &expression);
	
	inline CalculateResult Calculate(const SuffixExpression &expression);
	
	inline double GetResult()const;
	
private:

	double m_prevResult;
	
};
	
Calculator::CalculateResult Calculator::Calculate(const std::string &expression)
{
	return Calculate(InfixExpression(expression));
}
	
Calculator::CalculateResult Calculator::Calculate(const InfixExpression &expression)
{
	return Calculate(SuffixExpression(expression));
}
	
Calculator::CalculateResult Calculator::Calculate(const SuffixExpression &expression)
{
	std::stack<ItemBase*> calcStack(expression.GetExpression().size/2);//为计算stack预留空间
	for(auto i:expression.GetExpression())
	{
		switch(i->GetType())
		{
			case ItemBase::Value:
				calcStack.push(i);
				break;
			case ItemBase::Operator:
				if(((OperatorItem*)i)->GetOperatorType()==OperatorItem::BinaryOperator)
				{
					/*二元运算符*/
					if(calcStack.size()<2)//操作数不够
						return ExpressionError;
					ItemBase *rightItem=calcStack.top();
					calcStack.pop();
					ItemBase *leftItem=calcStack.top();
					calcStack.pop();
					/*做类型检查*/
					if(rightItem->GetType()!=ItemBase::Value||leftItem->GetType()!=ItemBase::Value)
						return ExpressionError;
					
					
				}
				ValueItem *rightValue=calcStack.top();
				break;
		}
	}
}