
/**
 * \file tints.c
 * \date 2015
 */

#include "unittest.h"

#include <cbase/ints.h>

TEST_FUNC( invariants )
{
    TEST_TRUE( CBASE_32_BIT || CBASE_64_BIT );
    TEST_TRUE( !CBASE_BIG_ENDIAN );
    TEST_TRUE( sizeof(cb_char)   == 1 );
    TEST_TRUE( sizeof(cb_uchar)  == 1 );
    TEST_TRUE( sizeof(cb_int8)   == 1 );
    TEST_TRUE( sizeof(cb_uint8)  == 1 );
    TEST_TRUE( sizeof(cb_int16)  == 2 );
    TEST_TRUE( sizeof(cb_uint16) == 2 );
    TEST_TRUE( sizeof(cb_int32)  == 4 );
    TEST_TRUE( sizeof(cb_uint32) == 4 );
    TEST_TRUE( sizeof(cb_char32) == 4 );
    TEST_TRUE( sizeof(cb_int64)  == 8 );
    TEST_TRUE( sizeof(cb_uint64) == 8 );
    TEST_TRUE( sizeof(float)     == 4 );
    TEST_TRUE( sizeof(double)    == 8 );
#if CBASE_32_BIT
    TEST_TRUE( sizeof(cb_size)   == 4 );
    TEST_TRUE( sizeof(cb_ssize)  == 4 );
#endif
#if CBASE_64_BIT
    TEST_TRUE( sizeof(cb_size)   == 8 );
    TEST_TRUE( sizeof(cb_ssize)  == 8 );
#endif
    TEST_TRUE( sizeof(cb_bool)   == 1 );
    TEST_TRUE( CB_TRUE   );
    TEST_TRUE( !CB_FALSE );
}

void SetupTests(void)
{
    REG_TEST( invariants );
}

