#ifndef _ETK_EVENT_FLAGS_H_
#define _ETK_EVENT_FLAGS_H_

/*
########## Event flags synopsis ##########

namespace etk {

class event_flags {
public:
    enum mode {
        wait_any,
        wait_all,
    };

    event_flags();
    ~event_flags();

    void set(uint32_t flags);

    void clear(uint32_t flags);

    uint32_t wait(uint32_t flags, mode wait_mode);
};

}   // etk
*/

#include "etk/__event_flags/event_flags.h"

#endif // _ETK_EVENT_FLAGS_H_