#pragma once

#include <vector>

class IBeginStatement
{
public:

	virtual ~IBeginStatement() = default;

	virtual bool Execute(const std::vector<double>& args) = 0;
};
