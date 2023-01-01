// Auto-generated file. Do not edit!
//   Template: src/f32-velu/sse-rr2-lut16-p3.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <smmintrin.h>

#include <xnnpack/vunary.h>
#include <xnnpack/common.h>


extern XNN_INTERNAL const float xnn_table_exp2minus_k_over_16[16];

void xnn_f32_velu_ukernel__sse41_rr2_lut16_p3_x8(
    size_t n,
    const float* x,
    float* y,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN
{
  assert(n != 0);
  assert(n % sizeof(float) == 0);
  assert(x != NULL);
  assert(y != NULL);

  const __m128 vprescale = _mm_load_ps(params->sse.prescale);
  const __m128 valpha = _mm_load_ps(params->sse.alpha);
  const __m128 vbeta = _mm_load_ps(params->sse.beta);

  const __m128 vsat_cutoff = _mm_set1_ps(-0x1.154246p+4f);
  const __m128 vmagic_bias = _mm_set1_ps(0x1.800000p19f);
  const __m128 vlog2e = _mm_set1_ps(0x1.715476p+0f);
  const __m128i vindex_mask = _mm_set1_epi32(0xF);
  const __m128 vminus_ln2_hi = _mm_set1_ps(-0x1.62E400p-1f);
  const __m128 vminus_ln2_lo = _mm_set1_ps(-0x1.7F7D1Cp-20f);
  const __m128 vc3 = _mm_set1_ps(0x1.55561Cp-3f);
  const __m128 vc2 = _mm_set1_ps(0x1.0001ECp-1f);
  const __m128 vone = _mm_set1_ps(1.0f);

  for (; n >= 8 * sizeof(float); n -= 8 * sizeof(float)) {
    __m128 vx0123 = _mm_loadu_ps(x);
    __m128 vx4567 = _mm_loadu_ps(x + 4);
    x += 8;

    const __m128 vz0123 = _mm_max_ps(vsat_cutoff, _mm_mul_ps(vx0123, vprescale));
    const __m128 vz4567 = _mm_max_ps(vsat_cutoff, _mm_mul_ps(vx4567, vprescale));

    __m128 vn0123 = _mm_add_ps(_mm_mul_ps(vz0123, vlog2e), vmagic_bias);
    __m128 vn4567 = _mm_add_ps(_mm_mul_ps(vz4567, vlog2e), vmagic_bias);

    const __m128i vidx0123 = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn0123), vindex_mask), 2);
    const __m128i ven0123 = _mm_slli_epi32(_mm_castps_si128(vn0123), 19);
    const __m128i vidx4567 = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn4567), vindex_mask), 2);
    const __m128i ven4567 = _mm_slli_epi32(_mm_castps_si128(vn4567), 19);

    #if XNN_ARCH_X86_64
      const uint64_t vidx01 = (uint64_t) _mm_cvtsi128_si64(vidx0123);
      const uint64_t vidx23 = (uint64_t) _mm_extract_epi64(vidx0123, 1);
      const __m128i vl0   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx01)));
      const __m128i vl2 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx23)));
      const __m128i vl01 = _mm_insert_epi32(vl0, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx01 >> 32))), 1);
      const __m128i vl23 = _mm_insert_epi32(vl2, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx23 >> 32))), 1);
      const __m128i vl0123 = _mm_unpacklo_epi64(vl01, vl23);
      const uint64_t vidx45 = (uint64_t) _mm_cvtsi128_si64(vidx4567);
      const uint64_t vidx67 = (uint64_t) _mm_extract_epi64(vidx4567, 1);
      const __m128i vl4   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx45)));
      const __m128i vl6 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx67)));
      const __m128i vl45 = _mm_insert_epi32(vl4, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx45 >> 32))), 1);
      const __m128i vl67 = _mm_insert_epi32(vl6, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx67 >> 32))), 1);
      const __m128i vl4567 = _mm_unpacklo_epi64(vl45, vl67);
    #else  // !XNN_ARCH_X86_64
      const uint32_t vidx0 = (uint32_t) _mm_cvtsi128_si32(vidx0123);
      const uint32_t vidx1 = (uint32_t) _mm_extract_epi16(vidx0123, 2);
      const uint32_t vidx2 = (uint32_t) _mm_extract_epi16(vidx0123, 4);
      const uint32_t vidx3 = (uint32_t) _mm_extract_epi16(vidx0123, 6);
      const __m128i vl0   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx0)));
      const __m128i vl2 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx2)));
      const __m128i vl01 = _mm_insert_epi32(vl0, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx1)), 1);
      const __m128i vl23 = _mm_insert_epi32(vl2, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx3)), 1);
      const __m128i vl0123 = _mm_unpacklo_epi64(vl01, vl23);
      const uint32_t vidx4 = (uint32_t) _mm_cvtsi128_si32(vidx4567);
      const uint32_t vidx5 = (uint32_t) _mm_extract_epi16(vidx4567, 2);
      const uint32_t vidx6 = (uint32_t) _mm_extract_epi16(vidx4567, 4);
      const uint32_t vidx7 = (uint32_t) _mm_extract_epi16(vidx4567, 6);
      const __m128i vl4   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx4)));
      const __m128i vl6 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx6)));
      const __m128i vl45 = _mm_insert_epi32(vl4, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx5)), 1);
      const __m128i vl67 = _mm_insert_epi32(vl6, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + vidx7)), 1);
      const __m128i vl4567 = _mm_unpacklo_epi64(vl45, vl67);
    #endif  // XNN_ARCH_X86_64

    vn0123 = _mm_sub_ps(vn0123, vmagic_bias);
    __m128 vs0123 = _mm_castsi128_ps(_mm_add_epi32(vl0123, ven0123));
    vn4567 = _mm_sub_ps(vn4567, vmagic_bias);
    __m128 vs4567 = _mm_castsi128_ps(_mm_add_epi32(vl4567, ven4567));

    __m128 vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_hi), vz0123);
    __m128 vt4567 = _mm_add_ps(_mm_mul_ps(vn4567, vminus_ln2_hi), vz4567);

    vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_lo), vt0123);
    vt4567 = _mm_add_ps(_mm_mul_ps(vn4567, vminus_ln2_lo), vt4567);

    __m128 vp0123 = _mm_add_ps(_mm_mul_ps(vc3, vt0123), vc2);
    __m128 vp4567 = _mm_add_ps(_mm_mul_ps(vc3, vt4567), vc2);

    vp0123 = _mm_mul_ps(vp0123, vt0123);
    vp4567 = _mm_mul_ps(vp4567, vt4567);

    vt0123 = _mm_mul_ps(vt0123, vs0123);
    vs0123 = _mm_sub_ps(vs0123, vone);
    vt4567 = _mm_mul_ps(vt4567, vs4567);
    vs4567 = _mm_sub_ps(vs4567, vone);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vt0123);
    vp4567 = _mm_add_ps(_mm_mul_ps(vp4567, vt4567), vt4567);

    const __m128 ve0123 = _mm_mul_ps(_mm_add_ps(vp0123, vs0123), valpha);
    const __m128 ve4567 = _mm_mul_ps(_mm_add_ps(vp4567, vs4567), valpha);

    vx0123 = _mm_mul_ps(vx0123, vbeta);
    vx4567 = _mm_mul_ps(vx4567, vbeta);

    const __m128 vy0123 = _mm_blendv_ps(vx0123, ve0123, vx0123);
    const __m128 vy4567 = _mm_blendv_ps(vx4567, ve4567, vx4567);

    _mm_storeu_ps(y, vy0123);
    _mm_storeu_ps(y + 4, vy4567);
    y += 8;
  }
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    __m128 vx = _mm_loadu_ps(x);
    x += 4;

    const __m128 vz = _mm_max_ps(vsat_cutoff, _mm_mul_ps(vx, vprescale));

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);

    const __m128i ven = _mm_slli_epi32(_mm_castps_si128(vn), 19);
    const __m128i vidx = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn), vindex_mask), 2);
    #if XNN_ARCH_X86_64
      const uint64_t vidx_lo = (uint64_t) _mm_cvtsi128_si64(vidx);
      const uint64_t vidx_hi = (uint64_t) _mm_extract_epi64(vidx, 1);
      const __m128i vl_ll   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_lo)));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_hi)));
      const __m128i vl_lo = _mm_insert_epi32(vl_ll, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_lo >> 32))), 1);
      const __m128i vl_hi = _mm_insert_epi32(vl_hl, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_hi >> 32))), 1);
    #else  // !XNN_ARCH_X86_64
      const __m128i vl_ll = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_cvtsi128_si32(vidx))));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 4))));
      const __m128i vl_lo = _mm_insert_epi32(vl_ll, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 2))), 1);
      const __m128i vl_hi = _mm_insert_epi32(vl_hl, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 6))), 1);
    #endif  // XNN_ARCH_X86_64
    const __m128i vl = _mm_unpacklo_epi64(vl_lo, vl_hi);
    __m128 vs = _mm_castsi128_ps(_mm_add_epi32(vl, ven));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    __m128 vp = _mm_add_ps(_mm_mul_ps(vc3, vt), vc2);
    vp = _mm_mul_ps(vp, vt);

    vt = _mm_mul_ps(vt, vs);
    vs = _mm_sub_ps(vs, vone);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vt);
    const __m128 ve = _mm_mul_ps(_mm_add_ps(vp, vs), valpha);

    vx = _mm_mul_ps(vx, vbeta);
    const __m128 vy = _mm_blendv_ps(vx, ve, vx);

    _mm_storeu_ps(y, vy);
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    __m128 vx = _mm_loadu_ps(x);

    const __m128 vz = _mm_max_ps(vsat_cutoff, _mm_mul_ps(vx, vprescale));

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);

    const __m128i ven = _mm_slli_epi32(_mm_castps_si128(vn), 19);
    const __m128i vidx = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn), vindex_mask), 2);
    #if XNN_ARCH_X86_64
      const uint64_t vidx_lo = (uint64_t) _mm_cvtsi128_si64(vidx);
      const uint64_t vidx_hi = (uint64_t) _mm_extract_epi64(vidx, 1);
      const __m128i vl_ll   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_lo)));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_hi)));
      const __m128i vl_lo = _mm_insert_epi32(vl_ll, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_lo >> 32))), 1);
      const __m128i vl_hi = _mm_insert_epi32(vl_hl, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_hi >> 32))), 1);
    #else  // !XNN_ARCH_X86_64
      const __m128i vl_ll = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_cvtsi128_si32(vidx))));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 4))));
      const __m128i vl_lo = _mm_insert_epi32(vl_ll, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 2))), 1);
      const __m128i vl_hi = _mm_insert_epi32(vl_hl, *((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) _mm_extract_epi16(vidx, 6))), 1);
    #endif  // XNN_ARCH_X86_64
    const __m128i vl = _mm_unpacklo_epi64(vl_lo, vl_hi);
    __m128 vs = _mm_castsi128_ps(_mm_add_epi32(vl, ven));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    __m128 vp = _mm_add_ps(_mm_mul_ps(vc3, vt), vc2);
    vp = _mm_mul_ps(vp, vt);

    vt = _mm_mul_ps(vt, vs);
    vs = _mm_sub_ps(vs, vone);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vt);
    const __m128 ve = _mm_mul_ps(_mm_add_ps(vp, vs), valpha);

    vx = _mm_mul_ps(vx, vbeta);
    __m128 vy = _mm_blendv_ps(vx, ve, vx);

    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vy);
      vy = _mm_movehl_ps(vy, vy);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vy);
    }
  }
}