
#include "GMS_complex_zmm16r4.h"


                    void cadd_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       const float * __restrict yre,
                                       const float * __restrict yim,
                                       float *       __restrict zre,
                                       float *       __restrict zim)  {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&yre[0]);
                        _mm512_storeu_ps(&zre[0], _mm512_add_ps(zmm0,zmm1));
                        zmm2  = _mm512_loadu_ps(&xim[0]);
                        zmm3  = _mm512_loadu_ps(&yim[0]);
                        _mm512_storeu_ps(&zim[0], _mm512_add_ps(zmm2,zmm3)); 
                   }


                    void cadd_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       const float * __restrict __attribute__((aligned(64))) yre,
                                       const float * __restrict __attribute__((aligned(64))) yim,
                                       float *       __restrict __attribute__((aligned(64))) zre,
                                       float *       __restrict __attribute__((aligned(64))) zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&yre[0]);
                        _mm512_store_ps(&zre[0], _mm512_add_ps(zmm0,zmm1));
                        zmm2  = _mm512_load_ps(&xim[0]);
                        zmm3  = _mm512_load_ps(&yim[0]);
                        _mm512_store_ps(&zim[0], _mm512_add_ps(zmm2,zmm3));  
                   }


                  void cadd_zmm16r4( const __m512 xre,
                                     const __m512 xim,
                                     const __m512 yre,
                                     const __m512 yim,
                                     __m512 * __restrict zre,
                                     __m512 * __restrict zim) {

                        register __m512 zmm0,zmm1;
                        zmm0  = _mm512_add_ps(xre,yre);
                        *zre  = zmm0;
                        zmm1  = _mm512_add_ps(xim,yim);
                        *zim  = zmm1; 
                  }


                 
                   void cadd_zmm16r4_uip(const float * __restrict xre,
                                         const float * __restrict xim,
                                         float *       __restrict zre,
                                         float *       __restrict zim) {
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&xim[0]);
                        zmm2  = _mm512_loadu_ps(&zre[0]);
                        zmm3  = _mm512_loadu_ps(&zim[0])
                        _mm512_storeu_ps(&zre[0], _mm512_add_ps(zmm2,zmm0));
                        _mm512_storeu_ps(&zim[0], _mm512_add_ps(zmm3,zmm1));
              }


                  
                   void cadd_zmm16r4_aip(const float * __restrict __attribute__((aligned(64))) xre,
                                         const float * __restrict __attribute__((aligned(64))) xim,
                                         float *       __restrict __attribute__((aligned(64))) zre,
                                         float *       __restrict __attribute__((aligned(64))) zim) {
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&xim[0]);
                        zmm2  = _mm512_load_ps(&zre[0]);
                        zmm3  = _mm512_load_ps(&zim[0])
                        _mm512_store_ps(&zre[0], _mm512_add_ps(zmm2,zmm0));
                        _mm512_store_ps(&zim[0], _mm512_add_ps(zmm3,zmm1));
              }


              /////////////////////////////////////////////////////////////////////////////////////////


                
                   void csub_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       const float * __restrict yre,
                                       const float * __restrict yim,
                                       float *       __restrict zre,
                                       float *       __restrict zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&yre[0]);
                        _mm512_storeu_ps(&zre[0], _mm512_sub_ps(zmm0,zmm1));
                        zmm2  = _mm512_loadu_ps(&xim[0]);
                        zmm3  = _mm512_loadu_ps(&yim[0]);
                        _mm512_storeu_ps(&zim[0], _mm512_sub_ps(zmm2,zmm3));
                 }


                  
                   void csub_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       const float * __restrict __attribute__((aligned(64))) yre,
                                       const float * __restrict __attribute__((aligned(64))) yim,
                                       float *       __restrict __attribute__((aligned(64))) zre,
                                       float *       __restrict __attribute__((aligned(64))) zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&yre[0]);
                        _mm512_store_ps(&zre[0], _mm512_sub_ps(zmm0,zmm1));
                        zmm2  = _mm512_load_ps(&xim[0]);
                        zmm3  = _mm512_load_ps(&yim[0]);
                        _mm512_store_ps(&zim[0], _mm512_sub_ps(zmm2,zmm3));
                 }


                 
                   void csub_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 yre,
                                     const __m512 yim,
                                     __m512 * __restrict     zre,
                                     __m512 * __restrict     zim) {
                     
                        register __m512 zmm0,zmm1;
                        zmm0  = _mm512_sub_ps(xre,yre);
                        *zre  = zmm0;
                        zmm1  = _mm512_sub_ps(xim,yim);
                        *zim  = zmm1;
                }


                 
                   void csub_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 s,
                                     __m512 * __restrict     zre,
                                     __m512 * __restrict     zim) {

                        *zre = _mm512_sub_ps(xre,s);
                        *zim = _mm512_sub_ps(xim,s);
               }


                  
                   void csub_zmm16r4_uip(const float * __restrict xre,
                                         const float * __restrict xim,
                                         float *       __restrict zre,
                                         float *       __restrict zim) {
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&xim[0]);
                        zmm2  = _mm512_loadu_ps(&zre[0]);
                        zmm3  = _mm512_loadu_ps(&zim[0])
                        _mm512_storeu_ps(&zre[0], _mm512_sub_ps(zmm2,zmm0));
                        _mm512_storeu_ps(&zim[0], _mm512_sub_ps(zmm3,zmm1));
              }


                  
                   void csub_zmm16r4_aip(const float * __restrict __attribute__((aligned(64))) xre,
                                         const float * __restrict __attribute__((aligned(64))) xim,
                                         float *       __restrict __attribute__((aligned(64))) zre,
                                         float *       __restrict __attribute__((aligned(64))) zim) {
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&xim[0]);
                        zmm2  = _mm512_load_ps(&zre[0]);
                        zmm3  = _mm512_load_ps(&zim[0])
                        _mm512_store_ps(&zre[0], _mm512_sub_ps(zmm2,zmm0));
                        _mm512_store_ps(&zim[0], _mm512_sub_ps(zmm3,zmm1));
              }


           ////////////////////////////////////////////////////////////////////////////////////


                
                   void cmul_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       const float * __restrict yre,
                                       const float * __restrict yim,
                                       float *       __restrict zre,
                                       float *       __restrict zim) {

                           register __m512 zmm0,zmm1,zmm2,zmm3,zmm4,zmm5;
                           zmm0  = _mm512_loadu_ps(&xre[0]);
                           zmm1  = _mm512_loadu_ps(&yre[0]);
                           zmm2  = _mm512_loadu_ps(&xim[0]);
                           zmm3  = _mm512_loadu_ps(&yim[0]);
                           zmm4  = _mm512_sub_ps(_mm512_mul_ps(zmm0,zmm1),
                                                                        _mm512_mul_ps(zmm2,zmm3));
                           _mm512_storeu_ps(&zre[0], zmm4);
                           zmm5  = _mm512_mul_ps(_mm512_mul_ps(zmm2,zmm1),
                                                                        _mm512_mul_ps(zmm0,zmm3));
                           _mm512_storeu_ps(&zim[0], zmm5);
               }


                
                   void cmul_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       const float * __restrict __attribute__((aligned(64))) yre,
                                       const float * __restrict __attribute__((aligned(64))) yim,
                                       float *       __restrict __attribute__((aligned(64))) zre,
                                       float *       __restrict __attribute__((aligned(64))) zim) {

                           register __m512 zmm0,zmm1,zmm2,zmm3,zmm4,zmm5;
                           zmm0  = _mm512_load_ps(&xre[0]);
                           zmm1  = _mm512_load_ps(&yre[0]);
                           zmm2  = _mm512_load_ps(&xim[0]);
                           zmm3  = _mm512_load_ps(&yim[0]);
                           zmm4  = _mm512_sub_ps(_mm512_mul_ps(zmm0,zmm1),
                                                                        _mm512_mul_ps(zmm2,zmm3));
                           _mm512_store_ps(&zre[0], zmm4);
                           zmm5  = _mm512_mul_ps(_mm512_mul_ps(zmm2,zmm1),
                                                                        _mm512_mul_ps(zmm0,zmm3));
                           _mm512_store_ps(&zim[0], zmm5);
               }


                 
                   void cmul_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 yre,
                                     const __m512 yim,
                                     __m512 * __restrict     zre,
                                     __m512 * __restrict     zim) {

                         register __m512 zmm0,zmm1;
                         zmm0 = _mm512_sub_ps(_mm512_mul_ps(xre,yre),
                                              _mm512_mul_ps(xim,yim));
                         *zre  = zmm0;
                         zmm1 = _mm512_mul_ps(_mm512_mul_ps(xim,yre),
                                              _mm512_mul_ps(xre,yim));
                         *zim  = zmm1;
                }


                  
                   void cmul_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 s,
                                     __m512 * __restrict   zre,
                                     __m512 * __restrict   zim) {

                        *zre = _mm512_mul_ps(xre,s);
                        *zim = _mm512_mul_ps(xim,s);
               }


                  
                   void cmul_zmm16r4_uip(const float * __restrict xre,
                                         const float * __restrict xim,
                                         float *       __restrict zre,
                                         float *       __restrict zim) {

                           register __m512 zmm0,zmm1,zmm2,zmm3,zmm4,zmm5;
                           zmm0  = _mm512_loadu_ps(&xre[0]);
                           zmm1  = _mm512_loadu_ps(&zre[0]);
                           zmm2  = _mm512_loadu_ps(&xim[0]);
                           zmm3  = _mm512_loadu_ps(&zim[0]);
                           zmm4  = _mm512_sub_ps(_mm512_mul_ps(zmm0,zmm1),
                                                 _mm512_mul_ps(zmm2,zmm3));
                           _mm512_storeu_ps(&zre[0], zmm4);
                           zmm5  = _mm512_mul_ps(_mm512_mul_ps(zmm2,zmm1),
                                                 _mm512_mul_ps(zmm0,zmm3));
                           _mm512_storeu_ps(&zim[0], zmm5);
               }


                  
                   void cmul_zmm16r4_aip(const float * __restrict __attribute__((aligned(64))) xre,
                                         const float * __restrict __attribute__((aligned(64))) xim,
                                         float *       __restrict __attribute__((aligned(64))) zre,
                                         float *       __restrict __attribute__((aligned(64))) zim) {

                           register __m512 zmm0,zmm1,zmm2,zmm3,zmm4,zmm5;
                           zmm0  = _mm512_load_ps(&xre[0]);
                           zmm1  = _mm512_load_ps(&zre[0]);
                           zmm2  = _mm512_load_ps(&xim[0]);
                           zmm3  = _mm512_load_ps(&zim[0]);
                           zmm4  = _mm512_sub_ps(_mm512_mul_ps(zmm0,zmm1),
                                                 _mm512_mul_ps(zmm2,zmm3));
                           _mm512_store_ps(&zre[0], zmm4);
                           zmm5  = _mm512_mul_ps(_mm512_mul_ps(zmm2,zmm1),
                                                 _mm512_mul_ps(zmm0,zmm3));
                           _mm512_store_ps(&zim[0], zmm5);
               }


              /////////////////////////////////////////////////////////////////////////////////


              
                   void cdiv_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       const float * __restrict yre,
                                       const float * __restrict yim,
                                       float *       __restrict zre,
                                       float *       __restrict zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3; 
                        register __m512 zmm4,zmm5,zmm6;
                        zmm0  = _mm512_loadu_ps(&xre[0]); //a
                        zmm1  = _mm512_loadu_ps(&yim[0]); //d
                        zmm2  = _mm512_loadu_ps(&xim[0]); //b
                        zmm3  = _mm512_loadu_ps(&yre[0]); //c
                        zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                        zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                        zmm6  = _mm512_fmadd_ps(zmm3,zmm3),
                                                _mm512_mul_ps(zmm1,zmm1));
                        _mm512_storeu_ps(&zre[0], _mm512_div_ps(zmm4,zmm6));
                        _mm512_storeu_ps(&zim[0], _mm512_div_ps(zmm5,zmm6));
                }


                  
                   void cdiv_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       const float * __restrict __attribute__((aligned(64))) yre,
                                       const float * __restrict __attribute__((aligned(64))) yim,
                                       float *       __restrict __attribute__((aligned(64))) zre,
                                       float *       __restrict __attribute__((aligned(64))) zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3; 
                        register __m512 zmm4,zmm5,zmm6;
                        zmm0  = _mm512_load_ps(&xre[0]); //a
                        zmm1  = _mm512_load_ps(&yim[0]); //d
                        zmm2  = _mm512_load_ps(&xim[0]); //b
                        zmm3  = _mm512_load_ps(&yre[0]); //c
                        zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                        zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                        zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                        _mm512_store_ps(&zre[0], _mm512_div_ps(zmm4,zmm6));
                        _mm512_store_ps(&zim[0], _mm512_div_ps(zmm5,zmm6));
                }
              
                                         
                  
                   void cdiv_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 yre,
                                     const __m512 yim,
                                     __m512 * __restrict zre,
                                     __m512 * __restrict zim) {

                      register __m512 zmm0,zmm1,zmm2;
                      zmm0 = _mm512_fmadd_ps(xre,yre,
                                           _mm512_mul_ps(xim,yim));
                      zmm1 = _mm512_fmsub_ps(xim,yre,
                                           _mm512_mul_ps(xre,yim));
                      zmm2 = _mm512_fmadd_ps(zmm3,zmm3,
                                           _mm512_mul_ps(zmm1,zmm1));
                      *zre  = _mm512_div_ps(zmm0,zmm2);
                      *zim  = _mm512_div_ps(zmm1,zmm2);
                }


                 
                   void cdiv_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     const __m512 s,
                                     __m512 * __restrict zre,
                                     __m512 * __restrict zim) {

                        *zre = _mm512_div_ps(xre,s);
                        *zim = _mm512_div_ps(xim,s);
               }


                  
                   void cdiv_zmm16r4_uip(const float * __restrict xre,
                                         const float * __restrict xim,
                                         float *       __restrict zre,
                                         float *       __restrict zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3; 
                        register __m512 zmm4,zmm5,zmm6;
                        zmm0  = _mm512_loadu_ps(&xre[0]); //a
                        zmm1  = _mm512_loadu_ps(&zim[0]); //d
                        zmm2  = _mm512_loadu_ps(&xim[0]); //b
                        zmm3  = _mm512_loadu_ps(&zre[0]); //c
                        zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                        zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                        zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                        _mm512_storeu_ps(&zre[0], _mm512_div_ps(zmm4,zmm6));
                        _mm512_storeu_ps(&zim[0], _mm512_div_ps(zmm5,zmm6));
              }


                  
                   void cdiv_zmm16r4_aip(const float * __restrict __attribute__((aligned(64))) xre,
                                         const float * __restrict __attribute__((aligned(64))) xim,
                                         float *       __restrict __attribute__((aligned(64))) zre,
                                         float *       __restrict __attribute__((aligned(64))) zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3; 
                        register __m512 zmm4,zmm5,zmm6;
                        zmm0  = _mm512_load_ps(&xre[0]); //a
                        zmm1  = _mm512_load_ps(&zim[0]); //d
                        zmm2  = _mm512_load_ps(&xim[0]); //b
                        zmm3  = _mm512_load_ps(&zre[0]); //c
                        zmm4  = _mm512_fmadd_ps(zmm0,zmm3,
                                                _mm512_mul_ps(zmm2,zmm1));
                        zmm5  = _mm512_fmsub_ps(zmm2,zmm3,
                                                _mm512_mul_ps(zmm0,zmm1));
                        zmm6  = _mm512_fmadd_ps(zmm3,zmm3,
                                                _mm512_mul_ps(zmm1,zmm1));
                        _mm512_store_ps(&zre[0], _mm512_div_ps(zmm4,zmm6));
                        _mm512_store_ps(&zim[0], _mm512_div_ps(zmm5,zmm6));
              }


             //////////////////////////////////////////////////////////////////////////////////


              
                   void cdiv_smith_zmm16r4_u(const float * __restrict xre,
                                             const float * __restrict xim,
                                             const float * __restrict yre,
                                             const float * __restrict yim,
                                             float *       __restrict zre,
                                             float *       __restrict zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 r,den;
                        __mmask16 m = 0x0;
                        zmm0 = _mm512_loadu_ps(&yre[0]); // c
                        zmm1 = _mm512_loadu_ps(&yim[0]); // d
                        zmm2 = _mm512_loadu_ps(&xre[0]); // a
                        zmm3 = _mm512_loadu_ps(&xim[0]); // b
                        m    = _mm512_cmp_ps_mask(_mm512_abs_ps(zmm0),
                                                  _mm512_abs_ps(zmm1),
                                                  _CMP_GE_OQ);
                        r    = _mm512_mask_blend_ps(m,_mm512_div_ps(zmm0,zmm1),
                                                      _mm512_div_ps(zmm1,zmm0)); // r
                        den  = _mm512_mask_blend_ps(m,_mm512_fmadd_ps(r,zmm0,zmm1),
                                                      _mm512_fmadd_ps(r,zmm1,zmm0));
                        _mm512_storeu_ps(&zre[0], _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmadd_ps(zmm2,r,zmm3),den),
                                                _mm512_div_ps(_mm512_fmadd_ps(zmm3,r,zmm2),den)));
                        _mm512_storeu_ps(&zim[0], _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmsub_ps(zmm3,r,zmm2),den),
                                                _mm512_div_ps(_mm512_sub_ps(zmm3,_mm512_mul_ps(zmm2,r)),den)));
               }


                 
                   void cdiv_smith_zmm16r4_a(const float * __restrict __attribute__((aligned(64)))  xre,
                                             const float * __restrict __attribute__((aligned(64)))  xim,
                                             const float * __restrict __attribute__((aligned(64)))  yre,
                                             const float * __restrict __attribute__((aligned(64)))  yim,
                                             float *       __restrict __attribute__((aligned(64)))  zre,
                                             float *       __restrict __attribute__((aligned(64)))  zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 r,den;
                        __mmask16 m = 0x0;
                        zmm0 = _mm512_load_ps(&yre[0]); // c
                        zmm1 = _mm512_load_ps(&yim[0]); // d
                        zmm2 = _mm512_load_ps(&xre[0]); // a
                        zmm3 = _mm512_load_ps(&xim[0]); // b
                        m    = _mm512_cmp_ps_mask(_mm512_abs_ps(zmm0),
                                                  _mm512_abs_ps(zmm1),
                                                  _CMP_GE_OQ);
                        r    = _mm512_mask_blend_ps(m,_mm512_div_ps(zmm0,zmm1),
                                                      _mm512_div_ps(zmm1,zmm0)); // r
                        den  = _mm512_mask_blend_ps(m,_mm512_fmadd_ps(r,zmm0,zmm1),
                                                      _mm512_fmadd_ps(r,zmm1,zmm0));
                        _mm512_storeu_ps(&zre[0], _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmadd_ps(zmm2,r,zmm3),den),
                                                _mm512_div_ps(_mm512_fmadd_ps(zmm3,r,zmm2),den)));
                        _mm512_storeu_ps(&zim[0], _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmsub_ps(zmm3,r,zmm2),den),
                                                _mm512_div_ps(_mm512_sub_ps(zmm3,_mm512_mul_ps(zmm2,r)),den)));
               }


                  
                   void cdiv_smith_zmm16r4(const __m512 xre,
                                           const __m512 xim,
                                           const __m512 yre,
                                           const __m512 yim,
                                           __m512 * __restrict zre,
                                           __m512 * __restrict zim) {

                        register __m512 r,den;
                        __mmask16 m = 0x0;
                        m    = _mm512_cmp_ps_mask(_mm512_abs_ps(yre),
                                                  _mm512_abs_ps(yim),
                                                  _CMP_GE_OQ);
                        r    = _mm512_mask_blend_ps(m,_mm512_div_ps(yre,yim),
                                                      _mm512_div_ps(yim,yre)); // r
                        den  = _mm512_mask_blend_ps(m,_mm512_fmadd_ps(r,yre,yim),
                                                      _mm512_fmadd_ps(r,yim,yre));
                        *zre  =  _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmadd_ps(xre,r,xim),den),
                                                _mm512_div_ps(_mm512_fmadd_ps(xim,r,xre),den));
                        *zim  =  _mm512_mask_blend_ps(m,
                                                _mm512_div_ps(_mm512_fmsub_ps(xim,r,xre),den),
                                                _mm512_div_ps(_mm512_sub_ps(xim,_mm512_mul_ps(xre,r)),den)));
               }

