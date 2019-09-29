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
	};

	ParserError() = default;
	ParserError(const ParserError&) = delete;
	ParserError(ParserError&&) = delete;
	~ParserError() = default;

	inline void AddMessage(const std::string& msg, unsigned line);

	/*返回所有信息*/
	inline const std::vector<Message>& GetMessages()const;
	/*将所有信息组合，用换行符分割*/
	inline std::string ToString()const;

	inline void Clear();

private:

	std::vector<Message> m_msgs;

};

void ParserError::AddMessage(const std::string& msg, unsigned line)
{
	m_msgs.push_back({ msg,line });
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
