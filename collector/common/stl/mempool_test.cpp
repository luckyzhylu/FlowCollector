#include "CMemPool.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;


void test ();
CMemPool<100, 10> pool;
int main(int argc, char *argv[])
{
	pool.Init();

	test();
	test();

	return 0;
}

void test () {
	void *p = NULL;
	list<void *> vMemList;
	list<void *> ::iterator iter;

	while ((p = pool.Malloc()) != NULL) {
		vMemList.push_back(p);
	}
	cout << "vMemList.size=" << vMemList.size() << endl;

	for (iter = vMemList.begin(); iter != vMemList.end(); iter++) {
		pool.Free(*iter);
	}
	vMemList.clear();
	cout << "vMemList.size=" << vMemList.size() << endl;
}
