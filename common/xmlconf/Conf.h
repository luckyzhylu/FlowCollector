#ifndef __VITO__XML__CONF__CONF__H__
#define __VITO__XML__CONF__CONF__H__

#include <Public.h>
#include <Node.h>
#include <Error.h>

NS_VITO_XML_CONF

/**
 * @class CConf
 * @brief XML配置文件类
 *
 * 用于从XML文件或XML文本构造出一个包含'CNode'的节点树。
 *
 * <pre>
 * 读取XML文件使用示例：
 * using namespace Venus::Xml::Conf;
 * CConf conf;
 * conf.LoadXmlFile(sConfigFile);
 * CNode nodeRoot = conf.GetRootNode();
 * CNode nodeChild = nodeRoot.GetFirstChildByName(sNodeName);
 * if(CNode::NullNode != nodeChild)
 * {
 * 　　string str = nodeChild.GetAttribute(sAttribute);
 * 　　// ......
 * }
 * conf.SaveXmlFile(sConfigFile);
 * </pre>
 *
 * @note
 * 当CConf的对象销毁之后，和该CConf对象关联的CNode将失效，禁止再使用。<br>
 * 使用中要注意保证CConf对象的生命周期超过对应的CNode对象的生命周期。<br>
 */


class CConfImpl;
class CConf
{
public:
	/**
	 * 默认构造函数
	 */
	CConf() throw();

	/**
	 * 析构函数
	 */
	~CConf() throw();

	/**
	 * 从XML文件读取文档对象
	 *
	 * @param[in] rcsFile		XML文件名
	 *
	 * @note
	 * 如果文件无法打开或者文件格式不正确，抛出CError异常
	 */
	void LoadXmlFile(const string& rcsFile) throw(CError);

	/**
	 * 从XML文本读取文档对象
	 *
	 * @param[in] rcsText		XML文本
	 *
	 * @note
	 * 如果XML文本格式不正确，抛出CError异常
	 */
	void LoadXmlText(const string& rcsText) throw(CError);

	/**
	 * 保存文档对象到XML文件
	 *
	 * @param[in] rcsFile	XML文件名
	 *
	 * @note
	 * 如果文件无法打开，抛出CError异常
	 */
	void SaveXmlFile(const string& rcsFile) const throw(CError);

	/**
	 * 保存文档对象到XML文本
	 *
	 * @param[out] rsText	XML文本
	 */
	void SaveXmlText(string& rsText) const throw(CError);

	/**
	 * 清空该对象
	 *
	 * @note
	 * 清空后调用'GetRootNode()'将返回空节点
	 */
	void Clear();

	/**
	 * 判断该对象是否为空
	 *
	 * @retval true			表示文档对象为空，此时'GetRootNode'返回空节点
	 * @retval false		表示文档对象非空
	 */
	bool Empty() const throw();

	/**
	 * 获得根节点对象
	 * 
	 * @return				文档对象根节点
	 */
	const CNode GetRootNode() const throw();

protected:
	/**
	 * @note
	 * 定义非公开的拷贝构造函数，防止被使用
	 */
	CConf(const CConf& rcNodeOther);
	/**
	 * @note
	 * 定义非公开的重载赋值运算符，防止被使用
	 */
	bool operator=(const CConf& rcNodeOther);

protected:
	CConfImpl* m_pConfImpl;
};

NS_END_LAYER_3

#endif // __VITO__XML__CONF__CONF__H__
