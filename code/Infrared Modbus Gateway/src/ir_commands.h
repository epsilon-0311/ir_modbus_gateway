#ifndef IR_COMMANDS_H
#define IR_COMMANDS_H

#include <Arduino.h>

const uint16_t pwr_on[] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};
const uint16_t pwr_on_len = 67;

const uint16_t pwr_off[] = {0xFFFF, 0x0000};
const uint16_t pwr_off_len = 2;

const uint16_t next_src[] = {0xFFFF, 0x0000};
const uint16_t next_src_len = 2;

const uint16_t priv_src[] = {0xFFFF, 0x0000};
const uint16_t priv_src_len = 2;

const uint16_t ir_frequency = 38;

#endif