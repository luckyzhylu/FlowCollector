#ifndef __VITO__XML__CONF__NODE__H__
#define __VITO__XML__CONF__NODE__H__

#include <Public.h>
#include <Error.h>
#include <map>

NS_VITO_XML_CONF

/**
 * @class CNode
 * @brief XML�ڵ���
 *
 * �����ṩ�ڵ�ĸ��ֲ������ܣ���ӡ�ɾ�����޸ģ���<br>
 *
 * \section name ע������
 *
 * \subsection null_node �սڵ�
 * <pre>
 * ���ĳ���ڵ�Ϊ�սڵ㣬������ýڵ�ĳ�Ա�������׳�CError�쳣��
 * ����ʹ������ʾ���ж�ĳ���ڵ�Ϊ�գ�
 * if(CNode::NullNode == node1)
 * {
 * ����// ......
 * }
 * </pre>
 *
 * \subsection node_name �ڵ����淶
 * �ڵ���ֻ�ܰ�����ĸ�����ֺ��»��ߣ�����ֻ������ĸ���»��߿�ͷ
 *
 * \subsection attribute_name �������淶
 * ������ֻ�ܰ�����ĸ�����ֺ��»��ߣ�����ֻ������ĸ���»��߿�ͷ
 */


class CNodeImpl;
class CNode
{
public:
	/**
	 * Ĭ�Ϲ��캯��
	 *
	 * @note
	 * �չ���õĶ���Ϊ�սڵ�
	 */
	CNode() throw();

	/**
	 * ���캯��
	 *
	 * @note
	 * �ú���Ϊ�ڲ�ʹ��
	 */
	CNode(CNodeImpl* pNodeImpl) throw();

	/**
	 * ��������
	 */
	~CNode() throw();


	/** 
	 * ��ȡ�ڵ��ֵ
	 * 
	 * @return �ڵ�ֵ
	 */
	const string& GetValue() const;


	/** 
	 * ���ýڵ��ֵ
	 * 
	 * @param[in] rcsValue �ڵ�ֵ
	 */
	void SetValue(const string& rcsValue) throw(CError);

	/**
	 * ��ýڵ�����
	 *
	 * @return	�ڵ�����
	 */
	const string& GetName() const throw(CError);

	/**
	 * ���ýڵ�����
	 *
	 * @param[in] rcsName		�ڵ�����
	 *
	 * @pre						rcsName ������� @ref node_name
	 */
	void SetName(const string& rcsName) throw(CError);

	/**
	 * �����һ���ӽڵ�
	 *
	 * @param[in] rcsName		�½ڵ������
	 * @return					������Ľڵ����
	 *
	 * @pre						rcsName ������� @ref node_name
	 */
	const CNode InsertFirstChild(const string& rcsName) throw(CError);

	/**
	 * ������һ���ֵܽڵ�
	 *
	 * @param[in] rcsName		�½ڵ������
	 * @return					������Ľڵ����
	 *
	 * @pre						rcsName ������� @ref node_name
	 */
	const CNode InsertNextSibling(const string& rcsName) throw(CError);

	/**
	 * ɾ��ָ�����Ƶ��ӽڵ�
	 *
	 * @note
	 * ��ǰ�ڵ㱻ɾ��֮�󣬽���Ϊ�սڵ㡣<br>
	 * �Ը��ڵ�ִ�иò������׳�'CError'�쳣��
	 */
	void Delete() throw(CError);

	/**
	 * ���ָ�����Ƶ�����ֵ
	 *
	 * @param[in] rcsName		��������
	 * @return					����ֵ
	 *
	 * @pre						rcsName ������� @ref attribute_name
	 */
	const string GetAttribute(const string& rcsName) const throw(CError);

	/**
	 * ����ָ�����Ƶ�����ֵ
	 *
	 * @param[in] rcsName		��������
	 * @param[in] rcsValue		����ֵ
	 *
	 * @pre						rcsName ������� @ref attribute_name
	 */
	void SetAttribute(const string& rcsName,
						const string& rcsValue) throw(CError);


