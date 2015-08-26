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
	 * 日志是否要输出到标准出错
	 * 
	 */

	if (mapGlogConf["logtostderr"] == "true") {
		FLAGS_logtostderr = true;
	} else {
		FLAGS_logtostderr = false;
	}

	/**
	 * 日志是否同时输出到文件和标准出错
	 * 
	 */
	if (mapGlogConf["alsologtostderr"] == "true") {
		FLAGS_alsologtostderr = true;
	} else {
		FLAGS_alsologtostderr = false;
	}

	/**
	 * 每行日志是否要添加前缀,如时间,代码文件的行号等
	 * 
	 */
	if (mapGlogConf["log_prefix"] == "true") {
		FLAGS_log_prefix = true;
	} else {
		FLAGS_log_prefix = false;
	}

	/**
	 * 设置日志输出到stderr的级别.如果是fatal,则Fatal日志写入到日志文件的
	 * 同时,也会输出到stderr;如果是error,则级别高于error的日志写入日志文件的同时
	 * 也会输出到stderr
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
	 * 设置日志输出的级别,低于该级别的日志不输出
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
	 * 设置日志输出的路径
	 * 
	 */
	if (mapGlogConf["log_dir"] != "") {
		FLAGS_log_dir = mapGlogConf["log_dir"];
	}

	/**
	 * 设置日志文件的大小的阀值
	 * 
	 */
	if (mapGlogConf["max_log_size"] != "") {
		FLAGS_max_log_size = atoi(mapGlogConf["max_log_size"].c_str());
	}

	google::InitGoogleLogging(progName);
}
