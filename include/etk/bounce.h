#ifndef _ETK_BOUNCE_H_
#define _ETK_BOUNCE_H_

template <class T, class Method, Method m, class... Params>
static auto bounce(void *priv, Params... params)
    -> decltype(((*reinterpret_cast<T *>(priv)).*m)(params...)) {
    return ((*reinterpret_cast<T *>(priv)).*m)(params...);
}

/**
 * Convenience macro to simplify bounce statement usage
 */
#define BOUNCE(c, m) bounce<c, decltype(&c::m), &c::m>

#endif // _ETK_BOUNCE_H_