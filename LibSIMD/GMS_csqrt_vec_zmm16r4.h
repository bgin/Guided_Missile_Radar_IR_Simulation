

#ifndef __GMS_CSQRT_VEC_ZMM16R4_H__
#define __GMS_CSQRT_VEC_ZMM16R4_H__ 271220221650




    const unsigned int GMS_CSQRT_VEC_ZMM16R4_MAJOR = 1U;
    const unsigned int GMS_CSQRT_VEC_ZMM16R4_MINOR = 0U;
    const unsigned int GMS_CSQRT_VEC_ZMM16R4_MICRO = 0U;
    const unsigned int GMS_CSQRT_VEC_ZMM16R4_FULLVER =
      1000U*GMS_CSQRT_VEC_ZMM16R4_MAJOR+
      100U*GMS_CSQRT_VEC_ZMM16R4_MINOR+
      10U*GMS_CSQRT_VEC_ZMM16R4_MICRO;
    const char * const GMS_CSQRT_VEC_ZMM16R4_CREATION_DATE = "27-12-2022 16:50  +00200 (TUE 27 DEC 2022 GMT+2)";
    const char * const GMS_CSQRT_VEC_ZMM16R4_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const GMS_CSQRT_VEC_ZMM16R4_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const GMS_CSQRT_VEC_ZMM16R4_DESCRIPTION   = "AVX512 optimized decomposed complex vector sqrt operations."



#include <cstdint>

 void csqrtv_zmm16r4_unroll_10x_u(const float * __restrict xre,
                                  const float * __restrict yim,
                                  float * __restrict wrkc,
                                  float * __restrict csqr,
                                  float * __restrict csqi,
                                  const int32_t n)

                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));


void csqrtv_zmm16r4_unroll_10x_a(const float * __restrict  xre,
                                 const float * __restrict yim,
                                 float * __restrict  wrkc,
                                 float * __restrict  csqr,
                                 float * __restrict  csqi,
                                 const int32_t n)

                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));

 void csqrtv_zmm16r4_unroll_8x_u(const float * __restrict xre,
                                 const float * __restrict yim,
                                 float * __restrict wrkc,
                                 float * __restrict csqr,
                                 float * __restrict csqi,
                                 const int32_t n) 

                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));


void csqrtv_zmm16r4_unroll_8x_a(const float * __restrict  xre,
                                const float * __restrict  yim,
                                float * __restrict  wrkc,
                                float * __restrict  csqr,
                                float * __restrict  csqi,
                                const int32_t n)

                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));

void csqrtv_zmm16r4_unroll_6x_a(const float * __restrict xre,
                                const float * __restrict yim,
                                float * __restrict wrkc,
                                float * __restrict  csqr,
                                float * __restrict csqi,
                                const int32_t n) 

                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));


void csqrtv_zmm16r4_unroll_6x_u(const float * __restrict xre,
                                const float * __restrict yim,
                                float * __restrict wrkc,
                                float * __restrict csqr,
                                float * __restrict csqi,
                                const int32_t n)


                                                         __attribute__((noinline))
							 __attribute__((hot))
                                                         __attribute__((aligned(32)));



#endif /*__GMS_CSQRT_VEC_ZMM16R4_H__*/
