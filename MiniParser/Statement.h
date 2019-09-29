#pragma once

#include <iostream>
#include "ParserError.h"

class Statement
{
public:

	enum StatementType :char
	{
		AssignStatement
	};

	virtual bool Check() = 0;

	virtual bool Excuse() = 0;

	virtual StatementType GetType()const = 0;

	virtual void Save(std::ostream* o)const = 0;

	virtual bool Load(std::istream* o) = 0;

protected:



};
