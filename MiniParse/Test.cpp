#include <iostream>
#include "Various.h"
#include "DynamicSizeArray.h"
#include "FixedSizeArray.h"
#include "VariousTable.h"

using namespace std;
int main()
{
	VariousTable table;
	table.UpdateVarious("���Ա���", Various::GetVarious(520));
	table.UpdateVarious("���Ծ�̬����(1)", FixedSizeArray::GetFixedSizeArray(5));
	table.UpdateVarious("���Ծ�̬����(2)", FixedSizeArray::GetFixedSizeArray({ 1,2,3.3 }));
	table.UpdateVarious("���Ծ�̬����(3)", FixedSizeArray::GetFixedSizeArray(5, { 1,2,3.4,5 }));

	FixedSizeArray &f = *((FixedSizeArray*)table.GetVarious("���Ծ�̬����(1)"));
	FixedSizeArray &ff = *((FixedSizeArray*)table.GetVarious("���Ծ�̬����(2)"));
	FixedSizeArray &fff = *((FixedSizeArray*)table.GetVarious("���Ծ�̬����(3)"));
	cout << "���Ա��� : " << ((Various*)table.GetVarious("���Ա���"))->GetValue() << endl;
	cout << "���Ծ�̬����(1) : " << f.Size() << "->[3]=" << f[3].value << endl;
	cout << "���Ծ�̬����(2) : " << ff.Size() << "->[3]=" << ff[3].value << endl;
	cout << "���Ծ�̬����(3) : " << fff.Size() << "->[3]=" << fff[3].value << endl;
	return 0;
}