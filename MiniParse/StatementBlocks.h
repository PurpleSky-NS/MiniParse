#pragma once

#include <vector>
#include "Statement.h"

class StatementBlocks : public Statement
{
public:

	StatementBlocks();
	~StatementBlocks();

	inline void Add(Statement *statement);

	/*��������Լ���Free��ֻ��������������Free�����vector*/
	void Clear();

	inline virtual void Excuse() override;

	inline virtual void Save(std::ofstream & out) override;

	inline virtual void Load(std::ifstream & in) override;

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

void StatementBlocks::Save(std::ofstream &out) 
{
	for (auto i : m_statementBlocks)
		i->Save(out);
}

void StatementBlocks::Load(std::ifstream &in)
{
	for (auto i : m_statementBlocks)
		i->Load(in);
}

void StatementBlocks::Free()
{
	delete this;
}