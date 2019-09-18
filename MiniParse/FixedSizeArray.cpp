#include "FixedSizeArray.h"
FixedSizeArray *FixedSizeArray::GetFixedSizeArray(unsigned size)
{
	return new FixedSizeArray(size);
}

FixedSizeArray *FixedSizeArray::GetFixedSizeArray(const std::vector<double>& initialValues)
{
	return new FixedSizeArray(initialValues);
}

FixedSizeArray *FixedSizeArray::GetFixedSizeArray(unsigned size, const std::vector<double>& initialValues)
{
	return new FixedSizeArray(size,initialValues);
}

void FixedSizeArray::FreeFixedSizeArray(FixedSizeArray *array)
{
	delete array;
}
