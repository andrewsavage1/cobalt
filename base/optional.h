#ifndef BASE_OPTIONAL_H_
#define BASE_OPTIONAL_H_

#include <optional>

namespace base {
template <typename T>
using Optional = std::optional<T>;

using nullopt = std::nullopt_t;
}

#endif  // BASE_OPTIONAL_H_
