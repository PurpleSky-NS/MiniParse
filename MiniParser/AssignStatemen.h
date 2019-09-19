#pragma once

#include <functional>
#include "VariousTable.h"
#include "Statement.h"

class AssignStatemen :public Statement
{
public:
	AssignStatemen();
	~AssignStatemen();

	inline virtual void Excuse() override;

	virtual void Save(std::ostream &out) override;

	virtual void Load(std::istream &in) override;

	inline virtual void Free() override;

private:
	std::string m_valueName;
	PostfixExpression m_expression;
};
void AssignStatemen::Excuse()
{
}

void AssignStatemen::Free()
{
}