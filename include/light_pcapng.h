// light_pcapng.h
// Created on: Jul 23, 2016

// Copyright (c) 2016 Radu Velea

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LIGHT_PCAPNG_H_
#define LIGHT_PCAPNG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "light_special.h"

#define LIGHT_SECTION_HEADER_BLOCK  0x0A0D0D0A
#define LIGHT_INTERFACE_BLOCK       0x00000001
#define LIGHT_ENHANCED_PACKET_BLOCK 0x00000006
#define LIGHT_SIMPLE_PACKET_BLOCK   0x00000003

#define LIGHT_CUSTOM_DATA_BLOCK     0xB16B00B5

#define BYTE_ORDER_MAGIC            0x1A2B3C4D

/////////////////////////////// ////////////ERROR CODES //////////////////////////////////////////////

#define LIGHT_SUCCESS           0
#define LIGHT_INVALID_SECTION  -1

/////////////////////////////// STANDARD PCAPNG STRUCTURES & FUNCTIONS ///////////////////////////////

typedef struct _light_pcapng *light_pcapng;
typedef struct _light_option *light_option;

// Read/Write Functions
light_pcapng light_read_from_path(const char *file_name);
light_pcapng light_read_from_memory(const uint32_t *memory, size_t size);
uint32_t *light_pcapng_to_memory(const light_pcapng pcapng, size_t *size);
int light_pcapng_to_file(const char *file_name, const light_pcapng pcapng);
void light_pcapng_release(light_pcapng pcapng);
// For Debugging Purposes
char *light_pcapng_to_string(light_pcapng pcapng);

// Manipulation Functions
int light_add_option(light_pcapng section, light_pcapng pcapng, light_option option, int copy);
int light_subcapture(const light_pcapng section, int (*predicate)(const light_pcapng), light_pcapng *subcapture);

// Allocation and free functions
light_option light_alloc_option(uint16_t option_length);
light_pcapng light_alloc_block(uint32_t block_body_lengh);
void light_free_option(light_option option);
void light_free_block(light_pcapng pcapng);

/////////////////////////////// CONTINUOUS MEMORY BLOCK STRUCTURES & FUNCTIONS ///////////////////////////////

typedef struct _light_pcapng_mem *light_pcapng_mem;

// Continuous Memory Functions
struct _light_pcapng_mem *light_no_copy_from_memory(uint32_t *memory, size_t size, int is_owner);
void light_pcapng_mem_release(struct _light_pcapng_mem *pcapng);

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_PCAPNG_H_ */