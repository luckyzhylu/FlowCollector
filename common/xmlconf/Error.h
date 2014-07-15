#ifndef __VITO__XML__CONF__ERROR__H__
#define __VITO__XML__CONF__ERROR__H__

#include <Public.h>
#include <string>

using namespace std;

NS_VITO_XML_CONF

/**
 * @class CError
 * @brief XML�쳣��
 *
 * �ڲ���XML�ļ���XML�ڵ�����쳣ʱ���׳����ࡣ<br>
 * ����ͨ��catch(CError&)���в���
 */


class CError : public std::runtime_error
{
public:
	/**
	 * ���캯��
	 *
	 * @param[in] pcszDesc	�쳣����
	 */
	explicit CError(const string& rcsDesc) throw();

	/**
	 * ��������
	 */
	virtual ~CError() throw();
};

NS_END_LAYER_3

#endif // #ifndef __VITO__XML__CONF__ERROR__H__
