



#include <cstdint>
#include <immintrin.h>
#include "GMS_cdiv_vec_zmm16r4.h"





                  
                  
                   void cdivv_zmm16r4_unroll_10x_u(const float * __restrict  xre,
                                                  const float * __restrict  xim,
                                                  const float * __restrict  yre,
                                                  const float * __restrict  yim,
                                                  float * __restrict        zre,
                                                  float * __restrict        zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+159) < n; i += 160) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          _mm_prefetch((const char *)&xre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+144],_MM_HINT_T0);
                          zmm10  = _mm512_loadu_ps(&xre[i+96]); //a
                          zmm11  = _mm512_loadu_ps(&yim[i+96]); //d
                          zmm12  = _mm512_loadu_ps(&xim[i+96]); //b
                          zmm13  = _mm512_loadu_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_storeu_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_loadu_ps(&xre[i+112]); //a
                          zmm18  = _mm512_loadu_ps(&yim[i+112]); //d
                          zmm19  = _mm512_loadu_ps(&xim[i+112]); //b
                          zmm20  = _mm512_loadu_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_storeu_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_storeu_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));
                          zmm24  = _mm512_loadu_ps(&xre[i+128]); //a
                          zmm25  = _mm512_loadu_ps(&yim[i+128]); //d
                          zmm26  = _mm512_loadu_ps(&xim[i+128]); //b
                          zmm27  = _mm512_loadu_ps(&yre[i+128]); //c
                          zmm28  = _mm512_fmadd_ps(zmm24,zmm27,
                                                _mm512_mul_ps(zmm26,zmm25));
                          zmm29  = _mm512_fmsub_ps(zmm26,zmm27,
                                                _mm512_mul_ps(zmm24,zmm25));
                          zmm30  = _mm512_fmadd_ps(zmm27,zmm27,
                                                _mm512_mul_ps(zmm25,zmm25));
                          _mm512_storeu_ps(&zre[i+128], _mm512_div_ps(zmm28,zmm30));
                          _mm512_storeu_ps(&zim[i+128], _mm512_div_ps(zmm29,zmm30));
                          zmm31 = _mm512_loadu_ps(&xre[i+144]); //a
                          zmm0  = _mm512_loadu_ps(&yim[i+144]); //d
                          zmm1  = _mm512_loadu_ps(&xim[i+144]); //b
                          zmm2  = _mm512_loadu_ps(&yre[i+144]); //c
                          zmm3  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm4  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm5  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+144], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+144], _mm512_div_ps(zmm8,zmm9));
                      }

                      for(; (i+127) < n; i += 128) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          zmm10  = _mm512_loadu_ps(&xre[i+96]); //a
                          zmm11  = _mm512_loadu_ps(&yim[i+96]); //d
                          zmm12  = _mm512_loadu_ps(&xim[i+96]); //b
                          zmm13  = _mm512_loadu_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_storeu_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_loadu_ps(&xre[i+112]); //a
                          zmm18  = _mm512_loadu_ps(&yim[i+112]); //d
                          zmm19  = _mm512_loadu_ps(&xim[i+112]); //b
                          zmm20  = _mm512_loadu_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_storeu_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_storeu_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));

                      }

                      for(; (i+95) < n; i += 96) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));

                      }

                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));

                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }

              ///////////////////////////////////////////////////////////////////////////////////
              
                  
                   void cdivv_zmm16r4_unroll_10x_a(const float * __restrict __ATTR_ALIGN__(64) xre,
                                                  const float * __restrict __ATTR_ALIGN__(64) xim,
                                                  const float * __restrict __ATTR_ALIGN__(64) yre,
                                                  const float * __restrict __ATTR_ALIGN__(64) yim,
                                                  float * __restrict       __ATTR_ALIGN__(64) zre,
                                                  float * __restrict       __ATTR_ALIGN__(64) zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+159) < n; i += 160) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          _mm_prefetch((const char *)&xre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+144],_MM_HINT_T0);
                          zmm10  = _mm512_load_ps(&xre[i+96]); //a
                          zmm11  = _mm512_load_ps(&yim[i+96]); //d
                          zmm12  = _mm512_load_ps(&xim[i+96]); //b
                          zmm13  = _mm512_load_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_store_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_store_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_load_ps(&xre[i+112]); //a
                          zmm18  = _mm512_load_ps(&yim[i+112]); //d
                          zmm19  = _mm512_load_ps(&xim[i+112]); //b
                          zmm20  = _mm512_load_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_store_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_store_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));
                          zmm24  = _mm512_load_ps(&xre[i+128]); //a
                          zmm25  = _mm512_load_ps(&yim[i+128]); //d
                          zmm26  = _mm512_load_ps(&xim[i+128]); //b
                          zmm27  = _mm512_load_ps(&yre[i+128]); //c
                          zmm28  = _mm512_fmadd_ps(zmm24,zmm27,
                                                _mm512_mul_ps(zmm26,zmm25));
                          zmm29  = _mm512_fmsub_ps(zmm26,zmm27,
                                                _mm512_mul_ps(zmm24,zmm25));
                          zmm30  = _mm512_fmadd_ps(zmm27,zmm27,
                                                _mm512_mul_ps(zmm25,zmm25));
                          _mm512_store_ps(&zre[i+128], _mm512_div_ps(zmm28,zmm30));
                          _mm512_store_ps(&zim[i+128], _mm512_div_ps(zmm29,zmm30));
                          zmm31 = _mm512_load_ps(&xre[i+144]); //a
                          zmm0  = _mm512_load_ps(&yim[i+144]); //d
                          zmm1  = _mm512_load_ps(&xim[i+144]); //b
                          zmm2  = _mm512_load_ps(&yre[i+144]); //c
                          zmm3  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm4  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm5  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+144], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+144], _mm512_div_ps(zmm8,zmm9));
                      }

                      for(; (i+127) < n; i += 128) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          zmm10  = _mm512_load_ps(&xre[i+96]); //a
                          zmm11  = _mm512_load_ps(&yim[i+96]); //d
                          zmm12  = _mm512_load_ps(&xim[i+96]); //b
                          zmm13  = _mm512_load_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_store_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_store_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_load_ps(&xre[i+112]); //a
                          zmm18  = _mm512_load_ps(&yim[i+112]); //d
                          zmm19  = _mm512_load_ps(&xim[i+112]); //b
                          zmm20  = _mm512_load_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_store_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_store_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));

                      }

                      for(; (i+95) < n; i += 96) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                      }

                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));

                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }

                 /////////////////////////////////////////////////////////////////////////////
                  
                   void cdivv_zmm16r4_unroll_8x_u(const float * __restrict  xre,
                                                  const float * __restrict  xim,
                                                  const float * __restrict  yre,
                                                  const float * __restrict  yim,
                                                  float * __restrict        zre,
                                                  float * __restrict        zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+127) < n; i += 128) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          _mm_prefetch((const char *)&xre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+144],_MM_HINT_T0);
                          zmm10  = _mm512_loadu_ps(&xre[i+96]); //a
                          zmm11  = _mm512_loadu_ps(&yim[i+96]); //d
                          zmm12  = _mm512_loadu_ps(&xim[i+96]); //b
                          zmm13  = _mm512_loadu_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_storeu_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_loadu_ps(&xre[i+112]); //a
                          zmm18  = _mm512_loadu_ps(&yim[i+112]); //d
                          zmm19  = _mm512_loadu_ps(&xim[i+112]); //b
                          zmm20  = _mm512_loadu_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_storeu_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_storeu_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));
                      }

                     
                      for(; (i+95) < n; i += 96) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));

                      }

                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));

                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }

              ///////////////////////////////////////////////////////////////////////////////////

                 
                   void cdivv_zmm16r4_unroll_8x_a(const float * __restrict __ATTR_ALIGN__(64) xre,
                                                  const float * __restrict __ATTR_ALIGN__(64) xim,
                                                  const float * __restrict __ATTR_ALIGN__(64) yre,
                                                  const float * __restrict __ATTR_ALIGN__(64) yim,
                                                  float * __restrict       __ATTR_ALIGN__(64) zre,
                                                  float * __restrict       __ATTR_ALIGN__(64) zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+127) < n; i += 128) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                          _mm_prefetch((const char *)&xre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+144],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+144],_MM_HINT_T0);
                          zmm10  = _mm512_load_ps(&xre[i+96]); //a
                          zmm11  = _mm512_load_ps(&yim[i+96]); //d
                          zmm12  = _mm512_load_ps(&xim[i+96]); //b
                          zmm13  = _mm512_load_ps(&yre[i+96]); //c
                          zmm14  = _mm512_fmadd_ps(zmm10,zmm13,
                                                _mm512_mul_ps(zmm12,zmm11));
                          zmm15  = _mm512_fmsub_ps(zmm12,zmm13,
                                                _mm512_mul_ps(zmm10,zmm11));
                          zmm16  = _mm512_fmadd_ps(zmm13,zmm13,
                                                _mm512_mul_ps(zmm11,zmm11));
                          _mm512_store_ps(&zre[i+96], _mm512_div_ps(zmm14,zmm16));
                          _mm512_store_ps(&zim[i+96], _mm512_div_ps(zmm15,zmm16));
                          zmm17  = _mm512_load_ps(&xre[i+112]); //a
                          zmm18  = _mm512_load_ps(&yim[i+112]); //d
                          zmm19  = _mm512_load_ps(&xim[i+112]); //b
                          zmm20  = _mm512_load_ps(&yre[i+112]); //c
                          zmm21  = _mm512_fmadd_ps(zmm17,zmm20,
                                                _mm512_mul_ps(zmm19,zmm18));
                          zmm22  = _mm512_fmsub_ps(zmm19,zmm20,
                                                _mm512_mul_ps(zmm17,zmm18));
                          zmm23  = _mm512_fmadd_ps(zmm20,zmm20,
                                                _mm512_mul_ps(zmm18,zmm18));
                          _mm512_store_ps(&zre[i+112], _mm512_div_ps(zmm21,zmm23));
                          _mm512_store_ps(&zim[i+112], _mm512_div_ps(zmm22,zmm23));
                     }

                     

                      for(; (i+95) < n; i += 96) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                      }

                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));

                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }
 
                ////////////////////////////////////////////////////////////////////////// 
                     
                  
                   void cdivv_zmm16r4_unroll_6x_a(const float * __restrict __ATTR_ALIGN__(64) xre,
                                                  const float * __restrict __ATTR_ALIGN__(64) xim,
                                                  const float * __restrict __ATTR_ALIGN__(64) yre,
                                                  const float * __restrict __ATTR_ALIGN__(64) yim,
                                                  float * __restrict       __ATTR_ALIGN__(64) zre,
                                                  float * __restrict       __ATTR_ALIGN__(64) zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+95) < n; i += 96) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_load_ps(&xre[i+64]); //a
                          zmm29  = _mm512_load_ps(&yim[i+64]); //d
                          zmm30  = _mm512_load_ps(&xim[i+64]); //b
                          zmm31  = _mm512_load_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_load_ps(&xre[i+80]); //a
                          zmm4  = _mm512_load_ps(&yim[i+80]); //d
                          zmm5  = _mm512_load_ps(&xim[i+80]); //b
                          zmm6  = _mm512_load_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                     }

                       

                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_load_ps(&xre[i+32]); //a
                          zmm15  = _mm512_load_ps(&yim[i+32]); //d
                          zmm16  = _mm512_load_ps(&xim[i+32]); //b
                          zmm17  = _mm512_load_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_load_ps(&xre[i+48]); //a
                          zmm22  = _mm512_load_ps(&yim[i+48]); //d
                          zmm23  = _mm512_load_ps(&xim[i+48]); //b
                          zmm24  = _mm512_load_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));

                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_load_ps(&xre[i+16]); //a
                          zmm8  = _mm512_load_ps(&yim[i+16]); //d
                          zmm9  = _mm512_load_ps(&xim[i+16]); //b
                          zmm10 = _mm512_load_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_load_ps(&xre[i+0]); //a
                          zmm1  = _mm512_load_ps(&yim[i+0]); //d
                          zmm2  = _mm512_load_ps(&xim[i+0]); //b
                          zmm3  = _mm512_load_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }
 
                /////////////////////////////////////////////////////////////////////

                  
                   void cdivv_zmm16r4_unroll_6x_u(const float * __restrict  xre,
                                                  const float * __restrict  xim,
                                                  const float * __restrict  yre,
                                                  const float * __restrict  yim,
                                                  float * __restrict        zre,
                                                  float * __restrict        zim,
                                                  const int32_t n) {
                     
                      if(__builtin_expect(0==n,0)) {return;}
                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      register __m512 zmm4,zmm5,zmm6,zmm7;
                      register __m512 zmm8,zmm9,zmm10,zmm11;
                      register __m512 zmm12,zmm13,zmm14,zmm15;
                      register __m512 zmm16,zmm17,zmm18,zmm19;
                      register __m512 zmm20,zmm21,zmm22,zmm23;
                      register __m512 zmm24,zmm25,zmm26,zmm27;
                      register __m512 zmm28,zmm29,zmm30,zmm31;
                      int32_t i;
                      for(i = 0; (i+95) < n; i += 96) {
                          _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+48],_MM_HINT_T0);
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yre[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                          _mm_prefetch((const char *)&yim[i+96],_MM_HINT_T0);
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                          zmm28  = _mm512_loadu_ps(&xre[i+64]); //a
                          zmm29  = _mm512_loadu_ps(&yim[i+64]); //d
                          zmm30  = _mm512_loadu_ps(&xim[i+64]); //b
                          zmm31  = _mm512_loadu_ps(&yre[i+64]); //c
                          zmm0  = _mm512_fmadd_ps(zmm28,zmm31,
                                                _mm512_mul_ps(zmm30,zmm29));
                          zmm1  = _mm512_fmsub_ps(zmm30,zmm31,
                                                _mm512_mul_ps(zmm28,zmm29));
                          zmm2  = _mm512_fmadd_ps(zmm31,zmm31,
                                                _mm512_mul_ps(zmm29,zmm29));
                          _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm0,zmm2));
                          _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm1,zmm2));
                          zmm3  = _mm512_loadu_ps(&xre[i+80]); //a
                          zmm4  = _mm512_loadu_ps(&yim[i+80]); //d
                          zmm5  = _mm512_loadu_ps(&xim[i+80]); //b
                          zmm6  = _mm512_loadu_ps(&yre[i+80]); //c
                          zmm7  = _mm512_fmadd_ps(zmm3,zmm6,
                                                _mm512_mul_ps(zmm5,zmm4));
                          zmm8  = _mm512_fmsub_ps(zmm5,zmm6,
                                                _mm512_mul_ps(zmm3,zmm4));
                          zmm9  = _mm512_fmadd_ps(zmm6,zmm6,
                                                _mm512_mul_ps(zmm4,zmm4));
                          _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm7,zmm9));
                          _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm8,zmm9));
                      }

                                         
                      for(; (i+63) < n; i += 64) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));
                          zmm14  = _mm512_loadu_ps(&xre[i+32]); //a
                          zmm15  = _mm512_loadu_ps(&yim[i+32]); //d
                          zmm16  = _mm512_loadu_ps(&xim[i+32]); //b
                          zmm17  = _mm512_loadu_ps(&yre[i+32]); //c
                          zmm18  = _mm512_fmadd_ps(zmm14,zmm17,
                                                _mm512_mul_ps(zmm16,zmm15));
                          zmm19  = _mm512_fmsub_ps(zmm16,zmm17,
                                                _mm512_mul_ps(zmm14,zmm15));
                          zmm20  = _mm512_fmadd_ps(zmm17,zmm17,
                                                _mm512_mul_ps(zmm15,zmm15));
                          _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm18,zmm20));
                          _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm19,zmm20));
                          zmm21  = _mm512_loadu_ps(&xre[i+48]); //a
                          zmm22  = _mm512_loadu_ps(&yim[i+48]); //d
                          zmm23  = _mm512_loadu_ps(&xim[i+48]); //b
                          zmm24  = _mm512_loadu_ps(&yre[i+48]); //c
                          zmm25  = _mm512_fmadd_ps(zmm21,zmm24,
                                                _mm512_mul_ps(zmm23,zmm22));
                          zmm26  = _mm512_fmsub_ps(zmm23,zmm24,
                                                _mm512_mul_ps(zmm21,zmm24));
                          zmm27  = _mm512_fmadd_ps(zmm24,zmm24,
                                                _mm512_mul_ps(zmm22,zmm22));
                          _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm25,zmm27));
                          _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm26,zmm27));
                      }

                      for(; (i+31) < n; i += 32) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                          zmm7  = _mm512_loadu_ps(&xre[i+16]); //a
                          zmm8  = _mm512_loadu_ps(&yim[i+16]); //d
                          zmm9  = _mm512_loadu_ps(&xim[i+16]); //b
                          zmm10 = _mm512_loadu_ps(&yre[i+16]); //c
                          zmm11 = _mm512_fmadd_ps(zmm7,zmm10,
                                                _mm512_mul_ps(zmm9,zmm8));
                          zmm12 = _mm512_fmsub_ps(zmm9,zmm10,
                                                _mm512_mul_ps(zmm7,zmm8));
                          zmm13 = _mm512_fmadd_ps(zmm10,zmm10,
                                                _mm512_mul_ps(zmm8,zmm8));
                          _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm11,zmm13));
                          _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm12,zmm13));

                      }

                     for(; (i+15) < n; i += 16) {
                          zmm0  = _mm512_loadu_ps(&xre[i+0]); //a
                          zmm1  = _mm512_loadu_ps(&yim[i+0]); //d
                          zmm2  = _mm512_loadu_ps(&xim[i+0]); //b
                          zmm3  = _mm512_loadu_ps(&yre[i+0]); //c
                          zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                 _mm512_mul_ps(zmm2,zmm1));
                          zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                          zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                          _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm4,zmm6));
                          _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm5,zmm6));
                     }

                    for(; (i+0) < n; i += 1) {
                        const float tre = (xre[i] * yim[i]) + (xim[i] * yim[i]);
		        const float tim = (xim[i] * yre[i]) - (xre[i] * yim[i]);
		        const float den = (yre[i] * yre[i]) + (yim[i] * yim[i]);
		        zre[i] = tre / den;
		        zim[i] = tim / den;
                    }
              }
         
                     
                  
                   void cdiv_zmm16r4_unroll_10x_u(const float * __restrict xre,
                                                  const float * __restrict xim, 
                                                  const __m512             vs,
                                                  float  * __restrict zre,
                                                  float  * __restrict zim,
                                                  const int32_t n) {

                         if(__builtin_expect(0==n,0)) { return;}
                          register __m512 zmm0,zmm1,zmm2,zmm3;
                          register __m512 zmm4,zmm5,zmm6,zmm7;
                          register __m512 zmm8,zmm9,zmm10,zmm11;
                          register __m512 zmm12,zmm13,zmm14,zmm15;
                          register __m512 zmm16,zmm17,zmm18,zmm19;
                          register  __m512 zmmx    = vs;
                          const float * __restrict pzmm =  (const float*)&vs[0];
                         for(i = 0; (i+159) < n; i += 160) {
                              _mm_prefetch((const char *)&xre[i+32],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+32],_MM_HINT_T0);
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              _mm_prefetch((const char *)&xre[i+64],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+64],_MM_HINT_T0);
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_loadu_ps(&xre[i+64]);
                              _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_loadu_ps(&xim[i+64]);
                              _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                              zmm10 = _mm512_loadu_ps(&xre[i+80]);
                              _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                              zmm11 = _mm512_loadu_ps(&xim[i+80]);
                              _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                              zmm12 = _mm512_loadu_ps(&xre[i+96]);
                              _mm512_storeu_ps(&zre[i+96], _mm512_div_ps(zmm12,zmmx));
                              zmm13 = _mm512_loadu_ps(&xim[i+96]);
                              _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm13,zmmx));
                              _mm_prefetch((const char *)&xre[i+128],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+128],_MM_HINT_T0);
                              zmm14 = _mm512_loadu_ps(&xre[i+112]);
                              _mm512_storeu_ps(&zre[i+112], _mm512_div_ps(zmm14,zmmx));
                              zmm15 = _mm512_loadu_ps(&xim[i+112]);
                              _mm512_storeu_ps(&zim[i+112], _mm512_div_ps(zmm15,zmmx));
                              zmm16 = _mm512_loadu_ps(&xre[i+128]);
                              _mm512_storeu_ps(&zre[i+128], _mm512_div_ps(zmm16,zmmx));
                              zmm17 = _mm512_loadu_ps(&xim[i+128]);
                              _mm512_storeu_ps(&zim[i+128], _mm512_div_ps(zmm17,zmmx));
                              zmm18 = _mm512_loadu_ps(&xre[i+144]);
                              _mm512_storeu_ps(&zre[i+144], _mm512_div_ps(zmm18,zmmx));
                              zmm19 = _mm512_loadu_ps(&xim[i+144]);
                              _mm512_storeu_ps(&zim[i+144], _mm512_div_ps(zmm19,zmmx));
                        }

                       for(; (i+127) < n; i += 128) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_loadu_ps(&xre[i+64]);
                              _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_loadu_ps(&xim[i+64]);
                              _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              zmm10 = _mm512_loadu_ps(&xre[i+80]);
                              _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                              zmm11 = _mm512_loadu_ps(&xim[i+80]);
                              _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                              zmm12 = _mm512_loadu_ps(&xre[i+96]);
                              _mm512_storeu_ps(&zre[i+96], _mm512_div_ps(zmm12,zmmx));
                              zmm13 = _mm512_loadu_ps(&xim[i+96]);
                              _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm13,zmmx));
                              zmm14 = _mm512_loadu_ps(&xre[i+112]);
                              _mm512_storeu_ps(&zre[i+112], _mm512_div_ps(zmm14,zmmx));
                              zmm15 = _mm512_loadu_ps(&xim[i+112]);
                              _mm512_storeu_ps(&zim[i+112], _mm512_div_ps(zmm15,zmmx));
                       }

                       for(; (i+79) < n; i += 80) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_loadu_ps(&xre[i+64]);
                              _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_loadu_ps(&xim[i+64]);
                              _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                       }

                      for(; (i+63) < n; i += 64) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx)); 
                      }

                     for(; (i+31) < n; i += 32) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                     }

                    for(; (i+15) < n; i += 16) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));    
                    }

                    for(; (i+0) < n; i += 1) {
                          const float s = pzmm[i];
                          zre[i] = xre[i] / s;
                          zim[i] = zim[i] / s;
                    }

                 }
 

                  
                   void cdiv_zmm16r4_unroll_10x_a(const float * __restrict __ATTR_ALIGN__(64) xre,
                                                  const float * __restrict __ATTR_ALIGN__(64) xim, 
                                                  const __m512             vs,
                                                  float  * __restrict __ATTR_ALIGN__(64) zre,
                                                  float  * __restrict __ATTR_ALIGN__(64) zim,
                                                  const int32_t n) {

                         if(__builtin_expect(0==n,0)) { return;}
                          register __m512 zmm0,zmm1,zmm2,zmm3;
                          register __m512 zmm4,zmm5,zmm6,zmm7;
                          register __m512 zmm8,zmm9,zmm10,zmm11;
                          register __m512 zmm12,zmm13,zmm14,zmm15;
                          register __m512 zmm16,zmm17,zmm18,zmm19;
                          register  __m512 zmmx    = vs;
                          const float * __restrict pzmm =  (const float*)&vs[0];
                          for(i = 0; (i+159) < n; i += 160) {
                              _mm_prefetch((const char *)&xre[i+32],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+32],_MM_HINT_T0);
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              _mm_prefetch((const char *)&xre[i+64],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+64],_MM_HINT_T0);
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                               zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_load_ps(&xre[i+64]);
                              _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_load_ps(&xim[i+64]);
                              _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                               zmm10 = _mm512_load_ps(&xre[i+80]);
                              _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                              zmm11 = _mm512_load_ps(&xim[i+80]);
                              _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                               zmm12 = _mm512_load_ps(&xre[i+96]);
                              _mm512_store_ps(&zre[i+96], _mm512_div_ps(zmm12,zmmx));
                              zmm13 = _mm512_load_ps(&xim[i+96]);
                              _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm13,zmmx));
                              _mm_prefetch((const char *)&xre[i+128],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+128],_MM_HINT_T0);
                              zmm14 = _mm512_load_ps(&xre[i+112]);
                              _mm512_store_ps(&zre[i+112], _mm512_div_ps(zmm14,zmmx));
                              zmm15 = _mm512_load_ps(&xim[i+112]);
                              _mm512_store_ps(&zim[i+112], _mm512_div_ps(zmm15,zmmx));
                               zmm16 = _mm512_load_ps(&xre[i+128]);
                              _mm512_store_ps(&zre[i+128], _mm512_div_ps(zmm16,zmmx));
                               zmm17 = _mm512_load_ps(&xim[i+128]);
                              _mm512_store_ps(&zim[i+128], _mm512_div_ps(zmm17,zmmx));
                               zmm18 = _mm512_load_ps(&xre[i+144]);
                              _mm512_store_ps(&zre[i+144], _mm512_div_ps(zmm18,zmmx));
                               zmm19 = _mm512_load_ps(&xim[i+144]);
                              _mm512_store_ps(&zim[i+144], _mm512_div_ps(zmm19,zmmx));
                        }

                       for(; (i+127) < n; i += 128) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                               zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_load_ps(&xre[i+64]);
                              _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_load_ps(&xim[i+64]);
                              _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              zmm10 = _mm512_load_ps(&xre[i+80]);
                              _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                              zmm11 = _mm512_load_ps(&xim[i+80]);
                              _mm512_store_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                               zmm12 = _mm512_load_ps(&xre[i+96]);
                              _mm512_store_ps(&zre[i+96], _mm512_div_ps(zmm12,zmmx));
                              zmm13 = _mm512_load_ps(&xim[i+96]);
                              _mm512_storeu_ps(&zim[i+96], _mm512_div_ps(zmm13,zmmx));
                              zmm14 = _mm512_load_ps(&xre[i+112]);
                              _mm512_store_ps(&zre[i+112], _mm512_div_ps(zmm14,zmmx));
                              zmm15 = _mm512_load_ps(&xim[i+112]);
                              _mm512_store_ps(&zim[i+112], _mm512_div_ps(zmm15,zmmx));
                       }

                       for(; (i+79) < n; i += 80) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                               zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_load_ps(&xre[i+64]);
                              _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_load_ps(&xim[i+64]);
                              _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                       }

                      for(; (i+63) < n; i += 64) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                               zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                      }

                     for(; (i+31) < n; i += 32) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                     }

                    for(; (i+15) < n; i += 16) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                    }

                    for(; (i+0) < n; i += 1) {
                          const float s = pzmm[i];
                          zre[i] = xre[i] / s;
                          zim[i] = zim[i] / s;
                    }

                 }


                  
                   void cdiv_zmm16r4_unroll_6x_u(const float * __restrict xre,
                                                  const float * __restrict xim, 
                                                  const __m512             vs,
                                                  float  * __restrict zre,
                                                  float  * __restrict zim,
                                                  const int32_t n) {

                         if(__builtin_expect(0==n,0)) { return;}
                          register __m512 zmm0,zmm1,zmm2,zmm3;
                          register __m512 zmm4,zmm5,zmm6,zmm7;
                          register __m512 zmm8,zmm9,zmm10,zmm11;
                          register  __m512 zmmx    = vs;
                          const float * __restrict pzmm =  (const float*)&vs[0];
                          for(i = 0; (i+95) < n; i += 96) {
                              _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                               zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                               zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                               zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                              zmm8 = _mm512_loadu_ps(&xre[i+64]);
                              _mm512_storeu_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                              zmm9 = _mm512_loadu_ps(&xim[i+64]);
                              _mm512_storeu_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              zmm10 = _mm512_loadu_ps(&xre[i+80]);
                              _mm512_storeu_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                              zmm11 = _mm512_loadu_ps(&xim[i+80]);
                              _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                            
                        }

                       for(; (i+63) < n; i += 64) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                               zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                               zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_loadu_ps(&xre[i+32]);
                              _mm512_storeu_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                               zmm5 = _mm512_loadu_ps(&xim[i+32]);
                              _mm512_storeu_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_loadu_ps(&xre[i+48]);
                              _mm512_storeu_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_loadu_ps(&xim[i+48]);
                              _mm512_storeu_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                      }

                     for(; (i+31) < n; i += 32) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                               zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                               zmm2 = _mm512_loadu_ps(&xre[i+16]);
                              _mm512_storeu_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                              zmm3 = _mm512_loadu_ps(&xim[i+16]);
                              _mm512_storeu_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));  
                     }

                    for(; (i+15) < n; i += 16) {
                              zmm0 = _mm512_loadu_ps(&xre[i+0]);
                              _mm512_storeu_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                               zmm1 = _mm512_loadu_ps(&xim[i+0]);
                              _mm512_storeu_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                    }

                    for(; (i+0) < n; i += 1) {
                          const float s = pzmm[i];
                          zre[i] = xre[i] / s;
                          zim[i] = zim[i] / s;
                    }

                 }


                  
                   void cdiv_zmm16r4_unroll_6x_a( const float * __restrict __ATTR_ALIGN__(64) xre,
                                                  const float * __restrict __ATTR_ALIGN__(64) xim, 
                                                  const __m512             vs,
                                                  float  * __restrict __ATTR_ALIGN__(64) zre,
                                                  float  * __restrict __ATTR_ALIGN__(64) zim,
                                                  const int32_t n) {

                         if(__builtin_expect(0==n,0)) { return;}
                          register __m512 zmm0,zmm1,zmm2,zmm3;
                          register __m512 zmm4,zmm5,zmm6,zmm7;
                          register __m512 zmm8,zmm9,zmm10,zmm11;
                          register  __m512 zmmx    = vs;
                          const float * __restrict pzmm =  (const float*)&vs[0];
                          for(i = 0; (i+95) < n; i += 96) {
                              _mm_prefetch((const char *)&xre[i+48],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+48],_MM_HINT_T0);
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                               zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              _mm_prefetch((const char *)&xre[i+96],_MM_HINT_T0);
                              _mm_prefetch((const char *)&xim[i+96],_MM_HINT_T0);
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                               zmm8 = _mm512_load_ps(&xre[i+64]);
                              _mm512_store_ps(&zre[i+64], _mm512_div_ps(zmm8,zmmx));
                               zmm9 = _mm512_load_ps(&xim[i+64]);
                              _mm512_store_ps(&zim[i+64], _mm512_div_ps(zmm9,zmmx));
                              zmm10 = _mm512_load_ps(&xre[i+80]);
                              _mm512_store_ps(&zre[i+80], _mm512_div_ps(zmm10,zmmx));
                               zmm11 = _mm512_load_ps(&xim[i+80]);
                              _mm512_storeu_ps(&zim[i+80], _mm512_div_ps(zmm11,zmmx));
                        }

                        for(; (i+63) < n; i += 64) {
                              zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                              zmm1 = _mm512_load_ps(&xim[i+0]);
                              _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                              zmm2 = _mm512_load_ps(&xre[i+16]);
                              _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                               zmm3 = _mm512_load_ps(&xim[i+16]);
                              _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                              zmm4 = _mm512_load_ps(&xre[i+32]);
                              _mm512_store_ps(&zre[i+32], _mm512_div_ps(zmm4,zmmx));
                              zmm5 = _mm512_load_ps(&xim[i+32]);
                              _mm512_store_ps(&zim[i+32], _mm512_div_ps(zmm5,zmmx));
                              zmm6 = _mm512_load_ps(&xre[i+48]);
                              _mm512_store_ps(&zre[i+48], _mm512_div_ps(zmm6,zmmx));
                              zmm7 = _mm512_load_ps(&xim[i+48]);
                              _mm512_store_ps(&zim[i+48], _mm512_div_ps(zmm7,zmmx));
                      }

                     for(; (i+31) < n; i += 32) {
                             zmm0 = _mm512_load_ps(&xre[i+0]);
                              _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                             zmm1 = _mm512_load_ps(&xim[i+0]);
                             _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                             zmm2 = _mm512_load_ps(&xre[i+16]);
                             _mm512_store_ps(&zre[i+16], _mm512_div_ps(zmm2,zmmx));
                             zmm3 = _mm512_load_ps(&xim[i+16]);
                             _mm512_store_ps(&zim[i+16], _mm512_div_ps(zmm3,zmmx));
                     }

                    for(; (i+15) < n; i += 16) {
                             zmm0 = _mm512_load_ps(&xre[i+0]);
                             _mm512_store_ps(&zre[i+0], _mm512_div_ps(zmm0,zmmx));
                             zmm1 = _mm512_load_ps(&xim[i+0]);
                             _mm512_store_ps(&zim[i+0], _mm512_div_ps(zmm1,zmmx));
                    }

                    for(; (i+0) < n; i += 1) {
                          const float s = pzmm[i];
                          zre[i] = xre[i] / s;
                          zim[i] = zim[i] / s;
                    }

                 }




       















