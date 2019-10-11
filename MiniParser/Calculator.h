#pragma once

#include <cmath>
#include <functional>
#include "SuffixExpression.h"
#include "ObjectPool.h"

class Calculator
{
public:

	enum CalculateResult : char
	{
		Succeed,
		ExpressionError,
		IDFError,
		MathError
	};

	/*运算的表达式必须都是后缀表达式，否则计算不成功*/
	static inline double Calculate(const ExpressionType& expression, CalculateResult& res);
	static inline double Calculate(const ExpressionType& expression, std::function<bool(IdentificationItem*, double&)>GetVal, CalculateResult& res);
	static inline double Calculate(const ExpressionType& expression, std::function<bool(IdentificationItem*, double&)>GetVal, ObjectPool<NoFreeValueItem>& valuePool, CalculateResult& res);

	/*对表达式模拟运算，只对表达式正确性做检查*/
	static inline bool CheckExpression(const ExpressionType& expression);

	static inline bool IsDigit(double v);

private:

	Calculator() = delete;
	Calculator(const Calculator&) = delete;
	Calculator(Calculator&&) = delete;
	~Calculator() = delete;

	static inline bool CheckIdentification(IdentificationItem* item);
	static inline bool CheckFunction(FunctionIDF* item);
	static inline bool CheckVarious(VariousIDF* item);

	static inline double CalculateBinaryOperator(BinaryOperator::BinaryOperatorType type, double left, double right, CalculateResult& res);

	static inline double CalculateUnaryOperator(UnaryOperator::UnaryOperatorType type, double value, CalculateResult& res);

	static inline bool IsZero(double value);

};

double Calculator::Calculate(const ExpressionType& expression, CalculateResult& res)
{
	return Calculate(expression, nullptr, res);
}

double Calculator::Calculate(const ExpressionType& expression, std::function<bool(IdentificationItem*, double&)>GetVal, CalculateResult& res)
{
	/*预留一半值对象*/
	ObjectPool<NoFreeValueItem> valuePool((unsigned)expression.size() / 2, (unsigned)expression.size() / 4);
	return Calculate(expression, GetVal, valuePool, res);
}

double Calculator::Calculate(const ExpressionType& expression, std::function<bool(IdentificationItem*, double&)>GetVal, ObjectPool<NoFreeValueItem>& valuePool, CalculateResult& res)
{
	res = Succeed;
	if (expression.empty())//空的算啥
	{
		res = ExpressionError;
		return 0;
	}
	else if (expression.size() == 1)//只有一个还用算？
	{
		switch (expression[0]->GetType())
		{
		case ItemBase::Value:
			return ((ValueItem*)expression[0])->Value();
		case ItemBase::Identification:
			double ret;
			if (!GetVal((IdentificationItem*)expression[0], ret))
				res = IDFError;
			return ret;
		default:
			res = ExpressionError;
			return 0;
		}
	}
	std::stack<ItemBase*> calcStack;//计算栈
	for (auto& i : expression)
	{
		switch (i->GetType())
		{
		case ItemBase::Value:
		{
			ValueItem* cpValue = valuePool.GetObject();
			cpValue->Value() = ((ValueItem*)i)->Value();
			calcStack.push(cpValue);
		}
		break;
		case ItemBase::Operator:
			if (((OperatorItem*)i)->GetOperatorType() == OperatorItem::BinaryOperator)
			{
				/*二元运算符*/
				if (calcStack.size() < 2)//操作数不够
				{
					res = ExpressionError;
					break;
				}
				ItemBase* rightItem = calcStack.top();
				calcStack.pop();
				ItemBase* leftItem = calcStack.top();
				/*做类型检查*/
				if (rightItem->GetType() != ItemBase::Value || leftItem->GetType() != ItemBase::Value)
				{
					res = ExpressionError;
					break;
				}
				NoFreeValueItem* leftValue = (NoFreeValueItem*)leftItem, * rightValue = (NoFreeValueItem*)rightItem;
				/*左操作数还在栈里，不取出来了*/
				leftValue->Value() = CalculateBinaryOperator(((BinaryOperator*)i)->GetBinaryOperatorType(), leftValue->Value(), rightValue->Value(), res);
				if (res != Succeed)
					break;
				valuePool.FreeObject(rightValue);
			}
			else
			{
				/*一元运算符*/
				if (calcStack.empty())//操作数不够
				{
					res = ExpressionError;
					break;
				}
				ItemBase* item = calcStack.top();
				if (item->GetType() != ItemBase::Value)
				{
					res = ExpressionError;
					break;
				}
				ValueItem* value = (ValueItem*)item;
				value->Value() = CalculateUnaryOperator(((UnaryOperator*)i)->GetUnaryOperatorType(), value->Value(), res);
				if (res != Succeed)
					break;
			}
			break;
		case ItemBase::Identification:
		{
			if (GetVal == nullptr)
			{
				res = IDFError;
				break;
			}
			NoFreeValueItem* value = valuePool.GetObject();
			if (GetVal((IdentificationItem*)i, value->Value()))
				calcStack.push(value);
			else
			{
				valuePool.FreeObject(value);
				res = IDFError;
				break;
			}
		}
		break;
		}
		if (res != Succeed)
			break;
	}
	if (res != Succeed)
	{
		/*释放对象池的对象*/
		for (; !calcStack.empty(); calcStack.pop())
			if (calcStack.top()->GetType() == ItemBase::Value)
				valuePool.FreeObject((NoFreeValueItem*)calcStack.top());
		return 0.0;
	}

	if (calcStack.size() == 1 && calcStack.top()->GetType() == ItemBase::Value)
	{
		double val = ((ValueItem*)calcStack.top())->Value();
		/*释放对象池的对象*/
		valuePool.FreeObject((NoFreeValueItem*)calcStack.top());
		return val;
	}
	/*释放对象池的对象*/
	for (; !calcStack.empty(); calcStack.pop())
		if (calcStack.top()->GetType() == ItemBase::Value)
			valuePool.FreeObject((NoFreeValueItem*)calcStack.top());
	res = ExpressionError;
	return 0;
}

