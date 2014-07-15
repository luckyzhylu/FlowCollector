#ifndef _STRINGCONV_H_
#define _STRINGCONV_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <typename T> T fromString(const string& s)
{
	T t;
	istringstream is(s);
	is >> t;

	return t;
}

template <typename T> string toString(const T& t)
{
	ostringstream ostr;
	ostr << t;
	return ostr.str();
}

#endif /* _STRINGCONV_H_ */
