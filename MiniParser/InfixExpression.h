#pragma once

#include <string>
#include <cctype>
#include <cmath>
#include "Expression.h"
#include "ValueItem.h"
#include "BracketItem.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "VariousIDF.h"
#include "FunctionIDF.h"

class InfixExpression : public Expression
{
public:

	inline InfixExpression() = default;
	/*中缀表达式字符串构造*/;
	inline InfixExpression(const std::string& exp);
	InfixExpression(const InfixExpression&) = delete;
	InfixExpression(InfixExpression&&) = default;
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

	ItemBase* m_prevItem = nullptr;

	/*去除空白字符*/
	inline std::string RemoveSpace(const std::string& exp)const;

	inline bool IsNumber(char ch);

	/* 是否是分隔符，+ - * / % ^ ! , ( ) */
	inline bool IsDivOperator(char ch);

	/*获得一个元素*/
	inline ItemBase* GetItem(const std::string& exp, size_t& bgPos);

	/*若碰到非数字或者重复小数点(不是纯数字) 或者 正常分隔符会停下,返回是否是数字*/
	inline bool GetNumber(const std::string& exp, size_t& bgPos, std::string& itemStr);

	/*获取标识符*/
	inline IdentificationItem::IdentificationType GetIdentification(const std::string& exp, size_t& bgPos, std::string& itemStr);
};

InfixExpression::InfixExpression(const std::string& exp)
{
	ParseExpression(exp);
}

bool InfixExpression::ParseExpression(const std::string& srcExp)
{
	m_prevItem = nullptr;
	Clear();
	std::string exp = RemoveSpace(srcExp);
	for (size_t i = 0; i < exp.size();)
	{
		m_prevItem = GetItem(exp, i);
		if (m_prevItem == nullptr)
		{
			Clear();
			return false;
		}
		m_expression.push_back(m_prevItem);
	}
	return true;
}

std::string InfixExpression::RemoveSpace(const std::string& exp) const
{
	std::string newExp;
	newExp.reserve(exp.size());
	for (auto i : exp)
		if (!isspace(i))
			newExp += i;
	return newExp;
}

bool InfixExpression::IsNumber(char ch)
{
	return ch == '.' || isdigit(ch);
}

bool InfixExpression::IsDivOperator(char ch)
{
	return !(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' &&
		ch != '^' && ch != '!' && ch != ',' && ch != '(' && ch != ')' && ch != '[' && ch != ']');
}

