#pragma once

#include <vector>
#include <functional>
#include "Array.h"

class DynamicSizeArray : public Array
{
public:

	static DynamicSizeArray *GetDynamicSizeArray();
	static DynamicSizeArray *GetDynamicSizeArray(const Array &array);
	static DynamicSizeArray *GetDynamicSizeArray(const std::vector<double> &initialValues);

	static void FreeDynamicSizeArray(DynamicSizeArray *array);
	
	/*加末尾*/
	inline void Add(double value);
	/*加任意位置*/
	inline void Add(double value,unsigned pos);
	
	/*删末尾*/
	inline void RemoveLast();
	/*删任意位置*/
	inline void Remove(unsigned pos);
	inline void Remove(unsigned pos, unsigned size);
	/*删符合条件的*/
	inline bool RemoveIf(std::function<bool (const ArrayItem &item)> judge);//删一个
	inline bool RemoveRangeIf(std::function<bool (const ArrayItem &item)> judge);//删一堆

	inline virtual ArrayItem &operator[](unsigned idx) override;
	inline virtual const ArrayItem &operator[](unsigned idx)const override;

	inline virtual bool Contains(double value) const override;
	inline virtual bool ContainsIf(std::function<bool (const ArrayItem &item)> judge) const override;
	
	inline virtual int IndexOf(double value) const override;
	inline virtual int IndexOf(std::function<bool (const ArrayItem &item)> judge) const override;
	
	inline virtual unsigned Size() const override;

	inline virtual void Foreach(std::function<void(ArrayItem&)> Func) override;
	inline virtual void Foreach(std::function<void(ArrayItem&, unsigned)> Func) override;

	inline virtual void Free() override;

	inline virtual ArrayType GetArrayType()const override;

private:

	std::vector<ArrayItem> m_values;

	inline DynamicSizeArray();
	inline DynamicSizeArray(const std::vector<double> &initialValues);
	inline DynamicSizeArray(const Array &array);
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
DynamicSizeArray::DynamicSizeArray(const Array &array)
{
	m_values.reserve(array.Size());
	for (int i=0;i<array.Size();++i)
		m_values.push_back(array[i]);
}
DynamicSizeArray::ArrayItem &DynamicSizeArray::operator[](unsigned idx)
{
	return m_values[idx];
}
const DynamicSizeArray::ArrayItem &DynamicSizeArray::operator[](unsigned idx) const
{
	return m_values[idx];
}
void DynamicSizeArray::Add(double value)
{
	m_values.push_back({value});
}
void DynamicSizeArray::Add(double value,unsigned pos)
{
	m_values.insert(m_values.begin()+pos,{value});
}
void DynamicSizeArray::RemoveLast()
{
	m_values.pop_back();
}
void DynamicSizeArray::Remove(unsigned pos)
{
	m_values.erase(m_values.begin()+pos);
}
void DynamicSizeArray::Remove(unsigned pos, unsigned size)
{
	m_values.erase(m_values.begin() + pos, m_values.begin() + pos + size);
}
bool DynamicSizeArray::RemoveIf(std::function<bool (const ArrayItem &item)> judge)
{
	for(int i=0;i<m_values.size();++i)
		if(judge(m_values[i]))
		{
			m_values.erase(m_values.begin()+i);
			return true;
		}
	return false;
}
bool DynamicSizeArray::RemoveRangeIf(std::function<bool (const ArrayItem &item)> judge)
{
	bool isDeleted=false;
	for(int i=0;i<m_values.size();++i)
		if(judge(m_values[i]))
		{
			m_values.erase(m_values.begin()+i--);
			isDeleted = true;
		}
	return isDeleted;
}
bool DynamicSizeArray::Contains(double value) const
{
	for (auto i : m_values)
		if (i.value == value)
			return true;
	return false;
}
bool DynamicSizeArray::ContainsIf(std::function<bool (const ArrayItem &item)> judge) const
{
	for (auto i : m_values)
		if (judge(i))
			return true;
	return false;
}
int DynamicSizeArray::IndexOf(double value)const
{
	for(unsigned i=0;i<m_values.size();++i)
		if(m_values[i].value==value)
			return (int)i;
	return -1;
}
int DynamicSizeArray::IndexOf(std::function<bool (const ArrayItem &item)> judge)const
{
	for(unsigned i=0;i<m_values.size();++i)
		if(judge(m_values[i]))
			return (int)i;
	return -1;
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