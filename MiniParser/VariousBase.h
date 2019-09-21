#pragma once

#include <string>

class VariousBase :public IFreeable
{
public:

	enum VariousType :unsigned char
	{
		Various,
		Array
	};

	virtual VariousType GetType()const = 0;

protected:
	VariousBase() = default;
	VariousBase(const VariousBase &) = delete;
	VariousBase(VariousBase &&) = delete;

};