noinst_LIBRARIES=libxmlconf.a


#bin_PROGRAMS=xml_tester

#xml_tester_SOURCES=xmlconf_test.cpp CodingConv.cpp Conf.cpp Error.cpp ExpatNode.cpp \
#	ExpatParser.cpp Node.cpp StdAfx.cpp XmlTools.cpp

libxmlconf_a_SOURCES=CodingConv.cpp Conf.cpp Error.cpp ExpatNode.cpp \
	ExpatParser.cpp Node.cpp StdAfx.cpp XmlTools.cpp

INCLUDES= -I/usr/local/include/ \
	-I$(top_srcdir)/config/ \
	-I$(top_srcdir)/ 

libxmlconf_a_LIBADD=/usr/local/lib/libexpat.a \
	/usr/local/lib/libiconv.a
#xml_tester_LDADD= /usr/local/lib/libexpat.a

AM_CFLAGS=

#EXTRA_DIST = Readme.txt