bool Calculator::CheckExpression(const ExpressionType& expression)
{
	if (expression.empty())//空的算啥
		return false;
	else if (expression.size() == 1)//只有一个还用算？
	{
		switch (expression[0]->GetType())
		{
		case ItemBase::Value:
			return true;
		case ItemBase::Identification:
			if (!CheckIdentification((IdentificationItem*)expression[0]))
				return false;
			return true;
		default:
			return false;
		}
	}
	std::stack<ItemBase::ItemType> calcStack;
	for (auto& i : expression)
	{
		switch (i->GetType())
		{
		case ItemBase::Identification:
			/*如果是函数，检查成功后当成普通数值处理*/
			if (!CheckIdentification((IdentificationItem*)i))
				return false;
		case ItemBase::Value:
			calcStack.push(ItemBase::Value);
			break;
		case ItemBase::Operator:
			if (((OperatorItem*)i)->GetOperatorType() == OperatorItem::BinaryOperator)
			{
				/*二元运算符*/
				if (calcStack.size() < 2)//操作数不够
					return false;
				ItemBase::ItemType rightItem = calcStack.top();
				calcStack.pop();
				/*左操作数还在栈里，不取出来了*/
				ItemBase::ItemType leftItem = calcStack.top();
				/*做类型检查*/
				if (rightItem != ItemBase::Value || leftItem != ItemBase::Value)
					return false;
			}
			else
			{
				/*一元运算符*/
				if (calcStack.empty())//操作数不够
					return false;
				ItemBase::ItemType item = calcStack.top();
				if (item != ItemBase::Value)
					return false;
			}
			break;
		}
	}
	if (calcStack.size() == 1 && calcStack.top() == ItemBase::Value)
		return true;
	return false;
}

bool Calculator::IsDigit(double v)
{
	return v - (int)v == 0.0;
}

bool Calculator::CheckIdentification(IdentificationItem* item)
{
	if (item->GetIdentificationType() == IdentificationItem::VariousIDF)
		return CheckVarious((VariousIDF*)item);
	return CheckFunction((FunctionIDF*)item);
}

bool Calculator::CheckFunction(FunctionIDF* item)
{
	for (auto& i : item->Params())
		if (!CheckExpression(i))
			return false;
	return true;
}

bool Calculator::CheckVarious(VariousIDF* item)
{
	if (item->IsArrayItem() && !CheckExpression(item->ArrayPosExpression()))
		return false;
	return true;
}

double Calculator::CalculateBinaryOperator(BinaryOperator::BinaryOperatorType type, double left, double right, CalculateResult& res)
{
	switch (type)
	{
	case BinaryOperator::Add:
		return left + right;
	case BinaryOperator::Subtract:
		return left - right;
	case BinaryOperator::Multiply:
		return left * right;
	case BinaryOperator::Divide:
		if (IsZero(right))
		{
			res = MathError;
			return 0.0;
		}
		return left / right;
	case BinaryOperator::Mod:
		return fmod(left, right);
	case BinaryOperator::Power:
		return pow(left, right);
	}
	return 0.0;
}

double Calculator::CalculateUnaryOperator(UnaryOperator::UnaryOperatorType type, double value, CalculateResult& res)
{
	switch (type)
	{
	case UnaryOperator::Factorial:
		if (value < -1)
		{
			res = MathError;
			return 0.0;
		}
		return tgamma(value + 1);
	case UnaryOperator::Lg:
		return log10(value);
	case UnaryOperator::Ln:
		return log(value);
	case UnaryOperator::Sin:
		return sin(value);
	case UnaryOperator::Cos:
		return cos(value);
	case UnaryOperator::Tan:
		return tan(value);
	case UnaryOperator::Arcsin:
		return asin(value);
	case UnaryOperator::Arccos:
		return acos(value);
	case UnaryOperator::Arctan:
		return atan(value);
	}
	return 0.0;
}

bool Calculator::IsZero(double value)
{
	return value == 0.0;
}
