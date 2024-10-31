semaphore::semaphore(unsigned int initial) noexcept {
    __etk_semaphore_init(&__sem_, initial);
}

semaphore::~semaphore() noexcept { __etk_semaphore_destroy(&__sem_); }

void semaphore::wait() { __etk_semaphore_wait(&__sem_); }

void semaphore::try_wait() { __etk_semaphore_trywait(&__sem_); }

void semaphore::signal() { __etk_semaphore_post(&__sem_); }

unsigned int semaphore::count() {
    int value;
    __etk_semaphore_getvalue(&__sem_, &value);
    return value;
}