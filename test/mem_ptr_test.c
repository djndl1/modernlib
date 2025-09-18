#include "modernlib/allocator.h"
#include "modernlib/resmgmt.h"

#undef nullptr 
#define nullptr NULL
#include "utest.h"

#define mem_ptr_typename int_ptr
#define mem_ptr_target_typename int
#include "modernlib/mem_ptr_itf.h"

#define mem_ptr_typename long_ptr
#define mem_ptr_target_typename long
#include "modernlib/mem_ptr_itf.h"

typedef struct kilobyte {
    uint8_t bytes[1024];
} kilobyte;

#define mem_ptr_typename kilobyte_ptr
#define mem_ptr_target_typename kilobyte
#include "modernlib/mem_ptr_itf.h"

UTEST(MEM_PTR, CREATE_DESTROY) {
    for (int i = 0; i < 100000000; i++) {
        kilobyte_ptr ip = kilobyte_ptr_allocate(1, std_allocator).result;
        deferred(kilobyte_ptr_destroy(&ip)) {
            ASSERT_NE(ip.ptr, nullptr);
        }
    }
}

UTEST(MEM_PTR, MOVE) {
    kilobyte_ptr ip = kilobyte_ptr_allocate(1, std_allocator).result;
    ASSERT_NE(ip.ptr, nullptr);
    deferred(kilobyte_ptr_destroy(&ip)) {
        for (int i = 0; i < 100000000; i++) {
            kilobyte_ptr another = kilobyte_ptr_move(&ip);
            ASSERT_EQ(ip.ptr, nullptr);
            ASSERT_EQ(ip.allocator, nullptr);

            ASSERT_NE(another.ptr, nullptr);
            ASSERT_NE(another.allocator, nullptr);

            ip = kilobyte_ptr_move(&another);

            ASSERT_EQ(another.ptr, nullptr);
            ASSERT_EQ(another.allocator, nullptr);
        }
    }
}


UTEST_MAIN();
