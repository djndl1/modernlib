#ifndef UTFCONVERTER_H_
#define UTFCONVERTER_H_ value

#include <stdint.h>

MODERNLIB_PUBLIC
uint16_t *utf8_to_utf16(const uint8_t *utf8_buffer, size_t buffer_len);

MODERNLIB_PUBLIC
uint8_t *utf16_to_utf8(const uint16_t *utf16_buffer, size_t buffer_len);

#endif /* ifndef UTFCONVERTER_H_ */
