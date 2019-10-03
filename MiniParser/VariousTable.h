#pragma once

#include <unordered_map>
#include <string>
#include "VariousBase.h"

class VariousTable
{
public:

	VariousTable() = default;
	VariousTable(const VariousTable&) = delete;
	VariousTable(VariousTable&&) = delete;
	~VariousTable() = default;

	inline void UpdateVarious(const std::string& name, VariousBase* various);

	/*没找到返回nullptr*/
	inline VariousBase* GetVarious(const std::string& name)const;

	inline void RemoveVarious(const std::string& name);

	inline bool ExistVarious(const std::string& name);

private:

	std::unordered_map<std::string, VariousBase*> m_variousMap;

};
void VariousTable::UpdateVarious(const std::string& name, VariousBase* various)
{
	m_variousMap.insert({ name, various });
}

VariousBase* VariousTable::GetVarious(const std::string& name) const
{
	auto fd = m_variousMap.find(name);
	if (fd == m_variousMap.end())
		return nullptr;
	return fd->second;
}

void VariousTable::RemoveVarious(const std::string& name)
{
	m_variousMap.erase(name);
}

bool VariousTable::ExistVarious(const std::string& name)
{
	return m_variousMap.find(name) != m_variousMap.end();
}
