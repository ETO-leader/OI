#ifndef __TEST_LIB_H__
#define __TEST_LIB_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void cache_init(uint8_t associativity, uint8_t algorithm);
uint32_t cache_read(uint32_t address);

uint32_t memory_read(uint32_t address);

#endif
