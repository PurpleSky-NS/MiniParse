#pragma once

#include "IdentificationItem.h"

/*作为变量的标识符，仅作为标识符，应在表达式中将之替换为数值*/
class VariousIDF : public IdentificationItem
{
public:

	inline VariousIDF(const std::string& name);
	inline VariousIDF(const std::string& name, bool isNegSigned);
	inline VariousIDF(const VariousIDF&) = delete;
	inline VariousIDF(VariousIDF&&) = delete;
	inline ~VariousIDF() = default;

	inline bool& NegSigned();

	/*该变量是否数组元素*/
	inline bool IsArrayItem()const;

	/*将该变量标识为数组元素*/
	inline void SetToArrayItem(bool isArrayItem);

	inline ExpressionType& ArrayPosExpression();

	inline virtual IdentificationType GetIdentificationType()const override;

	inline virtual void Free() override;

private:

	/*是否是相反数*/
	bool m_isNegSigned = false;

	bool m_isArrayItem = false;
	ExpressionType m_arrPosExp;//数组下标表达式
};

VariousIDF::VariousIDF(const std::string& name) :
	IdentificationItem(name)
{}

VariousIDF::VariousIDF(const std::string& name, bool isNegSigned) :
	VariousIDF(name)
{
	m_isNegSigned = isNegSigned;
}

bool& VariousIDF::NegSigned()
{
	return m_isNegSigned;
}

bool VariousIDF::IsArrayItem() const
{
	return m_isArrayItem;
}

void VariousIDF::SetToArrayItem(bool isArrayItem)
{
	m_isArrayItem = isArrayItem;
}

ExpressionType& VariousIDF::ArrayPosExpression()
{
	return m_arrPosExp;
}

VariousIDF::IdentificationType VariousIDF::GetIdentificationType() const
{
	return IdentificationType::VariousIDF;
}

void VariousIDF::Free()
{
	delete this;
}
