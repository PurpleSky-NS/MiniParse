#pragma once

#include <iostream>

//后缀表达式类,占个位置
class PostfixExpression
{};

class Statement
{
public:

	virtual void Excuse() = 0;

	virtual void Save(std::ostream &out) = 0;

	virtual void Load(std::istream &in) = 0;

	virtual void Free() = 0;

};