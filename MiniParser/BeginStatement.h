#pragma once

#include "Statement.h"

/*获取输入参数的初始语句*/
class BeginStatement :public Statement
{
public:

	BeginStatement() = default;
	BeginStatement(const BeginStatement&) = delete;
	BeginStatement(BeginStatement&&) = delete;
	~BeginStatement() = default;

	inline bool SetStatement(const std::string& argsStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	inline virtual bool Execute() override;

	inline virtual void Clear() override;

	inline virtual StatementType GetType()const;

	inline virtual void Save(std::ostream& out)const;

	inline virtual void Load(std::istream& in);

private:
	struct _ArgStruct
	{
		bool isArray;
		SuffixExpression* capacity;//动态分配
		std::string argName;
	};
	std::vector<_ArgStruct> m_argsList;

};
bool BeginStatement::SetStatement(const std::string& argsStr)
{
	/*
	(a,b)
	(a,b,c)
	()
	(a[])
	(a,b[])
	(a[8],b[9])
	(a[2],b[])
	(a,b[a])
	*/

	/*空列表就不做转换了*/
	if (argsStr.empty())
		return true;

	InfixExpression inf;

	/*放初始化列表*/
	for (size_t beg = 0, end = argsStr.find(',', 0);; beg = end + 1, end = argsStr.find(',', beg))
	{
		//获取单个参数
		std::string argStr = argsStr.substr(beg, (end == argsStr.npos ? argsStr.size() : end) - beg);
		size_t bgBr = argStr.find('['), edBr = argStr.rfind(']');//寻找数组容量
		if (bgBr == argStr.npos || edBr == argStr.npos || bgBr >= edBr)//视作找不到容量表达式
			//当普通变量处理
			m_argsList.push_back({ false,nullptr,argStr });
		else
		{
			SuffixExpression* suf = new SuffixExpression;
			if (!(inf.ParseExpression(argStr.substr(bgBr + 1, edBr - bgBr - 1)) && suf->ParseExpression(inf)))
			{
				delete suf;
				CompileError("参数数组[" + argStr + "]容量的表达式写错了吧...");
				return false;
			}
			m_argsList.push_back({ true,suf,argStr.substr(0,bgBr) });
		}
		if (end == argsStr.npos)
			break;
	}
	return true;
}

inline bool BeginStatement::Check()
{
	return true;
}

inline bool BeginStatement::DynamicCheck()
{
	return true;
}

inline bool BeginStatement::Execute()
{
	return true;
}

inline void BeginStatement::Clear()
{
}

inline StatementBase::StatementType BeginStatement::GetType() const
{
	return StatementType::BeginStatement;
}

inline void BeginStatement::Save(std::ostream& out) const
{
}

inline void BeginStatement::Load(std::istream& in)
{
}
