




/*MIT License
Copyright (c) 2020 Bernard Gingold
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/



#include "GMS_rcs_ellips_ogive_zmm16r4.h"
#include "GMS_sleefsimdsp.hpp"
#include "GMS_complex_zmm16r4.hpp"




                      /*
                            High-frequency cross-section of perfectly
                            conducting ellipsoid.
                            Bistatic case.
                            Formula 5.1.54
                        */


                  
                   __m512 rcs_f5154_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 c,
                                            const __m512 th1,
                                            const __m512 phi1,
                                            const __m512 th2,
                                            const __m512 phi2) {

                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5154_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pc,
                                            const float * __restrict __ATTR_ALIGN__(64) pth1,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                            const float * __restrict __ATTR_ALIGN__(64) pth2,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi2) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 th1 = _mm512_load_ps(&pth1[0]);
                          register __m512 phi1= _mm512_load_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_load_ps(&pth2[0]);
                          register __m512 phi2= _mm512_load_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                  
                   __m512 rcs_f5154_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pc,
                                            const float * __restrict  pth1,
                                            const float * __restrict  pphi1,
                                            const float * __restrict  pth2,
                                            const float * __restrict  pphi2) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 th1 = _mm512_loadu_ps(&pth1[0]);
                          register __m512 phi1= _mm512_loadu_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_loadu_ps(&pth2[0]);
                          register __m512 phi2= _mm512_loadu_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                       /*
                            High-frequency cross-section of perfectly
                            conducting ellipsoid.
                            Backscattering case.
                            Formula 5.1.55
                        */ 

                   __m512 rcs_f5155_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 c,
                                            const __m512 th,
                                            const __m512 phi) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                   __m512 rcs_f5155_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) pth,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi) {
                                           
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 th  = _mm512_load_ps(&pth[0]);
                          register __m512 phi = _mm512_load_ps(&pphi[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                   __m512 rcs_f5155_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pb,
                                              const float * __restrict  pc,
                                              const float * __restrict  pth,
                                              const float * __restrict  pphi) {
                                           
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 th  = _mm512_loadu_ps(&pth[0]);
                          register __m512 phi = _mm512_loadu_ps(&pphi[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                    /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Bistatic case.
                           Formula 5.1-67
                        */

              
                   __m512 rcs_f5167_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 th1,
                                            const __m512 phi1,
                                            const __m512 th2,
                                            const __m512 phi2) {

                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                   __m512 rcs_f5167_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pth1,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                              const float * __restrict __ATTR_ALIGN__(64) pth2,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi2) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 th1 = _mm512_load_ps(&pth1[0]);
                          register __m512 phi1= _mm512_load_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_load_ps(&pth2[0]);
                          register __m512 phi2= _mm512_load_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5167_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pb,
                                              const float * __restrict  pth1,
                                              const float * __restrict  pphi1,
                                              const float * __restrict  pth2,
                                              const float * __restrict  pphi2) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 th1 = _mm512_loadu_ps(&pth1[0]);
                          register __m512 phi1= _mm512_loadu_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_loadu_ps(&pth2[0]);
                          register __m512 phi2= _mm512_loadu_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                  /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Backscatter case.
                           Formula 5.1-68
                     */


                 
                   __m512 rcs_f5168_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 phi) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                 
                   __m512 rcs_f5168_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 phi = _mm512_load_ps(&pph1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                   __m512 rcs_f5168_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pphi) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 phi = _mm512_loadu_ps(&pph1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                    /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Incidence along a the major axis -- the backscatter RCS.
                           Formula 5.1-69
                     */


               
                   __m512 rcs_f5169_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


               
                   __m512 rcs_f5169_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                
                   __m512 rcs_f5169_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict pb,
                                            const float * __restrict  pk0) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                  /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Incidence along a the minor axis -- the backscatter RCS.
                           Formula 5.1-70

                    */


                   __m512 rcs_f5170_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                   
                   __m512 rcs_f5170_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                  
                   __m512 rcs_f5170_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pk0) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                   /*
                         Oblate spheroids.
                         Low frequency solutions.
                         Helper parameters: Ia,Ib
                         Formula 5.1-91
                     */


                
                   __m512 IaIb_f5191_zmm16r4(const __m512 a,
                                             const __m512 c) {

                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                
                   __m512 IaIb_f5191_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                               const float * __restrict __ATTR_ALIGN__(64) pc) {

                          register __m512 a = _mm512_load_ps(&pa[0]);
                          register __m512 c = _mm512_load_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                  
                   __m512 IaIb_f5191_zmm16r4_u(const float * __restrict  pa,
                                               const float * __restrict  pc) {

                          register __m512 a = _mm512_loadu_ps(&pa[0]);
                          register __m512 c = _mm512_loadu_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                     /*
                         Oblate spheroids.
                         Low frequency solutions.
                         Helper parameters: Ia,Ib
                         Formula 5.1-92
                     */


              
                   __m512 Ic_f5192_zmm16r4(const __m512 a,
                                             const __m512 c) {

                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                  
                   __m512 Ic_f5192_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                           const float * __restrict __ATTR_ALIGN__(64) pc) {

                          register __m512 a = _mm512_load_ps(&pa[0]);
                          register __m512 c = _mm512_load_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                 
                   __m512 Ic_f5192_zmm16r4_u(const float * __restrict  pa,
                                           const float * __restrict  pc) {

                          register __m512 a = _mm512_loadu_ps(&pa[0]);
                          register __m512 c = _mm512_loadu_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                   /*
                         Oblate spheroids (perfectly conducting);
                         Low frequency solutions.
                         Backscatter RCS.
                         Formula 5.1-89
                     */


                 
                   __m512 rcs_f5189_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht,
                                            const __m512 k0) {

                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5189_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0 ) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                  
                   __m512 rcs_f5189_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pc,
                                              const float * __restrict  ptht,
                                              const float * __restrict  pk0 ) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                     /*
                         Oblate spheroids (perfectly conducting);
                         Low frequency solutions.
                         Backscatter RCS.
                         Formula 5.1-90
                     */


                
                   __m512 rcs_f5190_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht,
                                            const __m512 k0) {

                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,strm,trm1,IaIc,x1,inv;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          inv  = _mm512_rcp14_ps(IaIc);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          trm2 = _mm512_div_ps(ctht2,Ia);
                          trm3 = _mm512_div_ps(stht3,Ic);
                          strm = _mm512_add_ps(trm2,trm3);
                          x1   = _mm512_mul_ps(strm,strm);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 } 


                  
                   __m512 rcs_f5190_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,strm,trm1,IaIc,x1,inv;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          inv  = _mm512_rcp14_ps(IaIc);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          trm2 = _mm512_div_ps(ctht2,Ia);
                          trm3 = _mm512_div_ps(stht3,Ic);
                          strm = _mm512_add_ps(trm2,trm3);
                          x1   = _mm512_mul_ps(strm,strm);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 } 


                   /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          E-field (theta), perpendicular, formula 5.1-83
                    */

                
                   void ESth_f5183_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht2,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
                }


                 
                   void ESth_f5183_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_load_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_load_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1,resr,resi;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht2,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
                }


                
                   void ESth_f5183_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  ESr,
                                          float * __restrict  ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_loadu_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_loadu_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1,resr,resi;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht2,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_storeu_ps(&ESr[0], resr);
                       _mm512_storeu_ps(&ESi[0], resi);
                }


                  /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          H-field (phi), perpendicular formula 5.1-83
                    */


                   void HSph_f5183_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict HSr,
                                          __m512 * __restrict HSi) {

                    ESth_f5183_zmm16r4(k0,r,epsr,epsi,mur,mui,a,
                                       c,tht1,tht2,phi2,*HSr,*HSi);
               }


                  
                   void HSph_f5183_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) HSr,
                                          float * __restrict __ATTR_ALIGN__(64) HSi) {

                         ESth_f5183_zmm16r4_a(pk0,pr,pepsr,pepsi,pmur,pmui,
                                              pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                
                   void HSph_f5183_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  HSr,
                                          float * __restrict  HSi) {

                         ESth_f5183_zmm16r4_u(pk0,pr,pepsr,pepsi,pmur,pmui,
                                              pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                 /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          E-field (phi), perpendicular formula 5.1-84

                    */


                 
                   void ESph_f5184_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(cphi2,den1r);
                       t1r    = _mm512_div_ps(x0,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       t2r    = _mm512_div_ps(x1,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0i    = _mm512_div_ps(cphi2,den1i);
                       t1i    = _mm512_div_ps(x0,den2i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       t2i    = _mm512_div_ps(x1,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_sub_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_sub_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
                }


                
                   void ESph_f5184_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_load_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_load_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci,resr,resi;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(cphi2,den1r);
                       t1r    = _mm512_div_ps(x0,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       t2r    = _mm512_div_ps(x1,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0i    = _mm512_div_ps(cphi2,den1i);
                       t1i    = _mm512_div_ps(x0,den2i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       t2i    = _mm512_div_ps(x1,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_sub_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_sub_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
                }


                 
                   void ESph_f5184_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict pr,
                                          const float * __restrict pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  ESr,
                                          float * __restrict  ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_loadu_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_load_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci,resr,resi;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(cphi2,den1r);
                       t1r    = _mm512_div_ps(x0,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       t2r    = _mm512_div_ps(x1,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0i    = _mm512_div_ps(cphi2,den1i);
                       t1i    = _mm512_div_ps(x0,den2i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       t2i    = _mm512_div_ps(x1,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_sub_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_sub_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_storeu_ps(&ESr[0], resr);
                       _mm512_storeu_ps(&ESi[0], resi);
                }


                  /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          H-field (theta), perpendicular formula 5.1-84
                    */


                 
                   void HSth_f5184_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict HSr,
                                          __m512 * __restrict HSi) {

                        ESph_f5184_zmm16r4(k0,r,epsr,epsi,mur,mui,
                                           a,c,tht1,tht2,phi2,*HSr,*HSi);
                  }


                
                   void HSph_f5184_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) HSr,
                                          float * __restrict __ATTR_ALIGN__(64) HSi) {

                         ESph_f5184_zmm16r4_a(pk0,pr,pepsr,pepsi,pmur,pmui,
                                              pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                 
                   void HSph_f5184_zmm16r4_u(const float * __restrict pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  HSr,
                                          float * __restrict  HSi) {

                         ESph_f5184_zmm16r4_u(pk0,pr,pepsr,pepsi,pmur,pmui,
                                              pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                     /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          E-field (theta), parallel, formula 5.1-85

                    */


                 
                   void ESth_f5185_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t2r    = _mm512_div_ps(cphi2,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t2i    = _mm512_div_ps(cphi2,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_add_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_add_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
                }


                 
                   void ESth_f5185_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_load_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_load_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci,resr,resi;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t2r    = _mm512_div_ps(cphi2,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t2i    = _mm512_div_ps(cphi2,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_add_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_add_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
                }


                
                   void ESth_f5185_zmm16r4_u(const float * __restrict pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  ESr,
                                          float * __restrict  ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_loadu_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_loadu_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht1,ctht2,facr,faci,resr,resi;
                       register __m512 sth2,sth1,ear,eai,cer,cei,epsrm1,epsim1,cphi2,t2r,t2i;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c,den3r,den3i;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i,mul3r,mul3i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       cphi2  = xcosf(phi2);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       sth2   = xsinf(tht2);
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(cth1,_mm512_mul_ps(ctht2,cphi2));
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(stht1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       t2r    = _mm512_div_ps(cphi2,den3r);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t1r,t1i,&mul2r,&mul2i);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t2i    = _mm512_div_ps(cphi2,den3i);
                       cmul_zmm16r4(murm1,muim1,t2r,t2i,&mul3r,&mul3i);
                       t0r = _mm512_add_ps(mul1r,_mm512_sub_ps(mul2r,mul3r));
                       t0i = _mm512_add_ps(mul1i,_mm512_sub_ps(mul2i,mul3i));
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
                }


                   /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          H-field (phi), parallel, formula 5.1-85

                    */



                  
                   void HSph_f5185_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict HSr,
                                          __m512 * __restrict HSi) {

                        ESth_f5185_zmm16r4(k0,r,epsr,epsi,mur,mui,
                                           a,c,tht1,tht2,phi2,*HSr,*HSi);
               }


                  
                   void HSph_f5185_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pr,
                                             const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                             const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                             const float * __restrict __ATTR_ALIGN__(64) pmur,
                                             const float * __restrict __ATTR_ALIGN__(64) pmui,
                                             const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pc,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                             const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                             float * __restrict __ATTR_ALIGN__(64) HSr,
                                             float * __restrict __ATTR_ALIGN__(64) HSi) {

                       ESth_f5185_zmm16r4_a(pk0,pr,pepsr,pepsi,pmur,pmui,
                                            pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                 
                   void HSph_f5185_zmm16r4_u(const float * __restrict pk0,
                                             const float * __restrict  pr,
                                             const float * __restrict  pepsr,
                                             const float * __restrict  pepsi,
                                             const float * __restrict  pmur,
                                             const float * __restrict  pmui,
                                             const float * __restrict  pa,
                                             const float * __restrict  pc,
                                             const float * __restrict  ptht1,
                                             const float * __restrict  ptht2,
                                             const float * __restrict  pphi2,
                                             float * __restrict  HSr,
                                             float * __restrict  HSi) {

                       ESth_f5185_zmm16r4_u(pk0,pr,pepsr,pepsi,pmur,pmui,
                                            pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
                }


                  /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          E-field (phi), parallel, formula 5.1-86


                     */


                   void ESph_f5186_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(-0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht1,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht2,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
                }


                 
                   void ESph_f5186_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_load_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_load_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(-0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1,resr,resi;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht1,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht2,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
                }


                  
                   void ESph_f5186_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  ESr,
                                          float * __restrict _ ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht1[0]); 
                       register __m512  tht2  = _mm512_loadu_ps(&ptht2[0]);
                       register __m512  phi2  = _mm512_loadu_ps(&pphi2[0]);
                       const __m512 _23 = _mm512_set1_ps(-0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,a2c,ctht1,ctht2,facr,faci;
                       register __m512 sph2,ear,eai,cer,cei,epsrm1,epsim1,resr,resi;
                       register __m512 murm1,muim1,x0,x1,t0r,t0i,t1r,t1i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,mul1r,mul1i,mul2r,mul2i;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht2  = xcosf(tht2);
                       murm1  = _mm512_sub_ps(mur,_1)
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht2  = xsinf(tht2);
                       k0r    = _mm512_mul_ps(k0,r);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ctht1  = xcosf(tht1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       x0     = _mm512_mul_ps(ctht1,stht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       x1     = _mm512_mul_ps(ctht2,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       t0r    = _mm512_div_ps(x0,den1r);
                       t1r    = _mm512_div_ps(x1,den2r);
                       t0i    = _mm512_div_ps(x0,den1i);
                       t1i    = _mm512_div_ps(x1,den2i);
                       cmul_zmm16r4(epsrm1,epsim1,t0r,t0i,&mul1r,&mul1i);
                       cmul_zmm16r4(murm1,muim1,t1r,t1i,&mul2r,&mul2i);
                       t0r = _mm512_sub_ps(mul1r,mul2r);
                       t0i = _mm512_sub_ps(mul1i,mul2i);
                       cmul_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_storeu_ps(&ESr[0], resr);
                       _mm512_storeu_ps(&ESi[0], resi);
                }


                      /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          H-field (theta), parallel, formula 5.1-86


                     */


                 
                   void HSth_f5186_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht1,
                                          const __m512 tht2,
                                          const __m512 phi2,
                                          __m512 * __restrict HSr,
                                          __m512 * __restrict HSi) {

                        ESph_f5186_zmm16r4(k0,r,epsr,epsi,mur,mui,
                                           a,c,tht1,tht2,phi3,*HSr,*HSi);
                }


                
                   void HSth_f5186_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                          const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                          float * __restrict __ATTR_ALIGN__(64) HSr,
                                          float * __restrict __ATTR_ALIGN__(64) HSi) {

                        ESph_f5186_zmm16r4_a(pk0,pr,pepsr,pepsi,pmur,pmui,
                                             pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
               }


                 
                   void HSth_f5186_zmm16r4_u(const float * __restrict pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht1,
                                          const float * __restrict  ptht2,
                                          const float * __restrict  pphi2,
                                          float * __restrict  HSr,
                                          float * __restrict  HSi) {

                        ESph_f5186_zmm16r4_u(pk0,pr,pepsr,pepsi,pmur,pmui,
                                             pa,pc,ptht1,ptht2,pphi2,HSr,HSi);
               }


                    /*
                          Low-frequency oblate spheroid Rayleigh
                          Backscattered fields.
                          E-field (phi), perpendicular, formula 5.1-87         
 
                     */


                  
                   void ESph_f5187_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(murm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(murm1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       num1i  = _mm512_mul_ps(muim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(muim1,stht2);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       cdiv_zmm16r4(epsrm1,epsim1,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num1r,num1i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(num2r,num2i,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_sub_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_sub_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
               }


                 
                   void ESph_f5187_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht[0]); 
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c,resr,resi;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(murm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(murm1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       num1i  = _mm512_mul_ps(muim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(muim1,stht2);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       cdiv_zmm16r4(epsrm1,epsim1,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num1r,num1i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(num2r,num2i,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_sub_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_sub_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
               }

              
                 
                   void ESph_f5187_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict  pepsi,
                                          const float * __restrict pmur,
                                          const float * __restrict  pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht,
                                          float * __restrict  ESr,
                                          float * __restrict  ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht[0]); 
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c,resr,resi;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(murm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(murm1,stht2);
                       den2r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ic,_2a2c);
                       num1i  = _mm512_mul_ps(muim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(muim1,stht2);
                       den2i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ic,_2a2c);
                       cdiv_zmm16r4(epsrm1,epsim1,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num1r,num1i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(num2r,num2i,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_sub_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_sub_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_storeu_ps(&ESr[0], resr);
                       _mm512_storeu_ps(&ESi[0], resi);
               }



                   /*
                          Low-frequency oblate spheroid Rayleigh
                          Backscattered fields.
                          E-field (theta), parallel, formula 5.1-88         
 
                     */


                  
                   void ESth_f5188_zmm16r4(const __m512 k0,
                                          const __m512 r,
                                          const __m512 epsr,
                                          const __m512 epsi,
                                          const __m512 mur,
                                          const __m512 mui,
                                          const __m512 a,
                                          const __m512 c,
                                          const __m512 tht,
                                          __m512 * __restrict ESr,
                                          __m512 * __restrict ESi) {

                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(epsrm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(epsrm1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       num1i  = _mm512_mul_ps(epsim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(epsim1,stht2);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       cdiv_zmm16r4(num1r,num1i,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num2r,num2i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(murm1,muim1,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_add_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_add_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,*ESr,*ESi);
               }


                 
                   void ESth_f5188_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                          const float * __restrict __ATTR_ALIGN__(64) pr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui,
                                          const float * __restrict __ATTR_ALIGN__(64) pa,
                                          const float * __restrict __ATTR_ALIGN__(64) pc,
                                          const float * __restrict __ATTR_ALIGN__(64) ptht,
                                          float * __restrict __ATTR_ALIGN__(64) ESr,
                                          float * __restrict __ATTR_ALIGN__(64) ESi) {

                       register __m512  k0    = _mm512_load_ps(&pk0[0]);
                       register __m512  r     = _mm512_load_ps(&pr[0]);
                       register __m512  epsr  = _mm512_load_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_load_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_load_ps(&pmur[0]);
                       register __m512  mui   = _mm512_load_ps(&pmui[0]);
                       register __m512  a     = _mm512_load_ps(&pa[0]);
                       register __m512  c     = _mm512_load_ps(&pc[0]);
                       register __m512  tht1  = _mm512_load_ps(&ptht[0]); 
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c,resr,resi;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(epsrm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(epsrm1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       num1i  = _mm512_mul_ps(epsim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(epsim1,stht2);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       cdiv_zmm16r4(num1r,num1i,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num2r,num2i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(murm1,muim1,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_add_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_add_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_store_ps(&ESr[0], resr);
                       _mm512_store_ps(&ESi[0], resi);
               }


                  
                   void ESth_f5188_zmm16r4_u(const float * __restrict  pk0,
                                          const float * __restrict  pr,
                                          const float * __restrict  pepsr,
                                          const float * __restrict pepsi,
                                          const float * __restrict  pmur,
                                          const float * __restrict pmui,
                                          const float * __restrict  pa,
                                          const float * __restrict  pc,
                                          const float * __restrict  ptht,
                                          float * __restrict  ESr,
                                          float * __restrict  ESi) {

                       register __m512  k0    = _mm512_loadu_ps(&pk0[0]);
                       register __m512  r     = _mm512_loadu_ps(&pr[0]);
                       register __m512  epsr  = _mm512_loadu_ps(&pepsr[0]);
                       register __m512  epsi  = _mm512_loadu_ps(&pepsi[0]);
                       register __m512  mur   = _mm512_loadu_ps(&pmur[0]);
                       register __m512  mui   = _mm512_loadu_ps(&pmui[0]);
                       register __m512  a     = _mm512_loadu_ps(&pa[0]);
                       register __m512  c     = _mm512_loadu_ps(&pc[0]);
                       register __m512  tht1  = _mm512_loadu_ps(&ptht[0]); 
                       const __m512 _23 = _mm512_set1_ps(0.666666666666666666666666666667f);
                       const __m512 _1  = _mm512_set1_ps(1.0f);
                       const __m512 _2  = _mm512_set1_ps(2.0f);
                       const __m512 _0  = _mm512_setzero_ps();
                       register __m512 k02,a2,invr,Ia,Ic,a2c,ctht,stht,facr,faci;
                       register __m512 ear,eai,cer,cei,epsrm1,epsim1,t2r,t2i,den3r,den3i;
                       register __m512 murm1,muim1,x0,t0r,t0i,_2a2c,resr,resi;
                       register __m512 den1r,den1i,den2r,den2i,div1r,div1i,div2r,div2i,div3r,div3i;
                       register __m512 num1r,num1i,num2r,num2i,ctht2,stht2;
                       epsrm1 = _mm512_sub_ps(epsr,_1);
                       k02    = _mm512_mul_ps(k0,k0);
                       ctht   = xcosf(tht);
                       murm1  = _mm512_sub_ps(mur,_1)
                       ctht2  = _mm512_mul_ps(ctht,ctht);
                       invr   = _mm512_rcp14_ps(r);
                       epsim1 = _mm512_sub_ps(epsi,_1);
                       stht   = xsinf(tht);
                       k0r    = _mm512_mul_ps(k0,r);
                       stht2  = _mm512_mul_ps(stht,stht);
                       muim1  = _mm512_sub_ps(mui,_1);
                       ear    = _0;
                       x0     = _mm512_mul_ps(_23,k02);
                       eai    = k0r;
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       Ia     = IaIb_f5191_zmm16r4(a,c);
                       facr   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cer));
                       a2c    = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                       faci   = _mm512_mul_ps(x0,_mm512_mul_ps(invr,cei));
                       _2a2c  = _mm512_div_ps(_2,a2c);
                       Ic     = Ic_f5192_zmm16r4(a,c);
                       num1r  = _mm512_mul_ps(epsrm1,ctht2);
                       den1r  = _mm512_fmadd_ps(epsrm1,Ia,_2a2c);
                       num2r  = _mm512_mul_ps(epsrm1,stht2);
                       den2r  = _mm512_fmadd_ps(epsrm1,Ic,_2a2c);
                       den3r  = _mm512_fmadd_ps(murm1,Ia,_2a2c);
                       num1i  = _mm512_mul_ps(epsim1,ctht2);
                       den1i  = _mm512_fmadd_ps(epsim1,Ia,_2a2c);
                       num2i  = _mm512_mul_ps(epsim1,stht2);
                       den2i  = _mm512_fmadd_ps(epsim1,Ic,_2a2c);
                       den3i  = _mm512_fmadd_ps(muim1,Ia,_2a2c);
                       cdiv_zmm16r4(num1r,num1i,den1r,den1i,&div1r,&div1i);
                       cdiv_zmm16r4(num2r,num2i,den2r,den2i,&div2r,&div2i);
                       cdiv_zmm16r4(murm1,muim1,den3r,den3i,&div2r,&div2i);
                       t0r = _mm512_add_ps(div1r,_mm512_sub_ps(div2r,div3r));
                       t0r = _mm512_add_ps(div1i,_mm512_sub_ps(div2i,div3i));
                       cexp_zmm16r4(facr,faci,t0r,t0i,&resr,&resi);
                       _mm512_storeu_ps(&ESr[0], resr);
                       _mm512_storeu_ps(&ESi[0], resi);
               }


                    /*
                          High-frequency solutions.
                          Bistatic case RCS of oblate spheroid.
                          Formula 5.1-93
                      */


                 
                   __m512 rcs_f5193_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht1,
                                            const __m512 tht2,
                                            const __m512 phi2) {

                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,num,a4,a2,c2,den,sden,trm1,trm2,trm3;
                          register __m512 stht1,stht2,cphi2,ctht1,ctht2,sphi2,strm1,strm2,strm3;
                          stht1 = xsinf(tht1);
                          a2    = _mm512_mul_ps(a,a);
                          cphi2 = xcosf(phi2);
                          c2    = _mm512_mul_ps(c,c);
                          ctht1 = xcosf(tht1);
                          a4    = _mm512_mul_ps(a2,a2);
                          ctht2 = xcosf(tht2);
                          num   = _mm512_mul_ps(_4pi,_mm512_mul_ps(a4,c2));
                          sphi2 = xsinf(phi2);
                          stht2 = xsinf(tht2);
                          trm1  = _mm512_fmadd_ps(stht2,cphi2,stht1);
                          strm1 = _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          trm2  = _mm512_mul_ps(stht2,sphi2);
                          strm2 = _mm512_mul_ps(a2,_mm512_mul_ps(trm2,trm2));
                          trm3  = _mm512_mul_ps(ctht1,ctht2);
                          strm3 = _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          den   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          sden  = _mm512_mul_ps(den,den);
                          rcs   = _mm512_div_ps(num,sden);
                          return (rcs);
                } 


                 
                   __m512 rcs_f5193_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pc,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                             const float * __restrict __ATTR_ALIGN__(64) pphi2) {

                          register __m512  a     = _mm512_load_ps(&pa[0]);
                          register __m512  c     = _mm512_load_ps(&pc[0]);
                          register __m512  tht1  = _mm512_load_ps(&ptht1[0]); 
                          register __m512  tht2  = _mm512_load_ps(&ptht2[0]); 
                          register __m512  pphi2 = _mm512_load_ps(&pphi2[0]); 
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,num,a4,a2,c2,den,sden,trm1,trm2,trm3;
                          register __m512 stht1,stht2,cphi2,ctht1,ctht2,sphi2,strm1,strm2,strm3;
                          stht1 = xsinf(tht1);
                          a2    = _mm512_mul_ps(a,a);
                          cphi2 = xcosf(phi2);
                          c2    = _mm512_mul_ps(c,c);
                          ctht1 = xcosf(tht1);
                          a4    = _mm512_mul_ps(a2,a2);
                          ctht2 = xcosf(tht2);
                          num   = _mm512_mul_ps(_4pi,_mm512_mul_ps(a4,c2));
                          sphi2 = xsinf(phi2);
                          stht2 = xsinf(tht2);
                          trm1  = _mm512_fmadd_ps(stht2,cphi2,stht1);
                          strm1 = _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          trm2  = _mm512_mul_ps(stht2,sphi2);
                          strm2 = _mm512_mul_ps(a2,_mm512_mul_ps(trm2,trm2));
                          trm3  = _mm512_mul_ps(ctht1,ctht2);
                          strm3 = _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          den   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          sden  = _mm512_mul_ps(den,den);
                          rcs   = _mm512_div_ps(num,sden);
                          return (rcs);
                } 


                
                   __m512 rcs_f5193_zmm16r4_u( const float * __restrict  pa,
                                             const float * __restrict  pc,
                                             const float * __restrict  ptht1,
                                             const float * __restrict  ptht2,
                                             const float * __restrict  pphi2) {

                          register __m512  a     = _mm512_loadu_ps(&pa[0]);
                          register __m512  c     = _mm512_loadu_ps(&pc[0]);
                          register __m512  tht1  = _mm512_loadu_ps(&ptht1[0]); 
                          register __m512  tht2  = _mm512_loadu_ps(&ptht2[0]); 
                          register __m512  pphi2 = _mm512_loadu_ps(&pphi2[0]); 
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,num,a4,a2,c2,den,sden,trm1,trm2,trm3;
                          register __m512 stht1,stht2,cphi2,ctht1,ctht2,sphi2,strm1,strm2,strm3;
                          stht1 = xsinf(tht1);
                          a2    = _mm512_mul_ps(a,a);
                          cphi2 = xcosf(phi2);
                          c2    = _mm512_mul_ps(c,c);
                          ctht1 = xcosf(tht1);
                          a4    = _mm512_mul_ps(a2,a2);
                          ctht2 = xcosf(tht2);
                          num   = _mm512_mul_ps(_4pi,_mm512_mul_ps(a4,c2));
                          sphi2 = xsinf(phi2);
                          stht2 = xsinf(tht2);
                          trm1  = _mm512_fmadd_ps(stht2,cphi2,stht1);
                          strm1 = _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          trm2  = _mm512_mul_ps(stht2,sphi2);
                          strm2 = _mm512_mul_ps(a2,_mm512_mul_ps(trm2,trm2));
                          trm3  = _mm512_mul_ps(ctht1,ctht2);
                          strm3 = _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          den   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          sden  = _mm512_mul_ps(den,den);
                          rcs   = _mm512_div_ps(num,sden);
                          return (rcs);
                } 


                   /*
                          High-frequency solutions.
                          Backscatter case RCS of oblate spheroid.
                          Formula 5.1-94
                      */


                  
                   __m512 rcs_f5194_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a4,a2,c2,num,den,sden;
                          register __m512 stht,ctht,stht2,ctht2;
                          stht = xsinf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          ctht = xcosf(tht);
                          c2   = _mm512_mul_ps(c,c);
                          stht2= _mm512_mul_ps(stht,stht);
                          a4   = _mm512_mul_ps(a2,a2);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a4,c2));
                          den  = _mm512_fmadd_ps(a2,stht2,_mm512_mul_ps(c2,ctht2));
                          sden = _mm512_mul_ps(den,den);
                          rcs  = _mm512_div_ps(num,sden);
                          return (rcs):
                 }


                 
                   __m512 rcs_f5194_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pc,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht) {

                          register __m512  a     = _mm512_load_ps(&pa[0]);
                          register __m512  c     = _mm512_load_ps(&pc[0]);
                          register __m512  tht  = _mm512_load_ps(&ptht[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a4,a2,c2,num,den,sden;
                          register __m512 stht,ctht,stht2,ctht2;
                          stht = xsinf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          ctht = xcosf(tht);
                          c2   = _mm512_mul_ps(c,c);
                          stht2= _mm512_mul_ps(stht,stht);
                          a4   = _mm512_mul_ps(a2,a2);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a4,c2));
                          den  = _mm512_fmadd_ps(a2,stht2,_mm512_mul_ps(c2,ctht2));
                          sden = _mm512_mul_ps(den,den);
                          rcs  = _mm512_div_ps(num,sden);
                          return (rcs):
                 }


                 
                   __m512 rcs_f5194_zmm16r4_u(const float * __restrict  pa,
                                             const float * __restrict  pc,
                                             const float * __restrict  ptht) {

                          register __m512  a     = _mm512_loadu_ps(&pa[0]);
                          register __m512  c     = _mm512_loadu_ps(&pc[0]);
                          register __m512  tht  = _mm512_loadu_ps(&ptht[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a4,a2,c2,num,den,sden;
                          register __m512 stht,ctht,stht2,ctht2;
                          stht = xsinf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          ctht = xcosf(tht);
                          c2   = _mm512_mul_ps(c,c);
                          stht2= _mm512_mul_ps(stht,stht);
                          a4   = _mm512_mul_ps(a2,a2);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a4,c2));
                          den  = _mm512_fmadd_ps(a2,stht2,_mm512_mul_ps(c2,ctht2));
                          sden = _mm512_mul_ps(den,den);
                          rcs  = _mm512_div_ps(num,sden);
                          return (rcs):
                 }


                    /*
                           Prolate spheroid.
                           Axial incidence "Physical Optics" backscatter RCS.
                           Formula 5.1-95
                      */

 
                 
                   __m512 rcs_f5195_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0c,a4,a2,c2,_2k0c,k0cs;
                          register __m512 sarg,trm1,trm2,trm3,x0;
                          k0c  = _mm512_mul_ps(k0,c);
                          a2   = _mm512_mul_ps(a,a);
                          _2k0c= _mm512_add_ps(k0c,k0c);
                          c2   = _mm512_mul_ps(c,c);
                          sarg = xsinf(_2k0c);
                          trm2 = _mm512_div_ps(sarg,k0c);
                          a4   = _mm512_mul_ps(a2,a2);
                          k0cs = _mm512_mul_ps(k0c,k0c);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,ar),c2);
                          trm3 = _mm512_div_ps(sarg,k0cs);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5195_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512  a     = _mm512_load_ps(&pa[0]);
                          register __m512  c     = _mm512_load_ps(&pc[0]);
                          register __m512  k0    = _mm512_load_ps(&pk0[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0c,a4,a2,c2,_2k0c,k0cs;
                          register __m512 sarg,trm1,trm2,trm3,x0;
                          k0c  = _mm512_mul_ps(k0,c);
                          a2   = _mm512_mul_ps(a,a);
                          _2k0c= _mm512_add_ps(k0c,k0c);
                          c2   = _mm512_mul_ps(c,c);
                          sarg = xsinf(_2k0c);
                          trm2 = _mm512_div_ps(sarg,k0c);
                          a4   = _mm512_mul_ps(a2,a2);
                          k0cs = _mm512_mul_ps(k0c,k0c);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,ar),c2);
                          trm3 = _mm512_div_ps(sarg,k0cs);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5195_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pc,
                                              const float * __restrict  pk0) {

                          register __m512  a     = _mm512_loadu_ps(&pa[0]);
                          register __m512  c     = _mm512_loadu_ps(&pc[0]);
                          register __m512  k0    = _mm512_loadu_ps(&pk0[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0c,a4,a2,c2,_2k0c,k0cs;
                          register __m512 sarg,trm1,trm2,trm3,x0;
                          k0c  = _mm512_mul_ps(k0,c);
                          a2   = _mm512_mul_ps(a,a);
                          _2k0c= _mm512_add_ps(k0c,k0c);
                          c2   = _mm512_mul_ps(c,c);
                          sarg = xsinf(_2k0c);
                          trm2 = _mm512_div_ps(sarg,k0c);
                          a4   = _mm512_mul_ps(a2,a2);
                          k0cs = _mm512_mul_ps(k0c,k0c);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,ar),c2);
                          trm3 = _mm512_div_ps(sarg,k0cs);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                  /*
                           Prolate spheroid.
                           Incidence perpendicular to the axis. 
                           "Physical Optics" backscatter RCS.
                           Formula 5.1-96
                      */


                 
                   __m512 rcs_f5196_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0a,c2,_2k0a,k0as;
                          register __m512 sarg,trm1,trm2,trm3,x0,x1;
                          k0a  = _mm512_mul_ps(k0,a);
                          c2   = _mm512_mul_ps(c,c);
                          _2k0a= _mm512_add_ps(k0a,k0a);
                          sarg = xsinf(_2k0a);
                          trm2 = _mm512_div_ps(sarg,k0a);
                          k0as = _mm512_mul_ps(k0a,k0a);
                          trm1 = _mm512_mul_ps(pi,c2);
                          x1   = _mm512_mul_ps(sarg,sarg);
                          trm3 = _mm512_div_ps(x1,k0as);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                
                   __m512 rcs_f5196_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512  a     = _mm512_load_ps(&pa[0]);
                          register __m512  c     = _mm512_load_ps(&pc[0]);
                          register __m512  k0    = _mm512_load_ps(&pk0[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0a,c2,_2k0a,k0as;
                          register __m512 sarg,trm1,trm2,trm3,x0,x1;
                          k0a  = _mm512_mul_ps(k0,a);
                          c2   = _mm512_mul_ps(c,c);
                          _2k0a= _mm512_add_ps(k0a,k0a);
                          sarg = xsinf(_2k0a);
                          trm2 = _mm512_div_ps(sarg,k0a);
                          k0as = _mm512_mul_ps(k0a,k0a);
                          trm1 = _mm512_mul_ps(pi,c2);
                          x1   = _mm512_mul_ps(sarg,sarg);
                          trm3 = _mm512_div_ps(x1,k0as);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5196_zmm16r4_u(  const float * __restrict  pa,
                                              const float * __restrict  pc,
                                              const float * __restrict  pk0) {

                          register __m512  a     = _mm512_loadu_ps(&pa[0]);
                          register __m512  c     = _mm512_loadu_ps(&pc[0]);
                          register __m512  k0    = _mm512_loadu_ps(&pk0[0]); 
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,k0a,c2,_2k0a,k0as;
                          register __m512 sarg,trm1,trm2,trm3,x0,x1;
                          k0a  = _mm512_mul_ps(k0,a);
                          c2   = _mm512_mul_ps(c,c);
                          _2k0a= _mm512_add_ps(k0a,k0a);
                          sarg = xsinf(_2k0a);
                          trm2 = _mm512_div_ps(sarg,k0a);
                          k0as = _mm512_mul_ps(k0a,k0a);
                          trm1 = _mm512_mul_ps(pi,c2);
                          x1   = _mm512_mul_ps(sarg,sarg);
                          trm3 = _mm512_div_ps(x1,k0as);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm2),trm3);
                          rcs  = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                 }


                   /*
                        Perfectly conducting ogive.
                        Backscatter RCS, axial incidence.
                        Parabolic ogive.
                        Formula 5.2-1
                    */


                 
                   __m512 rcs_f521_zmm16r4(const __m512 a,
                                           const __m512 b,
                                           const __m512 k0) {

                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 c0   = _mm512_set1_ps(0.8f);
                          const __m512 c1   = _mm512_set1_ps(1.066666666666666666666666666667f);
                          register __m512 rcs,V,rho,V2,k04,k02,expr;
                          register __m512 trm1,trm2,b2,invr,x0,inve,strm2;
                          k02  = _mm512_mul_ps(k0,k0);
                          rho  = _mm512_mul_ps(c0,_mm512_div_ps(a,b));
                          k04  = _mm512_mul_ps(k02,k02);
                          b2   = _mm512_mul_ps(b,b);
                          x0   = _mm512_mul_ps(pi,rho);
                          expr = xexpf(rho);
                          invr = _mm512_rcp14_ps(x0);
                          V    = _mm512_mul_ps(_mm512_set1_ps(3.351032163829112787693486275498f),
                                               _mm512_mul_ps(a,b2));
                          inve = _mm512_rcp14_ps(expr);
                          V2   = _mm512_mul_ps(V,V);
                          trm2 = _mm512_fmadd_ps(invr,inve,_1);
                          trm1 = _mm512_mul_ps(_4pi,_mm512_mul_ps(k04,V2));
                          strm2= _mm512_mul_ps(trm2,trm2);
                          rcs  = _mm512_mul_ps(trm1,strm2);
                          return (rcs);
                }


                   __m512 rcs_f521_zmm16r4_a(   const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512  a     = _mm512_load_ps(&pa[0]);
                          register __m512  b     = _mm512_load_ps(&pb[0]);
                          register __m512  k0    = _mm512_load_ps(&pk0[0]); 
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 c0   = _mm512_set1_ps(0.8f);
                          const __m512 c1   = _mm512_set1_ps(1.066666666666666666666666666667f);
                          register __m512 rcs,V,rho,V2,k04,k02,expr;
                          register __m512 trm1,trm2,b2,invr,x0,inve,strm2;
                          k02  = _mm512_mul_ps(k0,k0);
                          rho  = _mm512_mul_ps(c0,_mm512_div_ps(a,b));
                          k04  = _mm512_mul_ps(k02,k02);
                          b2   = _mm512_mul_ps(b,b);
                          x0   = _mm512_mul_ps(pi,rho);
                          expr = xexpf(rho);
                          invr = _mm512_rcp14_ps(x0);
                          V    = _mm512_mul_ps(_mm512_set1_ps(3.351032163829112787693486275498f),
                                               _mm512_mul_ps(a,b2));
                          inve = _mm512_rcp14_ps(expr);
                          V2   = _mm512_mul_ps(V,V);
                          trm2 = _mm512_fmadd_ps(invr,inve,_1);
                          trm1 = _mm512_mul_ps(_4pi,_mm512_mul_ps(k04,V2));
                          strm2= _mm512_mul_ps(trm2,trm2);
                          rcs  = _mm512_mul_ps(trm1,strm2);
                          return (rcs);
                }


                 
                   __m512 rcs_f521_zmm16r4_u(   const float * __restrict  pa,
                                              const float * __restrict  pb,
                                              const float * __restrict  pk0) {

                          register __m512  a     = _mm512_loadu_ps(&pa[0]);
                          register __m512  b     = _mm512_loadu_ps(&pb[0]);
                          register __m512  k0    = _mm512_loadu_ps(&pk0[0]); 
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 c0   = _mm512_set1_ps(0.8f);
                          const __m512 c1   = _mm512_set1_ps(1.066666666666666666666666666667f);
                          register __m512 rcs,V,rho,V2,k04,k02,expr;
                          register __m512 trm1,trm2,b2,invr,x0,inve,strm2;
                          k02  = _mm512_mul_ps(k0,k0);
                          rho  = _mm512_mul_ps(c0,_mm512_div_ps(a,b));
                          k04  = _mm512_mul_ps(k02,k02);
                          b2   = _mm512_mul_ps(b,b);
                          x0   = _mm512_mul_ps(pi,rho);
                          expr = xexpf(rho);
                          invr = _mm512_rcp14_ps(x0);
                          V    = _mm512_mul_ps(_mm512_set1_ps(3.351032163829112787693486275498f),
                                               _mm512_mul_ps(a,b2));
                          inve = _mm512_rcp14_ps(expr);
                          V2   = _mm512_mul_ps(V,V);
                          trm2 = _mm512_fmadd_ps(invr,inve,_1);
                          trm1 = _mm512_mul_ps(_4pi,_mm512_mul_ps(k04,V2));
                          strm2= _mm512_mul_ps(trm2,trm2);
                          rcs  = _mm512_mul_ps(trm1,strm2);
                          return (rcs);
                }


                  /*
                        Perfectly conducting ogive.
                        Backscatter RCS, axial incidence.
                        Circular ogive.
                        Formula 5.2-4
                    */


                
                   __m512 rcs_f524_zmm16r4(const __m512 alp,
                                           const __m512 r0,
                                           const __m512 k0) {

                          const __m512 tpi   = _mm512_set1_ps(2.0f*3.14159265358979323846264338328f);
                          const __m512 _4pi  = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 c0    = _mm512_set1_ps(0.33333333333333333333333333333333333f);
                          const __m512 c1    = _mm512_set1_ps(1.5f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,rho,V,V2,k04,salp,calp,trm2,trm3;
                          register __m512 num,den,expr,invr,inve,x0,x1,x2,trm1,x3;
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(tpi,_mm512_mul_ps(r0,r0));
                          salp= xsinf(alp);
                          k04 = _mm512_mul_ps(x0,x0);
                          calp= xcosf(alp);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          x0  = _mm512_mul_ps(salp,_mm512_mul_ps(salp,salp));
                          x3  = _mm512_sub_ps(_1,calp);
                          x2  = _mm512_mul_ps(c0,x0);
                          den = _mm512_mul_ps(x3,_mm512_mul_ps(x3,x3));
                          num = _mm512_sub_ps(salp,_mm512_fmsub_ps(alp,calp,x2));
                          rho = _mm512_mul_ps(c1,_mm512_div_ps(num,den));
                          invr= _mm512_rcp14_ps(rho);
                          V   = _mm512_mul_ps(x1,num);
                          expr= xexpf(rho);
                          V2  = _mm512_mul_ps(V,V);
                          inve= _mm512_rcp14_ps(expr);
                          trm2= _mm512_mul_ps(trm1,V2);
                          trm3= _mm512_fmadd_ps(inve,invr,_1);
                          rcs = _mm512_mul_ps(trm2,trm3);
                          return (rcs);
                }


                 
                   __m512 rcs_f524_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pr0,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512  alp   = _mm512_load_ps(&palp[0]);
                          register __m512  r0    = _mm512_load_ps(&pr0[0]);
                          register __m512  k0    = _mm512_load_ps(&pk0[0]); 
                          const __m512 tpi   = _mm512_set1_ps(2.0f*3.14159265358979323846264338328f);
                          const __m512 _4pi  = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 c0    = _mm512_set1_ps(0.33333333333333333333333333333333333f);
                          const __m512 c1    = _mm512_set1_ps(1.5f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,rho,V,V2,k04,salp,calp,trm2,trm3;
                          register __m512 num,den,expr,invr,inve,x0,x1,x2,trm1,x3;
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(tpi,_mm512_mul_ps(r0,r0));
                          salp= xsinf(alp);
                          k04 = _mm512_mul_ps(x0,x0);
                          calp= xcosf(alp);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          x0  = _mm512_mul_ps(salp,_mm512_mul_ps(salp,salp));
                          x3  = _mm512_sub_ps(_1,calp);
                          x2  = _mm512_mul_ps(c0,x0);
                          den = _mm512_mul_ps(x3,_mm512_mul_ps(x3,x3));
                          num = _mm512_sub_ps(salp,_mm512_fmsub_ps(alp,calp,x2));
                          rho = _mm512_mul_ps(c1,_mm512_div_ps(num,den));
                          invr= _mm512_rcp14_ps(rho);
                          V   = _mm512_mul_ps(x1,num);
                          expr= xexpf(rho);
                          V2  = _mm512_mul_ps(V,V);
                          inve= _mm512_rcp14_ps(expr);
                          trm2= _mm512_mul_ps(trm1,V2);
                          trm3= _mm512_fmadd_ps(inve,invr,_1);
                          rcs = _mm512_mul_ps(trm2,trm3);
                          return (rcs);
                }


                  
                   __m512 rcs_f524_zmm16r4_u( const float * __restrict  palp,
                                              const float * __restrict  pr0,
                                              const float * __restrict  pk0) {

                          register __m512  alp   = _mm512_loadu_ps(&palp[0]);
                          register __m512  r0    = _mm512_loadu_ps(&pr0[0]);
                          register __m512  k0    = _mm512_loadu_ps(&pk0[0]); 
                          const __m512 tpi   = _mm512_set1_ps(2.0f*3.14159265358979323846264338328f);
                          const __m512 _4pi  = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 c0    = _mm512_set1_ps(0.33333333333333333333333333333333333f);
                          const __m512 c1    = _mm512_set1_ps(1.5f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,rho,V,V2,k04,salp,calp,trm2,trm3;
                          register __m512 num,den,expr,invr,inve,x0,x1,x2,trm1,x3;
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(tpi,_mm512_mul_ps(r0,r0));
                          salp= xsinf(alp);
                          k04 = _mm512_mul_ps(x0,x0);
                          calp= xcosf(alp);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          x0  = _mm512_mul_ps(salp,_mm512_mul_ps(salp,salp));
                          x3  = _mm512_sub_ps(_1,calp);
                          x2  = _mm512_mul_ps(c0,x0);
                          den = _mm512_mul_ps(x3,_mm512_mul_ps(x3,x3));
                          num = _mm512_sub_ps(salp,_mm512_fmsub_ps(alp,calp,x2));
                          rho = _mm512_mul_ps(c1,_mm512_div_ps(num,den));
                          invr= _mm512_rcp14_ps(rho);
                          V   = _mm512_mul_ps(x1,num);
                          expr= xexpf(rho);
                          V2  = _mm512_mul_ps(V,V);
                          inve= _mm512_rcp14_ps(expr);
                          trm2= _mm512_mul_ps(trm1,V2);
                          trm3= _mm512_fmadd_ps(inve,invr,_1);
                          rcs = _mm512_mul_ps(trm2,trm3);
                          return (rcs);
                }


                 /*
                        Circular ogive.
                        Axial incidence -- RCS.
                        Formula 5.2-9
                   */


                 
                   __m512 rcs_f529_zmm16r4(const __m512 gam0,
                                           const __m512 alp,
                                           const __m512 k0a) {

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,trm1,trm2,trm3,talp,calp,_2k0a,tan2,x0;
                          register __m512 gam2,tan4,calp4,den1,num,carg,den2;
                          talp   = xtanf(alp);
                          gam2   = _mm512_mul_ps(gam0,gam0);
                          calp   = xcosf(alp);
                          _2k0a  = _mm512_add_ps(k0a,k0a);
                          den1   = _mm512_add_ps(_1,calp);
                          tan2   = _mm512_mul_ps(talp,talp);
                          den2   = _mm512_mul_ps(den1,den1);
                          tan4   = _mm512_mul_ps(tan2,tan2);
                          x0     = _mm512_mul_ps(calp,calp);
                          trm1   = _mm512_div_ps(_mm512_mul_ps(gam2,tan4),_16pi);
                          calp4  = _mm512_mul_ps(x0,x0);
                          carg   = xcosf(_2k0a);
                          trm3   = _mm512_div_ps(calp4,den2);
                          num    = _mm512_mul_ps(x0,carg);
                          trm2   = _mm512_div_ps(num,den1);
                          x0     = _mm512_add_ps(_1,_mm512_add_ps(trm2,trm3));
                          rcs    = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                }


                
                   __m512 rcs_f529_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0a) {

                          register __m512  gam0   = _mm512_load_ps(&pgam0[0]);
                          register __m512  alp    = _mm512_load_ps(&palp[0]);
                          register __m512  k0a    = _mm512_load_ps(&pk0a[0]); 
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,trm1,trm2,trm3,talp,calp,_2k0a,tan2,x0;
                          register __m512 gam2,tan4,calp4,den1,num,carg,den2;
                          talp   = xtanf(alp);
                          gam2   = _mm512_mul_ps(gam0,gam0);
                          calp   = xcosf(alp);
                          _2k0a  = _mm512_add_ps(k0a,k0a);
                          den1   = _mm512_add_ps(_1,calp);
                          tan2   = _mm512_mul_ps(talp,talp);
                          den2   = _mm512_mul_ps(den1,den1);
                          tan4   = _mm512_mul_ps(tan2,tan2);
                          x0     = _mm512_mul_ps(calp,calp);
                          trm1   = _mm512_div_ps(_mm512_mul_ps(gam2,tan4),_16pi);
                          calp4  = _mm512_mul_ps(x0,x0);
                          carg   = xcosf(_2k0a);
                          trm3   = _mm512_div_ps(calp4,den2);
                          num    = _mm512_mul_ps(x0,carg);
                          trm2   = _mm512_div_ps(num,den1);
                          x0     = _mm512_add_ps(_1,_mm512_add_ps(trm2,trm3));
                          rcs    = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                }


                 
                   __m512 rcs_f529_zmm16r4_u( const float * __restrict pgam0,
                                              const float * __restrict  palp,
                                              const float * __restrict  pk0a) {

                          register __m512  gam0   = _mm512_loadu_ps(&pgam0[0]);
                          register __m512  alp    = _mm512_loadu_ps(&palp[0]);
                          register __m512  k0a    = _mm512_loadu_ps(&pk0a[0]); 
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,trm1,trm2,trm3,talp,calp,_2k0a,tan2,x0;
                          register __m512 gam2,tan4,calp4,den1,num,carg,den2;
                          talp   = xtanf(alp);
                          gam2   = _mm512_mul_ps(gam0,gam0);
                          calp   = xcosf(alp);
                          _2k0a  = _mm512_add_ps(k0a,k0a);
                          den1   = _mm512_add_ps(_1,calp);
                          tan2   = _mm512_mul_ps(talp,talp);
                          den2   = _mm512_mul_ps(den1,den1);
                          tan4   = _mm512_mul_ps(tan2,tan2);
                          x0     = _mm512_mul_ps(calp,calp);
                          trm1   = _mm512_div_ps(_mm512_mul_ps(gam2,tan4),_16pi);
                          calp4  = _mm512_mul_ps(x0,x0);
                          carg   = xcosf(_2k0a);
                          trm3   = _mm512_div_ps(calp4,den2);
                          num    = _mm512_mul_ps(x0,carg);
                          trm2   = _mm512_div_ps(num,den1);
                          x0     = _mm512_add_ps(_1,_mm512_add_ps(trm2,trm3));
                          rcs    = _mm512_mul_ps(trm1,x0);
                          return (rcs);
                }


                   /*
                           Circular ogive.
                           RCS as function of theta angle, i.e. (0<<theta<<(90-alpha))
                           Formula 5.2-6
                     */

                 
                   __m512 rcs_f526_zmm16r4(const __m512 gam0,
                                           const __m512 alp,
                                           const __m512 tht) { // in degrees.
                                           
                          const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1     = _mm512_set1_ps(1.0f);
                          register __m512 rcs,talp,talp2,talp4,tath,tath2;
                          register __m512 num,den,ctht,ctht2,ctht6,_1mt2;
                          register __m512 x0,x1,gam2;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          talp  = xtanf(alp);
                          ctht  = xcosf(tht);
                          tath  = xtanf(tht);
                          talp2 = _mm512_mul_ps(talp,talp);
                          ctht2 = _mm512_mul_ps(ctht,ctht);
                          _1mt2 = _mm512_sub_ps(_1,talp2);
                          ctht6 = _mm512_mul_ps(ctht2,_mm512_mul_ps(ctht2,ctht2));
                          tath2 = _mm512_mul_ps(tath,tath);
                          x1    = _mm512_mul_ps(_1mt2,tath2);
                          num   = _mm512_mul_ps(gam2,_mm512_mul_ps(talp2,talp2));
                          x0    = _mm512_mul_ps(_16pi,ctht6);
                          den   = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                          den   = _mm512_mul_ps(x0,den);
                          rcs   = _mm512_div_ps(num,den);
                          return (rcs);
                }


                 
                   __m512 rcs_f526_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht) { // in degrees.
                           
                          register __m512  gam0   = _mm512_load_ps(&pgam0[0]);
                          register __m512  alp    = _mm512_load_ps(&palp[0]);
                          register __m512  tht    = _mm512_load_ps(&ptht[0]);                 
                          const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1     = _mm512_set1_ps(1.0f);
                          register __m512 rcs,talp,talp2,talp4,tath,tath2;
                          register __m512 num,den,ctht,ctht2,ctht6,_1mt2;
                          register __m512 x0,x1,gam2;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          talp  = xtanf(alp);
                          ctht  = xcosf(tht);
                          tath  = xtanf(tht);
                          talp2 = _mm512_mul_ps(talp,talp);
                          ctht2 = _mm512_mul_ps(ctht,ctht);
                          _1mt2 = _mm512_sub_ps(_1,talp2);
                          ctht6 = _mm512_mul_ps(ctht2,_mm512_mul_ps(ctht2,ctht2));
                          tath2 = _mm512_mul_ps(tath,tath);
                          x1    = _mm512_mul_ps(_1mt2,tath2);
                          num   = _mm512_mul_ps(gam2,_mm512_mul_ps(talp2,talp2));
                          x0    = _mm512_mul_ps(_16pi,ctht6);
                          den   = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                          den   = _mm512_mul_ps(x0,den);
                          rcs   = _mm512_div_ps(num,den);
                          return (rcs);
                }


                  
                   __m512 rcs_f526_zmm16r4_u(const float * __restrict  pgam0,
                                              const float * __restrict  palp,
                                              const float * __restrict  ptht) { // in degrees.
                           
                          register __m512  gam0   = _mm512_loadu_ps(&pgam0[0]);
                          register __m512  alp    = _mm512_loadu_ps(&palp[0]);
                          register __m512  tht    = _mm512_loadu_ps(&ptht[0]);                 
                          const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1     = _mm512_set1_ps(1.0f);
                          register __m512 rcs,talp,talp2,talp4,tath,tath2;
                          register __m512 num,den,ctht,ctht2,ctht6,_1mt2;
                          register __m512 x0,x1,gam2;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          talp  = xtanf(alp);
                          ctht  = xcosf(tht);
                          tath  = xtanf(tht);
                          talp2 = _mm512_mul_ps(talp,talp);
                          ctht2 = _mm512_mul_ps(ctht,ctht);
                          _1mt2 = _mm512_sub_ps(_1,talp2);
                          ctht6 = _mm512_mul_ps(ctht2,_mm512_mul_ps(ctht2,ctht2));
                          tath2 = _mm512_mul_ps(tath,tath);
                          x1    = _mm512_mul_ps(_1mt2,tath2);
                          num   = _mm512_mul_ps(gam2,_mm512_mul_ps(talp2,talp2));
                          x0    = _mm512_mul_ps(_16pi,ctht6);
                          den   = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                          den   = _mm512_mul_ps(x0,den);
                          rcs   = _mm512_div_ps(num,den);
                          return (rcs);
                }


                    /*
                           Circular ogive.
                           RCS as function of theta angle, i.e. theta = 90-alpha
                           Formula 5.2-7
                     */


                  
                   __m512 rcs_f527_zmm16r4(const __m512 b,
                                           const __m512 alp) {

                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 hlf   = _mm512_set1_ps(0.5f);
                          register __m512 rcs,b2,alp2,talp,x0;
                          b2  = _mm512_mul_ps(b,b);
                          alp2= _mm512_mul_ps(alp,hlf);
                          talp= xtanf(alp2);
                          x0  = _mm512_mul_ps(_4pi,_mm512_mul_ps(talp,talp));
                          rcs = _mm512_div_ps(b2,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f527_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512  b    = _mm512_load_ps(&pb[0]);
                          register __m512  alp  = _mm512_load_ps(&palp[0]);    
                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 hlf   = _mm512_set1_ps(0.5f);
                          register __m512 rcs,b2,alp2,talp,x0;
                          b2  = _mm512_mul_ps(b,b);
                          alp2= _mm512_mul_ps(alp,hlf);
                          talp= xtanf(alp2);
                          x0  = _mm512_mul_ps(_4pi,_mm512_mul_ps(talp,talp));
                          rcs = _mm512_div_ps(b2,x0);
                          return (rcs);
                 }


                  
                   __m512 rcs_f527_zmm16r4_u(const float * __restrict  pb,
                                              const float * __restrict  palp) {

                          register __m512  b    = _mm512_loadu_ps(&pb[0]);
                          register __m512  alp  = _mm512_loadu_ps(&palp[0]);    
                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 hlf   = _mm512_set1_ps(0.5f);
                          register __m512 rcs,b2,alp2,talp,x0;
                          b2  = _mm512_mul_ps(b,b);
                          alp2= _mm512_mul_ps(alp,hlf);
                          talp= xtanf(alp2);
                          x0  = _mm512_mul_ps(_4pi,_mm512_mul_ps(talp,talp));
                          rcs = _mm512_div_ps(b2,x0);
                          return (rcs);
                 }


                   /*
                           Circular ogive.
                           RCS as function of theta angle, i.e. theta = (90-alpha) < theta << 90
                           Formula 5.2-8
                      */


                 
                   __m512 rcs_f528_zmm16r4(const __m512 r0,
                                           const __m512 b,
                                           const __m512 tht) {

                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          register __m512 rcs,num,den,r02,stht,x0,rat;
                          r02  = _mm512_mul_ps(r0,r0);
                          stht = xsinf(tht);
                          x0   = _mm512_mul_ps(pi,r02);
                          num  = _mm512_sub_ps(r0,b);
                          den  = _mm512_mul_ps(r0,stht);
                          rat  = _mm512_div_ps(num,den);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(_1,rat));
                          return (rat);
                 }

                    
                 
                   __m512 rcs_f528_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pb,
                                           const float * __restrict __ATTR_ALIGN__(64) pr0,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht ) {

                          register __m512  b     = _mm512_load_ps(&pb[0]);
                          register __m512  r0    = _mm512_load_ps(&pr0[0]);
                          register __m512  tht    = _mm512_load_ps(&ptht[0]);    
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          register __m512 rcs,num,den,r02,stht,x0,rat;
                          r02  = _mm512_mul_ps(r0,r0);
                          stht = xsinf(tht);
                          x0   = _mm512_mul_ps(pi,r02);
                          num  = _mm512_sub_ps(r0,b);
                          den  = _mm512_mul_ps(r0,stht);
                          rat  = _mm512_div_ps(num,den);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(_1,rat));
                          return (rat);
                 }


                   __m512 rcs_f528_zmm16r4_u(const float * __restrict  pb,
                                           const float * __restrict  pr0,
                                           const float * __restrict  ptht ) {

                          register __m512  b     = _mm512_loadu_ps(&pb[0]);
                          register __m512  r0    = _mm512_loadu_ps(&pr0[0]);
                          register __m512  tht   = _mm512_loadu_ps(&ptht[0]);    
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          register __m512 rcs,num,den,r02,stht,x0,rat;
                          r02  = _mm512_mul_ps(r0,r0);
                          stht = xsinf(tht);
                          x0   = _mm512_mul_ps(pi,r02);
                          num  = _mm512_sub_ps(r0,b);
                          den  = _mm512_mul_ps(r0,stht);
                          rat  = _mm512_div_ps(num,den);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(_1,rat));
                          return (rat);
                 }


                  /*
                       Dispatch kernel for Circular ogive RCS.
                       Formulae: 5.2-6, 5.2-7, 5.2-8
                    */


                
                   __m512 rcs_f52678_zmm16r4(const __m512 gam0,
                                             const __m512 alp,
                                             const __m512 tht,
                                             const __m512 b,
                                             const __m512 r0) {

                          const __m512 _90        = _mm512_set1_ps(90.0f);
                          const __m512 _0         = _mm512_setzero_ps();
                          const __m512 dif        = _mm512_sub_ps(_90,alp);
                          const __mmask16 m1      = _mm512_cmp_ps_mask(_0,tht,_CMP_LE_OQ);
                          const __mmask16 m2      = _mm512_cmp_ps_mask(tht,dif,_CMP_LT_OQ);
                          const __mmask16 m3      = _mm512_cmp_ps_mask(tht,dif,_CMP_EQ_OQ);
                          const __mmask16 m4      = _mm512_cmp_ps_mask(dif,tht,_CMP_LT_OQ);
                          const __mmask16 m5      = _mm512_cmp_ps_mask(tht,_90,_CMP_LE_OQ);
                          if(m1 && m2) {
                              return (rcs_f526_zmm16r4(gam0,alp,tht));
                          }
                          else if(m3) {
                              return (rcs_f527_zmm16r4(b,alp));
                          }
                          else(m4 && m5) {
                               return (rcs_f528_zmm16r4(b,r0,tht)); 
                          }
                }


                 
                   __m512 rcs_f52678_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                               const float * __restrict __ATTR_ALIGN__(64) palp,
                                               const float * __restrict __ATTR_ALIGN__(64) ptht,
                                               const float * __restrict __ATTR_ALIGN__(64) pb,
                                               const float * __restrict __ATTR_ALIGN__(64) pr0) {

                          const __m512 _90        = _mm512_set1_ps(90.0f);
                          const __m512 _0         = _mm512_setzero_ps();
                          const __m512 dif        = _mm512_sub_ps(_90,alp);
                          const __mmask16 m1      = _mm512_cmp_ps_mask(_0,tht,_CMP_LE_OQ);
                          const __mmask16 m2      = _mm512_cmp_ps_mask(tht,dif,_CMP_LT_OQ);
                          const __mmask16 m3      = _mm512_cmp_ps_mask(tht,dif,_CMP_EQ_OQ);
                          const __mmask16 m4      = _mm512_cmp_ps_mask(dif,tht,_CMP_LT_OQ);
                          const __mmask16 m5      = _mm512_cmp_ps_mask(tht,_90,_CMP_LE_OQ);
                          if(m1 && m2) {
                              return (rcs_f526_zmm16r4_a(pgam0,palp,ptht));
                          }
                          else if(m3) {
                              return (rcs_f527_zmm16r4_a(pb,palp));
                          }
                          else(m4 && m5) {
                               return (rcs_f528_zmm16r4_a(pb,pr0,ptht)); 
                          }
                }


                  
                   __m512 rcs_f52678_zmm16r4_u(const float * __restrict  pgam0,
                                               const float * __restrict  palp,
                                               const float * __restrict  ptht,
                                               const float * __restrict  pb,
                                               const float * __restrict  pr0) {

                          const __m512 _90        = _mm512_set1_ps(90.0f);
                          const __m512 _0         = _mm512_setzero_ps();
                          const __m512 dif        = _mm512_sub_ps(_90,alp);
                          const __mmask16 m1      = _mm512_cmp_ps_mask(_0,tht,_CMP_LE_OQ);
                          const __mmask16 m2      = _mm512_cmp_ps_mask(tht,dif,_CMP_LT_OQ);
                          const __mmask16 m3      = _mm512_cmp_ps_mask(tht,dif,_CMP_EQ_OQ);
                          const __mmask16 m4      = _mm512_cmp_ps_mask(dif,tht,_CMP_LT_OQ);
                          const __mmask16 m5      = _mm512_cmp_ps_mask(tht,_90,_CMP_LE_OQ);
                          if(m1 && m2) {
                              return (rcs_f526_zmm16r4_u(pgam0,palp,ptht));
                          }
                          else if(m3) {
                              return (rcs_f527_zmm16r4_u(pb,palp));
                          }
                          else(m4 && m5) {
                               return (rcs_f528_zmm16r4_u(pb,pr0,ptht)); 
                          }
                }


                  /*
                      Long thin bodies of revolution.
                      Axial-incidence backscatter RCS.
                      Long thin parabolic ogive - MISSILE NOISE CONE.
                      Formula 5.2-10
                  */

                 
                   __m512 rcs_f5210_zmm16r4(const __m512 gam0,
                                            const __m512 alp,
                                            const __m512 k0a) {

                        const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                        const __m512 _1     = _mm512_set1_ps(1.0f);  
                        const __m512 _3     = _mm512_set1_ps(3.0f);
                        const __m512 _4     = _mm512_set1_ps(4.0f);
                        register __m512 rcs,gam2,talp,talp2,talp4,_2k0a;
                        register __m512 k0as,ear,eai,cer,cei,cabs,x0,x1;
                        register __m512 trm1,t0r,t0i,t1r,t1i,t2r,t2i,trm2r,trm2i;
                        gam2  = _mm512_mul_ps(gam0,gam0);
                        talp  = xtanf(alp);
                        _2k0a = _mm512_add_ps(k0a,k0a);
                        k0as  = _mm512_mul_ps(_4,_mm512_mul_ps(k0a,k0a));
                        talp2 = _mm512_mul_ps(talp,talp);
                        ear   = _mm512_setzero_ps();
                        talp4 = _mm512_mul_ps(talp2,talp2);
                        x0    = _mm512_div_ps(_3,_2k0a);
                        eai   = _mm512_add_ps(_2k0a,_2k0a);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_16pi);
                        t0r   = _mm512_sub_ps(_1,cer);
                        t0i   = _mm512_sub_ps(_1,cei);
                        x1    = _mm512_div_ps(_3,k0as);
                        t2r   = _mm512_mul_ps(x1,t0r);
                        t1r   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cer));
                        t2i   = _mm512_mul_ps(x1,t0i);
                        t1i   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cei));
                        trm2r = _mm512_sub_ps(t0r,_mm512_sub_ps(t1r,t2r));
                        trm2i = _mm512_sub_ps(t0i,_mm512_sub_ps(t1i,t2i));
                        cabs  = cabs_zmm16r4(trm2r,trm2i);
                        rcs   = _mm512_mul_ps(trm1,cabs);
                        return (rcs);                 
                }


                  
                   __m512 rcs_f5210_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                               const float * __restrict __ATTR_ALIGN__(64) palp,
                                               const float * __restrict __ATTR_ALIGN__(64) pk0a) {

                        register __m512  gam0     = _mm512_load_ps(&pgam0[0]);
                        register __m512  alp      = _mm512_load_ps(&palp[0]);
                        register __m512  k0s      = _mm512_load_ps(&pk0a[0]); 
                        const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                        const __m512 _1     = _mm512_set1_ps(1.0f);  
                        const __m512 _3     = _mm512_set1_ps(3.0f);
                        const __m512 _4     = _mm512_set1_ps(4.0f);
                        register __m512 rcs,gam2,talp,talp2,talp4,_2k0a;
                        register __m512 k0as,ear,eai,cer,cei,cabs,x0,x1;
                        register __m512 trm1,t0r,t0i,t1r,t1i,t2r,t2i,trm2r,trm2i;
                        gam2  = _mm512_mul_ps(gam0,gam0);
                        talp  = xtanf(alp);
                        _2k0a = _mm512_add_ps(k0a,k0a);
                        k0as  = _mm512_mul_ps(_4,_mm512_mul_ps(k0a,k0a));
                        talp2 = _mm512_mul_ps(talp,talp);
                        ear   = _mm512_setzero_ps();
                        talp4 = _mm512_mul_ps(talp2,talp2);
                        x0    = _mm512_div_ps(_3,_2k0a);
                        eai   = _mm512_add_ps(_2k0a,_2k0a);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_16pi);
                        t0r   = _mm512_sub_ps(_1,cer);
                        t0i   = _mm512_sub_ps(_1,cei);
                        x1    = _mm512_div_ps(_3,k0as);
                        t2r   = _mm512_mul_ps(x1,t0r);
                        t1r   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cer));
                        t2i   = _mm512_mul_ps(x1,t0i);
                        t1i   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cei));
                        trm2r = _mm512_sub_ps(t0r,_mm512_sub_ps(t1r,t2r));
                        trm2i = _mm512_sub_ps(t0i,_mm512_sub_ps(t1i,t2i));
                        cabs  = cabs_zmm16r4(trm2r,trm2i);
                        rcs   = _mm512_mul_ps(trm1,cabs);
                        return (rcs);                 
                }


               
                   __m512 rcs_f5210_zmm16r4_u( const float * __restrict  pgam0,
                                               const float * __restrict  palp,
                                               const float * __restrict  pk0a,) {

                        register __m512  gam0     = _mm512_loadu_ps(&pgam0[0]);
                        register __m512  alp      = _mm512_loadu_ps(&palp[0]);
                        register __m512  k0s      = _mm512_loadu_ps(&pk0a[0]); 
                        const __m512 _16pi  = _mm512_set1_ps(50.265482457436691815402294132472f);
                        const __m512 _1     = _mm512_set1_ps(1.0f);  
                        const __m512 _3     = _mm512_set1_ps(3.0f);
                        const __m512 _4     = _mm512_set1_ps(4.0f);
                        register __m512 rcs,gam2,talp,talp2,talp4,_2k0a;
                        register __m512 k0as,ear,eai,cer,cei,cabs,x0,x1;
                        register __m512 trm1,t0r,t0i,t1r,t1i,t2r,t2i,trm2r,trm2i;
                        gam2  = _mm512_mul_ps(gam0,gam0);
                        talp  = xtanf(alp);
                        _2k0a = _mm512_add_ps(k0a,k0a);
                        k0as  = _mm512_mul_ps(_4,_mm512_mul_ps(k0a,k0a));
                        talp2 = _mm512_mul_ps(talp,talp);
                        ear   = _mm512_setzero_ps();
                        talp4 = _mm512_mul_ps(talp2,talp2);
                        x0    = _mm512_div_ps(_3,_2k0a);
                        eai   = _mm512_add_ps(_2k0a,_2k0a);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_16pi);
                        t0r   = _mm512_sub_ps(_1,cer);
                        t0i   = _mm512_sub_ps(_1,cei);
                        x1    = _mm512_div_ps(_3,k0as);
                        t2r   = _mm512_mul_ps(x1,t0r);
                        t1r   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cer));
                        t2i   = _mm512_mul_ps(x1,t0i);
                        t1i   = _mm512_mul_ps(x0,_mm512_add_ps(_1,cei));
                        trm2r = _mm512_sub_ps(t0r,_mm512_sub_ps(t1r,t2r));
                        trm2i = _mm512_sub_ps(t0i,_mm512_sub_ps(t1i,t2i));
                        cabs  = cabs_zmm16r4(trm2r,trm2i);
                        rcs   = _mm512_mul_ps(trm1,cabs);
                        return (rcs);                 
                }


                 /*
                      Long thin bodies of revolution.
                      Axial-incidence backscatter RCS.
                      High-frequency limit.
                      Long thin parabolic ogive - MISSILE NOISE CONE.
                      Formula 5.2-12
                  */


               
                   __m512 rcs_f5212_zmm16r4(const __m512 gam0,
                                            const __m512 alp,
                                            const __m512 k0a) {

                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _8pi   = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 rcs,gam2,talp,talp2,talp4,arg,carg,x0,rat;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          arg = _mm512_mul_ps(_4,k0a);
                          talp = xtanf(alp);
                          carg = xcosf(arg);
                          talp2= _mm512_mul_ps(talp,talp);
                          x0   = _mm512_add_ps(_1,carg);
                          talp4= _mm512_mul_ps(talp2,talp2);
                          rat  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_8pi);
                          rcs  = _mm512_mul_ps(rat,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5212_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                               const float * __restrict __ATTR_ALIGN__(64) palp,
                                               const float * __restrict __ATTR_ALIGN__(64) pk0a) {

                          register __m512  gam0     = _mm512_load_ps(&pgam0[0]);
                          register __m512  alp      = _mm512_load_ps(&palp[0]);
                          register __m512  k0s      = _mm512_load_ps(&pk0a[0]); 
                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _8pi   = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 rcs,gam2,talp,talp2,talp4,arg,carg,x0,rat;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          arg = _mm512_mul_ps(_4,k0a);
                          talp = xtanf(alp);
                          carg = xcosf(arg);
                          talp2= _mm512_mul_ps(talp,talp);
                          x0   = _mm512_add_ps(_1,carg);
                          talp4= _mm512_mul_ps(talp2,talp2);
                          rat  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_8pi);
                          rcs  = _mm512_mul_ps(rat,x0);
                          return (rcs);
                 }


                 
                   __m512 rcs_f5212_zmm16r4_u(const float * __restrict  pgam0,
                                               const float * __restrict palp,
                                               const float * __restrict  pk0a) {

                          register __m512  gam0     = _mm512_loadu_ps(&pgam0[0]);
                          register __m512  alp      = _mm512_loadu_ps(&palp[0]);
                          register __m512  k0s      = _mm512_loadu_ps(&pk0a[0]); 
                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _8pi   = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 rcs,gam2,talp,talp2,talp4,arg,carg,x0,rat;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          arg = _mm512_mul_ps(_4,k0a);
                          talp = xtanf(alp);
                          carg = xcosf(arg);
                          talp2= _mm512_mul_ps(talp,talp);
                          x0   = _mm512_add_ps(_1,carg);
                          talp4= _mm512_mul_ps(talp2,talp2);
                          rat  = _mm512_div_ps(_mm512_mul_ps(gam2,talp4),_8pi);
                          rcs  = _mm512_mul_ps(rat,x0);
                          return (rcs);
                 }


                    /*
                         Circular ogive nose-on RCS (en emprical solution).
                         Formula 5.2-14
                     */


                
                   __m512 rcs_f5214_zmm16r4(const __m512 gam0,
                                            const __m512 alp,
                                            const __m512 k0a) {

                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _2pi   = _mm512_set1_ps(6.283185307179586476925286766559f);
                          const __m512 pi     = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0     = _mm512_set1_ps(20000000000.0f);
                          const __m512 c1     = _mm512_set1_ps(4.3f);
                          const __m512 c2     = _mm512_set1_ps(1.25f);
                          register __m512 rcs,gam2,alp2,alp2p,s2alp,arg,sarg;
                          register __m512 num,den,rat,num1,den1;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          alp2  = _mm512_add_ps(alp,alp);
                          s2alp = xsinf(alp2);
                          num   = _mm512_mul_ps(_mm512_mul_ps(_4,k0a),alp);
                          den   = _mm512_mul_ps(pi,s2alp);
                          alp2p = _mm512_pow_ps(alp2,c1);
                          rat   = _mm512_sub_ps(_mm512_div_ps(num,den),c2);
                          num1  = _mm512_mul_ps(pi,_mm512_mul_ps(gam2,alp2p));
                          arg   = _mm512_mul_ps(_2pi,rat);
                          den1  = _mm512_div_ps(num1,c0);
                          sarg  = xsinf(arg);
                          rcs   = _mm512_mul_ps(den1,_mm512_add_ps(_1,sarg));
                          return (rcs);
                 }


                 
                   __m512 rcs_f5214_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0a) {

                          register __m512  gam0     = _mm512_load_ps(&pgam0[0]);
                          register __m512  alp      = _mm512_load_ps(&palp[0]);
                          register __m512  k0s      = _mm512_load_ps(&pk0a[0]); 
                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _2pi   = _mm512_set1_ps(6.283185307179586476925286766559f);
                          const __m512 pi     = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0     = _mm512_set1_ps(20000000000.0f);
                          const __m512 c1     = _mm512_set1_ps(4.3f);
                          const __m512 c2     = _mm512_set1_ps(1.25f);
                          register __m512 rcs,gam2,alp2,alp2p,s2alp,arg,sarg;
                          register __m512 num,den,rat,num1,den1;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          alp2  = _mm512_add_ps(alp,alp);
                          s2alp = xsinf(alp2);
                          num   = _mm512_mul_ps(_mm512_mul_ps(_4,k0a),alp);
                          den   = _mm512_mul_ps(pi,s2alp);
                          alp2p = _mm512_pow_ps(alp2,c1);
                          rat   = _mm512_sub_ps(_mm512_div_ps(num,den),c2);
                          num1  = _mm512_mul_ps(pi,_mm512_mul_ps(gam2,alp2p));
                          arg   = _mm512_mul_ps(_2pi,rat);
                          den1  = _mm512_div_ps(num1,c0);
                          sarg  = xsinf(arg);
                          rcs   = _mm512_mul_ps(den1,_mm512_add_ps(_1,sarg));
                          return (rcs);
                 }


                  
                   __m512 rcs_f5214_zmm16r4_u(const float * __restrict pgam0,
                                              const float * __restrict  palp,
                                              const float * __restrict  pk0a) {

                          register __m512  gam0     = _mm512_loadu_ps(&pgam0[0]);
                          register __m512  alp      = _mm512_loadu_ps(&palp[0]);
                          register __m512  k0s      = _mm512_loadu_ps(&pk0a[0]); 
                          const __m512 _1     = _mm512_set1_ps(1.0f);  
                          const __m512 _4     = _mm512_set1_ps(4.0f);
                          const __m512 _2pi   = _mm512_set1_ps(6.283185307179586476925286766559f);
                          const __m512 pi     = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0     = _mm512_set1_ps(20000000000.0f);
                          const __m512 c1     = _mm512_set1_ps(4.3f);
                          const __m512 c2     = _mm512_set1_ps(1.25f);
                          register __m512 rcs,gam2,alp2,alp2p,s2alp,arg,sarg;
                          register __m512 num,den,rat,num1,den1;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          alp2  = _mm512_add_ps(alp,alp);
                          s2alp = xsinf(alp2);
                          num   = _mm512_mul_ps(_mm512_mul_ps(_4,k0a),alp);
                          den   = _mm512_mul_ps(pi,s2alp);
                          alp2p = _mm512_pow_ps(alp2,c1);
                          rat   = _mm512_sub_ps(_mm512_div_ps(num,den),c2);
                          num1  = _mm512_mul_ps(pi,_mm512_mul_ps(gam2,alp2p));
                          arg   = _mm512_mul_ps(_2pi,rat);
                          den1  = _mm512_div_ps(num1,c0);
                          sarg  = xsinf(arg);
                          rcs   = _mm512_mul_ps(den1,_mm512_add_ps(_1,sarg));
                          return (rcs);
                 }


                 



                  


















