AUTOMAKE_OPTIONS=foreign

bin_PROGRAMS=print_hours time_math local_utc_conversion

print_hours_SOURCES=print_hours.cpp
local_utc_conversion_SOURCES=local_utc_conversion.cpp
time_math_SOURCES=time_math.cpp

INCLUDES=-I/usr/local/include \
	-I$(top_srcdir)/date_time/

print_hours_LDADD=-L/usr/local/lib -lboost_date_time
time_math_LDADD=-L/usr/local/lib -lboost_date_time
local_utc_conversion_LDADD=-L/usr/local/lib -lboost_date_time
