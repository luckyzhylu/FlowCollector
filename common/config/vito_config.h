#ifndef _VITO_CONFIG_H_
#define _VITO_CONFIG_H_

#include <string>
#include <map>
#include <iostream>

using namespace std;

class CVitoConfig
{
public:
	enum {
		MAPTOFILE = 1,
		FILETOMAP
	};
public:
	CVitoConfig(bool caseless = false);
	virtual ~CVitoConfig();

	bool load(const char *path = NULL);
	bool sync(int syncType = MAPTOFILE);
	bool find(const char *titile, string& rvalue);
	void dump(ostream& rOs = cout);

	bool set(const char *titile, const string& rcsValue);
	bool read(const char *titile, string& rsValue);

	static bool readFile(const char *path, map<string, string>& rMap,
			     bool bcase = false);
	static bool writeFile(const char *path, const map<string, string>& rMap,
			      bool bMerge = true);
private:
	CVitoConfig(const CVitoConfig& rc);
	CVitoConfig& operator=(const CVitoConfig& rc);
private:
	string m_configPath;		// 配置文件路径
	bool m_bCaseless;		// 区分大小写
public:
	map<string, string> m_mapContext; // 配置文件内容
};



#endif /* _VITO_CONFIG_H_ */
