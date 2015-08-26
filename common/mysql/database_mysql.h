#ifndef _DATABASE_MYSQL_H_
#define _DATABASE_MYSQL_H_
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <mysql.h>
#include <stdexcept>
#include <string>

using namespace std;

class MysqlConnector
{
public:
	MysqlConnector();
	virtual ~MysqlConnector();

	void Connect() throw(logic_error);
	void Connect(const string& rcsHost, const string& rcsUser,
			  const string& rcsPassword, const string& rcsDbName,
			  int port = 3306) throw(logic_error);

	void DisConnect();

	void Excute(const string& rcsSql, bool bReConnect = true)throw (logic_error);
	void SelectQuery(const string& rcsSelectSql, int& nFields) throw(logic_error);
	bool NextRow(MYSQL_ROW *row, unsigned long **pLength);
	void SelectQueryEnd();
	void SetCharSet(const char *cName) {
		mysql_set_character_set(m_sock, cName);
	}

	int Errno();
	void Error(string& rsErr);

	int Escape(char *dst, char *src, int srcLen) {
		return mysql_real_escape_string(m_sock, dst, src, srcLen);
	}
public:
	void SetMysqlUser(const string& rcsUser) {
		m_sUserName = rcsUser;
	}

	void SetMysqlPassword(const string& rcsPassword) {
		m_sPassword = rcsPassword;
	}

	void SetMysqlDbName(const string& rcsDbName) {
		m_sDbName = rcsDbName;
	}
	void SetMysqlPort(int port) {
		m_port = port;
	}
private:
	MysqlConnector(const MysqlConnector& rc);
	MysqlConnector& operator = (const MysqlConnector& rc);

private:
	MYSQL	*m_sock;
	MYSQL_RES *m_mysqlRes;
	string m_sUserName;
	string m_sPassword;
	string m_sHostName;
	string m_sDbName;
	int m_port;
};

#endif
