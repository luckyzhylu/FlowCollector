#ifndef __VITO__XML__CONF__ERROR__H__
#define __VITO__XML__CONF__ERROR__H__

#include <Public.h>
#include <string>

using namespace std;

NS_VITO_XML_CONF

/**
 * @class CError
 * @brief XML异常类
 *
 * 在操作XML文件或XML节点出现异常时，抛出该类。<br>
 * 可以通过catch(CError&)进行捕获。
 */


class CError : public std::runtime_error
{
public:
	/**
	 * 构造函数
	 *
	 * @param[in] pcszDesc	异常描述
	 */
	explicit CError(const string& rcsDesc) throw();

	/**
	 * 析构函数
	 */
	virtual ~CError() throw();
};

NS_END_LAYER_3

#endif // #ifndef __VITO__XML__CONF__ERROR__H__
