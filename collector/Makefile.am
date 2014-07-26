AUTOMAKE_OPTIONS=foreign

SUBDIRS=common

bin_PROGRAMS=fc

fc_SOURCES=collector_main.cpp

INCLUDES=-I$(top_srcdir)/src/ \
	-I$(top_srcdir)/src/parser/ \
	-I$(top_srcdir)/src/ip_locate/ \
	-I$(top_srcdir)/../common/config \
	-I$(top_srcdir)/../common/util \
	-I$(top_srcdir)/../common/include \
	-I$(top_srcdir)/../common/glog \
	-I$(top_srcdir)/../common/xmlconf \
	-I$(top_srcdir)/../common/socket \
	-I$(top_srcdir)/../common/public \
	-I$(top_srcdir)/../common/mysql/

#indatabase_LDADD=$(top_srcdir)/../common/mysql/libmysqlconnect.a 
