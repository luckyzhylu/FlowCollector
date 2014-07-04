#include <iostream>
#include <map>


typedef struct _Key_t {
	long long int src_dev_id;
	long long int dst_dev_id;
} Key_t;

using namespace std;

struct KeyLess {
	bool operator() (const Key_t& rLeft, const Key_t& rRight) const {
		if (rLeft.src_dev_id < rRight.src_dev_id) {
			return true;
		} else if (rLeft.src_dev_id > rRight.src_dev_id){
			return false;
		} else {
			if (rLeft.dst_dev_id < rRight.dst_dev_id) {
				return true;
			} else {
				return false;
			}
		}
	}
};

int main(int argc, char *argv[])
{
	map<Key_t, int, KeyLess > myMap;
	map<Key_t, int>::iterator iter;
	int value = 10;

	Key_t key1 = {10, 20};

	for (int i = 1; i < 100; i++) {
		Key_t key2;
		key2.src_dev_id = key1.src_dev_id;
		key2.dst_dev_id = key1.dst_dev_id + i;
		myMap[key2] = 100 + i;
	}

	for (iter = myMap.begin(); iter != myMap.end(); iter++) {
		cout << "key:" << iter->first.src_dev_id << "," << iter->first.dst_dev_id;
		cout << "===>" << iter->second << endl;
	}

	key1.src_dev_id = 10;
	key1.dst_dev_id = 30;
	value = myMap[key1];
	cout << "key[10,30]==" << value <<endl;

	return 0;
}
