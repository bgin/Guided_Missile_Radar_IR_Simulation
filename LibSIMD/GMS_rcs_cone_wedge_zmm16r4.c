

#include "GMS_rcs_cone_wedge_zmm16r4.h"







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


#include "GMS_sleefsimdsp.h"
#include "GMS_complex_zmm16r4.h"






                   /*
                       Small-angle cone (alpha ~ 0).
                       Backscattered RCS.
                       Formula 6.2-12
                   */


                   __m512 rcs_f6212_zmm16r4(const __m512 gam0,
                                            const __m512 alp) {

                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          const __m512 _3    = _mm512_set1_ps(3.0f);
                          register __m512 rcs,gam2,calp,trm1,trm2,trm3,x0;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          calp  = xcosf(alp);
                          trm1  = _mm512_div_ps(gam2,_4pi);
                          x0    = _mm512_sub_ps(_1,calp);
                          trm3  = _mm512_fmadd_ps(_3,x0,_1);
                          trm2  = _mm512_mul_ps(x0,x0);
                          rcs   = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                  }


              
                   __m512 rcs_f6212_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          const __m512 _3    = _mm512_set1_ps(3.0f);
                          register __m512 rcs,gam2,calp,trm1,trm2,trm3,x0;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          calp  = xcosf(alp);
                          trm1  = _mm512_div_ps(gam2,_4pi);
                          x0    = _mm512_sub_ps(_1,calp);
                          trm3  = _mm512_fmadd_ps(_3,x0,_1);
                          trm2  = _mm512_mul_ps(x0,x0);
                          rcs   = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                  }


                
                   __m512 rcs_f6212_zmm16r4_u(const float * __restrict  pgam0,
                                              const float * __restrict  palp) {

                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          const __m512 _4pi  = _mm512_set1_ps(12.566370614359172953850573533118f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          const __m512 _3    = _mm512_set1_ps(3.0f);
                          register __m512 rcs,gam2,calp,trm1,trm2,trm3,x0;
                          gam2  = _mm512_mul_ps(gam0,gam0);
                          calp  = xcosf(alp);
                          trm1  = _mm512_div_ps(gam2,_4pi);
                          x0    = _mm512_sub_ps(_1,calp);
                          trm3  = _mm512_fmadd_ps(_3,x0,_1);
                          trm2  = _mm512_mul_ps(x0,x0);
                          rcs   = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                  }


                     /*
                           Small-angle cone (alpha ~ pi/2).
                           Backscattered RCS.
                           Formula 6.2-13
                       */

                
                   __m512 rcs_f6213_zmm16r4(const __m512 gam0,
                                            const __m512 alp) {

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,calp,calp2,calp4,gam2,trm1,trm2,x0;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          calp = xcosf(alp);
                          x0   = _mm512_div_ps(gam2,_16pi);
                          calp2= _mm512_mul_ps(calp,calp);
                          trm2 = _mm512_sub_ps(_1,_mm512_add_ps(calp2,calp2));
                          calp4= _mm512_mul_ps(calp2,calp2);
                          trm1 = _mm512_mul_ps(x0,calp4);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                  }


                 
                   __m512 rcs_f6213_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,calp,calp2,calp4,gam2,trm1,trm2,x0;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          calp = xcosf(alp);
                          x0   = _mm512_div_ps(gam2,_16pi);
                          calp2= _mm512_mul_ps(calp,calp);
                          trm2 = _mm512_sub_ps(_1,_mm512_add_ps(calp2,calp2));
                          calp4= _mm512_mul_ps(calp2,calp2);
                          trm1 = _mm512_mul_ps(x0,calp4);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                  }


                
                   __m512 rcs_f6213_zmm16r4_u(const float * __restrict  pgam0,
                                              const float * __restrict  palp) {

                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          const __m512 _1    = _mm512_set1_ps(1.0f);
                          register __m512 rcs,calp,calp2,calp4,gam2,trm1,trm2,x0;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          calp = xcosf(alp);
                          x0   = _mm512_div_ps(gam2,_16pi);
                          calp2= _mm512_mul_ps(calp,calp);
                          trm2 = _mm512_sub_ps(_1,_mm512_add_ps(calp2,calp2));
                          calp4= _mm512_mul_ps(calp2,calp2);
                          trm1 = _mm512_mul_ps(x0,calp4);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                  }


                   /*
                         Backscattering case.
                         E-field scattered for (phi component).
                         Formula 6.2-16
    
                     */


                 
                   void ESph_f6216_zmm16r4(const __m512 k0,
                                           const __m512 r,
                                           const __m512 alp,
                                           const __m512 tht,
                                           __m512 * __restrict ESr,
                                           __m512 * __restrict ESi) {
  
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _3  = _mm512_set1_ps(3.0f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        register __m512 k0r,inv,alph,alphs,ctht,t0r,t0i;
                        register __m512 ctht2,num,den,ear,eai,cer,cei,rat;
                        k0r  = _mm512_mul_ps(k0,r);
                        ctht = xcosf(tht);
                        alph = _mm512_mul_ps(alp,hlf);
                        ctht2= _mm512_mul_ps(ctht,ctht);
                        ear  = _mm512_setzero_ps();
                        ctht3= _mm512_mul_ps(ctht2,ctht);
                        eai  = k0r;
                        num  = _mm512_add_ps(_3,ctht2);
                        inv  = _mm512_rcp14_ps(k0r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        den  = _mm512_mul_ps(_4,ctht3);
                        t0r  = _mm512_mul_ps(cer,inv);
                        rat  = _mm512_div_ps(num,den);
                        t0i  = _mm512_mul_ps(cei,inv);
                        alphs= _mm512_mul_ps(_mm512_mul_ps(alph,alph),rat);
                        *ESr = _mm512_mul_ps(t0r,alphs);
                        *ESi = _mm512_mul_ps(t0i,alphs);
                 }


                 
                   void ESph_f6216_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pr,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht,
                                           float * __restrict __ATTR_ALIGN__(64) ESr,
                                           float * __restrict __ATTR_ALIGN__(64) ESi) {
  
                        register __m512 k0  = _mm512_load_ps(&pk0[0]);
                        register __m512 r   = _mm512_load_ps(&pr[0]);
                        register __m512 alp = _mm512_load_ps(&palp[0]);
                        register __m512 tht = _mm512_load_ps(&ptht[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _3  = _mm512_set1_ps(3.0f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        register __m512 k0r,inv,alph,alphs,ctht,t0r,t0i;
                        register __m512 ctht2,num,den,ear,eai,cer,cei,rat;
                        k0r  = _mm512_mul_ps(k0,r);
                        ctht = xcosf(tht);
                        alph = _mm512_mul_ps(alp,hlf);
                        ctht2= _mm512_mul_ps(ctht,ctht);
                        ear  = _mm512_setzero_ps();
                        ctht3= _mm512_mul_ps(ctht2,ctht);
                        eai  = k0r;
                        num  = _mm512_add_ps(_3,ctht2);
                        inv  = _mm512_rcp14_ps(k0r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        den  = _mm512_mul_ps(_4,ctht3);
                        t0r  = _mm512_mul_ps(cer,inv);
                        rat  = _mm512_div_ps(num,den);
                        t0i  = _mm512_mul_ps(cei,inv);
                        alphs= _mm512_mul_ps(_mm512_mul_ps(alph,alph),rat);
                        _mm512_store_ps(&ESr[0] ,_mm512_mul_ps(t0r,alphs));
                        _mm512_store_ps(&ESi[0] ,_mm512_mul_ps(t0i,alphs));
                 }


               
                   void ESph_f6216_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pr,
                                           const float * __restrict  palp,
                                           const float * __restrict  ptht,
                                           float * __restrict  ESr,
                                           float * __restrict  ESi) {
  
                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                        register __m512 r   = _mm512_loadu_ps(&pr[0]);
                        register __m512 alp = _mm512_loadu_ps(&palp[0]);
                        register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _3  = _mm512_set1_ps(3.0f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        register __m512 k0r,inv,alph,alphs,ctht,t0r,t0i;
                        register __m512 ctht2,num,den,ear,eai,cer,cei,rat;
                        k0r  = _mm512_mul_ps(k0,r);
                        ctht = xcosf(tht);
                        alph = _mm512_mul_ps(alp,hlf);
                        ctht2= _mm512_mul_ps(ctht,ctht);
                        ear  = _mm512_setzero_ps();
                        ctht3= _mm512_mul_ps(ctht2,ctht);
                        eai  = k0r;
                        num  = _mm512_add_ps(_3,ctht2);
                        inv  = _mm512_rcp14_ps(k0r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        den  = _mm512_mul_ps(_4,ctht3);
                        t0r  = _mm512_mul_ps(cer,inv);
                        rat  = _mm512_div_ps(num,den);
                        t0i  = _mm512_mul_ps(cei,inv);
                        alphs= _mm512_mul_ps(_mm512_mul_ps(alph,alph),rat);
                        _mm512_storeu_ps(&ESr[0] ,_mm512_mul_ps(t0r,alphs));
                        _mm512_storeu_ps(&ESi[0] ,_mm512_mul_ps(t0i,alphs));
                 }


                   /*
                         Bistatic RCS case.
                         E-field scattered for (theta component).
                         Formula 6.2-14
                    */


                 
                   void ESth_f6214_zmm16r4(const __m512 k0,
                                           const __m512 r,
                                           const __m512 alp,
                                           const __m512 tht1, //inc
                                           const __m512 tht2  //scat
                                           const __m512 phi1, //inc
                                           const __m512 phi2, //scat
                                           __m512 * __restrict ESr,
                                           __m512 * __restrict ESi) {

                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        register __m512 k0r,htht1,htht2,phid,ear,eai,cer,cei;
                        register __m512 sphid,t0r,t0i,num1,den1,num2,den2,inv;
                        register __m512 ctht1,ctht2,sect1,sect2,x0,x1,alp2;
                        register __m512 stht1,stht2,chtht1,chtht2,rat1,rat2,cx0,cx1;
                        phid   = _mm512_sub_ps(phi1,phi2);
                        k0r    = _mm512_mul_ps(k0,r);
                        htht1  = _mm512_mul_ps(tht1,hlf);
                        sphid  = xsinf(phid);
                        htht2  = _mm512_mul_ps(tht2,hlf);
                        inv    = _mm512_rcp14_ps(k0r);
                        ear    = _mm512_setzero_ps();
                        ctht1  = xcosf(tht1);
                        cx1    = _mm512_mul_ps(ctht1);
                        x0     = _mm512_mul_ps(alp,hlf);
                        ctht2  = xcosf(tht2);
                        cx2    = _mm512_mul_ps(ctht2,ctht2);
                        alp2   = _mm512_mul_ps(x0,x0);
                        chtht1 = xcosf(htht1);
                        eai    = k0r;
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sect1  = _mm512_rcp14_ps(chtht1);
                        den1   = _mm512_add_ps(ctht1,ctht2);
                        stht1  = xsinf(tht1);
                        t0r    = _mm512_mul_ps(cer,inv);
                        chtht2 = xcosf(htht2);
                        t0i    = _mm512_mul_ps(cei,inv);
                        sect2  = _mm512_rcp14_ps(chtht2);
                        stht2  = xsinf(tht2);
                        num2   = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        num1   = _mm512_fmadd_ps(sect1,sect1,_mm512_mul_ps(sect2,sect2));
                        x0     = _mm512_mul_ps(sphid,alp2);
                        rat1   = _mm512_div_ps(num1,den1);
                        x1     = _mm512_mul_ps(_2,_mm512_mul_ps(cx1,cx2));
                        sect1  = _mm512_add_ps(ctht1,ctht2);
                        sect2  = _mm512_mul_ps(sect1,sect1);
                        cer    = _mm512_mul_ps(t0r,x0);
                        den2   = _mm512_mul_ps(x1,sect2);
                        cei    = _mm512_mul_ps(t0i,x0);
                        rat2   = _mm512_div_ps(num2,den2);
                        *ESr   = _mm512_fmadd_ps(cer,rat1,rat2);
                        *ESi   = _mm512_fmadd_ps(cei,rat1,rat2);
                }


                
                   void ESth_f6214_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pr,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                           float * __restrict __ATTR_ALIGN__(64) ESr,
                                           float * __restrict __ATTR_ALIGN__(64) ESi) {

                        register __m512 k0   = _mm512_load_ps(&pk0[0]);
                        register __m512 r    = _mm512_load_ps(&pr[0]);
                        register __m512 alp  = _mm512_load_ps(&palp[0]);
                        register __m512 tht1 = _mm512_load_ps(&ptht1[0]);
                        register __m512 tht2 = _mm512_load_ps(&ptht2[0]);
                        register __m512 phi1 = _mm512_load_ps(&pphi1[0]);
                        register __m512 phi2 = _mm512_load_ps(&pphi2[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        register __m512 k0r,htht1,htht2,phid,ear,eai,cer,cei;
                        register __m512 sphid,t0r,t0i,num1,den1,num2,den2,inv;
                        register __m512 ctht1,ctht2,sect1,sect2,x0,x1,alp2;
                        register __m512 stht1,stht2,chtht1,chtht2,rat1,rat2,cx0,cx1;
                        phid   = _mm512_sub_ps(phi1,phi2);
                        k0r    = _mm512_mul_ps(k0,r);
                        htht1  = _mm512_mul_ps(tht1,hlf);
                        sphid  = xsinf(phid);
                        htht2  = _mm512_mul_ps(tht2,hlf);
                        inv    = _mm512_rcp14_ps(k0r);
                        ear    = _mm512_setzero_ps();
                        ctht1  = xcosf(tht1);
                        cx1    = _mm512_mul_ps(ctht1);
                        x0     = _mm512_mul_ps(alp,hlf);
                        ctht2  = xcosf(tht2);
                        cx2    = _mm512_mul_ps(ctht2,ctht2);
                        alp2   = _mm512_mul_ps(x0,x0);
                        chtht1 = xcosf(htht1);
                        eai    = k0r;
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sect1  = _mm512_rcp14_ps(chtht1);
                        den1   = _mm512_add_ps(ctht1,ctht2);
                        stht1  = xsinf(tht1);
                        t0r    = _mm512_mul_ps(cer,inv);
                        chtht2 = xcosf(htht2);
                        t0i    = _mm512_mul_ps(cei,inv);
                        sect2  = _mm512_rcp14_ps(chtht2);
                        stht2  = xsinf(tht2);
                        num2   = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        num1   = _mm512_fmadd_ps(sect1,sect1,_mm512_mul_ps(sect2,sect2));
                        x0     = _mm512_mul_ps(sphid,alp2);
                        rat1   = _mm512_div_ps(num1,den1);
                        x1     = _mm512_mul_ps(_2,_mm512_mul_ps(cx1,cx2));
                        sect1  = _mm512_add_ps(ctht1,ctht2);
                        sect2  = _mm512_mul_ps(sect1,sect1);
                        cer    = _mm512_mul_ps(t0r,x0);
                        den2   = _mm512_mul_ps(x1,sect2);
                        cei    = _mm512_mul_ps(t0i,x0);
                        rat2   = _mm512_div_ps(num2,den2);
                        _mm512_store_ps(&ESr[0] ,_mm512_fmadd_ps(cer,rat1,rat2));
                        _mm512_store_ps(&ESi[0] ,_mm512_fmadd_ps(cei,rat1,rat2));
                }


                
                   void ESth_f6214_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pr,
                                           const float * __restrict  palp,
                                           const float * __restrict  ptht1,
                                           const float * __restrict  ptht2,
                                           const float * __restrict  pphi1,
                                           const float * __restrict  pphi2,
                                           float * __restrict  ESr,
                                           float * __restrict  ESi) {

                        register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                        register __m512 r    = _mm512_loadu_ps(&pr[0]);
                        register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                        register __m512 tht1 = _mm512_loadu_ps(&ptht1[0]);
                        register __m512 tht2 = _mm512_loadu_ps(&ptht2[0]);
                        register __m512 phi1 = _mm512_loadu_ps(&pphi1[0]);
                        register __m512 phi2 = _mm512_loadu_ps(&pphi2[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        register __m512 k0r,htht1,htht2,phid,ear,eai,cer,cei;
                        register __m512 sphid,t0r,t0i,num1,den1,num2,den2,inv;
                        register __m512 ctht1,ctht2,sect1,sect2,x0,x1,alp2;
                        register __m512 stht1,stht2,chtht1,chtht2,rat1,rat2,cx0,cx1;
                        phid   = _mm512_sub_ps(phi1,phi2);
                        k0r    = _mm512_mul_ps(k0,r);
                        htht1  = _mm512_mul_ps(tht1,hlf);
                        sphid  = xsinf(phid);
                        htht2  = _mm512_mul_ps(tht2,hlf);
                        inv    = _mm512_rcp14_ps(k0r);
                        ear    = _mm512_setzero_ps();
                        ctht1  = xcosf(tht1);
                        cx1    = _mm512_mul_ps(ctht1);
                        x0     = _mm512_mul_ps(alp,hlf);
                        ctht2  = xcosf(tht2);
                        cx2    = _mm512_mul_ps(ctht2,ctht2);
                        alp2   = _mm512_mul_ps(x0,x0);
                        chtht1 = xcosf(htht1);
                        eai    = k0r;
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sect1  = _mm512_rcp14_ps(chtht1);
                        den1   = _mm512_add_ps(ctht1,ctht2);
                        stht1  = xsinf(tht1);
                        t0r    = _mm512_mul_ps(cer,inv);
                        chtht2 = xcosf(htht2);
                        t0i    = _mm512_mul_ps(cei,inv);
                        sect2  = _mm512_rcp14_ps(chtht2);
                        stht2  = xsinf(tht2);
                        num2   = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        num1   = _mm512_fmadd_ps(sect1,sect1,_mm512_mul_ps(sect2,sect2));
                        x0     = _mm512_mul_ps(sphid,alp2);
                        rat1   = _mm512_div_ps(num1,den1);
                        x1     = _mm512_mul_ps(_2,_mm512_mul_ps(cx1,cx2));
                        sect1  = _mm512_add_ps(ctht1,ctht2);
                        sect2  = _mm512_mul_ps(sect1,sect1);
                        cer    = _mm512_mul_ps(t0r,x0);
                        den2   = _mm512_mul_ps(x1,sect2);
                        cei    = _mm512_mul_ps(t0i,x0);
                        rat2   = _mm512_div_ps(num2,den2);
                        _mm512_storeu_ps(&ESr[0] ,_mm512_fmadd_ps(cer,rat1,rat2));
                        _mm512_storeu_ps(&ESi[0] ,_mm512_fmadd_ps(cei,rat1,rat2));
                }


                    /*
                           Bistatic RCS case.
                           E-field scattered for (phi component).
                           Formula 6.2-15
                      */


                 
                   void ESph_f6215_zmm16r4(const __m512 k0,
                                           const __m512 r,
                                           const __m512 alp,
                                           const __m512 tht1, //inc
                                           const __m512 tht2  //scat
                                           const __m512 phi1, //inc
                                           const __m512 phi2, //scat
                                           __m512 * __restrict ESr,
                                           __m512 * __restrict ESi) {

                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _16 = _mm512_set1_ps(16.0f);
                        register __m512 k0r,inv,alph,ear,eai,cer,cei;
                        register __m512 t0r,t0i,trm1,trm2,trm3,trm4;
                        register __m512 stht1,stht2,ctht1,ctht2;
                        register __m512 htht1,htht2,chtht1,chtht2;
                        register __m512 shtht1,shtht2,x0,x1,phid,cphid;
                        register __m512 ctht12,sect1,sect2,x2,x3,cthtp3;
                        k0r   = _mm512_mul_ps(k0,r);
                        stht1 = xsinf(tht1);
                        alph  = _mm512_mul_ps(alp,hlf);
                        ctht1 = xcosf(tht1);
                        phid  = _mm512_sub_ps(phi1,phi2);
                        stht2 = xsinf(tht2);
                        htht1 = _mm512_mul_ps(tht1,hlf);
                        ctht2 = xcosf(tht2);
                        ear   = _mm512_setzero_ps();
                        htht2 = _mm512_mul_ps(tht2);
                        eai   = k0r;
                        inv   = _mm512_rcp14_ps(k0r);
                        ctht12= _mm512_add_ps(ctht1,ctht2);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        x0    = _mm512_fmadd_ps(stht2,stht1,stht1);
                        chtht1= xcosf(htht1);
                        cer   = _mm512_mul_ps(_mm512_mul_ps(t0r,inv),alph);
                        cthtp3= _mm512_mul_ps(ctht12,_mm512_mul_ps(ctht12,ctht12));
                        cei   = _mm512_mul_ps(_mm512_mul_ps(t0i,inv),alph);
                        chtht2= xcosf(htht2);
                        trm1  = _mm512_div_ps(x0,cthtp3);
                        x2    = _mm512_rcp14_ps(chtht1);
                        shtht1= xsinf(htht1);
                        x3    = _mm512_rcp14_ps(chtht2);
                        shtht2= xsinf(htht2);
                        x0    = _mm512_fmadd_ps(x2,x2,_mm512_mul_ps(x3,x3));
                        trm2  = _mm512_div_ps(x0,ctht12);
                        x1    = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        x2    = _mm512_mul_ps(_2,_mm512_mul_ps(_mm512_mul_ps(chtht1,chtht1),
                                              _mm512_mul_ps(chtht2,chtht2)));
                        x3    = _mm512_mul_ps(ctht12,ctht12);
                        t0r   = _mm512_mul_ps(x2,x3);
                        trm3  = _mm512_div_ps(x1,t0r);
                        x0    = _mm512_mul_ps(_16,_mm512_mul_ps(shtht1,shtht1));
                        cphid = xcosf(phid);
                        x1    = _mm512_mul_ps(shtht2,shtht2);
                        x2    = _mm512_mul_ps(x0,x1);
                        trm4  = _mm512_div_ps(x2,cthtp3);
                        x3    = _mm512_add_ps(trm1,cphid);
                        x4    = _mm512_add_ps(trm2,_mm512_add_ps(trm3,trm4));
                        x0    = _mm512_mul_ps(x3,x4);
                        *ESr  = _mm512_mul_ps(cer,x0);
                        *ESi  = _mm512_mul_ps(cei,x0);
                                                
                }


                 
                   void ESph_f6215_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pr,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                           float * __restrict __ATTR_ALIGN__(64) ESr,
                                           float * __restrict __ATTR_ALIGN__(64) ESi) {

                        register __m512 k0   = _mm512_load_ps(&pk0[0]);
                        register __m512 r    = _mm512_load_ps(&pr[0]);
                        register __m512 alp  = _mm512_load_ps(&palp[0]);
                        register __m512 tht1 = _mm512_load_ps(&ptht1[0]);
                        register __m512 tht2 = _mm512_load_ps(&ptht2[0]);
                        register __m512 phi1 = _mm512_load_ps(&pphi1[0]);
                        register __m512 phi2 = _mm512_load_ps(&pphi2[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _16 = _mm512_set1_ps(16.0f);
                        register __m512 k0r,inv,alph,ear,eai,cer,cei;
                        register __m512 t0r,t0i,trm1,trm2,trm3,trm4;
                        register __m512 stht1,stht2,ctht1,ctht2;
                        register __m512 htht1,htht2,chtht1,chtht2;
                        register __m512 shtht1,shtht2,x0,x1,phid,cphid;
                        register __m512 ctht12,sect1,sect2,x2,x3,cthtp3;
                        k0r   = _mm512_mul_ps(k0,r);
                        stht1 = xsinf(tht1);
                        alph  = _mm512_mul_ps(alp,hlf);
                        ctht1 = xcosf(tht1);
                        phid  = _mm512_sub_ps(phi1,phi2);
                        stht2 = xsinf(tht2);
                        htht1 = _mm512_mul_ps(tht1,hlf);
                        ctht2 = xcosf(tht2);
                        ear   = _mm512_setzero_ps();
                        htht2 = _mm512_mul_ps(tht2);
                        eai   = k0r;
                        inv   = _mm512_rcp14_ps(k0r);
                        ctht12= _mm512_add_ps(ctht1,ctht2);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        x0    = _mm512_fmadd_ps(stht2,stht1,stht1);
                        chtht1= xcosf(htht1);
                        cer   = _mm512_mul_ps(_mm512_mul_ps(t0r,inv),alph);
                        cthtp3= _mm512_mul_ps(ctht12,_mm512_mul_ps(ctht12,ctht12));
                        cei   = _mm512_mul_ps(_mm512_mul_ps(t0i,inv),alph);
                        chtht2= xcosf(htht2);
                        trm1  = _mm512_div_ps(x0,cthtp3);
                        x2    = _mm512_rcp14_ps(chtht1);
                        shtht1= xsinf(htht1);
                        x3    = _mm512_rcp14_ps(chtht2);
                        shtht2= xsinf(htht2);
                        x0    = _mm512_fmadd_ps(x2,x2,_mm512_mul_ps(x3,x3));
                        trm2  = _mm512_div_ps(x0,ctht12);
                        x1    = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        x2    = _mm512_mul_ps(_2,_mm512_mul_ps(_mm512_mul_ps(chtht1,chtht1),
                                              _mm512_mul_ps(chtht2,chtht2)));
                        x3    = _mm512_mul_ps(ctht12,ctht12);
                        t0r   = _mm512_mul_ps(x2,x3);
                        trm3  = _mm512_div_ps(x1,t0r);
                        x0    = _mm512_mul_ps(_16,_mm512_mul_ps(shtht1,shtht1));
                        cphid = xcosf(phid);
                        x1    = _mm512_mul_ps(shtht2,shtht2);
                        x2    = _mm512_mul_ps(x0,x1);
                        trm4  = _mm512_div_ps(x2,cthtp3);
                        x3    = _mm512_add_ps(trm1,cphid);
                        x4    = _mm512_add_ps(trm2,_mm512_add_ps(trm3,trm4));
                        x0    = _mm512_mul_ps(x3,x4);
                        _mm512_store_ps(&ESr[0] ,_mm512_mul_ps(cer,x0));
                        _mm512_store_ps(&ESi[0] ,_mm512_mul_ps(cei,x0));
                                                
                }


                 
                   void ESph_f6215_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pr,
                                           const float * __restrict  palp,
                                           const float * __restrict  ptht1,
                                           const float * __restrict  ptht2,
                                           const float * __restrict  pphi1,
                                           const float * __restrict  pphi2,
                                           float * __restrict  ESr,
                                           float * __restrict  ESi) {

                        register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                        register __m512 r    = _mm512_loadu_ps(&pr[0]);
                        register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                        register __m512 tht1 = _mm512_loadu_ps(&ptht1[0]);
                        register __m512 tht2 = _mm512_loadu_ps(&ptht2[0]);
                        register __m512 phi1 = _mm512_loadu_ps(&pphi1[0]);
                        register __m512 phi2 = _mm512_loadu_ps(&pphi2[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _16 = _mm512_set1_ps(16.0f);
                        register __m512 k0r,inv,alph,ear,eai,cer,cei;
                        register __m512 t0r,t0i,trm1,trm2,trm3,trm4;
                        register __m512 stht1,stht2,ctht1,ctht2;
                        register __m512 htht1,htht2,chtht1,chtht2;
                        register __m512 shtht1,shtht2,x0,x1,phid,cphid;
                        register __m512 ctht12,sect1,sect2,x2,x3,cthtp3;
                        k0r   = _mm512_mul_ps(k0,r);
                        stht1 = xsinf(tht1);
                        alph  = _mm512_mul_ps(alp,hlf);
                        ctht1 = xcosf(tht1);
                        phid  = _mm512_sub_ps(phi1,phi2);
                        stht2 = xsinf(tht2);
                        htht1 = _mm512_mul_ps(tht1,hlf);
                        ctht2 = xcosf(tht2);
                        ear   = _mm512_setzero_ps();
                        htht2 = _mm512_mul_ps(tht2);
                        eai   = k0r;
                        inv   = _mm512_rcp14_ps(k0r);
                        ctht12= _mm512_add_ps(ctht1,ctht2);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        x0    = _mm512_fmadd_ps(stht2,stht1,stht1);
                        chtht1= xcosf(htht1);
                        cer   = _mm512_mul_ps(_mm512_mul_ps(t0r,inv),alph);
                        cthtp3= _mm512_mul_ps(ctht12,_mm512_mul_ps(ctht12,ctht12));
                        cei   = _mm512_mul_ps(_mm512_mul_ps(t0i,inv),alph);
                        chtht2= xcosf(htht2);
                        trm1  = _mm512_div_ps(x0,cthtp3);
                        x2    = _mm512_rcp14_ps(chtht1);
                        shtht1= xsinf(htht1);
                        x3    = _mm512_rcp14_ps(chtht2);
                        shtht2= xsinf(htht2);
                        x0    = _mm512_fmadd_ps(x2,x2,_mm512_mul_ps(x3,x3));
                        trm2  = _mm512_div_ps(x0,ctht12);
                        x1    = _mm512_fmadd_ps(stht1,stht1,_mm512_mul_ps(stht2,stht2));
                        x2    = _mm512_mul_ps(_2,_mm512_mul_ps(_mm512_mul_ps(chtht1,chtht1),
                                              _mm512_mul_ps(chtht2,chtht2)));
                        x3    = _mm512_mul_ps(ctht12,ctht12);
                        t0r   = _mm512_mul_ps(x2,x3);
                        trm3  = _mm512_div_ps(x1,t0r);
                        x0    = _mm512_mul_ps(_16,_mm512_mul_ps(shtht1,shtht1));
                        cphid = xcosf(phid);
                        x1    = _mm512_mul_ps(shtht2,shtht2);
                        x2    = _mm512_mul_ps(x0,x1);
                        trm4  = _mm512_div_ps(x2,cthtp3);
                        x3    = _mm512_add_ps(trm1,cphid);
                        x4    = _mm512_add_ps(trm2,_mm512_add_ps(trm3,trm4));
                        x0    = _mm512_mul_ps(x3,x4);
                        _mm512_storeu_ps(&ESr[0] ,_mm512_mul_ps(cer,x0));
                        _mm512_storeu_ps(&ESi[0] ,_mm512_mul_ps(cei,x0));
                                                
                }


                  /*
                           Bistatic RCS case -- Physical Optics approximated.
                           E-field scattered for (theta component).
                           Formula 6.2-17
                    */

#include "GMS_simd_utils.h"

                 
                   void ESth_f6217_zmm16r4(const __m512 k0,
                                           const __m512 r,
                                           const __m512 alp,
                                           const __m512 tht,
                                           const __m512 phi,
                                           __m512 * __restrict ESr,
                                           __m512 * __restrict ESi) {

                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,cphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         cphi  = xcosf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         *ESr  = _mm512_mul_ps(cer,t0i);
                         *ESi  = _mm512_mul_ps(cei,t0i);
                }


                
                   void ESth_f6217_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pr,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi,
                                           float * __restrict __ATTR_ALIGN__(64) ESr,
                                           float * __restrict __ATTR_ALIGN__(64) ESi) {

                         register __m512 k0   = _mm512_load_ps(&pk0[0]);
                         register __m512 r    = _mm512_load_ps(&pr[0]);
                         register __m512 alp  = _mm512_load_ps(&palp[0]);
                         register __m512 tht  = _mm512_load_ps(&ptht[0]);
                         register __m512 phi = _mm512_load_ps(&pphi[0]);
                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,cphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         cphi  = xcosf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         _mm512_store_ps(&ESr[0] ,_mm512_mul_ps(cer,t0i));
                         _mm512_store_ps(&ESi[0] ,_mm512_mul_ps(cei,t0i));
                }


                  
                   void ESth_f6217_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pr,
                                           const float * __restrict  palp,
                                           const float * __restrict  ptht,
                                           const float * __restrict  pphi,
                                           float * __restrict  ESr,
                                           float * __restrict  ESi) {

                         register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                         register __m512 r    = _mm512_loadu_ps(&pr[0]);
                         register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                         register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                         register __m512 phi  = _mm512_loadu_ps(&pphi[0]);
                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,cphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         cphi  = xcosf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         _mm512_storeu_ps(&ESr[0] ,_mm512_mul_ps(cer,t0i));
                         _mm512_storeu_ps(&ESi[0] ,_mm512_mul_ps(cei,t0i));
                }


                    /*
                           Bistatic RCS case -- Physical Optics approximated.
                           E-field scattered for (phi component).
                           Formula 6.2-18
                      */


                 
                   void ESph_f6218_zmm16r4(const __m512 k0,
                                           const __m512 r,
                                           const __m512 alp,
                                           const __m512 tht,
                                           const __m512 phi,
                                           __m512 * __restrict ESr,
                                           __m512 * __restrict ESi) {
                        
                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         const __m512 n1  = _mm512_set1_ps(-1.0f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,sphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         sphi  = xsinf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         *ESr  = _mm512_mul_ps(n1,_mm512_mul_ps(cer,t0i)));
                         *ESi  = _mm512_mul_ps(n1,_mm512_mul_ps(cei,t0i)));
                }


                 
                   void ESph_f6218_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pr,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht,
                                           const float * __restrict __ATTR_ALIGN__(64) pphi,
                                           float * __restrict __ATTR_ALIGN__(64) ESr,
                                           float * __restrict __ATTR_ALIGN__(64) ESi) {

                         register __m512 k0   = _mm512_load_ps(&pk0[0]);
                         register __m512 r    = _mm512_load_ps(&pr[0]);
                         register __m512 alp  = _mm512_load_ps(&palp[0]);
                         register __m512 tht  = _mm512_load_ps(&ptht[0]);
                         register __m512 phi = _mm512_load_ps(&pphi[0]);
                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         const __m512 n1  = _mm512_set1_ps(-1.0f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,sphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         sphi  = xsinf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         _mm512_store_ps(&ESr[0]  ,_mm512_mul_ps(n1,_mm512_mul_ps(cer,t0i)));
                         _mm512_store_ps(&ESi[0]  ,_mm512_mul_ps(n1,_mm512_mul_ps(cei,t0i)));
                }


                  
                   void ESph_f6218_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pr,
                                           const float * __restrict  palp,
                                           const float * __restrict  ptht,
                                           const float * __restrict  pphi,
                                           float * __restrict  ESr,
                                           float * __restrict  ESi) {

                         register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                         register __m512 r    = _mm512_loadu_ps(&pr[0]);
                         register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                         register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                         register __m512 phi  = _mm512_loadu_ps(&pphi[0]);
                         const __m512 hlf = _mm512_set1_ps(0.5f);
                         const __m512 _4  = _mm512_set1_ps(4.0f);
                         const __m512 c0  = _mm512_set1_ps(1.5f);
                         const __m512 n1  = _mm512_set1_ps(-1.0f);
                         register __m512 k0r,ear,eai,cer,cei,t0r,t0i,inv,x0,chtht;
                         register __m512 L,sphi,cosa,sina,htht,argm,argp,num,den;
                         k0r   = _mm512_mul_ps(k0,r);
                         sphi  = xsinf(phi);
                         htht  = _mm512_mul_ps(tht,hlf);
                         cosa  = xcosf(alp);
                         ear   = _mm512_setzero_ps();
                         inv   = _mm512_rcp14_ps(k0r);
                         eai   = k0r;
                         argm  = _mm512_add_ps(alp,htht);
                         cexp_zmm16r4(ear,eai,&t0r,&t0i);
                         argp  = _mm512_sub_ps(alp,htht);
                         sina  = xsinf(alp);
                         x0    = _mm512_mul_ps(sina,sina);
                         chtht = xcosf(htht);
                         cer   = _mm512_mul_ps(t0r,inv);
                         num   = _mm512_mul_ps(negate_zmm16r4(x0),cosa);
                         cei   = _mm512_mul_ps(t0i,inv);
                         ear   = xcosf(argp);
                         eai   = xcosf(argm);
                         x0    = _mm512_pow_ps(_mm512_add_ps(ear,eai),c0);
                         den   = _mm512_mul_ps(_mm512_mul_ps(_4,chtht),x0);
                         L     = _mm512_div_ps(num,den);
                         t0i   = _mm512_mul_ps(L,cphi);
                         _mm512_storeu_ps(&ESr[0]  ,_mm512_mul_ps(n1,_mm512_mul_ps(cer,t0i)));
                         _mm512_storeu_ps(&ESi[0]  ,_mm512_mul_ps(n1,_mm512_mul_ps(cei,t0i)));
                }



                    /*
                           Physical-Optics axial-incidence bistatic RCS
                           function of theta for (0 << theta < PI-2*alpha)
                           Formula 6.2-20
                      */


                 
                   __m512 rcs_f6220_zmm16r4(const __m512 gam0,
                                            const __m512 alp,
                                            const __m512 tht) {

                           const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                           const __m512 _1    = _mm512_set1_ps(1.0f);
                           register __m512 rcs,gam2,tana,tan4,x0,x1,trm1;
                           register __m512 alp2,calp2,ctht,trm2,num,den,x2;
                           gam2  = _mm512_mul_ps(gam0,gam0);
                           tana  = xtanf(alp);
                           alp2  = _mm512_add_ps(alp,alp);
                           calp2 = xcosf(alp2);
                           x0    = _mm512_mul_ps(tana,tana);
                           x1    = _mm512_add_ps(_1,calp2);
                           x2    = _mm512_mul_ps(x0,x0);
                           ctht  = xcosf(tht);
                           trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,x2),_16pi);
                           x0    = _mm512_add_ps(_1,ctht);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           num   = _mm512_add_ps(x2,x2);
                           x1    = _mm512_add_ps(ctht,calp2);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           den   = _mm512_mul_ps(x0,x2);
                           trm2  = _mm512_div_ps(num,den);
                           rcs   = _mm512_mul_ps(trm1,trm2);
                           return (rcs);
                  }


                
                   __m512 rcs_f6220_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                            const float * __restrict __ATTR_ALIGN__(64) palp,
                                            const float * __restrict __ATTR_ALIGN__(64) ptht) {

                           register __m512  gam0  = _mm512_load_ps(&pgam0[0]);
                           register __m512  alp   = _mm512_load_ps(&palp[0]);
                           register __m512  tht   = _mm512_load_ps(&ptht[0]);
                           const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                           const __m512 _1    = _mm512_set1_ps(1.0f);
                           register __m512 rcs,gam2,tana,tan4,x0,x1,trm1;
                           register __m512 alp2,calp2,ctht,trm2,num,den,x2;
                           gam2  = _mm512_mul_ps(gam0,gam0);
                           tana  = xtanf(alp);
                           alp2  = _mm512_add_ps(alp,alp);
                           calp2 = xcosf(alp2);
                           x0    = _mm512_mul_ps(tana,tana);
                           x1    = _mm512_add_ps(_1,calp2);
                           x2    = _mm512_mul_ps(x0,x0);
                           ctht  = xcosf(tht);
                           trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,x2),_16pi);
                           x0    = _mm512_add_ps(_1,ctht);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           num   = _mm512_add_ps(x2,x2);
                           x1    = _mm512_add_ps(ctht,calp2);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           den   = _mm512_mul_ps(x0,x2);
                           trm2  = _mm512_div_ps(num,den);
                           rcs   = _mm512_mul_ps(trm1,trm2);
                           return (rcs);
                  }


                  
                   __m512 rcs_f6220_zmm16r4_u(const float * __restrict  pgam0,
                                            const float * __restrict  palp,
                                            const float * __restrict  ptht) {

                           register __m512  gam0  = _mm512_loadu_ps(&pgam0[0]);
                           register __m512  alp   = _mm512_loadu_ps(&palp[0]);
                           register __m512  tht   = _mm512_loadu_ps(&ptht[0]);
                           const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                           const __m512 _1    = _mm512_set1_ps(1.0f);
                           register __m512 rcs,gam2,tana,tan4,x0,x1,trm1;
                           register __m512 alp2,calp2,ctht,trm2,num,den,x2;
                           gam2  = _mm512_mul_ps(gam0,gam0);
                           tana  = xtanf(alp);
                           alp2  = _mm512_add_ps(alp,alp);
                           calp2 = xcosf(alp2);
                           x0    = _mm512_mul_ps(tana,tana);
                           x1    = _mm512_add_ps(_1,calp2);
                           x2    = _mm512_mul_ps(x0,x0);
                           ctht  = xcosf(tht);
                           trm1  = _mm512_div_ps(_mm512_mul_ps(gam2,x2),_16pi);
                           x0    = _mm512_add_ps(_1,ctht);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           num   = _mm512_add_ps(x2,x2);
                           x1    = _mm512_add_ps(ctht,calp2);
                           x2    = _mm512_mul_ps(x1,_mm512_mul_ps(x1,x1));
                           den   = _mm512_mul_ps(x0,x2);
                           trm2  = _mm512_div_ps(num,den);
                           rcs   = _mm512_mul_ps(trm1,trm2);
                           return (rcs);
                  }


                     /*
                           Axial incidence backscattering (theta = 0)
                           RCS (Spencer equation).
                           Formula 6.2-22
                       */

               
                   __m512 rcs_f6222_zmm16r4(const __m512 gam0,
                                        const __m512 alp) {

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 rcs,gam2,trm1,tana,x0,x1;
                          gam2 = _mm512_mul_ps(gam0,gam00;
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          x1   = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 }


                 
                   __m512 rcs_f6222_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                            const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512  gam0  = _mm512_load_ps(&pgam0[0]);
                          register __m512  alp   = _mm512_load_ps(&palp[0]);
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 rcs,gam2,trm1,tana,x0,x1;
                          gam2 = _mm512_mul_ps(gam0,gam00;
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          x1   = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 }


                  
                   __m512 rcs_f6222_zmm16r4_u(const float * __restrict  pgam0,
                                            const float * __restrict  palp) {

                          register __m512  gam0  = _mm512_loadu_ps(&pgam0[0]);
                          register __m512  alp   = _mm512_loadu_ps(&palp[0]);
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 rcs,gam2,trm1,tana,x0,x1;
                          gam2 = _mm512_mul_ps(gam0,gam00;
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          x1   = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 }


                    /*
                           Narrow-angle cone.
                           Scattered E-field.
                           Formula 6.2-24
                       */


                 
                   void ES_f6224_zmm16r4(const __m512 k0,
                                         const __m512 z,
                                         const __m512 alp,
                                         const __m512 x,
                                         const __m512 y,
                                         const __m512 z,
                                         __m512 * __restrict xre,
                                         __m512 * __restrict xim,
                                         __m512 * __restrict yre,
                                         __m512 * __restrict yim,
                                         __m512 * __restrict zre,
                                         __m512 * __restrict zim) {

                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 alph,x0,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        alph = _mm512_mul_ps(alp,hlf);
                        k0z  = _mm512_mul_ps(k0,z);
                        ear  = _mm512_setzero_ps();
                        inv  = _mm512_rcp14_ps(k0z);
                        eai  = k0z;
                        x0   = _mm512_mul_ps(alph,alph);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(x0,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(x0,_mm512_mul_ps(cei,inv));
                        *xre  = _mm512_mul_ps(x,cer);
                        *xim  = _mm512_mul_ps(x,cei);
                        *yre  = _mm512_mul_ps(y,cer);
                        *yim  = _mm512_mul_ps(y,cei);
                        *zre  = _mm512_mul_ps(z,cer);
                        *zim  = _mm512_mul_ps(z,cei);
                 }


                 
                   void ES_f6224_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pz,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) px,
                                           const float * __restrict __ATTR_ALIGN__(64) py,
                                           const float * __restrict __ATTR_ALIGN__(64) pz,
                                           float * __restrict __ATTR_ALIGN__(64) xre,
                                           float * __restrict __ATTR_ALIGN__(64) xim,
                                           float * __restrict __ATTR_ALIGN__(64) yre,
                                           float * __restrict __ATTR_ALIGN__(64) yim,
                                           float * __restrict __ATTR_ALIGN__(64) zre,
                                           float * __restrict __ATTR_ALIGN__(64) zim) {

                        register __m512 k0  = _mm512_load_ps(&pk0[0]);
                        register __m512 z   = _mm512_load_ps(&pz[0]);
                        register __m512 alp = _mm512_load_ps(&palp[0]);
                        register __m512 x   = _mm512_load_ps(&px[0]);
                        register __m512 y   = _mm512_load_ps(&py[0]);
                        register __m512 z   = _mm512_load_ps(&pz[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 alph,x0,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        alph = _mm512_mul_ps(alp,hlf);
                        k0z  = _mm512_mul_ps(k0,z);
                        ear  = _mm512_setzero_ps();
                        inv  = _mm512_rcp14_ps(k0z);
                        eai  = k0z;
                        x0   = _mm512_mul_ps(alph,alph);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(x0,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(x0,_mm512_mul_ps(cei,inv));
                        _mm512_store_ps(&xre[0] ,_mm512_mul_ps(x,cer));
                        _mm512_store_ps(&xim[0] ,_mm512_mul_ps(x,cei));
                        _mm512_store_ps(&yre[0] ,_mm512_mul_ps(y,cer));
                        _mm512_store_ps(&yim[0] ,_mm512_mul_ps(y,cei));
                        _mm512_store_ps(&zre[0] ,_mm512_mul_ps(z,cer));
                        _mm512_store_ps(&zim[0] ,_mm512_mul_ps(z,cei));
                 }


                 
                   void ES_f6224_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict pz,
                                           const float * __restrict palp,
                                           const float * __restrict  px,
                                           const float * __restrict  py,
                                           const float * __restrict  pz,
                                           float * __restrict  xre,
                                           float * __restrict  xim,
                                           float * __restrict  yre,
                                           float * __restrict  yim,
                                           float * __restrict  zre,
                                           float * __restrict  zim) {

                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                        register __m512 z   = _mm512_loadu_ps(&pz[0]);
                        register __m512 alp = _mm512_loadu_ps(&palp[0]);
                        register __m512 x   = _mm512_loadu_ps(&px[0]);
                        register __m512 y   = _mm512_loadu_ps(&py[0]);
                        register __m512 z   = _mm512_loadu_ps(&pz[0]);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 alph,x0,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        alph = _mm512_mul_ps(alp,hlf);
                        k0z  = _mm512_mul_ps(k0,z);
                        ear  = _mm512_setzero_ps();
                        inv  = _mm512_rcp14_ps(k0z);
                        eai  = k0z;
                        x0   = _mm512_mul_ps(alph,alph);
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(x0,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(x0,_mm512_mul_ps(cei,inv));
                        _mm512_storeu_ps(&xre[0] ,_mm512_mul_ps(x,cer));
                        _mm512_storeu_ps(&xim[0] ,_mm512_mul_ps(x,cei));
                        _mm512_storeu_ps(&yre[0] ,_mm512_mul_ps(y,cer));
                        _mm512_storeu_ps(&yim[0] ,_mm512_mul_ps(y,cei));
                        _mm512_storeu_ps(&zre[0] ,_mm512_mul_ps(z,cer));
                        _mm512_storeu_ps(&zim[0] ,_mm512_mul_ps(z,cei));
                 }


                     /*
                           Wide-angle cone.
                           Scattered E-field.
                           Formula 6.2-25
                       */


               
                   void ES_f6225_zmm16r4(const __m512 k0,
                                         const __m512 z,
                                         const __m512 alp,
                                         const __m512 x,
                                         const __m512 y,
                                         const __m512 z,
                                         __m512 * __restrict xre,
                                         __m512 * __restrict xim,
                                         __m512 * __restrict yre,
                                         __m512 * __restrict yim,
                                         __m512 * __restrict zre,
                                         __m512 * __restrict zim) {

                        const __m512 pi2 = _mm512_set1_ps(1.57079632679489661923132169164f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 pima,x0,pimas,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        pima = _mm512_sub_ps(pi2,alp);
                        k0z  = _mm512_mul_ps(k0,z);
                        pimas= _mm512_mul_ps(pima,pima);
                        ear  = _mm512_setzero_ps();
                        x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0z),pimas);
                        inv  = _mm512_rcp14_ps(x0);
                        eai  = k0z;
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(alph,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(alph,_mm512_mul_ps(cei,inv));
                        *xre  = _mm512_mul_ps(x,cer);
                        *xim  = _mm512_mul_ps(x,cei);
                        *yre  = _mm512_mul_ps(y,cer);
                        *yim  = _mm512_mul_ps(y,cei);
                        *zre  = _mm512_mul_ps(z,cer);
                        *zim  = _mm512_mul_ps(z,cei);
                 }


                 
                   void ES_f6225_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pz,
                                           const float * __restrict __ATTR_ALIGN__(64) palp,
                                           const float * __restrict __ATTR_ALIGN__(64) px,
                                           const float * __restrict __ATTR_ALIGN__(64) py,
                                           const float * __restrict __ATTR_ALIGN__(64) pz,
                                           float * __restrict __ATTR_ALIGN__(64) xre,
                                           float * __restrict __ATTR_ALIGN__(64) xim,
                                           float * __restrict __ATTR_ALIGN__(64) yre,
                                           float * __restrict __ATTR_ALIGN__(64) yim,
                                           float * __restrict __ATTR_ALIGN__(64) zre,
                                           float * __restrict __ATTR_ALIGN__(64) zim) {

                        register __m512 k0  = _mm512_load_ps(&pk0[0]);
                        register __m512 z   = _mm512_load_ps(&pz[0]);
                        register __m512 alp = _mm512_load_ps(&palp[0]);
                        register __m512 x   = _mm512_load_ps(&px[0]);
                        register __m512 y   = _mm512_load_ps(&py[0]);
                        register __m512 z   = _mm512_load_ps(&pz[0]);
                        const __m512 pi2 = _mm512_set1_ps(1.57079632679489661923132169164f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 pima,x0,pimas,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        pima = _mm512_sub_ps(pi2,alp);
                        k0z  = _mm512_mul_ps(k0,z);
                        pimas= _mm512_mul_ps(pima,pima);
                        ear  = _mm512_setzero_ps();
                        x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0z),pimas);
                        inv  = _mm512_rcp14_ps(x0);
                        eai  = k0z;
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(alph,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(alph,_mm512_mul_ps(cei,inv));
                        _mm512_store_ps(&xre[0] ,_mm512_mul_ps(x,cer));
                        _mm512_store_ps(&xim[0] ,_mm512_mul_ps(x,cei));
                        _mm512_store_ps(&yre[0] ,_mm512_mul_ps(y,cer));
                        _mm512_store_ps(&yim[0] ,_mm512_mul_ps(y,cei));
                        _mm512_store_ps(&zre[0] ,_mm512_mul_ps(z,cer));
                        _mm512_store_ps(&zim[0] ,_mm512_mul_ps(z,cei));
                 }


                 
                   void ES_f6225_zmm16r4_u(const float * __restrict  pk0,
                                           const float * __restrict  pz,
                                           const float * __restrict  palp,
                                           const float * __restrict  px,
                                           const float * __restrict  py,
                                           const float * __restrict  pz,
                                           float * __restrict  xre,
                                           float * __restrict  xim,
                                           float * __restrict  yre,
                                           float * __restrict  yim,
                                           float * __restrict  zre,
                                           float * __restrict  zim) {

                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                        register __m512 z   = _mm512_loadu_ps(&pz[0]);
                        register __m512 alp = _mm512_loadu_ps(&palp[0]);
                        register __m512 x   = _mm512_loadu_ps(&px[0]);
                        register __m512 y   = _mm512_loadu_ps(&py[0]);
                        register __m512 z   = _mm512_loadu_ps(&pz[0]);
                        const __m512 pi2 = _mm512_set1_ps(1.57079632679489661923132169164f);
                        const __m512 _4  = _mm512_set1_ps(4.0f);
                        const __m512 cr  = _mm512_set1_ps(0.0f);
                        const __m512 ci  = _mm512_set1_ps(1.0f);
                        register __m512 pima,x0,pimas,k0z,inv,ear,eai,cer,cei;
                        register __m512 t0r,t0i;
                        
                        pima = _mm512_sub_ps(pi2,alp);
                        k0z  = _mm512_mul_ps(k0,z);
                        pimas= _mm512_mul_ps(pima,pima);
                        ear  = _mm512_setzero_ps();
                        x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0z),pimas);
                        inv  = _mm512_rcp14_ps(x0);
                        eai  = k0z;
                        cexp_zmm16r4(ear,eai,&t0r,&t0i);
                        cmul_zmm16r4(t0r,t0i,cr,ci,&cer,&cei);
                        cer  = _mm512_mul_ps(alph,_mm512_mul_ps(cer,inv));
                        cei  = _mm512_mul_ps(alph,_mm512_mul_ps(cei,inv));
                        _mm512_storeu_ps(&xre[0] ,_mm512_mul_ps(x,cer));
                        _mm512_storeu_ps(&xim[0] ,_mm512_mul_ps(x,cei));
                        _mm512_storeu_ps(&yre[0] ,_mm512_mul_ps(y,cer));
                        _mm512_storeu_ps(&yim[0] ,_mm512_mul_ps(y,cei));
                        _mm512_storeu_ps(&zre[0] ,_mm512_mul_ps(z,cer));
                        _mm512_storeu_ps(&zim[0] ,_mm512_mul_ps(z,cei));
                 }


                   /*
                           Wide-angle cone.
                           Radar Cross Section (angle = 0)
                           Formula 6.2-26
                     */

                 
                   __m512 rcs_f6226_zmm16r4(const __m512 gam2,
                                            const __m512 alp) {

                         const __m512 pi2   = _mm512_set1_ps(1.57079632679489661923132169164f);
                         const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                         register __m512 rcs,gam2,trm1,inv,pim,x0,pim4;
                         gam2 = _mm512_mul_ps(gam0,gam0);
                         pim  = _mm512_sub_ps(pi2,alp);
                         trm1 = _mm512_div_ps(gam2,_16pi);
                         x0   = _mm512_mul_ps(pim,pim);
                         pim4 = _mm512_mul_ps(x0,x0);
                         inv  = _mm512_rcp14_ps(pim4);
                         rcs  = _mm512_mul_ps(trm1,inv);
                         return (rcs);
                 } 


                   __m512 rcs_f6226_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam2,
                                            const float * __restrict __ATTR_ALIGN__(64) palp) {

                         register __m512 gam2   = _mm512_load_ps(&pgam2[0]);
                         register __m512 alp = _mm512_load_ps(&palp[0]);
                         const __m512 pi2   = _mm512_set1_ps(1.57079632679489661923132169164f);
                         const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                         register __m512 rcs,gam2,trm1,inv,pim,x0,pim4;
                         gam2 = _mm512_mul_ps(gam0,gam0);
                         pim  = _mm512_sub_ps(pi2,alp);
                         trm1 = _mm512_div_ps(gam2,_16pi);
                         x0   = _mm512_mul_ps(pim,pim);
                         pim4 = _mm512_mul_ps(x0,x0);
                         inv  = _mm512_rcp14_ps(pim4);
                         rcs  = _mm512_mul_ps(trm1,inv);
                         return (rcs);
                 } 


                
                   __m512 rcs_f6226_zmm16r4_u(const float * __restrict  pgam2,
                                            const float * __restrict  palp) {

                         register __m512 gam2   = _mm512_loadu_ps(&pgam2[0]);
                         register __m512 alp = _mm512_loadu_ps(&palp[0]);
                         const __m512 pi2   = _mm512_set1_ps(1.57079632679489661923132169164f);
                         const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                         register __m512 rcs,gam2,trm1,inv,pim,x0,pim4;
                         gam2 = _mm512_mul_ps(gam0,gam0);
                         pim  = _mm512_sub_ps(pi2,alp);
                         trm1 = _mm512_div_ps(gam2,_16pi);
                         x0   = _mm512_mul_ps(pim,pim);
                         pim4 = _mm512_mul_ps(x0,x0);
                         inv  = _mm512_rcp14_ps(pim4);
                         rcs  = _mm512_mul_ps(trm1,inv);
                         return (rcs);
                 } 


                    /*
                          The concave-tip axial-incidence, Physical-Optics RCS.
                          Formula 6.2-29

                      */


                 
                   __m512 rcs_f6229_zmm16r4(const __m512 k0,
                                            const __m512 alp,
                                            const __m512 R) {

                           const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                           const __m512 _2   = _mm512_set1_ps(2.0f);
                           const __m512 _1   = _mm512_set1_ps(1.0f);
                           register __m512 rcs,trm1,ear1,eai1,ear2,eai2;
                           register __m512 cer1,cei1,cer2,cei2,inv1,inv2;
                           register __m512 t0r,t0i,x0,x1,k0R,R2,calp,x2,x3,t1r,t1i,cabs;
                           R2   = _m512_mul_ps(R,R);
                           x1   = _mm512_mul_ps(k0,k0);
                           calp = xcosf(alp);
                           k0R  = _mm512_mul_ps(k0,R);
                           x0   = _mm512_mul_ps(R2,R2);
                           ear1 = _mm512_setzero_ps();
                           trm1 = _mm512_mul_ps(_mm512_mul_ps(_4pi,x1),x0);
                           eai1 = _mm512_add_ps(k0R,k0R);
                           x0   = _mm512_mul_ps(eai1,eai1);
                           x1   = _mm512_sub_ps(eai1,_1);
                           inv1 = _mm512_rcp14_ps(x0);
                           cexp_zmm16r4(ear1,eai1,t0r,t0i);
                           x2   = _mm512_sub_ps(calp,_1);
                           cmul_zmm16r4(ear1,x1,t0r,t0i,&cer1,&cei1);
                           cer1 = _mm512_mul_ps(cer1,inv1);
                           cei1 = _mm512_mul_ps(cei1,inv1);
                           ear2 = ear1;
                           eai2 = _mm512_mul_ps(eai1,calp);
                           inv2 = _mm512_rcp14_ps(_mm512_mul_ps(eai2,eai2));
                           x3   = _mm512_mul_ps(eai1,x2); 
                           cexp_zmm16r4(ear2,eai2,t0r,t0i);
                           cmul_zmm16r4(ear2,x3,t0r,t0i,&cer2,&cei2);
                           cer2 = _mm512_mul_ps(cer2,inv2);
                           cei2 = _mm512_mul_ps(cei2,inv2);
                           t1r  = _mm512_sub_ps(cer1,cer2);
                           t1i  = _mm512_sub_ps(cei1,cei2);
                           cabs = cabs_zmm16r4(t1r,t1i);
                           rcs  = _mm512_mul_ps(trm1,cabs);
                           return (rcs);
                 }


                  
                   __m512 rcs_f6229_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pR) {

                           register __m512 k0     = _mm512_load_ps(&pk0[0]);
                           register __m512 alp    = _mm512_load_ps(&palp[0]);
                           register __m512 R      = _mm512_load_ps(&pR[0]);
                           const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                           const __m512 _2   = _mm512_set1_ps(2.0f);
                           const __m512 _1   = _mm512_set1_ps(1.0f);
                           register __m512 rcs,trm1,ear1,eai1,ear2,eai2;
                           register __m512 cer1,cei1,cer2,cei2,inv1,inv2;
                           register __m512 t0r,t0i,x0,x1,k0R,k0R2,R2,calp,x2,x3,t1r,t1i,cabs;
                           R2   = _m512_mul_ps(R,R);
                           x1   = _mm512_mul_ps(k0,k0);
                           calp = xcosf(alp);
                           k0R  = _mm512_mul_ps(k0,R);
                           x0   = _mm512_mul_ps(R2,R2);
                           ear1 = _mm512_setzero_ps();
                           trm1 = _mm512_mul_ps(_mm512_mul_ps(_4pi,x1),x0);
                           eai1 = _mm512_add_ps(k0R,k0R);
                           x0   = _mm512_mul_ps(eai1,eai1);
                           x1   = _mm512_sub_ps(eai1,_1);
                           inv1 = _mm512_rcp14_ps(x0);
                           cexp_zmm16r4(ear1,eai1,t0r,t0i);
                           x2   = _mm512_sub_ps(calp,_1);
                           cmul_zmm16r4(ear1,x1,t0r,t0i,&cer1,&cei1);
                           cer1 = _mm512_mul_ps(cer1,inv1);
                           cei1 = _mm512_mul_ps(cei1,inv1);
                           ear2 = ear1;
                           eai2 = _mm512_mul_ps(eai1,calp);
                           inv2 = _mm512_rcp14_ps(_mm512_mul_ps(eai2,eai2));
                           x3   = _mm512_mul_ps(eai1,x2); 
                           cexp_zmm16r4(ear2,eai2,t0r,t0i);
                           cmul_zmm16r4(ear2,x3,t0r,t0i,&cer2,&cei2);
                           cer2 = _mm512_mul_ps(cer2,inv2);
                           cei2 = _mm512_mul_ps(cei2,inv2);
                           t1r  = _mm512_sub_ps(cer1,cer2);
                           t1i  = _mm512_sub_ps(cei1,cei2);
                           cabs = cabs_zmm16r4(t1r,t1i);
                           rcs  = _mm512_mul_ps(trm1,cabs);
                           return (rcs);
                 }


                
                   __m512 rcs_f6229_zmm16r4_u(const float * __restrict  pk0,
                                              const float * __restrict  palp,
                                              const float * __restrict  pR) {

                           register __m512 k0     = _mm512_loadu_ps(&pk0[0]);
                           register __m512 alp    = _mm512_loadu_ps(&palp[0]);
                           register __m512 R      = _mm512_loadu_ps(&pR[0]);
                           const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                           const __m512 _2   = _mm512_set1_ps(2.0f);
                           const __m512 _1   = _mm512_set1_ps(1.0f);
                           register __m512 rcs,trm1,ear1,eai1,ear2,eai2;
                           register __m512 cer1,cei1,cer2,cei2,inv1,inv2;
                           register __m512 t0r,t0i,x0,x1,k0R,k0R2,R2,calp,x2,x3,t1r,t1i,cabs;
                           R2   = _m512_mul_ps(R,R);
                           x1   = _mm512_mul_ps(k0,k0);
                           calp = xcosf(alp);
                           k0R  = _mm512_mul_ps(k0,R);
                           x0   = _mm512_mul_ps(R2,R2);
                           ear1 = _mm512_setzero_ps();
                           trm1 = _mm512_mul_ps(_mm512_mul_ps(_4pi,x1),x0);
                           eai1 = _mm512_add_ps(k0R,k0R);
                           x0   = _mm512_mul_ps(eai1,eai1);
                           x1   = _mm512_sub_ps(eai1,_1);
                           inv1 = _mm512_rcp14_ps(x0);
                           cexp_zmm16r4(ear1,eai1,t0r,t0i);
                           x2   = _mm512_sub_ps(calp,_1);
                           cmul_zmm16r4(ear1,x1,t0r,t0i,&cer1,&cei1);
                           cer1 = _mm512_mul_ps(cer1,inv1);
                           cei1 = _mm512_mul_ps(cei1,inv1);
                           ear2 = ear1;
                           eai2 = _mm512_mul_ps(eai1,calp);
                           inv2 = _mm512_rcp14_ps(_mm512_mul_ps(eai2,eai2));
                           x3   = _mm512_mul_ps(eai1,x2); 
                           cexp_zmm16r4(ear2,eai2,t0r,t0i);
                           cmul_zmm16r4(ear2,x3,t0r,t0i,&cer2,&cei2);
                           cer2 = _mm512_mul_ps(cer2,inv2);
                           cei2 = _mm512_mul_ps(cei2,inv2);
                           t1r  = _mm512_sub_ps(cer1,cer2);
                           t1i  = _mm512_sub_ps(cei1,cei2);
                           cabs = cabs_zmm16r4(t1r,t1i);
                           rcs  = _mm512_mul_ps(trm1,cabs);
                           return (rcs);
                 }


                    /*
                           RCS of pointed cone and flat plate of radius b.
                           Formula 6.2-30
                      */


                 
                   __m512 rcs_f6230_zmm16r4(const __m512 b,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 b4,k02,k0b2,b2;
                          register __m512 trm1,trm1,rcs,x0;
                          b2  = _mm512_mul_ps(b,b);
                          k02 = _mm512_mul_ps(k0,k0);
                          b4  = _mm512_mul_ps(b2,b2);
                          k0b2= _mm512_mul_ps(k02,k02);
                          trm2= _mm512_mul_ps(k0b2,_mm512_mul_ps(pi,b2));
                          x0  = _mm512_mul_ps(_4,k02);
                          trm1= _mm512_div_ps(_mm512_mul_ps(pi,b4),x0);
                          rcs = _mm512_add_ps(trm1,trm2);
                          return (rcs);
                }


                  
                   __m512 rcs_f6230_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 b  = _mm512_load_ps(&pb[0]);
                          register __m512 k0 = _mm512_load_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 b4,k02,k0b2,b2;
                          register __m512 trm1,trm1,rcs,x0;
                          b2  = _mm512_mul_ps(b,b);
                          k02 = _mm512_mul_ps(k0,k0);
                          b4  = _mm512_mul_ps(b2,b2);
                          k0b2= _mm512_mul_ps(k02,k02);
                          trm2= _mm512_mul_ps(k0b2,_mm512_mul_ps(pi,b2));
                          x0  = _mm512_mul_ps(_4,k02);
                          trm1= _mm512_div_ps(_mm512_mul_ps(pi,b4),x0);
                          rcs = _mm512_add_ps(trm1,trm2);
                          return (rcs);
                }


                
                   __m512 rcs_f6230_zmm16r4_u(const float * __restrict  pb,
                                              const float * __restrict  pk0) {

                          register __m512 b  = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 b4,k02,k0b2,b2;
                          register __m512 trm1,trm1,rcs,x0;
                          b2  = _mm512_mul_ps(b,b);
                          k02 = _mm512_mul_ps(k0,k0);
                          b4  = _mm512_mul_ps(b2,b2);
                          k0b2= _mm512_mul_ps(k02,k02);
                          trm2= _mm512_mul_ps(k0b2,_mm512_mul_ps(pi,b2));
                          x0  = _mm512_mul_ps(_4,k02);
                          trm1= _mm512_div_ps(_mm512_mul_ps(pi,b4),x0);
                          rcs = _mm512_add_ps(trm1,trm2);
                          return (rcs);
                }


                  /*
                       Physical-Optics approximation of rounded-tip cone,
                       for axial incidence.
                       Formula 6.2-31
                   */


                 
                   __m512 rcs_f6231_zmm16r4(const __m512 alp,
                                            const __m512 k0,
                                            const __m512 b) {

                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 b2,k0b,_2k0b,k0b2,arg;
                          register __m512 sarg,carg,salp,calp,calp2,calp4;
                          register __m512 rcs,trm1,trm2,trm3,x0,x1;
                          b2   = _mm512_mul_ps(b,b);
                          calp = xcosf(alp);
                          k0b  = _mm512_mul_ps(k0,b);
                          calp2= _mm512_mul_ps(calp,calp);
                          _2k0b= _mm512_add_ps(k0b,k0b);
                          calp4= _mm512_mul_ps(calp2,calp2);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          salp = xsinf(alp);
                          arg  = _mm512_mul_ps(_2k0b,_mm512_sub_ps(_1,salp));
                          x0   = _mm512_mul_ps(k0b,calp2);
                          sarg = xsinf(arg);
                          x1   = _mm512_add_ps(_1,calp4);
                          trm1 = _mm512_div_ps(sarg,x0);
                          x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0b2),calp4);
                          trm2 = _mm512_div_ps(x1,x0);
                          carg = xcosf(arg);
                          x0   = _mm512_mul_ps(_mm512_add_ps(k0b2,k0b2),calp2);
                          trm3 = _mm512_div_ps(carg,x0);
                          x1   = _mm512_mul_ps(pi,b2);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm1),trm2);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(x0,trm3));
                          return (rcs);
                 }


                 
                   __m512 rcs_f6231_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) palp,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0,
                                            const float * __restrict __ATTR_ALIGN__(64) pb) {

                          register __m512 alp= _mm512_load_ps(&palp[0]);
                          register __m512 b  = _mm512_load_ps(&pb[0]);
                          register __m512 k0 = _mm512_load_ps(&pk0[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 b2,k0b,_2k0b,k0b2,arg;
                          register __m512 sarg,carg,salp,calp,calp2,calp4;
                          register __m512 rcs,trm1,trm2,trm3,x0,x1;
                          b2   = _mm512_mul_ps(b,b);
                          calp = xcosf(alp);
                          k0b  = _mm512_mul_ps(k0,b);
                          calp2= _mm512_mul_ps(calp,calp);
                          _2k0b= _mm512_add_ps(k0b,k0b);
                          calp4= _mm512_mul_ps(calp2,calp2);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          salp = xsinf(alp);
                          arg  = _mm512_mul_ps(_2k0b,_mm512_sub_ps(_1,salp));
                          x0   = _mm512_mul_ps(k0b,calp2);
                          sarg = xsinf(arg);
                          x1   = _mm512_add_ps(_1,calp4);
                          trm1 = _mm512_div_ps(sarg,x0);
                          x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0b2),calp4);
                          trm2 = _mm512_div_ps(x1,x0);
                          carg = xcosf(arg);
                          x0   = _mm512_mul_ps(_mm512_add_ps(k0b2,k0b2),calp2);
                          trm3 = _mm512_div_ps(carg,x0);
                          x1   = _mm512_mul_ps(pi,b2);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm1),trm2);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(x0,trm3));
                          return (rcs);
                 }


                  
                   __m512 rcs_f6231_zmm16r4_u(const float * __restrict  palp,
                                            const float * __restrict  pk0,
                                            const float * __restrict  pb) {

                          register __m512 alp= _mm512_loadu_ps(&palp[0]);
                          register __m512 b  = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 b2,k0b,_2k0b,k0b2,arg;
                          register __m512 sarg,carg,salp,calp,calp2,calp4;
                          register __m512 rcs,trm1,trm2,trm3,x0,x1;
                          b2   = _mm512_mul_ps(b,b);
                          calp = xcosf(alp);
                          k0b  = _mm512_mul_ps(k0,b);
                          calp2= _mm512_mul_ps(calp,calp);
                          _2k0b= _mm512_add_ps(k0b,k0b);
                          calp4= _mm512_mul_ps(calp2,calp2);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          salp = xsinf(alp);
                          arg  = _mm512_mul_ps(_2k0b,_mm512_sub_ps(_1,salp));
                          x0   = _mm512_mul_ps(k0b,calp2);
                          sarg = xsinf(arg);
                          x1   = _mm512_add_ps(_1,calp4);
                          trm1 = _mm512_div_ps(sarg,x0);
                          x0   = _mm512_mul_ps(_mm512_mul_ps(_4,k0b2),calp4);
                          trm2 = _mm512_div_ps(x1,x0);
                          carg = xcosf(arg);
                          x0   = _mm512_mul_ps(_mm512_add_ps(k0b2,k0b2),calp2);
                          trm3 = _mm512_div_ps(carg,x0);
                          x1   = _mm512_mul_ps(pi,b2);
                          x0   = _mm512_add_ps(_mm512_sub_ps(_1,trm1),trm2);
                          rcs  = _mm512_mul_ps(x0,_mm512_sub_ps(x0,trm3));
                          return (rcs);
                 }


                   /*
                          Not nose-one incidence, for theta << alpha -- 
                          PO approximation for rounded-tip cones.
                          Formula 6.2-23
                      */


                   __m512 rcs_f6223_zmm16r4(const __m512 tht,
                                            const __m512 k0,
                                            const __m512 b,
                                            const __m512 a,
                                            const __m512 alp) {

                          const __m512 hlf= _mm512_set1_ps(0.5f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 n4 = _mm512_set1_ps(-4.0f);
                          const __m512 _3 = _mm512_set1_ps(3.0f);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 n2 = _mm512_set1_ps(-2.0f);
                          const __m512 _6 = _mm512_set1_ps(6.0f);
                          const __m512 _8 = _mm512_set1_ps(8.0f);
                          const __m512 _13= _mm512_set1_ps(13.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 k0b,salp,arg,_2k0,b2,sarg,carg,ctht,a2,salp1,tht3;
                          register __m512 trm1,trm2,trm3;
                          register __m512 rcs,A1,A2,A3;
                          __m512 alp2,tht2,alp4,tht4,k0b2,k0b3,k0b4,a2,k0bt,k0a;
                          __m512 t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
                          __m512 t10,t11,t12,t13,t14,t15,t16,t17,t18,t19;
                          __m512 x0,x1,x2,x3,x4;
                          k0b  = _mm512_mul_ps(k0,b);
                          tht2 = _mm512_mul_ps(tht,tht);
                          _2k0 = _mm512_add_ps(k0,k0);
                          salp = xsinf(alp);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          ctht = xcosf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          salp1= _mm512_sub_ps(_1,salp);
                          k0a  = _mm512_mul_ps(k0,a);
                          alp2 = _mm512_mul_ps(alp,alp);
                          tht3 = _mm512_mul_ps(tht2,tht);
                          arg  = _mm512_mul_ps(_2k0,_mm512_mul_ps(calp,salp1));
                          tht4 = _mm512_mul_ps(tht2,tht2);
                          alp4 = _mm512_mul_ps(alp2,alp2);
                          k0b3 = _mm512_mul_ps(k0b2,k0b);
                          k0b4 = _mm512_mul_ps(k0b2,k0b2);
                          trm1 = _mm512_div_ps(_mm512_add_ps(_1,tht2),
                                               _mm512_mul_ps(_4,k0b2));
                          a2   = _mm512_mul_ps(a,a);
                          k0bt = _mm512_mul_ps(k0b,tht);
                          t0   = _mm512_add_ps(alp2,alp2); //2alp^2
                          t1   = _mm512_add_ps(tht2,tht2); //2tht^2
                          t2   = _mm512_mul_ps(alp2,tht2);//alp2*tht2
                          t3   = _mm512_mul_ps(tht4,hlf); //tht4*0.5
                          t4   = _mm512_mul_ps(_mm512_mul_ps(_2,alp4),tht2);//2*alp4*tht2
                          t5   = _mm512_mul_ps(_4,k0b2);//4*k0b2
                          t6   = _mm512_mul_ps(_mm512_mul_ps(_2,k0b2),tht2);//2*k0b2*tht2
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht2);//8*k0b3*tht2
                          t8   = _mm512_mul_ps(k0b2,tht4);//k0b2*tht4
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),
                                               _mm512_mul_ps(a2,tht2));//6*k0b2*a2*tht2
                          t10  = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht4);//8*k0b3*tht4
                          t11  = _mm512_mul_ps(_mm512_mul_ps(_13,k0b4),tht4);//13*k0b4*tht4
                          sarg = xsinf(arg);
                          x0   = _mm512_sub_ps(_mm512_add_ps(_2,t0),
                                               _mm512_add_ps(t1,alp4));
                          x1   = _mm512_add_ps(_mm512_add_ps(t2,t3),
                                               _mm512_add_ps(t4,t5));
                          x2   = _mm512_add_ps(_mm512_sub_ps(t6,t7),
                                               _mm512_add_ps(t8,t9));
                          x3   = _mm512_add_ps(t10,t11);
                          x4   = _mm512_sub_ps(x0,x1);
                          carg = xcosf(arg);
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),tht2);
                          A1   = _mm512_sub_ps(_mm512_sub_ps(x0,x1),
                                               _mm512_add_ps(x2,x3));
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b4),tht3);
                          x0   = _mm512_sub_ps(_mm512_sub_ps(n2,t0),
                                               _mm512_add_ps(t1,t2));
                          t8   = _mm512_mul_ps(_mm512_mul_ps(_3,k0b2),tht4);
                          x1   = _mm512_add_ps(_mm512_sub_ps(t3,t9),
                                               _mm512_add_ps(t7,t8));
                          A2   = _mm512_sub_ps(x0,x1);
                          t11  = _mm512_mul_ps(k0bt,k0bt);
                          t10  = _mm512_mul_ps(t11,k0bt);
                          t9   = _mm512_mul_ps(k0b,tht2);
                          t8   = _mm512_mul_ps(_3,_mm512_mul_ps(k0a,k0a));
                          x0   = _mm512_sub_ps(_mm512_add_ps(_1,alp2),
                                               _mm512_add_ps(t2,t8));
                          x1   = _mm512_sub_ps(k0b,_mm512_sub_ps(t9,t11));
                          A3   = _mm512_mul_ps(_mm512_mul_ps(n4,x0),
                                               _mm512_sub_ps(x1,_mm512_mul_ps(_4,t10)));
                          trm2 = _mm512_fmadd_ps(carg,A2,A1);
                          trm3 = _mm512_fmadd_ps(sarg,A3,trm2);
                          rcs  = _mm512_mul_ps(trm1,trm3);
                          return (rcs);
                 }


                 
                   __m512 rcs_f6223_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 tht  = _mm512_load_ps(&ptht[0]);
                          register __m512 k0   = _mm512_load_ps(&pk0[0]);
                          register __m512 b    = _mm512_load_ps(&pb[0]);
                          register __m512 a    = _mm512_load_ps(&pa[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          const __m512 hlf= _mm512_set1_ps(0.5f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 n4 = _mm512_set1_ps(-4.0f);
                          const __m512 _3 = _mm512_set1_ps(3.0f);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 n2 = _mm512_set1_ps(-2.0f);
                          const __m512 _6 = _mm512_set1_ps(6.0f);
                          const __m512 _8 = _mm512_set1_ps(8.0f);
                          const __m512 _13= _mm512_set1_ps(13.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 k0b,salp,arg,_2k0,b2,sarg,carg,ctht,a2,salp1,tht3;
                          register __m512 trm1,trm2,trm3;
                          register __m512 rcs,A1,A2,A3;
                          __m512 alp2,tht2,alp4,tht4,k0b2,k0b3,k0b4,a2,k0bt,k0a;
                          __m512 t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
                          __m512 t10,t11,t12,t13,t14,t15,t16,t17,t18,t19;
                          __m512 x0,x1,x2,x3,x4;
                          k0b  = _mm512_mul_ps(k0,b);
                          tht2 = _mm512_mul_ps(tht,tht);
                          _2k0 = _mm512_add_ps(k0,k0);
                          salp = xsinf(alp);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          ctht = xcosf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          salp1= _mm512_sub_ps(_1,salp);
                          k0a  = _mm512_mul_ps(k0,a);
                          alp2 = _mm512_mul_ps(alp,alp);
                          tht3 = _mm512_mul_ps(tht2,tht);
                          arg  = _mm512_mul_ps(_2k0,_mm512_mul_ps(calp,salp1));
                          tht4 = _mm512_mul_ps(tht2,tht2);
                          alp4 = _mm512_mul_ps(alp2,alp2);
                          k0b3 = _mm512_mul_ps(k0b2,k0b);
                          k0b4 = _mm512_mul_ps(k0b2,k0b2);
                          trm1 = _mm512_div_ps(_mm512_add_ps(_1,tht2),
                                               _mm512_mul_ps(_4,k0b2));
                          a2   = _mm512_mul_ps(a,a);
                          k0bt = _mm512_mul_ps(k0b,tht);
                          t0   = _mm512_add_ps(alp2,alp2); //2alp^2
                          t1   = _mm512_add_ps(tht2,tht2); //2tht^2
                          t2   = _mm512_mul_ps(alp2,tht2);//alp2*tht2
                          t3   = _mm512_mul_ps(tht4,hlf); //tht4*0.5
                          t4   = _mm512_mul_ps(_mm512_mul_ps(_2,alp4),tht2);//2*alp4*tht2
                          t5   = _mm512_mul_ps(_4,k0b2);//4*k0b2
                          t6   = _mm512_mul_ps(_mm512_mul_ps(_2,k0b2),tht2);//2*k0b2*tht2
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht2);//8*k0b3*tht2
                          t8   = _mm512_mul_ps(k0b2,tht4);//k0b2*tht4
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),
                                               _mm512_mul_ps(a2,tht2));//6*k0b2*a2*tht2
                          t10  = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht4);//8*k0b3*tht4
                          t11  = _mm512_mul_ps(_mm512_mul_ps(_13,k0b4),tht4);//13*k0b4*tht4
                          sarg = xsinf(arg);
                          x0   = _mm512_sub_ps(_mm512_add_ps(_2,t0),
                                               _mm512_add_ps(t1,alp4));
                          x1   = _mm512_add_ps(_mm512_add_ps(t2,t3),
                                               _mm512_add_ps(t4,t5));
                          x2   = _mm512_add_ps(_mm512_sub_ps(t6,t7),
                                               _mm512_add_ps(t8,t9));
                          x3   = _mm512_add_ps(t10,t11);
                          x4   = _mm512_sub_ps(x0,x1);
                          carg = xcosf(arg);
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),tht2);
                          A1   = _mm512_sub_ps(_mm512_sub_ps(x0,x1),
                                               _mm512_add_ps(x2,x3));
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b4),tht3);
                          x0   = _mm512_sub_ps(_mm512_sub_ps(n2,t0),
                                               _mm512_add_ps(t1,t2));
                          t8   = _mm512_mul_ps(_mm512_mul_ps(_3,k0b2),tht4);
                          x1   = _mm512_add_ps(_mm512_sub_ps(t3,t9),
                                               _mm512_add_ps(t7,t8));
                          A2   = _mm512_sub_ps(x0,x1);
                          t11  = _mm512_mul_ps(k0bt,k0bt);
                          t10  = _mm512_mul_ps(t11,k0bt);
                          t9   = _mm512_mul_ps(k0b,tht2);
                          t8   = _mm512_mul_ps(_3,_mm512_mul_ps(k0a,k0a));
                          x0   = _mm512_sub_ps(_mm512_add_ps(_1,alp2),
                                               _mm512_add_ps(t2,t8));
                          x1   = _mm512_sub_ps(k0b,_mm512_sub_ps(t9,t11));
                          A3   = _mm512_mul_ps(_mm512_mul_ps(n4,x0),
                                               _mm512_sub_ps(x1,_mm512_mul_ps(_4,t10)));
                          trm2 = _mm512_fmadd_ps(carg,A2,A1);
                          trm3 = _mm512_fmadd_ps(sarg,A3,trm2);
                          rcs  = _mm512_mul_ps(trm1,trm3);
                          return (rcs);
                 }


                   
                   __m512 rcs_f6223_zmm16r4_u(const float * __restrict  ptht,
                                            const float * __restrict  pk0,
                                            const float * __restrict  pb,
                                            const float * __restrict  pa,
                                            const float * __restrict  palp) {

                          register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                          register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                          register __m512 b    = _mm512_loadu_ps(&pb[0]);
                          register __m512 a    = _mm512_loadu_ps(&pa[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          const __m512 hlf= _mm512_set1_ps(0.5f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          const __m512 n4 = _mm512_set1_ps(-4.0f);
                          const __m512 _3 = _mm512_set1_ps(3.0f);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 n2 = _mm512_set1_ps(-2.0f);
                          const __m512 _6 = _mm512_set1_ps(6.0f);
                          const __m512 _8 = _mm512_set1_ps(8.0f);
                          const __m512 _13= _mm512_set1_ps(13.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 k0b,salp,arg,_2k0,b2,sarg,carg,ctht,a2,salp1,tht3;
                          register __m512 trm1,trm2,trm3;
                          register __m512 rcs,A1,A2,A3;
                          __m512 alp2,tht2,alp4,tht4,k0b2,k0b3,k0b4,a2,k0bt,k0a;
                          __m512 t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
                          __m512 t10,t11,t12,t13,t14,t15,t16,t17,t18,t19;
                          __m512 x0,x1,x2,x3,x4;
                          k0b  = _mm512_mul_ps(k0,b);
                          tht2 = _mm512_mul_ps(tht,tht);
                          _2k0 = _mm512_add_ps(k0,k0);
                          salp = xsinf(alp);
                          k0b2 = _mm512_mul_ps(k0b,k0b);
                          ctht = xcosf(tht);
                          a2   = _mm512_mul_ps(a,a);
                          salp1= _mm512_sub_ps(_1,salp);
                          k0a  = _mm512_mul_ps(k0,a);
                          alp2 = _mm512_mul_ps(alp,alp);
                          tht3 = _mm512_mul_ps(tht2,tht);
                          arg  = _mm512_mul_ps(_2k0,_mm512_mul_ps(calp,salp1));
                          tht4 = _mm512_mul_ps(tht2,tht2);
                          alp4 = _mm512_mul_ps(alp2,alp2);
                          k0b3 = _mm512_mul_ps(k0b2,k0b);
                          k0b4 = _mm512_mul_ps(k0b2,k0b2);
                          trm1 = _mm512_div_ps(_mm512_add_ps(_1,tht2),
                                               _mm512_mul_ps(_4,k0b2));
                          a2   = _mm512_mul_ps(a,a);
                          k0bt = _mm512_mul_ps(k0b,tht);
                          t0   = _mm512_add_ps(alp2,alp2); //2alp^2
                          t1   = _mm512_add_ps(tht2,tht2); //2tht^2
                          t2   = _mm512_mul_ps(alp2,tht2);//alp2*tht2
                          t3   = _mm512_mul_ps(tht4,hlf); //tht4*0.5
                          t4   = _mm512_mul_ps(_mm512_mul_ps(_2,alp4),tht2);//2*alp4*tht2
                          t5   = _mm512_mul_ps(_4,k0b2);//4*k0b2
                          t6   = _mm512_mul_ps(_mm512_mul_ps(_2,k0b2),tht2);//2*k0b2*tht2
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht2);//8*k0b3*tht2
                          t8   = _mm512_mul_ps(k0b2,tht4);//k0b2*tht4
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),
                                               _mm512_mul_ps(a2,tht2));//6*k0b2*a2*tht2
                          t10  = _mm512_mul_ps(_mm512_mul_ps(_8,k0b3),tht4);//8*k0b3*tht4
                          t11  = _mm512_mul_ps(_mm512_mul_ps(_13,k0b4),tht4);//13*k0b4*tht4
                          sarg = xsinf(arg);
                          x0   = _mm512_sub_ps(_mm512_add_ps(_2,t0),
                                               _mm512_add_ps(t1,alp4));
                          x1   = _mm512_add_ps(_mm512_add_ps(t2,t3),
                                               _mm512_add_ps(t4,t5));
                          x2   = _mm512_add_ps(_mm512_sub_ps(t6,t7),
                                               _mm512_add_ps(t8,t9));
                          x3   = _mm512_add_ps(t10,t11);
                          x4   = _mm512_sub_ps(x0,x1);
                          carg = xcosf(arg);
                          t9   = _mm512_mul_ps(_mm512_mul_ps(_6,k0b2),tht2);
                          A1   = _mm512_sub_ps(_mm512_sub_ps(x0,x1),
                                               _mm512_add_ps(x2,x3));
                          t7   = _mm512_mul_ps(_mm512_mul_ps(_8,k0b4),tht3);
                          x0   = _mm512_sub_ps(_mm512_sub_ps(n2,t0),
                                               _mm512_add_ps(t1,t2));
                          t8   = _mm512_mul_ps(_mm512_mul_ps(_3,k0b2),tht4);
                          x1   = _mm512_add_ps(_mm512_sub_ps(t3,t9),
                                               _mm512_add_ps(t7,t8));
                          A2   = _mm512_sub_ps(x0,x1);
                          t11  = _mm512_mul_ps(k0bt,k0bt);
                          t10  = _mm512_mul_ps(t11,k0bt);
                          t9   = _mm512_mul_ps(k0b,tht2);
                          t8   = _mm512_mul_ps(_3,_mm512_mul_ps(k0a,k0a));
                          x0   = _mm512_sub_ps(_mm512_add_ps(_1,alp2),
                                               _mm512_add_ps(t2,t8));
                          x1   = _mm512_sub_ps(k0b,_mm512_sub_ps(t9,t11));
                          A3   = _mm512_mul_ps(_mm512_mul_ps(n4,x0),
                                               _mm512_sub_ps(x1,_mm512_mul_ps(_4,t10)));
                          trm2 = _mm512_fmadd_ps(carg,A2,A1);
                          trm3 = _mm512_fmadd_ps(sarg,A3,trm2);
                          rcs  = _mm512_mul_ps(trm1,trm3);
                          return (rcs);
                 }


                  /*
                         Finite cones, approximated solutions.
                         Rayleigh region.
                         RCS.
                         Formula 6.3-4
                     */

#include "GMS_simd_utils.h"   

                  
              
                   __m512 rcs_f634_zmm16r4(const __m512 k0,
                                           const __m512 a,
                                           const __m512 h) {

                         
                          const __m512 c0 = _mm512_set1_ps(1.396263401595463661538952614791f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 k04,a4,h2,_4a,arg,earg,pih,x0,x1,nh;
                          register __m512 rcs,trm1,trm2;
                          h2  = _mm512_mul_ps(h,h);
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(a,a);
                          _4a = _mm512_mul_ps(_4,a);
                          pih = _mm512_mul_ps(_mm512_set1_ps(3.14159265358979323846264338328f),h);
                          nh  = negate_zmm16r4(h);
                          k04 = _mm512_mul_ps(x0,x0);
                          arg = _mm512_div_ps(nh,_4a);
                          a4  = _mm512_mul_ps(x1,x1);
                          earg= xexpf(arg);
                          trm1= _mm512_mul_ps(_mm512_mul_ps(k04,a4),h2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(_4,earg),pih);
                          trm1= _mm512_mul_ps(c0,trm1);
                          x1  = _mm512_add_ps(_1,x0);
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                  
                   __m512 rcs_f634_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) ph) {

                        
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 h   = _mm512_load_ps(&ph[0]);
                          const __m512 c0 = _mm512_set1_ps(1.396263401595463661538952614791f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 k04,a4,h2,_4a,arg,earg,pih,x0,x1,nh;
                          register __m512 rcs,trm1,trm2;
                          h2  = _mm512_mul_ps(h,h);
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(a,a);
                          _4a = _mm512_mul_ps(_4,a);
                          pih = _mm512_mul_ps(_mm512_set1_ps(3.14159265358979323846264338328f),h);
                          nh  = negate_zmm16r4(h);
                          k04 = _mm512_mul_ps(x0,x0);
                          arg = _mm512_div_ps(nh,_4a);
                          a4  = _mm512_mul_ps(x1,x1);
                          earg= xexpf(arg);
                          trm1= _mm512_mul_ps(_mm512_mul_ps(k04,a4),h2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(_4,earg),pih);
                          trm1= _mm512_mul_ps(c0,trm1);
                          x1  = _mm512_add_ps(_1,x0);
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                 
                   __m512 rcs_f634_zmm16r4_u(const float * __restrict pk0,
                                             const float * __restrict  pa,
                                             const float * __restrict ph) {

                          
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 h   = _mm512_loadu_ps(&ph[0]);
                          const __m512 c0 = _mm512_set1_ps(1.396263401595463661538952614791f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 _4 = _mm512_set1_ps(4.0f);
                          register __m512 k04,a4,h2,_4a,arg,earg,pih,x0,x1,nh;
                          register __m512 rcs,trm1,trm2;
                          h2  = _mm512_mul_ps(h,h);
                          x0  = _mm512_mul_ps(k0,k0);
                          x1  = _mm512_mul_ps(a,a);
                          _4a = _mm512_mul_ps(_4,a);
                          pih = _mm512_mul_ps(_mm512_set1_ps(3.14159265358979323846264338328f),h);
                          nh  = negate_zmm16r4(h);
                          k04 = _mm512_mul_ps(x0,x0);
                          arg = _mm512_div_ps(nh,_4a);
                          a4  = _mm512_mul_ps(x1,x1);
                          earg= xexpf(arg);
                          trm1= _mm512_mul_ps(_mm512_mul_ps(k04,a4),h2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(_4,earg),pih);
                          trm1= _mm512_mul_ps(c0,trm1);
                          x1  = _mm512_add_ps(_1,x0);
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                   /*
                          Rayleigh RCS of cone-hemispheroid.
                          Formula 6.3-5
                     */


                 
                   __m512 rcs_f635_zmm16r4(const __m512 k0,
                                           const __m512 a,
                                           const __m512 b,
                                           const __m512 h) {

                        
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,h2b,nh2b,pia2,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2b = _mm512_fmadd_ps(b,_2,h);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2b= negate_zmm16r4(h2b);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          arg = _mm512_div_ps(nh2b,_4a);
                          x1  = _mm512_mul_ps(c1,_mm512_mul_ps(pia2,b));
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2b),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                 
                   __m512 rcs_f635_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pb,
                                             const float * __restrict __ATTR_ALIGN__(64) ph) {
                                             
                        
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 h   = _mm512_load_ps(&ph[0]);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,h2b,nh2b,pia2,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2b = _mm512_fmadd_ps(b,_2,h);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2b= negate_zmm16r4(h2b);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          arg = _mm512_div_ps(nh2b,_4a);
                          x1  = _mm512_mul_ps(c1,_mm512_mul_ps(pia2,b));
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2b),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                 
                   __m512 rcs_f635_zmm16r4_u(const float * __restrict  pk0,
                                             const float * __restrict  pa,
                                             const float * __restrict  pb,
                                             const float * __restrict  ph) {
                                             
                         
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 h   = _mm512_loadu_ps(&ph[0]);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,h2b,nh2b,pia2,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2b = _mm512_fmadd_ps(b,_2,h);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2b= negate_zmm16r4(h2b);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          arg = _mm512_div_ps(nh2b,_4a);
                          x1  = _mm512_mul_ps(c1,_mm512_mul_ps(pia2,b));
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2b),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                  /*
                          Rayleigh RCS of cone-hemispheroid (b == a)
                          Formula 6.3-6
                      */

                 
                   __m512 rcs_f636_zmm16r4(const __m512 k0,
                                           const __m512 a,
                                           const __m512 h) {

                        
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,a3,h2a,nh2a,pia2,pia3,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2a = _mm512_fmadd_ps(a,_2,h);
                          a3  = _mm512_mul_ps(a2,a);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2a= negate_zmm16r4(h2a);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          pia3= _mm512_mul_ps(pi,a3);
                          arg = _mm512_div_ps(nh2a,_4a);
                          x1  = _mm512_mul_ps(c1,pia3);
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2a),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                
                   __m512 rcs_f636_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) ph) {

                        
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 h   = _mm512_load_ps(&ph[0]);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,a3,h2a,nh2a,pia2,pia3,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2a = _mm512_fmadd_ps(a,_2,h);
                          a3  = _mm512_mul_ps(a2,a);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2a= negate_zmm16r4(h2a);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          pia3= _mm512_mul_ps(pi,a3);
                          arg = _mm512_div_ps(nh2a,_4a);
                          x1  = _mm512_mul_ps(c1,pia3);
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2a),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                
                   __m512 rcs_f636_zmm16r4_u(const float * __restrict  pk0,
                                             const float * __restrict  pa,
                                             const float * __restrict  ph) {

                        
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 h   = _mm512_loadu_ps(&ph[0]);
                          const __m512 _4pi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0   = _mm512_set1_ps(0.33333333333333333333333333333f);
                          const __m512 c1   = _mm512_set1_ps(0.666666666666666666666666666667f);
                          const __m512 _4   = _mm512_set1_ps(4.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          register __m512 k04,a2,_4a,a3,h2a,nh2a,pia2,pia3,arg,earg,x0,x1,x2;
                          register __m512 rcs,trm1,trm2,trm3;
                          x0  = _mm512_mul_ps(k0,k0);
                          a2  = _mm512_mul_ps(a,a);
                          h2a = _mm512_fmadd_ps(a,_2,h);
                          a3  = _mm512_mul_ps(a2,a);
                          k04 = _mm512_mul_ps(x0,x0);
                          _4a = _mm512_mul_ps(_4,a);
                          trm1= _mm512_mul_ps(_4pi,k04);
                          pia2= _mm512_mul_ps(pi,a2);
                          nh2a= negate_zmm16r4(h2a);
                          x0  = _mm512_mul_ps(c0,_mm512_mul_ps(pia2,h));
                          pia3= _mm512_mul_ps(pi,a3);
                          arg = _mm512_div_ps(nh2a,_4a);
                          x1  = _mm512_mul_ps(c1,pia3);
                          earg= xexpf(arg);
                          x2  = _mm512_add_ps(x0,x1);
                          trm2= _mm512_mul_ps(x2,x2);
                          x0  = _mm512_div_ps(_mm512_mul_ps(pi,h2a),_4a);
                          x1  = _mm512_add_ps(_1, _mm512_div_ps(earg,x0));
                          trm2= _mm512_mul_ps(x1,x1);
                          rcs = _mm512_mul_ps(trm1,_mm512_mul_ps(trm2,trm3));
                          return (rcs);
                }


                   /*
                         Flat-back cone, backscatter RCS.
                         Formula 6.3-9
                   */


                 
                   __m512 rcs_f639_zmm16r4(const __m512 gam0,
                                           const __m512 alp,
                                           const __m512 k0,
                                           const __m512 h) {

                         
                          const __m512 c0 = _mm512_set1_ps(-0.25f);
                          const __m512 _0 = _mm512_set1_ps(-0.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 n1 = _mm512_set1_ps(-1.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 gam2,talp,k0h,x0,ear,eai,cer,cei;
                          register __m512 t0r,t0i,trm2r,trm2i,trm1r,trm1i,t1r,t1i;
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          talp  = xtanf(alp);
                          k0h   = _mm512_mul_ps(k0,h);
                          x0    = _mm512_mul_ps(talp,talp);
                          ear   = _mm512_setzero_ps();
                          t0r   = n1
                          eai   = _mm512_add_ps(k0h,k0h);
                          t0i   = _mm512_sub_ps(eai,_1);
                          cexp_zmm16r4(eai,ear,&cer,&cei);
                          trm1r = ear;
                          trm1i = negate_zmm16r4(x0);
                          cmul_zmm16r4(t0r,t0i,cer,cei,&trm2r,&trm2i);
                          trm2r = _mm512_add_ps(_1,trm2r);
                          trm2i = _mm512_add_ps(_1,trm2i);
                          cmul_zmm16r4(trm1r,trm1i,trm2r,&t0r,&t0i);
                          cabs = cabs_zmm16r4(t0r,t0i);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                 }


                   
                   __m512 rcs_f639_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0, 
                                             const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) palp,
                                             const float * __restrict __ATTR_ALIGN__(64) ph) {

                         
                          register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          register __m512 h   = _mm512_load_ps(&ph[0]);
                          const __m512 c0 = _mm512_set1_ps(-0.25f);
                          const __m512 _0 = _mm512_set1_ps(-0.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 n1 = _mm512_set1_ps(-1.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 gam2,talp,k0h,x0,ear,eai,cer,cei;
                          register __m512 t0r,t0i,trm2r,trm2i,trm1r,trm1i,t1r,t1i;
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          talp  = xtanf(alp);
                          k0h   = _mm512_mul_ps(k0,h);
                          x0    = _mm512_mul_ps(talp,talp);
                          ear   = _mm512_setzero_ps();
                          t0r   = n1
                          eai   = _mm512_add_ps(k0h,k0h);
                          t0i   = _mm512_sub_ps(eai,_1);
                          cexp_zmm16r4(eai,ear,&cer,&cei);
                          trm1r = ear;
                          trm1i = negate_zmm16r4(x0);
                          cmul_zmm16r4(t0r,t0i,cer,cei,&trm2r,&trm2i);
                          trm2r = _mm512_add_ps(_1,trm2r);
                          trm2i = _mm512_add_ps(_1,trm2i);
                          cmul_zmm16r4(trm1r,trm1i,trm2r,&t0r,&t0i);
                          cabs = cabs_zmm16r4(t0r,t0i);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                 }


                
                   __m512 rcs_f639_zmm16r4_u(const float * __restrict  pgam0, 
                                             const float * __restrict  pk0,
                                             const float * __restrict  palp,
                                             const float * __restrict  ph) {

                         
                          register __m512 gam0= _mm512_loadu_ps(&pgam0[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          register __m512 h   = _mm512_loadu_ps(&ph[0]);
                          const __m512 c0 = _mm512_set1_ps(-0.25f);
                          const __m512 _0 = _mm512_set1_ps(-0.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          const __m512 n1 = _mm512_set1_ps(-1.0f);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 gam2,talp,k0h,x0,ear,eai,cer,cei;
                          register __m512 t0r,t0i,trm2r,trm2i,trm1r,trm1i,t1r,t1i;
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          talp  = xtanf(alp);
                          k0h   = _mm512_mul_ps(k0,h);
                          x0    = _mm512_mul_ps(talp,talp);
                          ear   = _mm512_setzero_ps();
                          t0r   = n1
                          eai   = _mm512_add_ps(k0h,k0h);
                          t0i   = _mm512_sub_ps(eai,_1);
                          cexp_zmm16r4(eai,ear,&cer,&cei);
                          trm1r = ear;
                          trm1i = negate_zmm16r4(x0);
                          cmul_zmm16r4(t0r,t0i,cer,cei,&trm2r,&trm2i);
                          trm2r = _mm512_add_ps(_1,trm2r);
                          trm2i = _mm512_add_ps(_1,trm2i);
                          cmul_zmm16r4(trm1r,trm1i,trm2r,&t0r,&t0i);
                          cabs = cabs_zmm16r4(t0r,t0i);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                 }


                   /*
                        Cone tip scattering RCS.
                        Formula 6.3-10
                    */


                
                   __m512 rcs_f6310_zmm16r4(const __m512 gam0,
                                            const __m512 alp) {

                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 gam2,tana,x0,tan4,trm1;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          tan4 = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,tan4);
                          return (rcs);
                 }


                
                   __m512 rcs_f6310_zmm16r4_a(const float * __restrict  __ATTR_ALIGN__(64) pgam0, 
                                              const float * __restrict  __ATTR_ALIGN__(64) palp) {

                          register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 gam2,tana,x0,tan4,trm1;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          tan4 = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,tan4);
                          return (rcs);
                 }


                
                   __m512 rcs_f6310_zmm16r4_u(const float * __restrict  pgam0, 
                                              const float * __restrict  palp) {

                          register __m512 gam0= _mm512_loadu_ps(&pgam0[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          const __m512 _16pi = _mm512_set1_ps(50.265482457436691815402294132472f);
                          register __m512 gam2,tana,x0,tan4,trm1;
                          gam2 = _mm512_mul_ps(gam0,gam0);
                          tana = xtanf(alp);
                          trm1 = _mm512_div_ps(gam2,_16pi);
                          x0   = _mm512_mul_ps(tana,tana);
                          tan4 = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_mul_ps(trm1,tan4);
                          return (rcs);
                 }


                   /*
                         Case of flat-back cone joined by the sphere.
                         Axial-incidence backscatter RCS.
                         Formula 6.3-11
                    */

                   
                 
                   __m512 rcs_f6311_zmm16r4(const __m512 gam0,
                                            const __m512 alp,
                                            const __m512 k0,
                                            const __m512 h,
                                            const __m512 z1) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 c1 = _mm512_set1_ps(-0.25f);
                          register __m512 gam2,tana,tana2,cosa,seca,k0h,z1h,kz1h,i4r,ir4;
                          register __m512 ear1,eai1,cer1,cei1,ear2,eai2,cer2,cei2;
                          register __m512 t0r,t0i,t1r,t1i,x0,x1,cabs;
                          k0h  = _mm512_mul_ps(k0,h);
                          tana = xtanf(alp);
                          z1h  = _mm512_add_ps(z1,h);
                          tana2= _mm512_mul_ps(tana,tana);
                          kz1h = _mm512_mul_ps(k0,z1h);
                          gam2 = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          i4r  = _mm512_setzero_ps();
                          i4i  = c1;
                          cosa = xcosf(alp);
                          ear1 = i4r;
                          eai1 = _mm512_add_ps(k0h,k0h);
                          seca = _mm512_mul_ps(cosa,cosa);
                          t0r  = i4r;
                          x0   = _mm512_fmsub_ps(h,tana2,z1);
                          t0i  = _mm512_mul_ps(tana2,i4i);
                          cexp_zmm16r4(ear1,eai1,&cer1,&cei1);
                          x1   = _mm512_sub_ps(x0,seca);
                          t1r  = i4r;
                          ear2 = i4r;
                          t1i  = _mm512_sub_ps(t0i,_mm512_mul_ps(c0,x1));
                          eai2 = _mm512_add_ps(kz1h,kz1h);
                          cexp_zmm16r4(ear2,eai2,&cer2,&cei2);
                          cer2 = i4r;
                          cmul_zmm16r4(t1r,t1i,cer1,cei1,&t0r,&t0i);
                          cei2 = _mm512_mul_ps(cei2,c0);
                          x0   = _mm512_sub_ps(t0r,cer2);
                          x1   = _mm512_sub_ps(t0i,cei2);
                          cabs = cabs_zmm16r4(x0,x1);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                  }


                
                   __m512 rcs_f6311_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0, 
                                             const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) palp,
                                             const float * __restrict __ATTR_ALIGN__(64) ph,
                                             const float * __restrict __ATTR_ALIGN__(64) pz1) {

                          register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          register __m512 h   = _mm512_load_ps(&ph[0]);
                          register __m512 z1  = _mm512_load_ps(&pz1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 c1 = _mm512_set1_ps(-0.25f);
                          register __m512 gam2,tana,tana2,cosa,seca,k0h,z1h,kz1h,i4r,ir4;
                          register __m512 ear1,eai1,cer1,cei1,ear2,eai2,cer2,cei2;
                          register __m512 t0r,t0i,t1r,t1i,x0,x1,cabs;
                          k0h  = _mm512_mul_ps(k0,h);
                          tana = xtanf(alp);
                          z1h  = _mm512_add_ps(z1,h);
                          tana2= _mm512_mul_ps(tana,tana);
                          kz1h = _mm512_mul_ps(k0,z1h);
                          gam2 = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          i4r  = _mm512_setzero_ps();
                          i4i  = c1;
                          cosa = xcosf(alp);
                          ear1 = i4r;
                          eai1 = _mm512_add_ps(k0h,k0h);
                          seca = _mm512_mul_ps(cosa,cosa);
                          t0r  = i4r;
                          x0   = _mm512_fmsub_ps(h,tana2,z1);
                          t0i  = _mm512_mul_ps(tana2,i4i);
                          cexp_zmm16r4(ear1,eai1,&cer1,&cei1);
                          x1   = _mm512_sub_ps(x0,seca);
                          t1r  = i4r;
                          ear2 = i4r;
                          t1i  = _mm512_sub_ps(t0i,_mm512_mul_ps(c0,x1));
                          eai2 = _mm512_add_ps(kz1h,kz1h);
                          cexp_zmm16r4(ear2,eai2,&cer2,&cei2);
                          cer2 = i4r;
                          cmul_zmm16r4(t1r,t1i,cer1,cei1,&t0r,&t0i);
                          cei2 = _mm512_mul_ps(cei2,c0);
                          x0   = _mm512_sub_ps(t0r,cer2);
                          x1   = _mm512_sub_ps(t0i,cei2);
                          cabs = cabs_zmm16r4(x0,x1);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                  }


                 
                   __m512 rcs_f6311_zmm16r4_u(const float * __restrict  pgam0, 
                                             const float * __restrict  pk0,
                                             const float * __restrict  palp,
                                             const float * __restrict  ph,
                                             const float * __restrict  pz1) {

                          register __m512 gam0= _mm512_loadu_ps(&pgam0[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          register __m512 h   = _mm512_loadu_ps(&ph[0]);
                          register __m512 z1  = _mm512_loadu_ps(&pz1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 c1 = _mm512_set1_ps(-0.25f);
                          register __m512 gam2,tana,tana2,cosa,seca,k0h,z1h,kz1h,i4r,ir4;
                          register __m512 ear1,eai1,cer1,cei1,ear2,eai2,cer2,cei2;
                          register __m512 t0r,t0i,t1r,t1i,x0,x1,cabs;
                          k0h  = _mm512_mul_ps(k0,h);
                          tana = xtanf(alp);
                          z1h  = _mm512_add_ps(z1,h);
                          tana2= _mm512_mul_ps(tana,tana);
                          kz1h = _mm512_mul_ps(k0,z1h);
                          gam2 = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          i4r  = _mm512_setzero_ps();
                          i4i  = c1;
                          cosa = xcosf(alp);
                          ear1 = i4r;
                          eai1 = _mm512_add_ps(k0h,k0h);
                          seca = _mm512_mul_ps(cosa,cosa);
                          t0r  = i4r;
                          x0   = _mm512_fmsub_ps(h,tana2,z1);
                          t0i  = _mm512_mul_ps(tana2,i4i);
                          cexp_zmm16r4(ear1,eai1,&cer1,&cei1);
                          x1   = _mm512_sub_ps(x0,seca);
                          t1r  = i4r;
                          ear2 = i4r;
                          t1i  = _mm512_sub_ps(t0i,_mm512_mul_ps(c0,x1));
                          eai2 = _mm512_add_ps(kz1h,kz1h);
                          cexp_zmm16r4(ear2,eai2,&cer2,&cei2);
                          cer2 = i4r;
                          cmul_zmm16r4(t1r,t1i,cer1,cei1,&t0r,&t0i);
                          cei2 = _mm512_mul_ps(cei2,c0);
                          x0   = _mm512_sub_ps(t0r,cer2);
                          x1   = _mm512_sub_ps(t0i,cei2);
                          cabs = cabs_zmm16r4(x0,x1);
                          rcs  = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                  }


                    /*
                          Flat-back cone backscattering RCS.
                          Formula 6.3-14
                     */

                  
                   __m512 rcs_f6314_zmm16r4(const __m512 a,
                                            const __m512 alp) {

                          const __m512 pi3   = _mm512_set1_ps(31.006276680299820175476315067101f);
                          const __m512 _4pi2 = _mm512_set1_ps(39.478417604357434475337963999505f);
                          const __m512 _3pi  = _mm512_set1_ps(9.424777960769379715387930149839f);
                          const __m512 _3pi2 = _mm512_set1_ps(4.712388980384689857693965074919f)
                          register __m512 rcs,a2,num1,den1,arg,sarg,csc,x0,alp2;
                          a2   = _mm512_mul_ps(a,a);
                          alp2 = _mm512_add_ps(alp,alp);
                          num1 = _mm512_mul_ps(pi3,a2);
                          arg  = _mm512_div_ps(_4pi2,_mm512_add_ps(_3pi,alp2));
                          x0   = _mm512_add_ps(alp,_3pi2);
                          sarg = xsinf(arg);
                          den1 = _mm512_mul_ps(x0,x0);
                          csc  = _mm512_rcp14_ps(sarg);
                          x0   = _mm512_mul_ps(csc,csc);
                          arg  = _mm512_div_ps(num1,den1);
                          rcs  = _mm512_mul_ps(arg,x0);
                          return (rcs);
                }


                
                   __m512 rcs_f6314_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          const __m512 pi3   = _mm512_set1_ps(31.006276680299820175476315067101f);
                          const __m512 _4pi2 = _mm512_set1_ps(39.478417604357434475337963999505f);
                          const __m512 _3pi  = _mm512_set1_ps(9.424777960769379715387930149839f);
                          const __m512 _3pi2 = _mm512_set1_ps(4.712388980384689857693965074919f)
                          register __m512 rcs,a2,num1,den1,arg,sarg,csc,x0,alp2;
                          a2   = _mm512_mul_ps(a,a);
                          alp2 = _mm512_add_ps(alp,alp);
                          num1 = _mm512_mul_ps(pi3,a2);
                          arg  = _mm512_div_ps(_4pi2,_mm512_add_ps(_3pi,alp2));
                          x0   = _mm512_add_ps(alp,_3pi2);
                          sarg = xsinf(arg);
                          den1 = _mm512_mul_ps(x0,x0);
                          csc  = _mm512_rcp14_ps(sarg);
                          x0   = _mm512_mul_ps(csc,csc);
                          arg  = _mm512_div_ps(num1,den1);
                          rcs  = _mm512_mul_ps(arg,x0);
                          return (rcs);
                }


                 
                   __m512 rcs_f6314_zmm16r4_u( const float * __restrict  pa,
                                             const float * __restrict  palp) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          const __m512 pi3   = _mm512_set1_ps(31.006276680299820175476315067101f);
                          const __m512 _4pi2 = _mm512_set1_ps(39.478417604357434475337963999505f);
                          const __m512 _3pi  = _mm512_set1_ps(9.424777960769379715387930149839f);
                          const __m512 _3pi2 = _mm512_set1_ps(4.712388980384689857693965074919f)
                          register __m512 rcs,a2,num1,den1,arg,sarg,csc,x0,alp2;
                          a2   = _mm512_mul_ps(a,a);
                          alp2 = _mm512_add_ps(alp,alp);
                          num1 = _mm512_mul_ps(pi3,a2);
                          arg  = _mm512_div_ps(_4pi2,_mm512_add_ps(_3pi,alp2));
                          x0   = _mm512_add_ps(alp,_3pi2);
                          sarg = xsinf(arg);
                          den1 = _mm512_mul_ps(x0,x0);
                          csc  = _mm512_rcp14_ps(sarg);
                          x0   = _mm512_mul_ps(csc,csc);
                          arg  = _mm512_div_ps(num1,den1);
                          rcs  = _mm512_mul_ps(arg,x0);
                          return (rcs);
                }


                   /*
                          Scattering from a thick cylinder of length
                          being a slant height of the cone of radius
                          (4/9*a*sec(alpha)), i.e. RCS(PI/2-alpha).
                          Formula 6.3-18
                      */


                
                   __m512 rcs_f6318_zmm16r4(const __m512 gam0,
                                            const __m512 k0h,
                                            const __m512 alp) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.33333333333333333333333333333f);
                          register __m512 rcs,gam2,k0h3,x0,salp,calp,seca,sqr,x1,sabs;
                          x0   = _mm512_mul_ps(gam0,gam0);
                          k0h3 = _mm512_mul_ps(k0h,c0);
                          gam2 = _mm512_div_ps(x0,pi);
                          salp = xsinf(alp);
                          calp = xcosf(alp);
                          x1   = _mm512_mul_ps(k0h,salp);
                          x0   = _mm512_div_ps(x1,pi);
                          seca = _mm512_rcp14_ps(calp);
                          sqr  = _mm512_sqrt_ps(x0);
                          x1   = _mm512_mul_ps(seca,seca);
                          x0   = _mm512_mul_ps(k0h3,_mm512_mul_ps(sqr,x1));
                          sabs = _mm512_abs_ps(x0);
                          x1   = _mm512_mul_ps(sabs,sabs);
                          rcs  = _mm512_mul_ps(gam2,x1);
                          return (rcs);
                 }


                 
                   __m512 rcs_f6318_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0, 
                                             const float * __restrict __ATTR_ALIGN__(64) pk0h,
                                             const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 k0h  = _mm512_load_ps(&pk0[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.33333333333333333333333333333f);
                          register __m512 rcs,gam2,k0h3,x0,salp,calp,seca,sqr,x1,sabs;
                          x0   = _mm512_mul_ps(gam0,gam0);
                          k0h3 = _mm512_mul_ps(k0h,c0);
                          gam2 = _mm512_div_ps(x0,pi);
                          salp = xsinf(alp);
                          calp = xcosf(alp);
                          x1   = _mm512_mul_ps(k0h,salp);
                          x0   = _mm512_div_ps(x1,pi);
                          seca = _mm512_rcp14_ps(calp);
                          sqr  = _mm512_sqrt_ps(x0);
                          x1   = _mm512_mul_ps(seca,seca);
                          x0   = _mm512_mul_ps(k0h3,_mm512_mul_ps(sqr,x1));
                          sabs = _mm512_abs_ps(x0);
                          x1   = _mm512_mul_ps(sabs,sabs);
                          rcs  = _mm512_mul_ps(gam2,x1);
                          return (rcs);
                 }
                                            



                
                   __m512 rcs_f6318_zmm16r4_u(const float * __restrict  pgam0, 
                                             const float * __restrict  pk0h,
                                             const float * __restrict  palp) {

                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 k0h  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 c0 = _mm512_set1_ps(0.33333333333333333333333333333f);
                          register __m512 rcs,gam2,k0h3,x0,salp,calp,seca,sqr,x1,sabs;
                          x0   = _mm512_mul_ps(gam0,gam0);
                          k0h3 = _mm512_mul_ps(k0h,c0);
                          gam2 = _mm512_div_ps(x0,pi);
                          salp = xsinf(alp);
                          calp = xcosf(alp);
                          x1   = _mm512_mul_ps(k0h,salp);
                          x0   = _mm512_div_ps(x1,pi);
                          seca = _mm512_rcp14_ps(calp);
                          sqr  = _mm512_sqrt_ps(x0);
                          x1   = _mm512_mul_ps(seca,seca);
                          x0   = _mm512_mul_ps(k0h3,_mm512_mul_ps(sqr,x1));
                          sabs = _mm512_abs_ps(x0);
                          x1   = _mm512_mul_ps(sabs,sabs);
                          rcs  = _mm512_mul_ps(gam2,x1);
                          return (rcs);
                 }

#include "GMS_rcs_common_zmm16r4.h"
                 /*
                     Fresnel integral component.
                     Helper kernel for formula 6.3-15
                     Formula 6.3-16
                  */


                 
                   void Frho_f6316_zmm16r4(const __m512 xxa,
                                           const __m512 rho,
                                           __m512 * __restrict ssa,
                                           __m512 * __restrict cca) {

                        const __m512 n1 = _mm512_set1_ps(-1.0f);
                        register __m512 irho,rho2,ear,eai,cer,cei,resr,resi;
                        rho2 = _mm512_mul_ps(rho,rho);
                        ear  = _mm512_setzero_ps();
                        irho = _mm512_rcp14_ps(rho);
                        eai  = _mm512_mul_ps(n1,rho2);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        fresnel_zmm16r4(xxa,&resr,&resi);
                        cer = _mm512_mul_ps(cer,irho);
                        cei = _mm512_mul_ps(cei,irho);
                        cmul_zmm16r4(cer,cei,resr,resi,*ssa,*cca);
                }


              
                   void Frho_f6316_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pxxa,
                                             const float * __restrict __ATTR_ALIGN__(64) prho,
                                             float * __restrict __ATTR_ALIGN__(64) ssa,
                                             float * __restrict __ATTR_ALIGN__(64) cca) {

                        register __m512 xxa = _mm512_load_ps(&pxxa[0]);
                        register __m512 rho = _mm512_load_ps(&prho[0]);
                        const __m512 n1 = _mm512_set1_ps(-1.0f);
                        register __m512 irho,rho2,ear,eai,cer,cei,t0r,t0i,resr,resi;
                        rho2 = _mm512_mul_ps(rho,rho);
                        ear  = _mm512_setzero_ps();
                        irho = _mm512_rcp14_ps(rho);
                        eai  = _mm512_mul_ps(n1,rho2);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        fresnel_zmm16r4(xxa,&resr,&resi);
                        cer = _mm512_mul_ps(cer,irho);
                        cei = _mm512_mul_ps(cei,irho);
                        cmul_zmm16r4(cer,cei,resr,resi,&t0r,&t0i);
                        _mm512_store_ps(&ssa[0], t0i);
                        _mm512_store_ps(&cca[0], t0r);
                }


                
                   void Frho_f6316_zmm16r4_u(const float * __restrict  pxxa,
                                             const float * __restrict  prho,
                                             float * __restrict __ATTR_ALIGN__(64) ssa,
                                             float * __restrict __ATTR_ALIGN__(64) cca) {

                        register __m512 xxa = _mm512_loadu_ps(&pxxa[0]);
                        register __m512 rho = _mm512_loadu_ps(&prho[0]);
                        const __m512 n1 = _mm512_set1_ps(-1.0f);
                        register __m512 irho,rho2,ear,eai,cer,cei,t0r,t0i,resr,resi;
                        rho2 = _mm512_mul_ps(rho,rho);
                        ear  = _mm512_setzero_ps();
                        irho = _mm512_rcp14_ps(rho);
                        eai  = _mm512_mul_ps(n1,rho2);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        fresnel_zmm16r4(xxa,&resr,&resi);
                        cer = _mm512_mul_ps(cer,irho);
                        cei = _mm512_mul_ps(cei,irho);
                        cmul_zmm16r4(cer,cei,resr,resi,&t0r,&t0i);
                        _mm512_storeu_ps(&ssa[0], t0i);
                        _mm512_storeu_ps(&cca[0], t0r);
                }


                   /*
                          Incidence near broadside to the cone - backscatter RCS.
                          Formula 6.3-15
                      */


               
                   __m512 rcs_f6315_zmm16r4(const __m512 rho,
                                            const __m512 gam0,
                                            const __m512 k0h,
                                            const __m512 tht,
                                            const __m512 alp) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi4= _mm512_set1_ps(0.78539816339744830961566084582f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 ssa,cca,gam2,ear,eai,cer,cei,thalp,ir,ii,num,den,rat;
                          register __m512 rcs,tana,tanta,costa,xxa,_2k0h,cosa,x0,x1,sth,seca,trm1;
                          register __m512 t0r,t0i,t1r,t1i,cabs;
                          thalp = _mm512_add_ps(tht,alp);
                          cosa   = xcosf(alp);
                          ir    = _mm512_setzero_ps();
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          ii    = pi4;
                          seca  = _mm512_rcp14_ps(cosa);
                          tanta = xtanf(thalp);
                          _2k0h = _mm512_add_ps(k0h,k0h);
                          tana  = xtanf(alp);
                          costa = xcosf(thalp);
                          x0    = _mm512_mul_ps(_2k0h,_mm512_mul_ps(costa,seca));
                          sth   = xsinf(tht);
                          ear   = ir;
                          num   = _mm512_mul_ps(k0h,tana);
                          xxa   = _mm512_sqrt_ps(x0);
                          den   = _mm512_mul_ps(pi,sth);
                          Frho_f6316_zmm16r4(rho,xxa,&ssa,&cca);
                          eai   = _mm512_add_ps(ii,x0);
                          trm1  = _mm512_mul_ps(_mm512_sqrt_ps(den),tanta);
                          t0r   = _mm512_sub_ps(_1,ssa);
                          t0i   = _mm512_sub_ps(_1,cca);
                          cexp_zmm16r4(ear,eai,&cer,&cei);
                          cer   = _mm512_mul_ps(cer,c0);
                          cei   = _mm512_mul_ps(cei,c0);
                          x0    = _mm512_mul_ps(trm1,t0r);
                          x1    = _mm512_mul_ps(trm1,t0i);
                          cmul_zmm16r4(cer,cei,t0r,t0i,&t1r,&t1i);
                          cabs  = cabs_zmm16r4(t1r,t1i);
                          rcs   = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                   }


                  
                   __m512 rcs_f6315_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) prho,
                                              const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0h,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 rho  = _mm512_load_ps(&prho[0]);
                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 k0h  = _mm512_load_ps(&pk0h[0]);
                          register __m512 tht  = _mm512_load_ps(&ptht[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi4= _mm512_set1_ps(0.78539816339744830961566084582f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 ssa,cca,gam2,ear,eai,cer,cei,thalp,ir,ii,num,den,rat;
                          register __m512 rcs,tana,tanta,costa,xxa,_2k0h,cosa,x0,x1,sth,seca,trm1;
                          register __m512 t0r,t0i,t1r,t1i,cabs;
                          thalp = _mm512_add_ps(tht,alp);
                          cosa   = xcosf(alp);
                          ir    = _mm512_setzero_ps();
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          ii    = pi4;
                          seca  = _mm512_rcp14_ps(cosa);
                          tanta = xtanf(thalp);
                          _2k0h = _mm512_add_ps(k0h,k0h);
                          tana  = xtanf(alp);
                          costa = xcosf(thalp);
                          x0    = _mm512_mul_ps(_2k0h,_mm512_mul_ps(costa,seca));
                          sth   = xsinf(tht);
                          ear   = ir;
                          num   = _mm512_mul_ps(k0h,tana);
                          xxa   = _mm512_sqrt_ps(x0);
                          den   = _mm512_mul_ps(pi,sth);
                          Frho_f6316_zmm16r4(rho,xxa,&ssa,&cca);
                          eai   = _mm512_add_ps(ii,x0);
                          trm1  = _mm512_mul_ps(_mm512_sqrt_ps(den),tanta);
                          t0r   = _mm512_sub_ps(_1,ssa);
                          t0i   = _mm512_sub_ps(_1,cca);
                          cexp_zmm16r4(ear,eai,&cer,&cei);
                          cer   = _mm512_mul_ps(cer,c0);
                          cei   = _mm512_mul_ps(cei,c0);
                          x0    = _mm512_mul_ps(trm1,t0r);
                          x1    = _mm512_mul_ps(trm1,t0i);
                          cmul_zmm16r4(cer,cei,t0r,t0i,&t1r,&t1i);
                          cabs  = cabs_zmm16r4(t1r,t1i);
                          rcs   = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                   }


               
                   __m512 rcs_f6315_zmm16r4_u(const float * __restrict  prho,
                                              const float * __restrict  pgam0,
                                              const float * __restrict  pk0h,
                                              const float * __restrict  ptht,
                                              const float * __restrict  palp) {

                          register __m512 rho  = _mm512_loadu_ps(&prho[0]);
                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 k0h  = _mm512_loadu_ps(&pk0h[0]);
                          register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi4= _mm512_set1_ps(0.78539816339744830961566084582f);
                          const __m512 c0 = _mm512_set1_ps(0.25f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 ssa,cca,gam2,ear,eai,cer,cei,thalp,ir,ii,num,den,rat;
                          register __m512 rcs,tana,tanta,costa,xxa,_2k0h,cosa,x0,x1,sth,seca,trm1;
                          register __m512 t0r,t0i,t1r,t1i,cabs;
                          thalp = _mm512_add_ps(tht,alp);
                          cosa   = xcosf(alp);
                          ir    = _mm512_setzero_ps();
                          gam2  = _mm512_div_ps(_mm512_mul_ps(gam0,gam0),pi);
                          ii    = pi4;
                          seca  = _mm512_rcp14_ps(cosa);
                          tanta = xtanf(thalp);
                          _2k0h = _mm512_add_ps(k0h,k0h);
                          tana  = xtanf(alp);
                          costa = xcosf(thalp);
                          x0    = _mm512_mul_ps(_2k0h,_mm512_mul_ps(costa,seca));
                          sth   = xsinf(tht);
                          ear   = ir;
                          num   = _mm512_mul_ps(k0h,tana);
                          xxa   = _mm512_sqrt_ps(x0);
                          den   = _mm512_mul_ps(pi,sth);
                          Frho_f6316_zmm16r4(rho,xxa,&ssa,&cca);
                          eai   = _mm512_add_ps(ii,x0);
                          trm1  = _mm512_mul_ps(_mm512_sqrt_ps(den),tanta);
                          t0r   = _mm512_sub_ps(_1,ssa);
                          t0i   = _mm512_sub_ps(_1,cca);
                          cexp_zmm16r4(ear,eai,&cer,&cei);
                          cer   = _mm512_mul_ps(cer,c0);
                          cei   = _mm512_mul_ps(cei,c0);
                          x0    = _mm512_mul_ps(trm1,t0r);
                          x1    = _mm512_mul_ps(trm1,t0i);
                          cmul_zmm16r4(cer,cei,t0r,t0i,&t1r,&t1i);
                          cabs  = cabs_zmm16r4(t1r,t1i);
                          rcs   = _mm512_mul_ps(gam2,cabs);
                          return (rcs);
                   }


                      /*
                          Specular return (RCS) of equivalent cylinder
                          to cone sphere.
                          Formula 6.3-19
                      */


                   __m512 rcs_f6319_zmm16r4(const __m512 k0h,
                                            const __m512 alp,
                                            const __m512 a) {

                          const __m512 c0 = _mm512_set1_ps(0.333333333333333333333333333333333f);
                          register __m512 k0h2,a2o3,cosa,seca,trm1,trm2,rcs,x0; 
                          a2o3 = _mm512_mul_ps(_mm512_mul_ps(a,a),c0);
                          cosa = xcosf(alp);
                          k0h2 = _mm512_mul_ps(k0h,k0h);
                          seca = _mm512_rcp14_ps(cosa);
                          x0   = _mm512_mul_ps(a2o3,cosa);
                          trm1 = _mm512_mul_ps(k0h2,_mm512_mul_ps(seca,seca));
                          trm2 = _mm512_sqrt_ps(x0);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                  
                   __m512 rcs_f6319_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0h,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 k0h  = _mm512_load_ps(&pk0h[0]);
                          register __m512 a    = _mm512_load_ps(&pa[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          const __m512 c0 = _mm512_set1_ps(0.333333333333333333333333333333333f);
                          register __m512 k0h2,a2o3,cosa,seca,trm1,trm2,rcs,x0; 
                          a2o3 = _mm512_mul_ps(_mm512_mul_ps(a,a),c0);
                          cosa = xcosf(alp);
                          k0h2 = _mm512_mul_ps(k0h,k0h);
                          seca = _mm512_rcp14_ps(cosa);
                          x0   = _mm512_mul_ps(a2o3,cosa);
                          trm1 = _mm512_mul_ps(k0h2,_mm512_mul_ps(seca,seca));
                          trm2 = _mm512_sqrt_ps(x0);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                  
                   __m512 rcs_f6319_zmm16r4_u(const float * __restrict  pk0h,
                                              const float * __restrict  pa,
                                              const float * __restrict  palp) {

                          register __m512 k0h  = _mm512_loadu_ps(&pk0h[0]);
                          register __m512 a    = _mm512_loadu_ps(&pa[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          const __m512 c0 = _mm512_set1_ps(0.333333333333333333333333333333333f);
                          register __m512 k0h2,a2o3,cosa,seca,trm1,trm2,rcs,x0; 
                          a2o3 = _mm512_mul_ps(_mm512_mul_ps(a,a),c0);
                          cosa = xcosf(alp);
                          k0h2 = _mm512_mul_ps(k0h,k0h);
                          seca = _mm512_rcp14_ps(cosa);
                          x0   = _mm512_mul_ps(a2o3,cosa);
                          trm1 = _mm512_mul_ps(k0h2,_mm512_mul_ps(seca,seca));
                          trm2 = _mm512_sqrt_ps(x0);
                          rcs  = _mm512_mul_ps(trm1,trm2);
                          return (rcs);
                 }


                  /*
                          Width of specular lobe of cylinder formula 6.3-19
                          Formula 6.3-20 
                     */

                    
                 
                   __m512 dpsi_f6320_zmm16r4(const __m512 gam0,
                                             const __m512 h,
                                             const __m512 alp) {

                          register __m512 dpsi,cosa,seca;
                          cosa = xcosf(alp);
                          seca = _mm512_rcp14_ps(cosa);
                          dpsi = _mm512_div_ps(gam0,_mm512_mul_ps(h,seca));
                          return (dpsi);
                }


                 
                   __m512 dpsi_f6320_zmm16r4_a(const float * __ATTR_ALIGN__(64) pgam0,
                                               const float * __ATTR_ALIGN__(64) ph,
                                               const float * __ATTR_ALIGN__(64) palp) {

                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 h    = _mm512_load_ps(&ph[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          register __m512 dpsi,cosa,seca;
                          cosa = xcosf(alp);
                          seca = _mm512_rcp14_ps(cosa);
                          dpsi = _mm512_div_ps(gam0,_mm512_mul_ps(h,seca));
                          return (dpsi);
                }


                
                   __m512 dpsi_f6320_zmm16r4_u(const float *  pgam0,
                                               const float *  ph,
                                               const float *  palp) {

                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 h    = _mm512_loadu_ps(&ph[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          register __m512 dpsi,cosa,seca;
                          cosa = xcosf(alp);
                          seca = _mm512_rcp14_ps(cosa);
                          dpsi = _mm512_div_ps(gam0,_mm512_mul_ps(h,seca));
                          return (dpsi);
                }


                 


                  /*
                          Helper argument K1 for calculation
                          of 6.3-41.
                          Formula 6.3-42
                     */


               
                   __m512 K1_f6342_zmm16r4(const __m512 k0a,
                                           const __m512 tht,
                                           const __m512 alp) {
                          
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 K1,sth,cth,cota,trm1,trm2,calp,salp;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_mul_ps(k0a,trm2);
                          K1  = _mm512_mul_ps(_4opi,trm1);
                          return (K1);
                  }


                 
                   __m512 K1_f6342_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0a,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht,
                                             const float * __restrict __ATTR_ALIGN__(64) palp) {
                          
                          register __m512 k0a = _mm512_load_ps(&pk0a[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 K1,sth,cth,cota,trm1,trm2,calp,salp;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_mul_ps(k0a,trm2);
                          K1  = _mm512_mul_ps(_4opi,trm1);
                          return (K1);
                  }


                  
                   __m512 K1_f6342_zmm16r4_u(const float * __restrict  pk0a,
                                             const float * __restrict  ptht,
                                             const float * __restrict  palp) {
                          
                          register __m512 k0a = _mm512_loadu_ps(&pk0a[0]);
                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 K1,sth,cth,cota,trm1,trm2,calp,salp;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_mul_ps(k0a,trm2);
                          K1  = _mm512_mul_ps(_4opi,trm1);
                          return (K1);
                  }


                   /*
                          Helper argument K1 for calculation
                          of 6.3-41.
                          Formula 6.3-43
                     */


                 
                   __m512 K2_f6343_zmm16r4(const __m512 k0,
                                           const __m512 a,
                                           const __m512 Ls,
                                           const __m512 tht,
                                           const __m512 alp) {
                          
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 sth,cth,cota,trm1,trm2,calp,salp;
                          register __m512 tana,x0,K2;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          tana= xtanf(alp);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_sub_ps(a,_mm512_mul_ps(Ls,tana));
                          x0  = _mm512_mul_ps(k0,trm1);
                          K2  = _mm512_mul_ps(_4opi,_mm512_mul_ps(trm1,trm2));
                          return (K2);
                  }


                 
                   __m512 K2_f6343_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pLs,
                                             const float * __restrict __ATTR_ALIGN__(64) ptht,
                                             const float * __restrict __ATTR_ALIGN__(64) palp) {
                          
                          register __m512 k0a = _mm512_load_ps(&pk0a[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 Ls  = _mm512_load_ps(&pLs[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 sth,cth,cota,trm1,trm2,calp,salp;
                          register __m512 tana,x0,K2;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          tana= xtanf(alp);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_sub_ps(a,_mm512_mul_ps(Ls,tana));
                          x0  = _mm512_mul_ps(k0,trm1);
                          K2  = _mm512_mul_ps(_4opi,_mm512_mul_ps(trm1,trm2));
                          return (K2);
                  }


                  
                   __m512 K2_f6343_zmm16r4_u(const float * __restrict  pk0,
                                             const float * __restrict  pa,
                                             const float * __restrict  pLs,
                                             const float * __restrict  ptht,
                                             const float * __restrict  palp) {
                          
                          register __m512 k0a = _mm512_loadu_ps(&pk0a[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 Ls  = _mm512_loadu_ps(&pLs[0]);
                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          const __m512 _4opi = _mm512_set1_ps(1.27323954473516268615107010698f);
                          register __m512 sth,cth,cota,trm1,trm2,calp,salp;
                          register __m512 tana,x0,K2;
                          sth = xsinf(tht);
                          calp= xcosf(alp);
                          cth = xcosf(tht);
                          tana= xtanf(alp);
                          salp= xsinf(alp);
                          cota= _mm512_div_ps(calp,salp);
                          trm2= _mm512_sub_ps(sth,_mm512_mul_ps(cota,cth));
                          trm1= _mm512_sub_ps(a,_mm512_mul_ps(Ls,tana));
                          x0  = _mm512_mul_ps(k0,trm1);
                          K2  = _mm512_mul_ps(_4opi,_mm512_mul_ps(trm1,trm2));
                          return (K2);
                  }


                    /*
                          Cylindrical current approximation of
                          flat based truncated cone RCS for
                          perpendicular polarization.
                          Formula 6.3-41 
                    */


                  
                   __m512 rcs_f6341_zmm16r4(const __m512 gam0,
                                            const __m512 tht,
                                            const __m512 alp,
                                            const __m512 Ls,
                                            const __m512 k0,
                                            const __m512 a,
                                            const __m512 a1) {

                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi2 = _mm512_set1_ps(-1.57079632679489661923132169164f);
                          const __m512 _16 = _mm512_set1_ps(16.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 n1  = _mm512_set1_ps(-1.0f);
                          const __m512 pi2a= _mm512_sub_ps(pi2,alp);
                          register __m512 sth,cosa,cosa2,sina,k02,k0a;
                          register __m512 thta,cthta,cthta3,num,den,trm1;
                          register __m512 K1,K2,CK1,SK1,CK2,SK2,x0,x1;
                          register __m512 eai,ear,cer1,cei1,cer2,cei2,t0r,t0i;
                          register __m512 rcs,cabs;

                          if(_mm512_cmp_ps_mask(tht,pi2a,_CMP_EQ_OQ)) {
                              const __m512 _4o9 = _mm512_set1_ps(0.444444444444444444444444444444f);
                              register __m512 a32,a132,sqr,cota,cotas,diff;
                              x0   = _mm512_mul_ps(_4o9,k0);
                              cosa = xcosf(alp);
                              a32  = _mm512_pow_ps(a,_mm512_set1_ps(1.5f);
                              sina = xsinf(alp);
                              a321 = _mm512_pow_ps(a1,_mm512_set1_ps(1.5f);
                              cota = _mm512_div_ps(cosa,sina);
                              diff = _mm512_sub_ps(a32,a321);
                              cotas= _mm512_mul_ps(cota,cota);
                              x0   = _mm512_mul_ps(x0,cosa);
                              x1   = _mm512_mul_ps(cotas,_mm512_mul_ps(diff,diff));
                              rcs  = _mm512_mul_ps(x0,x1);
                              return (rcs);
                          }
                          else if(_mm512_cmp_ps_mask(a1,
                                            _mm512_setzero_ps(),_CMP_EQ_OQ)) {
                                  const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                                  const __m512 _9   = _mm512_set1_ps(9.0f);
                                  register __m512 rat,a3,num,den,cosa,sina,cota,cotas;
                                  a3   = _mm512_mul_ps(a,_mm512_mul_ps(a,a))'
                                  cosa = xcosf(alp);
                                  sina = xsinf(alp);
                                  num  = _mm512_mul_ps(_8pi,a3);
                                  cota = _mm512_div_ps(cosa,sina); 
                                  den  = _mm512_mul_ps(_9,gam0);
                                  cotas= _mm512_mul_ps(cota,cota);
                                  rat  = _mm512_div_ps(num,den);
                                  rcs  = _mm512_mul_ps(rat,_mm512_mul_ps(cosa,cotas));
                                  return (rcs);
                          }

                          k02  = _mm512_mul_ps(_16,_mm512_mul_ps(k0,k0));
                          k0a  = _mm512_mul_ps(k0,a);
                          sth  = xsinf(tht);
                          thta = _mm512_add_ps(tht,a);
                          sina = xsinf(alp);
                          ear  = _mm512_setzero_ps();
                          cosa = xcosf(tht);
                          eai  = pi2;
                          x0   = _mm512_mul_ps(pi,sina);
                          cthta= xcosf(thta);
                          x1   = _mm512_mul_ps(cosa,cosa);
                          K1   = K1_f6342_zmm16r4(k0a,tht,alp);
                          num  = _mm512_mul_ps(x0,_mm512_mul_ps(x1,sina));
                          K2   = K2_f6343_zmm16r4(K0,a,Ls,tht,alp);
                          x0   = _mm512_mul_ps(cthta,_mm512_mul_ps(cthta,cthta));
                          den  = _mm512_mul_ps(k02,x0);
                          fresnel_zmm16r4(K1,&CK1,&SK1);
                          trm1 = _mm512_div_ps(num,den);
                          eai  = _mm512_mul_ps(eai,_mm512_mul_ps(K1,K1));
                          cexp_zmm16r4(ear,eai,&cer1,&cei1);
                          fresnel_zmm16r4(K2,&CK2,&SK2);
                          cer1 = _mm512_mul_ps(cer1,K1);
                          cei1 = _mm512_mul_ps(cei1,K1);
                          eai  = _mm512_mul_ps(pi2,_mm512_mul_ps(K2,K2));
                          cexp_zmm16r4(ear,eai,&cer2,&cei2);
                          cer2 = _mm512_mul_ps(cer2,K2);
                          cei2 = _mm512_mul_ps(cei2,K2);
                          t0r  = _mm512_sub_ps(cer1,cer2);
                          t0i  = _mm512_sub_ps(cei1,cei2);
                          x0   = _mm512_add_ps(CK1,CK2);
                          x1   = _mm512_add_ps(SK1,SK2);
                          ear  = _mm512_sub_ps(t0r,x0);
                          eai  = _mm512_sub_ps(t0i,x1);
                          cabs = cabs_zmm16r4(ear,eai);
                          rcs  = _mm512_mul_ps(trm1,cabs);
                          return (rcs);
                 }


                 
                   __m512 rcs_f6341_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pLs,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pa1) {

                          register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          register __m512 Ls  = _mm512_load_ps(&pLs[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 a   = _mm512_load_ps(&pa1[0]);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi2 = _mm512_set1_ps(-1.57079632679489661923132169164f);
                          const __m512 _16 = _mm512_set1_ps(16.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 n1  = _mm512_set1_ps(-1.0f);
                          register __m512 sth,cosa,cosa2,sina,k02,k0a;
                          register __m512 thta,cthta,cthta3,num,den,trm1;
                          register __m512 K1,K2,CK1,SK1,CK2,SK2,x0,x1;
                          register __m512 eai,ear,cer1,cei1,cer2,cei2,t0r,t0i;
                          register __m512 rcs,cabs;

                          if(_mm512_cmp_ps_mask(tht,pi2a,_CMP_EQ_OQ)) {
                              const __m512 _4o9 = _mm512_set1_ps(0.444444444444444444444444444444f);
                              register __m512 a32,a132,sqr,cota,cotas,diff;
                              x0   = _mm512_mul_ps(_4o9,k0);
                              cosa = xcosf(alp);
                              a32  = _mm512_pow_ps(a,_mm512_set1_ps(1.5f);
                              sina = xsinf(alp);
                              a321 = _mm512_pow_ps(a1,_mm512_set1_ps(1.5f);
                              cota = _mm512_div_ps(cosa,sina);
                              diff = _mm512_sub_ps(a32,a321);
                              cotas= _mm512_mul_ps(cota,cota);
                              x0   = _mm512_mul_ps(x0,cosa);
                              x1   = _mm512_mul_ps(cotas,_mm512_mul_ps(diff,diff));
                              rcs  = _mm512_mul_ps(x0,x1);
                              return (rcs);
                          } 
                          else if(_mm512_cmp_ps_mask(a1,
                                            _mm512_setzero_ps(),_CMP_EQ_OQ)) {
                                  const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                                  const __m512 _9   = _mm512_set1_ps(9.0f);
                                  register __m512 rat,a3,num,den,cosa,sina,cota,cotas;
                                  a3   = _mm512_mul_ps(a,_mm512_mul_ps(a,a))'
                                  cosa = xcosf(alp);
                                  sina = xsinf(alp);
                                  num  = _mm512_mul_ps(_8pi,a3);
                                  cota = _mm512_div_ps(cosa,sina); 
                                  den  = _mm512_mul_ps(_9,gam0);
                                  cotas= _mm512_mul_ps(cota,cota);
                                  rat  = _mm512_div_ps(num,den);
                                  rcs  = _mm512_mul_ps(rat,_mm512_mul_ps(cosa,cotas));
                                  return (rcs);
                          }

                          k02  = _mm512_mul_ps(_16,_mm512_mul_ps(k0,k0));
                          k0a  = _mm512_mul_ps(k0,a);
                          sth  = xsinf(tht);
                          thta = _mm512_add_ps(tht,a);
                          sina = xsinf(alp);
                          ear  = _mm512_setzero_ps();
                          cosa = xcosf(tht);
                          eai  = pi2;
                          x0   = _mm512_mul_ps(pi,sina);
                          cthta= xcosf(thta);
                          x1   = _mm512_mul_ps(cosa,cosa);
                          K1   = K1_f6342_zmm16r4(k0a,tht,alp);
                          num  = _mm512_mul_ps(x0,_mm512_mul_ps(x1,sina));
                          K2   = K2_f6343_zmm16r4(K0,a,Ls,tht,alp);
                          x0   = _mm512_mul_ps(cthta,_mm512_mul_ps(cthta,cthta));
                          den  = _mm512_mul_ps(k02,x0);
                          fresnel_zmm16r4(K1,&CK1,&SK1);
                          trm1 = _mm512_div_ps(num,den);
                          eai  = _mm512_mul_ps(eai,_mm512_mul_ps(K1,K1));
                          cexp_zmm16r4(ear,eai,&cer1,&cei1);
                          fresnel_zmm16r4(K2,&CK2,&SK2);
                          cer1 = _mm512_mul_ps(cer1,K1);
                          cei1 = _mm512_mul_ps(cei1,K1);
                          eai  = _mm512_mul_ps(pi2,_mm512_mul_ps(K2,K2));
                          cexp_zmm16r4(ear,eai,&cer2,&cei2);
                          cer2 = _mm512_mul_ps(cer2,K2);
                          cei2 = _mm512_mul_ps(cei2,K2);
                          t0r  = _mm512_sub_ps(cer1,cer2);
                          t0i  = _mm512_sub_ps(cei1,cei2);
                          x0   = _mm512_add_ps(CK1,CK2);
                          x1   = _mm512_add_ps(SK1,SK2);
                          ear  = _mm512_sub_ps(t0r,x0);
                          eai  = _mm512_sub_ps(t0i,x1);
                          cabs = cabs_zmm16r4(ear,eai);
                          rcs  = _mm512_mul_ps(trm1,cabs);
                          return (rcs);
                 }


                  
                   __m512 rcs_f6341_zmm16r4_u(const float * __restrict  pgam0,
                                              const float * __restrict  ptht,
                                              const float * __restrict  palp,
                                              const float * __restrict  pLs,
                                              const float * __restrict  pk0,
                                              const float * __restrict  pa,
                                              const float * __restrict  pa1) {

                          register __m512 gam0= _mm512_loadu_ps(&pgam0[0]); 
                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          register __m512 Ls  = _mm512_loadu_ps(&pLs[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 a1  = _mm512_loadu_ps(&pa1[0]);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 pi2 = _mm512_set1_ps(-1.57079632679489661923132169164f);
                          const __m512 _16 = _mm512_set1_ps(16.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 n1  = _mm512_set1_ps(-1.0f);
                          register __m512 sth,cosa,cosa2,sina,k02,k0a;
                          register __m512 thta,cthta,cthta3,num,den,trm1;
                          register __m512 K1,K2,CK1,SK1,CK2,SK2,x0,x1;
                          register __m512 eai,ear,cer1,cei1,cer2,cei2,t0r,t0i;
                          register __m512 rcs,cabs;

                          if(_mm512_cmp_ps_mask(tht,pi2a,_CMP_EQ_OQ)) {
                              const __m512 _4o9 = _mm512_set1_ps(0.444444444444444444444444444444f);
                              register __m512 a32,a132,sqr,cota,cotas,diff;
                              x0   = _mm512_mul_ps(_4o9,k0);
                              cosa = xcosf(alp);
                              a32  = _mm512_pow_ps(a,_mm512_set1_ps(1.5f);
                              sina = xsinf(alp);
                              a321 = _mm512_pow_ps(a1,_mm512_set1_ps(1.5f);
                              cota = _mm512_div_ps(cosa,sina);
                              diff = _mm512_sub_ps(a32,a321);
                              cotas= _mm512_mul_ps(cota,cota);
                              x0   = _mm512_mul_ps(x0,cosa);
                              x1   = _mm512_mul_ps(cotas,_mm512_mul_ps(diff,diff));
                              rcs  = _mm512_mul_ps(x0,x1);
                              return (rcs);
                          } 
                          else if(_mm512_cmp_ps_mask(a1,
                                            _mm512_setzero_ps(),_CMP_EQ_OQ)) {
                                  const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                                  const __m512 _9   = _mm512_set1_ps(9.0f);
                                  register __m512 rat,a3,num,den,cosa,sina,cota,cotas;
                                  a3   = _mm512_mul_ps(a,_mm512_mul_ps(a,a))'
                                  cosa = xcosf(alp);
                                  sina = xsinf(alp);
                                  num  = _mm512_mul_ps(_8pi,a3);
                                  cota = _mm512_div_ps(cosa,sina); 
                                  den  = _mm512_mul_ps(_9,gam0);
                                  cotas= _mm512_mul_ps(cota,cota);
                                  rat  = _mm512_div_ps(num,den);
                                  rcs  = _mm512_mul_ps(rat,_mm512_mul_ps(cosa,cotas));
                                  return (rcs);
                          }

                          k02  = _mm512_mul_ps(_16,_mm512_mul_ps(k0,k0));
                          k0a  = _mm512_mul_ps(k0,a);
                          sth  = xsinf(tht);
                          thta = _mm512_add_ps(tht,a);
                          sina = xsinf(alp);
                          ear  = _mm512_setzero_ps();
                          cosa = xcosf(tht);
                          eai  = pi2;
                          x0   = _mm512_mul_ps(pi,sina);
                          cthta= xcosf(thta);
                          x1   = _mm512_mul_ps(cosa,cosa);
                          K1   = K1_f6342_zmm16r4(k0a,tht,alp);
                          num  = _mm512_mul_ps(x0,_mm512_mul_ps(x1,sina));
                          K2   = K2_f6343_zmm16r4(K0,a,Ls,tht,alp);
                          x0   = _mm512_mul_ps(cthta,_mm512_mul_ps(cthta,cthta));
                          den  = _mm512_mul_ps(k02,x0);
                          fresnel_zmm16r4(K1,&CK1,&SK1);
                          trm1 = _mm512_div_ps(num,den);
                          eai  = _mm512_mul_ps(eai,_mm512_mul_ps(K1,K1));
                          cexp_zmm16r4(ear,eai,&cer1,&cei1);
                          fresnel_zmm16r4(K2,&CK2,&SK2);
                          cer1 = _mm512_mul_ps(cer1,K1);
                          cei1 = _mm512_mul_ps(cei1,K1);
                          eai  = _mm512_mul_ps(pi2,_mm512_mul_ps(K2,K2));
                          cexp_zmm16r4(ear,eai,&cer2,&cei2);
                          cer2 = _mm512_mul_ps(cer2,K2);
                          cei2 = _mm512_mul_ps(cei2,K2);
                          t0r  = _mm512_sub_ps(cer1,cer2);
                          t0i  = _mm512_sub_ps(cei1,cei2);
                          x0   = _mm512_add_ps(CK1,CK2);
                          x1   = _mm512_add_ps(SK1,SK2);
                          ear  = _mm512_sub_ps(t0r,x0);
                          eai  = _mm512_sub_ps(t0i,x1);
                          cabs = cabs_zmm16r4(ear,eai);
                          rcs  = _mm512_mul_ps(trm1,cabs);
                          return (rcs);
                 }


                   /*
                          Cylindrical current approximation of
                          flat based pointed cone RCS for
                          perpendicular polarization.
                          Formula 6.3-44
                     */


                
                   __m512 rcs_f6344_zmm16r4(const __m512 gam0,
                                            const __m512 a,
                                            const __m512 tht,
                                            const __m512 alp,
                                            const __m512 k0) {

                          const __m512 pi2  = _mm512_set1_ps(1.57079632679489661923132169164f);
                          const __m512 _4opi= _mm512_set1_ps(1.27323954473516268615107010698f)
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 gama,sint,tana,cost,sina1,cosa1,cott,cota1,den,x0,x1;
                          register __m512 C2,S2,rat,arg,carg,sarg,num,trm1,trm2,ksi,ksi2,x2;
                          k0a   = _mm512_mul_ps(k0,a);
                          x0    = _mm512_sub_ps(alp,_1);
                          sint  = xsinf(tht);
                          gama  = _mm512_mul_ps(gam0,a);
                          cost  = xcosf(tht);
                          cott  = _mm512_div_ps(cost,sint);
                          tana  = xtanf(alp);
                          sina1 = xsinf(x0);
                          cosa1 = xcosf(x0);
                          cota1 = _mm512_div_ps(cosa1,sina1);
                          x2    = _mm512_mul_ps(cott,cota1);
                          x1    = _mm512_mul_ps(k0a,_4opi);
                          ksi2  = _mm512_mul_ps(x1,_mm512_mul_ps(sint,x2));
                          arg   = _mm512_mul_ps(pi2,ksi2);
                          ksi   = _mm512_sqrt_ps(ksi2);
                          fresnel_zmm16r4(ksi,&C2,&S2);
                          carg  = xcosf(arg);
                          sarg  = xsinf(arg);
                          x0    = _mm512_mul_ps(tana,tana);
                          x1    = _mm512_mul_ps(_8pi,sint);
                          den   = _mm512_mul_ps(_mm512_mul_ps(x0,x1),x2);
                          trm1  = _mm512_div_ps(_mm512_fmadd_ps(C2,C2,
                                                            _mm512_mul_ps(S2,S2)),ksi2);
                          trm1  = _mm512_add_ps(_1,trm1);
                          x1    = _mm512_fmadd_ps(C2,carg,_mm512_mul_ps(S2,sarg));
                          x0    = _mm512_div_ps(_2,ksi);
                          num   = _mm512_sub_ps(trm1,_mm512_mul_ps(x0,x1));
                          rat   = _mm512_div_ps(num,den);
                          rcs   = _mm512_mul_ps(gama,rat);
                          return (rcs);
                }


                 
                   __m512 rcs_f6344_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam0,
                                            const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) palp,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 gam0 = _mm512_load_ps(&pgam0[0]);
                          register __m512 a    = _mm512_load_ps(&pa[0]);
                          register __m512 tht  = _mm512_load_ps(&ptht[0]);
                          register __m512 alp  = _mm512_load_ps(&palp[0]);
                          register __m512 k0   = _mm512_load_ps(&pk0[0]);
                          const __m512 pi2  = _mm512_set1_ps(1.57079632679489661923132169164f);
                          const __m512 _4opi= _mm512_set1_ps(1.27323954473516268615107010698f)
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 gama,sint,tana,cost,sina1,cosa1,cott,cota1,den,x0,x1;
                          register __m512 C2,S2,rat,arg,carg,sarg,num,trm1,trm2,ksi,ksi2,x2;
                          k0a   = _mm512_mul_ps(k0,a);
                          x0    = _mm512_sub_ps(alp,_1);
                          sint  = xsinf(tht);
                          gama  = _mm512_mul_ps(gam0,a);
                          cost  = xcosf(tht);
                          cott  = _mm512_div_ps(cost,sint);
                          tana  = xtanf(alp);
                          sina1 = xsinf(x0);
                          cosa1 = xcosf(x0);
                          cota1 = _mm512_div_ps(cosa1,sina1);
                          x2    = _mm512_mul_ps(cott,cota1);
                          x1    = _mm512_mul_ps(k0a,_4opi);
                          ksi2  = _mm512_mul_ps(x1,_mm512_mul_ps(sint,x2));
                          arg   = _mm512_mul_ps(pi2,ksi2);
                          ksi   = _mm512_sqrt_ps(ksi2);
                          fresnel_zmm16r4(ksi,&C2,&S2);
                          carg  = xcosf(arg);
                          sarg  = xsinf(arg);
                          x0    = _mm512_mul_ps(tana,tana);
                          x1    = _mm512_mul_ps(_8pi,sint);
                          den   = _mm512_mul_ps(_mm512_mul_ps(x0,x1),x2);
                          trm1  = _mm512_div_ps(_mm512_fmadd_ps(C2,C2,
                                                            _mm512_mul_ps(S2,S2)),ksi2);
                          trm1  = _mm512_add_ps(_1,trm1);
                          x1    = _mm512_fmadd_ps(C2,carg,_mm512_mul_ps(S2,sarg));
                          x0    = _mm512_div_ps(_2,ksi);
                          num   = _mm512_sub_ps(trm1,_mm512_mul_ps(x0,x1));
                          rat   = _mm512_div_ps(num,den);
                          rcs   = _mm512_mul_ps(gama,rat);
                          return (rcs);
                }


                 
                   __m512 rcs_f6344_zmm16r4_u(const float * __restrict  pgam0,
                                            const float * __restrict  pa,
                                            const float * __restrict  ptht,
                                            const float * __restrict  palp,
                                            const float * __restrict  pk0) {

                          register __m512 gam0 = _mm512_loadu_ps(&pgam0[0]);
                          register __m512 a    = _mm512_loadu_ps(&pa[0]);
                          register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                          register __m512 alp  = _mm512_loadu_ps(&palp[0]);
                          register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi2  = _mm512_set1_ps(1.57079632679489661923132169164f);
                          const __m512 _4opi= _mm512_set1_ps(1.27323954473516268615107010698f)
                          const __m512 _1   = _mm512_set1_ps(1.0f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          const __m512 _8pi = _mm512_set1_ps(25.132741228718345907701147066236f);
                          register __m512 gama,sint,tana,cost,sina1,cosa1,cott,cota1,den,x0,x1;
                          register __m512 C2,S2,rat,arg,carg,sarg,num,trm1,trm2,ksi,ksi2,x2;
                          k0a   = _mm512_mul_ps(k0,a);
                          x0    = _mm512_sub_ps(alp,_1);
                          sint  = xsinf(tht);
                          gama  = _mm512_mul_ps(gam0,a);
                          cost  = xcosf(tht);
                          cott  = _mm512_div_ps(cost,sint);
                          tana  = xtanf(alp);
                          sina1 = xsinf(x0);
                          cosa1 = xcosf(x0);
                          cota1 = _mm512_div_ps(cosa1,sina1);
                          x2    = _mm512_mul_ps(cott,cota1);
                          x1    = _mm512_mul_ps(k0a,_4opi);
                          ksi2  = _mm512_mul_ps(x1,_mm512_mul_ps(sint,x2));
                          arg   = _mm512_mul_ps(pi2,ksi2);
                          ksi   = _mm512_sqrt_ps(ksi2);
                          fresnel_zmm16r4(ksi,&C2,&S2);
                          carg  = xcosf(arg);
                          sarg  = xsinf(arg);
                          x0    = _mm512_mul_ps(tana,tana);
                          x1    = _mm512_mul_ps(_8pi,sint);
                          den   = _mm512_mul_ps(_mm512_mul_ps(x0,x1),x2);
                          trm1  = _mm512_div_ps(_mm512_fmadd_ps(C2,C2,
                                                            _mm512_mul_ps(S2,S2)),ksi2);
                          trm1  = _mm512_add_ps(_1,trm1);
                          x1    = _mm512_fmadd_ps(C2,carg,_mm512_mul_ps(S2,sarg));
                          x0    = _mm512_div_ps(_2,ksi);
                          num   = _mm512_sub_ps(trm1,_mm512_mul_ps(x0,x1));
                          rat   = _mm512_div_ps(num,den);
                          rcs   = _mm512_mul_ps(gama,rat);
                          return (rcs);
                }


                   /*
                        Geometrical Diffraction.
                        Flat-backed cone, backscattered RCS.
                        Simplified by neglecting a second order terms of 6.3-49
                        Formula 6.3-50
                    */


                 
                   __m512 rcs_f6350_zmm16r4(const __m512 k0,
                                            const __m512 a,
                                            const __m512 alp) {

                          const __m512 ipi = _mm512_set1_ps(0.318309886183790671537767526745f);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3pi= _mm512_set1_ps(9.424777960769379715387930149839f);
                          register __m512 k0a,n,arg,sarg,carg,arg2,carg2;
                          register __m512 rcs,x0,x1,inv2;
                          k0a  = _mm512_mul_ps(k0,a);
                          n    = _mm512_add_ps(_mm512_set1_ps(1.5f),
                                               _mm512_div_ps(alp,pi));
                          arg  = _mm512_div_ps(pi,n);
                          sarg = xsinf(arg);
                          x0   = _mm512_div_ps(_mm512_mul_ps(k0a,sarg),n);
                          carg = xcosf(arg);
                          arg2 = _mm512_div_ps(_3pi,n);
                          x1   = _mm512_mul_ps(x0,x0);
                          carg2= xcosf(arg2);
                          x0   = _mm512_sub_ps(carg,carg2);
                          inv2 = _mm512_rcp14_ps(_mm512_mul_ps(x0,x0));
                          rcs  = _mm512_mul_ps(ipi,_mm512_mul_ps(x0,inv2));
                          return (rcs);
                 }


                 
                   __m512 rcs_f6350_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) palp) {

                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          const __m512 ipi = _mm512_set1_ps(0.318309886183790671537767526745f);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3pi= _mm512_set1_ps(9.424777960769379715387930149839f);
                          register __m512 k0a,n,arg,sarg,carg,arg2,carg2;
                          register __m512 rcs,x0,x1,inv2;
                          k0a  = _mm512_mul_ps(k0,a);
                          n    = _mm512_add_ps(_mm512_set1_ps(1.5f),
                                               _mm512_div_ps(alp,pi));
                          arg  = _mm512_div_ps(pi,n);
                          sarg = xsinf(arg);
                          x0   = _mm512_div_ps(_mm512_mul_ps(k0a,sarg),n);
                          carg = xcosf(arg);
                          arg2 = _mm512_div_ps(_3pi,n);
                          x1   = _mm512_mul_ps(x0,x0);
                          carg2= xcosf(arg2);
                          x0   = _mm512_sub_ps(carg,carg2);
                          inv2 = _mm512_rcp14_ps(_mm512_mul_ps(x0,x0));
                          rcs  = _mm512_mul_ps(ipi,_mm512_mul_ps(x0,inv2));
                          return (rcs);
                 }


                   
                   __m512 rcs_f6350_zmm16r4_u(const float * __restrict  pk0,
                                              const float * __restrict  pa,
                                              const float * __restrict  palp) {

                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          const __m512 ipi = _mm512_set1_ps(0.318309886183790671537767526745f);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3pi= _mm512_set1_ps(9.424777960769379715387930149839f);
                          register __m512 k0a,n,arg,sarg,carg,arg2,carg2;
                          register __m512 rcs,x0,x1,inv2;
                          k0a  = _mm512_mul_ps(k0,a);
                          n    = _mm512_add_ps(_mm512_set1_ps(1.5f),
                                               _mm512_div_ps(alp,pi));
                          arg  = _mm512_div_ps(pi,n);
                          sarg = xsinf(arg);
                          x0   = _mm512_div_ps(_mm512_mul_ps(k0a,sarg),n);
                          carg = xcosf(arg);
                          arg2 = _mm512_div_ps(_3pi,n);
                          x1   = _mm512_mul_ps(x0,x0);
                          carg2= xcosf(arg2);
                          x0   = _mm512_sub_ps(carg,carg2);
                          inv2 = _mm512_rcp14_ps(_mm512_mul_ps(x0,x0));
                          rcs  = _mm512_mul_ps(ipi,_mm512_mul_ps(x0,inv2));
                          return (rcs);
                 }


                  /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series convergence.
                         Formula 6.3-56
                    */


                  /*
                         Complex 'j' phase associated with each 'j' amplitude.
                         Formula 6.3-58, 6.3-56 (complex exponent term only).
                    */


                  
                   void expj_f6358_zmm16(const __m512 k0,
                                         const __m512 beta,
                                         const __m512 a,
                                         const __m512 h,
                                         const __m512 tht,
                                       __m512 * __restrict cer,
                                       __m512 * __restrict cei) {

                        using gms::math;
                        const __m512 pi4 = _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        register __m512 _2k0,b2,sint,cost,cosb,negt,x0;
                        register __m512 ear,eai;
                        b2   = _mm512_mul_ps(beta,hlf);
                        sint = xsinf(tht);
                        _2k0 = _mm512_add_ps(k0,k0);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        cosb = xcosf(b2);
                        negt = negate_zmm16r4( _mm512_mul_ps(_2k0,cosb));
                        x0   = _mm512_fmadd_ps(a,sint,_mm512_mul_ps(h,cost));
                        eai  = _mm512_fmadd_ps(negt,x0,pi4);
                        cexp_zmm16r4(ear,eai,*cer,*cei);
                 }


                  
                   void expj_f6358_zmm16_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pbeta,
                                           const float * __restrict __ATTR_ALIGN__(64) pa,
                                           const float * __restrict __ATTR_ALIGN__(64) ph,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht,
                                           float * __restrict __ATTR_ALIGN__(64) cer,
                                           float * __restrict __ATTR_ALIGN__(64) cei) {

                        using gms::math;
                        register __m512 k0   = _mm512_load_ps(&pk0[0]);
                        register __m512 beta = _mm512_load_ps(&pbeta[0]);
                        register __m512 a    = _mm512_load_ps(&pa[0]);
                        register __m512 h    = _mm512_load_ps(&ph[0]);
                        register __m512 tht  = _mm512_load_ps(&ptht[0]);
                        const __m512 pi4 = _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        register __m512 _2k0,b2,sint,cost,cosb,negt,x0;
                        register __m512 ear,eai,resr,resi;
                        b2   = _mm512_mul_ps(beta,hlf);
                        sint = xsinf(tht);
                        _2k0 = _mm512_add_ps(k0,k0);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        cosb = xcosf(b2);
                        negt = negate_zmm16r4( _mm512_mul_ps(_2k0,cosb));
                        x0   = _mm512_fmadd_ps(a,sint,_mm512_mul_ps(h,cost));
                        eai  = _mm512_fmadd_ps(negt,x0,pi4);
                        cexp_zmm16r4(ear,eai,&resr,&resi);
                        _mm512_store_ps(&cer[0], resr);
                        _mm512_store_ps(&cei[0], resi);
                 }


                  
                   void expj_f6358_zmm16_u(const float * __restrict  pk0,
                                           const float * __restrict  pbeta,
                                           const float * __restrict  pa,
                                           const float * __restrict  ph,
                                           const float * __restrict  ptht,
                                           float * __restrict  cer,
                                           float * __restrict  cei) {

                        using gms::math;
                        register __m512 k0   = _mm512_loadu_ps(&pk0[0]);
                        register __m512 beta = _mm512_loadu_ps(&pbeta[0]);
                        register __m512 a    = _mm512_loadu_ps(&pa[0]);
                        register __m512 h    = _mm512_loadu_ps(&ph[0]);
                        register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                        const __m512 pi4 = _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 hlf = _mm512_set1_ps(0.5f);
                        register __m512 _2k0,b2,sint,cost,cosb,negt,x0;
                        register __m512 ear,eai,resr,resi;
                        b2   = _mm512_mul_ps(beta,hlf);
                        sint = xsinf(tht);
                        _2k0 = _mm512_add_ps(k0,k0);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        cosb = xcosf(b2);
                        negt = negate_zmm16r4( _mm512_mul_ps(_2k0,cosb));
                        x0   = _mm512_fmadd_ps(a,sint,_mm512_mul_ps(h,cost));
                        eai  = _mm512_fmadd_ps(negt,x0,pi4);
                        cexp_zmm16r4(ear,eai,&resr,&resi);
                        _mm512_storeu_ps(&cer[0], resr);
                        _mm512_storeu_ps(&cei[0], resi);
                 }


                   /*
                         Axially asymetric edge diffraction amplitudes.
                         Part of kernel 6.3-56
                         Formula 6.3-57
                     */


                 
                   __m512 rcs_f6357_zmm16r4(const __m512 alp,
                                            const __m512 tht,
                                            const __m512 beta,
                                            const __m512 beta1,
                                            const __m512 a,
                                            const __m512 k0,
                                            const bool ver ) { // addition (true) or subtraction (false) of cosine terms in 6.3-57

                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3o2 = _mm512_set1_ps(1.5f);
                          const __m512 hlf  = _mm512_set1_ps(0.5f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          register __m512 b1,n,arg1,psi1,sarg1,carg1,arg2,carg2,x2;
                          register __m512 rcs,invn,cosb2,x0,x1,trm1,trm2,trm3,sint,trm4;
                          n    = _mm512_add_ps(_3o2,_mm512_div_ps(alp,pi));
                          arg2 = _mm512_fmadd_ps(_2,beta,pi);
                          b1   = _mm512_mul_ps(beta1,hlf);
                          arg2 = _mm512_div_ps(arg2,n);
                          arg1 = _mm512_div_ps(pi,n);
                          psi1 = _mm512_add_ps(tht,b1);
                          sarg1= xsinf(arg1);
                          sint = xsinf(psi1);
                          invn = _mm512_rcp14_ps(n);
                          cosb2= xcosf(_mm512_mul_ps(beta,hlf));
                          trm1 = _mm512_mul_ps(sarg1,invn);
                          x2   = _mm512_div_ps(beta1,n);
                          carg1= xcosf(arg1);
                          x0   = _mm512_mul_ps(a,_mm512_rcp14_ps(sint));
                          carg2= xcosf(arg2);
                          x1   = _mm512_mul_ps(k0,cosb2);
                          sarg1= xcosf(x2);
                          trm2 = _mm512_div_ps(x0,x1);
                          trm3 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,carg2));
                          trm4 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,sarg1));
                          x0   = _mm512_sqrt_ps(trm2);
                          (ver == true) ? x1   = _mm512_add_ps(trm3,trm4) : 
                                          x1   = _mm512_sub_ps(trm3,trm4);
                          rcs  = _mm512_mul_ps(_mm512_mul_ps(trm1,x0),x1);
                          return (rcs);
                 }


                  
                   __m512 rcs_f6357_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) pbeta,
                                              const float * __restrict __ATTR_ALIGN__(64) pbeta1,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const bool ver) { // addition (true) or subtraction (false) of cosine terms in 6.3-57

                          register __m512 alp   = _mm512_load_ps(&palp[0]);
                          register __m512 tht   = _mm512_load_ps(&ptht[0]);
                          register __m512 beta  = _mm512_load_ps(&pbeta[0]);
                          register __m512 beta1 = _mm512_load_ps(&pbeta1[0]);
                          register __m512 a     = _mm512_load_ps(&pa[0]);
                          register __m512 k0    = _mm512_load_ps(&pk0[0]);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3o2 = _mm512_set1_ps(1.5f);
                          const __m512 hlf  = _mm512_set1_ps(0.5f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          register __m512 b1,n,arg1,psi1,sarg1,carg1,arg2,carg2,x2;
                          register __m512 rcs,invn,cosb2,x0,x1,trm1,trm2,trm3,sint,trm4;
                          n    = _mm512_add_ps(_3o2,_mm512_div_ps(alp,pi));
                          arg2 = _mm512_fmadd_ps(_2,beta,pi);
                          b1   = _mm512_mul_ps(beta1,hlf);
                          arg2 = _mm512_div_ps(arg2,n);
                          arg1 = _mm512_div_ps(pi,n);
                          psi1 = _mm512_add_ps(tht,b1);
                          sarg1= xsinf(arg1);
                          sint = xsinf(psi1);
                          invn = _mm512_rcp14_ps(n);
                          cosb2= xcosf(_mm512_mul_ps(beta,hlf));
                          trm1 = _mm512_mul_ps(sarg1,invn);
                          x2   = _mm512_div_ps(beta1,n);
                          carg1= xcosf(arg1);
                          x0   = _mm512_mul_ps(a,_mm512_rcp14_ps(sint));
                          carg2= xcosf(arg2);
                          x1   = _mm512_mul_ps(k0,cosb2);
                          sarg1= xcosf(x2);
                          trm2 = _mm512_div_ps(x0,x1);
                          trm3 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,carg2));
                          trm4 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,sarg1));
                          x0   = _mm512_sqrt_ps(trm2);
                          (ver == true) ? x1   = _mm512_add_ps(trm3,trm4) : 
                                          x1   = _mm512_sub_ps(trm3,trm4);
                          rcs  = _mm512_mul_ps(_mm512_mul_ps(trm1,x0),x1);
                          return (rcs);
                 }


                   
                   __m512 rcs_f6357_zmm16r4_u(const float * __restrict  palp,
                                              const float * __restrict  ptht,
                                              const float * __restrict  pbeta,
                                              const float * __restrict  pbeta1,
                                              const float * __restrict  pa,
                                              const float * __restrict  pk0,
                                              const bool ver) { // addition (true) or subtraction (false) of cosine terms in 6.3-57

                          register __m512 alp   = _mm512_loadu_ps(&palp[0]);
                          register __m512 tht   = _mm512_loadu_ps(&ptht[0]);
                          register __m512 beta  = _mm512_loadu_ps(&pbeta[0]);
                          register __m512 beta1 = _mm512_loadu_ps(&pbeta1[0]);
                          register __m512 a     = _mm512_loadu_ps(&pa[0]);
                          register __m512 k0    = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi   = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _3o2 = _mm512_set1_ps(1.5f);
                          const __m512 hlf  = _mm512_set1_ps(0.5f);
                          const __m512 _2   = _mm512_set1_ps(2.0f);
                          register __m512 b1,n,arg1,psi1,sarg1,carg1,arg2,carg2,x2;
                          register __m512 rcs,invn,cosb2,x0,x1,trm1,trm2,trm3,sint,trm4;
                          n    = _mm512_add_ps(_3o2,_mm512_div_ps(alp,pi));
                          arg2 = _mm512_fmadd_ps(_2,beta,pi);
                          b1   = _mm512_mul_ps(beta1,hlf);
                          arg2 = _mm512_div_ps(arg2,n);
                          arg1 = _mm512_div_ps(pi,n);
                          psi1 = _mm512_add_ps(tht,b1);
                          sarg1= xsinf(arg1);
                          sint = xsinf(psi1);
                          invn = _mm512_rcp14_ps(n);
                          cosb2= xcosf(_mm512_mul_ps(beta,hlf));
                          trm1 = _mm512_mul_ps(sarg1,invn);
                          x2   = _mm512_div_ps(beta1,n);
                          carg1= xcosf(arg1);
                          x0   = _mm512_mul_ps(a,_mm512_rcp14_ps(sint));
                          carg2= xcosf(arg2);
                          x1   = _mm512_mul_ps(k0,cosb2);
                          sarg1= xcosf(x2);
                          trm2 = _mm512_div_ps(x0,x1);
                          trm3 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,carg2));
                          trm4 = _mm512_rcp14_ps(_mm512_sub_ps(carg1,sarg1));
                          x0   = _mm512_sqrt_ps(trm2);
                          (ver == true) ? x1   = _mm512_add_ps(trm3,trm4) : 
                                          x1   = _mm512_sub_ps(trm3,trm4);
                          rcs  = _mm512_mul_ps(_mm512_mul_ps(trm1,x0),x1);
                          return (rcs);
                 }


                       /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- single term only
                    */


                 
                   __m512 rcs_f6356_term1_zmm16r4(const __m512 alp,
                                              const __m512 h,
                                              const __m512 beta,
                                              const __m512 beta1,
                                              const __m512 a,
                                              const __m512 k0,
                                              const __m512 tht,
                                              const bool ver) {

                          register __m512 cer,cei,rcs6357,t0r,t0i,cabs,rcs;
                          expj_f6358_zmm16(k0,beta,a,h,tht,&cer,&cei);
                          rcs6357 = rcs_f6357_zmm16r4(alp,tht,beta,beta1,
                                                      a,k0,ver);
                          t0r = _mm512_mul_ps(cer,rcs6357);
                          t0i = _mm512_mul_ps(cei,rcs6357);
                          cabs= cabs_zmm16r4(t0r,t0i);
                          rcs = cabs;
                          return (rcs);
                 } 


                 
                   __m512 rcs_f6356_term1_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) palp,
                                                  const float * __restrict __ATTR_ALIGN__(64) ph,
                                                  const float * __restrict __ATTR_ALIGN__(64) pbeta,
                                                  const float * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                  const float * __restrict __ATTR_ALIGN__(64) pa,
                                                  const float * __restrict __ATTR_ALIGN__(64) pk0,
                                                  const float * __restrict __ATTR_ALIGN__(64) ptht,
                                                  const bool ver) {

                          register __m512 alp   = _mm512_load_ps(&palp[0]);
                          register __m512 h     = _mm512_load_ps(&ph[0]);
                          register __m512 beta  = _mm512_load_ps(&pbeta[0]);
                          register __m512 beta1 = _mm512_load_ps(&pbeta1[0]);
                          register __m512 a     = _mm512_load_ps(&pa[0]);
                          register __m512 k0    = _mm512_load_ps(&pk0[0]);
                          register __m512 tht   = _mm512_load_ps(&ptht[0]);
                          register __m512 cer,cei,rcs6357,t0r,t0i,cabs,rcs;
                          expj_f6358_zmm16(k0,beta,a,h,tht,&cer,&cei);
                          rcs6357 = rcs_f6357_zmm16r4(alp,tht,beta,beta1,
                                                      a,k0,ver);
                          t0r = _mm512_mul_ps(cer,rcs6357);
                          t0i = _mm512_mul_ps(cei,rcs6357);
                          cabs= cabs_zmm16r4(t0r,t0i);
                          rcs = cabs;
                          return (rcs);
                 } 


               
                   __m512 rcs_f6356_term1_zmm16r4_u(const float * __restrict  palp,
                                                  const float * __restrict  ph,
                                                  const float * __restrict  pbeta,
                                                  const float * __restrict  pbeta1,
                                                  const float * __restrict  pa,
                                                  const float * __restrict  pk0,
                                                  const float * __restrict  ptht,
                                                  const bool ver) {

                          register __m512 alp   = _mm512_loadu_ps(&palp[0]);
                          register __m512 h     = _mm512_loadu_ps(&ph[0]);
                          register __m512 beta  = _mm512_loadu_ps(&pbeta[0]);
                          register __m512 beta1 = _mm512_loadu_ps(&pbeta1[0]);
                          register __m512 a     = _mm512_loadu_ps(&pa[0]);
                          register __m512 k0    = _mm512_loadu_ps(&pk0[0]);
                          register __m512 tht   = _mm512_loadu_ps(&ptht[0]);
                          register __m512 cer,cei,rcs6357,t0r,t0i,cabs,rcs;
                          expj_f6358_zmm16(k0,beta,a,h,tht,&cer,&cei);
                          rcs6357 = rcs_f6357_zmm16r4(alp,tht,beta,beta1,
                                                      a,k0,ver);
                          t0r = _mm512_mul_ps(cer,rcs6357);
                          t0i = _mm512_mul_ps(cei,rcs6357);
                          cabs= cabs_zmm16r4(t0r,t0i);
                          rcs = cabs;
                          return (rcs);
                 } 


                     /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- multiple terms.
                    */


                   __m512 rcs_f6356_nterm_zmm16r4(  const __m512 * __restrict __ATTR_ALIGN__(64) palp,
                                                    const __m512 h,
                                                    const __m512 * __restrict __ATTR_ALIGN__(64) pbeta,
                                                    const __m512 * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                    const __m512 a,
                                                    const __m512 k0,
                                                    const __m512 * __restrict __ATTR_ALIGN__(64) ptht,
                                                    const int32_t n,
                                                    const bool ver) {

                       

                         if(__builtin_expect(n<=0,0)) { return _mm512_setzero_ps();}
                         if(__builtin_expect(n==1,0)) { 
                             return (rcs_f6356_term1_zmm16r4(palp[0],h,pbeta[0],pbeta1[0],
                                                            a,k0,ptht[0],ver);)
                         }
                         
                         register __m512 cer,cei,rcs6357,t0r,t0i,cabs,rcs;
                         register __m512 accr,acci;
                         int32_t j; 
                         accr = _mm512_setzero_ps();
                         acci = accr;
                         for(j = 0; j != n; ++j) {
                             register __m512 al = palp[j];
                             register __m512 b = pbeta[j];
                             register __m512 b1= pbeta1[j];
                             register __m512 t = ptht[j];
                             expj_f6358_zmm16(k0,b,a,h,t,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al,t,b,b1,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                         }
                         cabs = cabs_zmm16r4(accr,acci);
                         rcs  = cabs;
                         return (rcs);
                 }


                    /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- multiple terms, unrolled 16x.
                    */

              
                   float rcs_f6356_nterm_u16x_zmm16r4(    const __m512 * __restrict __ATTR_ALIGN__(64) palp,
                                                         const __m512 h,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                         const __m512 a,
                                                         const __m512 k0,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) ptht,
                                                         const int32_t n,
                                                         const bool ver) {

                       

                         if(__builtin_expect(n<=0,0)) { return _mm512_setzero_ps();}
                                                  
                         __m512 cer,cei,rcs6357,t0r,t0i,cabs;
                         float rcs = 0.0f;
                         register __m512 al0,al1,al2,al3,al4,al5,al6,al7
                         register __m512 b0,b1,b2,b3,b4,b,b6,b7;
                         register __m512 b10,b11,b12,b13,b14,b1,b16,b17;
                         register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                         register __m512 accr,acci;
                         int32_t j,m,m1; 
                         accr = _mm512_setzero_ps();
                         acci = accr;
                         m = n%16;
                         if(m != 0) {
                            for(j = 0; j != m; ++j) {
                                register __m512 al = palp[j];
                                register __m512 b = pbeta[j];
                                register __m512 b1= pbeta1[j];
                                register __m512 t = ptht[j];
                                expj_f6358_zmm16(k0,b,a,h,t,&cer,&cei);
                                rcs6357 = rcs_f6357_zmm16r4(al,t,b,b1,
                                                         a,k0,ver);
                                t0r     = _mm512_mul_ps(cer,rcs6357);
                                accr    = _mm512_add_ps(accr,t0r);
                                t0i     = _mm512_mul_ps(cei,rcs6357);
                                acci    = _mm512_add_ps(acci,t0i);
                            }
                             if(n<16) {
                                cabs = cabs_zmm16r4(accr,acci);
                                rcs  = _mm512_reduce_add_ps(cabs);
                                return (rcs);
                             }
                         }
                         m1 = m+1;
                         for(j = m1; j != n; j += 16) {
                             al0 = palp[j+0];
                             b0 = pbeta[j+0];
                             b10= pbeta1[j+0];
                             t0 = ptht[j+0];
                             expj_f6358_zmm16(k0,b0,a,h,t0,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al0,t0,b0,b10,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al1 = palp[j+1];
                             b1 = pbeta[j+1];
                             b11= pbeta1[j+1];
                             t1 = ptht[j+1];
                             expj_f6358_zmm16(k0,b1,a,h,t1,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al1,t1,b1,b11,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al2 = palp[j+2];
                             b2 = pbeta[j+2];
                             b12= pbeta1[j+2];
                             t2 = ptht[j+2];
                             expj_f6358_zmm16(k0,b2,a,h,t2,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al2,t2,b2,b12,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al3 = palp[j+3];
                             b3 = pbeta[j+3];
                             b13= pbeta1[j+3];
                             t3 = ptht[j+3];
                             expj_f6358_zmm16(k0,b3,a,h,t3,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al3,t3,b3,b13,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al4 = palp[j+4];
                             b4 = pbeta[j+4];
                             b14= pbeta1[j+4];
                             t4 = ptht[j+4];
                             expj_f6358_zmm16(k0,b4,a,h,t4,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al4,t4,b4,b14,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al5 = palp[j+5];
                             b5 = pbeta[j+5];
                             b15= pbeta1[j+5];
                             t5 = ptht[j+5];
                             expj_f6358_zmm16(k0,b5,a,h,t5,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al5,t5,b5,b15,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al6 = palp[j+6];
                             b6 = pbeta[j+6];
                             b16= pbeta1[j+6];
                             t6 = ptht[j+6];
                             expj_f6358_zmm16(k0,b6,a,h,t6,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al6,t6,b6,b16,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al7 = palp[j+7];
                             b7 = pbeta[j+7];
                             b17= pbeta1[j+7];
                             t7 = ptht[j+7];
                             expj_f6358_zmm16(k0,b7,a,h,t7,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al7,t7,b7,b17,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al0 = palp[j+8];
                             b0 = pbeta[j+8];
                             b10= pbeta1[j+8];
                             t0 = ptht[j+8];
                             expj_f6358_zmm16(k0,b0,a,h,t0,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al0,t0,b0,b10,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al1 = palp[j+9];
                             b1 = pbeta[j+9];
                             b11= pbeta1[j+9];
                             t1 = ptht[j+9];
                             expj_f6358_zmm16(k0,b1,a,h,t1,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al1,t1,b1,b11,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al2 = palp[j+10];
                             b2 = pbeta[j+10];
                             b12= pbeta1[j+10];
                             t2 = ptht[j+10];
                             expj_f6358_zmm16(k0,b2,a,h,t2,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al2,t2,b2,b12,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al3 = palp[j+11];
                             b3 = pbeta[j+11];
                             b13= pbeta1[j+11];
                             t3 = ptht[j+11];
                             expj_f6358_zmm16(k0,b3,a,h,t3,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al3,t3,b3,b13,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al4 = palp[j+12];
                             b4 = pbeta[j+12];
                             b14= pbeta1[j+12];
                             t4 = ptht[j+12];
                             expj_f6358_zmm16(k0,b4,a,h,t4,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al4,t4,b4,b14,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al5 = palp[j+13];
                             b5 = pbeta[j+13];
                             b15= pbeta1[j+13];
                             t5 = ptht[j+13];
                             expj_f6358_zmm16(k0,b5,a,h,t5,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al5,t5,b5,b15,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al6 = palp[j+14];
                             b6 = pbeta[j+14];
                             b16= pbeta1[j+14];
                             t6 = ptht[j+14];
                             expj_f6358_zmm16(k0,b6,a,h,t6,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al6,t6,b6,b16,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             al7 = palp[j+15];
                             b7 = pbeta[j+15];
                             b17= pbeta1[j+15];
                             t7 = ptht[j+15];
                             expj_f6358_zmm16(k0,b7,a,h,t7,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al7,t7,b7,b17,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                         }
                         cabs = cabs_zmm16r4(accr,acci);
                         rcs  = _mm512_reduce_add_ps(cabs);
                         return (rcs);
                 }



                   /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- multiple terms, unrolled 8x.
                    */


                
                   float rcs_f6356_nterm_u8x_zmm16r4(    const __m512 * __restrict __ATTR_ALIGN__(64) palp,
                                                         const __m512 h,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                         const __m512 a,
                                                         const __m512 k0,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) ptht,
                                                         const int32_t n,
                                                         const bool ver) {

                       

                         if(__builtin_expect(n<=0,0)) { return _mm512_setzero_ps();}
                                                  
                         __m512 cer,cei,rcs6357,t0r,t0i,cabs;
                         float rcs = 0.0f;
                        // register __m512 al0,al1,al2,al3,al4,al5,al6,al7
                        // register __m512 b0,b1,b2,b3,b4,b,b6,b7;
                        // register __m512 b10,b11,b12,b13,b14,b1,b16,b17;
                        // register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                        // register __m512 accr,acci;
                         int32_t j,m,m1; 
                         accr = _mm512_setzero_ps();
                         acci = accr;
                         m = n%8;
                         if(m != 0) {
                            for(j = 0; j != m; ++j) {
                                register __m512 al = palp[j];
                                register __m512 b = pbeta[j];
                                register __m512 b1= pbeta1[j];
                                register __m512 t = ptht[j];
                                expj_f6358_zmm16(k0,b,a,h,t,&cer,&cei);
                                rcs6357 = rcs_f6357_zmm16r4(al,t,b,b1,
                                                         a,k0,ver);
                                t0r     = _mm512_mul_ps(cer,rcs6357);
                                accr    = _mm512_add_ps(accr,t0r);
                                t0i     = _mm512_mul_ps(cei,rcs6357);
                                acci    = _mm512_add_ps(acci,t0i);
                            }
                             if(n<8) {
                                cabs = cabs_zmm16r4(accr,acci);
                                rcs  = _mm512_reduce_add_ps(cabs);
                                return (rcs);
                             }
                         }
                         m1 = m+1;
                         for(j = m1; j != n; j += 8) {
                             register __m512 al0 = palp[j+0];
                             register __m512 b0 = pbeta[j+0];
                             register __m512 b10= pbeta1[j+0];
                             register __m512 t0 = ptht[j+0];
                             expj_f6358_zmm16(k0,b0,a,h,t0,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al0,t0,b0,b10,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al1 = palp[j+1];
                             register __m512 b1 = pbeta[j+1];
                             register __m512 b11= pbeta1[j+1];
                             register __m512 t1 = ptht[j+1];
                             expj_f6358_zmm16(k0,b1,a,h,t1,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al1,t1,b1,b11,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al2 = palp[j+2];
                             register __m512 b2 = pbeta[j+2];
                             register __m512 b12= pbeta1[j+2];
                             register __m512 t2 = ptht[j+2];
                             expj_f6358_zmm16(k0,b2,a,h,t2,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al2,t2,b2,b12,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al3 = palp[j+3];
                             register __m512 b3 = pbeta[j+3];
                             register __m512 b13= pbeta1[j+3];
                             register __m512 t3 = ptht[j+3];
                             expj_f6358_zmm16(k0,b3,a,h,t3,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al3,t3,b3,b13,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al4 = palp[j+4];
                             register __m512 b4 = pbeta[j+4];
                             register __m512 b14= pbeta1[j+4];
                             register __m512 t4 = ptht[j+4];
                             expj_f6358_zmm16(k0,b4,a,h,t4,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al4,t4,b4,b14,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al5 = palp[j+5];
                             register __m512 b5 = pbeta[j+5];
                             register __m512 b15= pbeta1[j+5];
                             register __m512 t5 = ptht[j+5];
                             expj_f6358_zmm16(k0,b5,a,h,t5,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al5,t5,b5,b15,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al6 = palp[j+6];
                             register __m512 b6 = pbeta[j+6];
                             register __m512 b16= pbeta1[j+6];
                             register __m512 t6 = ptht[j+6];
                             expj_f6358_zmm16(k0,b6,a,h,t6,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al6,t6,b6,b16,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al7 = palp[j+7];
                             register __m512 b7 = pbeta[j+7];
                             register __m512 b17= pbeta1[j+7];
                             register __m512 t7 = ptht[j+7];
                             expj_f6358_zmm16(k0,b7,a,h,t7,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al7,t7,b7,b17,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                         }
                         cabs = cabs_zmm16r4(accr,acci);
                         rcs  = _mm512_reduce_add_ps(cabs);
                         return (rcs);
                 }


              

                      /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- multiple terms, unrolled 4x.
                    */


                
                   float rcs_f6356_nterm_u4x_zmm16r4(    const __m512 * __restrict __ATTR_ALIGN__(64) palp,
                                                         const __m512 h,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                         const __m512 a,
                                                         const __m512 k0,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) ptht,
                                                         const int32_t n,
                                                         const bool ver) {

                       

                         if(__builtin_expect(n<=0,0)) { return _mm512_setzero_ps();}
                                                  
                         __m512 cer,cei,rcs6357,t0r,t0i,cabs;
                         float rcs = 0.0f;
                        // register __m512 al0,al1,al2,al3,al4,al5,al6,al7
                        // register __m512 b0,b1,b2,b3,b4,b,b6,b7;
                        // register __m512 b10,b11,b12,b13,b14,b1,b16,b17;
                        // register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                        // register __m512 accr,acci;
                         int32_t j,m,m1; 
                         accr = _mm512_setzero_ps();
                         acci = accr;
                         m = n%4;
                         if(m != 0) {
                            for(j = 0; j != m; ++j) {
                                register __m512 al = palp[j];
                                register __m512 b = pbeta[j];
                                register __m512 b1= pbeta1[j];
                                register __m512 t = ptht[j];
                                expj_f6358_zmm16(k0,b,a,h,t,&cer,&cei);
                                rcs6357 = rcs_f6357_zmm16r4(al,t,b,b1,
                                                         a,k0,ver);
                                t0r     = _mm512_mul_ps(cer,rcs6357);
                                accr    = _mm512_add_ps(accr,t0r);
                                t0i     = _mm512_mul_ps(cei,rcs6357);
                                acci    = _mm512_add_ps(acci,t0i);
                            }
                             if(n<4) {
                                cabs = cabs_zmm16r4(accr,acci);
                                rcs  = _mm512_reduce_add_ps(cabs);
                                return (rcs);
                             }
                         }
                         m1 = m+1;
                         for(j = m1; j != n; j += 4) {
                             register __m512 al0 = palp[j+0];
                             register __m512 b0 = pbeta[j+0];
                             register __m512 b10= pbeta1[j+0];
                             register __m512 t0 = ptht[j+0];
                             expj_f6358_zmm16(k0,b0,a,h,t0,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al0,t0,b0,b10,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al1 = palp[j+1];
                             register __m512 b1 = pbeta[j+1];
                             register __m512 b11= pbeta1[j+1];
                             register __m512 t1 = ptht[j+1];
                             expj_f6358_zmm16(k0,b1,a,h,t1,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al1,t1,b1,b11,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al2 = palp[j+2];
                             register __m512 b2 = pbeta[j+2];
                             register __m512 b12= pbeta1[j+2];
                             register __m512 t2 = ptht[j+2];
                             expj_f6358_zmm16(k0,b2,a,h,t2,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al2,t2,b2,b12,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al3 = palp[j+3];
                             register __m512 b3 = pbeta[j+3];
                             register __m512 b13= pbeta1[j+3];
                             register __m512 t3 = ptht[j+3];
                             expj_f6358_zmm16(k0,b3,a,h,t3,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al3,t3,b3,b13,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                           
                         }
                         cabs = cabs_zmm16r4(accr,acci);
                         rcs  = _mm512_reduce_add_ps(cabs);
                         return (rcs);
                 }


                     /*
                         Geometrical Theory of Diffraction
                         RCS by amplitude series summing convergence.
                         Formula 6.3-56 -- multiple terms, unrolled 2x.
                    */


                 
                   float rcs_f6356_nterm_u2x_zmm16r4(    const __m512 * __restrict __ATTR_ALIGN__(64) palp,
                                                         const __m512 h,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) pbeta1,
                                                         const __m512 a,
                                                         const __m512 k0,
                                                         const __m512 * __restrict __ATTR_ALIGN__(64) ptht,
                                                         const int32_t n,
                                                         const bool ver) {

                       

                         if(__builtin_expect(n<=0,0)) { return _mm512_setzero_ps();}
                                                  
                         __m512 cer,cei,rcs6357,t0r,t0i,cabs;
                         float rcs = 0.0f;
                        // register __m512 al0,al1,al2,al3,al4,al5,al6,al7
                        // register __m512 b0,b1,b2,b3,b4,b,b6,b7;
                        // register __m512 b10,b11,b12,b13,b14,b1,b16,b17;
                        // register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                        // register __m512 accr,acci;
                         int32_t j,m,m1; 
                         accr = _mm512_setzero_ps();
                         acci = accr;
                         m = n%2;
                         if(m != 0) {
                            for(j = 0; j != m; ++j) {
                                register __m512 al = palp[j];
                                register __m512 b = pbeta[j];
                                register __m512 b1= pbeta1[j];
                                register __m512 t = ptht[j];
                                expj_f6358_zmm16(k0,b,a,h,t,&cer,&cei);
                                rcs6357 = rcs_f6357_zmm16r4(al,t,b,b1,
                                                         a,k0,ver);
                                t0r     = _mm512_mul_ps(cer,rcs6357);
                                accr    = _mm512_add_ps(accr,t0r);
                                t0i     = _mm512_mul_ps(cei,rcs6357);
                                acci    = _mm512_add_ps(acci,t0i);
                            }
                             if(n<2) {
                                cabs = cabs_zmm16r4(accr,acci);
                                rcs  = _mm512_reduce_add_ps(cabs);
                                return (rcs);
                             }
                         }
                         m1 = m+1;
                         for(j = m1; j != n; j += 2) {
                             register __m512 al0 = palp[j+0];
                             register __m512 b0 = pbeta[j+0];
                             register __m512 b10= pbeta1[j+0];
                             register __m512 t0 = ptht[j+0];
                             expj_f6358_zmm16(k0,b0,a,h,t0,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al0,t0,b0,b10,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                             register __m512 al1 = palp[j+1];
                             register __m512 b1 = pbeta[j+1];
                             register __m512 b11= pbeta1[j+1];
                             register __m512 t1 = ptht[j+1];
                             expj_f6358_zmm16(k0,b1,a,h,t1,&cer,&cei);
                             rcs6357 = rcs_f6357_zmm16r4(al1,t1,b1,b11,
                                                         a,k0,ver);
                             t0r     = _mm512_mul_ps(cer,rcs6357);
                             accr    = _mm512_add_ps(accr,t0r);
                             t0i     = _mm512_mul_ps(cei,rcs6357);
                             acci    = _mm512_add_ps(acci,t0i);
                                                      
                         }
                         cabs = cabs_zmm16r4(accr,acci);
                         rcs  = _mm512_reduce_add_ps(cabs);
                         return (rcs);
                 }


                   /*
                          Large loop k0a >> 1 , for theta = 0 degree.
                          Formula 6.4-10
                      */


                
                   __m512 rcs_f6410_zmm16r4(const __m512 k0,
                                            const __m512 a,
                                            const __m512 b) {

                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _2pi= _mm512_set1_ps(9.869604401089358618834490999876f);
                          const __m512 _2  = _mm512_set1_ps(2.0f);
                          register __m512 num,k0a,k0a2,k0b,arg,larg,den,rcs,x0;
                          k0a = _mm512_mul_ps(k0,a);
                          k0b = _mm512_mul_ps(k0,b);
                          k0a2= _mm512_mul_ps(k0a,k0a);
                          arg = _mm512_div_ps(_2,k0b);
                          num = _mm512_mul_ps(pi,k0a2);
                          larg= xlogf(arg);
                          x0  = _mm512_add_ps(larg,larg);
                          den = _mm512_fmadd_ps(x0,x0,pi2);
                          rcs = _mm512_div_ps(num,den);
                          return (rcs);
                   }


                
                   __m512 rcs_f6410_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                            const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb) {

                          register __m512 k0 = _mm512_load_ps(&pk0[0]);
                          register __m512 a  = _mm512_load_ps(&pa[0]);
                          register __m512 b  = _mm512_load_ps(&pb[0]);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _2pi= _mm512_set1_ps(9.869604401089358618834490999876f);
                          const __m512 _2  = _mm512_set1_ps(2.0f);
                          register __m512 num,k0a,k0a2,k0b,arg,larg,den,rcs,x0;
                          k0a = _mm512_mul_ps(k0,a);
                          k0b = _mm512_mul_ps(k0,b);
                          k0a2= _mm512_mul_ps(k0a,k0a);
                          arg = _mm512_div_ps(_2,k0b);
                          num = _mm512_mul_ps(pi,k0a2);
                          larg= xlogf(arg);
                          x0  = _mm512_add_ps(larg,larg);
                          den = _mm512_fmadd_ps(x0,x0,pi2);
                          rcs = _mm512_div_ps(num,den);
                          return (rcs);
                   }


                 
                   __m512 rcs_f6410_zmm16r4_u(const float * __restrict  pk0,
                                            const float * __restrict  pa,
                                            const float * __restrict  pb) {

                          register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                          register __m512 a  = _mm512_loadu_ps(&pa[0]);
                          register __m512 b  = _mm512_loadu_ps(&pb[0]);
                          const __m512 pi  = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _2pi= _mm512_set1_ps(9.869604401089358618834490999876f);
                          const __m512 _2  = _mm512_set1_ps(2.0f);
                          register __m512 num,k0a,k0a2,k0b,arg,larg,den,rcs,x0;
                          k0a = _mm512_mul_ps(k0,a);
                          k0b = _mm512_mul_ps(k0,b);
                          k0a2= _mm512_mul_ps(k0a,k0a);
                          arg = _mm512_div_ps(_2,k0b);
                          num = _mm512_mul_ps(pi,k0a2);
                          larg= xlogf(arg);
                          x0  = _mm512_add_ps(larg,larg);
                          den = _mm512_fmadd_ps(x0,x0,pi2);
                          rcs = _mm512_div_ps(num,den);
                          return (rcs);
                   }


                     /*
                         THe far-zone amplitude for TE-case.
                         For small loop k0a<<1
                         Formula 6.4-11
                      */

                       
                
                   void Uv_f6411_zmm16r4(const __m512 a,
                                         const __m512 k0,
                                         const __m512 b,
                                         const __m512 tht,
                                         __m512 *  __restrict Uvr,
                                         __m512 *  __restrict Uvi) {

                        const __m512 pis = _mm512_set1_ps(9.869604401089358618834490999876f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _8  = _mm512_set1_ps(8.0f);
                        const __m512 sme0= _mm512_set1_ps(376.991118430775188623669955550061f);
                        register __m512 ir,ii,a2,k0a,sint,num,x0;
                        register __m512 arg,larg,den;
                        ir   = _mm512_setzero_ps();
                        a2   = _mm512_mul_ps(a,a);
                        sint = xsinf(tht);
                        k0a  = _mm512_mul_ps(a2,_mm512_mul_ps(k0,a));
                        arg  = _mm512_mul_ps(_8,_mm512_div_ps(a,b));
                        x0   = _mm512_fmadd_ps(sint,sint,_2);
                        larg = xlogf(arg);
                        num  = _mm512_mul_ps(pis,_mm512_mul_ps(k0a,x0));
                        den  = _mm512_mul_ps(sme0,_mm512_sub_ps(larg,_2));
                        ii   = num;
                        *Uvr = ir;
                        *Uvi = _mm512_div_ps(ii,den); 
                 }


               
                   void Uv_f6411_u16x_zmm16r4(const __m512 a,
                                              const __m512 k0,
                                              const __m512 b,
                                              const __m512 * __restrict __ATTR_ALIGN__(64) tht,
                                              __m512 * __restrict __ATTR_ALIGN__(64) Uvr,
                                              __m512 * __restrict __ATTR_ALIGN__(64) Uvi,
                                              const int32_t n) {

                        if(__builtin_expect(n<=0,0)) { return;}
                        register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                        register __m512 t8,t9,t10,t11,t12,t13,t14,t15;
                        register __m512 resr,resi;
                        int32_t j,m1,m;
                        m = n%16;

                        if(m != 0) {
                           for(j = 0; j != m; ++j) {
                               t0 = tht[j];
                               Uv_f6411_zmm16r4(a,k0,b,t0,&resr,&resi);
                               _mm512_store_ps(&Uvr[j],resr);
                               _mm512_store_ps(&Uvi[j],resi);
                           }
                           if(n<16) { return;}
                        }

                        m1 = m+1;
                        for(j = m1; j != n; j += 16) {
                             t0 = tht[j+0];
                             Uv_f6411_zmm16r4(a,k0,b,t0,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+0],resr);
                             _mm512_store_ps(&Uvi[j+0],resi);
                             t1 = tht[j+1];
                             Uv_f6411_zmm16r4(a,k0,b,t1,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+1],resr);
                             _mm512_store_ps(&Uvi[j+1],resi);
                             t2 = tht[j+2];
                             Uv_f6411_zmm16r4(a,k0,b,t2,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+2],resr);
                             _mm512_store_ps(&Uvi[j+2],resi);
                             t3 = tht[j+3];
                             Uv_f6411_zmm16r4(a,k0,b,t3,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+3],resr);
                             _mm512_store_ps(&Uvi[j+3],resi);
                             t4 = tht[j+4];
                             Uv_f6411_zmm16r4(a,k0,b,t4,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+4],resr);
                             _mm512_store_ps(&Uvi[j+4],resi);
                             t5 = tht[j+5];
                             Uv_f6411_zmm16r4(a,k0,b,t5,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+5],resr);
                             _mm512_store_ps(&Uvi[j+5],resi);
                             t6 = tht[j+6];
                             Uv_f6411_zmm16r4(a,k0,b,t6,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+6],resr);
                             _mm512_store_ps(&Uvi[j+6],resi);
                             t7 = tht[j+7];
                             Uv_f6411_zmm16r4(a,k0,b,t7,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+7],resr);
                             _mm512_store_ps(&Uvi[j+7],resi);
                             t8 = tht[j+8];
                             Uv_f6411_zmm16r4(a,k0,b,t8,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+8],resr);
                             _mm512_store_ps(&Uvi[j+8],resi);
                             t9 = tht[j+9];
                             Uv_f6411_zmm16r4(a,k0,b,t9,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+9],resr);
                             _mm512_store_ps(&Uvi[j+9],resi);
                             t10 = tht[j+10];
                             Uv_f6411_zmm16r4(a,k0,b,t10,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+10],resr);
                             _mm512_store_ps(&Uvi[j+10],resi);
                             t11 = tht[j+11];
                             Uv_f6411_zmm16r4(a,k0,b,t11,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+11],resr);
                             _mm512_store_ps(&Uvi[j+11],resi);
                             t12 = tht[j+12];
                             Uv_f6411_zmm16r4(a,k0,b,t12,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+12],resr);
                             _mm512_store_ps(&Uvi[j+12],resi); 
                             t13 = tht[j+13];
                             Uv_f6411_zmm16r4(a,k0,b,t13,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+13],resr);
                             _mm512_store_ps(&Uvi[j+13],resi);
                             t14 = tht[j+14];
                             Uv_f6411_zmm16r4(a,k0,b,t14,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+14],resr);
                             _mm512_store_ps(&Uvi[j+14],resi);
                             t15 = tht[j+15];
                             Uv_f6411_zmm16r4(a,k0,b,t15,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+15],resr);
                             _mm512_store_ps(&Uvi[j+15],resi);
                        }
                 }


                  
                   void Uv_f6411_u8x_zmm16r4( const __m512 a,
                                              const __m512 k0,
                                              const __m512 b,
                                              const __m512 * __restrict __ATTR_ALIGN__(64) tht,
                                              __m512 * __restrict __ATTR_ALIGN__(64) Uvr,
                                              __m512 * __restrict __ATTR_ALIGN__(64) Uvi,
                                              const int32_t n) {

                        if(__builtin_expect(n<=0,0)) { return;}
                        register __m512 t0,t1,t2,t3,t4,t5,t6,t7;
                        register __m512 resr,resi;
                        int32_t j,m1,m;
                        m = n%8;

                        if(m != 0) {
                           for(j = 0; j != m; ++j) {
                               t0 = tht[j];
                               Uv_f6411_zmm16r4(a,k0,b,t0,&resr,&resi);
                               _mm512_store_ps(&Uvr[j],resr);
                               _mm512_store_ps(&Uvi[j],resi);
                           }
                           if(n<8) { return;}
                        }

                        m1 = m+1;
                        for(j = m1; j != n; j += 8) {
                             t0 = tht[j+0];
                             Uv_f6411_zmm16r4(a,k0,b,t0,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+0],resr);
                             _mm512_store_ps(&Uvi[j+0],resi);
                             t1 = tht[j+1];
                             Uv_f6411_zmm16r4(a,k0,b,t1,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+1],resr);
                             _mm512_store_ps(&Uvi[j+1],resi);
                             t2 = tht[j+2];
                             Uv_f6411_zmm16r4(a,k0,b,t2,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+2],resr);
                             _mm512_store_ps(&Uvi[j+2],resi);
                             t3 = tht[j+3];
                             Uv_f6411_zmm16r4(a,k0,b,t3,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+3],resr);
                             _mm512_store_ps(&Uvi[j+3],resi);
                             t4 = tht[j+4];
                             Uv_f6411_zmm16r4(a,k0,b,t4,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+4],resr);
                             _mm512_store_ps(&Uvi[j+4],resi);
                             t5 = tht[j+5];
                             Uv_f6411_zmm16r4(a,k0,b,t5,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+5],resr);
                             _mm512_store_ps(&Uvi[j+5],resi);
                             t6 = tht[j+6];
                             Uv_f6411_zmm16r4(a,k0,b,t6,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+6],resr);
                             _mm512_store_ps(&Uvi[j+6],resi);
                             t7 = tht[j+7];
                             Uv_f6411_zmm16r4(a,k0,b,t7,&resr,&resi);
                             _mm512_store_ps(&Uvr[j+7],resr);
                             _mm512_store_ps(&Uvi[j+7],resi);
                      }
                 }



                 
                   void Uv_f6411_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                           const float * __restrict __ATTR_ALIGN__(64) pk0,
                                           const float * __restrict __ATTR_ALIGN__(64) pb,
                                           const float * __restrict __ATTR_ALIGN__(64) ptht,
                                           float * __restrict __ATTR_ALIGN__(64) Uvr,
                                           float * __restrict __ATTR_ALIGN__(64) Uvi) {
  
                        register __m512 a   = _mm512_load_ps(&pa[0]);
                        register __m512 k0  = _mm512_load_ps(&pk0[0]);
                        register __m512 b   = _mm512_load_ps(&pb[0]);
                        register __m512 tht = _mm512_load_ps(&ptht[0]);
                        
                        const __m512 pis = _mm512_set1_ps(9.869604401089358618834490999876f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _8  = _mm512_set1_ps(8.0f);
                        const __m512 sme0= _mm512_set1_ps(376.991118430775188623669955550061f);
                        register __m512 ir,ii,a2,k0a,sint,num,x0;
                        register __m512 arg,larg,den;
                        ir   = _mm512_setzero_ps();
                        a2   = _mm512_mul_ps(a,a);
                        sint = xsinf(tht);
                        k0a  = _mm512_mul_ps(a2,_mm512_mul_ps(k0,a));
                        arg  = _mm512_mul_ps(_8,_mm512_div_ps(a,b));
                        x0   = _mm512_fmadd_ps(sint,sint,_2);
                        larg = xlogf(arg);
                        num  = _mm512_mul_ps(pis,_mm512_mul_ps(k0a,x0));
                        den  = _mm512_mul_ps(sme0,_mm512_sub_ps(larg,_2));
                        ii   = num;
                        _mm512_store_ps(&Uvr[0] ,ir);
                        _mm512_store_ps(&Uvi[0] ,_mm512_div_ps(ii,den)); 
                 }


                 
                   void Uv_f6411_zmm16r4_u(const float * __restrict  pa,
                                           const float * __restrict  pk0,
                                           const float * __restrict  pb,
                                           const float * __restrict  ptht,
                                           float * __restrict  Uvr,
                                           float * __restrict  Uvi) {
  
                        register __m512 a   = _mm512_loadu_ps(&pa[0]);
                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                        register __m512 b   = _mm512_loadu_ps(&pb[0]);
                        register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                        
                        const __m512 pis = _mm512_set1_ps(9.869604401089358618834490999876f);
                        const __m512 _2  = _mm512_set1_ps(2.0f);
                        const __m512 _8  = _mm512_set1_ps(8.0f);
                        const __m512 sme0= _mm512_set1_ps(376.991118430775188623669955550061f);
                        register __m512 ir,ii,a2,k0a,sint,num,x0;
                        register __m512 arg,larg,den;
                        ir   = _mm512_setzero_ps();
                        a2   = _mm512_mul_ps(a,a);
                        sint = xsinf(tht);
                        k0a  = _mm512_mul_ps(a2,_mm512_mul_ps(k0,a));
                        arg  = _mm512_mul_ps(_8,_mm512_div_ps(a,b));
                        x0   = _mm512_fmadd_ps(sint,sint,_2);
                        larg = xlogf(arg);
                        num  = _mm512_mul_ps(pis,_mm512_mul_ps(k0a,x0));
                        den  = _mm512_mul_ps(sme0,_mm512_sub_ps(larg,_2));
                        ii   = num;
                        _mm512_storeu_ps(&Uvr[0] ,ir);
                        _mm512_storeu_ps(&Uvi[0] ,_mm512_div_ps(ii,den)); 
                 }


                  
                   __m512 rcs_f6412_zmm16(const __m512 a,
                                          const __m512 b,
                                          const __m512 k0,
                                          const __m512 tht) {

                        const __m512 pi34 = _mm512_set1_ps(7.751569170074955043869078766775f);
                        const __m512 _2   = _mm512_set1_ps(2.0f);
                        const __m512 _8   = _mm512_set1_ps(8.0f);
                        register __m512 a2,k0a4,x0,arg,larg;
                        register __m512 rcs,slarg,x1,sint;
                        a2   = _mm512_mul_ps(a,a);
                        arg  = _mm512_div_ps(_8,_mm512_mul_ps(a,a));
                        sint = _mm512_add_ps(_2,xsinf(tht));
                        x0   = _mm512_mul_ps(k0a,k0a);
                        larg = _mm512_sub_ps(xlogf(arg),_2);
                        k0a4 = _mm512_mul_ps(x0,x0);
                        x1   = _mm512_sqrt_ps(larg);
                        x0   = _mm512_mul_ps(pi34,_mm512_mul_ps(a2,k0a4));
                        slarg= _mm512_rcp14_ps(x1);
                        a2   = _mm512_mul_ps(sint,sint);
                        rcs  = _mm512_mul_ps(x0,_mm512_mul_ps(a2,slarg));
                        return (rcs);
                }


                 
                   __m512 rcs_f6412_zmm16_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0,
                                            const float * __restrict __ATTR_ALIGN__(64) ptht) {

                        register __m512 a  = _mm512_load_ps(&pa[0]);
                        register __m512 b  = _mm512_load_ps(&pb[0]);
                        register __m512 k0 = _mm512_load_ps(&pk0[0]);
                        register __m512 tht= _mm512_load_ps(&ptht[0]);
                        const __m512 pi34 = _mm512_set1_ps(7.751569170074955043869078766775f);
                        const __m512 _2   = _mm512_set1_ps(2.0f);
                        const __m512 _8   = _mm512_set1_ps(8.0f);
                        register __m512 a2,k0a4,x0,arg,larg;
                        register __m512 rcs,slarg,x1,sint;
                        a2   = _mm512_mul_ps(a,a);
                        arg  = _mm512_div_ps(_8,_mm512_mul_ps(a,a));
                        sint = _mm512_add_ps(_2,xsinf(tht));
                        x0   = _mm512_mul_ps(k0a,k0a);
                        larg = _mm512_sub_ps(xlogf(arg),_2);
                        k0a4 = _mm512_mul_ps(x0,x0);
                        x1   = _mm512_sqrt_ps(larg);
                        x0   = _mm512_mul_ps(pi34,_mm512_mul_ps(a2,k0a4));
                        slarg= _mm512_rcp14_ps(x1);
                        a2   = _mm512_mul_ps(sint,sint);
                        rcs  = _mm512_mul_ps(x0,_mm512_mul_ps(a2,slarg));
                        return (rcs);
                }


                 
                   __m512 rcs_f6412_zmm16_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pk0,
                                            const float * __restrict  ptht) {

                        register __m512 a  = _mm512_loadu_ps(&pa[0]);
                        register __m512 b  = _mm512_loadu_ps(&pb[0]);
                        register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                        register __m512 tht= _mm512_loadu_ps(&ptht[0]);
                        const __m512 pi34 = _mm512_set1_ps(7.751569170074955043869078766775f);
                        const __m512 _2   = _mm512_set1_ps(2.0f);
                        const __m512 _8   = _mm512_set1_ps(8.0f);
                        register __m512 a2,k0a4,x0,arg,larg;
                        register __m512 rcs,slarg,x1,sint;
                        a2   = _mm512_mul_ps(a,a);
                        arg  = _mm512_div_ps(_8,_mm512_mul_ps(a,a));
                        sint = _mm512_add_ps(_2,xsinf(tht));
                        x0   = _mm512_mul_ps(k0a,k0a);
                        larg = _mm512_sub_ps(xlogf(arg),_2);
                        k0a4 = _mm512_mul_ps(x0,x0);
                        x1   = _mm512_sqrt_ps(larg);
                        x0   = _mm512_mul_ps(pi34,_mm512_mul_ps(a2,k0a4));
                        slarg= _mm512_rcp14_ps(x1);
                        a2   = _mm512_mul_ps(sint,sint);
                        rcs  = _mm512_mul_ps(x0,_mm512_mul_ps(a2,slarg));
                        return (rcs);
                }


                 
                                          

                    


                    





                  


       


















