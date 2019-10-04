#include <iostream>
#include <fstream>
#include <regex>
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
#include "CalculatorParser.h"
using namespace std;

ostream& operator<<(ostream& out, ItemBase* v);
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
	out << '$' << (v->NegSigned() ? "-" : "") << v->GetName();
	if (v->IsArrayItem())
	{
		out << '[';
		for (auto& i : v->ArrayPosExpression())
			out << i << ' ';
		out << ']';
	}
	return out;
}

ostream& operator<<(ostream& out, FunctionIDF* v)
{
	out << '&' << v->GetName() << "(";
	for (int pos = 0; pos < v->Params().size(); ++pos)
	{
		for (auto& i : v->Params()[pos])
			out << i << " ";
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
		out << ((ValueItem*)v)->Value();
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
	for (auto& i : v.GetExpression())
		out << i << " ";
	return out;
}
int main()
{
	static const std::string assignPattern = "(.*)\\[(.*)\\]=\\[((?:.*,)*(?:.*))\\]";

	string tst = "sd[ds]=[a,,,f,g,4]";

	std::regex r(assignPattern);

	std::smatch sm;
	if (std::regex_search(tst, sm, r))
	{
		cout << "SU" << endl;
		for (int i = 0; i < sm.size(); ++i)
			cout << sm[i] << endl;
		cout << sm.size() << endl;
	}
	else
		cout << "FA" << endl;

	/*std::string exp;
	InfixExpression e("Func(2.2+sda[1+2+3]+Func(3.2+5!,Fun()),5+6)!-sd--ss");
	InfixExpression ee(std::move(e));
	cout << e << endl;
	cout << ee << endl;*/
	//e.ParseExpression("Func(1+23+6+asd)");
	//SuffixExpression se(e);
	//cout << se << endl;
	//cout << Calculator::CheckExpression(se);

	/*switch (calc.Calculate(see))
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
	}*/
	cin.get();
	cin.get();
	return 0;
}
