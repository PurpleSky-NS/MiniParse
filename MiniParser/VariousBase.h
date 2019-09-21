#pragma once

#include <string>
#include "IFreeable.h"

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