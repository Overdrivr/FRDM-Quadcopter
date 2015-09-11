#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>

//unsigned crc8(unsigned char *data, uint16_t len);
uint16_t crc16(uint8_t *data, uint16_t len);

#endif
