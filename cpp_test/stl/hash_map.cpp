#include <hash_map>
#include <string>
#include <iostream>

using namespace std;
using namespace __gnu_cxx;

//define the class
class ClassA{
        public:
        ClassA(int a, int b):c_a(a), c_b(b){}

        int getvalue()const { return c_a + c_b;}
        void setvalue(int a){c_a;}

public:
        int c_a;
	int c_b;
};

//1 define the hash function
struct hash_A{
        size_t operator()(const class ClassA & A)const{
                //  return  hash<int>(classA.getvalue());
                return A.getvalue();
        }
};

//2 define the equal function
struct equal_A{
        bool operator()(const class ClassA & a1, const class ClassA & a2)const{
		if (a1.getvalue() == a2.getvalue()) {
			if (a1.c_a == a2.c_a && a1.c_b == a2.c_b) {
				return true;
			}
		}
		return false;
        }
};

int main()
{
        hash_map<ClassA, string, hash_A, equal_A> hmap;
        ClassA a1(12, 13);
        hmap[a1]="I am 12 & 13";
        ClassA a2(13, 12);
        hmap[a2]="I am 13 & 12";

        cout<<hmap[a1]<<endl;
        cout<<hmap[a2]<<endl;

        return 0;
}
