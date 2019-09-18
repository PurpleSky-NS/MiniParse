#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"

using namespace std;
int main()
{
	VariousTable table;
	table.UpdateVarious("测试变量", Various::GetVarious(520));
	table.UpdateVarious("测试静态数组(1)", FixedSizeArray::GetFixedSizeArray(5));
	table.UpdateVarious("测试静态数组(2)", FixedSizeArray::GetFixedSizeArray({ 1,2,3.3 }));
	table.UpdateVarious("测试静态数组(3)", FixedSizeArray::GetFixedSizeArray(5, { 1,2,3.4,5 }));

	FixedSizeArray &f = *((FixedSizeArray*)table.GetVarious("测试静态数组(1)"));
	FixedSizeArray &ff = *((FixedSizeArray*)table.GetVarious("测试静态数组(2)"));
	FixedSizeArray &fff = *((FixedSizeArray*)table.GetVarious("测试静态数组(3)"));
	cout << "测试变量 : " << ((Various*)table.GetVarious("测试变量"))->GetValue() << endl;
	cout << "测试静态数组(1) : " << f.Size() << "->[3]=" << f[3].value << endl;
	cout << "测试静态数组(2) : " << ff.Size() << "->[3]=" << ff[3].value << endl;
	cout << "测试静态数组(3) : " << fff.Size() << "->[3]=" << fff[3].value << endl;
	return 0;
}