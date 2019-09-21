#pragma once

#include "ISerialisable.h"
#include "IFreeable.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"

class Statement : public ISerialisable,public IFreeable
{
public:

	virtual bool Excuse() = 0;

};