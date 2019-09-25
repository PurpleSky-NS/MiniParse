#pragma once

#include "ISavable.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"

class Statement : public ISavable
{
public:

	virtual bool Excuse() = 0;

};
