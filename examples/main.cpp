#include <iostream>

/* 
Device driver I/O operations
-I/O initialization: external to driver
-I/O read/write: override virtual function
-Interrupt handling: call function callback from IRQ
*/


class fake_mutex {
public:
    void lock() {
        std::cout << "fake_mutex::lock()" << std::endl;
    }
    void unlock() {}
};

template <class _Mutex>
class unique_lock {
public:


    _Mutex m;
    void do_lock() {
        m.lock();
    }

    void do_unlock() {
        m.unlock();
    }
};

int main() {
    unique_lock<fake_mutex> lock;
    lock.do_lock();
    lock.do_unlock();


    return 0;
}