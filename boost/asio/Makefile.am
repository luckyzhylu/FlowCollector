AUTOMAKE_OPTIONS=foreign

bin_PROGRAMS=timer timer2 timer3 timer4 timer5

timer_SOURCES=timer.cpp
timer2_SOURCES=timer2.cpp
timer3_SOURCES=timer3.cpp
timer4_SOURCES=timer4.cpp
timer5_SOURCES=timer5.cpp

INCLUDES=-I/usr/local/include \
	-I$(top_srcdir)/date_time/
	-I$(top_srcdir)/asio/

timer_LDADD=-L/usr/local/lib -lboost_date_time -lboost_system
timer2_LDADD=-L/usr/local/lib -lboost_date_time -lboost_system
timer3_LDADD=-L/usr/local/lib -lboost_date_time -lboost_system
timer4_LDADD=-L/usr/local/lib -lboost_date_time -lboost_system
timer5_LDADD=-L/usr/local/lib -lboost_date_time -lboost_system -lboost_thread
