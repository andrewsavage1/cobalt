#ifndef BASE_CALLBACK_H_
#define BASE_CALLBACK_H_

#include "base/functional/callback.h"

namespace base {
template <typename R, typename... Args>
using Callback = RepeatingCallback<R(Args...)>;
}

#endif
