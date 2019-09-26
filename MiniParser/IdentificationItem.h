#pragma once

#include <string>
#include "ItemBase.h"

class IdentificationItem :public ItemBase
{
public:

	enum IdentificationType : char
	{
		FunctionIDF,
		VariousIDF
	};
	
	IdentificationItem() = default;
	inline IdentificationItem(const std::string &name);
	IdentificationItem(const IdentificationItem&) = default;
	IdentificationItem(IdentificationItem&&) = default;
	~IdentificationItem() = default;
	
	virtual IdentificationType GetIdentificationType()const;

	virtual inline ItemType GetType() const override;

	inline const std::string &GetName()const;

	inline virtual void Save(std::ostream& out) override;

	inline virtual void Free() override;

private:

	std::string m_name;

};

IdentificationItem::IdentificationItem(const std::string &name):
	m_name(name)
{}

IdentificationItem::ItemType IdentificationItem::GetType() const
{
	return Identification;
}

const std::string &IdentificationItem::GetName()const
{
	return m_name;
}

void IdentificationItem::Save(std::ostream& out)
{
	out.put(Identification);
	//+++
}

void IdentificationItem::Free()
{
	delete this;
}