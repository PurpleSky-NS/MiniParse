#pragma once

class VariousBase
{
public:

	enum VariousType : char
	{
		Various,
		Array
	};

	virtual ~VariousBase() = default;

	virtual VariousType GetType()const = 0;

};
