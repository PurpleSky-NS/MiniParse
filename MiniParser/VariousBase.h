#pragma once

class VariousBase
{
public:

	enum VariousType : char
	{
		Various,
		Array
	};

	virtual VariousType GetType()const = 0;

};
