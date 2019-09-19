#include "DynamicSizeArray.h"
DynamicSizeArray *DynamicSizeArray::GetDynamicSizeArray()
{
	return new DynamicSizeArray();
}

DynamicSizeArray *DynamicSizeArray::GetDynamicSizeArray(const std::vector<double>& initialValues)
{
	return new DynamicSizeArray(initialValues);
}

void DynamicSizeArray::FreeDynamicSizeArray(DynamicSizeArray * array)
{
	delete array;
}
