#pragma once

#include "Statement.h"
#include "IBeginStatement.h"

/*Warning：注意，该类为多继承，所以在指针转换时要使用dynamic_cast不能强制转换
这是一个C++的UB问题，和虚函数机制有关，所以一定要用内置转换
另外delete的时候需要将之动态转换为Statement保证虚指针指向对象起始段*/
/*获取输入参数的初始语句*/
class BeginStatement :public Statement, public IBeginStatement
{
public:

	BeginStatement() = default;
	BeginStatement(const BeginStatement&) = delete;
	BeginStatement(BeginStatement&&) = delete;
	inline ~BeginStatement();

	inline bool SetStatement(const std::string& argsStr);

	/*静态检查语句错误*/
	inline virtual bool Check() override;

	inline virtual bool DynamicCheck() override;

	/*这个才是程序入口*/
	inline virtual bool Execute(const std::vector<double>& args) override;
	/*不执行任何操作直接返回true，可以不调用*/
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
inline BeginStatement::~BeginStatement()
{
	Clear();
}
inline bool BeginStatement::SetStatement(const std::string& argsStr)
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
			std::string capacityStr=argStr.substr(bgBr + 1, edBr - bgBr - 1);
			SuffixExpression *suf=(capacityStr.empty()?nullptr:new SuffixExpression);
			if (suf!=nullptr && !(inf.ParseExpression(capacityStr) && suf->ParseExpression(inf)))
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
	for (auto& i : m_argsList)
		if (i.capacity != nullptr && !CheckExpression(*i.capacity))
			return false;
	return true;
}

inline bool BeginStatement::DynamicCheck()
{
	return true;
}

inline bool BeginStatement::Execute(const std::vector<double>& args)
{
	unsigned argsPos = 0;
	for (auto& i : m_argsList)
	{
		if (i.isArray)
		{
			Array* arr;
			if (i.capacity == nullptr)//var[]的情况
			{
				if (argsPos == args.size())
				{
					RuntimeError("可变参数数组[" + i.argName + "]获取不到参数...");
					return false;
				}
				arr = m_program->arr_pool.GetObject();
				for (; argsPos != args.size(); ++argsPos)
					arr->Add(args[argsPos]);
				m_program->var_table.UpdateVarious(i.argName, arr);
			}
			else //var[cap]的情况
			{
				unsigned capacity;
				if (!CalculateToDigit(*i.capacity, capacity))
				{
					RuntimeError("固定参数数组[" + i.argName + "]获取不到足够的参数...");
					return false;
				}
				arr = m_program->arr_pool.GetObject();
				for (; capacity != 0; ++argsPos, --capacity)
					arr->Add(args[argsPos]);
				m_program->var_table.UpdateVarious(i.argName, arr);
			}
		}
		else
		{
			if (argsPos == args.size())
			{
				RuntimeError("参数变量[" + i.argName + "]获取不到参数...");
				return false;
			}
			Various* var = m_program->var_pool.GetObject();
			var->GetValue() = args[argsPos++];
			m_program->var_table.UpdateVarious(i.argName, var);
		}
	}
	return true;
}

inline bool BeginStatement::Execute()
{
	return true;
}

inline void BeginStatement::Clear()
{
	for (auto& i : m_argsList)
		if (i.capacity != nullptr)
			delete i.capacity;
	m_argsList.clear();
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