#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"

using namespace std;

bool Test(function<DynamicSizeArray *(const DynamicSizeArray &)> func,const DynamicSizeArray &testIn,const DynamicSizeArray &testOut)
{
	func(testIn)->Foreach([](Array::ArrayItem& i){cout<<i.value<<endl;});
	return *func(testIn)==testOut;
}
int main()
{
	auto t0=[](const DynamicSizeArray &in)->DynamicSizeArray*
	{
		DynamicSizeArray &d=*DynamicSizeArray::GetDynamicSizeArray(in);
		d.RemoveIf([](const Array::ArrayItem &item){return item.value==5;});
		d.RemoveRangeIf([](const Array::ArrayItem &item){return item.value==2;});
		return &d;
	};
	
	cout<<Test(t0,*DynamicSizeArray::GetDynamicSizeArray({1,5,5,5,2,2,2}),*DynamicSizeArray::GetDynamicSizeArray({1,5,5}))<<endl;
	cin.get();
	return 0;
}