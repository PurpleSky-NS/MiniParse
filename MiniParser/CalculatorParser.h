#pragma once

#include <iostream>
#include <string>
#include "ItemBase.h"
#include "BracketItem.h"
#include "FunctionIDF.h"
#include "VariousIDF.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "ValueItem.h"
#include "InfixExpression.h"
#include "SuffixExpression.h"

class CalculatorParser
{
public:

	static inline void Save(std::ostream& o, Expression* v);
	static inline void Save(std::ostream& o, InfixExpression* v);
	static inline void Save(std::ostream& o, SuffixExpression* v);
	static inline void Save(std::ostream& o, ItemBase* v);
	static inline void Save(std::ostream& o, BracketItem* v);
	static inline void Save(std::ostream& o, FunctionIDF* v);
	static inline void Save(std::ostream& o, VariousIDF* v);
	static inline void Save(std::ostream& o, BinaryOperator* v);
	static inline void Save(std::ostream& o, UnaryOperator* v);
	static inline void Save(std::ostream& o, ValueItem* v);

	static inline ItemBase* LoadItem(std::istream& in);
	static inline InfixExpression* LoadInfixExpression(std::istream& in);
	static inline SuffixExpression* LoadSuffixExpression(std::istream& in);

private:

	enum ItemType : char
	{
		ItemType_BracketItem,
		ItemType_FunctionIDF,
		ItemType_VariousIDF,
		ItemType_BinaryOperator,
		ItemType_UnaryOperator,
		ItemType_ValueItem,
		ItemType_InfixExpression,
		ItemType_SuffixExpression
	};

	CalculatorParser() = delete;
	CalculatorParser(const CalculatorParser&) = delete;
	CalculatorParser(CalculatorParser&&) = delete;
	~CalculatorParser() = delete;

	template<class T>
	static inline void Save(std::ostream& o, T v);
	static inline void Save(std::ostream& o, const std::string& v);

