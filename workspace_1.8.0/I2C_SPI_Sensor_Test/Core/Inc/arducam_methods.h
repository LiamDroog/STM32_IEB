/*
 * arducam_methods.h
 *
 *  Created on: Dec 15, 2021
 *      Author: Liam Droog
 */
#include "main.h"
#ifndef INC_ARDUCAM_METHODS_H_
#define INC_ARDUCAM_METHODS_H_

uint8_t SPI2_read_reg(uint8_t addr);
void SPI2_write_reg(uint8_t addr, uint8_t data);

uint8_t bus_write(int address, int value);
uint8_t bus_read(int address);




// ########################### SPI STUFF #################################



#endif /* INC_ARDUCAM_METHODS_H_ */
