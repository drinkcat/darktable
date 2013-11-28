/*
    This file is part of darktable,
    copyright (c) 2013 Nicolas Boichat.

    darktable is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    darktable is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with darktable.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DT_VECTOR_H
#define DT_VECTOR_H

#include <stdint.h>

typedef float v4sf __attribute__ ((vector_size (16)));

static inline v4sf v4sf_set(float x3, float x2, float x1, float x0) {
  return (v4sf){x0,x1,x2,x3};
}

static inline v4sf v4sf_setall(float x) {
  return v4sf_set(x,x,x,x);
}

static inline v4sf v4sf_min(v4sf x1, v4sf x2) {
  return (v4sf){
      (x1[0] < x2[0]) ? x1[0] : x2[0],
      (x1[1] < x2[1]) ? x1[1] : x2[1],
      (x1[2] < x2[2]) ? x1[2] : x2[2],
      (x1[3] < x2[3]) ? x1[3] : x2[3],
  };
}

static inline v4sf v4sf_max(v4sf x1, v4sf x2) {
  return (v4sf){
      (x1[0] > x2[0]) ? x1[0] : x2[0],
      (x1[1] > x2[1]) ? x1[1] : x2[1],
      (x1[2] > x2[2]) ? x1[2] : x2[2],
      (x1[3] > x2[3]) ? x1[3] : x2[3],
  };
}

typedef int32_t v4si __attribute__ ((vector_size (16)));

static inline v4si v4si_set(int32_t x3, int32_t x2, int32_t x1, int32_t x0) {
  return (v4si){x0,x1,x2,x3};
}

static inline v4si v4si_setall(int32_t x) {
  return v4si_set(x,x,x,x);
}

static inline v4sf v4si_to_v4sf(v4si x) {
  return (v4sf){(float)x[0], (float)x[1], (float)x[2], (float)x[3]};
}

static inline v4sf v4sf_sign(v4sf x) {
  return v4si_to_v4sf(-(x > 0) + (x < 0));
}

static inline v4sf v4sf_abs(v4sf x) {
  return v4sf_sign(x)*x;
}

static inline void vector_sfence() {
  __builtin_ia32_sfence ();
}

#endif
