semaphore::semaphore(unsigned int initial) noexcept
    : __count_(initial), __max_(UINT_MAX) {}

semaphore::semaphore(unsigned int max,
                                       unsigned int initial) noexcept
    : __count_(initial), __max_(max) {
    ASSERT(__count_ <= __max_);
}

void semaphore::wait() {
    unique_lock lock(mutex_);
    cond_var_.wait(lock, [this]() { return __count_ > 0; });
    __count_--;
}

bool semaphore::try_wait() {
    unique_lock lock(mutex_);
    if (__count_ == 0) {
        return false;
    }
    __count_--;
    return true;
}

void semaphore::signal() {
    unique_lock lock(mutex_);
    if (__count_ == __max_) {
        return;
    }
    __count_++;
    cond_var_.notify_one();
}

unsigned int semaphore::count() {
    unique_lock lock(mutex_);
    return __count_;
}