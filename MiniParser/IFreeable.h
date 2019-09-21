#pragma once
class IFreeable
{
public:
	/*不一定会进行delete操作，但会使用Free接口表明该对象不会再使用
	应该确保调用该接口的类对象都是动态分配的*/
	virtual void Free() = 0;
};

