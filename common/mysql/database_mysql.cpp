#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errmsg.h>
#include <mysqld_error.h>

#include "database_mysql.h"


bool MysqlConnector::NextRow(MYSQL_ROW *row, unsigned long **pLength)
{

	if (m_mysqlRes != NULL) {
		if ((*row = mysql_fetch_row(m_mysqlRes)) != NULL) {
			*pLength = mysql_fetch_lengths(m_mysqlRes);
			return true;
		}
	}
	return false;
}

MysqlConnector::MysqlConnector()
	:m_sock(NULL),
	 m_mysqlRes(NULL)
{
	m_port = 0;
}

MysqlConnector::~MysqlConnector()
{
	DisConnect();
}

void MysqlConnector::Connect() throw(logic_error)
{
	Connect(m_sHostName.c_str(), m_sUserName.c_str(),
		m_sPassword.c_str(), m_sDbName.c_str(), m_port);
}

void MysqlConnector::Connect(const string & rcsHost, const string & rcsUser,
			     const string & rcsPassword, const string & rcsDbName,
			     int port) throw(logic_error)
{
	string sError;

	if ((m_sock = mysql_init(NULL)) == NULL) {
		Error(sError);
		throw logic_error(sError);
	}

	if (mysql_real_connect(m_sock, rcsHost.c_str(),
			       rcsUser.c_str(), rcsPassword.c_str(),
			       rcsDbName.c_str(),
			       port, NULL, 0) == 0) {
		if (mysql_errno(m_sock)) {
			fprintf(stderr, "connect to mysql failed, errno:%d\n", mysql_errno(m_sock));
		}

		Error(sError);
		throw logic_error(sError);
	}

	m_sHostName = rcsHost;
	m_sUserName = rcsUser;
	m_sPassword = rcsPassword;
	m_sDbName = rcsDbName;
	m_port = port;
}

int MysqlConnector::Errno()
{
	return mysql_errno(m_sock);
}

void MysqlConnector::DisConnect()
{
	if (m_mysqlRes) {
		SelectQueryEnd();
	}

	if (m_sock != NULL) {
		mysql_close(m_sock);
		m_sock = NULL;
	}
}

void MysqlConnector::Excute(const string & rcsSql, bool bReConnect) throw(logic_error)
{
	if (rcsSql.empty()) {
		throw logic_error("sql string is empty!");
	}

	if (!(mysql_query(m_sock, rcsSql.c_str()))) {
		// excute ok
	} else {
		string sError;
		int ret = mysql_errno(m_sock);
		if ((ret == CR_SERVER_LOST) || (ret == CR_SERVER_GONE_ERROR)) {
			if (bReConnect) { // 如果设置了重连,连接成功后再次执行
				DisConnect();
				Connect();
				return Excute(rcsSql);
			}
		}

		Error(sError);

		throw logic_error(sError);
	}
}

void MysqlConnector::SelectQuery(const string & rcsSelectSql, int & nFields) throw(logic_error)
{
	string sError;
	if (rcsSelectSql.empty()) {
		throw logic_error("sql string is empty!");
	}

	Excute(rcsSelectSql);

	if (!(m_mysqlRes = mysql_store_result(m_sock))) {
		Error(sError);
		throw logic_error(sError);
	} else {
		nFields = mysql_num_fields(m_mysqlRes);
	}
}

void MysqlConnector::SelectQueryEnd()
{
	assert(m_mysqlRes);

	mysql_free_result(m_mysqlRes);
	m_mysqlRes = NULL;
}

void MysqlConnector::Error(string & rsErrorString)
{
	char buf[32];
	string sErr;

	snprintf(buf, sizeof(buf), "errno(%d):", Errno());
	sErr = mysql_error(m_sock);

	rsErrorString = string(buf) + sErr;
}
