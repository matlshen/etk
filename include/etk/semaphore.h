#ifndef __ETK_SEMAPHORE_H_
#define __ETK_SEMAPHORE_H_

/*
########## Semaphore synopsis ##########

namespace etk {

class counting_semaphore {
public:
    counting_semaphore(unsigned int initial) noexcept;
    counting_semaphore(unsigned int max, unsigned int initial) noexcept;

    void release();
    void acquire();
    bool try_acquire();

    size_t count();
};

using binary_semaphore = counting_semaphore<1>;

} // etk

*/

#include "etk/__semaphore/counting_semaphore.h"
#include "etk/__semaphore/binary_semaphore.h"

#endif // __ETK_SEMAPHORE_H_