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
	table.UpdateVarious("测试静态数组(2)", FixedSizeArray::GetFixedSizeArray({ 1,2,3.3,5.4 }));
	table.UpdateVarious("测试静态数组(3)", FixedSizeArray::GetFixedSizeArray(6, { 1,2,3,5 }));
	table.UpdateVarious("测试动态数组", DynamicSizeArray::GetDynamicSizeArray({ 1,2,3,5 }));

	FixedSizeArray &f = *((FixedSizeArray*)table.GetVarious("测试静态数组(1)"));
	FixedSizeArray &ff = *((FixedSizeArray*)table.GetVarious("测试静态数组(2)"));
	FixedSizeArray &fff = *((FixedSizeArray*)table.GetVarious("测试静态数组(3)"));
	cout << "测试变量 : " << ((Various*)table.GetVarious("测试变量"))->GetValue() << endl;
	cout << "测试静态数组(1) : " << f.Size() << "->[3]=" << f[3].value << endl;
	cout << "测试静态数组(2) : " << ff.Size() << "->[3]=" << ff[3].value << endl;
	cout << "测试静态数组(3) : " << fff.Size() << "->[3]=" << fff[3].value << endl;
	
	DynamicSizeArray &d = *((DynamicSizeArray*)table.GetVarious("测试动态数组"));
	cout << "测试动态数组 : " << d.Size() << "->[1]=" << d[1].value << endl;
	d.Add(12.3);
	cout << "测试动态数组 : " << d.Size() << "->[4]=" << d[4].value << endl;
	d.RemoveLast();
	d.Remove(0);
	cout << "测试动态数组 : " << d.Size() << "->[0]=" << d[0].value << endl;
	cout << "测试动态数组 : " << d.Size() << "->[?]=" << d.Contains(2) << endl;
	
	
	cin.get();
	return 0;
}