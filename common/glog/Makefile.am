noinst_LIBRARIES=libgloginit.a

libgloginit_a_SOURCES=glog_init.cpp


INCLUDES=-I$(top_srcdir)/arith \
	-I$(top_srcdir)/util \
	-I$(top_srcdir)/xmlconf \
	-I$(top_srcdir)/

libgloginit_a_LIBADD=/usr/local/lib/libglog.a \
	/usr/local/lib/libgflags.a \
	/usr/local/lib/libexpat.a

AM_CXXFLAGS=

#EXTRA_DIST = Readme.txt
