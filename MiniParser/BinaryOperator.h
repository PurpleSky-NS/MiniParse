#pragma once
#include "OperatorItem.h"
class BinaryOperator : public OperatorItem
{
public:
	enum BinaryOperatorType : char
	{
		Add,		//+
		Subtract,	//-
		Multiply,	//*
		Divide,		///
		Mod,		//%
	};

private:

	inline BinaryOperator() = default;
	inline BinaryOperator(BinaryOperatorType type);
	inline BinaryOperator(const BinaryOperator&) = default;
	inline BinaryOperator(BinaryOperator&&) = default;
	inline ~BinaryOperator() = default;

	virtual inline OperatorType GetOperatorType() const override;

	inline BinaryOperatorType GetBinaryOperatorType()const;

	inline void SetBinaryOperatorType(BinaryOperatorType type);

private:

	BinaryOperatorType m_type;
};

BinaryOperator::BinaryOperator(BinaryOperator::BinaryOperatorType type)
{
	m_type = type;
}

BinaryOperator::OperatorType BinaryOperator::GetOperatorType() const
{
	return OperatorType::BinaryOperator;
}

BinaryOperator::BinaryOperatorType BinaryOperator::GetBinaryOperatorType() const
{
	return m_type;
}

void BinaryOperator::SetBinaryOperatorType(BinaryOperatorType type)
{
	m_type = type;
}
