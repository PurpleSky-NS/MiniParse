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
	inline IdentificationItem(const std::string& name);
	IdentificationItem(const IdentificationItem&) = default;
	IdentificationItem(IdentificationItem&&) = default;
	~IdentificationItem() = default;

	virtual IdentificationType GetIdentificationType()const = 0;

	virtual inline ItemType GetType() const override;

	inline std::string& GetName();
	inline const std::string& GetName()const;

	inline virtual void Free() override;

protected:

	std::string m_name;

};

IdentificationItem::IdentificationItem(const std::string& name) :
	m_name(name)
{}

IdentificationItem::ItemType IdentificationItem::GetType() const
{
	return Identification;
}

std::string& IdentificationItem::GetName()
{
	return m_name;
}

const std::string& IdentificationItem::GetName()const
{
	return m_name;
}

void IdentificationItem::Free()
{
	delete this;
}
