#pragma once

#include "ValueItem.h"
#include "BinaryOperator.h"
#include "UnarOperator.h"
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
			return BinaryOperator::GetBinaryOperator((BinaryOperator::BinaryOperatorType)in.get());
		case OperatorItem::UnarOperator:
			return UnarOperator::GetUnarOperator((UnarOperator::UnarOperatorType)in.get());
		}
		return nullptr;
	case ItemBase::Bracket:
		return BracketItem::GetBracket((BracketItem::BracketType)in.get());
	}
	return nullptr;
}
