#pragma once

#include <vector>
#include "StatementBase.h"

class StatementBlocks : public StatementBase
{
public:

	inline ~StatementBlocks();

	inline void Add(StatementBase* statement);

	inline void Clear();

	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual StatementType GetType() const override;

	inline virtual void Save(std::ostream& out) const override;

	inline virtual void Load(std::istream& in) override;

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

bool StatementBlocks::Check()
{
	for (auto& i : m_statementBlocks)
		if (!i->Check())
			return false;
	return true;
}

bool StatementBlocks::DynamicCheck()
{
	for (auto& i : m_statementBlocks)
		if (!i->DynamicCheck())
			return false;
	return true;
}

bool StatementBlocks::Execute()
{
	for (auto& i : m_statementBlocks)
		if (!i->Execute())
			return false;
	return true;
}

StatementBase::StatementType StatementBlocks::GetType() const
{
	return StatementType::Blocks;
}

void StatementBlocks::Save(std::ostream& out) const
{
}

void StatementBlocks::Load(std::istream& in)
{
}

void StatementBlocks::Clear()
{
	for (auto& i : m_statementBlocks)
		delete i;
	m_statementBlocks.clear();
}
