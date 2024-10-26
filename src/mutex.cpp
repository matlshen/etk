#include "etk/mutex.h"
_ETK_BEGIN_NAMESPACE_ETK

Mutex::Mutex() noexcept { ASSERT_0(__etk_mutex_init(&__m_)); }

Mutex::~Mutex() noexcept { ASSERT_0(__etk_mutex_destroy(&__m_)); }

void Mutex::lock() { ASSERT_0(__etk_mutex_lock(&__m_)); }

bool Mutex::tryLock() { return __etk_mutex_trylock(&__m_); }

void Mutex::unlock() { ASSERT_0(__etk_mutex_unlock(&__m_)); }

_ETK_END_NAMESPACE_ETK