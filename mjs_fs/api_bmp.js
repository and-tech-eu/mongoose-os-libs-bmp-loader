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

let BMP_LOADER = {

  create: function () {
    return Object.create({

      _bmp: BMP_LOADER._create(),

      load: this._load,
      free: this._free,
      getData: this._getData,
      getPixel: this._getPixel,
      getWidth: this._getWidth,
      getHeight: this._getHeight
    });
  },

  load: function (file, flags) {
    return BMP_LOADER._load(this._bmp, file, flags);
  },

  free: function () {
    BMP_LOADER._free(this._bmp, file, flags);
    this._bmp = null;
    gc(true);
  },

  getData: function () {
    return BMP_LOADER._getData(this._bmp);
  },

  // ## **`bitmap.getPixel(x, y)`**
  // Returns pixel's RGB value at pos x,y
  getPixel: function (x, y) {
    let pixel = BMP_LOADER._getPixel(this._bmp, x, y);
    return [pixel[0], pixel[1], pixel[2]];
  },

  getWidth: function () {
    return BMP_LOADER._getWidth(this._bmp);
  },

  getHeight: function () {
    return BMP_LOADER._getHeight(this._bmp, x, y);
  },

  _create: ffi('void *mgos_bmp_loader_create(void);'),
  _load: ffi('int mgos_bmp_loader_load(void *, char *, int);'),
  _free: ffi('void mgos_bmp_loader_free(void *)'),
  _getData: ffi('void *mgos_bmp_loader_get_data(void *)'),
  _getPixel: ffi('void *mgos_bmp_loader_get_pixel(void *, int, int)'),
  _getWidth: ffi('void *mgos_bmp_loader_get_width(void *, int, int)'),
  _getHeight: ffi('void *mgos_bmp_loader_get_height(void *, int, int)'),

  BMPREAD_TOP_DOWN: 1,
  BMPREAD_BYTE_ALIGN: 2,
  BMPREAD_ANY_SIZE: 4,
  BMPREAD_ALPHA: 8

};
