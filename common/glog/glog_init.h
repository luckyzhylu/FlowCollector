#ifndef _GLOG_INIT_H_
#define _GLOG_INIT_H_

#include <glog/logging.h>
#include <stdexcept>

using namespace std;

class CGlogInit
{
public:
	/** 
	 * 初始化glog日志,所以得日志参数通过命令行或者环境变量来设置
	 * 
	 * @param progName 程序的名称,通常为argv[0]
	 */
	static void GlogInit(const char *progName);

	/** 
	 * 初始化glog日志,通过指定的配置文件来设置glog日志的默认参数值;可以通过命令行或
	 * 环境变量来更改已经设置的默认值
	 * 
	 * @param progName 程序的名称,通常为argv[0]
	 * @param logConfigFile 配置文件的全路径
	 *
	 * @note 如果日志文件格式有误,会抛出异常
	 */
	static void GLogInitConfig(const char *progName, const char *logConfigFile) throw(logic_error);
};



#endif /* _GLOG_INIT_H_ */



