noinst_LIBRARIES=libpublic.a

libpublic_a_SOURCES=lock_file.cpp proto.cpp
#proto.c system_log.c ca_serial_number.c \
#	ca_bypass_info.c match_product_type.c ca_ha_mang.c \
#	interface.c lock_file.c vmalloc.c del_dumpfiles.c \
#	oom_policy.c event_print.c

INCLUDES=-I$(top_srcdir)/arith \
	-I$(top_srcdir)/util \
	-I/usr/include/libxml2 \
	-I$(top_srcdir)/config \
	-I$(top_srcdir)/trace \
	-I$(top_srcdir)/product/restore \
	-I$(top_srcdir)/\
	-I$(top_srcdir)/data_struct

AM_CXXFLAGS=

#EXTRA_DIST = Readme.txt
