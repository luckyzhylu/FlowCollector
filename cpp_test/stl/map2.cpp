#include <map>
#include <string>
#include <stdint.h>

using namespace std;

//自定义map的key
typedef struct UrlKey
{
	uint64_t dwBussID;
	uint64_t dwVersion;
}UrlKey;

//自定义map的value
typedef struct UrlValue
{
	string strUrl;
}UrlValue;

//map的比较函数
struct cmp_key
{
	bool operator()(const UrlKey &k1, const UrlKey &k2)const
		{
			if(k1.dwBussID != k2.dwBussID)
			{
				return k1.dwBussID < k2.dwBussID;
			}

			if(k1.dwVersion != k2.dwVersion)
			{
				return k1.dwVersion < k2.dwVersion;
			}

			return false;
		}
};

int main()
{
	map<UrlKey, UrlValue, cmp_key> UrlMap;
	UrlKey stKey;
	stKey.dwBussID = 1;
	stKey.dwVersion = 2;

	UrlValue stValue;
	stValue.strUrl = "abc";

	UrlMap[stKey] = stValue;

	return 0;
}
