
/**
 * \file tVector.c
 * \date 2015
 */

#include "unittest.h"

#include <cbase/vector.h>

cbase_vector(cb_int32);

TEST_FUNC( vectorint )
{
    cb_int32* v = cbase_create_vector_cb_int32(20);
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
        v = cbase_vector_cb_int32_push(v, 1);
        TEST_TRUE( cbase_vector_size(v) == 21 );
        TEST_TRUE( cbase_vector_cap(v)  == 32 );
        TEST_TRUE( v[20] == 1 );
        ++sz;
        v = cbase_vector_cb_int32_push(v, 2);
        TEST_TRUE( cbase_vector_size(v) == 22 );
        TEST_TRUE( cbase_vector_cap(v)  == 32 );
        TEST_TRUE( v[21] == 2 );
        ++sz;
        for (; i != 10; ++i) {
            cb_int32* v1 = cbase_vector_cb_int32_push(v, 10);
            TEST_TRUE( cbase_vector_size(v) == i+sz+1 );
            TEST_TRUE( cbase_vector_cap(v)  == 32 );
            TEST_TRUE( v1[i + sz] == 10 );
            TEST_TRUE( v == v1 );
        }
        {/* beyond pow 2 capacity */
            cb_int32* v1 = cbase_vector_cb_int32_push(v, -1);
            TEST_TRUE( cbase_vector_size(v1) == 33 );
            TEST_TRUE( cbase_vector_cap(v1)  == 64 );
            v = v1;
        } 
    }
    {/* test resize */
        cb_int32* v1 = cbase_vector_cb_int32_resize(v, 5);
        ASSERT_TRUE( v == v1 );
        TEST_TRUE( cbase_vector_size(v) == 5 );

        v1 = cbase_vector_cb_int32_resize(v, 5000);
        TEST_TRUE( cbase_vector_size(v1) == 5000 );
        TEST_TRUE( cbase_vector_cap(v1) == 8192 );
        v = v1;
    }
    cbase_destroy_vector_cb_int32(v);
}

void SetupTests(void)
{
    REG_TEST( vectorint );
}
