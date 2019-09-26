#pragma once

#include <vector>
#include "IdentificationItem.h"

/*作为函数的标识符*/
class FunctionIDF : public IdentificationItem
{
public:

	typedef std::vector<ItemBase*> ParamType;

	FunctionIDF() = delete;
	inline FunctionIDF(const std::string& name);
	inline FunctionIDF(const FunctionIDF&) = delete;
	inline FunctionIDF(FunctionIDF&&) = delete;
	inline ~FunctionIDF() = default;

	inline std::vector<ParamType>& Params();
	inline const std::vector<ParamType>& Params()const;

	inline virtual IdentificationType GetIdentificationType()const override;

	inline virtual void Save(std::ostream& out) override;

	inline virtual void Free() override;

private:

	std::vector<ParamType> m_params;

};

FunctionIDF::FunctionIDF(const std::string& name) :
	IdentificationItem(name)
{}

std::vector<FunctionIDF::ParamType>& FunctionIDF::Params()
{
	return m_params;
}

const std::vector<FunctionIDF::ParamType>& FunctionIDF::Params()const
{
	return m_params;
}

FunctionIDF::IdentificationType FunctionIDF::GetIdentificationType() const
{
	return IdentificationType::FunctionIDF;
}

void FunctionIDF::Save(std::ostream& out)
{
	out.put(IdentificationType::FunctionIDF);
	//Save
}

void FunctionIDF::Free()
{
	for (auto i : m_params)
		for (auto item : i)
			item->Free();
	delete this;
}
