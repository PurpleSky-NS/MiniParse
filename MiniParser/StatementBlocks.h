#pragma once

#include <vector>
#include "Statement.h"

class StatementBlocks : public Statement
{
public:

	StatementBlocks() = default;
	~StatementBlocks();

	inline void Add(Statement *statement);

	/*不会调用自己的Free，只会调用子语句对象的Free并清空vector*/
	void Clear();

	inline virtual void Excuse() override;

	inline virtual void Save(std::ostream & out) override;

	inline virtual void Load(std::istream & in) override;

	inline virtual void Free();

private:
	std::vector<Statement*> m_statementBlocks;
};

void StatementBlocks::Add(Statement *statement)
{
	m_statementBlocks.push_back(statement);
}

void StatementBlocks::Excuse()
{
	for (auto i : m_statementBlocks)
		i->Excuse();
}

void StatementBlocks::Save(std::ostream &out) 
{
	for (auto i : m_statementBlocks)
		i->Save(out);
}

void StatementBlocks::Load(std::istream &in)
{
	for (auto i : m_statementBlocks)
		i->Load(in);
}

void StatementBlocks::Free()
{
	delete this;
}