#pragma once

#include <list>
#include "VariousBase.h"

class Various : public VariousBase
{
public:
	
	/*获取一个变量对象*/
	static Various *GetVarious(double initialValue);
	/*释放一个变量对象*/
	static void FreeVarious(Various *various);
	/*在程序结束时调用，清空变量池*/
	static void ClearVariousPool();
	
	inline double &GetValue();
	
	inline Various &operator=(const Various &various);
	inline Various &operator=(double constant);
	inline bool operator==(const Various &various)const;
	inline bool operator==(double constant)const;
	inline bool operator!=(const Various &various)const;
	inline bool operator!=(double constant)const;
	inline bool operator>(const Various &various)const;
	inline bool operator>(double constant)const;
	inline bool operator<(const Various &various)const;
	inline bool operator<(double constant)const;
	inline bool operator>=(const Various &various)const;
	inline bool operator>=(double constant)const;
	inline bool operator<=(const Various &various)const;
	inline bool operator<=(double constant)const;
	
protected:
	
	inline virtual void Free()override;
	
private:
	static std::list<Various*> m_variousPool;
	
	double m_value;
	
	inline Various(double initialValue);
	inline Various()=delete;
	inline Various(const Various &various)=delete;
	inline Various(Various &&)=delete;
	~Various()=default;
	
};
Various::Various(double initialValue)
	:VariousBase(VariousBase::Various)
{
	m_value=initialValue;
}
double &Various::GetValue()
{
	return m_value;
}
Various &Various::operator=(const Various &various)
{
	m_value=various.m_value;
	return *this;
}
Various &Various::operator=(double constant)
{
	m_value=constant;
	return *this;
}
bool Various::operator==(const Various &various)const
{
	return m_value==various.m_value;
}
bool Various::operator==(double constant)const
{
	return m_value==constant;
}
bool Various::operator!=(const Various &various)const
{
	return m_value!=various.m_value;
}
bool Various::operator!=(double constant)const
{
	return m_value!=constant;
}
bool Various::operator>(const Various &various)const
{
	return m_value>various.m_value;
}
bool Various::operator>(double constant)const
{
	return m_value>constant;
}
bool Various::operator<(const Various &various)const
{
	return m_value<various.m_value;
}
bool Various::operator<(double constant)const
{
	return m_value<constant;
}
bool Various::operator>=(const Various &various)const
{
	return m_value>=various.m_value;
}
bool Various::operator>=(double constant)const
{
	return m_value>=constant;
}
bool Various::operator<=(const Various &various)const
{
	return m_value<=various.m_value;
}
bool Various::operator<=(double constant)const
{
	return m_value<=constant;
}
void Various::Free()
{
	FreeVarious(this);
}