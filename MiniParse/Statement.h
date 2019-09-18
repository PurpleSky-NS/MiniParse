#pragma once

#include <fstream>

class Statement
{
public:

	virtual void Excuse() = 0;

	virtual void Save(std::ofstream &out) = 0;

	virtual void Load(std::ifstream &in) = 0;

	virtual void Free() = 0;

};