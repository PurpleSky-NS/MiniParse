#pragma once
class IFreeable
{
public:
	/*��һ�������delete����������ʹ��Free�ӿڱ����ö��󲻻���ʹ��
	Ӧ��ȷ�����øýӿڵ�������Ƕ�̬�����*/
	virtual void Free() = 0;
};

