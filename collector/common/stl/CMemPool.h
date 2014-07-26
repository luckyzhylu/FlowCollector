#ifndef _CMEMPOOL_H_
#define _CMEMPOOL_H_

/**
 * @file   CMemPool.h
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date   Sat Jul 26 14:37:35 2014
 * 
 * @brief  
 * 
 * 
 */

#include "clist.h"
#include <stdio.h>

template <size_t _size, int _num = 1000 >
class CMemPool
{
	typedef struct _MemBucket {
		CList list;
		char data[_size];
	} MemBucket;
public:
	CMemPool(): m_emptyNum(0), m_usedNum(0),
		    m_emptyList(NULL), m_usedList(NULL) {}

	virtual ~CMemPool() {}

	void Init() {
		for (int i = 0; i < m_maxNum; i++) {
			MemBucket *bucket = new MemBucket();
			// printf("start=%p, list=%p, data=%p\n", bucket, &bucket->list, &bucket->data);
			m_emptyNum++;
			if (i == 0) {
				m_emptyList = &bucket->list;
			} else {
				m_emptyList->InsertNext(&bucket->list);
			}
		}
	}

	void *Malloc() {
		if (m_emptyNum == 0) {
			return NULL;
		}

		assert(m_emptyList);
		m_emptyNum--;
		CList *cur = m_emptyList;
		m_emptyList = m_emptyList->Next();
		cur->Delete();

		if (m_usedNum == 0) {
			m_usedList = cur;
		} else {
			m_usedList->InsertNext(cur);
		}
		m_usedNum++;
		// printf("Malloc:emptyNum=%d,usedNum=%d\n", m_emptyNum, m_usedNum);
		// printf("Malloc addr=%p\n",  (void *)(((MemBucket *)cur)->data));
		return (void *)(((MemBucket *)cur)->data);
	}

	void Free(void *pMem) {
		// printf("Free addr=%p\n", pMem);
		MemBucket *p = (MemBucket *)((char *)pMem - m_offset);

		CList *list = &p->list;
		list->Delete();
		m_usedNum--;

		if (m_emptyNum == 0) {
			m_emptyList = list;
		} else {
			m_emptyList->InsertNext(list);
		}
		m_emptyNum++;
		printf("Free:emptyNum=%d,usedNum=%d\n", m_emptyNum, m_usedNum);
	}
private:
	CMemPool(const CMemPool& rc);
	CMemPool& operator=(const CMemPool& rc);
private:
	int m_emptyNum;
	int m_usedNum;
	CList *m_emptyList;
	CList *m_usedList;

	// static const int m_offset = OFFSET_OF(MemBucket, data);
	static const int m_offset = 24;
	static const int m_maxNum = _num;
};

#endif /* _CMEMPOOL_H_ */
