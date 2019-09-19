#include "StatementBlocks.h"
StatementBlocks::~StatementBlocks()
{
	Clear();
}

void StatementBlocks::Clear()
{
	for (auto i : m_statementBlocks)
		i->Free();
	m_statementBlocks.clear();
}