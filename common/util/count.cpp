#include "count.h"

template <class T>
long long unsigned int CCount<T>::m_countNum = 0;

template <class T>
long long unsigned int CCount<T>::m_lastCountNum = 0;

#if 1

// demo
class Count1 : public CCount<Count1> {
public:
	Count1(){}
	Count1(int num)
		: CCount<Count1>(num) {

	}
};
class Count2 : public CCount<Count2> {};

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	Count1 c1;
	Count1 c3;
	Count1 c4(4);
	cout << "count1:" << c1.GetCount() << endl;
	Count2 c2;
	c2++;
	c2 += 3;
	cout << "count1:" << c2.GetCount() << endl;

	return 0;
}
#endif
