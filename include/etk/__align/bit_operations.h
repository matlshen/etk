#ifndef _ETK___ALIGN_BIT_OPERATIONS_H_
#define _ETK___ALIGN_BIT_OPERATIONS_H_

#define BIT(x) (1 << x)
#define SET_BIT(x, n) (x |= BIT(n))
#define CLEAR_BIT(x, n) (x &= ~BIT(n))
#define TOGGLE_BIT(x, n) (x ^= BIT(n))
#define CHECK_BIT(x, n) (x & BIT(n))

#endif // _ETK___ALIGN_BIT_OPERATIONS_H_