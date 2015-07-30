
/**
 * \file tVector.c
 * \date 2015
 */

#include "unittest.h"

#include <cbase/vector.h>

cbase_vector(cb_int32);

TEST_FUNC( vectorint )
{
    cb_int32* v = cbase_vector_create_cb_int32(20);
    {/* test size */
        TEST_TRUE( cbase_vector_size(v) == 20 );
        TEST_TRUE( cbase_vector_cap(v)  == 32 );
    }
    {/* fill with zeros */
        cb_size sz = cbase_vector_size(v);
        cb_size i = 0;
        for (; i != sz; ++i) {
            v[i] = 0;
        }
    }
    {/* test zeros */
        cb_size sz = cbase_vector_size(v);
        cb_size i = 0;
        for (; i != sz; ++i) {
            TEST_TRUE( v[i] == 0 );
        }
    }
    {/* test push */
        cb_size sz = 20;
        cb_size i = 0;
        TEST_TRUE( cbase_vector_push_cb_int32(&v, 1) );
        TEST_TRUE( cbase_vector_size(v) == 21 );
        TEST_TRUE( cbase_vector_cap(v)  == 32 );
        TEST_TRUE( v[20] == 1 );
        ++sz;
        TEST_TRUE( cbase_vector_push_cb_int32(&v, 2) );
        TEST_TRUE( cbase_vector_size(v) == 22 );
        TEST_TRUE( cbase_vector_cap(v)  == 32 );
        TEST_TRUE( v[21] == 2 );
        ++sz;
        for (; i != 10; ++i) {
            TEST_TRUE( cbase_vector_push_cb_int32(&v, 10) );
            TEST_TRUE( cbase_vector_size(v) == i+sz+1 );
            TEST_TRUE( cbase_vector_cap(v)  == 32 );
            TEST_TRUE( v[i + sz] == 10 );
        }
        {/* beyond pow 2 capacity */
            TEST_TRUE( cbase_vector_push_cb_int32(&v, -1) );
            TEST_TRUE( cbase_vector_size(v) == 33 );
            TEST_TRUE( cbase_vector_cap(v)  == 64 );
        } 
    }
    {/* test resize */
        TEST_TRUE( cbase_vector_resize_cb_int32(&v, 5) );
        TEST_TRUE( cbase_vector_size(v) == 5 );

        TEST_TRUE( cbase_vector_resize_cb_int32(&v, 5000) );
        TEST_TRUE( cbase_vector_size(v) == 5000 );
        TEST_TRUE( cbase_vector_cap(v) == 8192 );
    }
    cbase_vector_destroy(v);
}

TEST_FUNC( vectorintTooBig )
{
    cb_int32* v = cbase_vector_create_cb_int32((cb_size)-1);
    TEST_TRUE( v == NULL );
    v = cbase_vector_create_cb_int32(20);
    TEST_TRUE( v );
    TEST_FALSE( cbase_vector_resize_cb_int32(&v, (cb_size)-1) );
    cbase_vector_destroy(v);
}

void SetupTests(void)
{
    REG_TEST( vectorint );
    REG_TEST( vectorintTooBig );
}
