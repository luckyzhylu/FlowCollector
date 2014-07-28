#ifndef _CLISTHEAD_H_
#define _CLISTHEAD_H_

/**
 * @file   CListHead.h
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date   Mon Jul 28 10:43:06 2014
 * 
 * @brief  ˫������ı�ͷ���ṩ����������ͷ������β�Ĳ����ɾ������������ı���������m_head��m_tail��ָ��
 *         ͬһ���ڵ㣻RemoveHead()��ɾ��ͷ�ڵ㣻RemoveTail()��ɾ��β�ڵ��prev�ڵ㣻
 * 
 * @note 1. Ҫ�������м�����ɾ�����������ȱ����ҵ�λ�ú��ٲ�����
 *       2. ʵ��δ���ڴ��ַУ�飬����ʱҪ��֤��ַ��ȷ��
 *       3. CListHead���ṩ��Ŀ������죻
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
	 * ɾ�������β�ڵ㣬ʵ����ɾ��m_tail->m_prev�ڵ㣻�������ֻ��һ��Ԫ��ʱ�Ż�ɾ����ͷ�ڵ�
	 *
	 * @return ɾ���ɹ��򷵻ر�ɾ���Ľڵ㣬����շ���NULL
	 *
	 * @note ���صĵ�ַ�����������Ƿ���Ч�ɵ���ʱУ��Ϳ���
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
	 * ɾ�������ͷ�㣬ʵ����ɾ��m_head�ڵ�;ɾ��ͷ�ڵ�֮��ͷ�ڵ��ָ��m_head->m_next
	 *
	 * @return ɾ���ɹ��򷵻ر�ɾ���Ľڵ㣬����շ���NULL
	 *
	 * @note ���صĵ�ַ�����������Ƿ���Ч�ɵ���ʱУ��Ϳ���
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
