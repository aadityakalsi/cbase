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

/**
 *
 */
#define cbase_vector(type) \
\
CBASE_INLINE \
type* cbase_create_vector_##type(cb_size sz) \
{ \
    cb_size cap = cbase_next_pow_2(sz); \
    cb_size* p = cbase_alloc((cap * sizeof(type)) + (2 * sizeof(cb_size))); \
    *(p++) = sz; \
    *(p++) = cap; \
    return (type*)p; \
} \
\
CBASE_INLINE \
cb_size cbase_vector_##type##_size(const type* v) \
{ \
    return *((const cb_size*)(v) - 2); \
} \
\
CBASE_INLINE \
cb_size cbase_vector_##type##_cap(const type* v) \
{ \
    return *((const cb_size*)(v) - 1); \
} \
\
CBASE_INLINE \
type* cbase_vector_##type##_resize(type* v, cb_size newsz) \
{ \
    cb_size cp = cbase_vector_##type##_cap(v); \
    if (newsz <= cp) { \
        *((cb_size*)(v) - 2) = newsz; \
    } else { \
        cb_size newcp = cbase_next_pow_2(newsz); \
        cb_size* p = ((cb_size*)(v) - 2); \
        p = cbase_realloc(p, newcp * sizeof(type) + 2 * sizeof(cb_size)); \
        *((cb_size*)p++) = newsz; \
        *((cb_size*)p++) = newcp; \
        v = (void*)p; \
    } \
    return v; \
} \
\
CBASE_INLINE \
type* cbase_vector_##type##_push(type* v, type val) \
{ \
    cb_size sz = cbase_vector_##type##_size(v); \
    cb_size cp = cbase_vector_##type##_cap(v); \
    if (sz == cp) { \
        v = cbase_vector_##type##_resize(v, sz + 1); \
    } else { \
        ++(*((cb_size*)(v) - 2)); \
    } \
    v[sz] = val; \
    return v; \
} \
\
CBASE_INLINE \
void cbase_destroy_vector_##type(type* v) \
{ \
    cbase_free((cb_size*)v - 2); \
} \

#endif//CBASE_VECTOR_H
