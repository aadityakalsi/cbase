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
 * \file utf8.h
 * \date 2015
 */

#ifndef CBASE_UTF8_H
#define CBASE_UTF8_H

#include <cbase/buildsym.h>
#include <cbase/ints.h>

CBASE_API
/**
 * Return whether successful and assign string length and number of code points
 * in the string.
 */
cb_bool cb_utf8_count_codepts(const cb_char* str, cb_size* slen, cb_size* ncp);

CBASE_API
/**
 * Return whether successful and assign string length and number of code points
 * in the string.
 */
cb_bool cb_utf16_count_codepts(const cb_char16* str, cb_size* slen, cb_size* ncp);

CBASE_API
/**
 * Return whether successful and assign string length and number of code points
 * in the string.
 */
cb_bool cb_utf32_count_codepts(const cb_char32* str, cb_size* slen);

CBASE_API
/**
 * Return num code points read. The \p cp must always point to at least
 * two \c cb_char16 as surrogate pairs may be encountered.
 */
cb_uint8 cb_utf8_utf16_next(const cb_char** str, cb_char16* cp);

CBASE_API
/**
 * Return num code points read.The \p cp must always point to at least
 * one \c cb_char32.
 */
cb_uint8 cb_utf8_utf32_next(const cb_char** str, cb_char32* cp);

CBASE_API
/**
 * Return num code points read. The \p cp must always point to at least
 * six \c cb_char as multi-byte code points may be encountered.
 */
cb_uint8 cb_utf16_utf8_next(const cb_char16** str, cb_char* cp);

CBASE_API
/**
 * Return num code points read.The \p cp must always point to at least
 * six \c cb_char as multi-byte code points may be encountered.
 */
cb_uint8 cb_utf32_utf8_next(const cb_char32** str, cb_char* cp);

/**
 *
 */
struct cb_utf8_utf16_cvt_tag;
typedef struct cb_utf8_utf16_cvt_tag cb_utf8_utf16_cvt;

CBASE_API
/**
 *
 */
cb_utf8_utf16_cvt* cb_make_utf8_utf16_cvt();

CBASE_API
/**
 *
 */
void cb_destroy_utf8_utf16_cvt(cb_utf8_utf16_cvt* cvt);

CBASE_API
/**
 *
 */
void cb_utf8_utf16_buffer(
        cb_utf8_utf16_cvt* cvt,
        const cb_char** src,
        cb_size* srclen,
        cb_char16** dst,
        cb_size* dstlen,
        cb_bool flush);

/**
 *
 */
struct cb_utf8_utf32_cvt_tag;
typedef struct cb_utf8_utf32_cvt_tag cb_utf8_utf32_cvt;

CBASE_API
/**
 *
 */
cb_utf8_utf32_cvt* cb_make_utf8_utf32_cvt();

CBASE_API
/**
 *
 */
void cb_destroy_utf8_utf32_cvt(cb_utf8_utf32_cvt* cvt);

CBASE_API
/**
 *
 */
void cb_utf8_utf32_buffer(
        cb_utf8_utf32_cvt* cvt,
        const cb_char** src,
        cb_size* srclen,
        cb_char32** dst,
        cb_size* dstlen,
        cb_bool flush);

/**
 *
 */
struct cb_utf16_utf8_cvt_tag;
typedef struct cb_utf16_utf8_cvt_tag cb_utf16_utf8_cvt;

CBASE_API
/**
 *
 */
cb_utf16_utf8_cvt* cb_make_utf16_utf8_cvt();

CBASE_API
/**
 *
 */
void cb_destroy_utf16_utf8_cvt(cb_utf16_utf8_cvt* cvt);

CBASE_API
/**
 *
 */
void cb_utf16_utf8_buffer(
        cb_utf16_utf8_cvt* cvt,
        const cb_char16** src,
        cb_size* srclen,
        cb_char** dst,
        cb_size* dstlen,
        cb_bool flush);

/**
 *
 */
struct cb_utf32_utf8_cvt_tag;
typedef struct cb_utf32_utf8_cvt_tag cb_utf32_utf8_cvt;

CBASE_API
/**
 *
 */
cb_utf32_utf8_cvt* cb_make_utf32_utf8_cvt();

CBASE_API
/**
 *
 */
void cb_destroy_utf32_utf8_cvt(cb_utf32_utf8_cvt* cvt);

CBASE_API
/**
 *
 */
void cb_utf32_utf8_buffer(
        cb_utf32_utf8_cvt* cvt,
        const cb_char32** src,
        cb_size* srclen,
        cb_char** dst,
        cb_size* dstlen,
        cb_bool flush);

#endif//CBASE_UTF8_H
