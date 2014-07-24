//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/)
{
	std::cout << "Hello, world!\n";
}

int main()
{
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(&print);
	std::cout << "go throught ...." << std::endl;
	io.run();

	return 0;
}






