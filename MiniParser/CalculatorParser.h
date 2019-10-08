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

class CalculatorParser
{
public:

	static inline void Save(std::ostream& out, const ExpressionType& v);
	static inline void Save(std::ostream& out, const BracketItem& v);
	static inline void Save(std::ostream& out, const FunctionIDF& v);
	static inline void Save(std::ostream& out, const VariousIDF& v);
	static inline void Save(std::ostream& out, const BinaryOperator& v);
	static inline void Save(std::ostream& out, const UnaryOperator& v);
	static inline void Save(std::ostream& out, const ValueItem& v);

	static inline void Load(std::istream& in, ExpressionType& v);
	static inline void Load(std::istream& in, FunctionIDF& v);
	static inline void Load(std::istream& in, VariousIDF& v);
	static inline void Load(std::istream& in, ValueItem& v);
	static inline BracketItem* LoadBracket(std::istream& i);
	static inline BinaryOperator* LoadBinaryOperator(std::istream& i);
	static inline UnaryOperator* LoadUnaryOperator(std::istream& i);

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
	static inline void Save(std::ostream& o, const T v);
	static inline void Save(std::ostream& o, size_t v);
	static inline void Save(std::ostream& o, ItemBase* v);
	static inline void Save(std::ostream& o, const std::string& v);

	static inline std::string LoadString(std::istream& in);
	static inline size_t LoadSize(std::istream& in);
	static inline double LoadDouble(std::istream& in);
	static inline bool LoadBool(std::istream& in);
	/*new出来的*/
	static inline ItemBase* LoadItem(std::istream& in);

};
void CalculatorParser::Save(std::ostream& out, const ExpressionType& v)
{
	Save(out, v.size());
	for (auto& i : v)
		Save(out, i);
}
void CalculatorParser::Save(std::ostream& out, const BracketItem& v)
{
	out.put(v.GetBracketType());
}
void CalculatorParser::Save(std::ostream& out, const FunctionIDF& v)
{
	Save(out, v.GetName());
	Save(out, v.Params().size());
	for (auto param : v.Params())
	{
		Save(out, param.size());
		for (auto paramItem : param)
			Save(out, paramItem);
	}
}
void CalculatorParser::Save(std::ostream& out, const VariousIDF& v)
{
	Save(out, v.GetName());
	Save(out, v.NegSigned());
	Save(out, v.IsArrayItem());
	if (v.IsArrayItem())
		Save(out, v.ArrayPosExpression());
}
void CalculatorParser::Save(std::ostream& out, const BinaryOperator& v)
{
	out.put(v.GetBinaryOperatorType());
}
void CalculatorParser::Save(std::ostream& out, const UnaryOperator& v)
{
	out.put(v.GetUnaryOperatorType());
}
void CalculatorParser::Save(std::ostream& out, const ValueItem& v)
{
	Save(out, v.Value());
}
void CalculatorParser::Load(std::istream& in, ExpressionType& v)
{
	size_t psSize = LoadSize(in);
	v.clear();
	v.reserve(psSize);
	for (size_t psPos = 0; psPos < psSize; ++psPos)
		v.push_back(LoadItem(in));
}
void CalculatorParser::Load(std::istream& in, FunctionIDF& v)
{
	v.GetName() = LoadString(in);
	size_t psSize = LoadSize(in);
	v.Params().resize(psSize);
	for (size_t pi = 0; pi < psSize; ++pi)
	{
		size_t pSize = LoadSize(in);
		v.Params()[pi].resize(pSize);
		for (size_t ppos = 0; ppos < pSize; ++ppos)
			v.Params()[pi][ppos] = LoadItem(in);
	}
}
void CalculatorParser::Load(std::istream& in, VariousIDF& v)
{
	v.GetName() = LoadString(in);
	v.NegSigned() = LoadBool(in);
	v.SetToArrayItem(LoadBool(in));
	if (v.IsArrayItem())
		Load(in, v.ArrayPosExpression());
}
void CalculatorParser::Load(std::istream& in, ValueItem& v)
{
	in.read((char*)& v.Value(), sizeof(double));
}
BracketItem* CalculatorParser::LoadBracket(std::istream& in)
{
	return BracketItem::GetBracket((BracketItem::BracketType)in.get());
}
BinaryOperator* CalculatorParser::LoadBinaryOperator(std::istream& in)
{
	return BinaryOperator::GetOperator((BinaryOperator::BinaryOperatorType)in.get());
}
UnaryOperator* CalculatorParser::LoadUnaryOperator(std::istream& in)
{
	return UnaryOperator::GetOperator((UnaryOperator::UnaryOperatorType)in.get());
}
template<class T>
void CalculatorParser::Save(std::ostream& out, const T v)
{
	out.write((char*)& v, sizeof(v));
}
void CalculatorParser::Save(std::ostream& out, size_t v)
{
	uint32_t size = (uint32_t)v;
	out.write((const char*)& size, sizeof(size));
}
void CalculatorParser::Save(std::ostream& out, ItemBase* v)
{
	switch (v->GetType())
	{
	case ItemBase::Bracket:
		out.put(ItemType_BracketItem);
		Save(out, *(BracketItem*)v);
		break;
	case ItemBase::Identification:
		switch (((IdentificationItem*)v)->GetIdentificationType())
		{
		case IdentificationItem::FunctionIDF:
			out.put(ItemType_FunctionIDF);
			Save(out, *(FunctionIDF*)v);
			break;
		case IdentificationItem::VariousIDF:
			out.put(ItemType_VariousIDF);
			Save(out, *(VariousIDF*)v);
			break;
		}
		break;
	case ItemBase::Operator:
		switch (((OperatorItem*)v)->GetOperatorType())
		{
		case OperatorItem::BinaryOperator:
			out.put(ItemType_BinaryOperator);
			Save(out, *(BinaryOperator*)v);
			break;
		case OperatorItem::UnaryOperator:
			out.put(ItemType_UnaryOperator);
			Save(out, *(UnaryOperator*)v);
			break;
		}
		break;
	case ItemBase::Value:
		out.put(ItemType_ValueItem);
		Save(out, *(ValueItem*)v);
		break;
	}
}
void CalculatorParser::Save(std::ostream& out, const std::string& v)
{
	Save(out, v.size());
	out.write(v.c_str(), v.size());
}
ItemBase* CalculatorParser::LoadItem(std::istream& in)
{
	switch ((ItemType)in.get())
	{
	case ItemType_BracketItem:
		return LoadBracket(in);
	case ItemType_FunctionIDF:
	{
		FunctionIDF* funcIDF = new FunctionIDF;
		Load(in, *funcIDF);
		return funcIDF;
	}
	case ItemType_VariousIDF:
	{
		VariousIDF* varIDF = new VariousIDF;
		Load(in, *varIDF);
		return varIDF;
	}
	case ItemType_BinaryOperator:
		return LoadBinaryOperator(in);
	case ItemType_UnaryOperator:
		return LoadUnaryOperator(in);
	case ItemType_ValueItem:
	{
		ValueItem* value = new ValueItem;
		Load(in, *value);
		return value;
	}
	}
	return nullptr;
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
	uint32_t v;
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
