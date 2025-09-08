#include "modernlib/dyn_char_array.h"
#include <stdlib.h>
#include "modernlib/resmgmt.h"
#include "modernlib/common_mem_ptr.h"
#include "modernlib/allocator.h"

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#   include <windows.h>

uint8_t *utf16_to_utf8(const uint16_t *wide_char_buffer, size_t buffer_len)
{
    if (wide_char_buffer == nullptr) return nullptr;

    int len_param = buffer_len < 1 ? -1 : buffer_len;
    int utf8_buffer_len = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer, len_param, nullptr, 0, nullptr, nullptr);

    uint8_t *utf8_buffer = calloc(utf8_buffer_len + 1, sizeof(char));
    if (utf8_buffer == nullptr) return nullptr;

    int result = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer, len_param, utf8_buffer, utf8_buffer_len + 1, nullptr, nullptr);
    if (result == 0) {
        if (utf8_buffer != nullptr) {
            free(utf8_buffer);
        }
        return nullptr;
    }

    return utf8_buffer;
}

uint16_t *utf8_to_utf16(const uint8_t *utf8_buffer, size_t buffer_len)
{
    if (utf8_buffer == nullptr) return nullptr;

    int len_param = buffer_len < 1 ? -1 : buffer_len;

    int utf16_buffer_len = MultiByteToWideChar(CP_UTF8, 0, utf8_buffer, len_param, nullptr, 0);

    uint16_t *utf16_buffer = calloc(utf16_buffer_len + 1, sizeof(wchar_t));
    if (utf16_buffer == nullptr) return nullptr;

    int result = MultiByteToWideChar(CP_UTF8, 0, utf8_buffer, len_param, utf16_buffer, utf16_buffer_len + 1);
    if (result == 0) {
        if (utf16_buffer != nullptr) {
            free(utf16_buffer);
        }
        return nullptr;
    }

    return utf16_buffer;
}

#else
#include <iconv.h>

char *iconv_convert(const char *source_charset, const char *dest_charset, const char *source_buffer, size_t buffer_len, size_t output_buffer_init_size, size_t output_cp_size)
{
    auto alloc_result = allocator_allocate(std_allocator, output_buffer_init_size);
    if(alloc_result.error) {
       return nullptr;
    }
    char *output_buffer = alloc_result.mem;

    iconv_t cd = iconv_open(dest_charset, source_charset);
    if (cd == (iconv_t)-1) {
        return nullptr;
    }

    char *result = nullptr;
    deferred(iconv_close(cd)) {
        char *input_buffer = (char*)source_buffer;
        char *output_ptr = output_buffer;
        size_t inputBytesLeft = buffer_len;
        size_t outputBytesLeft = output_buffer_init_size;
        size_t converted_num = iconv(cd, &input_buffer, &buffer_len, &output_ptr, &outputBytesLeft);
        (void)inputBytesLeft;

        if (converted_num == -1) {
            goto deallocate_output_buffer;
        }

        size_t real_output_len = output_buffer_init_size - outputBytesLeft;
        auto realloc_result = allocator_reallocate(std_allocator, output_buffer, real_output_len + output_cp_size);

        if (realloc_result.error) {
            goto deallocate_output_buffer;
        }
        result = realloc_result.mem;
        // set final NULL
        memset(result + real_output_len, 0, output_cp_size);

        break;
deallocate_output_buffer:
        allocator_deallocate(std_allocator, output_buffer);
        result = nullptr;

        break;
    }

    return result;
}

uint16_t *utf8_to_utf16(const uint8_t *utf8_buffer, size_t buffer_len)
{
    if (utf8_buffer == nullptr) return nullptr;
    if (buffer_len == 0) {
        auto alloc_result = uint16_mem_ptr_allocate(1, std_allocator);
        if (alloc_result.error) {
            return nullptr;
        }
        alloc_result.result.ptr[0] = 0;
        return alloc_result.result.ptr;
    }


    if (buffer_len < 0) {
        buffer_len = strlen((const char*)utf8_buffer);
    }
    const char *input_buffer = (const char*)utf8_buffer;
    char *output = iconv_convert("UTF-8", "UTF-16LE", input_buffer, buffer_len, 2 * buffer_len, 1);

    return (uint16_t*)output;
}

uint8_t *utf16_to_utf8(const uint16_t *utf16_buffer, size_t buffer_len)
{
    if (utf16_buffer == nullptr) return nullptr;
    if (buffer_len == 0) {
        auto alloc_result = uint8_mem_ptr_allocate(1, std_allocator);
        if (alloc_result.error) {
            return nullptr;
        }
        alloc_result.result.ptr[0] = 0;
        return alloc_result.result.ptr;
    }

    if (buffer_len < 0) {
        buffer_len = strlen((const char*)utf16_buffer);
    }
    const char *input_buffer = (const char*)utf16_buffer;
    char *output = iconv_convert("UTF-16LE", "UTF-8", input_buffer, buffer_len, buffer_len + buffer_len / 2 + 4, 2);
    if (output == nullptr) {
        output = iconv_convert("UTF-16LE", "UTF-8", input_buffer, buffer_len, 2 * buffer_len, 2);
    }

    return (uint8_t*)output;
}

#endif
