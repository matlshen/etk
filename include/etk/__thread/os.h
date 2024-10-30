#ifndef _ETK___THREAD_OS_H_
#define _ETK___THREAD_OS_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"

_ETK_BEGIN_NAMESPACE_ETK

namespace os {

/**
 * Additional functions
 */
void time_start();

unsigned int time_get();

} // namespace this_thread

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_OS_H_