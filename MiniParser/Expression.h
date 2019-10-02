#pragma once

#include <vector>
#include "ItemBase.h"

class Expression
{
public:

	inline Expression() = default;
	inline Expression(const Expression&) = default;
	inline Expression(Expression&&) = delete;
	inline ~Expression();

	/*获取表达式元素序列*/
	inline ExpressionType& GetExpression();

	/*获取表达式元素序列*/
	inline const ExpressionType& GetExpression()const;

	/*添加元素*/
	inline void AddItem(ItemBase* item);

	/*清空表达式*/
	inline void Clear();

protected:
	ExpressionType m_expression;
};

Expression::~Expression()
{
	Clear();
}

ExpressionType& Expression::GetExpression()
{
	return m_expression;
}

const ExpressionType& Expression::GetExpression()const
{
	return m_expression;
}

void Expression::AddItem(ItemBase* item)
{
	m_expression.push_back(item);
}

void Expression::Clear()
{
	for (auto i : m_expression)
		i->Free();
	m_expression.clear();
}
