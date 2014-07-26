#ifndef _CLIST_H_
#define _CLIST_H_

/**
 * @file   clist.h
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date   Sat Jul 26 11:35:41 2014
 * 
 * @brief  ˫�������ṩ��������Ĳ����ɾ��������

 * @note 1.δ�ṩ��������Ҫ�����������ʹ��Prev()��Next()����ʵ��
 *       2.δ�ṩ�������ܣ���Ҫ�����ڶ���CList��ͬʱ�ٶ�������ֶ�
 *       3.��ֹ��������
 *       4.�����Ƿ��̰߳�ȫ�ģ����ж��̲߳�����Ҫ����ʱ����
 */

#include <iostream>
#include <cassert>

#define OFFSET_OF(str, member)	((char *)(&((str *)0)->member) - (char *)0)

class CList
{

public:
	CList(): m_prev(this), m_next(this) {
	}
	CList(CList *prev, CList *next):m_prev(prev), m_next(next) {
	}
	virtual ~CList() {}
public:
	CList *Prev() {
		return m_prev;
	}
	CList *Next() {
		return m_next;
	}

	void InsertNext(CList *rcNew) {
		assert(rcNew);
		rcNew->m_prev = this;
		rcNew->m_next = m_next;

		m_next = rcNew;
		m_next->m_prev = rcNew;
	}

	void InsertFront(CList *rcNew) {
		assert(rcNew);
		rcNew->m_next = this;
		rcNew->m_prev = m_prev;

		m_prev->m_next = rcNew;
		m_prev = rcNew;
	}

	CList *Delete() {
		m_prev->m_next = m_next;
		m_next->m_prev = m_prev;

		m_next = m_prev = this;

		return this;
	}

	size_t Count() {
		size_t n = 1;
		for (CList *p = m_next; p != this; p = p->m_next) {
			n++;
		}

		return n;
	}


private:
	CList(const CList& rc);
	CList& operator=(const CList& rc);
protected:
	CList *m_prev;
	CList *m_next;
};

#endif /* _CLIST_H_ */
