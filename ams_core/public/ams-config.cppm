module;

#ifndef AMS_EXCEPTIONS
#define AMS_EXCEPTIONS_ENABLED true
#else
#define AMS_EXCEPTIONS_ENABLED false
#endif

#ifdef AMS_NEGATIVE_INDEXING
#define AMS_NEGATIVE_INDEXING_ENABLED true
#else
#define AMS_NEGATIVE_INDEXING_ENABLED false
#endif

#ifdef AMS_ENABLE_HIGH_PRECISION_INTEGERS
#define AMS_ENABLE_HIGH_PRECISION_INTEGERS_ENABLED true
#else
#define AMS_ENABLE_HIGH_PRECISION_INTEGERS_ENABLED false
#endif

export module ams:config;
#ifndef AMS_MODULES_STD
import <string>;
#else
import std;
#endif


namespace ams {

/**
 * @brief Are exceptions enabled?
 * @details If true, methods can throw exceptions when an error occurs.
 * If false, methods will not throw exceptions, but will instead return a default value or call
 * std::terminate() if a default value cannot be returned.
 */
export inline constexpr bool AMSExceptions = AMS_EXCEPTIONS_ENABLED;

/**
 * @brief Is negative indexing enabled?
 * @details If true, negative indexing is enabled for all ams containers. When enabled, providing a value of -1 to
 * a container's subscript operator will return <code> [container_type].size() + -1 </code>.
 *
 */
export inline constexpr bool AMSNegativeIndexing = AMS_NEGATIVE_INDEXING_ENABLED;

/**
 * @brief Are high precision integers enabled?
 * @details If true, high precision integers are enabled. When enabled, ams::int128_t and
 * ams::uint128_t are available. If false, these types are not available.
 */
export[[deprecated("High precision integers are not yet implemented. This value will always be false.")]]
inline constexpr bool AMSHighPrecisionIntegers = AMS_ENABLE_HIGH_PRECISION_INTEGERS_ENABLED;

}// namespace ams
