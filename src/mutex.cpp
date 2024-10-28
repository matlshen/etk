#include "etk/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

mutex::mutex() noexcept { ASSERT_0(__etk_mutex_init(&__m_)); }

mutex::~mutex() noexcept { ASSERT_0(__etk_mutex_destroy(&__m_)); }

void mutex::lock() { ASSERT_0(__etk_mutex_lock(&__m_)); }

bool mutex::try_lock() { return __etk_mutex_trylock(&__m_); }

void mutex::unlock() { ASSERT_0(__etk_mutex_unlock(&__m_)); }

mutex::native_handle_type mutex::native_handle() noexcept { return &__m_; }

_ETK_END_NAMESPACE_ETK