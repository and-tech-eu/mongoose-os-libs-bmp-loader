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

#include "mgos_bmp_loader.h"

static int* mgos_bmp_loader_rotate_coords(int x, int y, int w, int h, int angle)
{
    static int out[4];
    out[2] = w;
    out[3] = h;
    switch (angle) {
    case 90:
        out[0] = y;
        out[1] = (w - x - 1) % w;
        out[2] = h;
        out[3] = w;
        break;
    case 180:
        out[0] = x;
        out[1] = (h - y - 1) % h;
        break;
    case 270:
        out[0] = (h - y - 1) % h;
        out[1] = (w - x - 1) % w;
        out[2] = h;
        out[3] = w;
        break;
    default:
        out[0] = x;
        out[1] = y;
        break;
    }
    return out;
}

bmpread_t* mgos_bmp_loader_create()
{
    bmpread_t* bmp_reader = calloc(1, sizeof(bmpread_t));
    return bmp_reader;
}

bool mgos_bmp_loader_load(bmpread_t* p_bmp, const char* bmp_file, unsigned int flags)
{
    bool result = false;
    if (bmp_file == NULL) {
        LOG(LL_ERROR, ("Bitmap file name is NULL, so bitmap could not be loaded!"));
    } else {
        if (bmpread(bmp_file, flags, p_bmp) > 0) {
            LOG(LL_DEBUG, ("Bitmap file <%s> successfully loaded!", bmp_file));
            result = true;
        } else {
            LOG(LL_ERROR, ("Bitmap file <%s> could not be loaded!", bmp_file));
        }
    }
    return result;
}

uint8_t* mgos_bmp_loader_get_data(bmpread_t* p_bmp) {
    return (uint8_t*) p_bmp->data;
}

uint32_t mgos_bmp_loader_get_width(bmpread_t* p_bmp)
{
    return (uint32_t)p_bmp->width;
}

uint32_t mgos_bmp_loader_get_height(bmpread_t* p_bmp)
{
    return (uint32_t) p_bmp->height;
}

uint8_t* mgos_bmp_loader_get_pixel(bmpread_t* p_bmp, uint32_t x, uint32_t y) {
    int num_channels = 3;
    uint8_t* p_src = (((y * p_bmp->width) + x) * num_channels) + p_bmp->data;
    return p_src;
}

bool mgos_bmp_loader_rotate(bmpread_t* p_bmp, uint16_t angle)
{
    bool result = true;
    int num_channels = 3;
    uint8_t* dest = calloc(1, p_bmp->width * p_bmp->height + 3);
    int x_dest = 0, y_dest = 0, w_dest = 0, h_dest = 0;
    for (int y = 0; y < p_bmp->height; y++) {
        for (int x = 0; x < p_bmp->width; x++) {
            int *out = mgos_bmp_loader_rotate_coords(x, y, p_bmp->width, p_bmp->height, angle);
            x_dest = out[0];
            y_dest = out[1];
            w_dest = out[2];
            h_dest = out[3];
            uint8_t* p_src = (((y * p_bmp->width) + x) * num_channels) + p_bmp->data;
            uint8_t* p_dest = (((y_dest * w_dest) + x_dest) * num_channels) + dest;
            memcpy(p_dest, p_src, num_channels);
        }
    }
    free(p_bmp->data);
    p_bmp->data = dest;
    p_bmp->width = w_dest;
    p_bmp->height = h_dest;

    return result;
}

void mgos_bmp_loader_free(bmpread_t* p_bmp)
{
    bmpread_free(p_bmp);
    free(p_bmp);
}

bool mgos_bmp_loader_init(void)
{
    return true;
}
