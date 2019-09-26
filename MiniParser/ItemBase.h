#pragma once

#include "ISavable.h"

/*表达式元素基类*/
class ItemBase :public ISavable
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
