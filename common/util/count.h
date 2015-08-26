/**
 * Copyright (C) 2014 zhang yunlu
 *
 * This code has been released into the Public Domain.
 * You may do whatever you like with it.
 *
 * @file
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date 2014-05-29
 */


#ifndef COUNT_H_
#define COUNT_H_

template <class T>
class CCount
{
public:

	CCount():
		m_countNum(0),
		m_lastCountNum(0){
	}

	CCount(int num) {
		m_countNum += num;
	}


	virtual ~CCount(){}

	void operator++(int) {
		m_countNum++;
	}
	void operator--(int) {
		m_countNum--;
	}
	void operator+=(int num) {
		m_countNum += num;
	}
	void operator-=(int num) {
		m_countNum -= num;
	}

	long long unsigned int GetCount() {
		return m_countNum;
	}
	long long unsigned int GetInterval(bool bClear = false) {
		long long unsigned int num = m_countNum - m_lastCountNum;
		if (bClear) {
			m_lastCountNum = m_countNum;
		}
		return num;
	}
private:
	CCount(const CCount& rhs);
	CCount& operator=(const CCount& rhs);
private:
	long long unsigned int m_countNum;
	long long unsigned int m_lastCountNum;
};


#endif // COUNT_H_
