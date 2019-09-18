#pragma once

#include <unordered_map>
#include <string>
#include "VariousBase.h"

class VariousTable
{
public:

	inline void UpdateVarious(const std::string &name, VariousBase *various);

	inline VariousBase *GetVarious(const std::string &name)const;

private:
	std::unordered_map<std::string, VariousBase*> m_variousMap;

};
void VariousTable::UpdateVarious(const std::string &name, VariousBase *various)
{
	auto fd = m_variousMap.find(name);
	if (fd != m_variousMap.end())
		fd->second->Free();
	m_variousMap.insert({ name, various });
}

VariousBase *VariousTable::GetVarious(const std::string &name) const
{
	auto fd = m_variousMap.find(name);
	if (fd != m_variousMap.end())
		return nullptr;
	return fd->second;
}
