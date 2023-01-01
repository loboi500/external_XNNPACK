// Auto-generated file. Do not edit!
//   Template: src/f32-velu/wasmsimd-rr2-p6.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/vunary.h>
#include <xnnpack/common.h>


void xnn_f32_velu_ukernel__wasmsimd_x86_rr2_p6_x24(
    size_t n,
    const float* x,
    float* y,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN
{
  assert(n != 0);
  assert(n % sizeof(float) == 0);
  assert(x != NULL);
  assert(y != NULL);

  const v128_t vprescale = wasm_v32x4_load_splat(&params->scalar.prescale);
  const v128_t valpha = wasm_v32x4_load_splat(&params->scalar.alpha);
  const v128_t vbeta = wasm_v32x4_load_splat(&params->scalar.beta);

  const v128_t vsat_cutoff = wasm_f32x4_splat(-0x1.154246p+4f);
  const v128_t vmagic_bias = wasm_f32x4_splat(0x1.8000FEp23f);
  const v128_t vlog2e = wasm_f32x4_splat(0x1.715476p+0f);
  const v128_t vminus_ln2_hi = wasm_f32x4_splat(-0x1.62E440p-1f);
  const v128_t vminus_ln2_lo = wasm_f32x4_splat(0x1.0105C6p-21f);
  const v128_t vc6 = wasm_f32x4_splat(0x1.6b7338p-10f);
  const v128_t vc5 = wasm_f32x4_splat(0x1.12278Ep-7f);
  const v128_t vc4 = wasm_f32x4_splat(0x1.555716p-5f);
  const v128_t vc3 = wasm_f32x4_splat(0x1.5554B0p-3f);
  const v128_t vc2 = wasm_f32x4_splat(0x1.FFFFFEp-2f);
  const v128_t vone = wasm_f32x4_splat(1.0f);

  for (; n >= 24 * sizeof(float); n -= 24 * sizeof(float)) {
    v128_t vx0123 = wasm_v128_load(x);
    v128_t vx4567 = wasm_v128_load(x + 4);
    v128_t vx89AB = wasm_v128_load(x + 8);
    v128_t vxCDEF = wasm_v128_load(x + 12);
    v128_t vxGHIJ = wasm_v128_load(x + 16);
    v128_t vxKLMN = wasm_v128_load(x + 20);
    x += 24;

    const v128_t vz0123 = wasm_f32x4_mul(vx0123, vprescale);
    const v128_t vz4567 = wasm_f32x4_mul(vx4567, vprescale);
    const v128_t vz89AB = wasm_f32x4_mul(vx89AB, vprescale);
    const v128_t vzCDEF = wasm_f32x4_mul(vxCDEF, vprescale);
    const v128_t vzGHIJ = wasm_f32x4_mul(vxGHIJ, vprescale);
    const v128_t vzKLMN = wasm_f32x4_mul(vxKLMN, vprescale);

    v128_t vn0123 = wasm_f32x4_add(wasm_f32x4_mul(vz0123, vlog2e), vmagic_bias);
    v128_t vn4567 = wasm_f32x4_add(wasm_f32x4_mul(vz4567, vlog2e), vmagic_bias);
    v128_t vn89AB = wasm_f32x4_add(wasm_f32x4_mul(vz89AB, vlog2e), vmagic_bias);
    v128_t vnCDEF = wasm_f32x4_add(wasm_f32x4_mul(vzCDEF, vlog2e), vmagic_bias);
    v128_t vnGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vzGHIJ, vlog2e), vmagic_bias);
    v128_t vnKLMN = wasm_f32x4_add(wasm_f32x4_mul(vzKLMN, vlog2e), vmagic_bias);

    v128_t vs0123 = wasm_i32x4_shl(vn0123, 23);
    v128_t vs4567 = wasm_i32x4_shl(vn4567, 23);
    v128_t vs89AB = wasm_i32x4_shl(vn89AB, 23);
    v128_t vsCDEF = wasm_i32x4_shl(vnCDEF, 23);
    v128_t vsGHIJ = wasm_i32x4_shl(vnGHIJ, 23);
    v128_t vsKLMN = wasm_i32x4_shl(vnKLMN, 23);

    vn0123 = wasm_f32x4_sub(vn0123, vmagic_bias);
    vn4567 = wasm_f32x4_sub(vn4567, vmagic_bias);
    vn89AB = wasm_f32x4_sub(vn89AB, vmagic_bias);
    vnCDEF = wasm_f32x4_sub(vnCDEF, vmagic_bias);
    vnGHIJ = wasm_f32x4_sub(vnGHIJ, vmagic_bias);
    vnKLMN = wasm_f32x4_sub(vnKLMN, vmagic_bias);

    v128_t vt0123 = wasm_f32x4_add(wasm_f32x4_mul(vn0123, vminus_ln2_hi), vz0123);
    const v128_t vsatm0123 = wasm_f32x4_le(vz0123, vsat_cutoff);
    v128_t vt4567 = wasm_f32x4_add(wasm_f32x4_mul(vn4567, vminus_ln2_hi), vz4567);
    const v128_t vsatm4567 = wasm_f32x4_le(vz4567, vsat_cutoff);
    v128_t vt89AB = wasm_f32x4_add(wasm_f32x4_mul(vn89AB, vminus_ln2_hi), vz89AB);
    const v128_t vsatm89AB = wasm_f32x4_le(vz89AB, vsat_cutoff);
    v128_t vtCDEF = wasm_f32x4_add(wasm_f32x4_mul(vnCDEF, vminus_ln2_hi), vzCDEF);
    const v128_t vsatmCDEF = wasm_f32x4_le(vzCDEF, vsat_cutoff);
    v128_t vtGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vnGHIJ, vminus_ln2_hi), vzGHIJ);
    const v128_t vsatmGHIJ = wasm_f32x4_le(vzGHIJ, vsat_cutoff);
    v128_t vtKLMN = wasm_f32x4_add(wasm_f32x4_mul(vnKLMN, vminus_ln2_hi), vzKLMN);
    const v128_t vsatmKLMN = wasm_f32x4_le(vzKLMN, vsat_cutoff);

    vt0123 = wasm_f32x4_add(wasm_f32x4_mul(vn0123, vminus_ln2_lo), vt0123);
    vs0123 = wasm_v128_andnot(vs0123, vsatm0123);
    vt4567 = wasm_f32x4_add(wasm_f32x4_mul(vn4567, vminus_ln2_lo), vt4567);
    vs4567 = wasm_v128_andnot(vs4567, vsatm4567);
    vt89AB = wasm_f32x4_add(wasm_f32x4_mul(vn89AB, vminus_ln2_lo), vt89AB);
    vs89AB = wasm_v128_andnot(vs89AB, vsatm89AB);
    vtCDEF = wasm_f32x4_add(wasm_f32x4_mul(vnCDEF, vminus_ln2_lo), vtCDEF);
    vsCDEF = wasm_v128_andnot(vsCDEF, vsatmCDEF);
    vtGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vnGHIJ, vminus_ln2_lo), vtGHIJ);
    vsGHIJ = wasm_v128_andnot(vsGHIJ, vsatmGHIJ);
    vtKLMN = wasm_f32x4_add(wasm_f32x4_mul(vnKLMN, vminus_ln2_lo), vtKLMN);
    vsKLMN = wasm_v128_andnot(vsKLMN, vsatmKLMN);

    vt0123 = wasm_v128_andnot(vt0123, vsatm0123);
    v128_t vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vc6, vt0123), vc5);
    vt4567 = wasm_v128_andnot(vt4567, vsatm4567);
    v128_t vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vc6, vt4567), vc5);
    vt89AB = wasm_v128_andnot(vt89AB, vsatm89AB);
    v128_t vp89AB = wasm_f32x4_add(wasm_f32x4_mul(vc6, vt89AB), vc5);
    vtCDEF = wasm_v128_andnot(vtCDEF, vsatmCDEF);
    v128_t vpCDEF = wasm_f32x4_add(wasm_f32x4_mul(vc6, vtCDEF), vc5);
    vtGHIJ = wasm_v128_andnot(vtGHIJ, vsatmGHIJ);
    v128_t vpGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vc6, vtGHIJ), vc5);
    vtKLMN = wasm_v128_andnot(vtKLMN, vsatmKLMN);
    v128_t vpKLMN = wasm_f32x4_add(wasm_f32x4_mul(vc6, vtKLMN), vc5);

    vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vp0123, vt0123), vc4);
    vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vp4567, vt4567), vc4);
    vp89AB = wasm_f32x4_add(wasm_f32x4_mul(vp89AB, vt89AB), vc4);
    vpCDEF = wasm_f32x4_add(wasm_f32x4_mul(vpCDEF, vtCDEF), vc4);
    vpGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vpGHIJ, vtGHIJ), vc4);
    vpKLMN = wasm_f32x4_add(wasm_f32x4_mul(vpKLMN, vtKLMN), vc4);

    vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vp0123, vt0123), vc3);
    vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vp4567, vt4567), vc3);
    vp89AB = wasm_f32x4_add(wasm_f32x4_mul(vp89AB, vt89AB), vc3);
    vpCDEF = wasm_f32x4_add(wasm_f32x4_mul(vpCDEF, vtCDEF), vc3);
    vpGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vpGHIJ, vtGHIJ), vc3);
    vpKLMN = wasm_f32x4_add(wasm_f32x4_mul(vpKLMN, vtKLMN), vc3);

    vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vp0123, vt0123), vc2);
    vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vp4567, vt4567), vc2);
    vp89AB = wasm_f32x4_add(wasm_f32x4_mul(vp89AB, vt89AB), vc2);
    vpCDEF = wasm_f32x4_add(wasm_f32x4_mul(vpCDEF, vtCDEF), vc2);
    vpGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vpGHIJ, vtGHIJ), vc2);
    vpKLMN = wasm_f32x4_add(wasm_f32x4_mul(vpKLMN, vtKLMN), vc2);

    vp0123 = wasm_f32x4_mul(vp0123, vt0123);
    vp4567 = wasm_f32x4_mul(vp4567, vt4567);
    vp89AB = wasm_f32x4_mul(vp89AB, vt89AB);
    vpCDEF = wasm_f32x4_mul(vpCDEF, vtCDEF);
    vpGHIJ = wasm_f32x4_mul(vpGHIJ, vtGHIJ);
    vpKLMN = wasm_f32x4_mul(vpKLMN, vtKLMN);

    vt0123 = wasm_f32x4_mul(vt0123, vs0123);
    vs0123 = wasm_f32x4_sub(vs0123, vone);
    vt4567 = wasm_f32x4_mul(vt4567, vs4567);
    vs4567 = wasm_f32x4_sub(vs4567, vone);
    vt89AB = wasm_f32x4_mul(vt89AB, vs89AB);
    vs89AB = wasm_f32x4_sub(vs89AB, vone);
    vtCDEF = wasm_f32x4_mul(vtCDEF, vsCDEF);
    vsCDEF = wasm_f32x4_sub(vsCDEF, vone);
    vtGHIJ = wasm_f32x4_mul(vtGHIJ, vsGHIJ);
    vsGHIJ = wasm_f32x4_sub(vsGHIJ, vone);
    vtKLMN = wasm_f32x4_mul(vtKLMN, vsKLMN);
    vsKLMN = wasm_f32x4_sub(vsKLMN, vone);

    vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vp0123, vt0123), vt0123);
    vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vp4567, vt4567), vt4567);
    vp89AB = wasm_f32x4_add(wasm_f32x4_mul(vp89AB, vt89AB), vt89AB);
    vpCDEF = wasm_f32x4_add(wasm_f32x4_mul(vpCDEF, vtCDEF), vtCDEF);
    vpGHIJ = wasm_f32x4_add(wasm_f32x4_mul(vpGHIJ, vtGHIJ), vtGHIJ);
    vpKLMN = wasm_f32x4_add(wasm_f32x4_mul(vpKLMN, vtKLMN), vtKLMN);

    const v128_t ve0123 = wasm_f32x4_mul(wasm_f32x4_add(vp0123, vs0123), valpha);
    const v128_t ve4567 = wasm_f32x4_mul(wasm_f32x4_add(vp4567, vs4567), valpha);
    const v128_t ve89AB = wasm_f32x4_mul(wasm_f32x4_add(vp89AB, vs89AB), valpha);
    const v128_t veCDEF = wasm_f32x4_mul(wasm_f32x4_add(vpCDEF, vsCDEF), valpha);
    const v128_t veGHIJ = wasm_f32x4_mul(wasm_f32x4_add(vpGHIJ, vsGHIJ), valpha);
    const v128_t veKLMN = wasm_f32x4_mul(wasm_f32x4_add(vpKLMN, vsKLMN), valpha);

    const v128_t vsignm0123 = wasm_i32x4_shr(vx0123, 31);
    vx0123 = wasm_f32x4_mul(vx0123, vbeta);
    const v128_t vsignm4567 = wasm_i32x4_shr(vx4567, 31);
    vx4567 = wasm_f32x4_mul(vx4567, vbeta);
    const v128_t vsignm89AB = wasm_i32x4_shr(vx89AB, 31);
    vx89AB = wasm_f32x4_mul(vx89AB, vbeta);
    const v128_t vsignmCDEF = wasm_i32x4_shr(vxCDEF, 31);
    vxCDEF = wasm_f32x4_mul(vxCDEF, vbeta);
    const v128_t vsignmGHIJ = wasm_i32x4_shr(vxGHIJ, 31);
    vxGHIJ = wasm_f32x4_mul(vxGHIJ, vbeta);
    const v128_t vsignmKLMN = wasm_i32x4_shr(vxKLMN, 31);
    vxKLMN = wasm_f32x4_mul(vxKLMN, vbeta);

    const v128_t vy0123 = wasm_v128_bitselect(ve0123, vx0123, vsignm0123);
    const v128_t vy4567 = wasm_v128_bitselect(ve4567, vx4567, vsignm4567);
    const v128_t vy89AB = wasm_v128_bitselect(ve89AB, vx89AB, vsignm89AB);
    const v128_t vyCDEF = wasm_v128_bitselect(veCDEF, vxCDEF, vsignmCDEF);
    const v128_t vyGHIJ = wasm_v128_bitselect(veGHIJ, vxGHIJ, vsignmGHIJ);
    const v128_t vyKLMN = wasm_v128_bitselect(veKLMN, vxKLMN, vsignmKLMN);

    wasm_v128_store(y, vy0123);
    wasm_v128_store(y + 4, vy4567);
    wasm_v128_store(y + 8, vy89AB);
    wasm_v128_store(y + 12, vyCDEF);
    wasm_v128_store(y + 16, vyGHIJ);
    wasm_v128_store(y + 20, vyKLMN);
    y += 24;
  }
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    v128_t vx = wasm_v128_load(x);
    x += 4;

    const v128_t vz = wasm_f32x4_mul(vx, vprescale);

    v128_t vn = wasm_f32x4_add(wasm_f32x4_mul(vz, vlog2e), vmagic_bias);
    v128_t vs = wasm_i32x4_shl(vn, 23);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_hi), vz);
    const v128_t vsatm = wasm_f32x4_le(vz, vsat_cutoff);
    vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_lo), vt);
    vs = wasm_v128_andnot(vs, vsatm);
    vt = wasm_v128_andnot(vt, vsatm);

    v128_t vp = wasm_f32x4_add(wasm_f32x4_mul(vc6, vt), vc5);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc4);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc3);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc2);
    vp = wasm_f32x4_mul(vp, vt);

    vt = wasm_f32x4_mul(vt, vs);
    vs = wasm_f32x4_sub(vs, vone);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vt);
    const v128_t ve = wasm_f32x4_mul(wasm_f32x4_add(vp, vs), valpha);

    const v128_t vsignm = wasm_i32x4_shr(vx, 31);
    vx = wasm_f32x4_mul(vx, vbeta);
    const v128_t vy = wasm_v128_bitselect(ve, vx, vsignm);

    wasm_v128_store(y, vy);
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    v128_t vx = wasm_v128_load(x);

    const v128_t vz = wasm_f32x4_mul(vx, vprescale);

    v128_t vn = wasm_f32x4_add(wasm_f32x4_mul(vz, vlog2e), vmagic_bias);
    v128_t vs = wasm_i32x4_shl(vn, 23);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_hi), vz);
    const v128_t vsatm = wasm_f32x4_le(vz, vsat_cutoff);
    vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_lo), vt);
    vs = wasm_v128_andnot(vs, vsatm);
    vt = wasm_v128_andnot(vt, vsatm);

    v128_t vp = wasm_f32x4_add(wasm_f32x4_mul(vc6, vt), vc5);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc4);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc3);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vc2);
    vp = wasm_f32x4_mul(vp, vt);

    vt = wasm_f32x4_mul(vt, vs);
    vs = wasm_f32x4_sub(vs, vone);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vt);
    const v128_t ve = wasm_f32x4_mul(wasm_f32x4_add(vp, vs), valpha);

    const v128_t vsignm = wasm_i32x4_shr(vx, 31);
    vx = wasm_f32x4_mul(vx, vbeta);
    v128_t vy = wasm_v128_bitselect(ve, vx, vsignm);

    if (n & (2 * sizeof(float))) {
      *((double*) y) = wasm_f64x2_extract_lane(vy, 0);
      vy = wasm_v32x4_shuffle(vy, vy, 2, 3, 2, 3);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      *y = wasm_f32x4_extract_lane(vy, 0);
    }
  }
}