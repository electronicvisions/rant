// Copyright 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the LGPLv3 or newer.

#include <sstream>
#include <gtest/gtest.h>

#include "rant/rant.h"

using namespace rant;

typedef integral_range<int>          _int;
typedef integral_range<char>         _char;
typedef integral_range<long long>    _ll;
typedef floating_point_range<double> _d;


#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// not tested, but triggered a bug on gcc 9
#include <boost/serialization/shared_ptr.hpp>

#include "boost/serialization/rant.hpp"

template<typename OArchive, typename IArchive, typename T>
void test_serialization(T const& t)
{
	std::stringstream ss;
	{
		OArchive oar(ss);
		oar << boost::serialization::make_nvp("t", t);
	}
	ss.flush();

	T tmp;
	{
		IArchive iar(ss);
		iar >> boost::serialization::make_nvp("t", tmp);
	}
	ASSERT_EQ(t, tmp);
}

TEST(Serialization, XML)
{
	using namespace boost::archive;

	test_serialization<xml_oarchive, xml_iarchive>( _int(-42));
	test_serialization<xml_oarchive, xml_iarchive>(_char(-42));
	test_serialization<xml_oarchive, xml_iarchive>(  _ll(-42));
	test_serialization<xml_oarchive, xml_iarchive>(   _d(-42));
}

TEST(Serialization, Binary)
{
	using namespace boost::archive;
	test_serialization<binary_oarchive, binary_iarchive>( _int(-42));
	test_serialization<binary_oarchive, binary_iarchive>(_char(-42));
	test_serialization<binary_oarchive, binary_iarchive>(  _ll(-42));
	test_serialization<binary_oarchive, binary_iarchive>(   _d(-42));
}

#ifdef HAVE_CEREAL_CEREAL_HPP

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include "cereal/types/rant.hpp"

template<typename OArchive, typename IArchive, typename T>
void test_serialization_cereal(T const& t)
{
	std::stringstream ss;
	{
		OArchive oar(ss);
		oar << cereal::make_nvp("t", t);
		ss.flush();
	}

	T tmp;
	{
		IArchive iar(ss);
		iar >> cereal::make_nvp("t", tmp);
	}

	ASSERT_EQ(t, tmp);
}

TEST(SerializationCereal, XML)
{
	test_serialization_cereal<cereal::XMLOutputArchive, cereal::XMLInputArchive>( _int(-42));
	test_serialization_cereal<cereal::XMLOutputArchive, cereal::XMLInputArchive>(_char(-42));
	test_serialization_cereal<cereal::XMLOutputArchive, cereal::XMLInputArchive>(  _ll(-42));
	test_serialization_cereal<cereal::XMLOutputArchive, cereal::XMLInputArchive>(   _d(-42));
}

TEST(SerializationCereal, JSON)
{
	test_serialization_cereal<cereal::JSONOutputArchive, cereal::JSONInputArchive>( _int(-42));
	test_serialization_cereal<cereal::JSONOutputArchive, cereal::JSONInputArchive>(_char(-42));
	test_serialization_cereal<cereal::JSONOutputArchive, cereal::JSONInputArchive>(  _ll(-42));
	test_serialization_cereal<cereal::JSONOutputArchive, cereal::JSONInputArchive>(   _d(-42));
}

TEST(SerializationCereal, Binary)
{
	test_serialization_cereal<cereal::BinaryOutputArchive, cereal::BinaryInputArchive>( _int(-42));
	test_serialization_cereal<cereal::BinaryOutputArchive, cereal::BinaryInputArchive>(_char(-42));
	test_serialization_cereal<cereal::BinaryOutputArchive, cereal::BinaryInputArchive>(  _ll(-42));
	test_serialization_cereal<cereal::BinaryOutputArchive, cereal::BinaryInputArchive>(   _d(-42));
}

#endif // HAVE_CEREAL_CEREAL_HPP
