#include "etk/functor.h"

int main() {
    etk::functor f([]() { return 10; });
    return f();
}