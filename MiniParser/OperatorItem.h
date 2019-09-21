#pragma once

#include "ItemBase.h"

class OperatorItem :public ItemBase
{
public:

	/*运算符类型*/
	enum OperatorType : char
	{
		UnarOperator,	//单目运算符
		BinaryOperator	//双目运算符
	};

	virtual inline ItemType GetType() const override;

	virtual OperatorType GetOperatorType()const = 0;

};
OperatorItem::ItemType OperatorItem::GetType() const
{
	return Operator;
}
