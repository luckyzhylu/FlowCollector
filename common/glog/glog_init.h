#ifndef _GLOG_INIT_H_
#define _GLOG_INIT_H_

#include <glog/logging.h>
#include <stdexcept>

using namespace std;

class CGlogInit
{
public:
	/** 
	 * ��ʼ��glog��־,���Ե���־����ͨ�������л��߻�������������
	 * 
	 * @param progName ���������,ͨ��Ϊargv[0]
	 */
	static void GlogInit(const char *progName);

	/** 
	 * ��ʼ��glog��־,ͨ��ָ���������ļ�������glog��־��Ĭ�ϲ���ֵ;����ͨ�������л�
	 * ���������������Ѿ����õ�Ĭ��ֵ
	 * 
	 * @param progName ���������,ͨ��Ϊargv[0]
	 * @param logConfigFile �����ļ���ȫ·��
	 *
	 * @note �����־�ļ���ʽ����,���׳��쳣
	 */
	static void GLogInitConfig(const char *progName, const char *logConfigFile) throw(logic_error);
};



#endif /* _GLOG_INIT_H_ */



