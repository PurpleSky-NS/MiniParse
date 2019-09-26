#pragma once

#include "ValueItem.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "BracketItem.h"

class ItemParser
{
public:

	static inline ItemBase* ParseItem(std::istream& in);

private:
	ItemParser() = delete;
	ItemParser(const ItemParser&) = delete;
	ItemParser(ItemParser&&) = delete;
	~ItemParser() = delete;
};
ItemBase* ItemParser::ParseItem(std::istream& in)
{
	switch ((ItemBase::ItemType)in.get())
	{
	case ItemBase::Value:
		double value;
		in.read((char*)& value, sizeof(double));
		return new ValueItem(value);
	case ItemBase::Operator:
		switch ((OperatorItem::OperatorType)in.get())
		{
		case OperatorItem::BinaryOperator:
			return BinaryOperator::GetOperator((BinaryOperator::BinaryOperatorType)in.get());
		case OperatorItem::UnaryOperator:
			return UnaryOperator::GetOperator((UnaryOperator::UnaryOperatorType)in.get());
		}
		return nullptr;
	case ItemBase::Bracket:
		return BracketItem::GetBracket((BracketItem::BracketType)in.get());
	}
	return nullptr;
}
