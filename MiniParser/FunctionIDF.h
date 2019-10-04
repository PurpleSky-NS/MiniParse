#pragma once

#include "Expression.h"
#include "IdentificationItem.h"

/*作为函数的标识符*/
class FunctionIDF : public IdentificationItem
{
public:

	FunctionIDF() = default;
	inline FunctionIDF(const std::string& name);
	FunctionIDF(const FunctionIDF&) = delete;
	FunctionIDF(FunctionIDF&&) = delete;
	inline ~FunctionIDF();

	inline std::vector<ExpressionType>& Params();
	inline const std::vector<ExpressionType>& Params()const;

	inline virtual IdentificationType GetIdentificationType()const override;

	inline virtual void Clear() override;

	inline virtual void Free() override;

private:

	std::vector<ExpressionType> m_params;

};

FunctionIDF::FunctionIDF(const std::string& name) :
	IdentificationItem(name)
{}

FunctionIDF::~FunctionIDF()
{
	Clear();
}

std::vector<ExpressionType>& FunctionIDF::Params()
{
	return m_params;
}

const std::vector<ExpressionType>& FunctionIDF::Params()const
{
	return m_params;
}

FunctionIDF::IdentificationType FunctionIDF::GetIdentificationType() const
{
	return IdentificationType::FunctionIDF;
}

void FunctionIDF::Clear()
{
	IdentificationItem::Clear();
	for (auto& i : m_params)
		for (auto& item : i)
			item->Free();
}

void FunctionIDF::Free()
{
	Clear();
	delete this;
}
