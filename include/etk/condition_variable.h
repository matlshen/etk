#ifndef _ETK_CONDITION_VARIABLE_H_
#define _ETK_CONDITION_VARIABLE_H_

/*
########## Condition variable synopsis ##########

namespace etk {

class condition_variable {
public:
    condition_variable();
    condition_variable(const condition_variable&) = delete;
    ~condition_variable();

    void notify_one() noexcept;
    void notify_all() noexcept;

    void wait(unique_lock<mutex>& lock) noexcept;
    template <class Predicate>
    void wait(unique_lock<mutex>& lock, Predicate pred);

    native_handle_type native_handle();
};

}   // etk
*/

#include "etk/__condition_variable/condition_variable.h"
#include "etk/__config.h"

#endif // _ETK_CONDITION_VARIABLE_H_