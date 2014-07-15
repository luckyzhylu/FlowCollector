AUTOMAKE_OPTIONS=foreign

# SUBDIRS=parser ip_locate

bin_PROGRAMS=fc

indatabase_SOURCES=collector_main.cpp

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

indatabase_LDADD=$(top_srcdir)/../common/mysql/libmysqlconnect.a \
	$(top_srcdir)/../common/glog/libgloginit.a \
	$(top_srcdir)/../common/xmlconf/libxmlconf.a \
	$(top_srcdir)/../common/util/libutil.a \
	$(top_srcdir)/../common/socket/libsocket.a \
	$(top_srcdir)/src/parser/libeventparser.a \
	$(top_srcdir)/src/ip_locate/libiplocate.a \
	$(top_srcdir)/../common/public/libpublic.a \
	/usr/local/lib/libglog.a \
	/usr/local/lib/libgflags.a \
	/usr/local/lib/libexpat.a \
	/usr/local/lib/libiconv.a \
	-lpthread \
	-L/usr/lib64/mysql -lmysqlclient
#/infobright-4.0.7-x86_64/lib/mysql/libmysqlibclient.a
