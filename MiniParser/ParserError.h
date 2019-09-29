#pragma once

#include <string>
#include <vector>

class ParserError
{
public:

	struct Message
	{
		std::string msg;
		unsigned line;
	}empty_msg{"",0};

	inline ParserError& GetParserError();

	inline void AddMessage(const std::string& msg, unsigned line);

	/*返回第一条信息*/
	inline const Message& GetMessage()const;
	/*返回所有信息*/
	inline const std::vector<Message>& GetMessages()const;
	/*将所有信息组合，用换行符分割*/
	inline std::string ToString()const;

	inline void Clear();

private:

	static ParserError m_err;

	std::vector<Message> m_msgs;

	ParserError() = default;
	ParserError(const ParserError&) = delete;
	ParserError(ParserError&&) = delete;
	~ParserError() = default;

};

ParserError& ParserError::GetParserError()
{
	return m_err;
}

void ParserError::AddMessage(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ msg,line });
}

const ParserError::Message& ParserError::GetMessage() const
{
	if (m_msgs.empty())
		return empty_msg;
	return m_msgs.front();
}

const std::vector<ParserError::Message>& ParserError::GetMessages() const
{
	return m_msgs;
}

std::string ParserError::ToString() const
{
	std::string msgs;
	for (auto i : m_msgs)
		msgs += "in " + std::to_string(i.line) + " : " + i.msg + "\n";
	if (!msgs.empty())
		msgs.pop_back();
	return msgs;
}

void ParserError::Clear()
{
	m_msgs.clear();
}