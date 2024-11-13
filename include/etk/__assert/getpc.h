#ifndef _GET_PC_H_
#define _GET_PC_H_

/**
 * Currently supported platforms:
 * - aarch64-apple-darwin
 * 
 */


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__aarch64__) && defined(__APPLE__)
	#define GET_PC() __builtin_return_address(0)
#endif

#ifdef __cplusplus
}
#endif

#endif // _GET_PC_H_