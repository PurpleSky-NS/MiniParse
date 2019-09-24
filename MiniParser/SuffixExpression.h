#pragma once

#include <stack>
#include "BracketItem.h"
#include "OperatorItem.h"
#include "ValueItem.h"
#include "InfixExpression.h"

class SuffixExpression :public Expression
{
public:
	
	enum ParseResult
	{
		Succeed,
		BracketsMatchError
	};

	inline SuffixExpression() = default;
	/*中缀表达式类构造*/
	inline SuffixExpression(unsigned capacity);
	inline SuffixExpression(const InfixExpression& expression);
	SuffixExpression(const SuffixExpression&) = delete;
	SuffixExpression(SuffixExpression&&) = delete;
	~SuffixExpression() = default;
	
	inline ParseResult ParseExpression(const InfixExpression& expression);
	
};

SuffixExpression::SuffixExpression(unsigned capacity):
    Expression(capacity)
{}

SuffixExpression::SuffixExpression(const InfixExpression& expression)
{
	ParseExpression(expression);
}

SuffixExpression::ParseResult SuffixExpression::ParseExpression(const InfixExpression& expression)
{
	//静态优先级表，按二元运算符的优先级来
	static const unsigned char operatorPriority[]={1,1,2,2,2,3};
	
	std::stack<ItemBase*> operatorStack;//建立符号栈
	
	m_expression.reserve(expression.GetExpression().size());//为vector预留空间
	
	for(auto i:expression.GetExpression())
	{
		switch(i->GetType())
		{
			case ItemBase::Value:
				m_expression.push_back(i);
			break;
			case ItemBase::BracketItem:
				if(((BracketItem*)i)->GetBracketType()==BracketItem::Left)
					operatorStack.push(i);
				else
				{
					auto op=operatorStack.top();
					operatorStack.pop();
					/*当取出符号是左括号结束循环*/
					while(!(op->GetType()==BaseItem::Bracket&&((BracketItem)op)->GetBracketType()==BracketItem::Left))
					{
						if(operatorStack.empty())
							return BracketsMatchError;//括号不匹配
						m_expression.push_back(op);//将括号内运算符加入表达式
						op=operatorStack.top();//取出下一个符号
						operatorStack.pop();
					}
				}
			break;
			case ItemBase::OperatorItem:
				
			break;
		}
			
	}
	return Succeed;
}