#pragma once

#include <string>
#include "ItemBase.h"

class ValueItem :public ItemBase
{
public:

	static const double VALUE_PI;
	static const double VALUE_E;

	ValueItem() = default;
	inline ValueItem(double value);
	inline ValueItem(const ValueItem&) = default;
	inline ValueItem(ValueItem&&) = default;
	inline ~ValueItem() = default;

	virtual inline ItemType GetType() const override;

	inline double& Value();

	inline virtual void Free() override;

private:
	double m_value = 0.0;

};
ValueItem::ValueItem(double value)
{
	m_value = value;
}

ValueItem::ItemType ValueItem::GetType() const
{
	return ItemType::Value;
}

double& ValueItem::Value()
{
	return m_value;
}

void ValueItem::Free()
{
	delete this;
}

class NoFreeValueItem :public ValueItem
{
	NoFreeValueItem() = default;
	inline NoFreeValueItem(double value);
	inline NoFreeValueItem(const NoFreeValueItem&) = default;
	inline NoFreeValueItem(NoFreeValueItem&&) = default;
	inline ~NoFreeValueItem() = default;

	virtual void Free() override {}
};
NoFreeValueItem::NoFreeValueItem(double value) :
	ValueItem(value)
{}
