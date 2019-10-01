#pragma once

#include <stack>
#include "BracketItem.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "ValueItem.h"
#include "FunctionIDF.h"
#include "InfixExpression.h"

class SuffixExpression :public Expression
{
public:

	inline SuffixExpression() = default;
	/*中缀表达式类构造*/
	inline SuffixExpression(const InfixExpression& expression);
	SuffixExpression(const SuffixExpression&) = default;
	SuffixExpression(SuffixExpression&&) = delete;
	~SuffixExpression() = default;

	/*若失败，多半是因为括号不匹配*/
	inline bool ParseExpression(const InfixExpression& expression);

private:

	inline bool ParseExpression(const ExpressionType& expression, ExpressionType& outExpression);

	inline bool ParseFunction(FunctionIDF* func);
};

SuffixExpression::SuffixExpression(const InfixExpression& expression)
{
	ParseExpression(expression);
}

bool SuffixExpression::ParseExpression(const InfixExpression& expression)
{
	return ParseExpression(expression.GetExpression(), m_expression);
}

bool SuffixExpression::ParseExpression(const ExpressionType& expression, ExpressionType& outExpression)
{
	//静态优先级表，按二元运算符的优先级来
	//+ - * / % ^
	static const unsigned char binOpPriority[] = { 1,1,2,2,2,3 };

	ExpressionType sufExp;
	std::stack<ItemBase*> operatorStack;//建立符号栈
	sufExp.reserve(expression.size());//为vector预留空间

	for (auto i : expression)
	{
		switch (i->GetType())
		{
		case ItemBase::Identification:
			if (((IdentificationItem*)i)->GetIdentificationType() == IdentificationItem::FunctionIDF)
			{
				if (!ParseFunction((FunctionIDF*)i))
					return false;
			}
			else
			{
				VariousIDF* varIDF = (VariousIDF*)i;
				if (varIDF->IsArrayItem())
					ParseExpression(varIDF->ArrayPosExpression(), varIDF->ArrayPosExpression());
			}
		case ItemBase::Value:
			sufExp.push_back(i);
			break;
		case ItemBase::Bracket:
			if (((BracketItem*)i)->GetBracketType() == BracketItem::Left)
				operatorStack.push(i);
			else
			{
				auto op = operatorStack.top();
				operatorStack.pop();
				/*当取出符号是左括号结束循环*/
				while (!(op->GetType() == ItemBase::Bracket && ((BracketItem*)op)->GetBracketType() == BracketItem::Left))
				{
					if (operatorStack.empty())
						return false;//括号不匹配
					sufExp.push_back(op);//将括号内运算符加入表达式
					op = operatorStack.top();//取出下一个符号
					operatorStack.pop();
				}
			}
			break;
		case ItemBase::Operator:
			if (((OperatorItem*)i)->GetOperatorType() == OperatorItem::BinaryOperator)
			{
				BinaryOperator* thisOp = (BinaryOperator*)i;
				ItemBase* preOp;//栈顶运算符
				while (!operatorStack.empty())
				{
					preOp = operatorStack.top();
					if (preOp->GetType() == ItemBase::Bracket)
					{
						operatorStack.push(thisOp);//栈顶是左括号就直接入栈
						break;
					}
					else //否则就是运算符
					{
						//一元运算符优先级最大
						if (((OperatorItem*)preOp)->GetOperatorType() == OperatorItem::UnaryOperator)
						{
							operatorStack.pop();//把栈顶一元运算符弹出
							sufExp.push_back(preOp);//加到表达式里
						}
						else //二元比较优先级
						{
							//当前运算符优先级比之前的高，压栈
							if (binOpPriority[(unsigned)((BinaryOperator*)thisOp)->GetBinaryOperatorType()] > binOpPriority[(unsigned)((BinaryOperator*)preOp)->GetBinaryOperatorType()])
							{
								operatorStack.push(thisOp);
								break;
							}
							else //小于等于的话，弹出之前的运算符
							{
								operatorStack.pop();//把栈顶一元运算符弹出
								sufExp.push_back(preOp);//加到表达式里
							}
						}
					}
				}
				//空栈了，说明该运算符优先级最低，把运算符压入
				if (operatorStack.empty())
					operatorStack.push(thisOp);
			}
			else
				operatorStack.push(i);
			break;
		}
	}
	while (!operatorStack.empty())
	{
		sufExp.push_back(operatorStack.top());
		operatorStack.pop();
	}
	outExpression = std::move(sufExp);
	return true;
}

bool SuffixExpression::ParseFunction(FunctionIDF* func)
{
	for (auto& i : func->Params())
		if (!ParseExpression(i, i))
			return false;
	return true;
}
