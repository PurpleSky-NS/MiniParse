#pragma once

#include <vector>
#include "ErrorLog.h"
#include "ObjectPool.h"
#include "VariousTable.h"
#include "DynamicSizeArray.h"
#include "Various.h"
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
	ObjectPool<DynamicSizeArray> dsa_pool;
	ObjectPool<Various> var_pool;

	inline const std::string& GetName()const;

	inline double Execute(std::vector<double> args);

private:

	friend class ProgramParser;
	static std::string m_dirPath;

	inline Program();
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	inline ~Program();

	std::string m_name;
	StatementBlocks* m_baseBlocks;

	inline void Clear();

};

inline Program::Program()
{
	m_baseBlocks = new StatementBlocks;
}

inline Program::~Program()
{
	Clear();
}

inline const std::string& Program::GetName() const
{
	return m_name;
}

inline void Program::Clear()
{
	delete m_baseBlocks;
}
