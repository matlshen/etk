#ifndef _ETK___EVENT_FLAGS_SUPPORT_THREADX_H_
#define _ETK___EVENT_FLAGS_SUPPORT_THREADX_H_

#include "etk/__config.h"
#include "tx_api.h"

_ETK_BEGIN_NAMESPACE_ETK

typedef TX_EVENT_FLAGS_GROUP __etk_event_flags_t;
#define _ETK_EVENT_FLAGS_INITIALIZER 0

inline _ETK_INTERNAL_API int event_flags_create(__etk_event_flags_t* flags) {
    return tx_event_flags_create(flags, "");
}

inline _ETK_INTERNAL_API int
event_flags_set(__etk_event_flags_t* flags, uint32_t set) {
    return tx_event_flags_set(flags, set, TX_OR);
}

inline _ETK_INTERNAL_API int
event_flags_clear(__etk_event_flags_t* flags, uint32_t clear) {
    return tx_event_flags_set(flags, ~clear, TX_AND);
}

inline _ETK_INTERNAL_API int event_flags_get(
    __etk_event_flags_t* flags, uint32_t* set, event_flags::mode mode) {
    ULONG flags_set;
    ULONG mode_tx = (mode == event_flags::mode::wait_any) ? TX_OR : TX_AND;
    tx_event_flags_get(flags, set, mode_tx, &flags_set, TX_WAIT_FOREVER);
    return flags_get;
}

inline _ETK_INTERNAL_API int event_flags_destroy(__etk_event_flags_t* flags) {
    return tx_event_flags_delete(flags);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___EVENT_FLAGS_SUPPORT_THREADX_H_