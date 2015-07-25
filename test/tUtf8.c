
/**
 * \file tUtf8.c
 * \date 2015
 */

#include "unittest.h"

/* TEST includes
 */
#include <cbase/utf8.h>

TEST_FUNC( u32len )
{
    {// non zero len
        cb_char32 text[] = { 65, 66, 67, 32, 68, 69, 70, 0 };
        cb_size len = 0;
        TEST_TRUE( cb_utf32_count_codepts(text, &len) );
        TEST_TRUE( len == 7 );
    }
    {// zero len
        cb_char32 text[] = { 0 };
        cb_size len = 0;
        TEST_TRUE( cb_utf32_count_codepts(text, &len) );
        TEST_TRUE( len == 0 );
    }
}

TEST_FUNC( u16len )
{
    {// non zero len
        cb_char16 text[] = { 65, 66, 67, 32, 68, 69, 70, 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 7 );
        TEST_TRUE( ncp == 7 );
    }
    {// consecutive leading surr
        cb_char16 text[] = { 65, 66, 0xD801, 0xD801, 68, 69, 70, 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_FALSE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// consecutive trailing surr
        cb_char16 text[] = { 65, 66, 0xDC01, 0xDC01, 68, 69, 70, 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_FALSE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// trailing before leading
        cb_char16 text[] = { 65, 66, 0xDC01, 0xD801, 68, 69, 70, 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_FALSE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// valid sequence with surr
        cb_char16 text[] = { 65, 66, 0xD801, 0xDC01, 68, 69, 70, 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 7 );
        TEST_TRUE( ncp == 6 );
    }
    {// zero len
        cb_char16 text[] = { 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf16_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
}


void SetupTests(void)
{
    REG_TEST( u32len );
    REG_TEST( u16len );
}

