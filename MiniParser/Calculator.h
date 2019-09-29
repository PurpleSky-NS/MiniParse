#pragma once

#include <cmath>
#include "SuffixExpression.h"
#include "ObjectPool.h"

class Calculator
{
public:

	enum CalculateResult : char
	{
		Succeed,
		ExpressionError,
		MathError
	};

	Calculator() = default;
	Calculator(const Calculator&) = delete;
	Calculator(Calculator&&) = delete;
	~Calculator() = default;

	inline CalculateResult Calculate(const std::string& expression);

	inline CalculateResult Calculate(const InfixExpression& expression);

	inline CalculateResult Calculate(const SuffixExpression& expression);

	/*对表达式模拟运算，只对表达式正确性做检查，不能检查函数内部是否符合*/
	inline CalculateResult CheckExpression(const std::string& expression);

	inline CalculateResult CheckExpression(const InfixExpression& expression);

	inline CalculateResult CheckExpression(const SuffixExpression& expression);

	inline double GetResult()const;

private:

	double m_prevResult = 0.0;
	CalculateResult m_occurResult = Succeed;

	inline double CalculateBinaryOperator(BinaryOperator::BinaryOperatorType type, double left, double right);

	inline double CalculateUnaryOperator(UnaryOperator::UnaryOperatorType type, double value);

	inline bool IsZero(double value)const;

};

Calculator::CalculateResult Calculator::Calculate(const std::string& expression)
{
	return Calculate(InfixExpression(expression));
}

Calculator::CalculateResult Calculator::Calculate(const InfixExpression& expression)
{
	return Calculate(SuffixExpression(expression));
}

Calculator::CalculateResult Calculator::Calculate(const SuffixExpression& expression)
{
	std::stack<ItemBase*> calcStack;//为计算栈预留空间
	/*预留一半值对象*/
	ObjectPool<ValueItem> valuePool((unsigned)expression.GetExpression().size() / 2, (unsigned)expression.GetExpression().size() / 4);
	m_occurResult = Succeed;
	for (auto i : expression.GetExpression())
	{
		switch (i->GetType())
		{
		case ItemBase::Value:
			ValueItem* cpValue;
			cpValue = valuePool.GetObject();
			cpValue->Value() = ((ValueItem*)i)->Value();
			calcStack.push(cpValue);
			break;
		case ItemBase::Operator:
			if (((OperatorItem*)i)->GetOperatorType() == OperatorItem::BinaryOperator)
			{
				/*二元运算符*/
				if (calcStack.size() < 2)//操作数不够
					return ExpressionError;
				ItemBase* rightItem = calcStack.top();
				calcStack.pop();
				ItemBase* leftItem = calcStack.top();
				/*做类型检查*/
				if (rightItem->GetType() != ItemBase::Value || leftItem->GetType() != ItemBase::Value)
					return ExpressionError;
				ValueItem* leftValue = (ValueItem*)leftItem, * rightValue = (ValueItem*)rightItem;
				/*左操作数还在栈里，不取出来了*/
				leftValue->Value() = CalculateBinaryOperator(((BinaryOperator*)i)->GetBinaryOperatorType(), leftValue->Value(), rightValue->Value());
				if (m_occurResult != Succeed)
					return m_occurResult;
				valuePool.FreeObject(rightValue);
			}
			else
			{
				/*一元运算符*/
				if (calcStack.empty())//操作数不够
					return ExpressionError;
				ItemBase* item = calcStack.top();
				if (item->GetType() != ItemBase::Value)
					return ExpressionError;
				ValueItem* value = (ValueItem*)item;
				value->Value() = CalculateUnaryOperator(((UnaryOperator*)i)->GetUnaryOperatorType(), value->Value());
				if (m_occurResult != Succeed)
					return m_occurResult;
			}
			break;
		}
	}
	if (calcStack.size() == 1 && calcStack.top()->GetType() == ItemBase::Value)
		m_prevResult = ((ValueItem*)calcStack.top())->Value();
	else
		m_occurResult = ExpressionError;
	return m_occurResult;
}

Calculator::CalculateResult Calculator::CheckExpression(const std::string& expression)
{
	return CheckExpression(InfixExpression(expression));
}

Calculator::CalculateResult Calculator::CheckExpression(const InfixExpression& expression)
{
	return CheckExpression(SuffixExpression(expression));
}

Calculator::CalculateResult Calculator::CheckExpression(const SuffixExpression& expression)
{
	std::stack<ItemBase::ItemType> calcStack;//为计算栈预留空间
	for (auto i : expression.GetExpression())
	{
		switch (i->GetType())
		{
		case ItemBase::Identification:
		case ItemBase::Value:
			calcStack.push(ItemBase::Value);
			break;
		case ItemBase::Operator:
			if (((OperatorItem*)i)->GetOperatorType() == OperatorItem::BinaryOperator)
			{
				/*二元运算符*/
				if (calcStack.size() < 2)//操作数不够
					return ExpressionError;
				ItemBase::ItemType rightItem = calcStack.top();
				calcStack.pop();
				/*左操作数还在栈里，不取出来了*/
				ItemBase::ItemType leftItem = calcStack.top();
				/*做类型检查*/
				if (rightItem != ItemBase::Value || leftItem != ItemBase::Value)
					return ExpressionError;
			}
			else
			{
				/*一元运算符*/
				if (calcStack.empty())//操作数不够
					return ExpressionError;
				ItemBase::ItemType item = calcStack.top();
				if (item != ItemBase::Value)
					return ExpressionError;
			}
			break;
		}
	}
	if (calcStack.size() == 1 && calcStack.top() == ItemBase::Value)
		return Succeed;
	return ExpressionError;
}

double Calculator::GetResult() const
{
	return m_prevResult;
}

double Calculator::CalculateBinaryOperator(BinaryOperator::BinaryOperatorType type, double left, double right)
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
			m_occurResult = MathError;
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

double Calculator::CalculateUnaryOperator(UnaryOperator::UnaryOperatorType type, double value)
{
	switch (type)
	{
	case UnaryOperator::Factorial:
		if (value < -1)
		{
			m_occurResult = MathError;
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

bool Calculator::IsZero(double value) const
{
	return value == 0.0;
}
