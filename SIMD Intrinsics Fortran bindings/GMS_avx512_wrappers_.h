

#ifndef __GMS_AVX512_WRAPPERS_H__
#define __GMS_AVX512_WRAPPERS_H__


const unsigned int gGMS_AVX512_WRAPPERS_MAJOR = 1;
const unsigned int gGMS_AVX512_WRAPPERS_MINOR = 0;
const unsigned int gGMS_AVX512_WRAPPERS_MICRO = 0;
const unsigned int gGMS_AVX512_WRAPPERS_FULLVER =
  1000U*gGMS_AVX512_WRAPPERS_MAJOR+100U*gGMS_AVX512_WRAPPERS_MINOR+10U*gGMS_AVX512_WRAPPERS_MICRO;
const char * const pgGMS_AVX512_WRAPPERS_CREATE_DATE = "10-10-2019 11:39 +00200 (SUN 10 NOV 2019 GMT+2)";
const char * const pgGMS_AVX512_WRAPPERS_BUILD_DATE_TIME  = __DATE__" " __TIME__;
const char * const pgGMS_AVX512_WRAPPERS_AUTHOR = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
const char * const pgGMS_AVX512_WRAPPERS_SYNOPSIS = "Callable from Fortran C wrappers for AVX512F Intrinsics.";

