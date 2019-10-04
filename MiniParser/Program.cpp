#include "Program.h"
std::string Program::m_dirPath;
void Program::SetDirPath(const std::string& dirPath)
{
	m_dirPath = dirPath;
	m_dirPath += (m_dirPath.back() == '/' ? "" : "/");
}
