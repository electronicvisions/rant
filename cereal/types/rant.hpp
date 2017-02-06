#ifndef CEREAL_TYPES_RANT_HPP_
#define CEREAL_TYPES_RANT_HPP_

#include "rant/rant.h"

namespace cereal
{
  //! Serializing (save) for rant::integral_range
  template <class Archive, class T, T Max, T Min, class Check> inline
  void CEREAL_SAVE_FUNCTION_NAME( Archive & ar, ::rant::integral_range<T, Max, Min, Check> const & s )
  {
    T t = static_cast<T>(s);
    ar( CEREAL_NVP_("value", t) );
  }

  //! Serializing (load) for std::integral_range
  template <class Archive, class T, T Max, T Min, class Check> inline
  void CEREAL_LOAD_FUNCTION_NAME( Archive & ar, ::rant::integral_range<T, Max, Min, Check> & s )
  {
    T t;
    ar( CEREAL_NVP_("value", t) );
    s = rant::integral_range<T, Max, Min, Check>(t);
  }

  //! Serializing (save) for rant::floating_point_range
  template <class Archive, class T, class Max, class Min, class Check> inline
  void CEREAL_SAVE_FUNCTION_NAME( Archive & ar, rant::floating_point_range<T, Max, Min, Check> const & s )
  {
    T t = static_cast<T>(s);
    ar( CEREAL_NVP_("value", t) );
  }

  //! Serializing (load) for std::floating_point_range
  template <class Archive, class T, class Max, class Min, class Check> inline
  void CEREAL_LOAD_FUNCTION_NAME( Archive & ar, rant::floating_point_range<T, Max, Min, Check> & s )
  {
    T t;
    ar( CEREAL_NVP_("value", t) );
    s = rant::floating_point_range<T, Max, Min, Check>(t);
  }
} // namespace cereal

#endif // CEREAL_TYPES_RANT_HPP_
