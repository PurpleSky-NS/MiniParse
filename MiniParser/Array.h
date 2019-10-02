#pragma once

#include <functional>
#include "VariousBase.h"

class Array : public VariousBase
{
public:

	enum ArrayType
	{
		FixedSizeArray,
		DynamicSizeArray
	};

	struct ArrayItem
	{
		double value;
	};

	/*数组的随机访问要高效*/
	virtual ArrayItem& operator[](size_t idx) = 0;
	virtual const ArrayItem& operator[](size_t idx)const = 0;

	virtual bool Contains(double value)const = 0;
	virtual bool ContainsIf(std::function<bool(const ArrayItem&)> judge) const = 0;

	/*没有返回-1*/
	virtual int IndexOf(double value)const = 0;
	virtual int IndexOf(std::function<bool(const ArrayItem&)> judge)const = 0;

	/*数组的获取大小要高效*/
	virtual size_t Size()const = 0;

	virtual void Foreach(std::function<void(ArrayItem&)> Func) = 0;
	virtual void Foreach(std::function<void(ArrayItem&, size_t)> Func) = 0;

	/*比较两个数组，当且仅当大小和每个位置对应的变量都相同时才会为true*/
	inline virtual bool operator==(const Array& array)const;

	inline virtual VariousType GetType() const override;

	virtual ArrayType GetArrayType()const = 0;

};
bool Array::operator==(const Array& array)const
{
	if (Size() != array.Size())
		return false;
	for (size_t i = 0; i < Size(); ++i)
		if ((*this)[i].value != array[i].value)
			return false;
	return true;
}

Array::VariousType Array::GetType() const
{
	return Array::VariousType::Array;
}
