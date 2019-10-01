#pragma once

#include <vector>

/*表达式元素基类*/
class ItemBase
{
public:

	enum ItemType :char
	{
		Operator,
		Value,
		Bracket,
		Identification
	};

	virtual ItemType GetType()const = 0;

	/*该接口用于Expression管理内存*/
	virtual void Free() = 0;
};
typedef std::vector<ItemBase*> ExpressionType;