	void GetAttrMap(std::map<string, string>& rAttrMap) const;
	void SetAttrMap(std::map<string, string>& rcAttrMap);

	/**
	 * ɾ��ָ�����Ƶ�����
	 *
	 * @param[in] rcsName		��������
	 *
	 * @pre						rcsName ������� @ref attribute_name
	 */
	void RemoveAttribute(const string& rcsName) throw(CError);

	/**
	 * ��õ�ǰ�ڵ�ĸ��ڵ�
	 *
	 * @return					���ڵ�
	 *
	 * @note
	 * ���ڸ��ڵ㣬�õ��÷��ؿսڵ�
	 */
	const CNode GetParent() const throw(CError);

	/**
	 * ��õ�һ���ӽڵ�
	 *
	 * @return					��һ���ӽڵ�
	 *
	 * @note
	 * �����ǰ�ڵ�û���ӽڵ㣬���ؿսڵ�
	 */
	const CNode GetFirstChild() const throw(CError);

	/**
	 * �����һ���ֵܽڵ�
	 *
	 * @return					��һ���ֵܽڵ�
	 *
	 * @note
	 * �����ǰ�ڵ�û����һ���ֵܽڵ㣬���ؿսڵ�
	 */
	const CNode GetNextSibling() const throw(CError);

	/**
	 * ��õ�һ���������Ƶ��ӽڵ�
	 *
	 * @param[in] rcsName		ָ���Ľڵ�����
	 * @return					��һ���������Ƶ��ӽڵ�
	 *
	 * @pre						rcsName ������� @ref node_name
	 */
	const CNode GetFirstChildByName(const string& rcsName)
									const throw(CError);

	/**
	 * �����һ���������Ƶ��ֵܽڵ�
	 *
	 * @param[in] rcsName		ָ���Ľڵ�����
	 * @return					��һ���������Ƶ��ֵܽڵ�
	 *
	 * @pre						rcsName ������� @ref node_name
	 */
	const CNode GetNextSiblingByName(const string& rcsName)
									const throw(CError);

	/**
	 * ����·����ýڵ�
	 *
	 * @param[in] rcsPath		ָ���Ľڵ�·��
	 * @return					���ϸ�·���Ľڵ�
	 *
	 * @note
	 * ·���ַ����ĸ�ʽ���¡�/node1/node2/node3��
	 */
	const CNode GetChildByPath(const string& rcsPath) const throw(CError);

	/**
	 * ���ص��������
	 *
	 * @param[in] rcNodeOther	���бȽϵ���һ���ڵ����
	 * @retval true				�ȽϽ�����
	 * @retval false			�ȽϽ�������
	 */
	bool operator==(const CNode& rcNodeOther) const throw(CError);

	/**
	 * ���ز����������
	 *
	 * @param[in] rcNodeOther	���бȽϵ���һ���ڵ����
	 * @retval true				�ȽϽ�������
	 * @retval false			�ȽϽ�����
	 */
	bool operator!=(const CNode& rcNodeOther) const throw(CError);

	/**
	 * ��ȡ�ڵ��Ӧ���ַ���
	 *
	 * @return					�ڵ��Ӧ���ַ���
	 *
	 * @note
	 * �ú������ݹ���������ӽڵ����Ӧ���������ص��ַ�����һ��XML�ı�
	 */
	const string ToString() const throw(CError);

protected:
	const CNodeImpl* GetNodeImpl() const throw(CError);
	CNodeImpl* GetNodeImpl() throw(CError);

public:
	/**
	 * @note
	 * �þ�̬�������ڽ��нڵ��Ƿ�Ϊ�յ��жϣ�ʹ��Null Objectģʽ
	 */
	static CNode NullNode;

protected:
	CNodeImpl* m_pNodeImpl;
};

NS_END_LAYER_3

#endif // __VITO__XML__CONF__NODE__H__
