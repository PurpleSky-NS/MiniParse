#pragma once

#include "ISavable.h"
#include "IFreeable.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"

class Statement : public ISavable,public IFreeable
{
public:

	virtual bool Excuse() = 0;

};