#pragma once

#include <string>

class VariousBase
{
public:

	enum VariousType :unsigned char
	{
		Various,
		Array
	};

	virtual VariousType GetType()const = 0;

	/*不会进行delete操作，但会使用Free接口表明该对象不会再使用*/
	virtual void Free() = 0;

protected:
	VariousBase() = default;
	VariousBase(const VariousBase &) = delete;
	VariousBase(VariousBase &&) = delete;

};