#pragma once

#include <string>
#include "ItemBase.h"

class ValueItem :public ItemBase
{
public:
	virtual inline ItemType GetType() const override;

	inline double& GetValue();

private:
	double m_value;

};
ValueItem::ItemType ValueItem::GetType() const
{
	return Value;
}

double& ValueItem::GetValue()
{
	return m_value;
}
