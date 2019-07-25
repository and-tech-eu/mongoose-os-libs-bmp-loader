/*
 * Copyright (c) 2019 Manfred Müller-Späth <fms1961@gmail.com>
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _MGOS_BMP_LOADER_INCLUDE_H_
#define _MGOS_BMP_LOADER_INCLUDE_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bmpread.h"
#include "mgos.h"

#if defined(__cplusplus)
extern "C" { // Make sure we have C-declarations in C++ programs
#endif

bmpread_t* mgos_bmp_loader_create(void);
bool mgos_bmp_loader_load(bmpread_t* p_bmp, const char* bmp_file, unsigned int flags);
void mgos_bmp_loader_free(bmpread_t* p_bmp);

uint8_t* mgos_bmp_loader_get_data(bmpread_t* p_bmp);
uint32_t mgos_bmp_loader_get_width(bmpread_t* p_bmp);
uint32_t mgos_bmp_loader_get_height(bmpread_t* p_bmp);
uint8_t* mgos_bmp_loader_get_pixel(bmpread_t* p_bmp, uint32_t x, uint32_t y);

bool mgos_bmp_loader_rotate(bmpread_t* p_bmp, uint16_t angle);

#if defined(__cplusplus)
}
#endif

#endif /* _MGOS_BMP_LOADER_INCLUDE_H_ */
