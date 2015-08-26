#!/bin/sh
aclocal
touch AUTHORS NEWS README ChangeLog
autoheader
automake --add-missing
autoconf
./configure
