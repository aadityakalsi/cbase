
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
        cb_size ncp = 0;
        TEST_TRUE( cb_utf32_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 7 );
        TEST_TRUE( ncp == len );
    }
    {// zero len
        cb_char32 text[] = { 0 };
        cb_size len = 0;
        cb_size ncp = 0;
        TEST_TRUE( cb_utf32_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == len );
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

TEST_FUNC( u8len )
{
    {// zero len
        cb_char text[] = { 0 };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// all ASCII
        cb_char text[] = { 'a', 'b', 'c', 'd', 'e', 'f', '\0' };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 6 );
        TEST_TRUE( ncp == 6 );
    }
    {// all byte sizes (1-4)
        cb_char text[] = {
            0x10,                    /* 1 byte  */
            0xC1, 0x81,              /* 2 bytes */
            0xE1, 0x81, 0x81,        /* 3 bytes */
            0xF1, 0x81, 0x81, 0x81,  /* 4 bytes */
            '\0' };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 10 );
        TEST_TRUE( ncp == 4  );
    }
    {// lead char beyond 0xF5
        cb_char text[] = {
            0xF5, 0x81, 0x81, 0x81,  /* 4 bytes */
            '\0' };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( !cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// lead char continuation
        cb_char text[] = {
            0x81, 0x81, 0x81, 0x81,
            '\0' };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( !cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
    {// trailing char not starting with 0x80
        cb_char text[] = {
            0xC1, 0xC1, 0x81, 0x81,  /* 4 bytes */
            '\0' };
        cb_size ncp = 0;
        cb_size len = 0;
        TEST_TRUE( !cb_utf8_count_codepts(text, &len, &ncp) );
        TEST_TRUE( len == 0 );
        TEST_TRUE( ncp == 0 );
    }
}

void SetupTests(void)
{
    REG_TEST( u32len );
    REG_TEST( u16len );
    REG_TEST( u8len );    
}

