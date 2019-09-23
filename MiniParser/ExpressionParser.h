#pragma once

#include "Expression.h"
#include "ItemParser.h"

class ExpressionParser
{
public:

	static Expression* ParseExpression(std::istream& in);

private:
	ExpressionParser() = delete;
	ExpressionParser(const ExpressionParser&) = delete;
	ExpressionParser(ExpressionParser&&) = delete;
	~ExpressionParser() = delete;
};
Expression* ExpressionParser::ParseExpression(std::istream& in)
{
	uint32_t size;
	ItemBase* item;
	Expression* expression = new Expression();
	in.read((char*)& size, sizeof(size));
	for (uint32_t i = 0; i < size; ++i)
	{
		item = ItemParser::ParseItem(in);
		if (item == nullptr)
		{
			delete expression;
			expression = nullptr;
			break;
		}
		expression->AddItem(item);
	}
	return nullptr;
}
