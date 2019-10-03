#pragma once

#include <list>
#include "VariousBase.h"

class Various : public VariousBase
{
public:

	Various() = default;
	inline Various(double initialValue);
	Various(const Various& various) = delete;
	Various(Various&&) = delete;
	~Various() = default;

	inline double& GetValue();

	inline virtual VariousType GetType() const override;

	inline Various& operator=(const Various& various);
	inline Various& operator=(double constant);
	inline bool operator==(const Various& various)const;
	inline bool operator==(double constant)const;
	inline bool operator!=(const Various& various)const;
	inline bool operator!=(double constant)const;
	inline bool operator>(const Various& various)const;
	inline bool operator>(double constant)const;
	inline bool operator<(const Various& various)const;
	inline bool operator<(double constant)const;
	inline bool operator>=(const Various& various)const;
	inline bool operator>=(double constant)const;
	inline bool operator<=(const Various& various)const;
	inline bool operator<=(double constant)const;

private:

	double m_value;

};
Various::Various(double initialValue)
{
	m_value = initialValue;
}
double& Various::GetValue()
{
	return m_value;
}
Various::VariousType Various::GetType() const
{
	return Various::VariousType::Various;
}
Various& Various::operator=(const Various& various)
{
	m_value = various.m_value;
	return *this;
}
Various& Various::operator=(double constant)
{
	m_value = constant;
	return *this;
}
bool Various::operator==(const Various& various)const
{
	return m_value == various.m_value;
}
bool Various::operator==(double constant)const
{
	return m_value == constant;
}
bool Various::operator!=(const Various& various)const
{
	return m_value != various.m_value;
}
bool Various::operator!=(double constant)const
{
	return m_value != constant;
}
bool Various::operator>(const Various& various)const
{
	return m_value > various.m_value;
}
bool Various::operator>(double constant)const
{
	return m_value > constant;
}
bool Various::operator<(const Various& various)const
{
	return m_value < various.m_value;
}
bool Various::operator<(double constant)const
{
	return m_value < constant;
}
bool Various::operator>=(const Various& various)const
{
	return m_value >= various.m_value;
}
bool Various::operator>=(double constant)const
{
	return m_value >= constant;
}
bool Various::operator<=(const Various& various)const
{
	return m_value <= various.m_value;
}
bool Various::operator<=(double constant)const
{
	return m_value <= constant;
}
