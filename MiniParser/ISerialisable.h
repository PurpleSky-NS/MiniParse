#pragma once

#include <ostream>

class ISavable
{
public:
	virtual void Save(std::ostream& out) = 0;
};