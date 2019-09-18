#pragma once

#include <string>

class VariousBase
{
	public:
	
	enum VariousType:unsigned char
	{
		Various,
		Array
	};
	
	inline VariousType GetType()const;
	
	/*不会进行delete操作，但会使用Free接口表明该对象不会再使用*/
	virtual void Free()=0;
	
	protected:
	inline VariousBase(VariousType type);
	VariousBase()=delete;
	VariousBase(const VariousBase &)=delete;
	VariousBase(VariousBase &&)=delete;
	
	private:
	VariousType m_type;
	
};
VariousBase::VariousType VariousBase::GetType()const
{
	return m_type;
}
VariousBase::VariousBase(VariousBase::VariousType type)
{
	m_type=type;
}