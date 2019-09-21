#pragma once

#include <vector>
#include "IFreeable.h"
#include "ItemBase.h"

class Expression :public IFreeable, public ISerialisable
{
public:

	/*获取表达式元素序列*/
	inline const std::vector<ItemBase>& GetExpression()const;

	/*添加元素*/
	inline void AddItem(const ItemBase& item);

	inline virtual void Free();

protected:
	std::vector<ItemBase> m_expression;
};
const std::vector<ItemBase>& Expression::GetExpression()const
{
	return m_expression;
}

void Expression::AddItem(const ItemBase& item)
{
	m_expression.push_back(item);
}

void Expression::Free()
{
	delete this;
}