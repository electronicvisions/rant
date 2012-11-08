#include <gtest/gtest.h>

#include <sstream>
#include <typeinfo>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "test/test.h"

constexpr bool disable =
#ifndef RANT_DISABLE
	false;
#else
	true;
#endif // RANT_DISABLE

#define ALIASES \
template<typename T = int, \
	T Max = std::numeric_limits<T>::max(), \
	T Min = std::numeric_limits<T>::min()> \
struct iclip \
{ \
	typedef integral_range<T, Max, Min, \
		clip_on_error<T, \
			std::integral_constant<T, Max>, \
			std::integral_constant<T, Min>> \
	> type; \
}; \
\
template<typename T = double, \
	typename Max = std::ratio< std::numeric_limits<intmax_t>::max()>, \
	typename Min = std::ratio<-std::numeric_limits<intmax_t>::max()>> \
struct fclip \
{ \
	typedef floating_point_range<T, Max, Min, \
		clip_on_error<T, Max, Min>> type; \
};


namespace _debug {
using namespace rant::debug;
ALIASES
typedef typename iclip<int>::type     _int;
typedef typename fclip<double>::type  _d;
} // debug

using namespace rant;
ALIASES

typedef typename iclip<int>::type     _int;
typedef typename fclip<double>::type  _d;

TEST(Clip, Integral)
{
	typedef iclip<int, 64, 0>::type t;
	ASSERT_EQ(t(-1), t(-1));
	ASSERT_EQ(t(0), t(-1));
	ASSERT_EQ(t( 65), t( 64));
	ASSERT_EQ(t(111), t(354));

	typedef _debug::iclip<int, 64, 0>::type to;
	ASSERT_EQ(disable ? to( -1) : to(  0), to( -1));
	ASSERT_EQ(disable ? to( 65) : to( 64), to( 65));
	ASSERT_EQ(disable ? to(111) : to(354), to(111));
}

TEST(Clip, UnsignedIntegral)
{
	typedef iclip<unsigned int, 5, 0>::type _t;
	ASSERT_EQ(_t(5), _t(-1));
	ASSERT_EQ(_t(5), _t(6));

	typedef iclip<unsigned char, 5, 1>::type _u;
	ASSERT_EQ(_u(1), _u(0));
	ASSERT_EQ(_u(5), _u(6));
}

TEST(Clip, FloatingPoint)
{
	typedef fclip<double, std::ratio<10>, std::ratio<0>>::type      t;
	typedef _debug::fclip<double, std::ratio<10>, std::ratio<0>>::type to;

	ASSERT_EQ(t(0), t(-0.0));
	ASSERT_EQ(disable ? to(-0.1) : to(0), to(-0.1));
	ASSERT_EQ(t(10.0), t(10.0));
	ASSERT_EQ(disable ? to(10.1) : to(10.0), to(10.1));
}

TEST(Clip, MinMax)
{
	test_minmax<typename _debug::iclip<int, 4, -1>::type>(4, -1);

	typedef typename _debug::fclip<double,
			std::ratio<4, 1>,
			std::ratio<-1, 1>>::type __d;
	test_minmax<__d>(4, -1);
}

RANT_TEST_COMMON(Clip)
