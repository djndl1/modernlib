#include "modernlib/resmgmt.h"
#include <utest.h>
#include <stdint.h>
#include "modernlib/basis.h"


UTEST(RES_MGMT, MOVE_RES)
{
    merror e1 = { 1 };
    merror e2 = { 0 };

    move_res(e1, e2, (merror){0});
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

UTEST_MAIN();
