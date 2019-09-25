#pragma once

#include <string>
#include "ItemBase.h"

class ValueItem :public ItemBase
{
public:

	ValueItem() = default;
	inline ValueItem(double value);
	inline ValueItem(const ValueItem&) = default;
	inline ValueItem(ValueItem&&) = default;
	inline ~ValueItem() = default;

	virtual inline ItemType GetType() const override;

	inline double& GetValue();

	inline virtual void Save(std::ostream& out) override;

	inline virtual void Free() override;

private:
	double m_value;

};
ValueItem::ValueItem(double value)
{
	m_value = value;
}

ValueItem::ItemType ValueItem::GetType() const
{
	return Value;
}

double& ValueItem::GetValue()
{
	return m_value;
}

void ValueItem::Save(std::ostream& out)
{
	out.put(Value);
	out.write((const char*)& m_value, sizeof(m_value));
}

void ValueItem::Free()
{
	delete this;
}
