#pragma once

#include <vector>
#include "StatementBase.h"

class StatementBlocks : public StatementBase
{
public:

	inline ~StatementBlocks();

	inline void Add(StatementBase* statement);

	inline void Clear();

	inline virtual bool Execute() override;

private:
	std::vector<StatementBase*> m_statementBlocks;
};

StatementBlocks::~StatementBlocks()
{
	Clear();
}

void StatementBlocks::Add(StatementBase* statement)
{
	m_statementBlocks.push_back(statement);
}

bool StatementBlocks::Execute()
{
	for (auto i : m_statementBlocks)
		if (!i->Execute())
			return false;
	return true;
}

void StatementBlocks::Clear()
{
	for (auto i : m_statementBlocks)
		delete i;
	m_statementBlocks.clear();
}
