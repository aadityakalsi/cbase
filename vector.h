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
 * \file vector.h
 * \date 2015
 */

#ifndef CBASE_VECTOR_H
#define CBASE_VECTOR_H

#include <cbase/buildsym.h>
#include <cbase/ints.h>
#include <cbase/memory.h>

CBASE_INLINE
/**
 *
 */
cb_size cbase_next_pow_2(cb_size v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#if CBASE_64_BIT
    v |= v >> 32;
#endif/*CBASE_64_BIT*/
    v++;
    return v ? v : 1;
}

CBASE_INLINE
/**
 *
 */
cb_size cbase_vector_size(const void* v)
{
    return (cb_size)*((const cb_uint64*)(v) - 2);
}

CBASE_INLINE
/**
 *
 */
cb_size cbase_vector_cap(const void* v)
{
    return (cb_size)*((const cb_uint64*)(v) - 1);
}

CBASE_INLINE
/**
 *
 */
void cbase_vector_destroy(void* v)
{
    cbase_free((cb_uint64*)v - 2);
}

/**
 *
 */
#define cbase_vector(type) \
\
CBASE_INLINE \
type* cbase_vector_create_##type(cb_size sz) \
{ \
    cb_size cap = cbase_next_pow_2(sz); \
    if (cap < sz) { return NULL; } \
    /* always use cb_uint64 to maintain alignment */ \
    cb_uint64* p = cbase_alloc((cap * sizeof(type)) + (2 * sizeof(cb_uint64))); \
    if (!p) { return NULL; } \
    *(p++) = sz; \
    *(p++) = cap; \
    return (type*)p; \
} \
\
CBASE_INLINE \
cb_bool cbase_vector_resize_##type(type** pv, cb_size newsz) \
{ \
    type* v = *pv; \
    cb_size cp = cbase_vector_cap(v); \
    if (newsz <= cp) { \
        *((cb_uint64*)(v) - 2) = newsz; \
    } else { \
        cb_size newcp = cbase_next_pow_2(newsz); \
        if (newcp < newsz) { return CB_FALSE; } \
        cb_uint64* p = ((cb_uint64*)(v) - 2); \
        /* always use cb_uint64 to maintain alignment */ \
        p = cbase_realloc(p, newcp * sizeof(type) + 2 * sizeof(cb_uint64)); \
        if (!p) { return CB_FALSE; } \
        *(p++) = newsz; \
        *(p++) = newcp; \
        v = (void*)p; \
    } \
    *pv = v; \
    return CB_TRUE; \
} \
\
CBASE_INLINE \
cb_bool cbase_vector_push_##type(type** pv, type val) \
{ \
    type* v = *pv; \
    cb_size sz = cbase_vector_size(v); \
    cb_size cp = cbase_vector_cap(v); \
    if (sz == cp) { \
        if (!cbase_vector_resize_##type(&v, sz + 1)) { \
            return CB_FALSE; \
        } \
    } else { \
        ++(*((cb_uint64*)(v) - 2)); \
    } \
    v[sz] = val; \
    *pv = v; \
    return CB_TRUE; \
}


#endif//CBASE_VECTOR_H
