#include "UnaryOperator.h"
UnaryOperator UnaryOperator::operators[Count]
{
	UnaryOperator((UnaryOperator::UnaryOperatorType)0),
	UnaryOperator((UnaryOperator::UnaryOperatorType)1),
	UnaryOperator((UnaryOperator::UnaryOperatorType)2),
	UnaryOperator((UnaryOperator::UnaryOperatorType)3),
	UnaryOperator((UnaryOperator::UnaryOperatorType)4),
	UnaryOperator((UnaryOperator::UnaryOperatorType)5),
	UnaryOperator((UnaryOperator::UnaryOperatorType)6),
	UnaryOperator((UnaryOperator::UnaryOperatorType)7),
	UnaryOperator((UnaryOperator::UnaryOperatorType)8)
};
UnaryOperator* UnaryOperator::GetUnaryOperator(UnaryOperatorType type)
{
	return &operators[(size_t)type];
}
