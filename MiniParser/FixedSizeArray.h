#pragma once

#include <vector>
#include <memory>
#include "Array.h"

class FixedSizeArray : public Array
{
public:

	inline FixedSizeArray(size_t size);
	inline FixedSizeArray(const std::vector<double>& initialValues);
	inline FixedSizeArray(const Array& array);
	/*size必须比初始化列表的长度大*/
	inline FixedSizeArray(size_t size, const std::vector<double>& initialValues);
	inline FixedSizeArray(size_t size, const Array& array);
	FixedSizeArray() = delete;
	FixedSizeArray(const FixedSizeArray&) = delete;
	FixedSizeArray(FixedSizeArray&&) = delete;
	inline ~FixedSizeArray();

	inline virtual ArrayItem& operator[](size_t idx)override;
	inline virtual const ArrayItem& operator[](size_t idx)const override;

	inline virtual bool Contains(double value)const override;
	inline virtual bool ContainsIf(std::function<bool(const ArrayItem& item)> judge)const override;

	inline virtual int IndexOf(double value)const override;
	inline virtual int IndexOf(std::function<bool(const ArrayItem& item)> judge)const override;

	inline virtual size_t Size()const override;

	inline virtual void Foreach(std::function<void(ArrayItem&)> Func)override;
	inline virtual void Foreach(std::function<void(ArrayItem&, size_t)> Func)override;

	inline virtual ArrayType GetArrayType()const override;

private:

	ArrayItem* m_values;
	size_t m_size;
};

FixedSizeArray::FixedSizeArray(size_t size)
{
	m_values = new ArrayItem[size];
	m_size = size;
	memset(m_values, 0, sizeof(ArrayItem) * size);
}
FixedSizeArray::FixedSizeArray(const std::vector<double>& initialValues)
{
	m_values = new ArrayItem[initialValues.size()];
	m_size = initialValues.size();
	for (size_t i = 0; i < initialValues.size(); ++i)
		m_values[i].value = initialValues[i];
}
FixedSizeArray::FixedSizeArray(const Array& array)
{
	m_values = new ArrayItem[array.Size()];
	m_size = array.Size();
	for (size_t i = 0; i < array.Size(); ++i)
		m_values[i].value = array[i].value;
}
FixedSizeArray::FixedSizeArray(size_t capacity, const std::vector<double>& initialValues)
	:FixedSizeArray(capacity)
{
	for (size_t i = 0; i < initialValues.size(); ++i)
		m_values[i].value = initialValues[i];
}
FixedSizeArray::FixedSizeArray(size_t capacity, const Array& array)
	: FixedSizeArray(capacity)
{
	for (size_t i = 0; i < array.Size(); ++i)
		m_values[i].value = array[i].value;
}
FixedSizeArray::~FixedSizeArray()
{
	delete[] m_values;
}
FixedSizeArray::ArrayItem& FixedSizeArray::operator[](size_t idx)
{
	return m_values[idx];
}
const FixedSizeArray::ArrayItem& FixedSizeArray::operator[](size_t idx)const
{
	return m_values[idx];
}
bool FixedSizeArray::Contains(double value)const
{
	for (size_t i = 0; i < m_size; ++i)
		if (m_values[i].value == value)
			return true;
	return false;
}
bool FixedSizeArray::ContainsIf(std::function<bool(const ArrayItem& item)> judge)const
{
	for (size_t i = 0; i < m_size; ++i)
		if (judge(m_values[i]))
			return true;
	return false;
}
int FixedSizeArray::IndexOf(double value)const
{
	for (size_t i = 0; i < m_size; ++i)
		if (m_values[i].value == value)
			return (int)i;
	return -1;
}
int FixedSizeArray::IndexOf(std::function<bool(const ArrayItem& item)> judge)const
{
	for (size_t i = 0; i < m_size; ++i)
		if (judge(m_values[i]))
			return (int)i;
	return -1;
}
size_t FixedSizeArray::Size()const
{
	return m_size;
}
void FixedSizeArray::Foreach(std::function<void(ArrayItem&)> Func)
{
	for (size_t i = 0; i < m_size; ++i)
		Func(m_values[i]);
}
void FixedSizeArray::Foreach(std::function<void(ArrayItem&, size_t)> Func)
{
	for (size_t i = 0; i < m_size; ++i)
		Func(m_values[i], i);
}

FixedSizeArray::ArrayType FixedSizeArray::GetArrayType() const
{
	return FixedSizeArray::ArrayType::FixedSizeArray;
}
