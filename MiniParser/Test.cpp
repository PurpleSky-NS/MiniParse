#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "BracketItem.h"
#include "ValueItem.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"
#include "Calculator.h"
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
	return out;
}

ostream& operator<<(ostream& out, UnaryOperator* v)
{
	string str;
	switch (v->GetUnaryOperatorType())
	{
	case UnaryOperator::Factorial:
		str = "!";
		break;
	case UnaryOperator::Lg:
		str = "lg";
		break;;
	case UnaryOperator::Ln:
		str = "ln";
		break;;
	case UnaryOperator::Sin:
		str = "sin";
		break;
	case UnaryOperator::Cos:
		str = "cos";
		break;
	case UnaryOperator::Tan:
		str = "tan";
		break;
	case UnaryOperator::Arcsin:
		str = "arcsin";
		break;
	case UnaryOperator::Arccos:
		str = "arccos";
		break;
	case UnaryOperator::Arctan:
		str = "arctan";
		break;
	}
	out << str;
	return out;
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
	return out;
}

ostream& operator<<(ostream& out, OperatorItem* v)
{
	switch (v->GetOperatorType())
	{
	case OperatorItem::BinaryOperator:
		out << ((BinaryOperator*)v);
		break;
	case OperatorItem::UnaryOperator:
		out << ((UnaryOperator*)v);
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, ItemBase* v)
{
	switch (v->GetType())
	{
	case ItemBase::Value:
		out << ((ValueItem*)v)->GetValue();
		break;
	case ItemBase::Operator:
		out << ((OperatorItem*)v);
		break;
	case ItemBase::Bracket:
		out << ((BracketItem*)v);
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, const Expression& v)
{
	for (auto i : v.GetExpression())
		out << i;
	return out;
}
int main()
{
	InfixExpression e;

	e.AddItem(new ValueItem(5));
	e.AddItem(BinaryOperator::GetBinaryOperator(BinaryOperator::Divide));
	e.AddItem(BracketItem::GetBracket(BracketItem::Left));
	e.AddItem(new ValueItem(1.2));
	e.AddItem(UnaryOperator::GetUnaryOperator(UnaryOperator::Factorial));
	e.AddItem(BinaryOperator::GetBinaryOperator(BinaryOperator::Multiply));
	e.AddItem(new ValueItem(158));
	e.AddItem(BracketItem::GetBracket(BracketItem::Right));

	SuffixExpression se(e);
	Calculator calc;
	cout << e << endl;
	cout << se << endl;
	cout << (int)calc.Calculate(se) << " : " << calc.GetResult() << endl;
	cin.get();
	return 0;
}
