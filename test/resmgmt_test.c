#include "modernlib/resmgmt.h"
#include <utest.h>
#include <stdint.h>
#include <stdio.h>
#include "modernlib/basis.h"


UTEST(RES_MGMT, MOVE_RES)
{
    error_t e1 = { 1 };
    error_t e2 = { 0 };

    move_res(e1, e2, (error_t){0});
    EXPECT_EQ(e1.error, 0);
    EXPECT_EQ(e2.error, 1);
}


UTEST(RES_MGMT, MOVE_PTR)
{
    uint8_t b = 0;
    uint8_t *p1 = &b;
    uint8_t *p2;
    move_ptr(p1, p2);

    EXPECT_EQ(p2, &b);
    EXPECT_EQ(p1, nullptr);
}

#ifdef __GNUC__

void inner_scope(int *a)
{
    defer_stmt {
        *a = 0;
        printf("a set to 0\n");
    };
}

UTEST(RES_MGMT, GNU_DEFER) 
{
    int a = 1;

    inner_scope(&a);

    EXPECT_EQ(0, a);
}

#endif

UTEST_MAIN();