	static inline std::string LoadString(std::istream& in);
	static inline size_t LoadSize(std::istream& in);
	static inline double LoadDouble(std::istream& in);
	static inline bool LoadBool(std::istream& in);
	static inline Expression* LoadExpression(std::istream& in, Expression* exp);

};
void CalculatorParser::Save(std::ostream& o, Expression* v)
{
	Save(o, v->GetExpression().size());
	for (auto i : v->GetExpression())
		Save(o, i);
}
void CalculatorParser::Save(std::ostream& o, InfixExpression* v)
{
	Save(o, (Expression*)v);
}
void CalculatorParser::Save(std::ostream& o, SuffixExpression* v)
{
	Save(o, (Expression*)v);
}
void CalculatorParser::Save(std::ostream& o, ItemBase* v)
{
	switch (v->GetType())
	{
	case ItemBase::Bracket:
		Save(o, (BracketItem*)v);
		break;
	case ItemBase::Identification:
		switch (((IdentificationItem*)v)->GetIdentificationType())
		{
		case IdentificationItem::FunctionIDF:
			Save(o, (FunctionIDF*)v);
			break;
		case IdentificationItem::VariousIDF:
			Save(o, (VariousIDF*)v);
			break;
		}
		break;
	case ItemBase::Operator:
		switch (((OperatorItem*)v)->GetOperatorType())
		{
		case OperatorItem::BinaryOperator:
			Save(o, (BinaryOperator*)v);
			break;
		case OperatorItem::UnaryOperator:
			Save(o, (UnaryOperator*)v);
			break;
		}
		break;
	case ItemBase::Value:
		Save(o, (ValueItem*)v);
		break;
	}
}
void CalculatorParser::Save(std::ostream& o, BracketItem* v)
{
	o.put(ItemType_BracketItem);
	o.put(v->GetBracketType());
}
void CalculatorParser::Save(std::ostream& o, FunctionIDF* v)
{
	o.put(ItemType_FunctionIDF);
	Save(o, v->GetName());
	Save(o, v->Params().size());
	for (auto param : v->Params())
	{
		Save(o, param.size());
		for (auto paramItem : param)
			Save(o, paramItem);
	}
}
void CalculatorParser::Save(std::ostream& o, VariousIDF* v)
{
	o.put(ItemType_VariousIDF);
	Save(o, v->GetName());
	Save(o, v->NegSigned());
}
void CalculatorParser::Save(std::ostream& o, BinaryOperator* v)
{
	o.put(ItemType_BinaryOperator);
	o.put(v->GetBinaryOperatorType());
}
void CalculatorParser::Save(std::ostream& o, UnaryOperator* v)
{
	o.put(ItemType_UnaryOperator);
	o.put(v->GetUnaryOperatorType());
}
void CalculatorParser::Save(std::ostream& o, ValueItem* v)
{
	o.put(ItemType_ValueItem);
	Save(o, v->Value());
}
template<class T>
void CalculatorParser::Save(std::ostream& o, T v)
{
	o.write((char*)& v, sizeof(v));
}
void CalculatorParser::Save(std::ostream& o, const std::string& v)
{
	Save(o, v.size());
	o.write(v.c_str(), v.size());
}
ItemBase* CalculatorParser::LoadItem(std::istream& in)
{
	switch ((ItemType)in.get())
	{
	case ItemType_BracketItem:
		return BracketItem::GetBracket((BracketItem::BracketType)in.get());
	case ItemType_FunctionIDF:
	{
		/*
		Save(o, v->GetName());
		Save(o, v->Params().size());
		for (auto param : v->Params())
		{
			Save(o, param.size());
			for (auto paramItem : param)
				Save(o, paramItem);
		}*/

		std::string name = LoadString(in);
		FunctionIDF* funcIDF = new FunctionIDF(name);
		size_t paramsSize = LoadSize(in);
		funcIDF->Params().reserve(paramsSize);
		for (size_t i = 0; i < paramsSize; ++i)
		{
			size_t itemsSize = LoadSize(in);
			ExpressionType param;
			param.reserve(itemsSize);
			for (size_t j = 0; j < itemsSize; ++j)
				param.push_back(LoadItem(in));
			funcIDF->Params().push_back(param);
		}
		return funcIDF;
	}
	case ItemType_VariousIDF:
	{
		std::string name = LoadString(in);
		bool isNegSigned = LoadBool(in);
		return new VariousIDF(name, isNegSigned);
	}
	case ItemType_BinaryOperator:
		return BinaryOperator::GetOperator((BinaryOperator::BinaryOperatorType)in.get());
	case ItemType_UnaryOperator:
		return UnaryOperator::GetOperator((UnaryOperator::UnaryOperatorType)in.get());
	case ItemType_ValueItem:
		return new ValueItem(LoadDouble(in));
	}
	return nullptr;
}

InfixExpression* CalculatorParser::LoadInfixExpression(std::istream& in)
{
	return (InfixExpression*)LoadExpression(in, new InfixExpression);
}

SuffixExpression* CalculatorParser::LoadSuffixExpression(std::istream& in)
{
	return (SuffixExpression*)LoadExpression(in, new SuffixExpression);
}

std::string CalculatorParser::LoadString(std::istream& in)
{
	std::string v;
	size_t size = LoadSize(in);
	char buffer[1024];
	while (size)
	{
		in.read(buffer, (size > sizeof(buffer) - 1 ? sizeof(buffer) - 1 : size));
		buffer[in.gcount()] = 0;
		size -= in.gcount();
		v += buffer;
	}
	return v;
}

size_t CalculatorParser::LoadSize(std::istream& in)
{
	size_t v;
	in.read((char*)& v, sizeof(v));
	return v;
}

double CalculatorParser::LoadDouble(std::istream& in)
{
	double v;
	in.read((char*)& v, sizeof(v));
	return v;
}

bool CalculatorParser::LoadBool(std::istream& in)
{
	bool v;
	in.read((char*)& v, sizeof(v));
	return v;
}

Expression* CalculatorParser::LoadExpression(std::istream& in, Expression* expression)
{
	size_t size = LoadSize(in);
	ItemBase* item;
	expression->GetExpression().reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		item = LoadItem(in);
		if (item == nullptr)
		{
			delete expression;
			expression = nullptr;
			break;
		}
		expression->AddItem(item);
	}
	return expression;
}
