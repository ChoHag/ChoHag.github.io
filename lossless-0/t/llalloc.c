/*224:*/
#line 4356 "lossless.w"

#define LL_ALLOCATE fallible_reallocarray
/*4:*/
#line 87 "lossless.w"

#include <ctype.h> 
#include <limits.h> 
#include <setjmp.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
#include <sys/types.h> 
#ifndef LL_ALLOCATE
#define LL_ALLOCATE reallocarray
#endif

/*:4*/
#line 4358 "lossless.w"

void*fallible_reallocarray(void*,size_t,size_t);
#define LL_TEST
#include "../lossless.c" 

void*
fallible_reallocarray(void*ptr,
size_t nmemb,
size_t size)
{
return Allocate_Success--?reallocarray(ptr,nmemb,size):NULL;
}

/*:224*/
