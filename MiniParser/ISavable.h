#pragma once

#include <iostream>

/*实现二进制保存，二进制加载无法通过实现接口实现*/
class ISavable
{
public:
	virtual void Save(std::ostream& out) = 0;
};