#pragma once

#include "Program.h"
#include "Array.h"
#include "Various.h"
#include "SuffixExpression.h"

class Statement :public StatementBase
{
protected:

	inline void CompileError(const std::string& msg)const;
	inline void DynCompileError(const std::string& msg)const;
	inline void RuntimeError(const std::string& msg)const;

	/*静态检查*/
	inline bool CheckExpression(const SuffixExpression& expression)const;

	/*动态检查，在程序中查找标识符*/
	inline bool DynamicCheck(const ExpressionType& exp)const;
	/*动态检查，在程序中查找标识符*/
	inline bool DynamicCheck(IdentificationItem* idf)const;
	/*动态检查，在变量表中查找变量*/
	inline bool DynamicCheck(VariousIDF* var)const;
	/*动态检查，在程序中查找函数*/
	inline bool DynamicCheck(FunctionIDF* func)const;

};
inline void Statement::CompileError(const std::string& msg)const
{
	m_program->err_log.AddCompileError(msg, GetLine());
}

inline void Statement::DynCompileError(const std::string& msg)const
{
	m_program->err_log.AddCompileError(msg, GetLine());
}

inline void Statement::RuntimeError(const std::string& msg)const
{
	m_program->err_log.AddCompileError(msg, GetLine());
}

bool Statement::CheckExpression(const SuffixExpression& expression)const
{
	if (!Calculator::CheckExpression(expression))
	{
		CompileError("表达式都能写错，唉~");
		return false;
	}
	return true;
}

bool Statement::DynamicCheck(const ExpressionType& exp) const
{
	for (auto i : exp)
		if (i->GetType() == ItemBase::Identification && !DynamicCheck((IdentificationItem*)i))
			return false;
	return true;
}

bool Statement::DynamicCheck(IdentificationItem* idf) const
{
	if (idf->GetIdentificationType() == IdentificationItem::VariousIDF)
		return DynamicCheck((VariousIDF*)idf);
	return DynamicCheck((FunctionIDF*)idf);
}

bool Statement::DynamicCheck(VariousIDF* var)const
{
	if (!m_program->var_table.ExistVarious(var->GetName()))
	{
		DynCompileError("没看错的话，你这个变量[" + var->GetName() + "]之前好像没定义过吧...");
		return false;
	}
	return true;
}

bool Statement::DynamicCheck(FunctionIDF* func)const
{
	if (!Program::ExistProgram(func->GetName()))//如果不存在就报错
	{
		CompileError("[" + func->GetName() + "]这调用的啥，原谅我智商低识别不出来...");
		return false;
	}
	for (auto i : func->Params())//查参数
		for (auto j : i)
			if (j->GetType() == ItemBase::Identification)
			{
				if (((IdentificationItem*)j)->GetIdentificationType() == IdentificationItem::VariousIDF)
				{
					if (!DynamicCheck((VariousIDF*)j))
						return false;
				}
				else
				{
					if (!DynamicCheck((FunctionIDF*)j))
						return false;
				}
			}
	return true;
}
