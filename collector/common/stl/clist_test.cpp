#include "clist.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <string.h>
using namespace std;

typedef struct _MyStruct {
	int data_num;
	CList* data_list;

	int mem_num;
	CList* mem_list;
} MyStruct;



class CData
{
public:
	CList m_list;
public:
	CData(int num = 0): m_data(num) {

	}
	virtual ~CData() {}

	friend void operator << (ostream& rOs, CData& rc);
private:
	CData(const CData& rc);
	CData& operator=(const CData& rc);
protected:
	int m_data;
};
void operator << (ostream& rOs, CData& rc)
{
	rOs << "m_data=" << rc.m_data << endl;
}

class CMember
{
public:
	CList m_list;
public:
	CMember(int num = 0): m_data(num) {

	}
	virtual ~CMember() {}

	friend void operator << (ostream& rOs, CMember& rc);
private:
	CMember(const CMember& rc);
	CMember& operator=(const CMember& rc);
protected:
	int m_data;
};
void operator << (ostream& rOs, CMember& rc)
{
	rOs << "m_data=" << rc.m_data << endl;
}


int main(int argc, char *argv[])
{
	MyStruct ms1;

	memset(&ms1, 0, sizeof(MyStruct));

	CData *data = new CData();
	ms1.data_list = &data->m_list;
	ms1.data_num = 1;
	CMember *mem = new CMember();
	ms1.mem_list = &mem->m_list;
	ms1.mem_num = 1;

	for (int i = 0; i < 10; i++) {
		CData *data = new CData(i + 1);
		ms1.data_list->InsertFront(&data->m_list);

		CMember *mem = new CMember(i + 100);
		ms1.mem_list->InsertFront(&mem->m_list);

	}

	int i = 0;
	for (CList *p = ms1.data_list; i < ms1.data_num; i++, p = p->Next()) {
		int offset = OFFSET_OF(CData, m_list);
		CData *pData = (CData *) (((char *)p) - offset);
		cout << *pData;
	}


	for (CList *p = ms1.mem_list->Next(); p != ms1.mem_list; p = p->Next()) {
		int offset = OFFSET_OF(CMember, m_list);
		CMember *pData = (CMember *) (((char *)p) - offset);
		cout << *pData;
	}

	return 0;
}
