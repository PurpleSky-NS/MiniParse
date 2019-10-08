#pragma once

#include <vector>
#include "ErrorLog.h"
#include "ObjectPool.h"
#include "VariousTable.h"
#include "Various.h"
#include "Array.h"
#include "StatementBlocks.h"

class Program
{
public:
	/*设置目录路径，不设置就在当前路径下*/
	static void SetDirPath(const std::string& dirPath);

	/*从文件中获取程序，若没有返回nullptr*/
	static Program* LoadProgram(const std::string& name);

	/*从文件中获取程序，若没有返回nullptr*/
	static bool SaveProgram(Program* program);

	/*查找程序，若没有返回false*/
	static bool ExistProgram(const std::string& name) { return true; }

	/*in-class*/
	ErrorLog err_log;
	VariousTable var_table;
	ObjectPool<NoFreeValueItem> val_pool;
	ObjectPool<Array> arr_pool;
	ObjectPool<Various> var_pool;

	inline const std::string& GetName()const;

	inline bool Execute(std::vector<double> args);

	inline bool IsErrorExited()const;

	inline double GetResult()const;
	
	inline bool IsValid()const;

	/*异常退出*/
	inline void OnErrorFinish();

	inline void OnFinish(double result);

private:

	friend class ProgramParser;
	static std::string m_dirPath;

	inline Program();
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	inline ~Program();

	std::string m_name;
	StatementBlocks* m_baseBlocks;
	bool m_isFinished = false;
	bool m_isErrorExit = false;
	bool m_isValid = false;
	double m_result = 0.0;

	inline bool IsFinished()const;

	inline void Clear();

	inline void Begin();

	inline void End();
};

inline Program::Program()
{
	m_baseBlocks = new StatementBlocks;
	m_baseBlocks->SetFinishListener(std::bind(&Program::IsFinished, this));
}

inline Program::~Program()
{
	Clear();
}

inline const std::string& Program::GetName() const
{
	return m_name;
}

inline bool Program::Execute(std::vector<double> args)
{
	Begin();
	bool res = m_baseBlocks->Execute();
	m_isErrorExit = !res;
	End();
	return res;
}

inline bool Program::IsErrorExited() const
{
	return m_isErrorExit;
}

inline double Program::GetResult() const
{
	return m_result;
}

inline bool Program::IsValid()const
{
	return m_isValid;
}

inline void Program::OnErrorFinish()
{
	m_isFinished = true;
	m_isErrorExit = true;
}

inline void Program::OnFinish(double result)
{
	m_isFinished = true;
	m_result = result;
}

inline bool Program::IsFinished() const
{
	return m_isFinished;
}

inline void Program::Clear()
{
	delete m_baseBlocks;
}

inline void Program::Begin()
{
	m_isErrorExit = false;
	m_isFinished = false;

	val_pool.SetAllocationSize(4);
	arr_pool.SetAllocationSize(4);
	var_pool.SetAllocationSize(4);
	val_pool.AllocObjects();
	arr_pool.AllocObjects();
	var_pool.AllocObjects();
}

inline void Program::End()
{
	/*暂时以_ret作为返回值*/
	if (!IsErrorExited())
		m_result = ((Various*)var_table.GetVarious("_ret"))->GetValue();
	val_pool.ClearObjects();
	arr_pool.ClearObjects();
	var_pool.ClearObjects();
	var_table.Clear();
}