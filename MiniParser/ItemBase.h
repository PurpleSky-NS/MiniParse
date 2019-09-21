#pragma once

/*表达式元素基类，不实现IFreeable接口*/
class ItemBase :public ISerialisable
{
public:
	enum ItemType:char
	{
		Operator,
		Value
	};

	virtual ItemType GetType()const = 0;

};