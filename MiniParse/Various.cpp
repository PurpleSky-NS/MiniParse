#include "Various.h"
std::list<Various*> Various::m_variousPool;
Various *Various::GetVarious(double initialValue)
{
	if (!m_variousPool.empty())
	{
		auto various = m_variousPool.back();
		various->m_value = initialValue;
		m_variousPool.pop_back();
		return various;
	}
	return new Various(initialValue);
}

void Various::FreeVarious(Various *various)
{
	m_variousPool.push_front(various);
}

void Various::ClearVariousPool()
{
	for (auto i : m_variousPool)
		i->Free();
	m_variousPool.clear();
}
