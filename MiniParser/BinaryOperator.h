#pragma once

#include "OperatorItem.h"

class BinaryOperator : public OperatorItem
{
public:

	enum BinaryOperatorType : char
	{
		Add = 0,		//+
		Subtract,		//-
		Multiply,		//*
		Divide,			///
		Mod,			//%
		Power,          //^
		Count
	};

	static BinaryOperator* GetBinaryOperator(BinaryOperatorType type);

	inline void SetBinaryOperatorType(BinaryOperatorType type);

	inline BinaryOperatorType GetBinaryOperatorType()const;

	virtual inline OperatorType GetOperatorType() const override;

	virtual inline void Save(std::ostream& out) override;

private:

	static BinaryOperator operators[Count];

	inline BinaryOperator() = default;
	inline BinaryOperator(BinaryOperatorType type);
	inline BinaryOperator(const BinaryOperator&) = default;
	inline BinaryOperator(BinaryOperator&&) = default;
	inline ~BinaryOperator() = default;

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

void BinaryOperator::SetBinaryOperatorType(BinaryOperatorType type)
{
	m_type = type;
}

BinaryOperator::BinaryOperatorType BinaryOperator::GetBinaryOperatorType() const
{
	return m_type;
}

void BinaryOperator::Save(std::ostream& out)
{
	OperatorItem::Save(out);
	out.put(OperatorType::BinaryOperator);
	out.put(m_type);
}
