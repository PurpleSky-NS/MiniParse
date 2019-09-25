#include "StatementBlocks.h"
StatementBlocks::~StatementBlocks()
{
	Clear();
}

void StatementBlocks::Clear()
{
	m_statementBlocks.clear();
}
