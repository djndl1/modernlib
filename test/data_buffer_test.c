#include "modernlib/data_buffer.h"
#include "modernlib/basis.h"
#include <stdlib.h>
#include <time.h>

#undef nullptr 
#define nullptr NULL
#include "utest.h"

#define M_COUNT(n) (n * 1000000)

UTEST(DATA_BUFFER, transient)
{
    for (size_t i = 0; i < M_COUNT(100); i++) {
        srand(time(NULL));
        char bufarr[] = { rand(), rand(), rand(), rand(), rand(), 1, 1, 1, 1, 1, };
        data_buffer buf;
        scoped(buf = DATA_BUFFER_TRANSIENT(bufarr, sizeof bufarr),
               data_buffer_destroy(&buf)) {
            EXPECT_EQ(buf.length, sizeof bufarr);
            EXPECT_EQ(buf.data, bufarr);
            for (size_t i = 0; i < buf.length; i++) {
                EXPECT_EQ(byte_buffer_at(buf, i), bufarr[i]);
            }
        }
    }
}

UTEST(DATA_BUFFER, new)
{
    for (size_t i = 0; i < M_COUNT(10); i++) {
        srand(time(NULL));

        data_buffer buf;
        scoped(buf = data_buffer_new(100, std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
            }
        }
    }
}

UTEST(DATA_BUFFER, move_from)
{
    for (size_t i = 0; i < 10000; i++) {
        srand(time(NULL));

        data_buffer buf;
        scoped(buf = data_buffer_new(rand() % M_COUNT(1), std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
            }

            data_buffer moved;
            size_t len = buf.length;
            const mem_allocator *allocator = buf.allocator;
            void *data = data_buffer_release(&buf);
            EXPECT_EQ(buf.data, nullptr);

            const uint8_t *data_borrowed = data;
            scoped(moved = data_buffer_move_from(&data, len, allocator).buffer,
                   data_buffer_destroy(&moved)) {
                EXPECT_EQ(data, nullptr);
                EXPECT_EQ(moved.data, data_borrowed);

                for (size_t j = 0; j < moved.length; j++) {
                    EXPECT_EQ(byte_buffer_at(moved, j), data_borrowed[j]);
                }
            }
        }
    }
}

UTEST(DATA_BUFFER, copy_to)
{
    for (size_t i = 0; i < 10000; i++) {
        srand(time(NULL));

        data_buffer buf;
        scoped(buf = data_buffer_new(rand() % M_COUNT(1), std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
            }

            data_buffer copied;
            scoped(copied = data_buffer_new(buf.length, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_to(buf, &copied);
                EXPECT_EQ(e.error, 0);

                for (size_t j = 0; j < copied.length; j++) {
                    EXPECT_EQ(byte_buffer_at(copied, j), byte_buffer_at(buf, j));
                }
            }

            scoped(copied = data_buffer_new(buf.length / 2, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_to(buf, &copied);
                EXPECT_EQ(e.error, 0);

                for (size_t j = 0; j < copied.length; j++) {
                    EXPECT_EQ(byte_buffer_at(copied, j), byte_buffer_at(buf, j));
                }
            }

            scoped(copied = data_buffer_new(buf.length, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_to(buf, &copied);

                EXPECT_EQ(e.error, 0);
            }
        }
    }
}

UTEST(DATA_BUFFER, resize)
{
    for (size_t i = 0; i < 10000; i++) {
        srand(time(NULL));

        data_buffer buf;
        scoped(buf = data_buffer_new(rand() % M_COUNT(1), std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            uint8_t before_resizing[10];
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
                if (j < 10) {
                    before_resizing[j] = byte_buffer_at(buf, j);
                }
            }
            data_buffer_resize(&buf, 10);
            EXPECT_EQ(buf.length, 10);

            for (size_t j = 0; j < buf.length; j++) {
                EXPECT_EQ(byte_buffer_at(buf, j), before_resizing[j]);
            }
        }

        scoped(buf = data_buffer_new(rand() % M_COUNT(1), std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
            }

            data_buffer temp;
            scoped(temp = data_buffer_copy(buf).buffer, data_buffer_destroy(&temp)) {
                size_t newlen = buf.length * 2;
                data_buffer_resize(&buf, newlen);
                EXPECT_EQ(buf.length, newlen);

                for (size_t j = 0; j < temp.length; j++) {
                    EXPECT_EQ(byte_buffer_at(buf, j), byte_buffer_at(temp, j));
                }
            }
        }
    }
}


UTEST(DATA_BUFFER, copy_content_from)
{
    for (size_t i = 0; i < 10000; i++) {
        srand(time(NULL));

        data_buffer buf;
        scoped(buf = data_buffer_new(rand() % M_COUNT(1), std_allocator).buffer,
               data_buffer_destroy(&buf)) {
            for (size_t j = 0; j < buf.length; j++) {
                byte_buffer_at(buf, j) = rand();
            }

            data_buffer copied;
            scoped(copied = data_buffer_new(buf.length, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_content_from(&copied, buf.data, buf.length);
                EXPECT_EQ(e.error, 0);

                for (size_t j = 0; j < copied.length; j++) {
                    EXPECT_EQ(byte_buffer_at(copied, j), byte_buffer_at(buf, j));
                }
            }

            scoped(copied = data_buffer_new(buf.length / 2, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_content_from(&copied, buf.data, buf.length);
                EXPECT_EQ(e.error, 0);

                for (size_t j = 0; j < copied.length; j++) {
                    EXPECT_EQ(byte_buffer_at(copied, j), byte_buffer_at(buf, j));
                }
            }

            scoped(copied = data_buffer_new(buf.length, std_allocator).buffer,
                   data_buffer_destroy(&copied)) {
                merror e = data_buffer_copy_content_from(&copied, buf.data, 0);

                EXPECT_EQ(e.error, 0);
            }
        }
    }
}

UTEST(DATA_BUFFER, move)
{
    data_buffer initial;
    const size_t buflen = 100000;
    scoped(initial = data_buffer_new(buflen, std_allocator).buffer,
           data_buffer_destroy(&initial)) {

        for (size_t round = 0; round < M_COUNT(1000); round++) {
            data_buffer target = data_buffer_move(&initial);

            EXPECT_NE(target.data, nullptr);
            EXPECT_EQ(target.length, buflen);
            EXPECT_EQ(target.allocator, std_allocator);

            EXPECT_EQ(initial.data, nullptr);
            EXPECT_EQ(initial.length, 0);
            EXPECT_EQ(initial.allocator, nullptr);

            initial = data_buffer_move(&target);
        }
    }
}

UTEST_MAIN();