ItemBase* InfixExpression::GetItem(const std::string& exp, size_t& pos)
{
	static bool hasSignedOp = false;//读入数字/变量是否带符号位
	static bool isNegOp = true;//是否是-
	/*当+-在表达式的开头，'('的后面或者二元运算符的后面时，就是符号位*/
	switch (exp[pos])
	{
	case '(':
		++pos;
		return BracketItem::GetBracket(BracketItem::Left);
	case ')':
		++pos;
		return BracketItem::GetBracket(BracketItem::Right);
	case '+':
		if (pos == 0 || m_prevItem != nullptr &&
			(m_prevItem->GetType() == ItemBase::Bracket && ((BracketItem*)m_prevItem)->GetBracketType() == BracketItem::Left
				|| m_prevItem->GetType() == ItemBase::Operator && ((OperatorItem*)m_prevItem)->GetOperatorType() == OperatorItem::BinaryOperator))//说明是符号位
		{
			hasSignedOp = true;
			isNegOp = false;
			return GetItem(exp, ++pos);
		}
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Add);
	case '-':
		if (pos == 0 || m_prevItem != nullptr &&
			(m_prevItem->GetType() == ItemBase::Bracket && ((BracketItem*)m_prevItem)->GetBracketType() == BracketItem::Left
				|| m_prevItem->GetType() == ItemBase::Operator && ((OperatorItem*)m_prevItem)->GetOperatorType() == OperatorItem::BinaryOperator))//说明是符号位
		{
			hasSignedOp = true;
			isNegOp = true;
			return GetItem(exp, ++pos);
		}
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Subtract);
	case '*':
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Multiply);
	case '/':
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Divide);
	case '%':
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Mod);
	case '^':
		++pos;
		return BinaryOperator::GetOperator(BinaryOperator::Power);
	case '!':
		++pos;
		return UnaryOperator::GetOperator(UnaryOperator::Factorial);
	default:
		std::string itemStr;
		if (isdigit(exp[pos])) //数字开头有可能是数字或者标识符
			if (GetNumber(exp, pos, itemStr))//如果能取出来数字的话
			{
				if (hasSignedOp)//带符号位
				{
					hasSignedOp = false;
					return new ValueItem((isNegOp ? -stod(itemStr) : stod(itemStr)));
				}
				return new ValueItem(stod(itemStr));
			}
		//取不出来就继续按标识符解析
		if (GetIdentification(exp, pos, itemStr) == IdentificationItem::VariousIDF)//如果是变量
		{
			std::string arrPosStr;
			bool isArrayItem = false;
			/*可能是常量pi和e*/
			if (itemStr == "pi")
				return new ValueItem(ValueItem::VALUE_PI);
			else if (itemStr == "e")
				return new ValueItem(ValueItem::VALUE_E);
			if (exp[pos] == '[')//遇到'['则说明是数组元素
			{
				size_t fd = exp.find(']', ++pos);
				if (pos == exp.npos)//没找到右括号
					return nullptr;
				arrPosStr = exp.substr(pos, fd - pos);
				pos = fd + 1;//跳过']'
				isArrayItem = true;
			}
			VariousIDF* vidf = new VariousIDF(itemStr);
			if (isArrayItem)//数组元素
			{
				vidf->SetToArrayItem(true);
				vidf->ArrayPosExpression() = std::move(InfixExpression(arrPosStr).GetExpression());//设置数组下标表达式
			}
			if (hasSignedOp)
			{
				hasSignedOp = false;
				if (isNegOp)
					vidf->NegSigned() = true;//设置符号位
			}
			return vidf;
		}
		else //否则就是函数名
		{
			//先判断是不是系统自带函数
			UnaryOperator* sysOp = UnaryOperator::GetOperator(itemStr);
			if (sysOp != nullptr)//是系统自带函数
				return sysOp;
			//否则就是自定义函数
			//函数是长这个样子的Func(a,b,a+b,5.2)或者Func(fc(1,2,3),s3)...
			++pos;//跳过左括号
			FunctionIDF* func = new FunctionIDF(itemStr);
			/*获取他的参数*/
			while (pos < exp.size() && exp[pos] != ')')
			{
				ExpressionType param;
				while (pos < exp.size() && exp[pos] != ',' && exp[pos] != ')')//获取一个一个的参数
					param.push_back(GetItem(exp, pos));//一个递归
				if (pos < exp.size())
					func->Params().push_back(param);
				else //没遇到右括号，读取失败
				{
					func->Free();
					return nullptr;
				}
				if (exp[pos] == ',')//跳过逗号继续读下个参数
					++pos;
			}
			if (pos < exp.size())
				++pos;//跳过括号
			else //没有遇到右括号强行退出循环
			{
				func->Free();
				return nullptr;
			}
			return func;
		}
	}
	return nullptr;
}

bool InfixExpression::GetNumber(const std::string& exp, size_t& bgPos, std::string& itemStr)
{
	bool isMeetDot = false;
	bool isBad = false;
	size_t pos = bgPos;
	for (; pos < exp.size() && IsNumber(exp[pos]); ++pos)
		if (exp[pos] == '.')
		{
			if (isMeetDot)
			{
				isBad = true;
				break;
			}
			else
				isMeetDot = true;
		}

	itemStr = exp.substr(bgPos, pos - bgPos);
	bgPos = pos;
	if (pos == exp.size())//如果读到底了
		return true;
	return !isBad && IsDivOperator(exp[pos]);//如果没有重复小数点并且遇到分隔符说明是数字
}

IdentificationItem::IdentificationType InfixExpression::GetIdentification(const std::string& exp, size_t& pos, std::string& itemStr)
{
	while (pos < exp.size() && !IsDivOperator(exp[pos]))//直到遇到分隔符停止
		itemStr += exp[pos++];
	if (pos == exp.size())//如果读到底了，说明是变量
		return IdentificationItem::VariousIDF;//否则是变量
	if (exp[pos] == '(') //遇到右括号说明是函数
		return IdentificationItem::FunctionIDF;
	return IdentificationItem::VariousIDF;//否则是变量
}