// Compile it as a C-code

    // Interoperable with corresponding Fortran derived type

        typedef struct __attribute__((align(64))) v8f64 {
                 double v[8];
        }v8f64;

        typedef struct __attribute__((align(64))) v16f32 {
                 double v[16];
	}v16f32;




        v8f64 v8f64_add_pd( v8f64 , v8f64 ) __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        v16f32 v16f32_add_ps(v16f32, v16f32) __attribute__((noinline))
                                             __attribute__((hot))
				             __attribute__((regcall))
				             __attribute__((aligned(32)));

	v8f64 v8f64_sub_pd(v8f64 ,v8f64 ) __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_sub_ps(v16f32, v16f32) __attribute__((noinline))
                                             __attribute__((hot))
				             __attribute__((regcall))
				             __attribute__((aligned(32)));

	v8f64 v8f64_mul_pd(v8f64 ,v8f64 ) __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mul_ps(v16f32, v16f32) __attribute__((noinline))
                                             __attribute__((hot))
				             __attribute__((regcall))
				             __attribute__((aligned(32)));

	v8f64 v8f64_div_pd(v8f64 ,v8f64 ) __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_div_ps(v16f32, v16f32) __attribute__((noinline))
                                             __attribute__((hot))
				             __attribute__((regcall))
				             __attribute__((aligned(32)));

	v8f64 v8f64_mask_ceil_pd(v8f64 ,unsigned char ,v8f64 ) __attribute__((noinline))
                                                               __attribute__((hot))
				                               __attribute__((regcall))
				                               __attribute__((aligned(32)));

	v16f32 v16f32_mask_ceil_ps(v16f32, unsigned short, v16f32) __attribute__((noinline))
                                                                   __attribute__((hot))
				                                   __attribute__((regcall))
				                                   __attribute__((aligned(32)));

	v8f64 v8f64_ceil_pd(v8f64 )       __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_ceil_ps(v16f32)     __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_abs_pd(v8f64 )        __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_abs_ps(v16f32)      __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_abs_pd(v8f64 ,unsigned char ,v8f64 )  __attribute__((noinline))
                                                               __attribute__((hot))
				                               __attribute__((regcall))
				                               __attribute__((aligned(32)));

	v16f32 v16f32_mask_abs_ps(v16f32, unsigned short, v16f32) __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_mask_add_pd(v8f64 ,unsigned char ,v8f64 ,v8f64 ) __attribute__((noinline))
                                                                     __attribute__((hot))
				                                     __attribute__((regcall))
				                                     __attribute__((aligned(32)));

	v16f32 v16f32_mask_add_ps(v16f32, unsigned short, v16f32) __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_maskz_add_pd(unsigned char ,v8f64 ,v8f64 ) __attribute__((noinline))
                                                               __attribute__((hot))
				                               __attribute__((regcall))
				                               __attribute__((aligned(32)));

	v16f32 v16f32_maskz_add_ps(unsigned short, v16f32, v16f32) __attribute__((noinline))
                                                                   __attribute__((hot))
				                                   __attribute__((regcall))
				                                   __attribute__((aligned(32)));

	v8f64 v8f64_add_round_pd(v8f64 ,v8f64 ,int)               __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_add_round_ps(v16f32, v16f32, int) __attribute__((noinline))
                                                        __attribute__((hot))
				                        __attribute__((regcall))
				                        __attribute__((aligned(32)));

	v8f64 v8f64_mask_add_round_pd(v8f64 ,unsigned char ,v8f64 ,v8f64 ,int ) __attribute__((noinline))
                                                                                __attribute__((hot))
				                                                __attribute__((regcall))
				                                                __attribute__((aligned(32)));

	v16f32 v16f32_mask_add_round_ps(v16f32, unsigned short, v16f32, v16f32, int) __attribute__((noinline))
                                                                                     __attribute__((hot))
				                                                     __attribute__((regcall))
				                                                     __attribute__((aligned(32)));

	v8f64 v8f64_maskz_add_round_pd(unsigned char ,v8f64 ,v8f64 ,int )  __attribute__((noinline))
                                                                           __attribute__((hot))
				                                           __attribute__((regcall))
				                                           __attribute__((aligned(32)));

	v16f32 v16f32_maskz_add_round_ps(unsigned short, v16f32, v16f32, int) __attribute__((noinline))
                                                                              __attribute__((hot))
				                                              __attribute__((regcall))
				                                              __attribute__((aligned(32)));

	v8f64 v8f64_mask_div_pd(v8f64 ,unsigned char ,v8f64 ,v8f64 ) __attribute__((noinline))
                                                                     __attribute__((hot))
				                                     __attribute__((regcall))
				                                     __attribute__((aligned(32)));

	v16f32 v16f32_mask_div_ps(v16f32, unsigned short, v16f32, v16f32) __attribute__((noinline))
                                                                          __attribute__((hot))
				                                          __attribute__((regcall))
				                                          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_div_pd(unsigned char, v8f64, v8f64) __attribute__((noinline))
                                                              __attribute__((hot))
				                              __attribute__((regcall))
				                              __attribute__((aligned(32)));

	v16f32 v16f32_maskz_div_ps(unsigned short, v16f32, v16f32) __attribute__((noinline))
                                                                   __attribute__((hot))
				                                   __attribute__((regcall))
				                                   __attribute__((aligned(32)));

	v8f64 v8f64_div_round_pd(v8f64, v8f64, int) __attribute__((noinline))
                                                    __attribute__((hot))
				                    __attribute__((regcall))
				                    __attribute__((aligned(32)));

	v16f32 v16f32_div_round_ps(v16f32, v16f32, int) __attribute__((noinline))
                                                        __attribute__((hot))
				                        __attribute__((regcall))
				                        __attribute__((aligned(32)));

	v8f64 v8f64_mask_div_round_pd(v8f64, unsigned char, v8f64, v8f64,int) __attribute__((noinline))
                                                                              __attribute__((hot))
				                                              __attribute__((regcall))
				                                              __attribute__((aligned(32)));

	v16f32 v16f32_mask_div_round_ps(v16f32, unsigned short, v16f32, v16f32, int) __attribute__((noinline))
                                                                                     __attribute__((hot))
				                                                     __attribute__((regcall))
				                                                     __attribute__((aligned(32)));

	v8f64 v8f64_maskz_div_round_pd(unsigned char, v8f64, v8f64, int) __attribute__((noinline))
                                                                         __attribute__((hot))
				                                         __attribute__((regcall))
				                                         __attribute__((aligned(32)));
 
	v16f32 v16f32_maskz_div_round_ps(unsigned short, v16f32, v16f32, int) __attribute__((noinline))
                                                                              __attribute__((hot))
				                                              __attribute__((regcall))
				                                              __attribute__((aligned(32)));

	v8f64 v8f64_fmadd_pd(v8f64, v8f64, v8f64) __attribute__((noinline))
                                                  __attribute__((hot))
				                  __attribute__((regcall))
				                  __attribute__((aligned(32)));

	v16f32 v16f32_fmadd_ps(v16f32, v16f32, v16f32)
	                                               __attribute__((noinline))
                                                       __attribute__((hot))
				                       __attribute__((regcall))
				                       __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmadd_pd(v8f64, unsigned char, v8f64, v8f64)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmadd_ps(v16f32, unsigned short, v16f32, v16f32)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmadd_pd(v8f64, v8f64, v8f64, unsigned char)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmadd_ps(v16f32, v16f32, v16f32, unsigned short)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmadd_pd(unsigned char, v8f64, v8f64, v8f64)
                                                                  __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));
				                                  
	v16f32 v16f32_maskz_fmadd_ps(unsigned short, v16f32, v16f32, v16f32)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_fmadd_round_pd(v8f64, v8f64, v8f64, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_fmadd_round_ps(v16f32, v16f32, v16f32, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmadd_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmadd_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmadd_round_pd(v8f64, v8f64, v8f64, unsigned char, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmadd_round_ps(v16f32, v16f32, v16f32, unsigned short, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmadd_round_pd(unsigned char, v8f64, v8f64, v8f64, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmadd_round_ps(unsigned short, v16f32, v16f32, v16f32, int)
	                                                          __attribute__((noinline))
                                                                  __attribute__((hot))
				                                  __attribute__((regcall))
				                                  __attribute__((aligned(32)));

	v8f64 v8f64_fmaddsub_pd(v8f64, v8f64, v8f64)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v16f32 v16f32_fmaddsub_ps(v16f32, v16f32, v16f32)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmaddsub_pd(v8f64, unsigned char, v8f64, v8f64)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmaddsub_ps(v16f32, unsigned short, v16f32, v16f32)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmaddsub_pd(v8f64, v8f64, v8f64, unsigned char)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmaddsub_ps(v16f32, v16f32, v16f32, unsigned short)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmaddsub_pd(unsigned char, v8f64, v8f64, v8f64)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmaddsub_ps(unsigned short, v16f32, v16f32, v16f32)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v8f64 v8f64_fmaddsub_round_pd(v8f64, v8f64, v8f64, int)
	                                         __attribute__((noinline))
                                                 __attribute__((hot))
				                 __attribute__((regcall))
				                 __attribute__((aligned(32)));

	v16f32 v16f32_fmaddsub_round_ps(v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmaddsub_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmaddsub_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmaddsub_round_pd(v8f64, v8f64, v8f64, unsigned char, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmaddsub_round_ps(v16f32, v16f32, v16f32, unsigned short, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmaddsub_round_pd(unsigned char, v8f64, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmaddsub_round_ps(unsigned short, v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_fmsub_pd(v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fmsub_ps(v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmsub_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmsub_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmsub_pd(v8f64, v8f64, v8f64, unsigned char)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmsub_ps(v16f32, v16f32, v16f32, unsigned short)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmsub_pd(v8f64, v8f64, v8f64, unsigned char)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmsub_ps(v16f32, v16f32, v16f32, unsigned short)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_fmsubadd_pd(v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fmsubadd_ps(v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmsubadd_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmsubadd_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmsubadd_pd(v8f64, v8f64, v8f64, unsigned char)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmsubadd_ps(v16f32, v16f32, v16f32, unsigned short)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmusbadd_pd(unsigned char, v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmsubadd_ps(unsigned short, v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_fmsubadd_round_pd(v8f64, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fmsubadd_round_ps(v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fmsubadd_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fmsubadd_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fmsubbadd_round_pd(v8f64, v8f64, v8f64, unsigned char, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fmsubadd_round_ps(v16f32, v16f32, v16f32, unsigned short, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fmsubadd_round_pd(unsigned char, v8f64, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fmsubadd_round_ps(unsigned short, v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_fnmadd_pd(v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fnmadd_ps(v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fnmadd_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fnmadd_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fnmadd_pd(v8f64, v8f64, v8f64, unsigned char)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fnmadd_ps(v16f32, v16f32, v16f32, unsigned short)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fnmadd_pd(unsigned char, v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fnmadd_ps(unsigned short, v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        v8f64 v8f64_fnmadd_round_pd(v8f64, v8f64, v8f64, int)
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fnmadd_round_ps(v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fnmadd_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fnmadd_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fnmadd_round_pd(v8f64, v8f64, v8f64, unsigned char, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fnmadd_round_ps(v16f32, v16f32, v16f32, unsigned short, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fnmadd_round_pd(unsigned char, v8f64, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fnmadd_round_ps(unsigned short, v16f32, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_fnmsub_pd(v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_fnmsub_ps(v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_fnmsub_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_fnmsub_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask3_fnmsub_pd(v8f64, v8f64, v8f64, unsigned char)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask3_fnmsub_ps(v16f32, v16f32, v16f32, unsigned short)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_fnmsub_pd(unsigned char, v8f64, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_fnmsub_ps(unsigned short, v16f32, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_mul_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_mul_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_mul_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_mul_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_mul_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_mul_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_mul_round_pd(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_mul_round_ps(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        double  v8f64_mask_reduce_add_pd(unsigned char, v8f64)
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float  v16f32_mask_reduce_add_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_reduce_add_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float v16f32_reduce_add_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_mask_reduce_mul_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float v16f32_mask_reduce_mul_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_reduce_mul_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float v16f32_reduce_mul_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_mask_sub_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_sub_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64 v8f64_maskz_sub_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_sub_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmp_pd_mask(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmp_ps_mask(v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmp_pd_mask(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmp_ps_mask(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmp_round_pd_mask(v8f64, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmp_round_ps_mask(v16f32, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmp_round_pd_mask(unsigned char, v8f64, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmp_round_ps_mask(unsigned short, v16f32, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpeq_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpeq_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpeq_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpeq_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpunord_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpunord_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpunord_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpunord_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpord_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpord_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpord_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpord_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpnlt_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpnlt_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpnlt_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpnlt_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpnle_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpnle_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpnle_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpnle_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmpneq_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmpneq_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmpneq_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmpneq_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmplt_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmplt_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmplt_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmplt_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_cmple_pd_mask(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_cmple_ps_mask(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned char  v8f64_mask_cmple_pd_mask(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	unsigned short v16f32_mask_cmple_ps_mask(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_rcp14_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_rcp14_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_rcp14_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_rcp14_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_rcp14_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_rcp14_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_rsqrt14_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_rsqrt14_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_rsqrt14_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_rsqrt14_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_rsqrt14_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_rsqrt14_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_sqrt_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_sqrt_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_sqrt_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_sqrt_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_sqrt_round_pd(v8f64, unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_sqrt_round_ps(v16f32, unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_sqrt_round_pd(unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_sqrt_round_ps(unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_expandloadu_pd(v8f64, unsigned char, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_expandloadu_ps(v16f32, unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_expandload_pd(unsigned char, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_expandloadu_ps(unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_load_pd(v8f64, unsigned char, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_load_ps(v16f32, unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_load_pd(unsigned char, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_load_ps(unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_loadu_pd(v8f64, unsigned char, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_loadu_ps(v16f32, unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_loadu_pd(unsigned char, void * )
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_loadu_ps(unsigned short, void *)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_getexp_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_getexp_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_getexp_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_getexp_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_getexp_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_getexp_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_getexp_round_pd(v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_getexp_round_ps(v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_getexp_round_pd(v8f64, unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_getexp_round_ps(v16f32, unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_getexp_round_pd(unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_getexp_round_ps(unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_getmant_pd(v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_getmant_ps(v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_getmant_pd(v8f64, unsigned char, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_getmant_ps(v16f32, unsigned short, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_getmant_pd(unsigned char, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v1632_maskz_getmant_ps(unsigned short, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_getmant_round_pd(v8f64, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_getmant_round_ps(v16f32, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_getmant_round_pd(v8f64, unsigned char, v8f64, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_getmant_round_ps(v16f32, unsigned short, v16f32, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_getmant_round_pd(unsigned char, v8f64, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_getmant_round_ps(unsigned short, v16f32, int, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_roundscale_pd(v8f64, unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        v16f32 v16f32_mask_roundscale_ps(v16f32, unsigned short, v16f32, int)
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        v8f64  v8f64_maskz_roundscale_pd(unsigned char, v8f64, int)
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_roundscale_ps(unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_roundscale_pd(v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_roundscale_ps(v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_roundscale_round_pd(v8f64, unsigned char, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_roundscale_round_ps(v16f32, unsigned short, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_roundscale_round_pd(unsigned char, v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_roundscale_round_ps(unsigned short, v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_roundscale_round_pd(v8f64, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_roundscale_round_ps(v16f32, int, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_scalef_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_scalef_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_scalef_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_scalef_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_scalef_pd(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_scalef_ps(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_scalef_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_scalef_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_scalef_round_pd(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_scalef_round_ps(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_scalef_round_pd(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_scalef_round_ps(v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_mov_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_mov_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_mov_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_mov_ps(unsigned short, v16f32);
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_movedup_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_movedup_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_movedup_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_movedup_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_movedup_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_movedup_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_set4_pd(double, double, double, double)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        

	v8f64  v8f64_mask_max_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_max_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_max_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_max_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_max_pd(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_max_ps(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_max_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_max_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_max_round_pd(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_max_round_ps(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_max_round_pd(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_max_round_ps(v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_min_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_min_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_min_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_min_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_min_pd(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_min_ps(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_min_round_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_min_round_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_min_round_pd(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_min_round_ps(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_min_round_pd(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_min_round_ps(v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_mask_reduce_max_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float  v16f32_mask_reduce_max_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_reduce_max_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float  v16f32_reduce_max_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_mask_reduce_min_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float  v16f32_mask_reduce_min_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	double  v8f64_reduce_min_pd(v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	float  v16f32_reduce_min_ps(v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_unpacklo_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_unpacklo_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_unpacklo_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_unpacklo_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_unpacklo_pd(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_unpacklo_ps(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_unpackhi_pd(v8f64, unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_unpackhi_ps(v16f32, unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_unpackhi_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_unpackhi_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_unpackhi_pd(v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_unpackhi_ps(v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_shuffle_pd(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_shuffle_ps(v16f32, unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_shuffle_pd(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_shuffle_ps(unsigned short, v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_shuffle_pd(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_shuffle_ps(v16f32, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_shuffle_f64x2(v8f64, unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_shuffle_f64x2(unsigned char, v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_shuffle_f64x2(v8f64, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_permutex_pd(v8f64, unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_permutex_ps(v16f32, unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_permutex_pd(unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_permutex_ps(unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_permutex_pd(v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_permutex_ps(v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_blend_pd(unsigned char, v8f64, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_blend_ps(unsigned short, v16f32, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_compress_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_compress_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_compress_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_compress_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void   v8f64_mask_compressstoreu_pd(void *, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void   v16f32_mask_compressstoreu_ps(void *, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_expand_pd(v8f64, unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_expand_ps(v16f32, unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_expand_pd(unsigned char, v8f64)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_expand_ps(unsigned short, v16f32)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_mask_permute_pd(v8f64, unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_mask_permute_ps(v16f32, unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_maskz_permute_pd(unsigned char, v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_maskz_permute_ps(unsigned short, v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v8f64  v8f64_permute_pd(v8f64, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	v16f32 v16f32_permute_ps(v16f32, int)
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

// The same wrappers implemented as a void functions in order to reduce to 3
// the number of machine code instructions.
// The naming of functions was changed.



        void avx512_add_pd(double       * __restrict,
	                   const double * __restrict,
			   const double * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_add_ps(float        * __restrict,
	                   const float  * __restrict,
			   const float  * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_sub_pd(double       * __restrict,
	                   const double * __restrict,
			   const double * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        void avx512_sub_ps(float        * __restrict,
	                   const float  * __restrict,
			   const float  * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mul_pd(double       * __restrict,
	                   const double * __restrict,
			   const double * __restrict) 
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));
 
	void avx512_mul_ps(float        * __restrict,
	                   const float  * __restrict,
			   const float  * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_div_pd(double       * __restrict,
	                   const double * __restrict,
			   const double * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_div_ps(float        * __restrict,
	                   const float  * __restrict,
			   const float  * __restrict) 
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_ceil_pd(double       * __restrict,
	                         const double * __restrict,
	                         const unsigned char,
				 const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        void avx512_mask_ceil_ps(float        * __restrict,
	                         const float  * __restrict,
				 const unsigned short,
				 const float  * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_ceil_pd(double       * __restrict,
	                    const double * __restrict) 
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_ceil_ps(float        * __restrict,
	                    const float  * __restrict) 
	                                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_abs_pd(double       * __restrict,
	                        const double * __restrict,
				const unsigned char,
				const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_abs_ps(float        * __restrict,
	                        const float  * __restrict,
				const unsigned short,
				const float  * __restrict,
				const float  * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_add_pd(double       * __restrict,
	                        const double * __restrict,
				const unsigned char,
				const double * __restrict,
				const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_add_ps(float        * __restrict,
	                        const float  * __restrict,
				const unsigned short,
				const float  * __restrict,
				const float  * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_add_pd(double       * __restrict,
	                         const unsigned char,
				 const double * __restrict,
				 const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_add_ps(float        * __restrict,
	                         const unsigned short,
				 const float  * __restrict,
				 const float  * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_add_round_pd(double       * __restrict,
	                         const double * __restrict,
				 const double * __restrict,
				 const int)                 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_add_round_ps(float        * __restrict,
	                         const float  * __restrict,
				 const float  * __restrict,
				 const int)                 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_add_round_pd(double       * __restrict,
	                               const double * __restrict,
	                               const unsigned char,
				       const double * __restrict,
				       const double * __restrict,
				       const int)           
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_add_round_ps(float        * __restrict,
	                               const float  * __restrict,
				       const unsigned short,
				       const float  * __restrict,
				       const float  * __restrict,
				       const int)           
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_div_pd(double       * __restrict,
	                        const double * __restrict,
				const unsigned char,
				const double * __restrict,
				const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_div_ps((float       * __restrict,
	                        const float  * __restrict,
				const unsigned short,
				const float  * __restrict,
				const float  * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_div_pd(double       * __restrict,
	                         const unsigned char,
				 const double * __restrict,
				 const double * __restrict)  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_div_ps(float        * __restrict,
	                         const unsigned short,
				 const float  * __restrict,
				 const float  * __restrict)  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_div_round_pd(double       * __restrict,
	                         const double * __restrict,
				 const double * __restrict,
				 const int)                  
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));
 
	void avx512_div_round_ps(float        * __restrict,
	                         const float  * __restrict,
				 const float  * __restrict,
				 const int)                  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        void avx512_mask_div_round_pd(double       * __restrict,
	                              const double * __restrict,
				      const unsigned char,
				      const double * __restrict,
				      const double * __restrict,
				      const int)             
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_div_round_ps(float        * __restrict,
	                              const float  * __restrict,
				      const unsigned short,
				      const float  * __restrict,
				      const float  * __restrict,
				      const int)           
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_div_round_ps(double       * __restrict,
	                               const unsigned char,
				       const double * __restrict,
				       const double * __restrict,
				       const int)          
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_fmadd_pd(double       * __restrict,
	                     const double * __restrict,
			     const double * __restrict,
			     const double * __restrict)    
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_fmadd_ps(float        * __restrict,
	                     const float  * __restrict,
			     const float  * __restrict,
			     const float  * __restrict)     
			                  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_fmadd_pd(double       * __restrict,
	                          const double * __restrict,
	                          const unsigned char,
	                          const double * __restrict,
                                  const double * __restrict)  
                                          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_fmadd_ps(float        * __restrict,
	                          const float  * __restrict,
				  const unsigned short,
				  const float  * __restrict,
				  const float  * __restrict)  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask3_fmadd_pd(double       * __restrict,
	                           const double * __restrict,
				   const double * __restrict,
				   const double * __restrict,
				   const unsigned char)       
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask3_fmadd_ps(float        * __restrict,
	                           const float  * __restrict,
				   const float  * __restrict,
				   const float  * __restrict,
				   const unsigned short)     
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_fmadd_pd(double       * __restrict,
	                           const unsigned char,
				   const double * __restrict,
				   const double * __restrict,
				   const double * __restrict) 
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_fmadd_ps(float        * __restrict,
	                           const unsigned short,
				   const float  * __restrict,
				   const float  * __restrict,
				   const float  * __restrict)  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_fmadd_round_pd(double       * __restrict,
	                           const double * __restrict,
				   const double * __restrict,
				   const double * __restrict,
				   const int)                  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_fmadd_round_ps(float        * __restrict,
	                           const float  * __restrict,
				   const float  * __restrict,
				   const float  * __restrict,
				   const int)                   
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_fmadd_round_pd(double       * __restrict,
	                                const double * __restrict,
					const unsigned char,
					const double * __restrict,
					const double * __restrict,
					const int)               
					  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask_fmadd_round_ps(float        * __restrict,
	                                const float  * __restrict,
					const unsigned short,
					const float  * __restrict,
					const float  * __restrict,
					const int)               
					  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_mask3_fmadd_round_pd(double       * __restrict,
	                                 const double * __restrict,
				         const double * __restrict,
				         const double * __restrict,
					 const unsigned char,
					 const int)               
					  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

        void avx512_mask3_fmadd_round_ps(float        * __restrict,
	                                 const float  * __restrict,
				         const float  * __restrict,
				         const float  * __restrict,
					 const unsigned short,
					 const int)              
					  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_fmadd_round_pd(double      * __restrict,
	                                const unsigned char,
					const double * __restrict,
				        const double * __restrict,
				        const double * __restrict,
					const int)              
					  __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	void avx512_maskz_fmadd_round_ps(float       * __restrict,
	                                 const unsigned short,
					 const float  * __restrict,
				         const float  * __restrict,
				         const float  * __restrict,
				         const int)  
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));              

	void avx512_fmaddsub_pd(double       * __restrict,
	                        const double * __restrict,
				const double * __restrict,
				const double * __restrict)          
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));
				
	void avx512_fmaddsub_ps(float        * __restrict,
	                        const float  * __restrict,
			        const float  * __restrict,
				const float  * __restrict)           
				          __attribute__((noinline))
                                          __attribute__((hot))
				          __attribute__((regcall))
				          __attribute__((aligned(32)));

	

#endif /*__GMS_AVX512_WRAPPERS_H__*/
