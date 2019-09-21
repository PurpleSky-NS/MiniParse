#pragma once

#include <string>
#include "Expression.h"

class InfixExpression : public Expression
{
public:
	inline InfixExpression() = default;
	/*中缀表达式字符串构造*/
	inline InfixExpression(const std::string &expression);
	InfixExpression(const InfixExpression&) = delete;
	InfixExpression(InfixExpression&&) = delete;
	~InfixExpression() = default;

};