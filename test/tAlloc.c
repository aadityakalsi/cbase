/**
 * \file talloc.c
 * \date 2015
 */

#include "unittest.h"

/* TEST includes
 */
#include <cbase/memory.h>

TEST_FUNC( allocFree )
{
    void* p = cbase_alloc(50);
    TEST_TRUE( p );
    TEST_TRUE( (cb_size)p % CBASE_MEM_ALIGN == 0 );
    cbase_free(p);
}

TEST_FUNC( allocReallocFree )
{
    void* p = cbase_alloc(50);
    TEST_TRUE( p );
    TEST_TRUE( (cb_size)p % CBASE_MEM_ALIGN == 0 );
    p = cbase_realloc(p, 500);
    TEST_TRUE( p );
    TEST_TRUE( (cb_size)p % CBASE_MEM_ALIGN == 0 );
    cbase_free(p);
}

TEST_FUNC( callocFree )
{
    void* p = cbase_calloc(50);
    TEST_TRUE( p );
    TEST_TRUE( (cb_size)p % CBASE_MEM_ALIGN == 0 );
    {/* test calloc */
        char* mem = p;
        int i = 0;
        for (; i != 50; ++i) {
            TEST_TRUE( mem[i] == 0 );
        }
    }
    cbase_free(p);
}

void SetupTests(void)
{
    /* Correctness tests */
    REG_TEST( allocFree );
    REG_TEST( allocReallocFree );
    REG_TEST( callocFree );
}
