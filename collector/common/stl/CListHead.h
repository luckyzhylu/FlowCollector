#ifndef _CLISTHEAD_H_
#define _CLISTHEAD_H_

/**
 * @file   CListHead.h
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date   Mon Jul 28 10:43:06 2014
 * 
 * @brief  双向链表的表头，提供基本的链表头和链表尾的插入和删除操作，链表的遍历操作；m_head和m_tail都指向
 *         同一个节点；RemoveHead()是删除头节点；RemoveTail()是删除尾节点的prev节点；
 * 
 * @note 1. 要在链表中间插入和删除操作，需先遍历找到位置后再操作；
 *       2. 实现未对内存地址校验，调用时要保证地址正确；
 *       3. CListHead不提供类的拷贝构造；
 */

#include "clist.h"

class CListHead
{
public:
	CListHead(): m_head(NULL)
		   , m_tail(NULL)
		   ,m_listSize(0) {
	}

	virtual ~CListHead() {}

	void InsertTail(CList *list) {
		if (m_listSize == 0) {
			m_head = m_tail = list;
		} else {
			m_tail->InsertFront(list);
		}
		m_listSize++;
	}

	void InsertHead(CList *list) {
		if (m_listSize == 0) {
			m_head = m_tail = list;
		} else {
			m_head->InsertNext(list);
		}
		m_listSize++;
	}

	CList *Head() {
		return m_head;
	}

	CList *Tail() {
		return m_tail;
	}

	/** 
	 * 删除链表的尾节点，实际是删除m_tail->m_prev节点；如果链表只有一个元素时才会删除表头节点
	 *
	 * @return 删除成功则返回被删除的节点，链表空返回NULL
	 *
	 * @note 返回的地址的生命周期是否有效由调用时校验和考虑
	 */
	CList* RemoveTail() {
		CList *p = NULL;

		if (m_listSize == 0) {
			return NULL;
		} else if (m_listSize == 1) {
			p = m_tail;
			m_head = m_tail = NULL;
			m_listSize--;

			return p;
		} else {
			p = m_tail->Prev();
			p->Delete();
			m_listSize--;

			return p;
		}
	}

	/** 
	 * 删除链表的头点，实际是删除m_head节点;删除头节点之后，头节点会指向m_head->m_next
	 *
	 * @return 删除成功则返回被删除的节点，链表空返回NULL
	 *
	 * @note 返回的地址的生命周期是否有效由调用时校验和考虑
	 */
	CList* RemoveHead() {
		CList *p = NULL;

		if (m_listSize == 0) {
			return NULL;
		} else if (m_listSize == 1) {
			p = m_head;
			m_head = m_tail = NULL;
			m_listSize--;

			return p;
		} else {
			p = m_head;

			m_tail = m_head = p->Next();
			p->Delete();
			m_listSize--;

			return p;
		}
	}

	int Size() { return m_listSize; }


	/** 
	 * 
	 * 
	 * @param bFree 
	 */
	void Destroy(bool bFree = false) {

	}

private:
	CListHead(const CListHead& rc);
	CListHead& operator=(const CListHead& rc);
private:
	CList *m_head;
	CList *m_tail;
	int m_listSize;
};



#endif /* _CLISTHEAD_H_ */
