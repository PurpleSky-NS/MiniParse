#pragma once

#include "ErrorLog.h"
#include "ValueItem.h"
#include "ObjectPool.h"
#include "VariousTable.h"
#include "StatementBlocks.h"
#include "DynamicSizeArray.h"
#include "Various.h"

class Program
{
public:

	/*设置目录路径，不设置就在当前路径下*/
	static void SetDirPath(const std::string& dirPath);

	/*编译成功后会在目录下生成一个编译后的文件*/
	static Program* Compile(const std::string& name, const std::string& data);

	/*从文件中获取程序，若没有返回nullptr*/
	static Program* LoadProgram(const std::string& name);

	/*查找程序，若没有返回false*/
	static bool ExistProgram(const std::string& name);


	/*in-class*/
	ErrorLog err_log;
	VariousTable var_table;
	ObjectPool<NoFreeValueItem> val_pool;
	ObjectPool<DynamicSizeArray> dsa_pool;
	ObjectPool<Various> var_pool;

	inline const std::string& GetName()const;

	void Save();

private:

	static std::string m_dirPath;

	std::string m_name;
	StatementBlocks* m_baseBlocks;
};
inline const std::string& Program::GetName() const
{
	return m_name;
}
