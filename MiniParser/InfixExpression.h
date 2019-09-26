#pragma once

#include <string>
#include <cctype>
#include "Expression.h"
#include "ValueItem.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "IdentificationItem.h"

class InfixExpression : public Expression
{
public:
	inline InfixExpression() = default;
	/*中缀表达式字符串构造*/
	inline InfixExpression(const std::string& exp);
	InfixExpression(const InfixExpression&) = delete;
	InfixExpression(InfixExpression&&) = delete;
	~InfixExpression() = default;
	
	/*大长说明：
	分离字符串表达式
	操作符(一元，二元)全用对应的字母表示，会用到对应操作符类获取，获取不到就塞Identification里
	只有1.2,12,1.2000这样的数字会被转化为数字，1.2.2,12.0.0,12.0a,1a2这种会被转化为标识符
	匹配的运算符:+,-,*,/,%,^,!,(,)
	匹配的函数运算:系统库的(例如sin,cos),自定义函数(需要加括号，例如debug(1),deg(1,2,3),参数之间需要加逗号)
	匹配标识符:可以是变量名字，也可以是自定义函数(需要加括号)
	a+1.2.3-6.9*.5+(Fun(@!8,4-5,jj))%68
	1.2.3解析成标识符
	.5解析成标识符
	@!8解析成标识符
	jj是标识符
	a是标识符
	Fun函数标识符
	*/
	inline bool ParseExpression(const std::string& expression);
	
private:
	
	inline bool IsNumber(char ch);
	
	/* 是否是分隔符，+ - * / % ^ ! , */
	inline bool IsDivOperator(char ch);
	
	/*获得一个元素*/
	inline ItemBase *GetItem(const std::string &exp,size_t &bgPos);
	
	/*若碰到非数字或者重复小数点(不是纯数字) 或者 正常分隔符会停下*/
	inline std::string GetNumber(const std::string &exp,size_t &bgPos);
	
	inline std::string GetIdentification(const std::string &exp,size_t &bgPos,const std::string &appendStr="");
};

InfixExpression::InfixExpression(const std::string& exp)
{
	ParseExpression(expression);
}

bool InfixExpression::ParseExpression(const std::string& exp)
{
	std::string buf;
	for(size_t i=0;i<exp.size();)
	{
		
	}
}

bool IsNumber(char ch)
{
	return exp[pos]=='.'||isdigit(exp[pos]);
}

bool IsDivOperator(char ch)
{
	return ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^'||ch=='!'||ch==',';
}

std::string InfixExpression::GetNumber(const std::string &exp,size_t &pos)
{
	bool meetDot=false;
	std::string item;
	for(;IsNumber(ch);++pos)
		if(ch[i]=='.')
		{
			if(meetDot)
				return item;
			else
				meetDot=true;
			item+=exp[pos];
		}
	return item;
}

std::string GetIdentification(const std::string &exp,size_t &bgPos,const std::string &appendStr)
{
	std::string item=appendStr;
	
}