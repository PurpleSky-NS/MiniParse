#pragma once

#include <iostream>
#include "ParserError.h"

class Statement
{
public:

	enum StatementType :char
	{
		AssignStatement
	};

	inline const std::string& GetErrorMsg()const;

	inline void ClearErrorMsg();

	virtual bool Excuse() = 0;

	virtual StatementType GetType()const = 0;

	virtual void Save(std::ostream* o)const = 0;

	virtual bool Load(std::istream* o) = 0;

protected:

	inline void SetErrorMsg(const std::string& msg);

private:

	std::string m_errMsg;
};

void Statement::SetErrorMsg(const std::string& msg)
{
	m_errMsg = msg;
}

const std::string& Statement::GetErrorMsg()const
{
	return m_errMsg;
}

void Statement::ClearErrorMsg()
{
	m_errMsg.clear();
}
