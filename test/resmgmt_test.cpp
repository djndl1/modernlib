#include "modernlib/resmgmt.h"
#include "modernlib/basis.h"
#include <utest.h>

void inner_scope(int *a)
{
    defer_stmt {
        *a = 0;
        printf("a set to 0\n");
    };
}

UTEST(RES_MGMT, CPP_DEFER) 
{
    int a = 1;

    inner_scope(&a);

    EXPECT_EQ(0, a);
}

UTEST_MAIN();
