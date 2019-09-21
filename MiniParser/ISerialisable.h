#pragma once

#include <iostream>

class ISerialisable
{
	virtual void Save(std::ostream& out) = 0;

	virtual void Load(std::istream& in) = 0;
};