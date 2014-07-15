#include "vito_config.h"

#include <cassert>
#include <fstream>
#include <algorithm>
#include <ctype.h>


CVitoConfig::CVitoConfig(bool caseless)
	:m_bCaseless(caseless)
{

	m_configPath.clear();
	m_mapContext.clear();
}

CVitoConfig::~CVitoConfig()
{
}

void CVitoConfig::dump(ostream& rOs)
{
	map<string, string>::iterator iter;

	rOs << "#filePath:" << m_configPath <<"caseness:" << m_bCaseless << endl;
	for (iter = m_mapContext.begin(); iter != m_mapContext.end(); iter++) {
		rOs << iter->first << "=" << iter->second << endl;
	}
}

/** 
 * 加载配置文件，把所以得字段加载到m_mapContext中
 * 
 * @param path 文件的全路径
 * 
 * @return 成功返回true,失败返回false
 */
bool CVitoConfig::load(const char * path)
{
	if (path != NULL) {
		m_configPath = string(path);
	}

	assert(!m_configPath.empty());

	return readFile(m_configPath.c_str(), m_mapContext, m_bCaseless);
}

/** 
 * 文件内容同步:文件内容同步到内存map中;内存map同步到文件
 * 
 * @param type 同步类型
 * 
 * @return 成功返回true,失败返回false
 */
bool CVitoConfig::sync(int type)
{
	if (type == MAPTOFILE) {
		assert(m_mapContext.size() > 0);
		return writeFile(m_configPath.c_str(), m_mapContext);
	} else if (type == FILETOMAP) {
		m_mapContext.clear();
		return readFile(m_configPath.c_str(), m_mapContext);
	} else {
		assert(0);
	}
}

/** 
 * 用字段标题查找文件内容
 * 
 * @param titile 字段标题
 * 
 * @return 找到返回标题的值，可以修改,没有返回空字符串
 */
bool CVitoConfig::find(const char * title, string& rValue)
{
	map<string, string>::iterator iter;

	assert(title);
	iter = m_mapContext.find(title);
	if (iter == m_mapContext.end()) {
		return false;
	} else {
		rValue = iter->second;
		return true;
	}
}

bool CVitoConfig::set(const char * title, const string & rcsValue)
{
	map<string, string>::iterator iter;

	assert(title);
	assert(!rcsValue.empty());

	iter = m_mapContext.find(title);
	if (iter == m_mapContext.end()) {
		m_mapContext.insert(pair<string, string>(title, rcsValue));
	} else {
		iter->second = rcsValue;
	}

	return true;
}

bool CVitoConfig::read(const char * title, string & rsValue)
{
	map<string, string>::iterator iter;

	assert(title);
	iter = m_mapContext.find(title);
	if (iter == m_mapContext.end()) {
		return false;
	} else {
		rsValue = iter->second;
		return true;
	}
}

bool CVitoConfig::readFile(const char * path, map < string, string > & rMap, bool bcase)
{
	ifstream ifile;
	string sLine;

	ifile.open(path);
	if (!ifile.is_open()) {
		// cout << "open file faild:" << path << endl;
		goto err;
	}

	while (getline(ifile, sLine)) {
		if (sLine.length() <= 1 || sLine[0] == '#') {
			continue;
		}
		if (!bcase) {
			transform(sLine.begin(), sLine.end(), sLine.begin(), ::toupper);
		}
		string::iterator end_iter = remove_if(sLine.begin(),
						      sLine.end(), ::isspace);
		string::size_type pos = sLine.find_first_of("=", 0, end_iter - sLine.begin());
		if (pos == string::npos) {
			sLine.clear();
			continue;
		}
		string title = string(sLine.c_str(), pos);
		string value = string(sLine.c_str() + pos + 1,
				      end_iter - sLine.begin() - pos - 1);

		rMap.insert(pair<string, string>(title, value));

		sLine.clear();
	}

	ifile.close();

	return true;
err:
	return false;
}

bool CVitoConfig::writeFile(const char * path, const map < string, string > & rcMap,
	bool bMerge)
{
	ofstream ofile;
	map<string, string> mapOldContext;
	map<string, string> mergeMap = rcMap;
	map<string, string>::iterator iter;

	if (bMerge) {
		readFile(path, mapOldContext);
	}

	ofile.open(path, ios_base::out | ios_base::trunc );
	if (!ofile.is_open()) {
		return false;
	}

	for (iter = mapOldContext.begin(); iter != mapOldContext.end(); iter++) {
		map<string, string>::iterator iter1 = mergeMap.find(iter->first);
		if (iter == mergeMap.end()) {
			mergeMap.insert(pair<string, string>(iter1->first, iter1->second));
		}
	}

	for (iter = mergeMap.begin(); iter != mergeMap.end(); iter++) {
		ofile << iter->first << "=" << iter->second << endl;
	}

	ofile.close();

	return true;
}
