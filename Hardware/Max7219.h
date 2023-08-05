#ifndef __MAX7219_H
#define __MAX7219_H

void Max7219_x_WriteByte(uint8_t Address, uint8_t byte, uint8_t x);
void Max7219_Init(void);
void Max7219_1_ScanMatrix(uint16_t * Matrix);
void Max7219_OpenXY(uint8_t x, uint8_t y, uint16_t *Matrix);
void Max7219_CloseXY(uint8_t x, uint8_t y, uint16_t *Matrix);
uint8_t Max7219_CheckXY(uint8_t x, uint8_t y, uint16_t *Matrix);

#endif
