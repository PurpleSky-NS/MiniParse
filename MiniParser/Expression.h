#pragma once

#include <vector>
#include "IFreeable.h"
#include "ItemBase.h"

class Expression :public IFreeable, public ISavable
{
public:
	
	inline Expression()=default;
	inline Expression(const Expression &)=delete;
	inline Expression(Expression&&)=delete;
	inline ~Expression();

	/*获取表达式元素序列*/
	inline const std::vector<ItemBase*>& GetExpression()const;

	/*添加元素*/
	inline void AddItem(ItemBase *item);
	
	/*清空表达式*/
	inline void Clear();

	inline virtual void Free();
	
	inline virtual void Save(std::ostream &out) override;

protected:
	std::vector<ItemBase*> m_expression;
};

Expression::~Expression()
{
	Clear();
}

const std::vector<ItemBase*>& Expression::GetExpression()const
{
	return m_expression;
}

void Expression::AddItem(ItemBase *item)
{
	m_expression.push_back(item);
}

void Expression::Clear()
{
	for (auto i : m_expression)
		i->Free();
	m_expression.clear();
}

void Expression::Free()
{
	delete this;
}

void Expression::Save(std::ostream &out)
{
}