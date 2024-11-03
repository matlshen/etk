#ifndef _ETK___SEMAPHORE_BINARY_SEMAPHORE_H_
#define _ETK___SEMAPHORE_BINARY_SEMAPHORE_H_

#include "etk/__semaphore/counting_semaphore.h"

_ETK_BEGIN_NAMESPACE_ETK

using binary_semaphore = counting_semaphore<1>;

_ETK_END_NAMESPACE_ETK

#endif // _ETK___SEMAPHORE_BINARY_SEMAPHORE_H_