#ifndef __VITO__XML__CONF__CONF__H__
#define __VITO__XML__CONF__CONF__H__

#include <Public.h>
#include <Node.h>
#include <Error.h>

NS_VITO_XML_CONF

/**
 * @class CConf
 * @brief XML�����ļ���
 *
 * ���ڴ�XML�ļ���XML�ı������һ������'CNode'�Ľڵ�����
 *
 * <pre>
 * ��ȡXML�ļ�ʹ��ʾ����
 * using namespace Venus::Xml::Conf;
 * CConf conf;
 * conf.LoadXmlFile(sConfigFile);
 * CNode nodeRoot = conf.GetRootNode();
 * CNode nodeChild = nodeRoot.GetFirstChildByName(sNodeName);
 * if(CNode::NullNode != nodeChild)
 * {
 * ����string str = nodeChild.GetAttribute(sAttribute);
 * ����// ......
 * }
 * conf.SaveXmlFile(sConfigFile);
 * </pre>
 *
 * @note
 * ��CConf�Ķ�������֮�󣬺͸�CConf���������CNode��ʧЧ����ֹ��ʹ�á�<br>
 * ʹ����Ҫע�Ᵽ֤CConf������������ڳ�����Ӧ��CNode������������ڡ�<br>
 */


class CConfImpl;
class CConf
{
public:
	/**
	 * Ĭ�Ϲ��캯��
	 */
	CConf() throw();

	/**
	 * ��������
	 */
	~CConf() throw();

	/**
	 * ��XML�ļ���ȡ�ĵ�����
	 *
	 * @param[in] rcsFile		XML�ļ���
	 *
	 * @note
	 * ����ļ��޷��򿪻����ļ���ʽ����ȷ���׳�CError�쳣
	 */
	void LoadXmlFile(const string& rcsFile) throw(CError);

	/**
	 * ��XML�ı���ȡ�ĵ�����
	 *
	 * @param[in] rcsText		XML�ı�
	 *
	 * @note
	 * ���XML�ı���ʽ����ȷ���׳�CError�쳣
	 */
	void LoadXmlText(const string& rcsText) throw(CError);

	/**
	 * �����ĵ�����XML�ļ�
	 *
	 * @param[in] rcsFile	XML�ļ���
	 *
	 * @note
	 * ����ļ��޷��򿪣��׳�CError�쳣
	 */
	void SaveXmlFile(const string& rcsFile) const throw(CError);

	/**
	 * �����ĵ�����XML�ı�
	 *
	 * @param[out] rsText	XML�ı�
	 */
	void SaveXmlText(string& rsText) const throw(CError);

	/**
	 * ��ոö���
	 *
	 * @note
	 * ��պ����'GetRootNode()'�����ؿսڵ�
	 */
	void Clear();

	/**
	 * �жϸö����Ƿ�Ϊ��
	 *
	 * @retval true			��ʾ�ĵ�����Ϊ�գ���ʱ'GetRootNode'���ؿսڵ�
	 * @retval false		��ʾ�ĵ�����ǿ�
	 */
	bool Empty() const throw();

	/**
	 * ��ø��ڵ����
	 * 
	 * @return				�ĵ�������ڵ�
	 */
	const CNode GetRootNode() const throw();

protected:
	/**
	 * @note
	 * ����ǹ����Ŀ������캯������ֹ��ʹ��
	 */
	CConf(const CConf& rcNodeOther);
	/**
	 * @note
	 * ����ǹ��������ظ�ֵ���������ֹ��ʹ��
	 */
	bool operator=(const CConf& rcNodeOther);

protected:
	CConfImpl* m_pConfImpl;
};

NS_END_LAYER_3

#endif // __VITO__XML__CONF__CONF__H__
