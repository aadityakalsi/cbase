/*
Permission is hereby granted, free of charge, to any person or organization 
obtaining a copy of the software and accompanying documentation covered by this 
license (the "Software") to use, reproduce, display, distribute, execute, and 
transmit the Software, and to prepare derivative works of the Software, and to 
permit third-parties to whom the Software is furnished to do so, all subject to the 
following:

The copyright notices in the Software and this entire statement, including the 
above license grant, this restriction and the following disclaimer, must be 
included in all copies of the Software, in whole or in part, and all derivative 
works of the Software, unless such copies or derivative works are solely in the 
form of machine-executable object code generated by a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT 
HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER 
LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * \file memory.h
 * \date 2015
 */

#ifndef CBASE_MEMORY_H
#define CBASE_MEMORY_H

/* PKG includes
 */
#include <cbase/buildsym.h>
#include <cbase/ints.h>

/* Alignment in bytes */
#define CBASE_MEM_ALIGN 8

#if !defined(NDEBUG)

CBASE_API
/**
 *
 */
void* cbase_allocate_debug(cb_size sz, const cb_char* file, cb_int32 line);

CBASE_API
/**
 *
 */
void* cbase_reallocate_debug(void* ptr, cb_size sz, const cb_char* file, cb_int32 line);

CBASE_API
/**
 *
 */
void cbase_deallocate_debug(void* mem);

CBASE_API
/**
 *
 */
void* cbase_callocate_debug(cb_size sz, const cb_char* file, cb_int32 line);

/**
 *
 */
#  define cbase_alloc(x) cbase_allocate_debug((x), __FILE__, __LINE__)

/**
 *
 */
#  define cbase_realloc(x, sz) cbase_reallocate_debug((x), (sz), __FILE__, __LINE__)

/**
 *
 */
#  define cbase_calloc(x) cbase_callocate_debug((x), __FILE__, __LINE__)

/**
 *
 */
#  define cbase_free(x)  cbase_deallocate_debug((x))

#else/* Release */

CBASE_API
/**
 *
 */
void* cbase_allocate(cb_size sz);

CBASE_API
/**
 *
 */
void* cbase_reallocate(void* mem, cb_size sz);

CBASE_API
/**
 *
 */
void cbase_deallocate(void* mem);

CBASE_API
/**
 *
 */
void* cbase_callocate(cb_size sz);

/**
 *
 */
#  define cbase_alloc(x) cbase_allocate((x))

/**
 *
 */
#  define cbase_realloc(x, sz) cbase_reallocate((x), (sz))

/**
 *
 */
#  define cbase_calloc(x) cbase_callocate((x))

/**
 *
 */
#  define cbase_free(x)  cbase_deallocate((x))

#endif/*!defined(NDEBUG)*/

#endif//CBASE_MEMORY_H
