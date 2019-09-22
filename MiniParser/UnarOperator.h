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
		Arctan,		//arctan
		Count
	};

	static UnarOperator* GetUnarOperator(UnarOperatorType type);

	inline void SetUnarOperatorType(UnarOperatorType type);

	inline UnarOperatorType GetUnarOperatorType()const;

	virtual inline OperatorType GetOperatorType() const override;

	virtual inline void Save(std::ostream& out) override;

	virtual void Free()override {}

private:

	static UnarOperator operators[Count];

	inline UnarOperator() = default;
	inline UnarOperator(UnarOperatorType type);
	inline UnarOperator(const UnarOperator&) = default;
	inline UnarOperator(UnarOperator&&) = default;
	inline ~UnarOperator() = default;

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

void UnarOperator::SetUnarOperatorType(UnarOperatorType type)
{
	m_type = type;
}

UnarOperator::UnarOperatorType UnarOperator::GetUnarOperatorType() const
{
	return m_type;
}

void UnarOperator::Save(std::ostream& out)
{
	OperatorItem::Save(out);
	out.put(OperatorType::UnarOperator);
	out.put(m_type);
}