#pragma once

#include "ItemBase.h"

class OperatorItem :public ItemBase
{
public:

	/*运算符类型*/
	enum OperatorType : char
	{
		UnaryOperator,	//单目运算符
		BinaryOperator	//双目运算符
	};

	virtual inline ItemType GetType() const override;

	virtual OperatorType GetOperatorType()const = 0;

	virtual inline void Save(std::ostream& out) override;

	virtual void Free()override {}

};
OperatorItem::ItemType OperatorItem::GetType() const
{
	return Operator;
}

void OperatorItem::Save(std::ostream& out)
{
	out.put(Operator);
}
