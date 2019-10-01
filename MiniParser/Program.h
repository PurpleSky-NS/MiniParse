#pragma once

#include "VariousTable.h"
#include "ErrorLog.h"
#include "StatementBlocks.h"

class Program
{
public:

	/*设置目录路径，不设置就在当前路径下*/
	static void SetDirPath(const std::string& dirPath);

	/*编译成功后会在目录下生成一个编译后的文件*/
	static Program* Compile(const std::string& name, const std::string& data);

	/*从文件中获取程序，若没有返回nullptr*/
	static Program* LoadProgram(const std::string& name);


	ErrorLog err_log;
	VariousTable var_table;

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
