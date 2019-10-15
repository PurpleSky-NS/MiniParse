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

	/*不检查是否存在，没有的话就是OOR异常*/
	inline VariousBase* GetVarious(const std::string& name)const;

	inline void RemoveVarious(const std::string& name);

	inline bool ExistVarious(const std::string& name);

	inline void Clear();

private:

	std::unordered_map<std::string, VariousBase*> m_variousMap;

};
void VariousTable::UpdateVarious(const std::string& name, VariousBase* various)
{
	m_variousMap[name] = various;
}

VariousBase* VariousTable::GetVarious(const std::string& name) const
{
	return m_variousMap.at(name);
}

void VariousTable::RemoveVarious(const std::string& name)
{
	m_variousMap.erase(name);
}

bool VariousTable::ExistVarious(const std::string& name)
{
	return m_variousMap.find(name) != m_variousMap.end();
}

inline void VariousTable::Clear()
{
	m_variousMap.clear();
}
