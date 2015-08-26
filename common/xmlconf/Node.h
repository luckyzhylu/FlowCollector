#ifndef __VITO__XML__CONF__NODE__H__
#define __VITO__XML__CONF__NODE__H__

#include <Public.h>
#include <Error.h>
#include <map>

NS_VITO_XML_CONF

/**
 * @class CNode
 * @brief XML节点类
 *
 * 用于提供节点的各种操作功能（添加、删除、修改）。<br>
 *
 * \section name 注意事项
 *
 * \subsection null_node 空节点
 * <pre>
 * 如果某个节点为空节点，则操作该节点的成员函数将抛出CError异常。
 * 可以使用如下示例判断某个节点为空：
 * if(CNode::NullNode == node1)
 * {
 * 　　// ......
 * }
 * </pre>
 *
 * \subsection node_name 节点名规范
 * 节点名只能包含字母、数字和下划线，并且只能以字母或下划线开头
 *
 * \subsection attribute_name 属性名规范
 * 属性名只能包含字母、数字和下划线，并且只能以字母或下划线开头
 */


class CNodeImpl;
class CNode
{
public:
	/**
	 * 默认构造函数
	 *
	 * @note
	 * 刚构造好的对象为空节点
	 */
	CNode() throw();

	/**
	 * 构造函数
	 *
	 * @note
	 * 该函数为内部使用
	 */
	CNode(CNodeImpl* pNodeImpl) throw();

	/**
	 * 析构函数
	 */
	~CNode() throw();


	/** 
	 * 获取节点的值
	 * 
	 * @return 节点值
	 */
	const string& GetValue() const;


	/** 
	 * 设置节点的值
	 * 
	 * @param[in] rcsValue 节点值
	 */
	void SetValue(const string& rcsValue) throw(CError);

	/**
	 * 获得节点名称
	 *
	 * @return	节点名称
	 */
	const string& GetName() const throw(CError);

	/**
	 * 设置节点名称
	 *
	 * @param[in] rcsName		节点名称
	 *
	 * @pre						rcsName 必须符合 @ref node_name
	 */
	void SetName(const string& rcsName) throw(CError);

	/**
	 * 插入第一个子节点
	 *
	 * @param[in] rcsName		新节点的名称
	 * @return					被插入的节点对象
	 *
	 * @pre						rcsName 必须符合 @ref node_name
	 */
	const CNode InsertFirstChild(const string& rcsName) throw(CError);

	/**
	 * 插入下一个兄弟节点
	 *
	 * @param[in] rcsName		新节点的名称
	 * @return					被插入的节点对象
	 *
	 * @pre						rcsName 必须符合 @ref node_name
	 */
	const CNode InsertNextSibling(const string& rcsName) throw(CError);

	/**
	 * 删除指定名称的子节点
	 *
	 * @note
	 * 当前节点被删除之后，将成为空节点。<br>
	 * 对根节点执行该操作将抛出'CError'异常。
	 */
	void Delete() throw(CError);

	/**
	 * 获得指定名称的属性值
	 *
	 * @param[in] rcsName		属性名称
	 * @return					属性值
	 *
	 * @pre						rcsName 必须符合 @ref attribute_name
	 */
	const string GetAttribute(const string& rcsName) const throw(CError);

	/**
	 * 设置指定名称的属性值
	 *
	 * @param[in] rcsName		属性名称
	 * @param[in] rcsValue		属性值
	 *
	 * @pre						rcsName 必须符合 @ref attribute_name
	 */
	void SetAttribute(const string& rcsName,
						const string& rcsValue) throw(CError);


	void GetAttrMap(std::map<string, string>& rAttrMap) const;
	void SetAttrMap(std::map<string, string>& rcAttrMap);

	/**
	 * 删除指定名称的属性
	 *
	 * @param[in] rcsName		属性名称
	 *
	 * @pre						rcsName 必须符合 @ref attribute_name
	 */
	void RemoveAttribute(const string& rcsName) throw(CError);

	/**
	 * 获得当前节点的父节点
	 *
	 * @return					父节点
	 *
	 * @note
	 * 对于根节点，该调用返回空节点
	 */
	const CNode GetParent() const throw(CError);

	/**
	 * 获得第一个子节点
	 *
	 * @return					第一个子节点
	 *
	 * @note
	 * 如果当前节点没有子节点，返回空节点
	 */
	const CNode GetFirstChild() const throw(CError);

	/**
	 * 获得下一个兄弟节点
	 *
	 * @return					下一个兄弟节点
	 *
	 * @note
	 * 如果当前节点没有下一个兄弟节点，返回空节点
	 */
	const CNode GetNextSibling() const throw(CError);

	/**
	 * 获得第一个符合名称的子节点
	 *
	 * @param[in] rcsName		指定的节点名称
	 * @return					第一个符合名称的子节点
	 *
	 * @pre						rcsName 必须符合 @ref node_name
	 */
	const CNode GetFirstChildByName(const string& rcsName)
									const throw(CError);

	/**
	 * 获得下一个符合名称的兄弟节点
	 *
	 * @param[in] rcsName		指定的节点名称
	 * @return					下一个符合名称的兄弟节点
	 *
	 * @pre						rcsName 必须符合 @ref node_name
	 */
	const CNode GetNextSiblingByName(const string& rcsName)
									const throw(CError);

	/**
	 * 根据路径获得节点
	 *
	 * @param[in] rcsPath		指定的节点路径
	 * @return					符合该路径的节点
	 *
	 * @note
	 * 路径字符串的格式如下“/node1/node2/node3”
	 */
	const CNode GetChildByPath(const string& rcsPath) const throw(CError);

	/**
	 * 重载等于运算符
	 *
	 * @param[in] rcNodeOther	进行比较的另一个节点对象
	 * @retval true				比较结果相等
	 * @retval false			比较结果不相等
	 */
	bool operator==(const CNode& rcNodeOther) const throw(CError);

	/**
	 * 重载不等于运算符
	 *
	 * @param[in] rcNodeOther	进行比较的另一个节点对象
	 * @retval true				比较结果不相等
	 * @retval false			比较结果相等
	 */
	bool operator!=(const CNode& rcNodeOther) const throw(CError);

	/**
	 * 获取节点对应的字符串
	 *
	 * @return					节点对应的字符串
	 *
	 * @note
	 * 该函数将递归调用所有子节点的相应函数，返回的字符串是一个XML文本
	 */
	const string ToString() const throw(CError);

protected:
	const CNodeImpl* GetNodeImpl() const throw(CError);
	CNodeImpl* GetNodeImpl() throw(CError);

public:
	/**
	 * @note
	 * 该静态对象用于进行节点是否为空的判断，使用Null Object模式
	 */
	static CNode NullNode;

protected:
	CNodeImpl* m_pNodeImpl;
};

NS_END_LAYER_3

#endif // __VITO__XML__CONF__NODE__H__
