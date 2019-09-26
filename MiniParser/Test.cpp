#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "BracketItem.h"
#include "ValueItem.h"
#include "VariousIDF.h"
#include "FunctionIDF.h"
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
		str = "+";
		break;
	case BinaryOperator::Subtract:
		str = "-";
		break;
	case BinaryOperator::Multiply:
		str = "*";
		break;
	case BinaryOperator::Divide:
		str = "/";
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
	out << UnaryOperator::GetName(v->GetUnaryOperatorType());
	return out;
}

ostream& operator<<(ostream& out, BracketItem* v)
{
	string str;
	switch (v->GetBracketType())
	{
	case BracketItem::Left:
		str = "(";
		break;
	case BracketItem::Right:
		str = ")";
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

ostream& operator<<(ostream& out, VariousIDF* v)
{
	out << '$' << v->GetName();
	return out;
}

ostream& operator<<(ostream& out, ItemBase* v);
ostream& operator<<(ostream& out, FunctionIDF* v)
{
	out << '&' << v->GetName() << "(";
	for (int pos = 0; pos < v->Params().size(); ++pos)
	{
		for (auto i : v->Params()[pos])
			out << i;
		out << (pos == v->Params().size() - 1 ? '\0' : ',');
	}
	out << ')';
	return out;
}

ostream& operator<<(ostream& out, IdentificationItem* v)
{
	switch (v->GetIdentificationType())
	{
	case IdentificationItem::VariousIDF:
		out << (VariousIDF*)v;
		break;
	case IdentificationItem::FunctionIDF:
		out << (FunctionIDF*)v;
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
	case ItemBase::Identification:
		out << ((IdentificationItem*)v);
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, const Expression& v)
{
	for (auto i : v.GetExpression())
		out << i << " ";
	return out;
}
int main()
{
	/*InfixExpression e;

	e.AddItem(new ValueItem(5));
	e.AddItem(BinaryOperator::GetOperator(BinaryOperator::Divide));
	e.AddItem(BracketItem::GetBracket(BracketItem::Left));
	e.AddItem(new ValueItem(1.2));
	e.AddItem(UnaryOperator::GetOperator(UnaryOperator::Factorial));
	e.AddItem(BinaryOperator::GetOperator(BinaryOperator::Multiply));
	e.AddItem(new ValueItem(158));
	e.AddItem(BracketItem::GetBracket(BracketItem::Right));

	SuffixExpression se(e);
	Calculator calc;
	cout << e << endl;
	cout << se << endl;
	cout << (int)calc.Calculate(se) << " : ";
	cout << calc.GetResult() << endl;*/

	InfixExpression e("lg(10)+2.6*5");
	SuffixExpression se(e);
	Calculator calc;
	switch (calc.Calculate(se))
	{
	case Calculator::Succeed:
		cout << "结果是：" << calc.GetResult() << endl;
		break;
	case Calculator::MathError:
		cout << "表达式错误！" << endl;
		break;
	case Calculator::ExpressionError:
		cout << "数学错误！" << endl;
		break;
	}
	cin.get();
	return 0;
}
