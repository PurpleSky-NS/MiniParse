#include "UnarOperator.h"
UnarOperator UnarOperator::operators[Count]
{
	UnarOperator((UnarOperator::UnarOperatorType)0),
	UnarOperator((UnarOperator::UnarOperatorType)1),
	UnarOperator((UnarOperator::UnarOperatorType)2),
	UnarOperator((UnarOperator::UnarOperatorType)3),
	UnarOperator((UnarOperator::UnarOperatorType)4),
	UnarOperator((UnarOperator::UnarOperatorType)5),
	UnarOperator((UnarOperator::UnarOperatorType)6),
	UnarOperator((UnarOperator::UnarOperatorType)7),
	UnarOperator((UnarOperator::UnarOperatorType)8)
};
UnarOperator* UnarOperator::GetUnarOperator(UnarOperatorType type)
{
	return &operators[(size_t)type];
}