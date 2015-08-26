#include "glog_init.h"
#include "Conf.h"

#include <cassert>
#include <map>
#include <string>
#include <algorithm>

using namespace XmlConf;

/**
 * @file   glog_init.cpp
 * @author zhang yunlu <luckyzhylu@163.com>
 * @date   Thu Jun 12 15:10:13 2014
 *
 * @brief  config glog flags
 *//*
// Set whether log messages go to stderr instead of logfiles
DECLARE_bool(logtostderr);

// Set whether log messages go to stderr in addition to logfiles.
DECLARE_bool(alsologtostderr);

// Log messages at a level >= this flag are automatically sent to
// stderr in addition to log files.
DECLARE_int32(stderrthreshold);

// Set whether the log prefix should be prepended to each line of output.
DECLARE_bool(log_prefix);

// Log messages at a level <= this flag are buffered.
// Log messages at a higher level are flushed immediately.
DECLARE_int32(logbuflevel);

// Sets the maximum number of seconds which logs may be buffered for.
DECLARE_int32(logbufsecs);

// Log suppression level: messages logged at a lower level than this
// are suppressed.
DECLARE_int32(minloglevel);

// If specified, logfiles are written into this directory instead of the
// default logging directory.
DECLARE_string(log_dir);

// Sets the path of the directory into which to put additional links
// to the log files.
DECLARE_string(log_link);

DECLARE_int32(v);  // in vlog_is_on.cc

// Sets the maximum log file size (in MB).
DECLARE_int32(max_log_size);
 */


void CGlogInit::GlogInit(const char *progName)
{
	FLAGS_logtostderr = false;
	FLAGS_minloglevel = 0;
	FLAGS_stderrthreshold = 0;
	FLAGS_alsologtostderr = true;
	FLAGS_minloglevel = 1;
	FLAGS_log_dir = "";
	FLAGS_v = 1;
	// FLAGS_vmodule = "";
	FLAGS_max_log_size = 20;	// MB
	FLAGS_log_prefix = true;

	google::InitGoogleLogging(progName);
}

void CGlogInit::GLogInitConfig(const char *progName, const char *logConfigFile) throw(logic_error)
{
	assert(logConfigFile != NULL);
	map<string, string> mapGlogConf;

	try {
		CConf conf;
		conf.LoadXmlFile(logConfigFile);

		CNode rootNode = conf.GetRootNode();
		if (rootNode == CNode::NullNode) {
			throw logic_error(string(logConfigFile) + ": have no root node.");
		}


		CNode glogNode = rootNode.GetChildByPath("/glog_config");
		CNode node = glogNode.GetFirstChild();
		while (node != CNode::NullNode) {
			string name = node.GetName();
			string value = node.GetValue();
			transform(name.begin(), name.end(), name.begin(), ::tolower);
			transform(value.begin(), value.end(), value.begin(), ::tolower);
			mapGlogConf[name] = value;

			node = node.GetNextSibling();
		}
	} catch (CError &e) {
		throw logic_error(string("GLogInitConfig::") + e.what());
	}

	/**
	 * ��־�Ƿ�Ҫ�������׼����
	 * 
	 */

	if (mapGlogConf["logtostderr"] == "true") {
		FLAGS_logtostderr = true;
	} else {
		FLAGS_logtostderr = false;
	}

	/**
	 * ��־�Ƿ�ͬʱ������ļ��ͱ�׼����
	 * 
	 */
	if (mapGlogConf["alsologtostderr"] == "true") {
		FLAGS_alsologtostderr = true;
	} else {
		FLAGS_alsologtostderr = false;
	}

	/**
	 * ÿ����־�Ƿ�Ҫ���ǰ׺,��ʱ��,�����ļ����кŵ�
	 * 
	 */
	if (mapGlogConf["log_prefix"] == "true") {
		FLAGS_log_prefix = true;
	} else {
		FLAGS_log_prefix = false;
	}

	/**
	 * ������־�����stderr�ļ���.�����fatal,��Fatal��־д�뵽��־�ļ���
	 * ͬʱ,Ҳ�������stderr;�����error,�򼶱����error����־д����־�ļ���ͬʱ
	 * Ҳ�������stderr
	 */
	if (mapGlogConf["stderrthreshold"] == "faltal") {
		FLAGS_stderrthreshold = 3;
	} else if (mapGlogConf["stderrthreshold"] == "error") {
		FLAGS_stderrthreshold = 2;
	} else if (mapGlogConf["stderrthreshold"] == "warning") {
		FLAGS_stderrthreshold = 1;
	} else if (mapGlogConf["stderrthreshold"] == "info") {
		FLAGS_stderrthreshold = 0;
	}

	/**
	 * ������־����ļ���,���ڸü������־�����
	 * 
	 */
	if (mapGlogConf["minloglevel"] == "faltal") {
		FLAGS_minloglevel = 3;
	} else if (mapGlogConf["minloglevel"] == "error") {
		FLAGS_minloglevel = 2;
	} else if (mapGlogConf["minloglevel"] == "warning") {
		FLAGS_minloglevel = 1;
	} else if (mapGlogConf["minloglevel"] == "info") {
		FLAGS_minloglevel = 0;
	}

	/**
	 * ������־�����·��
	 * 
	 */
	if (mapGlogConf["log_dir"] != "") {
		FLAGS_log_dir = mapGlogConf["log_dir"];
	}

	/**
	 * ������־�ļ��Ĵ�С�ķ�ֵ
	 * 
	 */
	if (mapGlogConf["max_log_size"] != "") {
		FLAGS_max_log_size = atoi(mapGlogConf["max_log_size"].c_str());
	}

	google::InitGoogleLogging(progName);
}
