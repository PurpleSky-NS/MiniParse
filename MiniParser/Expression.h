#pragma once

#include <vector>
#include "ItemBase.h"

class Expression
{
public:

	inline Expression() = default;
	inline Expression(const Expression&) = delete;
	inline Expression(Expression&&) = delete;
	inline ~Expression() = default;

	/*获取表达式元素序列*/
	inline std::vector<ItemBase*>& GetExpression();

	/*获取表达式元素序列*/
	inline const std::vector<ItemBase*>& GetExpression()const;

	/*添加元素*/
	inline void AddItem(ItemBase* item);

	/*清空表达式，是否释放Value的内存*/
	inline void Clear(bool free);

protected:
	std::vector<ItemBase*> m_expression;
};

std::vector<ItemBase*>& Expression::GetExpression()
{
	return m_expression;
}

const std::vector<ItemBase*>& Expression::GetExpression()const
{
	return m_expression;
}

void Expression::AddItem(ItemBase* item)
{
	m_expression.push_back(item);
}

void Expression::Clear(bool free)
{
	if (free)
		for (auto i : m_expression)
			i->Free();
	m_expression.clear();
}