#include "GMS_sleefsimdsp.h"


               /////////////////////////////////////////////////////////////////////////////////////


                 
                   void cabs_zmm16r4_u(const float * __restrict re,
                                       const float * __restrict im,
                                       float * __restrict  cabs) {

                        register __m512 zmm0,zmm1,zmm2,zmm3,zmm4;
                        zmm0  = _mm512_loadu_ps(&re[0]);
                        zmm1  = _mm512_mul_ps(zmm0,zmm0);
                        zmm2  = _mm512_loadu_ps(&im[0]);
                        zmm3  = _mm512_mul_ps(zmm2,zmm2);
                        zmm4  = xsqrtf(_mm512_add_ps(zmm1,zmm3));
                        _mm512_storeu_ps(&cabs[0],zmm4);
                 }


                 
                   void cabs_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) re,
                                       const float * __restrict __attribute__((aligned(64))) im,
                                       float * __restrict  __attribute__((aligned(64))) cabs) {

                        register __m512 zmm0,zmm1,zmm2,zmm3,zmm4;
                        zmm0  = _mm512_load_ps(&re[0]);
                        zmm1  = _mm512_mul_ps(zmm0,zmm0);
                        zmm2  = _mm512_load_ps(&im[0]);
                        zmm3  = _mm512_mul_ps(zmm2,zmm2);
                        zmm4  = xsqrtf(_mm512_add_ps(zmm1,zmm3));
                        _mm512_store_ps(&cabs[0],zmm4);
                 }


                  
                   __m512 cabs_zmm16r4(const __m512 re,
                                       const __m512 im) {

                        register __m512 zmm0,zmm1,cabs;
                        zmm0 = _mm512_mul_ps(re,re);
                        zmm1 = _mm512_mul_ps(im,im);
                        cabs = xsqrtf(_mm512_add_ps(zmm0,zmm1));
                        return (cabs);
                 }


              ////////////////////////////////////////////////////////////////////////////////


                 
                   void carg_zmm16r4_u(const float * __restrict re,
                                       const float * __restrict im,
                                       float * __restrict  carg) {

                        register __m512 zmm0,zmm1;
                        zmm0 = _mm512_loadu_ps(&re[0]);
                        zmm1 = _mm512_loadu_ps(&im[0]);
                        _mm512_storeu_ps(&carg[0], xatan2f(zmm0,zmm1));
                }


                  
                   void carg_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) re,
                                       const float * __restrict __attribute__((aligned(64))) im,
                                       float * __restrict  __attribute__((aligned(64))) carg) {

                        register __m512 zmm0,zmm1;
                        zmm0 = _mm512_load_ps(&re[0]);
                        zmm1 = _mm512_load_ps(&im[0]);
                        _mm512_store_ps(&carg[0], xatan2f(zmm0,zmm1));
                }


                 
                   __m512 carg_zmm16r4(const __m512 re,
                                       const __m512 im) {

                       register __m512 carg;
                       carg = xatan2f(re,im);
                       return (carg);
                }


             //////////////////////////////////////////////////////////////////////////////


                
                   void cconj_zmm16r4_u(const float * __restrict im,
                                        float * __restrict  conj) {

                        register __m512 zmm0;
                        const register __m512 none = _mm512_set1_ps(-1.0f);
                        zmm0 = _mm512_loadu_ps(&im[0]);
                        _mm512_storeu_ps(&conj[0], _mm512_mul_ps(none,zmm0));
               }  


                 
                   void cconj_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) im,
                                        float * __restrict  __attribute__((aligned(64))) conj) {

                        register __m512 zmm0;
                        const register __m512 none = _mm512_set1_ps(-1.0f);
                        zmm0 = _mm512_load_ps(&im[0]);
                        _mm512_store_ps(&conj[0], _mm512_mul_ps(none,zmm0));
               }  


                  
                   __m512 cconj_zmm16r4(const __m512 im) {
                          
                         const register __m512 none = _mm512_set1_ps(-1.0f);
                         register __m512 conj;
                         conj = _mm512_mul_ps(none,im);
                         return (conj); 
               }  


              //////////////////////////////////////////////////////////////////


                   void ccos_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict  csre,
                                       float * __restrict  csim) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xcosf(zmm0),xcoshf(zmm1));
                      _mm512_storeu_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xsinf(zmm0),xsinhf(zmm1));
                      _mm512_storeu_ps(&csim[0],zmm3);
               }


                 
                   void ccos_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict  __attribute__((aligned(64))) csre,
                                       float * __restrict  __attribute__((aligned(64))) csim) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_load_ps(&xre[0]);
                      zmm1  = _mm512_load_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xcosf(zmm0),xcoshf(zmm1));
                      _mm512_store_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xsinf(zmm0),xsinhf(zmm1));
                      _mm512_store_ps(&csim[0],zmm3);
               }


                
                   void ccos_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     __m512 * __restrict csre,
                                     __m512 * __restrict csim) {

                      register __m512 zmm0,zmm1;
                      zmm0  = _mm512_mul_ps(xcosf(xre),xcoshf(xim));
                      *csre = zmm0;
                      zmm1  = _mm512_mul_ps(xsinf(xre),xsinhf(xim));
                      *csim = zmm1; 
               }


               ////////////////////////////////////////////////////////////////////////////////


                void csin_zmm16r4_u(   const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict  csre,
                                       float * __restrict  csim)  {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xsinf(zmm0),xcoshf(zmm1));
                      _mm512_storeu_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xcosf(zmm0),xsinhf(zmm1));
                      _mm512_storeu_ps(&csim[0],zmm3);
               }


                void csin_zmm16r4_a(   const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict  __attribute__((aligned(64))) csre,
                                       float * __restrict  __attribute__((aligned(64))) csim)  {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_load_ps(&xre[0]);
                      zmm1  = _mm512_load_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xsinf(zmm0),xcoshf(zmm1));
                      _mm512_store_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xcosf(zmm0),xsinhf(zmm1));
                      _mm512_store_ps(&csim[0],zmm3);
               }


               void csin_zmm16r4(    const __m512 xre,
                                     const __m512 xim,
                                     __m512 * __restrict csre,
                                     __m512 * __restrict csim) {

                      register __m512 zmm0,zmm1;
                      zmm0  = _mm512_mul_ps(xsinf(xre),xcoshf(xim));
                      *csre = zmm0;
                      zmm1  = _mm512_mul_ps(xcosf(xre),xsinhf(xim));
                      *csim = zmm1; 
               }

            ///////////////////////////////////////////////////////////////////////


               void csinh_zmm16r4_u(   const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict  csre,
                                       float * __restrict  csim) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xsinhf(zmm0),xcosf(zmm1));
                      _mm512_storeu_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xcoshf(zmm0),xsinf(zmm1));
                      _mm512_storeu_ps(&csim[0],zmm3);
                }


               void csinh_zmm16r4_a(   const float * __restrict  __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict  __attribute__((aligned(64))) csre,
                                       float * __restrict  __attribute__((aligned(64))) csim) {


                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_load_ps(&xre[0]);
                      zmm1  = _mm512_load_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xsinhf(zmm0),xcosf(zmm1));
                      _mm512_store_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xcoshf(zmm0),xsinf(zmm1));
                      _mm512_store_ps(&csim[0],zmm3);
                }


               void csinh_zmm16r4(   const __m512 xre,
                                     const __m512 xim,
                                     __m512 * __restrict csre,
                                     __m512 * __restrict csim)  {

                      register __m512 zmm0,zmm1;
                      zmm0  = _mm512_mul_ps(xsinhf(xre),xcoshf(xim));
                      *csre = zmm0;
                      zmm1  = _mm512_mul_ps(xcoshf(xre),xsinhf(xim));
                      *csim = zmm1; 
                }

            ///////////////////////////////////////////////////////////////////////
                
                   void ccosh_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict  csre,
                                       float * __restrict  csim) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xcoshf(zmm0),xcosf(zmm1));
                      _mm512_storeu_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xsinhf(zmm0),xsinf(zmm1));
                      _mm512_storeu_ps(&csim[0],zmm3);
               }


                  
                   void ccosh_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict  __attribute__((aligned(64))) csre,
                                       float * __restrict  __attribute__((aligned(64))) csim) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0  = _mm512_load_ps(&xre[0]);
                      zmm1  = _mm512_load_ps(&xim[0]);
                      zmm2  = _mm512_mul_ps(xcoshf(zmm0),xcosf(zmm1));
                      _mm512_store_ps(&csre[0],zmm2);
                      zmm3  = _mm512_mul_ps(xsinhf(zmm0),xsinf(zmm1));
                      _mm512_store_ps(&csim[0],zmm3);
               }


                   
                   void ccosh_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     __m512 * __restrict csre,
                                     __m512 * __restrict csim) {

                      register __m512 zmm0,zmm1;
                      zmm0  = _mm512_mul_ps(xcoshf(xre),xcosf(xim));
                      *csre = zmm0;
                      zmm1  = _mm512_mul_ps(xsinhf(xre),xsinf(xim));
                      *csim = zmm1; 
               }


             ////////////////////////////////////////////////////////////////////////////////////


                 void cpow_zmm16r4_u(      const float * __restrict xre,
                                           const float * __restrict xim,
                                           const float n,
                                           float * __restrict powr,
                                           float * __restrict powi) {

                      register __m512 zmm0,zmm1,r,tht,vn,ptrm,targ,rep,imp;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      rep   = _mm512_mul_ps(zmm0,zmm0);
                      vn    = _mm512_set1_ps(n);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      imp   = _mm512_mul_ps(zmm1,zmm1);
                      r     = _mm512_sqrt_ps(_mm512_add_ps(rep,imp));
                      tht   = xatanf(_mm512_div_ps(zmm1,zmm0));
                      ptrm  = _mm512_pow_ps(r,vn);
                      targ  = _mm512_mul_ps(vn,tht);
                      _mm512_storeu_ps(&powr[0],_mm512_mul_ps(ptrm,xcosf(targ)));
                      _mm512_storeu_ps(&powi[0],_mm512_mul_ps(ptrm,xsinf(targ)));
                }


                   void cpow_zmm16r4_a(    const float * __restrict __attribute__((aligned(64)))  xre,
                                           const float * __restrict __attribute__((aligned(64)))  xim,
                                           const float n,
                                           float * __restrict __attribute__((aligned(64)))  powr,
                                           float * __restrict __attribute__((aligned(64)))  powi) {

                      register __m512 zmm0,zmm1,r,tht,vn,ptrm,targ,rep,imp;
                      zmm0  = _mm512_load_ps(&xre[0]);
                      rep   = _mm512_mul_ps(zmm0,zmm0);
                      vn    = _mm512_set1_ps(n);
                      zmm1  = _mm512_load_ps(&xim[0]);
                      imp   = _mm512_mul_ps(zmm1,zmm1);
                      r     = _mm512_sqrt_ps(_mm512_add_ps(rep,imp));
                      tht   = xatanf(_mm512_div_ps(zmm1,zmm0));
                      ptrm  = _mm512_pow_ps(r,vn);
                      targ  = _mm512_mul_ps(vn,tht);
                      _mm512_store_ps(&powr[0],_mm512_mul_ps(ptrm,xcosf(targ)));
                      _mm512_store_ps(&powi[0],_mm512_mul_ps(ptrm,xsinf(targ)));
                }


                 void cpow_zmm16r4(const __m512 xre,
                                   const __m512 xim,
                                   const float n,
                                   __m512 * __restrict powr,
                                   __m512 * __restrict powi) {

                      register __m512 r,tht,vn,ptrm,targ,rep,imp;
                      rep   = _mm512_mul_ps(xre,xre);
                      vn    = _mm512_set1_ps(n);
                      imp   = _mm512_mul_ps(xim,xim);
                      r     = _mm512_sqrt_ps(_mm512_add_ps(rep,imp));
                      tht   = xatanf(_mm512_div_ps(xim,xre));
                      ptrm  = _mm512_pow_ps(r,vn);
                      targ  = _mm512_mul_ps(vn,tht);
                      *powr = _mm512_mul_ps(ptrm,xcosf(targ));
                      *powi = _mm512_mul_ps(ptrm,xsinf(targ));
               }


             ////////////////////////////////////////////////////////////////////////////////////
 

                  void clog_zmm16r4_u(  const float * __restrict xre,
                                        const float * __restrict xim,
                                        float * __restrict logr,
                                        float * __restrict logi) {

                      register __m512 zmm0,zmm1,cabs,carg,rep;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      cabs  = cabs_zmm16r4(zmm0,zmm1);
                      carg  = carg_zmm16r4(zmm0,zmm1);
                      rep   = xlogf(cabs);
                      _mm512_storeu_ps(&logr[0],rep);
                      _mm512_storeu_ps(&logi[0],carg); 
               }


                   void clog_zmm16r4_u(  const float * __restrict __attribute__((aligned(64))) xre,
                                         const float * __restrict __attribute__((aligned(64))) xim,
                                         float * __restrict __attribute__((aligned(64))) logr,
                                         float * __restrict __attribute__((aligned(64))) logi) {

                      register __m512 zmm0,zmm1,cabs,carg,rep;
                      zmm0  = _mm512_loadu_ps(&xre[0]);
                      zmm1  = _mm512_loadu_ps(&xim[0]);
                      cabs  = cabs_zmm16r4(zmm0,zmm1);
                      carg  = carg_zmm16r4(zmm0,zmm1);
                      rep   = xlogf(cabs);
                      _mm512_storeu_ps(&logr[0],rep);
                      _mm512_storeu_ps(&logi[0],carg); 
               }


                   void clog_zmm16r4(    const __m512 xre,
                                         const __m512 xim,
                                         __m512 * __restrict logr,
                                         __m512 * __restrict logi) {

                      register __m512 cabs,carg,rep;
                      cabs  = cabs_zmm16r4(zmm0,zmm1);
                      carg  = carg_zmm16r4(zmm0,zmm1);
                      rep   = xlogf(cabs);
                      *logr = rep;
                      *logi = carg; 
               }


             ////////////////////////////////////////////////////////////////////////////////////


              
                   void ceq_zmm16r4_u(const float * __restrict xre,
                                      const float * __restrict xim,
                                      const float * __restrict yre,
                                      const float * __restrict yim,
                                      __mmask16 * __restrict eqr,
                                      __mmask16 * __restrict eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_loadu_ps(&xre[0]);
                      zmm1 = _mm512_loadu_ps(&yre[0]);
                      _mm512_storeu_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_EQ_OQ));
                      zmm2 = _mm512_loadu_ps(&xim[0]);
                      zmm3 = _mm512_loadu_ps(&yim[0]);
                      _mm512_storeu_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_EQ_OQ));
              }


                 
                   void ceq_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                      const float * __restrict __attribute__((aligned(64))) xim,
                                      const float * __restrict __attribute__((aligned(64))) yre,
                                      const float * __restrict __attribute__((aligned(64))) yim,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqr,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_load_ps(&xre[0]);
                      zmm1 = _mm512_load_ps(&yre[0]);
                      _mm512_store_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_EQ_OQ));
                      zmm2 = _mm512_load_ps(&xim[0]);
                      zmm3 = _mm512_load_ps(&yim[0]);
                      _mm512_store_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_EQ_OQ));
              }


                
                   void ceq_zmm16r4(const __m512 xre,
                                    const __m512 xim,
                                    const __m512 yre,
                                    const __m512 yim,
                                    __mmask16 * __restrict eqr,
                                    __mmask16 * __restrict eqi) {

                         *eqr = _mm512_cmp_ps_mask(xre,yre,_CMP_EQ_OQ);
                         *eqi = _mm512_cmp_ps_mask(xim,yim,_CMP_EQ_OQ);
              }


              ////////////////////////////////////////////////////////////////////
                  
                   void cgt_zmm16r4_u(const float * __restrict xre,
                                      const float * __restrict xim,
                                      const float * __restrict yre,
                                      const float * __restrict yim,
                                      __mmask16 * __restrict eqr,
                                      __mmask16 * __restrict eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_loadu_ps(&xre[0]);
                      zmm1 = _mm512_loadu_ps(&yre[0]);
                      _mm512_storeu_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_GT_OQ));
                      zmm2 = _mm512_loadu_ps(&xim[0]);
                      zmm3 = _mm512_loadu_ps(&yim[0]);
                      _mm512_storeu_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_GT_OQ));
              }


                 
                   void cgt_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                      const float * __restrict __attribute__((aligned(64))) xim,
                                      const float * __restrict __attribute__((aligned(64))) yre,
                                      const float * __restrict __attribute__((aligned(64))) yim,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqr,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_load_ps(&xre[0]);
                      zmm1 = _mm512_load_ps(&yre[0]);
                      _mm512_store_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_GT_OQ));
                      zmm2 = _mm512_load_ps(&xim[0]);
                      zmm3 = _mm512_load_ps(&yim[0]);
                      _mm512_store_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_GT_OQ));
              }


                 
                   void cgt_zmm16r4(const __m512 xre,
                                    const __m512 xim,
                                    const __m512 yre,
                                    const __m512 yim,
                                    __mmask16 * __restrict eqr,
                                    __mmask16 * __restrict eqi) {

                         *eqr = _mm512_cmp_ps_mask(xre,yre,_CMP_GT_OQ);
                         *eqi = _mm512_cmp_ps_mask(xim,yim,_CMP_GT_OQ);
              }


              //////////////////////////////////////////////////////////////////////////


                   void clt_zmm16r4_u(const float * __restrict xre,
                                      const float * __restrict xim,
                                      const float * __restrict yre,
                                      const float * __restrict yim,
                                      __mmask16 * __restrict eqr,
                                      __mmask16 * __restrict eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_loadu_ps(&xre[0]);
                      zmm1 = _mm512_loadu_ps(&yre[0]);
                      _mm512_storeu_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_LT_OQ));
                      zmm2 = _mm512_loadu_ps(&xim[0]);
                      zmm3 = _mm512_loadu_ps(&yim[0]);
                      _mm512_storeu_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_LT_OQ));
              }


               
                   void clt_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                      const float * __restrict __attribute__((aligned(64))) xim,
                                      const float * __restrict __attribute__((aligned(64))) yre,
                                      const float * __restrict __attribute__((aligned(64))) yim,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqr,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_load_ps(&xre[0]);
                      zmm1 = _mm512_load_ps(&yre[0]);
                      _mm512_store_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_LT_OQ));
                      zmm2 = _mm512_load_ps(&xim[0]);
                      zmm3 = _mm512_load_ps(&yim[0]);
                      _mm512_store_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_LT_OQ));
              }


                 
                   void clt_zmm16r4(const __m512 xre,
                                    const __m512 xim,
                                    const __m512 yre,
                                    const __m512 yim,
                                    __mmask16 * __restrict eqr,
                                    __mmask16 * __restrict eqi) {

                         *eqr = _mm512_cmp_ps_mask(xre,yre,_CMP_LT_OQ);
                         *eqi = _mm512_cmp_ps_mask(xim,yim,_CMP_LT_OQ);
              }


               /////////////////////////////////////////////////////////////////////


                 
                   void cneq_zmm16r4_u(const float * __restrict xre,
                                      const float * __restrict xim,
                                      const float * __restrict yre,
                                      const float * __restrict yim,
                                      __mmask16 * __restrict eqr,
                                      __mmask16 * __restrict eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_loadu_ps(&xre[0]);
                      zmm1 = _mm512_loadu_ps(&yre[0]);
                      _mm512_storeu_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_NEQ_OQ));
                      zmm2 = _mm512_loadu_ps(&xim[0]);
                      zmm3 = _mm512_loadu_ps(&yim[0]);
                      _mm512_storeu_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_NEQ_OQ));
              }


                 
                   void cneq_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                      const float * __restrict __attribute__((aligned(64))) xim,
                                      const float * __restrict __attribute__((aligned(64))) yre,
                                      const float * __restrict __attribute__((aligned(64))) yim,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqr,
                                      __mmask16 * __restrict __attribute__((aligned(64))) eqi ) {

                      register __m512 zmm0,zmm1,zmm2,zmm3;
                      zmm0 = _mm512_load_ps(&xre[0]);
                      zmm1 = _mm512_load_ps(&yre[0]);
                      _mm512_store_ps(&eqr[0],
                                       _mm512_cmp_ps_mask(zmm0,zmm1,_CMP_NEQ_OQ));
                      zmm2 = _mm512_load_ps(&xim[0]);
                      zmm3 = _mm512_load_ps(&yim[0]);
                      _mm512_store_ps(&eqi[0],
                                       _mm512_cmp_ps_mask(zmm2,zmm3,_CMP_NEQ_OQ));
              }


                  
                   void cneq_zmm16r4(const __m512 xre,
                                    const __m512 xim,
                                    const __m512 yre,
                                    const __m512 yim,
                                    __mmask16 * __restrict eqr,
                                    __mmask16 * __restrict eqi) {

                         *eqr = _mm512_cmp_ps_mask(xre,yre,_CMP_NEQ_OQ);
                         *eqi = _mm512_cmp_ps_mask(xim,yim,_CMP_NEQ_OQ);
              }


               ////////////////////////////////////////////////////////////////////////////


               
                   void cexp_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict cexpr,
                                       float * __restrict cexpi ) {

                        register const __m512 I = _mm512_set1_ps(1.0f);
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&xim[0]);
                        zmm2  = xexpf(zmm0);
                        zmm3  = _mm512_mul_ps(zmm2,xcosf(zmm1));
                        _mm512_storeu_ps(&cexpr[0],zmm3);
                        zmm4  = _mm512_mul_ps(zmm2,_mm512_mul_ps(xsinf(zmm1),I));
                        _mm512_storeu_ps(&cexpi[0],zmm4);
              }


                 
                   void cexp_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict __attribute__((aligned(64))) cexpr,
                                       float * __restrict __attribute__((aligned(64))) cexpi ) {

                        register const __m512 I = _mm512_set1_ps(1.0f);
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&xim[0]);
                        zmm2  = xexpf(zmm0);
                        zmm3  = _mm512_mul_ps(zmm2,xcosf(zmm1));
                        _mm512_store_ps(&cexpr[0],zmm3);
                        zmm4  = _mm512_mul_ps(zmm2,_mm512_mul_ps(xsinf(zmm1),I));
                        _mm512_store_ps(&cexpi[0],zmm4);
              }


                  
                   void cexp_zmm16r4(const __m512 xre,
                                     const __m512 xim,
                                     __m512 * __restrict cexpr,
                                     __m512 * __restrict cexpi) {

                        register const __m512 I = _mm512_set1_ps(1.0f);
                        register __m512 zmm0;
                        zmm0   = xexpf(xre);
                        *cexpr = _mm512_mul_ps(zmm0,xcosf(xim));
                        *cexpi = _mm512_mul_ps(zmm0,_mm512_mul_ps(xsinf(xim),I));
              }


               ////////////////////////////////////////////////////////////////////


              
                   void cpolar_zmm16r4_u(const float * __restrict rho,
                                         const float * __restrict tht,
                                         float * __restrict  re,
                                         float * __restrict  im) {

                         register __m512 zmm0,zmm1,zmm2,zmm3;
                         zmm0 = _mm512_loadu_ps(&rho[0]);
                         zmm1 = _mm512_loadu_ps(&tht[0]);
                         zmm2 = _mm512_mul_ps(zmm0,xcosf(zmm1)); //tht
                         _mm512_storeu_ps(&re[0],zmm2);
                         zmm3 = _mm512_mul_ps(zmm0,xsinf(zmm1)); //tht
                         _mm512_storeu_ps(&im[0],zmm3);
              }


                 
                   void cpolar_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) rho,
                                         const float * __restrict __attribute__((aligned(64))) tht,
                                         float * __restrict  __attribute__((aligned(64))) re,
                                         float * __restrict  __attribute__((aligned(64))) im) {

                         register __m512 zmm0,zmm1,zmm2,zmm3;
                         zmm0 = _mm512_load_ps(&rho[0]);
                         zmm1 = _mm512_load_ps(&tht[0]);
                         zmm2 = _mm512_mul_ps(zmm0,xcosf(zmm1)); //tht
                         _mm512_store_ps(&re[0],zmm2);
                         zmm3 = _mm512_mul_ps(zmm0,xsinf(zmm1)); //tht
                         _mm512_store_ps(&im[0],zmm3);
              }


                 
                   void cpolar_zmm16r4(const __m512 rho,
                                       const __m512 tht,
                                       __m512 * __restrict re,
                                       __m512 * __restrict im) {

                        register __m512 zmm0,zmm1;
                        zmm0 = _mm512_mul_ps(rho,xcosf(tht));
                        *re  = zmm0;
                        zmm1 = _mm512_mul_ps(rho,xsinf(tht));
                        *im  = zmm1;
              }


             ///////////////////////////////////////////////////////////////////////////


              
                   void csqrt_zmm16r4_u(const float * __restrict xre,
                                       const float * __restrict xim,
                                       float * __restrict wrkc,
                                       float * __restrict csqr,
                                       float * __restrict csqi) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        const register __m512 half = _mm512_set1_ps(0.5f);
                        cabs_zmm16r4_u(xre,xim,wrkc);
                        zmm0  = _mm512_loadu_ps(&xre[0]);
                        zmm1  = _mm512_loadu_ps(&wrkc[0]);
                        zmm2  = _mm512_mul_ps(half,_mm512_add_ps(zmm1,zmm0));
                        _mm512_storeu_ps(&csqr[0],_mm512_sqrt_ps(zmm2));
                        zmm3  = _mm512_mul_ps(half,_mm512_sub_ps(zmm1,zmm0));
                        _mm512_storeu_ps(&csqi[0],_mm512_sqrt_ps(zmm3));
              }


                 
                   void csqrt_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                       const float * __restrict __attribute__((aligned(64))) xim,
                                       float * __restrict __attribute__((aligned(64))) wrkc,
                                       float * __restrict __attribute__((aligned(64))) csqr,
                                       float * __restrict __attribute__((aligned(64))) csqi) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        const register __m512 half = _mm512_set1_ps(0.5f);
                        cabs_zmm16r4_a(xre,xim,wrkc);
                        zmm0  = _mm512_load_ps(&xre[0]);
                        zmm1  = _mm512_load_ps(&wrkc[0]);
                        zmm2  = _mm512_mul_ps(half,_mm512_add_ps(zmm1,zmm0));
                        _mm512_store_ps(&csqr[0],_mm512_sqrt_ps(zmm2));
                        zmm3  = _mm512_mul_ps(half,_mm512_sub_ps(zmm1,zmm0));
                        _mm512_store_ps(&csqi[0],_mm512_sqrt_ps(zmm3));
              }


                 
                   void csqrt_zmm16r4(const __m512 xre,
                                      const __m512 xim,
                                      __m512 * __restrict wrkc,
                                      __m512 * __restrict csqr,
                                      __m512 * __restrict csqi) {

                       register __m512 zmm0,zmm1;
                       const register __m512 half = _mm512_set1_ps(0.5f); 
                       cabs_zmm16r4(xre,xim,wrkc);
                       zmm0  = _mm512_mul_ps(half,_mm512_add_ps(*wrkc,xre));
                       *csqr = zmm0;
                       zmm1  = _mm512_mul_ps(half,_mm512_sub_ps(*wrkc,xre));
                       *csqi = zmm1; 
              }


               ////////////////////////////////////////////////////////////////////////////


              
                
                   void cnorm_prod_zmm16r4_u(const float * __restrict xre,
                                             const float * __restrict xim,
                                             const float * __restrict yre,
                                             const float * __restrict yim,
                                             float * __restrict zre,
                                             float * __restrict zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        imp  = _mm512_fmadd_pd(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        zmm0 = _mm512_mul_ps(rep,rep);
                        zmm1 = _mm512_mul_ps(imp,imp);
                        zmm2 = _mm512_sqrt_ps(_mm512_add_ps(zmm0,zmm1));
                        _mm512_storeu_ps(&zre[0], _mm512_div_ps(rep,zmm2));
                        _mm512_storeu_ps(&zim[0], _mm512_div_ps(imp,zmm2));
              }


                  
                   void cnorm_prod_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                             const float * __restrict __attribute__((aligned(64))) xim,
                                             const float * __restrict __attribute__((aligned(64))) yre,
                                             const float * __restrict __attribute__((aligned(64))) yim,
                                             float * __restrict __attribute__((aligned(64))) zre,
                                             float * __restrict __attribute__((aligned(64))) zim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        imp  = _mm512_fmadd_pd(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        zmm0 = _mm512_mul_ps(rep,rep);
                        zmm1 = _mm512_mul_ps(imp,imp);
                        zmm2 = _mm512_sqrt_ps(_mm512_add_ps(zmm0,zmm1));
                        _mm512_store_ps(&zre[0], _mm512_div_ps(rep,zmm2));
                        _mm512_store_ps(&zim[0], _mm512_div_ps(imp,zmm2));
              }


                
                   void cnorm_prod_zmm16r4(  const __m512  xre,
                                             const __m512  xim,
                                             const __m512  yre,
                                             const __m512  yim,
                                             __m512 * __restrict zre,
                                             __m512 * __restrict zim) {

                        register __m512 rep,imp,zmm0,zmm1,zmm2;
                        rep  = _mm512_fmsub_ps(xre,yre,
                                               _mm512_mul_ps(xim,yim));
                        imp  = _mm512_fmadd_pd(xim,yre,
                                               _mm512_mul_ps(xre,yim));
                        zmm0 = _mm512_mul_ps(rep,rep);
                        zmm1 = _mm512_mul_ps(imp,imp);
                        zmm2 = _mm512_sqrt_ps(_mm512_add_ps(zmm0,zmm1));
                        *zre = _mm512_div_ps(rep,zmm2);
                        *zim = _mm512_div_ps(imp,zmm2);
             }


               ///////////////////////////////////////////////////////////////////////////


            
                  
                   void cmean_prod_zmm16r4_u(const float * __restrict xre,
                                             const float * __restrict xim,
                                             const float * __restrict yre,
                                             const float * __restrict yim,
                                             float * __restrict mre,
                                             float * __restrict mim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        sre = 0.0f;
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        sre  = _mm512_reduce_ps(rep);
                        *mre = sre*inv16;
                        sim  = 0.0f;
                        imp  = _mm512_fmadd_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = _mm512_reduce_ps(imp);
                        *mim = sim*inv16;
              }


                
                   void cmean_prod_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                             const float * __restrict __attribute__((aligned(64))) xim,
                                             const float * __restrict __attribute__((aligned(64))) yre,
                                             const float * __restrict __attribute__((aligned(64))) yim,
                                             float * __restrict mre,
                                             float * __restrict mim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        sre = 0.0f;
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        sre  = _mm512_reduce_ps(rep);
                        *mre = sre*inv16;
                        sim  = 0.0f;
                        imp  = _mm512_fmadd_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = _mm512_reduce_ps(imp);
                        *mim = sim*inv16;
              } 


                 
                   void cmean_prod_zmm16r4(const __m512 xre,
                                           const __m512 xim,
                                           const __m512 yre,
                                           const __m512 yim,
                                           float * __restrict mre,
                                           float * __restrict min) {

                        register __m512 rep,imp;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        sre = 0.0f;
                        rep  = _mm512_fmsub_ps(xre,yre,
                                               _mm512_mul_ps(xim,yim));
                        sre  = _mm512_reduce_ps(rep);
                        *mre = sre*inv16;
                        sim  = 0.0f;
                        imp  = _mm512_fmadd_ps(xim,yre,
                                               _mm512_mul_ps(xre,yim));
                        sim  = _mm512_reduce_ps(imp);
                        *mim = sim*inv16;
             }


             ////////////////////////////////////////////////////////////////////////////


               
                   void cmean_quot_zmm16r4_u(const float * __restrict xre,
                                             const float * __restrict xim,
                                             const float * __restrict yre,
                                             const float * __restrict yim,
                                             float * __restrict mre,
                                             float * __restrict mim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp,den,rquot,iquot;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        sre  = 0.0f;
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        imp  = _mm512_fmadd_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = 0.0f;
                        den  = _mm512_fmadd_ps(zmm1,zmm1,
                                               _mm512_mul_ps(zmm3,zmm3));
                        rquot = _mm512_div_ps(rep,den);
                        sre   = _mm512_reduce_ps(rquot);
                        *mre  = sre*inv16;
                        iquot = _mm512_div_ps(imp,den);
                        sim   = _mm512_reduce_ps(iquot);
                        *mim  = sre*inv16;
              }  


                 
                   void cmean_quot_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                             const float * __restrict __attribute__((aligned(64))) xim,
                                             const float * __restrict __attribute__((aligned(64))) yre,
                                             const float * __restrict __attribute__((aligned(64))) yim,
                                             float * __restrict mre,
                                             float * __restrict mim) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp,den,rquot,iquot;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        sre  = 0.0f;
                        rep  = _mm512_fmsub_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        imp  = _mm512_fmadd_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = 0.0f;
                        den  = _mm512_fmadd_ps(zmm1,zmm1,
                                               _mm512_mul_ps(zmm3,zmm3));
                        rquot = _mm512_div_ps(rep,den);
                        sre   = _mm512_reduce_ps(rquot);
                        *mre  = sre*inv16;
                        iquot = _mm512_div_ps(imp,den);
                        sim   = _mm512_reduce_ps(iquot);
                        *mim  = sre*inv16;
              }  


                  
                   void cmean_quot_zmm16r4(  const __m512 xre,
                                             const __m512 xim,
                                             const __m512 yre,
                                             const __m512 yim,
                                             float * __restrict mre,
                                             float * __restrict mim) {

                        register __m512 rep,imp,den,rquot,iquot;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        sre  = 0.0f;
                        rep  = _mm512_fmsub_ps(xre,yre,
                                               _mm512_mul_ps(xim,yim));
                        imp  = _mm512_fmadd_ps(xim,yre,
                                               _mm512_mul_ps(xre,yim));
                        sim  = 0.0f;
                        den  = _mm512_fmadd_ps(yre,yre,
                                               _mm512_mul_ps(yim,yim));
                        rquot = _mm512_div_ps(rep,den);
                        sre   = _mm512_reduce_ps(rquot);
                        *mre  = sre*inv16;
                        iquot = _mm512_div_ps(imp,den);
                        sim   = _mm512_reduce_ps(iquot);
                        *mim  = sre*inv16;
              }  


               //////////////////////////////////////////////////////////////


                
                   void cnorm_cprod_zmm16r4_u(const float * __restrict xre,
                                              const float * __restrict xim,
                                              const float * __restrict yre,
                                              const float * __restrict yim,
                                              float * __restrict mre,
                                              float * __restrict mim ) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp,magc1,magc2,vcmag;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        rep  = _mm512_fmadd_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        magc1= _mm512_mul_ps(rep,rep);
                        imp  = _mm512_fmsub_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        magc2= _mm512_mul_ps(imp,imp);
                        vcmag= _mm512_sqrt_ps(_mm512_add_ps(magc1,magc2));
                        _mm512_storeu_ps(&mre[0], _mm512_div_ps(rep,vcmag));
                        _mm512_storeu_ps(&mim[0], _mm512_div_ps(imp,vcmag));
             }


                 
                   void cnorm_cprod_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                              const float * __restrict __attribute__((aligned(64))) xim,
                                              const float * __restrict __attribute__((aligned(64))) yre,
                                              const float * __restrict __attribute__((aligned(64))) yim,
                                              float * __restrict __attribute__((aligned(64))) mre,
                                              float * __restrict __attribute__((aligned(64))) mim ) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 rep,imp,magc1,magc2,vcmag;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        rep  = _mm512_fmad_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        magc1= _mm512_mul_ps(rep,rep);
                        imp  = _mm512_fmsub_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        magc2= _mm512_mul_ps(imp,imp);
                        vcmag= _mm512_sqrt_ps(_mm512_add_ps(magc1,magc2));
                        _mm512_store_ps(&mre[0], _mm512_div_ps(rep,vcmag));
                        _mm512_store_ps(&mim[0], _mm512_div_ps(imp,vcmag));
             }


                
                   void cnorm_cprod_zmm16r4(const __m512 xre,
                                            const __m512 xim,
                                            const __m512 yre,
                                            const __m512 yim,
                                            __m512 * __restrict mre,
                                            __m512 * __restrict mim) {

                        register __m512 rep,imp,magc1,magc2,vcmag;
                        rep  = _mm512_fmad_ps(xre,yre,
                                               _mm512_mul_ps(xim,yim));
                        magc1= _mm512_mul_ps(rep,rep);
                        imp  = _mm512_fmsub_ps(xim,yre,
                                               _mm512_mul_ps(xre,yim));
                        magc2= _mm512_mul_ps(imp,imp);
                        vcmag= _mm512_sqrt_ps(_mm512_add_ps(magc1,magc2));
                        *mre = _mm512_div_ps(rep,vcmag);
                        *mim = _mm512_div_ps(imp,vcmag)
             }


              ///////////////////////////////////////////////////////////////////


               
                   void cmean_cprod_zmm16r4_u(const float * __restrict xre,
                                              const float * __restrict xim,
                                              const float * __restrict yre,
                                              const float * __restrict yim,
                                              float * __restrict mre,
                                              float * __restrict mim) {
                      
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 re,im;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        re   = _mm512_fmadd_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        sre  = _mm512_reduce_ps(re);
                        *mre = sre*inv16;
                        im   = _mm512_fmsub_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = _mm512_reduce_ps(im);
                        *mim = sim*inv16;
             }


                  
                   void cmean_cprod_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                              const float * __restrict __attribute__((aligned(64))) xim,
                                              const float * __restrict __attribute__((aligned(64))) yre,
                                              const float * __restrict __attribute__((aligned(64))) yim,
                                              float * __restrict mre,
                                              float * __restrict mim) {
                      
                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 re,im;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        re   = _mm512_fmadd_ps(zmm0,zmm1,
                                               _mm512_mul_ps(zmm2,zmm3));
                        sre  = _mm512_reduce_ps(re);
                        *mre = sre*inv16;
                        im   = _mm512_fmsub_ps(zmm2,zmm1,
                                               _mm512_mul_ps(zmm0,zmm3));
                        sim  = _mm512_reduce_ps(im);
                        *mim = sim*inv16;
             }


                  
                   void cmean_cprod_zmm16r4(const __m512 xre,
                                            const __m512 xim,
                                            const __m512 yre,
                                            const __m512 yim,
                                            float * __restrict mre,
                                            float * __restrict min) {

                        register __m512 re,im;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        re   = _mm512_fmadd_ps(xre,yre,
                                               _mm512_mul_ps(xim,yim));
                        sre  = _mm512_reduce_ps(re);
                        *mre = sre*inv16;
                        im   = _mm512_fmsub_ps(xim,yre,
                                               _mm512_mul_ps(xre,yim));
                        sim  = _mm512_reduce_ps(im);
                        *mim = sim*inv16;
             }

                  
               /////////////////////////////////////////////////////////////////////


               
                   void arith_cmean_zmm16r4_u(const float * __restrict xre,
                                              const float * __restrict xim,
                                              float * __restrict mre,
                                              float * __restrict min) {

                        register __m512 re,im;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        re   = _mm512_loadu_ps(&xre[0]);
                        sre  = _mm512_reduce_ps(re);
                        *mre = sre*inv16;
                        im   = _mm512_loadu_ps(&xim[0]);
                        sim  = _mm512_reduce_ps(im);
                        *mim = sim*inv16; 
             }


                 
                   void arith_cmean_zmm16r4_a(const float * __restrict __attribute__((aligned(64))) xre,
                                              const float * __restrict __attribute__((aligned(64))) xim,
                                              float * __restrict mre,
                                              float * __restrict min) {

                        register __m512 re,im;
                        const float inv16 = 0.0625f;
                        float sre,sim;
                        re   = _mm512_load_ps(&xre[0]);
                        sre  = _mm512_reduce_ps(re);
                        *mre = sre*inv16;
                        im   = _mm512_load_ps(&xim[0]);
                        sim  = _mm512_reduce_ps(im);
                        *mim = sim*inv16; 
             }


                 
                   void arith_cmean_zmm16r4(  const __m512 xre,
                                              const __m512 xim,
                                              float * __restrict mre,
                                              float * __restrict min) {

                        const float inv16 = 0.0625f;
                        float sre,sim;
                        sre  = _mm512_reduce_ps(xre);
                        *mre = sre*inv16;
                        sim  = _mm512_reduce_ps(xim);
                        *mim = sim*inv16; 
             }


              ///////////////////////////////////////////////////////////////////////////


              
                   void cnormalize_zmm16r4_u( const float * __restrict xre,
                                              const float * __restrict xim,
                                              const float * __restrict yre,
                                              const float * __restrict yim,
                                              float * __restrict mre,
                                              float * __restrict mim ) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 re,im,cvmag;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(zmm0,zmm1,
                                                              _mm512_mul_ps(zmm2,zmm3)));
                        _mm512_storeu_ps(&mre[0], _mm512_div_ps(zmm0,cvmag));
                        _mm512_storeu_ps(&mim[0], _mm512_div_ps(zmm2,cvmag));
             }


                  
                   void cnormalize_zmm16r4_a( const float * __restrict __attribute__((aligned(64))) xre,
                                              const float * __restrict __attribute__((aligned(64))) xim,
                                              const float * __restrict __attribute__((aligned(64))) yre,
                                              const float * __restrict __attribute__((aligned(64))) yim,
                                              float * __restrict __attribute__((aligned(64))) mre,
                                              float * __restrict __attribute__((aligned(64))) mim ) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 re,im,cvmag;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(zmm0,zmm1,
                                                              _mm512_mul_ps(zmm2,zmm3)));
                        _mm512_store_ps(&mre[0], _mm512_div_ps(zmm0,cvmag));
                        _mm512_store_ps(&mim[0], _mm512_div_ps(zmm2,cvmag));
             }


                
                   void cnormalize_zmm16r4( const __m512 xre,
                                            const __m512 xim,
                                            const __m512 yre,
                                            const __m512 yim,
                                            __m512 * __restrict mre,
                                            __m512 * __restrict mim ) {

                        register __m512 re,im,cvmag;
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(xre,yre,
                                                    _mm512_mul_ps(xim,yim)));
                        *mre = _mm512_div_ps(xre,cvmag));
                        *mim =  _mm512_div_ps(xim,cvmag));
             }


                
                   void cmagnitude_zmm16r4_u( const float * __restrict xre,
                                              const float * __restrict xim,
                                              const float * __restrict yre,
                                              const float * __restrict yim,
                                              float * __restrict mre) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 cvmag;
                        zmm0 = _mm512_loadu_ps(&xre[0]);
                        zmm1 = _mm512_loadu_ps(&yre[0]);
                        zmm2 = _mm512_loadu_ps(&xim[0]);
                        zmm3 = _mm512_loadu_ps(&yim[0]);
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(zmm0,zmm1,
                                                          _mm512_mul_ps(zmm2,zmm3)));
                        _mm512_storeu_ps(&mre[0], cvmag);
             }


                 
                   void cmagnitude_zmm16r4_a( const float * __restrict __attribute__((aligned(64))) xre,
                                              const float * __restrict __attribute__((aligned(64))) xim,
                                              const float * __restrict __attribute__((aligned(64))) yre,
                                              const float * __restrict __attribute__((aligned(64))) yim,
                                              float * __restrict __attribute__((aligned(64))) mre) {

                        register __m512 zmm0,zmm1,zmm2,zmm3;
                        register __m512 cvmag;
                        zmm0 = _mm512_load_ps(&xre[0]);
                        zmm1 = _mm512_load_ps(&yre[0]);
                        zmm2 = _mm512_load_ps(&xim[0]);
                        zmm3 = _mm512_load_ps(&yim[0]);
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(zmm0,zmm1,
                                                          _mm512_mul_ps(zmm2,zmm3)));
                        _mm512_store_ps(&mre[0], cvmag);
             }


                   
                   void cmagnitude_zmm16r4(   const __m512 xre,
                                              const __m512 xim,
                                              const __m512 yre,
                                              const __m512 yim,
                                              __m512 * __restrict  mre) {

                        register __m512 cvmag;
                        cvmag= _mm512_sqrt_ps(_mm512_fmadd_ps(xre,yre,
                                                          _mm512_mul_ps(xim,yim)));
                        *mre = cvmag;
             }



     





  





  
 




   





















