
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
        TEST_TRUE( cbase_vector_cb_int32_size(v) == 20 );
        TEST_TRUE( cbase_vector_cb_int32_cap(v)  == 32 );
    }
    // {/* fill with zeros */
    //     cb_size sz = cbase_vector_cb_int32_size(v);
    //     cb_size i = 0;
    //     for (; i != sz; ++i) {
    //         v[i] = 0;
    //     }
    // }
    // {/* test zeros */
    //     cb_size sz = cbase_vector_cb_int32_size(v);
    //     cb_size i = 0;
    //     for (; i != sz; ++i) {
    //         TEST_TRUE( v[i] == 0 );
    //     }
    // }
    cbase_destroy_vector_cb_int32(v);
}

void SetupTests(void)
{
    REG_TEST( vectorint );
}
