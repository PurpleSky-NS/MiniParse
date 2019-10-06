#pragma once

#include <vector>
#include <functional>
#include "VariousBase.h"

class Array : public VariousBase
{
public:

	Array() = default;
	inline Array(unsigned capacity);
	inline Array(unsigned capacity, const std::vector<double>& initialValues);
	inline Array(const std::vector<double>& initialValues);
	inline Array(std::vector<double>&& initialValues);
	Array(const Array&) = default;
	Array(Array&&) = default;
	~Array() = default;

	/*替换全部*/
	inline void Replace(unsigned capacity);
	/*容量要大于等于列表*/
	inline void Replace(unsigned capacity, const std::vector<double>& initialValues);
	inline void Replace(const std::vector<double>& initialValues);
	inline void Replace(std::vector<double>&& initialValues);

	/*加末尾*/
	inline void Add(double value);
	/*加任意位置*/
	inline void Add(double value, size_t pos);

	/*删末尾*/
	inline void RemoveLast();
	/*删任意位置*/
	inline void Remove(size_t pos);
	inline void Remove(size_t pos, size_t size);
	/*删符合条件的*/
	inline bool RemoveIf(std::function<bool(const double& item)> judge);//删一个
	inline bool RemoveRangeIf(std::function<bool(const double& item)> judge);//删一堆

	inline void Clear();

	inline double& operator[](size_t idx);
	inline const double& operator[](size_t idx)const;

	inline bool Contains(double value) const;
	inline bool ContainsIf(std::function<bool(const double& item)> judge) const;

	inline int IndexOf(double value) const;
	inline int IndexOf(std::function<bool(const double& item)> judge) const;

	inline size_t Size() const;

	inline void Foreach(std::function<void(double&)> Func);
	inline void Foreach(std::function<void(double&, size_t)> Func);

	/*比较两个数组，当且仅当大小和每个位置对应的变量都相同时才会为true*/
	inline bool operator==(const Array& array)const;

	inline virtual VariousType GetType()const override;

private:

	std::vector<double> m_values;
};
Array::Array(unsigned capacity)
{
	Replace(capacity);
}
Array::Array(unsigned capacity, const std::vector<double>& initialValues)
{
	Replace(capacity, initialValues);
}
Array::Array(const std::vector<double>& initialValues)
{
	m_values = initialValues;
}
Array::Array(std::vector<double>&& initialValues)
{
	m_values = std::move(initialValues);
}
void Array::Replace(unsigned capacity)
{
	m_values.assign(capacity, 0.0);
}
void Array::Replace(unsigned capacity, const std::vector<double>& initialValues)
{
	m_values.assign(initialValues.begin(), initialValues.end());
	m_values.resize(capacity, 0.0);
}
void Array::Replace(const std::vector<double>& initialValues)
{
	m_values = initialValues;
}
void Array::Replace(std::vector<double>&& initialValues)
{
	m_values = std::move(initialValues);
}
void Array::Add(double value)
{
	m_values.push_back(value);
}
void Array::Add(double value, size_t pos)
{
	m_values.insert(m_values.begin() + pos, value);
}
void Array::RemoveLast()
{
	m_values.pop_back();
}
void Array::Remove(size_t pos)
{
	m_values.erase(m_values.begin() + pos);
}
void Array::Remove(size_t pos, size_t size)
{
	m_values.erase(m_values.begin() + pos, m_values.begin() + pos + size);
}
bool Array::RemoveIf(std::function<bool(const double& item)> judge)
{
	for (int i = 0; i < m_values.size(); ++i)
		if (judge(m_values[i]))
		{
			m_values.erase(m_values.begin() + i);
			return true;
		}
	return false;
}
bool Array::RemoveRangeIf(std::function<bool(const double& item)> judge)
{
	bool isDeleted = false;
	for (int i = 0; i < m_values.size(); ++i)
		if (judge(m_values[i]))
		{
			m_values.erase(m_values.begin() + i--);
			isDeleted = true;
		}
	return isDeleted;
}
inline void Array::Clear()
{
	m_values.clear();
}
double& Array::operator[](size_t idx)
{
	return m_values[idx];
}
const double& Array::operator[](size_t idx) const
{
	return m_values[idx];
}
bool Array::Contains(double value) const
{
	for (auto& i : m_values)
		if (i == value)
			return true;
	return false;
}
bool Array::ContainsIf(std::function<bool(const double& item)> judge) const
{
	for (auto& i : m_values)
		if (judge(i))
			return true;
	return false;
}
int Array::IndexOf(double value)const
{
	for (size_t i = 0; i < m_values.size(); ++i)
		if (m_values[i] == value)
			return (int)i;
	return -1;
}
int Array::IndexOf(std::function<bool(const double& item)> judge)const
{
	for (size_t i = 0; i < m_values.size(); ++i)
		if (judge(m_values[i]))
			return (int)i;
	return -1;
}
size_t Array::Size() const
{
	return m_values.size();
}
void Array::Foreach(std::function<void(double&)> Func)
{
	for (auto& i : m_values)
		Func(i);
}
void Array::Foreach(std::function<void(double&, size_t)> Func)
{
	for (size_t i = 0; i < m_values.size(); ++i)
		Func(m_values[i], i);
}
bool Array::operator==(const Array& array)const
{
	if (Size() != array.Size())
		return false;
	for (size_t i = 0; i < Size(); ++i)
		if ((*this)[i] != array[i])
			return false;
	return true;
}
Array::VariousType Array::GetType() const
{
	return VariousType::Array;
}
