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

	/*深层拷贝表达式，函数和变量都是new出来的，数值是从对象池中获取的*/
	inline void CopyExpression(const ExpressionType& exp, ExpressionType& outExp)const;

	/*静态检查*/
	inline bool CheckExpression(const ExpressionType& expression)const;

	/*动态检查，在程序中查找函数*/
	inline bool DynamicCheck(FunctionIDF* func)const;
	/*动态检查，在变量表中查找变量*/
	inline bool DynamicCheck(VariousIDF* var)const;

	/*将表达式中的变量或者函数数值替换，执行过后，表达式将可执行计算*/
	inline bool Replace(ExpressionType& exp);

	inline ValueItem* Replace(FunctionIDF* func);
	inline ValueItem* Replace(VariousIDF* var);
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

inline void Statement::CopyExpression(const ExpressionType& exp, ExpressionType& outExp) const
{
	outExp.reserve(exp.size());
	for (auto i : exp)
	{
		switch (i->GetType())
		{
		case ItemBase::Value:
		{
			ValueItem* val = m_program->val_pool.GetRecordObject();
			val->Value() = ((ValueItem*)i)->Value();
			outExp.push_back(val);
		}
		break;
		case ItemBase::Identification:
			if (((IdentificationItem*)i)->GetIdentificationType() == IdentificationItem::VariousIDF)
			{
				VariousIDF* src = (VariousIDF*)i;
				VariousIDF* dst = new VariousIDF(src->GetName());
				dst->SetToArrayItem(src->IsArrayItem());
				dst->NegSigned() = src->NegSigned();
				if (dst->IsArrayItem())
					CopyExpression(src->ArrayPosExpression(), dst->ArrayPosExpression());
				outExp.push_back(dst);
			}
			else //函数表达式，参数深层拷贝
			{
				FunctionIDF* src = (FunctionIDF*)i;
				FunctionIDF* func = new FunctionIDF(src->GetName());
				func->Params().resize(src->Params().size());
				for (size_t i = 0; i < src->Params().size(); ++i)
					CopyExpression(src->Params()[i], func->Params()[i]);
			}
			break;
		default:
			outExp.push_back(i);
			break;
		}
	}
}

bool Statement::CheckExpression(const ExpressionType& expression)const
{
	if (!Calculator::CheckExpression(expression))
	{
		CompileError("表达式都能写错，唉~");
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

bool Statement::DynamicCheck(VariousIDF* var)const
{
	if (!m_program->var_table.ExistVarious(var->GetName()))
	{
		DynCompileError("没看错的话，你这个变量[" + var->GetName() + "]之前好像没定义过吧...");
		return false;
	}
	return true;
}

ValueItem* Statement::Replace(FunctionIDF* func)
{
	/*执行变量数值替换*/
	for (auto& i : func->Params())
		if (!Replace(i))
		{
			RuntimeError("函数[" + func->GetName() + "]的参数的表达式无法计算...");
			return nullptr;
		}
}

ValueItem* Statement::Replace(VariousIDF* var)
{
	VariousBase* varBase = m_program->var_table.GetVarious(var->GetName());//获取变量
	if (varBase == nullptr)
	{
		RuntimeError("变量[" + var->GetName() + "]在上面没找到，咳咳...");
		return nullptr;
	}
	ValueItem* val = m_program->val_pool.GetRecordObject();//获取返回出去的值
	if (var->IsArrayItem())//是数组的话还要计算下标表达式
	{
		if (varBase->GetType() != VariousBase::Array)
		{
			RuntimeError("[" + var->GetName() + "]不是一个数组");
			return nullptr;
		}
		SuffixExpression posExp;//构造临时表达式
		CopyExpression(var->ArrayPosExpression(), posExp.GetExpression());
		if (!Replace(posExp.GetExpression()))//变成可执行计算的表达式
		{
			RuntimeError("数组[" + var->GetName() + "]下标表达式无法计算...");
			return nullptr;
		}
		if (m_calc.CalculateExpUnsafe(posExp) != Calculator::Succeed)
		{
			RuntimeError("数组[" + var->GetName() + "]下标计算错误啦");
			return nullptr;
		}
		double pos = m_calc.GetResult();
		Array* arr = (Array*)varBase;//获取变量
		if (!Calculator::IsDigit(pos))
		{
			RuntimeError("数组[" + var->GetName() + "]下标都算出来小数了...");
			return false;
		}
		val->Value() = (var->NegSigned() ? (*arr)[(int)pos].value : -(*arr)[(int)pos].value);//给返回出去的值赋值
	}
	else
	{
		Various* various = (Various*)varBase;
		if (varBase->GetType() != VariousBase::Various)
		{
			m_program->err_log.AddRuntimeError("数组[" + var->GetName() + "]不是一个变量", GetLine());
			return nullptr;
		}
		val->Value() = (var->NegSigned() ? various->GetValue() : -various->GetValue());//给返回出去的值赋值
	}
	return val;
}

bool Statement::Replace(ExpressionType& exp)
{
	for (auto& i : exp)//替换非数值的元素
	{
		if (i->GetType() == ItemBase::Identification)//如果是变量或者函数则进行替换
		{
			if (((IdentificationItem*)i)->GetIdentificationType() == IdentificationItem::VariousIDF)
			{
				if ((i = Replace((VariousIDF*)i)) == nullptr)
					return false;
			}
			else
			{
				if ((i = Replace((FunctionIDF*)i)) == nullptr)
					return false;
			}
		}
	}
	return true;
}
