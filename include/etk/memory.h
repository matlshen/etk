#ifndef _ETK_MEMORY_H_
#define _ETK_MEMORY_H_

/**
########## Memory synopsis ##########

namespace etk {

class memory {
  public:
    static void* malloc(size_t size);
    static void free(void* ptr);
};

}   // etk
*/

#include "etk/__config.h"
#include "etk/__memory/memory.h"

#endif // _ETK_MEMORY_H_