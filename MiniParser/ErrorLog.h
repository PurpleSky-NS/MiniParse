#pragma once

#include <fstream>
#include <string>
#include <vector>

class ErrorLog
{
public:

	struct Message
	{
		std::string msg;
		unsigned line;
	};

	ErrorLog() = default;
	ErrorLog(const ErrorLog&) = delete;
	ErrorLog(ErrorLog&&) = delete;
	~ErrorLog() = default;

	inline void AddError(const std::string& msg, unsigned line);

	inline void AddCompileError(const std::string& msg, unsigned line);
	inline void AddDynCompileError(const std::string& msg, unsigned line);
	inline void AddRuntimeError(const std::string& msg, unsigned line);

	/*返回所有信息*/
	inline const std::vector<Message>& GetMessages()const;
	/*将所有信息组合，用换行符分割*/
	inline std::string ToString()const;

	/*保存至指定文件*/
	inline void Save(const std::string& path)const;

	inline void Clear();

private:

	std::vector<Message> m_msgs;

};

void ErrorLog::AddError(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ msg,line });
}

void ErrorLog::AddCompileError(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ "Compile : " + msg,line });
}

void ErrorLog::AddDynCompileError(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ "Dyn Compile : " + msg,line });
}

void ErrorLog::AddRuntimeError(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ "Runtime : " + msg,line });
}

const std::vector<ErrorLog::Message>& ErrorLog::GetMessages() const
{
	return m_msgs;
}

std::string ErrorLog::ToString() const
{
	std::string msgs;
	for (auto& i : m_msgs)
		msgs += "in " + std::to_string(i.line) + " line " + i.msg + "\n";
	if (!msgs.empty())
		msgs.pop_back();
	return msgs;
}

void ErrorLog::Save(const std::string& path) const
{
	std::ofstream o(path);
	o << ToString() << std::flush;
	o.close();
}

void ErrorLog::Clear()
{
	m_msgs.clear();
}
