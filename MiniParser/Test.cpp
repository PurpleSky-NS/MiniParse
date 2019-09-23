#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"
#include "BinaryOperator.h"
#include "UnarOperator.h"
#include "BracketItem.h"
#include "ValueItem.h"
using namespace std;

ostream& operator<<(ostream& out, BinaryOperator* v)
{
	string str;
	switch (v->GetBinaryOperatorType())
	{
	case BinaryOperator::Add:
		str = "＋";
		break;
	case BinaryOperator::Subtract:
		str = "－";
		break;
	case BinaryOperator::Multiply:
		str = "×";
		break;
	case BinaryOperator::Divide:
		str = "÷";
		break;
	case BinaryOperator::Mod:
		str = "%";
		break;
	}
	out << str;
}

ostream& operator<<(ostream& out, UnarOperator* v)
{
	string str;
	switch (v->GetUnarOperatorType())
	{
	case UnarOperator::Factorial:
		str = "!";
		break;
	case UnarOperator::Lg:
		str = "lg";
		break;;
	case UnarOperator::Ln:
		str = "ln";
		break;;
	case UnarOperator::Sin:
		str = "sin";
		break;
	case UnarOperator::Cos:
		str = "cos";
		break;
	case UnarOperator::Tan:
		str = "tan";
		break;
	case UnarOperator::Arcsin:
		str = "arcsin";
		break;
	case UnarOperator::Arccos:
		str = "arccos";
		break;
	case UnarOperator::Arctan:
		str = "arctan";
		break;
	}
	out << str;
}

ostream& operator<<(ostream& out, BracketItem* v)
{
	string str;
	switch (v->GetBracketType())
	{
	case BracketItem::Left:
		str = "（";
		break;
	case BracketItem::Right:
		str = "）";
		break;
	}
	out << str;
}

ostream& operator<<(ostream& out, ItemBase* v)
{
	switch (v->GetType())
	{
	case ItemBase::Value:
		out << ((ValueItem*)v)->GetValue;
		break;
	case ItemBase::Operator:
		out << ((OperatorItem*)v);
		break;
	case ItemBase::Bracket:
		out << ((BracketItem*)v);
		break;
	}
}
int main()
{
	cin.get();
	return 0;
}
