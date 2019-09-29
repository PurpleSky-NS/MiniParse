#pragma once

#include <vector>
#include "Statement.h"

class StatementBlocks : public Statement
{
public:

	inline ~StatementBlocks();

	inline void Add(Statement* statement);

	inline void Clear();

	inline virtual bool Excuse() override;

private:
	std::vector<Statement*> m_statementBlocks;
};

StatementBlocks::~StatementBlocks()
{
	Clear();
}

void StatementBlocks::Add(Statement* statement)
{
	m_statementBlocks.push_back(statement);
}

bool StatementBlocks::Excuse()
{
	for (auto i : m_statementBlocks)
		if (!i->Excuse())
			return false;
	return true;
}

void StatementBlocks::Clear()
{
	for (auto i : m_statementBlocks)
		delete i;
	m_statementBlocks.clear();
}
