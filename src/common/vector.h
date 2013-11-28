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

#ifdef __SSE2__
#include <xmmintrin.h>

static inline void vector_init() {
    // make everything go a lot faster.
  _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}

#else
#include <stdint.h>

static inline void vector_init() {}

typedef float __m128 __attribute__ ((vector_size (16)));
typedef int32_t __m128i __attribute__ ((vector_size (16)));
typedef int64_t __m128i2 __attribute__ ((vector_size (16)));

static inline __m128 _mm_set_ps(float x3, float x2, float x1, float x0) {
  return (__m128){x0,x1,x2,x3};
}

static inline __m128 _mm_set_ps1(float x) { return (__m128){x,x,x,x}; }
static inline __m128 _mm_set1_ps(float x) { return (__m128){x,x,x,x}; }

static inline __m128 _mm_setzero_ps() { return _mm_set_ps1(0.f); }

static inline __m128 _mm_min_ps(__m128 x1, __m128 x2) {
  return (__m128){
    x1[0]<x2[0]?x1[0]:x2[0],
    x1[1]<x2[1]?x1[1]:x2[1],
    x1[2]<x2[2]?x1[2]:x2[2],
    x1[3]<x2[3]?x1[3]:x2[3]
  };
}

static inline __m128 _mm_max_ps(__m128 x1, __m128 x2) {
  return (__m128){
    x1[0]>x2[0]?x1[0]:x2[0],
    x1[1]>x2[1]?x1[1]:x2[1],
    x1[2]>x2[2]?x1[2]:x2[2],
    x1[3]>x2[3]?x1[3]:x2[3]
  };
}

static inline __m128 _mm_cmple_ps(__m128 x1, __m128 x2) {
  return (__m128)(__m128i){
    x1[0]<=x2[0]? -1:0,
    x1[1]<=x2[1]? -1:0,
    x1[2]<=x2[2]? -1:0,
    x1[3]<=x2[3]? -1:0
  };
}

static inline __m128 _mm_cmpgt_ps(__m128 x1, __m128 x2) {
  return (__m128)(__m128i){
    x1[0]>x2[0]? -1:0,
    x1[1]>x2[1]? -1:0,
    x1[2]>x2[2]? -1:0,
    x1[3]>x2[3]? -1:0
  };
}

static inline __m128 _mm_add_ps(__m128 x1, __m128 x2) {
  return x1+x2;
}

static inline __m128 _mm_sub_ps(__m128 x1, __m128 x2) {
  return x1-x2;
}

static inline __m128 _mm_sub_ss(__m128 x1, __m128 x2) {
  return (__m128){x1[0]-x2[0],x1[1],x1[2],x1[3]};
}

static inline __m128 _mm_mul_ps(__m128 x1, __m128 x2) {
  return x1*x2;
}

static inline __m128 _mm_div_ps(__m128 x1, __m128 x2) {
  return x1/x2;
}

static inline __m128 _mm_rcp_ps(__m128 x) {
  return 1.f/x;
}

static inline __m128 _mm_and_ps(__m128 x1, __m128 x2) {
  return (__m128)((__m128i)x1 & (__m128i)x2);
}

static inline __m128 _mm_andnot_ps(__m128 x1, __m128 x2) {
  return (__m128)(~((__m128i)x1) & (__m128i)x2);
}

static inline __m128 _mm_or_ps(__m128 x1, __m128 x2) {
  return (__m128)((__m128i)x1 | (__m128i)x2);
}

#define _MM_SHUFFLE(x3, x2, x1, x0) ((__m128i){x0, x1, x2, x3})

static inline __m128 _mm_shuffle_ps(__m128 x, __m128 y, __m128i s) {
  return __builtin_shuffle(x,y,s);
}

static inline __m128 _mm_unpacklo_ps(__m128 x, __m128 y) {
  return _mm_shuffle_ps(x,y,(__m128i){0,4,1,5});
}

static inline __m128 _mm_unpackhi_ps(__m128 x, __m128 y) {
  return _mm_shuffle_ps(x,y,(__m128i){2,6,3,7});
}

static inline __m128 _mm_movehl_ps(__m128 x, __m128 y) {
  return _mm_shuffle_ps(x,y,(__m128i){6,7,3,2});
}

static inline __m128 _mm_movelh_ps(__m128 x, __m128 y) {
  return _mm_shuffle_ps(x,y,(__m128i){0,1,4,5});
}

static inline __m128 _mm_load_ps(const float* p) {
  return *((__m128*)p);
}

static inline void _mm_store_ps(float* p, __m128 x) {
  *((__m128*)p) = x;
}

static inline void _mm_stream_ps(float* p, __m128 x) {
  *((__m128*)p) = x;
}

static inline __m128i _mm_cvtps_epi32(__m128 x) {
  return (__m128i){(int32_t)x[0],(int32_t)x[1],(int32_t)x[2],(int32_t)x[3]};
}

static inline __m128 _mm_cvtepi32_ps(__m128i x) {
  return (__m128){(float)x[0],(float)x[1],(float)x[2],(float)x[3]};
}

static inline __m128i _mm_set_epi32(int32_t x3, int32_t x2, int32_t x1, int32_t x0) {
  return (__m128i){x0,x1,x2,x3};
}

static inline __m128i _mm_set1_epi32(int32_t x) {
  return (__m128i){x,x,x,x};
}

static inline __m128i _mm_add_epi32(__m128i x1, __m128i x2) {
  return x1+x2;
}

static inline __m128i _mm_and_si128(__m128i x1, __m128i x2) {
  return x1 & x2;
}

static inline __m128i _mm_andnot_si128(__m128i x1, __m128i x2) {
  return (~x1) & x2;
}

static inline __m128i _mm_or_si128(__m128i x1, __m128i x2) {
  return x1 | x2;
}

static inline __m128i _mm_slli_epi64(__m128i x, int count) {
  __m128i2 y = (__m128i2)x;
  return (__m128i)(y<<count);
}

static inline __m128i _mm_srai_epi32(__m128i x, int count) {
  return x << count;
}

static inline __m128 _mm_castsi128_ps(__m128i x) {
  return (__m128)x;
}

static inline __m128i _mm_castps_si128(__m128 x) {
  return (__m128i)x;
}

#define _MM_HINT_NTA 0

static inline void _mm_prefetch(char* p, int i) {
  /* FIXME */
}

static inline void _mm_sfence() {
  __sync_synchronize();
}

#endif

#endif
