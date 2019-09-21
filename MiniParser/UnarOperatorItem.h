#pragma once

#include "OperatorItem.h"

class UnarOperator : public OperatorItem
{
public:
	enum UnarOperatorType : char
	{
		Factorial,	//!
		Lg,			//lg
		Ln,			//ln
		Sin,		//sin
		Cos,		//cos
		Tan,		//tan
		Arcsin,		//arcsin
		Arccos,		//arccos
		Arctan		//arctan
	};

	inline UnarOperator() = default;
	inline UnarOperator(UnarOperatorType type);
	inline UnarOperator(const UnarOperator&) = default;
	inline UnarOperator(UnarOperator&&) = default;
	inline ~UnarOperator() = default;

	virtual inline OperatorType GetOperatorType() const override;

	inline UnarOperatorType GetUnarOperatorType()const;

	inline void SetUnarOperatorType(UnarOperatorType type);

private:

	UnarOperatorType m_type;

};
UnarOperator::UnarOperator(UnarOperatorType type)
{
	m_type = type;
}
UnarOperator::OperatorType UnarOperator::GetOperatorType() const
{
	return OperatorType::UnarOperator;
}

UnarOperator::UnarOperatorType UnarOperator::GetUnarOperatorType() const
{
	return m_type;
}

void UnarOperator::SetUnarOperatorType(UnarOperatorType type)
{
	m_type = type;
}
