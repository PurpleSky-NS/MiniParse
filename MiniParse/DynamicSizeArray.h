#pragma once

#include <vector>
#include "Array.h"

class DynamicSizeArray : public Array
{
public:

	static DynamicSizeArray *GetDynamicSizeArray();
	static DynamicSizeArray *GetDynamicSizeArray(const std::vector<double> &initialValues);

	static void FreeDynamicSizeArray(DynamicSizeArray *array);

	inline virtual ArrayItem & operator[](unsigned idx) override;
	inline virtual const ArrayItem & operator[](unsigned idx)const override;

	inline virtual bool Contains(double value) const override;

	inline virtual unsigned Size() const override;

	inline virtual void Foreach(std::function<void(ArrayItem&)> Func) override;
	inline virtual void Foreach(std::function<void(ArrayItem&, unsigned)> Func) override;

	inline virtual void Free() override;

	inline virtual ArrayType GetArrayType()const override;

private:

	std::vector<ArrayItem> m_values;

	inline DynamicSizeArray();
	inline DynamicSizeArray(const std::vector<double> &initialValues);
	DynamicSizeArray(const DynamicSizeArray &) = delete;
	DynamicSizeArray(DynamicSizeArray&&) = delete;
	~DynamicSizeArray() = default;
};
DynamicSizeArray::DynamicSizeArray()
{}
DynamicSizeArray::DynamicSizeArray(const std::vector<double>& initialValues)
{
	m_values.reserve(initialValues.size());
	for (auto i : initialValues)
		m_values.push_back({ i });
}
DynamicSizeArray::ArrayItem &DynamicSizeArray::operator[](unsigned idx)
{
	return m_values[idx];
}
const DynamicSizeArray::ArrayItem &DynamicSizeArray::operator[](unsigned idx) const
{
	return m_values[idx];
}
bool DynamicSizeArray::Contains(double value) const
{
	for (auto i : m_values)
		if (i.value == value)
			return true;
	return false;
}
unsigned DynamicSizeArray::Size() const
{
	return m_values.size();
}
void DynamicSizeArray::Foreach(std::function<void(ArrayItem&)> Func)
{
	for (auto i : m_values)
		Func(i);
}
void DynamicSizeArray::Foreach(std::function<void(ArrayItem&, unsigned)> Func)
{
	for (unsigned i = 0; i < m_values.size(); ++i)
		Func(m_values[i], i);
}
void DynamicSizeArray::Free()
{
	FreeDynamicSizeArray(this);
}

DynamicSizeArray::ArrayType DynamicSizeArray::GetArrayType() const
{
	return DynamicSizeArray::ArrayType::DynamicSizeArray;
}
