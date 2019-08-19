// Copyright 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the LGPLv3 or newer.

#pragma once

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

#include "rant/rant.h"


namespace boost::serialization {

/* serialization suppport for integral_range types */

template <typename Archiver, typename T, T Max, T Min, typename Check>
inline void save(Archiver& ar, ::rant::integral_range<T, Max, Min, Check> const& s, unsigned int const)
{
	auto t = static_cast<T>(s);
	ar << make_nvp("value", t);
}

template <typename Archiver, typename T, T Max, T Min, typename Check>
inline void load(Archiver& ar, ::rant::integral_range<T, Max, Min, Check>& s, unsigned int const)
{
	T t;
	ar >> make_nvp("value", t);
	s = ::rant::integral_range<T, Max, Min, Check>(t);
}

/* boost::serialization hacking; template/overload resolution in gcc 9 seems to pick
 * shared_ptr_helper.hpp's version of load => let's explicitly call ours below.
 *
 * note: the version without non-type template paramters seems fine; maybe related to
 *       https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84075
 *
**/
template<typename Archive, typename T, T Max, T Min, typename Check>
inline void split_free(
		Archive & ar,
		::rant::integral_range<T, Max, Min, Check>& t,
		const unsigned int file_version
		)
{
	if constexpr (Archive::is_saving::value) {
		save(ar, t, file_version);
	} else {
		// explicitly select version
		load<Archive, T, Max, Min, Check>(ar, t, file_version);
	}
}

template<typename Archiver, typename T, T Max, T Min, typename Check>
void serialize(Archiver& ar,
	::rant::integral_range<T, Max, Min, Check>& s,
	unsigned int const version)
{
	split_free<Archiver, T, Max, Min, Check>(ar, s, version);
}


/* serialization suppport for floating_point_range types */

template <class Archiver, class T, typename Max, typename Min, class Check> inline
void load(Archiver& ar,
	::rant::floating_point_range<T, Max, Min, Check>& s,
	unsigned int const)
{
	T t;
	ar >> make_nvp("value", t);
	s = ::rant::floating_point_range<T, Max, Min, Check>(t);
}

template <class Archiver, class T, typename Max, typename Min, class Check> inline
void save(Archiver& ar,
	::rant::floating_point_range<T, Max, Min, Check> const& s,
	unsigned int const)
{
	auto t = static_cast<T>(s);
	ar << make_nvp("value", t);
}

template<typename Archiver, typename T,
	typename Max,
	typename Min,
	typename Check>
void serialize(Archiver& ar,
	::rant::floating_point_range<T, Max, Min, Check>& s,
	unsigned int const version)
{
	split_free(ar, s, version);
}

} // boost::serialization
