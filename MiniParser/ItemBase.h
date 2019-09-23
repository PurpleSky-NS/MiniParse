#pragma once

#include "IFreeable.h"
#include "ISavable.h"

/*表达式元素基类*/
class ItemBase :public ISavable,public IFreeable
{
public:

	enum ItemType:char
	{
		Operator,
		Value,
		Bracket
	};

	virtual ItemType GetType()const = 0;
};