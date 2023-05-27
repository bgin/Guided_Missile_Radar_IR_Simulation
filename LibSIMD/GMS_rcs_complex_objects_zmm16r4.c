



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




#include "GMS_rcs_complex_objects_zmm16r4.h"
#include "GMS_sleefsimdsp.h"
#include "GMS_complex_zmm16r4.h"
#include "GMS_simd_utils.h"





         
         
             
         
              
              /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter diffraction coefficient 'D'.
                    Formula: 8.1-21
              */     
              
              
                  
                   void coef_D12_f8121_zmm16r4(const __m512 gam,
                                             const __m512 phi,
                                             const __m512 k0,
                                             __m512 * __restrict D1r,
                                             __m512 * __restrict D1i,
                                            __m512 * __restrict D2r,
                                            __m512 * __restrict D2i) {
                                            
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);
                        register __m512 invn,x0,x1,ear,eai,cer,cei,phi2,sqr,sinp,cos1,cos2,trm1,trm2;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328); 
                        ear  = _mm512_setzero_ps();
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        x1   = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(k0,
                                                C6283185307179586476925286766559));
                        sinp = xsinf(x1);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        cos1 = xcosf(x1);
                        x0   = _mm512_mul_ps(invn,phi2);
                        cos2 = xcosf(x0);
                        cer  = _mm512_mul_ps(cer,sinp);
                        trm1 = _mm512_rcp14_ps(_mm512_sub_ps(cos1),C10);
                        cei  = _mm512_mul_ps(cei,sinp);
                        trm2 = _mm512_rcp14_ps(_mm512_sub_ps(cos1,cos2));
                        sqr  = _mm512_mul_ps(invn,sqr);
                        ear  = _mm512_mul_ps(cer,sqr);
                        eai  = _mm512_mul_ps(cei,sqr);
                        x0   = _mm512_sub_ps(trm1,trm2);
                        *D1r = _mm512_mul_ps(ear,x0);
                        *D1i = _mm512_mul_ps(eai,x0);
                        x1   = _mm512_add_ps(trm1,trm2);
                        *D2r = _mm512_mul_ps(ear,x1);
                        *D2i = _mm512_mul_ps(eai,x1);
                }
                
                
                
                 
                   void coef_D12_f8121_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam,
                                               const float * __restrict __ATTR_ALIGN__(64) pphi,
                                               const float * __restrict __ATTR_ALIGN__(64) pk0,
                                               float * __restrict __ATTR_ALIGN__(64) D1r,
                                               float * __restrict __ATTR_ALIGN__(64) D1i,
                                               float * __restrict __ATTR_ALIGN__(64) D2r,
                                               float * __restrict __ATTR_ALIGN__(64) D2i) {
                                   
                        register __m512 gam = _mm512_load_ps(&pgam[0]);
                        register __m512 phi = _mm512_load_ps(&pphi[0]);  
                        register __m512 k0  = _mm512_load_ps(&pk0[0]);       
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);
                        register __m512 invn,x0,x1,ear,eai,cer,cei,phi2,sqr,sinp,cos1,cos2,trm1,trm2;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328); 
                        ear  = _mm512_setzero_ps();
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        x1   = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(k0,
                                                C6283185307179586476925286766559));
                        sinp = xsinf(x1);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        cos1 = xcosf(x1);
                        x0   = _mm512_mul_ps(invn,phi2);
                        cos2 = xcosf(x0);
                        cer  = _mm512_mul_ps(cer,sinp);
                        trm1 = _mm512_rcp14_ps(_mm512_sub_ps(cos1),C10);
                        cei  = _mm512_mul_ps(cei,sinp);
                        trm2 = _mm512_rcp14_ps(_mm512_sub_ps(cos1,cos2));
                        sqr  = _mm512_mul_ps(invn,sqr);
                        ear  = _mm512_mul_ps(cer,sqr);
                        eai  = _mm512_mul_ps(cei,sqr);
                        x0   = _mm512_sub_ps(trm1,trm2);
                        _mm512_store_ps(&D1r[0] ,_mm512_mul_ps(ear,x0));
                        _mm512_store_ps(&D1i[0] ,_mm512_mul_ps(eai,x0));
                        x1   = _mm512_add_ps(trm1,trm2);
                        _mm512_store_ps(&D2r[0] ,_mm512_mul_ps(ear,x1));
                        _mm512_store_ps(&D2i[0] ,_mm512_mul_ps(eai,x1));
                }
                
                
                
              
                   void coef_D12_f8121_zmm16r4_u(const float * __restrict  pgam,
                                               const float * __restrict  pphi,
                                               const float * __restrict  pk0,
                                               float * __restrict  D1r,
                                               float * __restrict  D1i,
                                               float * __restrict  D2r,
                                               float * __restrict  D2i) {
                                   
                        register __m512 gam = _mm512_loadu_ps(&pgam[0]);
                        register __m512 phi = _mm512_loadu_ps(&pphi[0]);  
                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);       
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);
                        register __m512 invn,x0,x1,ear,eai,cer,cei,phi2,sqr,sinp,cos1,cos2,trm1,trm2;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328); 
                        ear  = _mm512_setzero_ps();
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        x1   = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(k0,
                                                C6283185307179586476925286766559));
                        sinp = xsinf(x1);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        cos1 = xcosf(x1);
                        x0   = _mm512_mul_ps(invn,phi2);
                        cos2 = xcosf(x0);
                        cer  = _mm512_mul_ps(cer,sinp);
                        trm1 = _mm512_rcp14_ps(_mm512_sub_ps(cos1),C10);
                        cei  = _mm512_mul_ps(cei,sinp);
                        trm2 = _mm512_rcp14_ps(_mm512_sub_ps(cos1,cos2));
                        sqr  = _mm512_mul_ps(invn,sqr);
                        ear  = _mm512_mul_ps(cer,sqr);
                        eai  = _mm512_mul_ps(cei,sqr);
                        x0   = _mm512_sub_ps(trm1,trm2);
                        _mm512_storeu_ps(&D1r[0] ,_mm512_mul_ps(ear,x0));
                        _mm512_storeu_ps(&D1i[0] ,_mm512_mul_ps(eai,x0));
                        x1   = _mm512_add_ps(trm1,trm2);
                        _mm512_storeu_ps(&D2r[0] ,_mm512_mul_ps(ear,x1));
                        _mm512_storeu_ps(&D2i[0] ,_mm512_mul_ps(eai,x1));
                }
                
                
                /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter singly diffracted far-zone fields (E,H).
                    Formula: 8.1-19, 8.1-20
                
                */
                
               
                   void EsHs_f811920_zmm16r4(    const __m512 betai,
                                                 const __m512 betas,
                                                 const __m512 gam,
                                                 const __m512 phi,
                                                 const __m512 k0,
                                                 const __m512 r,
                                                 const __m512 rho,
                                                 const __m512 psi,
                                                 __m512 * __restrict Esr,
                                                 __m512 * __restrict Esi,
                                                 __m512 * __restrict Hsr,
                                                 __m512 * __restrict Hsi) {
                                                 
                       register __m512 ear,eai,cer,cei;
                       register __m512 D1r,D1i,D2r,D2i,x0,x1;
                       register __m512 rhos,cosb1,cosbs,sqrho,k0rp,invr;
                       k0rp  = _mm512_fmadd_ps(k0,r,psi);
                       coef_D12_f8121_zmm16r4(gam,phi,k0,&D1r,&D1i,&D2r,&D2i);
                       invr  = _mm512_rcp14_ps(r);
                       ear   = _mm512_setzero_ps();
                       cosbi = xcosf(betai);
                       eai   = k0rp;
                       cosbs = xcosf(betas);
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       cer   = _mm512_mul_ps(cer,invr);    
                       rhos  = _mm512_div_ps(rho,_mm512_add_ps(cosbi,cosbs));
                       cei   = _mm512_mul_ps(cei,invr);
                       sqrho = _mm512_sqrt_ps(rhos);
                       x0    = _mm512_mul_ps(sqrho,cer);
                       x1    = _mm512_mul_ps(sqrho,cei);
                       *Esr  = _mm512_mul_ps(D1r,x0);
                       *Hsr  = _mm512_mul_ps(D2r,x0);
                       *Esi  = _mm512_mul_ps(D1i,x1);
                       *Hsi  = _mm512_mul_ps(D2i,x1);                               
            }
            
            
                 
                   void EsHs_f811920_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) pbetai,
                                                 const float * __restrict __ATTR_ALIGN__(64) pbetas,
                                                 const float * __restrict __ATTR_ALIGN__(64) pgam,
                                                 const float * __restrict __ATTR_ALIGN__(64) pphi,
                                                 const float * __restrict __ATTR_ALIGN__(64) pk0,
                                                 const float * __restrict __ATTR_ALIGN__(64) pr,
                                                 const float * __restrict __ATTR_ALIGN__(64) prho,
                                                 const float * __restrict __ATTR_ALIGN__(64) ppsi,
                                                 float * __restrict __ATTR_ALIGN__(64) Esr,
                                                 float * __restrict __ATTR_ALIGN__(64) Esi,
                                                 float * __restrict __ATTR_ALIGN__(64) Hsr,
                                                 float * __restrict __ATTR_ALIGN__(64) Hsi) {
                              
                       register __m512 betai = _mm512_load_ps(&pbetai[0]);
                       register __m512 betas = _mm512_load_ps(&pbetas[0]); 
                       register __m512 gam   = _mm512_load_ps(&pgam[0]);   
                       register __m512 k0    = _mm512_load_ps(&pk0[0]); 
                       register __m512 r     = _mm512_load_ps(&pr[0]);
                       register __m512 rho   = _mm512_load_ps(&prho[0]); 
                       register __m512 psi   = _mm512_load_ps(&ppsi[0]);             
                       register __m512 ear,eai,cer,cei;
                       register __m512 D1r,D1i,D2r,D2i,x0,x1;
                       register __m512 rhos,cosb1,cosbs,sqrho,k0rp,invr;
                       k0rp  = _mm512_fmadd_ps(k0,r,psi);
                       coef_D12_f8121_zmm16r4(gam,phi,k0,&D1r,&D1i,&D2r,&D2i);
                       invr  = _mm512_rcp14_ps(r);
                       ear   = _mm512_setzero_ps();
                       cosbi = xcosf(betai);
                       eai   = k0rp;
                       cosbs = xcosf(betas);
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       cer   = _mm512_mul_ps(cer,invr);    
                       rhos  = _mm512_div_ps(rho,_mm512_add_ps(cosbi,cosbs));
                       cei   = _mm512_mul_ps(cei,invr);
                       sqrho = _mm512_sqrt_ps(rhos);
                       x0    = _mm512_mul_ps(sqrho,cer);
                       x1    = _mm512_mul_ps(sqrho,cei);
                       _mm512_store_ps(&Esr[0] ,_mm512_mul_ps(D1r,x0));
                       _mm512_store_ps(&Hsr[0] ,_mm512_mul_ps(D2r,x0));
                       _mm512_store_ps(&Esi[0] ,_mm512_mul_ps(D1i,x1));
                       _mm512_store_ps(&Hsi[0] ,_mm512_mul_ps(D2i,x1));                               
            }
            
            
                
                   void EsHs_f811920_zmm16r4_u(  const float * __restrict  pbetai,
                                                 const float * __restrict  pbetas,
                                                 const float * __restrict  pgam,
                                                 const float * __restrict  pphi,
                                                 const float * __restrict  pk0,
                                                 const float * __restrict  pr,
                                                 const float * __restrict  prho,
                                                 const float * __restrict ppsi,
                                                 float * __restrict  Esr,
                                                 float * __restrict  Esi,
                                                 float * __restrict  Hsr,
                                                 float * __restrict  Hsi) {
                              
                       register __m512 betai = _mm512_loadu_ps(&pbetai[0]);
                       register __m512 betas = _mm512_loadu_ps(&pbetas[0]); 
                       register __m512 gam   = _mm512_loadu_ps(&pgam[0]);   
                       register __m512 k0    = _mm512_loadu_ps(&pk0[0]); 
                       register __m512 r     = _mm512_loadu_ps(&pr[0]);
                       register __m512 rho   = _mm512_loadu_ps(&prho[0]); 
                       register __m512 psi   = _mm512_loadu_ps(&ppsi[0]);             
                       register __m512 ear,eai,cer,cei;
                       register __m512 D1r,D1i,D2r,D2i,x0,x1;
                       register __m512 rhos,cosb1,cosbs,sqrho,k0rp,invr;
                       k0rp  = _mm512_fmadd_ps(k0,r,psi);
                       coef_D12_f8121_zmm16r4(gam,phi,k0,&D1r,&D1i,&D2r,&D2i);
                       invr  = _mm512_rcp14_ps(r);
                       ear   = _mm512_setzero_ps();
                       cosbi = xcosf(betai);
                       eai   = k0rp;
                       cosbs = xcosf(betas);
                       cexp_zmm16r4(ear,eai,&cer,&cei);
                       cer   = _mm512_mul_ps(cer,invr);    
                       rhos  = _mm512_div_ps(rho,_mm512_add_ps(cosbi,cosbs));
                       cei   = _mm512_mul_ps(cei,invr);
                       sqrho = _mm512_sqrt_ps(rhos);
                       x0    = _mm512_mul_ps(sqrho,cer);
                       x1    = _mm512_mul_ps(sqrho,cei);
                       _mm512_storeu_ps(&Esr[0] ,_mm512_mul_ps(D1r,x0));
                       _mm512_storeu_ps(&Hsr[0] ,_mm512_mul_ps(D2r,x0));
                       _mm512_storeu_ps(&Esi[0] ,_mm512_mul_ps(D1i,x1));
                       _mm512_storeu_ps(&Hsi[0] ,_mm512_mul_ps(D2i,x1));                               
            }
            
            
            /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter diffraction coefficient 'D'.
                    Ray normal-incidence to one of edge faces.
                    Formula: 8.1-24
            */
            
                
                   void coef_D12_f8124_zmm16r4(const __m512 k0,
                                               const __m512 gam,
                                               __m512 * __restrict D1r,
                                               __m512 * __restrict D1i,
                                               __m512 * __restrict D2r,
                                               __m512 * __restrict D2i) {
                                               
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);  
                        register __m512 ear,eai,cer,cei,t0r,t0i;
                        register __m512 x0,invn,x1,sin1,cos1,sin2,cos2,x2,invn2,arg1,arg2;
                        ear  = _mm512_setzero_ps();
                        eai  = C078539816339744830961566084582; 
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);  
                        x1   = _mm512_mul_ps(k0,C6283185307179586476925286766559);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        invn = _mm512_rcp14_ps(x0);
                        cer  = negate_zmm16r4(cer);
                        invn2= _mm512_add_ps(invn,invn);      
                        cei  = negate_zmm16r4(cei);
                        arg1 = _mm512_mul_ps(C314159265358979323846264338328,invn2)
                        sin1 = xsinf(arg1);
                        arg2 = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        t0r  = _mm512_div_ps(cer,x1);
                        cos1 = xcosf(arg1);
                        x0   = _mm512_div_ps(cos1,sin1);
                        t0i  = _mm512_div_ps(cei,x1);   
                        sin2 = xsinf(arg2);
                        cos2 = xcosf(arg2);   
                        x1   = _mm512_div_ps(cos2,sin2);
                        ear  = _mm512_fmsub_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        eai  = _mm512_fmadd_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        cer  = _mm512_mul_ps(t0r,ear);
                        cei  = _mm512_mul_ps(t0i,eai);
                        *D1r = cer;
                        *D2r = cer;
                        *D1i = cei;
                        *D2i = cei;       
                }
                
                
                 
                   void coef_D12_f8124_zmm16r4_a(const  float * __restrict __ATTR_ALIGN__(64) pk0,
                                                 const  float * __restrict __ATTR_ALIGN__(64) pgam,
                                                 float * __restrict __ATTR_ALIGN__(64) D1r,
                                                 float * __restrict __ATTR_ALIGN__(64) D1i,
                                                 float * __restrict __ATTR_ALIGN__(64) D2r,
                                                 float * __restrict __ATTR_ALIGN__(64) D2i) {
                                    
                        register __m512 k0 = _mm512_load_ps(&pk0[0]);
                        register __m512 gam= _mm512_load_ps(&pgam[0]);           
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);  
                        register __m512 ear,eai,cer,cei,t0r,t0i;
                        register __m512 x0,invn,x1,sin1,cos1,sin2,cos2,x2,invn2,arg1,arg2;
                        ear  = _mm512_setzero_ps();
                        eai  = C078539816339744830961566084582; 
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);  
                        x1   = _mm512_mul_ps(k0,C6283185307179586476925286766559);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        invn = _mm512_rcp14_ps(x0);
                        cer  = negate_zmm16r4(cer);
                        invn2= _mm512_add_ps(invn,invn);      
                        cei  = negate_zmm16r4(cei);
                        arg1 = _mm512_mul_ps(C314159265358979323846264338328,invn2)
                        sin1 = xsinf(arg1);
                        arg2 = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        t0r  = _mm512_div_ps(cer,x1);
                        cos1 = xcosf(arg1);
                        x0   = _mm512_div_ps(cos1,sin1);
                        t0i  = _mm512_div_ps(cei,x1);   
                        sin2 = xsinf(arg2);
                        cos2 = xcosf(arg2);   
                        x1   = _mm512_div_ps(cos2,sin2);
                        ear  = _mm512_fmsub_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        eai  = _mm512_fmadd_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        cer  = _mm512_mul_ps(t0r,ear);
                        cei  = _mm512_mul_ps(t0i,eai);
                        _mm512_store_ps(&D1r[0] ,cer);
                        _mm512_store_ps(&D2r[0] ,cer);
                        _mm512_store_ps(&D1i[0] ,cei);
                        _mm512_store_ps(&D2i[0] ,cei);       
                }
                
                
                
                   void coef_D12_f8124_zmm16r4_u(const  float * __restrict  pk0,
                                                 const  float * __restrict pgam,
                                                 float * __restrict  D1r,
                                                 float * __restrict  D1i,
                                                 float * __restrict  D2r,
                                                 float * __restrict  D2i) {
                                    
                        register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                        register __m512 gam= _mm512_loadu_ps(&pgam[0]);           
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);
                        const __m512 C10                              = _mm512_set1_ps(1.0f);  
                        register __m512 ear,eai,cer,cei,t0r,t0i;
                        register __m512 x0,invn,x1,sin1,cos1,sin2,cos2,x2,invn2,arg1,arg2;
                        ear  = _mm512_setzero_ps();
                        eai  = C078539816339744830961566084582; 
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);  
                        x1   = _mm512_mul_ps(k0,C6283185307179586476925286766559);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        invn = _mm512_rcp14_ps(x0);
                        cer  = negate_zmm16r4(cer);
                        invn2= _mm512_add_ps(invn,invn);      
                        cei  = negate_zmm16r4(cei);
                        arg1 = _mm512_mul_ps(C314159265358979323846264338328,invn2)
                        sin1 = xsinf(arg1);
                        arg2 = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        t0r  = _mm512_div_ps(cer,x1);
                        cos1 = xcosf(arg1);
                        x0   = _mm512_div_ps(cos1,sin1);
                        t0i  = _mm512_div_ps(cei,x1);   
                        sin2 = xsinf(arg2);
                        cos2 = xcosf(arg2);   
                        x1   = _mm512_div_ps(cos2,sin2);
                        ear  = _mm512_fmsub_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        eai  = _mm512_fmadd_ps(invn,x0,_mm512_mul_ps(invn2,x1));
                        cer  = _mm512_mul_ps(t0r,ear);
                        cei  = _mm512_mul_ps(t0i,eai);
                        _mm512_storeu_ps(&D1r[0] ,cer);
                        _mm512_storeu_ps(&D2r[0] ,cer);
                        _mm512_storeu_ps(&D1i[0] ,cei);
                        _mm512_storeu_ps(&D2i[0] ,cei);       
                }
                
                
                /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter diffraction coefficient 'D'.
                    Backscatter direction axial caustic (for slightly diffracted rays).
                    Formula: 8.1-26
                */
                
                
                
                   void coef_Ddiff_f8126_zmm16r4(const __m512 gam,
                                             const __m512 phi,
                                             const __m512 k0,
                                             __m512 * __restrict Dr,
                                             __m512 * __restrict Di) {
                                             
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);  
                        const __m512 C20                              = 
                                                     _mm512_set1_ps(2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 invn,n,phi2,pin,spin,cpin,cphin,sqr,x0,x1;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_mul_ps(C6283185307179586476925286766559,k0);
                        ear  = _mm512_setzero_ps();
                        n    = _mm512_div_ps(gam,C314159265358979323846264338328);
                        eai  = C078539816339744830961566084582;
                        invn = _mm512_rcp14_ps(n); 
                        sqr  = _mm512_sqrt_ps(x0);
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        spin = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        cpin = xcosf(pin);
                        cei  = _mm512_div_ps(cei,sqr);
                        cphin= xcosf(_mm512_mul_ps(phi2,invn));
                        x0   = _mm512_mul_ps(_mm512_mul_ps(C20,invn),spin);
                        x1   = _mm512_sub_ps(cpin,cphin);
                        n    = _mm512_div_ps(x0,x1);
                        *Dr  = _mm512_mul_ps(cer,n);
                        *Di  = _mm512_mul_ps(cei,n);
                }
                
                
                 
                   void coef_Ddiff_f8126_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pgam,
                                               const float * __restrict __ATTR_ALIGN__(64) pphi,
                                               const float * __restrict __ATTR_ALIGN__(64) pk0,
                                               float * __restrict __ATTR_ALIGN__(64)  Dr,
                                               float * __restrict __ATTR_ALIGN__(64)  Di) {
                                    
                        register __m512 gam  = _mm512_load_ps(&pgam[0]);
                        register __m512 phi  = _mm512_load_ps(&pphi[0]);
                        register __m512 k0   = _mm512_load_ps(&pk0[0]);         
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);  
                        const __m512 C20                              = 
                                                     _mm512_set1_ps(2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 invn,n,phi2,pin,spin,cpin,cphin,sqr,x0,x1;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_mul_ps(C6283185307179586476925286766559,k0);
                        ear  = _mm512_setzero_ps();
                        n    = _mm512_div_ps(gam,C314159265358979323846264338328);
                        eai  = C078539816339744830961566084582;
                        invn = _mm512_rcp14_ps(n); 
                        sqr  = _mm512_sqrt_ps(x0);
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        spin = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        cpin = xcosf(pin);
                        cei  = _mm512_div_ps(cei,sqr);
                        cphin= xcosf(_mm512_mul_ps(phi2,invn));
                        x0   = _mm512_mul_ps(_mm512_mul_ps(C20,invn),spin);
                        x1   = _mm512_sub_ps(cpin,cphin);
                        n    = _mm512_div_ps(x0,x1);
                        _mm512_store_ps(&Dr[0] ,_mm512_mul_ps(cer,n));
                        _mm512_store_ps(&Di[0] ,_mm512_mul_ps(cei,n));
                }
                
                
                
                 
                   void coef_Ddiff_f8126_zmm16r4_u(const float * __restrict  pgam,
                                                   const float * __restrict pphi,
                                                   const float * __restrict  pk0,
                                                   float * __restrict  Dr,
                                                   float * __restrict  Di) {
                                    
                        register __m512 gam  = _mm512_loadu_ps(&pgam[0]);
                        register __m512 phi  = _mm512_loadu_ps(&pphi[0]);
                        register __m512 k0   = _mm512_loadu_ps(&pk0[0]);         
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f);  
                        const __m512 C20                              = 
                                                     _mm512_set1_ps(2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 invn,n,phi2,pin,spin,cpin,cphin,sqr,x0,x1;
                        phi2 = _mm512_add_ps(phi,phi);
                        x0   = _mm512_mul_ps(C6283185307179586476925286766559,k0);
                        ear  = _mm512_setzero_ps();
                        n    = _mm512_div_ps(gam,C314159265358979323846264338328);
                        eai  = C078539816339744830961566084582;
                        invn = _mm512_rcp14_ps(n); 
                        sqr  = _mm512_sqrt_ps(x0);
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        spin = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        cpin = xcosf(pin);
                        cei  = _mm512_div_ps(cei,sqr);
                        cphin= xcosf(_mm512_mul_ps(phi2,invn));
                        x0   = _mm512_mul_ps(_mm512_mul_ps(C20,invn),spin);
                        x1   = _mm512_sub_ps(cpin,cphin);
                        n    = _mm512_div_ps(x0,x1);
                        _mm512_storeu_ps(&Dr[0] ,_mm512_mul_ps(cer,n));
                        _mm512_storeu_ps(&Di[0] ,_mm512_mul_ps(cei,n));
                }
                
                
                   /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter diffraction coefficient 'D'.
                    Backscatter direction axial caustic (for slightly diffracted rays).
                    Scattered Electric and Magnetic fields.
                    Formula: 8.1-25
                */
                
                
                 
                   void EsHs_f8125_zmm16r4(const __m512 a,
                                           const __m512 k0,
                                           const __m512 r,
                                           const __m512 gam,
                                           const __m512 phi,
                                           const __m512 psi,
                                           __m512 * __restrict Esr,
                                           __m512 * __restrict Esi,
                                           __m512 * __restrict Hsr,
                                           __m512 * __restrict Hsi) {
                                           
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f); 
                        const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                        register __m512 Dr,Di,x0,x1;
                        register __m512 ear,eai,cer,cei;
                        register __m512 k0r,invr,t0r,t0i;
                        register __m512 sqr;
                        k0r  = _mm512_mul_ps(k0,r);
                        ear  = _mm512_setzero_ps();
                        eai  = _mm512_add_ps(k0r,_mm512_sub_ps(psi,
                                                   C078539816339744830961566084582));
                        coef_Ddiff_f8126_zmm16r4(gam,phi,k0,Dr,Di); 
                        invr = _mm512_rcp_ps(r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(C6283185307179586476925286766559,k0));
                        t0r  = _mm512_mul_ps(Dr,C05);
                        cer  = _mm512_mul_ps(cer,invr);
                        sqr  = _mm512_mul_ps(a,sqr);
                        t0i  = _mm512_mul_ps(Di,C05);  
                        cei  = _mm512_mul_ps(cei,invr);
                        x0   = _mm512_mul_ps(t0r,_mm512_mul_ps(sqr,cer));
                        x1   = _mm512_mul_ps(t0i,_mm512_mul_ps(sqr,cei));
                        *Esr = gms::math::negate_zmm16r4(x0);
                        *Esi = gms::math::negate_zmm16r4(x1); 
                        *Hsr = x0;
                        *Hsi = x1;             
                      
                }
                
                
                
                   void EsHs_f8125_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                             const float * __restrict __ATTR_ALIGN__(64) pk0,
                                             const float * __restrict __ATTR_ALIGN__(64) pr,
                                             const float * __restrict __ATTR_ALIGN__(64) pgam,
                                             const float * __restrict __ATTR_ALIGN__(64) pphi,
                                             const float * __restrict __ATTR_ALIGN__(64) ppsi,
                                             float * __restrict __ATTR_ALIGN__(64) Esr,
                                             float * __restrict __ATTR_ALIGN__(64) Esi,
                                             float * __restrict __ATTR_ALIGN__(64) Hsr,
                                             float * __restrict __ATTR_ALIGN__(64) Hsi) {
                            
                        register __m512 a   = _mm512_load_ps(&pa[0]);
                        register __m512 k0  = _mm512_load_ps(&pk0[0]);   
                        register __m512 r   = _mm512_load_ps(&pr[0]);   
                        register __m512 gam = _mm512_load_ps(&pgam[0]);   
                        register __m512 phi = _mm512_load_ps(&pphi[0]); 
                        register __m512 psi = _mm512_load_ps(&ppsi[0]);     
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f); 
                        const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                        register __m512 Dr,Di,x0,x1;
                        register __m512 ear,eai,cer,cei;
                        register __m512 k0r,invr,t0r,t0i;
                        register __m512 sqr;
                        k0r  = _mm512_mul_ps(k0,r);
                        ear  = _mm512_setzero_ps();
                        eai  = _mm512_add_ps(k0r,_mm512_sub_ps(psi,
                                                   C078539816339744830961566084582));
                        coef_Ddiff_f8126_zmm16r4(gam,phi,k0,Dr,Di); 
                        invr = _mm512_rcp_ps(r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(C6283185307179586476925286766559,k0));
                        t0r  = _mm512_mul_ps(Dr,C05);
                        cer  = _mm512_mul_ps(cer,invr);
                        sqr  = _mm512_mul_ps(a,sqr);
                        t0i  = _mm512_mul_ps(Di,C05);  
                        cei  = _mm512_mul_ps(cei,invr);
                        x0   = _mm512_mul_ps(t0r,_mm512_mul_ps(sqr,cer));
                        x1   = _mm512_mul_ps(t0i,_mm512_mul_ps(sqr,cei));
                        _mm512_store_ps(&Esr[0] ,gms::math::negate_zmm16r4(x0));
                        _mm512_store_ps(&Esi[0] ,gms::math::negate_zmm16r4(x1)); 
                        _mm512_store_ps(&Hsr[0] ,x0);
                        _mm512_store_ps(&Hsi[0] ,x1);             
                      
                }
                
            
                   void EsHs_f8125_zmm16r4_u(const float * __restrict  pa,
                                             const float * __restrict  pk0,
                                             const float * __restrict  pr,
                                             const float * __restrict pgam,
                                             const float * __restrict  pphi,
                                             const float * __restrict  ppsi,
                                             float * __restrict  Esr,
                                             float * __restrict  Esi,
                                             float * __restrict  Hsr,
                                             float * __restrict  Hsi) {
                            
                        register __m512 a   = _mm512_loadu_ps(&pa[0]);
                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);   
                        register __m512 r   = _mm512_loadu_ps(&pr[0]);   
                        register __m512 gam = _mm512_loadu_ps(&pgam[0]);   
                        register __m512 phi = _mm512_loadu_ps(&pphi[0]); 
                        register __m512 psi = _mm512_loadu_ps(&ppsi[0]);     
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f); 
                        const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                        register __m512 Dr,Di,x0,x1;
                        register __m512 ear,eai,cer,cei;
                        register __m512 k0r,invr,t0r,t0i;
                        register __m512 sqr;
                        k0r  = _mm512_mul_ps(k0,r);
                        ear  = _mm512_setzero_ps();
                        eai  = _mm512_add_ps(k0r,_mm512_sub_ps(psi,
                                                   C078539816339744830961566084582));
                        coef_Ddiff_f8126_zmm16r4(gam,phi,k0,Dr,Di); 
                        invr = _mm512_rcp_ps(r);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(C6283185307179586476925286766559,k0));
                        t0r  = _mm512_mul_ps(Dr,C05);
                        cer  = _mm512_mul_ps(cer,invr);
                        sqr  = _mm512_mul_ps(a,sqr);
                        t0i  = _mm512_mul_ps(Di,C05);  
                        cei  = _mm512_mul_ps(cei,invr);
                        x0   = _mm512_mul_ps(t0r,_mm512_mul_ps(sqr,cer));
                        x1   = _mm512_mul_ps(t0i,_mm512_mul_ps(sqr,cei));
                        _mm512_storeu_ps(&Esr[0] ,gms::math::negate_zmm16r4(x0));
                        _mm512_storeu_ps(&Esi[0] ,gms::math::negate_zmm16r4(x1)); 
                        _mm512_storeu_ps(&Hsr[0] ,x0);
                        _mm512_storeu_ps(&Hsi[0] ,x1);             
                      
                }
                
                
                /*
                    Surface discontinuities.
                    General perfectly conducting convex edge.
                    Backscatter diffraction coefficient 'D'.
                    Doubly and high order diffracted rays --
                    bistatic diffraction coefficients.
                    Formula: 8.1-27  
                
                */
                
                
                
                   void coef_D12_f8127_zmm16r4(const __m512 k0,
                                               const __m512 gam,
                                               const __m512 phi1,
                                               const __m512 phi2,
                                               __m512 * __restrict D1r,
                                               __m512 * __restrict D1i,
                                               __m512 * __restrict D2r,
                                               __m512 * __restrict D2i) {
                                               
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                        register __m512 invn,x0,x1,ear,eai,cer,cei;
                        register __m512 sqr,pin,spin,cpin,phis,phid,invc1,invc2;
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);
                        phid = _mm512_mul_ps(_mm512_sub_ps(phi1,phi2),invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(
                                             C6283185307179586476925286766559,k0)); 
                        ear  = _mm512_setzero_ps();
                        phis = _mm512_mul_ps(_mm512_add_ps(phi1,phi2),invn);
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        x0   = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        spin = _mm512_mul_ps(x0,invn);
                        cei  = _mm512_div_ps(cei,sqr);
                        cpin = xcosf(pin);
                        x0   = xcosf(phid);
                        invc1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x0));
                        x1   = xcosf(phis);
                        invc2= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x1));
                        ear  = _mm512_mul_ps(cer,spin);
                        phis = _mm512_sub_ps(invc1,invc2);
                        eai  = _mm512_mul_ps(cei,spin);
                        phid = _mm512_add_ps(invc1,invc2);
                        *D1r = _mm512_mul_ps(ear,phis);
                        *D1i = _mm512_mul_ps(eai,phis);
                        *D2r = _mm512_mul_ps(ear,phid);
                        *D2i = _mm512_mul_ps(eai,phid);
                }
                
                
                
                   void coef_D12_f8127_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                                 const float * __restrict __ATTR_ALIGN__(64) pgam,
                                                 const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                                 const float * __restrict __ATTR_ALIGN__(64) pphi2,
                                                 float * __restrict __ATTR_ALIGN__(64)  D1r,
                                                 float * __restrict __ATTR_ALIGN__(64)  D1i,
                                                 float * __restrict __ATTR_ALIGN__(64)  D2r,
                                                 float * __restrict __ATTR_ALIGN__(64)  D2i) {
                              
                        register __m512 k0  = _mm512_load_ps(&pk0[0]);
                        register __m512 gam = _mm512_load_ps(&pgam[0]);
                        register __m512 phi1= _mm512_load_ps(&pphi1[0]);
                        register __m512 phi2= _mm512_load_ps(&pphi2[0]);                 
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                        register __m512 invn,x0,x1,ear,eai,cer,cei;
                        register __m512 sqr,pin,spin,cpin,phis,phid,invc1,invc2;
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);
                        phid = _mm512_mul_ps(_mm512_sub_ps(phi1,phi2),invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(
                                             C6283185307179586476925286766559,k0)); 
                        ear  = _mm512_setzero_ps();
                        phis = _mm512_mul_ps(_mm512_add_ps(phi1,phi2),invn);
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        x0   = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        spin = _mm512_mul_ps(x0,invn);
                        cei  = _mm512_div_ps(cei,sqr);
                        cpin = xcosf(pin);
                        x0   = xcosf(phid);
                        invc1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x0));
                        x1   = xcosf(phis);
                        invc2= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x1));
                        ear  = _mm512_mul_ps(cer,spin);
                        phis = _mm512_sub_ps(invc1,invc2);
                        eai  = _mm512_mul_ps(cei,spin);
                        phid = _mm512_add_ps(invc1,invc2);
                        _mm512_store_ps(&D1r[0] ,_mm512_mul_ps(ear,phis));
                        _mm512_store_ps(&D1i[0] ,_mm512_mul_ps(eai,phis));
                        _mm512_store_ps(&D2r[0] ,_mm512_mul_ps(ear,phid));
                        _mm512_store_ps(&D2i[0] ,_mm512_mul_ps(eai,phid));
                }
                
                
                
                
                   void coef_D12_f8127_zmm16r4_u(const float * __restrict  pk0,
                                                 const float * __restrict  pgam,
                                                 const float * __restrict  pphi1,
                                                 const float * __restrict  pphi2,
                                                 float * __restrict   D1r,
                                                 float * __restrict  D1i,
                                                 float * __restrict   D2r,
                                                 float * __restrict  D2i) {
                              
                        register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                        register __m512 gam = _mm512_loadu_ps(&pgam[0]);
                        register __m512 phi1= _mm512_loadu_ps(&pphi1[0]);
                        register __m512 phi2= _mm512_loadu_ps(&pphi2[0]);                 
                        const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                        const __m512 C6283185307179586476925286766559 = 
                                                     _mm512_set1_ps(6.283185307179586476925286766559f);
                        const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                        register __m512 invn,x0,x1,ear,eai,cer,cei;
                        register __m512 sqr,pin,spin,cpin,phis,phid,invc1,invc2;
                        x0   = _mm512_div_ps(gam,C314159265358979323846264338328);
                        phid = _mm512_mul_ps(_mm512_sub_ps(phi1,phi2),invn);
                        sqr  = _mm512_sqrt_ps(_mm512_mul_ps(
                                             C6283185307179586476925286766559,k0)); 
                        ear  = _mm512_setzero_ps();
                        phis = _mm512_mul_ps(_mm512_add_ps(phi1,phi2),invn);
                        invn = _mm512_rcp14_ps(x0);
                        eai  = C078539816339744830961566084582;
                        pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        x0   = xsinf(pin);
                        cer  = _mm512_div_ps(cer,sqr);
                        spin = _mm512_mul_ps(x0,invn);
                        cei  = _mm512_div_ps(cei,sqr);
                        cpin = xcosf(pin);
                        x0   = xcosf(phid);
                        invc1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x0));
                        x1   = xcosf(phis);
                        invc2= _mm512_rcp14_ps(_mm512_sub_ps(cpin,x1));
                        ear  = _mm512_mul_ps(cer,spin);
                        phis = _mm512_sub_ps(invc1,invc2);
                        eai  = _mm512_mul_ps(cei,spin);
                        phid = _mm512_add_ps(invc1,invc2);
                        _mm512_storeu_ps(&D1r[0] ,_mm512_mul_ps(ear,phis));
                        _mm512_storeu_ps(&D1i[0] ,_mm512_mul_ps(eai,phis));
                        _mm512_storeu_ps(&D2r[0] ,_mm512_mul_ps(ear,phid));
                        _mm512_storeu_ps(&D2i[0] ,_mm512_mul_ps(eai,phid));
                }
                
                
                /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Formula 8.1-62
                */
#include <stdint.h>                
#include <complex.h>    
#include <tgmath.h>  
#include <omp.h>         
//#include "GMS_cspint_quad.hpp"
//#include "GMS_avint_quad.hpp"

                   
                   static inline
                   float avint(    const float * __restrict x,
                                    const float * __restrict y,
                                    const int32_t n,
                                    const float xlo,
                                    const float xup,
                                    int32_t * __restrict ierr)        {

                          float a , b , c , ca , cb , cc , fl , fr , r3 , &
                                rp5 , slope , sum , syl , syl2 , syl3 , syu , &
                                syu2 , syu3 , term1 , term2 , term3 , x1 , &
                                x12 , x13 , x2 , x23 , x3, ans;
                          int32_t i , inlft , inrt , istart , istop;
                          *ierr = 1;
                          ans = 0.0;
                          // Error check and trivial cases
                          if(xlo==xup) return;
                          if(xlo>xup) {
                             *ierr = 2;
                             return SNANF;
                          }
                          if(n<2) {
                             *ierr = 5;
                             return SNANF;
                          }
                          for(i = 1; i < n; ++i) {
                               if(x[i]<=x[i-1]) {
                                  *ierr = 4;
                                  return SNANF;
                               }
                               if(x[i]>xup) break;
                         }
                         
                         if(n<3) {
                             
                            //! special n=2 case
                            slope = (y[1]-y[0])/(x[1]-x[0]);
                            fl    =  y[0] + slope*(xlo-x[0]);
                            fr    =  y[1] + slope*(xup-x[1]);
                            ans   =  0.5*(fl+fr)*(xup-xlo);
                       
                         }
                         else if(x[n-2]<xlo) {
                            *ierr = 3;
                                              
                         }
                         else if(x[2]<=xup) {

                              i = 1;
                              while(true) {
                                
                                 if(x[i]>=xlo) {
                                    inlft = i;
                                    i     = n;
                                    while(true) {
                                        
                                       if(x[i]<=xup) {
                                          inrt = i;
                                          if((inrt-inlft)>=2) {
                                              istart = inlft;
                                              if(inlft==1) istart = 2;
                                              istop = inrt;
                                              if(inrt==n) istop = n-1;
                                              r3  = 3.0f;
                                              rp5 = 0.5f;
                                              sum = 0.0f;
                                              syl = xlo;
                                              syl2= syl*syl;
                                              syl3= syl2*syl;
                                              for(i = istart; i < istop; ++i) {
                                                  x1    = x[i-1];
                                                  x2    = x[i];
                                                  x3    = x[i+1];
                                                  x12   = x1-x2;
                                                  x13   = x1-x3;
                                                  x23   = x2-x3;
                                                  term1 = y[i-1]/(x12*x13);
                                                  term2 = -y[i]/(x12*x23);
                                                  term3 = y[i+1]/(x13*x23);
                                                  a     = term1 + term2 + term3;
                                                  b     = -(x2+x3)*term1 - (x1+x3)*term2 - (x1+x2)*term3;
                                                  c     = x2*x3*term1 + x1*x3*term2 + x1*x2*term3;
                                                  if(i>istart) {
                                                        ca = 0.5f*(a+ca);
                                                        cb = 0.5f*(b+cb);
                                                        cc = 0.5f*(c+cc);
                                                  }
                                                  else {
                                                        ca = a;
                                                        cb = b;
                                                        cc = c;
                                                  }
                                                  syu  = x2;
                                                  syu2 = syu*syu;
                                                  syu3 = syu2*syu;
                                                  sum  = sum + ca*(syu3-syl3)/r3 + cb*rp5*(syu2-syl2) + cc*(syu-syl);
                                                  ca   = a;
                                                  cb   = b;
                                                  cc   = c;
                                                  syl  = syu;
                                                  syl2 = syu2;
                                                  syl3 = syu3;
                                              }//end for
                                               syu = xup;
                                               ans = sum + ca*(syu*syu*syu-syl3)/r3 + cb*rp5*(syu*syu-syl2) + cc*(syu-syl);
                                          }
                                          else {
                                               *ierr = 3;
                                          }
                                          return;
                                       } //end if
                                       i -= 1;
                                    } //end while
                                 } // end if
                                  i += 1;
                             }// end while
                         }
                         else {
                              *ierr = 3;
                        } //end if
                          
                   }
                   
                   
                   static inline
                   void cspint(       const int32_t ntab,
                                      const float * __restrict __ATTR_ALIGN__(64) xtab
                                      const float * __restrict __ATTR_ALIGN__(64) ftab
                                      const float A,
                                      const float B,
                                      float * __restrict __ATTR_ALIGN__(64) y1,
                                      float * __restrict __ATTR_ALIGN__(64) y2,
                                      float * __restrict __ATTR_ALIGN__(64) y3,
                                      float * __restrict __ATTR_ALIGN__(64) e,
                                      float * __restrict __ATTR_ALIGN__(64) work,
                                      float * __restrict result) {
                           
                           if(ntab<3) {
                              *result = SNANF;
                              return;
                           }
                           float r,s,term,u,t0;
                           int32_t i,j;

                           __assume_aligned(xtab,64);
                           __assume_aligned(ftab,64);
                           __assume_aligned(y1,64);
                           __assume_aligned(y2,64);
                           __assume_aligned(y3,64);
                           __assume_aligned(e,64);
                           __assume_aligned(work,64);

                           for(i = 0; i != ntab-1; ++i) {
                               if(xtab[i+1]<=xtab[i]) {
                                  *result = SNANF;
                                  return;
                               }
                           }
                           s = 0.0f;
                           #pragma vector aligned
                           #pragma omp simd
                           for(i = 0; i != ntab-1; ++i) {
                               r     = (ftab[i+1]-ftab[i])/(xtab[i+1]-xtab[i]);
                               y2[i] = r-s;
                               s     = r;
                           }
                           s = 0.0f;
                           r = 0.0f;
                           y2[0]    = 0.0f;
                           y2[ntab] = 0.0f;

                           for(i = 1; i != ntab-1; ++i) {
                               y2[i]  = y2[i]+r*y2[i-1];
                               work[i]= 2.0f*(xtab[i-1]-xtab[i+1])-r*s;
                               s      = xtab[i+1]-xtab[i];
                               r      = s/work[i];
                           }

                           #pragma vector aligned
                           #pragma omp simd
                           for(j = 1; j != ntab-1; ++j) {
                               i = ntab+1-j;
                               y2[i] = (xtab[i+1]-xtab[i]*y2[i+1]-y2[i])/work[i];
                           }

                           #pragma vector aligned
                           #pragma omp simd
                           for(i = 0; i != ntab-1; ++i) {
                               s     = xtab[i+1]-xtab[i];
                               r     = y2[i+1]-y2[i];
                               y3[i] = r/s;
                               y2[i] = 3.0f*y2[i];
                               t0    = y2[i]+r;
                               y1[i] = (ftab[i+1]-ftab[i])/(s-t0*s);
                           }

                           e[0] = 0.0f;
                           #pragma vector aligned
                           #pragma omp simd reduction(+:e)
                           for(i = 0; i != ntab-1; ++i) {
                               s    = xtab[i+1]-xtab[i];
                               term = ((( y3[i]*0.25f*s+y2[i]*0.33333333333333333333333333333f)*s
                                      + y1[i]*0.5f)*s+ftab[i])*s;
                               e[i+1] = e[i]+term; 
                           }
                          //!
                          //!  Determine where the endpoints A and B lie in the mesh of XTAB's.
                          //!
                          r = A;
                          u = 1.0f;
                          *result = 0.0f;
                          for(j = 0, j != 1; ++j) {
                              //The endpoint is less than or equal to XTAB(1).
                              if(r<=xtab[0]) {
                                 *result = *result-u*((r-xtab[0])* y1[0]*0.5f+
                                 ftab[0])*(r-xtab[0]); 
                              }
                              else if(xtab[ntab]<=r) {
                              // The endpoint is greater than or equal to XTAB(NTAB).
                                *result = *result-u*(e[ntab]+(r-xtab[ntab]) 
                                         *(ftab[ntab]+0.5f*(ftab[ntab-1] 
                                         +(xtab[ntab]-xtab[ntab-1])*y1[ntab-1]) 
                                         *(r-xtab[ntab])));
                              }
                              else {
                               //  The endpoint is strictly between XTAB(1) and XTAB(NTAB).
                                 for(i = 0; i != ntab-1; ++i) {
                                     if(r<=xtab[i+1]) {
                                        r = r-xtab[i];
                                        *result = result-u*(e[i]+(((
                                                 y3[i]*0.25f*r 
                                                 +y2[i]*0.333333333333333333333333333333333f)*r
                                                 +y1[i]*0.5f)*r+ftab[i])*r);
                                        goto label120;
                                     }
                                 }

                              }
label120:
                                 u = -1.0f;
                                 r = B;
                          }
                      }



                 
                
                   float rcs_f8162_zmm16r4_u(const float * __restrict pdAdl,
                                             const float *  __restrict pdl,
                                             const float   k0,
                                             const float   l) {
                          
                         __ATTR_ALIGN__(64) float intr[16];
                         __ATTR_ALIGN__(64) float inti[16]; 
                         __ATTR_ALIGN__(64) float Y1[16];
                         __ATTR_ALIGN__(64) float Y2[16];
                         __ATTR_ALIGN__(64) float Y3[16]; 
                         __ATTR_ALIGN__(64) float E[16];
                         __ATTR_ALIGN__(64) float WRK[16];
                         
                         constexpr int32_t NTAB = 16;               
                         constexpr float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                         register __m512 dAdl = _mm512_loadu_ps(&pdAdl[0]);
                         register __m512 dl   = _mm512_loadu_ps(&pdl[0]);                                 
                         register __m512 vk0,k0l,ear,eai,cer,cei;
                         float complex c;
                         register float rcs,k02,frac,sumr,sumi;
                         vk0  = _mm512_set1_ps(k0);
                         k0l  = _mm512_mul_ps(vk0,dl);
                         ear  = _mm512_setzero_ps();
                         eai  = _mm512_add_ps(k0l,k0l);
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         _mm512_store_ps(&intr[0], _mm512_mul_ps(cer,dAdl);
                         _mm512_store_ps(&inti[0], _mm512_mul_ps(cei,dAdl);
                         sumr = 0.0f;
                         sumi = 0.0f;
                         cspint(NTAB,pdl,&intr[0],0.0f,l,&Y1[0],&Y2[0],&Y3[0],&E[0],&WRK[0],&sumr);
                         cspint(NTAB,pdl,&inti[0],0.0f,l,&Y1[0],&Y2[0],&Y3[0],&E[0],&WRK[0],&sumi);
                         c = sumr+sumi*I;
                         k02   = k0*k0;   
                         frac  = k02/C314159265358979323846264338328;
                         rcs   = frac*abs(c);
                         return (rcs);                         
                  }
                  
                  
                 
                   float rcs_f8162_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                             const float * __restrict __ATTR_ALIGN__(64) pdl,
                                             const float   k0,
                                             const float   l) {
                          
                         __ATTR_ALIGN__(64) float intr[16];
                         __ATTR_ALIGN__(64) float inti[16]; 
                         __ATTR_ALIGN__(64) float Y1[16];
                         __ATTR_ALIGN__(64) float Y2[16];
                         __ATTR_ALIGN__(64) float Y3[16]; 
                         __ATTR_ALIGN__(64) float E[16];
                         __ATTR_ALIGN__(64) float WRK[16];
                         
                         constexpr int32_t NTAB = 16;               
                         constexpr float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                         register __m512 dAdl = _mm512_load_ps(&pdAdl[0]);
                         register __m512 dl   = _mm512_load_ps(&pdl[0]);                                 
                         register __m512 vk0,k0l,ear,eai,cer,cei;
                         float complex c;
                         register float rcs,k02,frac,sumr,sumi;
                         vk0  = _mm512_set1_ps(k0);
                         k0l  = _mm512_mul_ps(vk0,dl);
                         ear  = _mm512_setzero_ps();
                         eai  = _mm512_add_ps(k0l,k0l);
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         _mm512_store_ps(&intr[0], _mm512_mul_ps(cer,dAdl);
                         _mm512_store_ps(&inti[0], _mm512_mul_ps(cei,dAdl);
                         sumr = 0.0f;
                         sumi = 0.0f;
                         cspint(NTAB,pdl,&intr[0],0.0f,l,&Y1[0],&Y2[0],&Y3[0],&E[0],&WRK[0],&sumr);
                         cspint(NTAB,pdl,&inti[0],0.0f,l,&Y1[0],&Y2[0],&Y3[0],&E[0],&WRK[0],&sumi);
                         c =  sumr+sumi*I;
                         k02   = k0*k0;   
                         frac  = k02/C314159265358979323846264338328;
                         rcs   = frac*abs(c);
                         return (rcs);                         
                  }
                  
                  
                   /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Case of small integrand. 
                       Integrator 'avint' i.e. irregular abscissas
                       Formula 8.1-62
                */
                
                  
                   float rcs_f8162_zmm16r4_avint_u(const float * __restrict pdAdl,
                                                   const float *  __restrict pdl,
                                                   const float   k0,
                                                   const float   l,
                                                   int32_t * __restrict ierr,
                                                   int32_t * __restrict ieri) {
                          
                         __ATTR_ALIGN__(64) float intr[16];
                         __ATTR_ALIGN__(64) float inti[16]; 
                                         
                         constexpr int32_t NTAB = 16;               
                         constexpr float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                         register __m512 dAdl = _mm512_loadu_ps(&pdAdl[0]);
                         register __m512 dl   = _mm512_loadu_ps(&pdl[0]);                                 
                         register __m512 vk0,k0l,ear,eai,cer,cei;
                         float complex c;
                         register float rcs,k02,frac,sumr,sumi;
                         int32_t err,eri;
                         vk0  = _mm512_set1_ps(k0);
                         k0l  = _mm512_mul_ps(vk0,dl);
                         ear  = _mm512_setzero_ps();
                         eai  = _mm512_add_ps(k0l,k0l);
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         _mm512_store_ps(&intr[0], _mm512_mul_ps(cer,dAdl);
                         _mm512_store_ps(&inti[0], _mm512_mul_ps(cei,dAdl);
                         sumr = 0.0f;
                         sumi = 0.0f;
                         sumr = avint(pdl,&intr[0],0.0f,l,&err);
                         sumi = avint(pdl,&inti[0],0.0f,l,&eri);
                         *ierr = err;
                         *ieri = eri;
                         if(*ierr == 3 || *ieri == 3) {
                             return SNANF;
                         }
                         c = sumr+sumi*I;
                         k02   = k0*k0;   
                         frac  = k02/C314159265358979323846264338328;
                         rcs   = frac*abs(c);
                         return (rcs);                         
                  }
                  
                  
                  
                   float rcs_f8162_zmm16r4_avint_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                                   const float * __restrict __ATTR_ALIGN__(64) pdl,
                                                   const float   k0,
                                                   const float   l,
                                                   int32_t * ierr,
                                                   int32_t * ieri) {
                          
                         __ATTR_ALIGN__(64) float intr[16];
                         __ATTR_ALIGN__(64) float inti[16]; 
                                         
                         constexpr int32_t NTAB = 16;               
                         constexpr float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                         register __m512 dAdl = _mm512_load_ps(&pdAdl[0]);
                         register __m512 dl   = _mm512_load_ps(&pdl[0]);                                 
                         register __m512 vk0,k0l,ear,eai,cer,cei;
                         float complex c;
                         register float rcs,k02,frac,sumr,sumi;
                         int32_t err,eri;
                         vk0  = _mm512_set1_ps(k0);
                         k0l  = _mm512_mul_ps(vk0,dl);
                         ear  = _mm512_setzero_ps();
                         eai  = _mm512_add_ps(k0l,k0l);
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         _mm512_stor_ps(&intr[0], _mm512_mul_ps(cer,dAdl);
                         _mm512_stor_ps(&inti[0], _mm512_mul_ps(cei,dAdl);
                         sumr = 0.0f;
                         sumi = 0.0f;
                         sumr = avint(pdl,&intr[0],0.0f,l,&err);
                         sumi = avint(pdl,&inti[0],0.0f,l,&eri);
                         *ierr = err;
                         *ieri = eri;
                         if(*ierr == 3 || *ieri == 3) {
                            return SNANF;
                         }
                         c = sumr+sumi*I;
                         k02   = k0*k0;   
                         frac  = k02/C314159265358979323846264338328;
                         rcs   = frac*abs(c);
                         return (rcs);                         
                  }
                  
                  
                  
                  
                  
                   /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Case of small integrand -- single-threaded execution.
                       Formula 8.1-62
                */
                
                
                
                   float rcs_f8162_zmm16r4_u(const float * __restrict  pdAdl,
                                             const float * __restrict  pdl,
                                             float * __restrict  intr,
                                             float * __restrict  inti,
                                             float * __restrict  Y1,
                                             float * __restrict  Y2,
                                             float * __restrict  Y3,
                                             float * __restrict  E,
                                             float * __restrict  WRK
                                             const float   k0,
                                             const float   l,
                                             const int32_t NTAB) {
                                             
                        if(__builtin_expect(NTAB==16,0)) {
                            float rcs = 0.0f;
                            rcs = rcs_f8162_zmm16r4_u(pdAdl,pdl,k0,l);
                            return (rcs);
                        }    
                        
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_loadu_ps(&pdAdl[i]);
                             register __m512 y = _mm512_loadu_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_storeu_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_storeu_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
                      cspint(NTAB,pdl,intr,0.0f,l,Y1,Y2,Y3,E,WRK,&sumr); 
                      cspint(NTAB,pdl,inti,0.0f,l,Y1,Y2,Y3,E,WRK,&sumi);  
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
               
                   float rcs_f8162_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                             const float * __restrict __ATTR_ALIGN__(64) pdl,
                                             float * __restrict __ATTR_ALIGN__(64) intr,
                                             float * __restrict __ATTR_ALIGN__(64) inti,
                                             float * __restrict __ATTR_ALIGN__(64) Y1,
                                             float * __restrict __ATTR_ALIGN__(64) Y2,
                                             float * __restrict __ATTR_ALIGN__(64) Y3,
                                             float * __restrict __ATTR_ALIGN__(64) E,
                                             float * __restrict __ATTR_ALIGN__(64) WRK
                                             const float   k0,
                                             const float   l,
                                             const int32_t NTAB) {
                                             
                        if(__builtin_expect(NTAB==16,0)) {
                            float rcs = 0.0f;
                            rcs = rcs_f8162_zmm16r4_a(pdAdl,pdl,k0,l);
                            return (rcs);
                        }    
                        
                        constexpr float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_load_ps(&pdAdl[i]);
                             register __m512 y = _mm512_load_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_store_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_store_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
                      cspint(NTAB,pdl,intr,0.0f,l,Y1,Y2,Y3,E,WRK,&sumr); 
                      cspint(NTAB,pdl,inti,0.0f,l,Y1,Y2,Y3,E,WRK,&sumi);  
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
                   /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Case of large integrand - single thread.
                       Integrator 'avint' i.e. irregular abscissas
                       Formula 8.1-62
                */
                
                
                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   float rcs_f8162_zmm16r4_avint_u(const float * __restrict  pdAdl,
                                                   const float * __restrict  pdl,
                                                   float * __restrict  intr,
                                                   float * __restrict  inti,
                                                   const float   k0,
                                                   const float   l,
                                                   int32_t * ierr,
                                                   int32_t * ieri,
                                                   const int32_t NTAB) {
                                             
                                                
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i,err,eri; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_loadu_ps(&pdAdl[i]);
                             register __m512 y = _mm512_loadu_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_storeu_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_storeu_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
                      sumr = avint(pdl,intr,NTAB,0.0f,l,&err); 
                      sumi = avint(pdl,inti,NTAB,0.0f,l,&eri); 
                      *ierr = err;
                      *ieri = eri;
                      if(ierr == 3 || ieri == 3) {
                         return SNANF;
                      } 
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
                
                   float rcs_f8162_zmm16r4_avint_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                                   const float * __restrict __ATTR_ALIGN__(64) pdl,
                                                   float * __restrict __ATTR_ALIGN__(64) intr,
                                                   float * __restrict __ATTR_ALIGN__(64) inti,
                                                   const float   k0,
                                                   const float   l,
                                                   int32_t * ierr,
                                                   int32_t * ieri,
                                                   const int32_t NTAB) {
                                             
                                                
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i,err,eri; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_load_ps(&pdAdl[i]);
                             register __m512 y = _mm512_load_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_store_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_store_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
                      sumr = avint(pdl,intr,NTAB,0.0f,l,&err); 
                      sumi = avint(pdl,inti,NTAB,0.0f,l,&eri); 
                      *ierr = err;
                      *ieri = eri;
                      if(*ierr == 3 || *ieri == 3) {
                         return SNANF;
                      } 
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
               
               
                 /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Case of large integrand -- two-threaded execution of integrator.
                       Integrator 'cspint'
                       Formula 8.1-62
                */
                
#include <omp.h>
    
                
                
                   float rcs_f8162_zmm16r4_cspint2t_u(const float * __restrict  pdAdl,
                                                     const float * __restrict  pdl,
                                                     float * __restrict  intr,
                                                     float * __restrict  inti,
                                                     struct RCS_F8162_DATA w,
                                                     const float   k0,
                                                     const float   l,
                                                     const int32_t NTAB) {
                                             
                        if(__builtin_expect(NTAB==16,0)) {
                            float rcs = 0.0f;
                            rcs = rcs_f8162_zmm16r4_u(pdAdl,pdl,k0,l);
                            return (rcs);
                        }    
                        
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float * __restrict px1 = w.Ya1;
                        float * __restrict py1 = w.Yb1;
                        float * __restrict px2 = w.Ya2;
                        float * __restrict py2 = w.Yb2;
                        float * __restrict px3 = w.Ya3;
                        float * __restrict py3 = w.Yb3;
                        float * __restrict px4 = w.Ea;
                        float * __restrict py4 = w.Eb;
                        float * __restrict px5 = w.WRKa;
                        float * __restrict py5 = w.WRKb;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_loadu_ps(&pdAdl[i]);
                             register __m512 y = _mm512_loadu_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_storeu_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_storeu_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
   #pragma omp parallel sctions
                {
                     #pragma omp section
                       {
                             cspint(NTAB,pdl,intr,0.0f,l,px1,px2,px3,px4,px5,&sumr); 
                       }
                     #pragma omp section
                       {
                             cspint(NTAB,pdl,inti,0.0f,l,py1,py2,py3,py4,py5,&sumi); 
                       }
                } 
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
               
                   float rcs_f8162_zmm16r4_cspint2t_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                                     const float * __restrict __ATTR_ALIGN__(64) pdl,
                                                     float * __restrict __ATTR_ALIGN__(64) intr,
                                                     float * __restrict __ATTR_ALIGN__(64) inti,
                                                     struct RCS_F8162_DATA w,
                                                     const float   k0,
                                                     const float   l,
                                                     const int32_t NTAB) {
                                             
                        if(__builtin_expect(NTAB==16,0)) {
                            float rcs = 0.0f;
                            rcs = rcs_f8162_zmm16r4_u(pdAdl,pdl,k0,l);
                            return (rcs);
                        }    
                        
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float * __restrict __ATTR_ALIGN__(64) px1 = w.Ya1;
                        float * __restrict __ATTR_ALIGN__(64) py1 = w.Yb1;
                        float * __restrict __ATTR_ALIGN__(64) px2 = w.Ya2;
                        float * __restrict __ATTR_ALIGN__(64) py2 = w.Yb2;
                        float * __restrict __ATTR_ALIGN__(64) px3 = w.Ya3;
                        float * __restrict __ATTR_ALIGN__(64) py3 = w.Yb3;
                        float * __restrict __ATTR_ALIGN__(64) px4 = w.Ea;
                        float * __restrict __ATTR_ALIGN__(64) py4 = w.Eb;
                        float * __restrict __ATTR_ALIGN__(64) px5 = w.WRKa;
                        float * __restrict __ATTR_ALIGN__(64) py5 = w.WRKb;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_load_ps(&pdAdl[i]);
                             register __m512 y = _mm512_load_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_store_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_store_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
   #pragma omp parallel sctions
                {
                     #pragma omp section
                       {
                             cspint(NTAB,pdl,intr,0.0f,l,px1,px2,px3,px4,px5,&sumr); 
                       }
                     #pragma omp section
                       {
                             cspint(NTAB,pdl,inti,0.0f,l,py1,py2,py3,py4,py5,&sumi); 
                       }
                } 
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
                /*
                       Adachi expression for axial-incidence
                       of backscatter RCS for entire scatterer length.
                       Shall be used in case of thin long axially symetric 
                       bodies e.g. 'ogives,double-cones, etc.,'
                       Vectorization of an integrand.
                       Case of large integrand -- two-threaded execution of integrator.
                       Integrator 'avint' (irregular abscissas).
                       Formula 8.1-62
                */
                
                
               
                   float rcs_f8162_zmm16r4_avint2t_u(const float * __restrict  pdAdl,
                                                     const float * __restrict  pdl,
                                                     float * __restrict  intr,
                                                     float * __restrict  inti,
                                                     int32_t * __restrict ierr,
                                                     int32_t * __restrict ieri,
                                                     const float   k0,
                                                     const float   l,
                                                     const int32_t NTAB) {
                                             
                                              
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i,err,eri; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_loadu_ps(&pdAdl[i]);
                             register __m512 y = _mm512_loadu_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_storeu_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_storeu_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
   #pragma omp parallel sctions
                {
                     #pragma omp section
                       {
                            sumr = avint(pdl,intr,NTAB,0.0f,l,&err); 
                       }
                     #pragma omp section
                       {
                            sumi = avint(pdl,inti,NTAB,0.0f,l,&eri); 
                       }
                } 
                      *ierr = err;
                      *ieri = eri
                      if(*ierr == 3 || *ieri == 3) {
                          return SNANF;
                      }
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
               
                   float rcs_f8162_zmm16r4_avint2t_a(const float * __restrict __ATTR_ALIGN__(64) pdAdl,
                                                     const float * __restrict __ATTR_ALIGN__(64) pdl,
                                                     float * __restrict __ATTR_ALIGN__(64) intr,
                                                     float * __restrict __ATTR_ALIGN__(64) inti,
                                                     int32_t * __restrict ierr,
                                                     int32_t * __restrict ieri,
                                                     const float   k0,
                                                     const float   l,
                                                     const int32_t NTAB) {
                                             
                                              
                        const float C314159265358979323846264338328 = 
                                                        3.14159265358979323846264338328f;
                        register __m512 vk0,k0l,ear,eai,cer,cei;
                        float complex c;
                        register float rcs,k02,frac,sumr,sumi; 
                        int32_t i,err,eri; 
                        vk0  = _mm512_set1_ps(k0);
                        ear  = _mm512_setzero_ps();
                        for(i = 0; i != ROUND_TO_SIXTEEN(NTAB,15); i += 16) {
                             _mm_prefetch((const char*)&pdAdl[i],_MM_NTA_T0);
                             _mm_prefetch((const char*)&pdl[i],  _MM_NTA_T0);
                             register __m512 x = _mm512_load_ps(&pdAdl[i]);
                             register __m512 y = _mm512_load_ps(&pdl[i]);
                             k0l               = _mm512_mul_ps(vk0,y);
                             eai               = _mm512_add_ps(k0l,k0l);
                             cexp_zmm16r4(ear,eai,&cer,&cei);
                             register __m512 t0 = cer;
                             register __m512 t1 = cei;
                             _mm512_store_ps(&intr[i], _mm512_mul_ps(t0,x));
                             _mm512_store_ps(&inti[i], _mm512_mul_ps(t1,x));
                       } 
                       sumr = 0.0f;
                       sumi = 0.0f;
                       for(; i != NTAB; ++i) {
                           const float x  = pdAdl[i];
                           const float y  = pdl[i];
                           const float k0l= k0*y;
                           const float eai= k0l+k0l;
                           float complex cc = exp(0.0f+eai*I);
                           intr[i]        = creal(cc)*x;
                           inti[i]        = cimag(cc)*x;
                      }   
   #pragma omp parallel sctions
                {
                     #pragma omp section
                       {
                            sumr = avint(pdl,intr,NTAB,0.0f,l,&err); 
                       }
                     #pragma omp section
                       {
                            sumi = avint(pdl,inti,NTAB,0.0f,l,&eri); 
                       }
                } 
                      *ierr = err;
                      *ieri = eri
                      if(*ierr == 3 || *ieri == 3) {
                          return SNANF;
                      }
                      c = sumr+sumi*I;
                      k02   = k0*k0;   
                      frac  = k02/C314159265358979323846264338328;
                      rcs   = frac*abs(c);
                      return (rcs);               
               }
               
               
               
               
               
               
               /*
                     High frequency approximations.
                     Rounded-tip cone total nose-on
                     backscatter RCS.
                     Formula 8.1-93
               */
               
               
              
                   __m512 rcs_f8193_zmm16r4(const __m512 b,
                                            const __m512 a,
                                            const __m512 k0,
                                            const __m512 alp,
                                            const __m512 l) {
                                            
                         const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);
                         const __m512 C15                              =
                                                     _mm512_set1_ps(1.5f);
                         register __m512 sina,pin,n,invn,x0,x1,k0l,sqr;
                         register __m512 ear,eai,cer,cei,cosa;
                         register __m512 rcs,cpin,cos2a,k0b,t0,t1;
                         k0b  = _mm512_mul_ps(k0,b);
                         ear  = _mm512_setzero_ps();
                         n    = _mm512_add_ps(C15,_mm512_div_ps(alp,   
                                                          C314159265358979323846264338328));
                         k0l  = _mm512_mul_ps(k0,l);
                         eai  = _mm512_add_ps(k0l,k0l);
                         invn = _mm512_rcp14_ps(n);
                         sina = _mm512_sub_ps(C10,xsinf(alp));
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         cosa = xcosf(alp);
                         x0   = xsinf(_mm512_mul_ps(
                                              _mm512_add_ps(k0b,k0b),sina));
                         x1   = _mm512_mul_ps(k0b,_mm512_mul_ps(cosa,cosa));
                         sqr  = _mm512_sub_ps(C10,_mm512_div_ps(x0,x1));
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         x0   = _mm512_sqrt_ps(sqr);
                         spin = _mm512_mul_ps(xsinf(pin),invn);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_add_ps(alp,alp),invn);
                         cos2a= xcosf(x1);
                         t0   = _mm512_mul_ps(C1772453850905516027298167483341,
                                                              _mm512_mul_ps(b,x0)); // keep
                         x1   = _mm512_sub_ps(cpin,cos2a);
                         t1   = _mm512_mul_ps(_mm512_add_ps(C1772453850905516027298167483341,
                                                            C1772453850905516027298167483341),
                                                                           _mm512_mul_ps(a,spin)); // keep
                         x0   = _mm512_rcp14_ps(x1); // keep
                         ear  = _mm512_mul_ps(_mm512_add_ps(t0,t1),x0);
                         t0   = _mm512_mul_ps(ear,cer);
                         t1   = _mm512_mul_ps(ear,cei);
                         rcs  = cabs_zmm16r4(t0,t1);
                         return (rcs);                      
                 }
                 
                 
             
                   __m512 rcs_f8193_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pl) {
                                     
                         register __m512 b  = _mm512_load_ps(&pb[0]);
                         register __m512 a  = _mm512_load_ps(&pa[0]);  
                         register __m512 k0 = _mm512_load_ps(&pk0[0]);
                         register __m512 alp= _mm512_load_ps(&palp[0]);  
                         register __m512 l  = _mm512_load_ps(&pl[0]);   
                         const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);
                         const __m512 C15                              =
                                                     _mm512_set1_ps(1.5f);
                         register __m512 sina,pin,n,invn,x0,x1,k0l,sqr;
                         register __m512 ear,eai,cer,cei,cosa;
                         register __m512 rcs,cpin,cos2a,k0b,t0,t1;
                         k0b  = _mm512_mul_ps(k0,b);
                         ear  = _mm512_setzero_ps();
                         n    = _mm512_add_ps(C15,_mm512_div_ps(alp,   
                                                          C314159265358979323846264338328));
                         k0l  = _mm512_mul_ps(k0,l);
                         eai  = _mm512_add_ps(k0l,k0l);
                         invn = _mm512_rcp14_ps(n);
                         sina = _mm512_sub_ps(C10,xsinf(alp));
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         cosa = xcosf(alp);
                         x0   = xsinf(_mm512_mul_ps(
                                              _mm512_add_ps(k0b,k0b),sina));
                         x1   = _mm512_mul_ps(k0b,_mm512_mul_ps(cosa,cosa));
                         sqr  = _mm512_sub_ps(C10,_mm512_div_ps(x0,x1));
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         x0   = _mm512_sqrt_ps(sqr);
                         spin = _mm512_mul_ps(xsinf(pin),invn);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_add_ps(alp,alp),invn);
                         cos2a= xcosf(x1);
                         t0   = _mm512_mul_ps(C1772453850905516027298167483341,
                                                              _mm512_mul_ps(b,x0)); // keep
                         x1   = _mm512_sub_ps(cpin,cos2a);
                         t1   = _mm512_mul_ps(_mm512_add_ps(C1772453850905516027298167483341,
                                                            C1772453850905516027298167483341),
                                                                           _mm512_mul_ps(a,spin)); // keep
                         x0   = _mm512_rcp14_ps(x1); // keep
                         ear  = _mm512_mul_ps(_mm512_add_ps(t0,t1),x0);
                         t0   = _mm512_mul_ps(ear,cer);
                         t1   = _mm512_mul_ps(ear,cei);
                         rcs  = cabs_zmm16r4(t0,t1);
                         return (rcs);                      
                 }
                 
                 
                 
               
                   __m512 rcs_f8193_zmm16r4_u(const float * __restrict  pb,
                                              const float * __restrict  pa,
                                              const float * __restrict  pk0,
                                              const float * __restrict  palp,
                                              const float * __restrict _pl) {
                                     
                         register __m512 b  = _mm512_loadu_ps(&pb[0]);
                         register __m512 a  = _mm512_loadu_ps(&pa[0]);  
                         register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
                         register __m512 alp= _mm512_loadu_ps(&palp[0]);  
                         register __m512 l  = _mm512_loadu_ps(&pl[0]);   
                         const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);
                         const __m512 C15                              =
                                                     _mm512_set1_ps(1.5f);
                         register __m512 sina,pin,n,invn,x0,x1,k0l,sqr;
                         register __m512 ear,eai,cer,cei,cosa;
                         register __m512 rcs,cpin,cos2a,k0b,t0,t1;
                         k0b  = _mm512_mul_ps(k0,b);
                         ear  = _mm512_setzero_ps();
                         n    = _mm512_add_ps(C15,_mm512_div_ps(alp,   
                                                          C314159265358979323846264338328));
                         k0l  = _mm512_mul_ps(k0,l);
                         eai  = _mm512_add_ps(k0l,k0l);
                         invn = _mm512_rcp14_ps(n);
                         sina = _mm512_sub_ps(C10,xsinf(alp));
                         cexp_zmm16r4(ear,eai,&cer,&cei);
                         cosa = xcosf(alp);
                         x0   = xsinf(_mm512_mul_ps(
                                              _mm512_add_ps(k0b,k0b),sina));
                         x1   = _mm512_mul_ps(k0b,_mm512_mul_ps(cosa,cosa));
                         sqr  = _mm512_sub_ps(C10,_mm512_div_ps(x0,x1));
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         x0   = _mm512_sqrt_ps(sqr);
                         spin = _mm512_mul_ps(xsinf(pin),invn);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_add_ps(alp,alp),invn);
                         cos2a= xcosf(x1);
                         t0   = _mm512_mul_ps(C1772453850905516027298167483341,
                                                              _mm512_mul_ps(b,x0)); // keep
                         x1   = _mm512_sub_ps(cpin,cos2a);
                         t1   = _mm512_mul_ps(_mm512_add_ps(C1772453850905516027298167483341,
                                                            C1772453850905516027298167483341),
                                                                           _mm512_mul_ps(a,spin)); // keep
                         x0   = _mm512_rcp14_ps(x1); // keep
                         ear  = _mm512_mul_ps(_mm512_add_ps(t0,t1),x0);
                         t0   = _mm512_mul_ps(ear,cer);
                         t1   = _mm512_mul_ps(ear,cei);
                         rcs  = cabs_zmm16r4(t0,t1);
                         return (rcs);                      
                 }
                 
                 
                 /*
                     High frequency approximations.
                     Backscatter RCS of conical frustum
                     for |theta| = PI/2-alpha
                     Formula 8.1-96
                 */
                 
                 
               
                   __m512 rcs_f8196_zmm16r4(const __m512 k0,
                                            const __m512 alp,
                                            const __m512 a,
                                            const __m512 b) {
                                            
                         
                          const __m512 C0444444444444444444444444444444 = 
                                                        _mm512_set1_ps(0.444444444444444444444444444444f);
                          register __m512 rcs,t0,cosa,cota,x0,x1,a32,bca32,sina,t1;
                          t0    = _mm512_mul_ps(C0444444444444444444444444444444,k0);
                          cosa  = xcosf(alp);
                          a32   = _mm512_mul_ps(a,_mm512_sqrt_ps(a));
                          x0    = _mm512_mul_ps(b,cosa);
                          sina  = xsinf(alp);
                          bca32 = _mm512_mul_ps(x0,_mm512_sqrt_ps(x0));
                          x1    = _mm512_div_ps(cosa,sina);
                          cota  = _mm512_mul_ps(x1,x1);
                          t1    = _mm512_mul_ps(t0,_mm512_mul_ps(cosa,cota));
                          x0    = _mm512_sub_ps(a32,bca32);
                          rcs   = _mm512_mul_ps(t1,_mm512_mul_ps(x0,x0));
                          return (rcs);
                 }
                 
                 
               
                   __m512 rcs_f8196_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
                                              const float * __restrict __ATTR_ALIGN__(64) palp,
                                              const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb) {
                                            
                         
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          register __m512 alp = _mm512_load_ps(&palp[0]);
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          const __m512 C0444444444444444444444444444444 = 
                                                        _mm512_set1_ps(0.444444444444444444444444444444f);
                          register __m512 rcs,t0,cosa,cota,x0,x1,a32,bca32,sina,t1;
                          t0    = _mm512_mul_ps(C0444444444444444444444444444444,k0);
                          cosa  = xcosf(alp);
                          a32   = _mm512_mul_ps(a,_mm512_sqrt_ps(a));
                          x0    = _mm512_mul_ps(b,cosa);
                          sina  = xsinf(alp);
                          bca32 = _mm512_mul_ps(x0,_mm512_sqrt_ps(x0));
                          x1    = _mm512_div_ps(cosa,sina);
                          cota  = _mm512_mul_ps(x1,x1);
                          t1    = _mm512_mul_ps(t0,_mm512_mul_ps(cosa,cota));
                          x0    = _mm512_sub_ps(a32,bca32);
                          rcs   = _mm512_mul_ps(t1,_mm512_mul_ps(x0,x0));
                          return (rcs);
                 }
                 
                 
                
                   __m512 rcs_f8196_zmm16r4_u(const float * __restrict pk0,
                                              const float * __restrict palp,
                                              const float * __restrict pa,
                                              const float * __restrict pb) {
                                            
                         
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          register __m512 alp = _mm512_loadu_ps(&palp[0]);
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          const __m512 C0444444444444444444444444444444 = 
                                                        _mm512_set1_ps(0.444444444444444444444444444444f);
                          register __m512 rcs,t0,cosa,cota,x0,x1,a32,bca32,sina,t1;
                          t0    = _mm512_mul_ps(C0444444444444444444444444444444,k0);
                          cosa  = xcosf(alp);
                          a32   = _mm512_mul_ps(a,_mm512_sqrt_ps(a));
                          x0    = _mm512_mul_ps(b,cosa);
                          sina  = xsinf(alp);
                          bca32 = _mm512_mul_ps(x0,_mm512_sqrt_ps(x0));
                          x1    = _mm512_div_ps(cosa,sina);
                          cota  = _mm512_mul_ps(x1,x1);
                          t1    = _mm512_mul_ps(t0,_mm512_mul_ps(cosa,cota));
                          x0    = _mm512_sub_ps(a32,bca32);
                          rcs   = _mm512_mul_ps(t1,_mm512_mul_ps(x0,x0));
                          return (rcs);
                 }
                 
                 
                 /*
                     High frequency approximations.
                     Backscatter RCS of conical frustum
                     for 0<|theta|<alpha
                     Perpendicular RCS.
                     Formula 8.1-94
                 */
                 
                 
             /*      __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
	           __m512 rcs_perpendic_f8194_zmm16r4(const __m512 h,
	                                        const __m512 l,
	                                        const __m512 b,
	                                        const __m512 a,
	                                        const __m512 k0,
	                                        const __m512 tht,
	                                        const __m512 alp) {
	                                 
	                                  
	                 const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);  
                         const __m512 C15                              = 
                                                     _mm512_set1_ps(1.5f); 
                         const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                         const __m512 C20                              =
                                                     _mm512_set1_ps(2.0f);
                         register __m512 pin,n,invn,spin,cos1,k02,cos2,sint,cost;
                         register __m512 ear,eai1,eai2,eai3,cer1,cei1,sk02,sacs;
                         register __m512 cer2,cei2,cer3,cei3,x0,x1,x2,x3,atant;
                         register __m512 cpin1,cpin2,trm1,trm2,rcs;
                         __m512 t0r,t0i,t1r,t1i,a2;
                         hlb  = _mm512_sub_ps(h,_mm512_add_ps(l,b));
                         sint = xsinf(tht);
                         k02  = _mm512_add_ps(k0,k0);
                         n    = _mm512_mul_ps(C15,_mm512_div_ps(alp,  
                                                           C314159265358979323846264338328));   
                         csct = _mm512_rcp14_ps(sint);
                         a2   = _mm512_mul_ps(a,C05);
                         ear  = _mm512_setzero_ps();
                         sk02 = _mm512_sqrt_ps(_mm512_mul_ps(k0,C05));
                         x0   = _mm512_mul_ps(hlb,_mm512_sub_ps(cost,b));
                         invn = _mm512_rcp14_ps(n);
                         //x2   = _mm512_mul_ps(a,C05);
                         eai  = _mm512_mul_ps(k02,x0);
                         tant = xtanf(tht);
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         sacs = _mm512_sqrt_ps(_mm512_mul_ps(a2,csct));
                         atant= _mm512_mul_ps(a,tant);
                         cost = xcosf(tht);
                         x0   = _mm512_mul_ps(b,C1772453850905516027298167483341);
                         cexp_zmm16r4(ear,eai,&cer1,&cei1);
                         cer1 = _mm512_mul_ps(x0,cer1);
                         spin = xsinf(pin);
                         cei1 = _mm512_mul_ps(x0,cei1);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_sub_ps(h,atant),cost);
                         eai2 = _mm512_fmadd_ps(k02,x1,C078539816339744830961566084582);
                         cexp_zmm16r4(ear,eai2,&cer2,&cei);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_mul_ps(x0,sacs);
                         cer2 = _mm512_mul_ps(cer2,x1);
                         cei2 = _mm512_mul_ps(cei2,x1);
                         cpin1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,C10));
                         x2   = _mm512_mul_ps(C20,_mm512_add_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x2,invn));
                         x3   = _mm512_rcp14_ps(_mm512_sub_ps(cpin,cpin2));
                         trm1 = _mm512_sub_ps(cpin1,x3);
                         cmul_zmm16r4(cer1,cei1,cer2,cei2,&t0r,&t0i);
                         t0r  = _mm512_mul_ps(t0r,trm1);
                         t0i  = _mm512_mul_ps(t0i,trm1);
                         x0   = _mm512_mul_ps(C20,_mm512_sub_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x0,invn));
                         x1   = _mm512_rcp14_ps(cpin2);
                         trm2 = _mm512_sub_ps(cpin1,x1);
                         x2   = _mm512_fmadd_ps(cost,_mm512_mul_ps(k02,
                                                               _mm512_add_ps(h,atant)));
                         eai3 = _mm512_add_ps(C078539816339744830961566084582,x2);
                         cexp_zmm16r4(ear,ea3,&cer3,&cei3);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_sqrt_ps(_mm512_mul_ps(gms::math::
                                                                  negate_zmm16r4(a2),csct));
                         x2   = _mm512_mul_ps(x0,x1);
                         cer3 = _mm512_mul_ps(_mm512_mul_ps(cer3,x2),trm2);
                         cei3 = _mm512_mul_ps(_mm512_mul_ps(cei3,x2),trm2);
                         cmul_zmm16r4(t0r,t0i,cer3,cei3,&t1r,&t1i);
                         rcs  = cabs_zmm16r4(t1r,t1i);
                         return (rcs);
	        }
	        
	        
	        
	                                  
                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
	           __m512 rcs_perpendic_f8194_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ph,
	                                         const float * __restrict __ATTR_ALIGN__(64) pl,
	                                         const float * __restrict __ATTR_ALIGN__(64) pb,
	                                         const float * __restrict __ATTR_ALIGN__(64) pa,
	                                         const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                         const float * __restrict __ATTR_ALIGN__(64) ptht,
	                                         const float * __restrict __ATTR_ALIGN__(64) palp) {
	                                 
	                  
	                 register __m512 h  = _mm512_load_ps(&ph[0]);
	                 register __m512 l  = _mm512_load_ps(&pl[0]); 
	                 register __m512 b  = _mm512_load_ps(&pb[0]);   
	                 register __m512 a  = _mm512_load_ps(&pa[0]);  
	                 register __m512 k0 = _mm512_load_ps(&pk0[0]);
	                 register __m512 tht= _mm512_load_ps(&ptht[0]); 
	                 register __m512 alp= _mm512_load_ps(&palp[0]);        
	                 const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);  
                         const __m512 C15                              = 
                                                     _mm512_set1_ps(1.5f); 
                         const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                         const __m512 C20                              =
                                                     _mm512_set1_ps(2.0f);
                         __m512 pin,n,invn,spin,cos1,k02,cos2,sint,cost;
                         register __m512 ear,eai1,eai2,eai3,cer1,cei1,sk02,sacs;
                         register __m512 cer2,cei2,cer3,cei3,x0,x1,x2,x3,atant;
                         register __m512 cpin1,cpin2,trm1,trm2,rcs;
                         __m512 t0r,t0i,t1r,t1i,a2;
                         hlb  = _mm512_sub_ps(h,_mm512_add_ps(l,b));
                         sint = xsinf(tht);
                         k02  = _mm512_add_ps(k0,k0);
                         n    = _mm512_mul_ps(C15,_mm512_div_ps(alp,  
                                                           C314159265358979323846264338328));   
                         csct = _mm512_rcp14_ps(sint);
                         a2   = _mm512_mul_ps(a,C05);
                         ear  = _mm512_setzero_ps();
                         sk02 = _mm512_sqrt_ps(_mm512_mul_ps(k0,C05));
                         x0   = _mm512_mul_ps(hlb,_mm512_sub_ps(cost,b));
                         invn = _mm512_rcp14_ps(n);
                         //x2   = _mm512_mul_ps(a,C05);
                         eai  = _mm512_mul_ps(k02,x0);
                         tant = xtanf(tht);
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         sacs = _mm512_sqrt_ps(_mm512_mul_ps(a2,csct));
                         atant= _mm512_mul_ps(a,tant);
                         cost = xcosf(tht);
                         x0   = _mm512_mul_ps(b,C1772453850905516027298167483341);
                         cexp_zmm16r4(ear,eai,&cer1,&cei1);
                         cer1 = _mm512_mul_ps(x0,cer1);
                         spin = xsinf(pin);
                         cei1 = _mm512_mul_ps(x0,cei1);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_sub_ps(h,atant),cost);
                         eai2 = _mm512_fmadd_ps(k02,x1,C078539816339744830961566084582);
                         cexp_zmm16r4(ear,eai2,&cer2,&cei);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_mul_ps(x0,sacs);
                         cer2 = _mm512_mul_ps(cer2,x1);
                         cei2 = _mm512_mul_ps(cei2,x1);
                         cpin1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,C10));
                         x2   = _mm512_mul_ps(C20,_mm512_add_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x2,invn));
                         x3   = _mm512_rcp14_ps(_mm512_sub_ps(cpin,cpin2));
                         trm1 = _mm512_sub_ps(cpin1,x3);
                         cmul_zmm16r4(cer1,cei1,cer2,cei2,&t0r,&t0i);
                         t0r  = _mm512_mul_ps(t0r,trm1);
                         t0i  = _mm512_mul_ps(t0i,trm1);
                         x0   = _mm512_mul_ps(C20,_mm512_sub_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x0,invn));
                         x1   = _mm512_rcp14_ps(cpin2);
                         trm2 = _mm512_sub_ps(cpin1,x1);
                         x2   = _mm512_fmadd_ps(cost,_mm512_mul_ps(k02,
                                                               _mm512_add_ps(h,atant)));
                         eai3 = _mm512_add_ps(C078539816339744830961566084582,x2);
                         cexp_zmm16r4(ear,ea3,&cer3,&cei3);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_sqrt_ps(_mm512_mul_ps(gms::math::
                                                                  negate_zmm16r4(a2),csct));
                         x2   = _mm512_mul_ps(x0,x1);
                         cer3 = _mm512_mul_ps(_mm512_mul_ps(cer3,x2),trm2);
                         cei3 = _mm512_mul_ps(_mm512_mul_ps(cei3,x2),trm2);
                         cmul_zmm16r4(t0r,t0i,cer3,cei3,&t1r,&t1i);
                         rcs  = cabs_zmm16r4(t1r,t1i);
                         return (rcs);
	        }
	        
	        
	        
	           __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
	           __m512 rcs_perpendic_f8194_zmm16r4_u(    const float * __restrict  ph,
	                                                    const float * __restrict  pl,
	                                                    const float * __restrict  pb,
	                                                    const float * __restrict  pa,
	                                                    const float * __restrict  pk0,
	                                                    const float * __restrict  ptht,
	                                                    const float * __restrict  palp) {
	                                 
	                  
	                 register __m512 h  = _mm512_loadu_ps(&ph[0]);
	                 register __m512 l  = _mm512_loadu_ps(&pl[0]); 
	                 register __m512 b  = _mm512_loadu_ps(&pb[0]);   
	                 register __m512 a  = _mm512_loadu_ps(&pa[0]);  
	                 register __m512 k0 = _mm512_loadu_ps(&pk0[0]);
	                 register __m512 tht= _mm512_loadu_ps(&ptht[0]); 
	                 register __m512 alp= _mm512_loadu_ps(&palp[0]);        
	                 const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);  
                         const __m512 C15                              = 
                                                     _mm512_set1_ps(1.5f); 
                         const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                         const __m512 C20                              =
                                                     _mm512_set1_ps(2.0f);
                         __m512 pin,n,invn,spin,cos1,k02,cos2,sint,cost;
                         register __m512 ear,eai1,eai2,eai3,cer1,cei1,sk02,sacs;
                         register __m512 cer2,cei2,cer3,cei3,x0,x1,x2,x3,atant;
                         register __m512 cpin1,cpin2,trm1,trm2,rcs;
                         __m512 t0r,t0i,t1r,t1i,a2;
                         hlb  = _mm512_sub_ps(h,_mm512_add_ps(l,b));
                         sint = xsinf(tht);
                         k02  = _mm512_add_ps(k0,k0);
                         n    = _mm512_mul_ps(C15,_mm512_div_ps(alp,  
                                                           C314159265358979323846264338328));   
                         csct = _mm512_rcp14_ps(sint);
                         a2   = _mm512_mul_ps(a,C05);
                         ear  = _mm512_setzero_ps();
                         sk02 = _mm512_sqrt_ps(_mm512_mul_ps(k0,C05));
                         x0   = _mm512_mul_ps(hlb,_mm512_sub_ps(cost,b));
                         invn = _mm512_rcp14_ps(n);
                         //x2   = _mm512_mul_ps(a,C05);
                         eai  = _mm512_mul_ps(k02,x0);
                         tant = xtanf(tht);
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         sacs = _mm512_sqrt_ps(_mm512_mul_ps(a2,csct));
                         atant= _mm512_mul_ps(a,tant);
                         cost = xcosf(tht);
                         x0   = _mm512_mul_ps(b,C1772453850905516027298167483341);
                         cexp_zmm16r4(ear,eai,&cer1,&cei1);
                         cer1 = _mm512_mul_ps(x0,cer1);
                         spin = xsinf(pin);
                         cei1 = _mm512_mul_ps(x0,cei1);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_sub_ps(h,atant),cost);
                         eai2 = _mm512_fmadd_ps(k02,x1,C078539816339744830961566084582);
                         cexp_zmm16r4(ear,eai2,&cer2,&cei);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_mul_ps(x0,sacs);
                         cer2 = _mm512_mul_ps(cer2,x1);
                         cei2 = _mm512_mul_ps(cei2,x1);
                         cpin1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,C10));
                         x2   = _mm512_mul_ps(C20,_mm512_add_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x2,invn));
                         x3   = _mm512_rcp14_ps(_mm512_sub_ps(cpin,cpin2));
                         trm1 = _mm512_sub_ps(cpin1,x3);
                         cmul_zmm16r4(cer1,cei1,cer2,cei2,&t0r,&t0i);
                         t0r  = _mm512_mul_ps(t0r,trm1);
                         t0i  = _mm512_mul_ps(t0i,trm1);
                         x0   = _mm512_mul_ps(C20,_mm512_sub_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x0,invn));
                         x1   = _mm512_rcp14_ps(cpin2);
                         trm2 = _mm512_sub_ps(cpin1,x1);
                         x2   = _mm512_fmadd_ps(cost,_mm512_mul_ps(k02,
                                                               _mm512_add_ps(h,atant)));
                         eai3 = _mm512_add_ps(C078539816339744830961566084582,x2);
                         cexp_zmm16r4(ear,ea3,&cer3,&cei3);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_sqrt_ps(_mm512_mul_ps(gms::math::
                                                                  negate_zmm16r4(a2),csct));
                         x2   = _mm512_mul_ps(x0,x1);
                         cer3 = _mm512_mul_ps(_mm512_mul_ps(cer3,x2),trm2);
                         cei3 = _mm512_mul_ps(_mm512_mul_ps(cei3,x2),trm2);
                         cmul_zmm16r4(t0r,t0i,cer3,cei3,&t1r,&t1i);
                         rcs  = cabs_zmm16r4(t1r,t1i);
                         return (rcs);
	        }*/
	        
	        
	        
	         /*
                     High frequency approximations.
                     Backscatter RCS of conical frustum
                     for 0<|theta|<alpha
                     Parallel RCS.
                     Formula 8.1-94
                 */
                 
                 
             /*      __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
	           __m512 rcs_parallel_f8194_zmm16r4(const __m512 h,
	                                             const __m512 l,
	                                             const __m512 b,
	                                             const __m512 a,
	                                             const __m512 k0,
	                                             const __m512 tht,
	                                             const __m512 alp) {
	                                 
	                                  
	                 const __m512 C314159265358979323846264338328  = 
                                                     _mm512_set1_ps(3.14159265358979323846264338328f); 
                         const __m512 C1772453850905516027298167483341 = 
                                                     _mm512_set1_ps(1.772453850905516027298167483341f);
                         const __m512 C078539816339744830961566084582  = 
                                                     _mm512_set1_ps(0.78539816339744830961566084582f);
                         const __m512 C10                              = 
                                                     _mm512_set1_ps(1.0f);  
                         const __m512 C15                              = 
                                                     _mm512_set1_ps(1.5f); 
                         const __m512 C05                              = 
                                                     _mm512_set1_ps(0.5f);
                         const __m512 C20                              =
                                                     _mm512_set1_ps(2.0f);
                         register __m512 pin,n,invn,spin,cos1,k02,cos2,sint,cost;
                         register __m512 ear,eai1,eai2,eai3,cer1,cei1,sk02,sacs;
                         register __m512 cer2,cei2,cer3,cei3,x0,x1,x2,x3,atant;
                         register __m512 cpin1,cpin2,trm1,trm2,rcs;
                         __m512 t0r,t0i,t1r,t1i,a2;
                         hlb  = _mm512_sub_ps(h,_mm512_add_ps(l,b));
                         sint = xsinf(tht);
                         k02  = _mm512_add_ps(k0,k0);
                         n    = _mm512_mul_ps(C15,_mm512_div_ps(alp,  
                                                           C314159265358979323846264338328));   
                         csct = _mm512_rcp14_ps(sint);
                         a2   = _mm512_mul_ps(a,C05);
                         ear  = _mm512_setzero_ps();
                         sk02 = _mm512_sqrt_ps(_mm512_mul_ps(k0,C05));
                         x0   = _mm512_mul_ps(hlb,_mm512_sub_ps(cost,b));
                         invn = _mm512_rcp14_ps(n);
                         //x2   = _mm512_mul_ps(a,C05);
                         eai  = _mm512_mul_ps(k02,x0);
                         tant = xtanf(tht);
                         pin  = _mm512_mul_ps(C314159265358979323846264338328,invn);
                         sacs = _mm512_sqrt_ps(_mm512_mul_ps(a2,csct));
                         atant= _mm512_mul_ps(a,tant);
                         cost = xcosf(tht);
                         x0   = _mm512_mul_ps(b,C1772453850905516027298167483341);
                         cexp_zmm16r4(ear,eai,&cer1,&cei1);
                         cer1 = _mm512_mul_ps(x0,cer1);
                         spin = xsinf(pin);
                         cei1 = _mm512_mul_ps(x0,cei1);
                         cpin = xcosf(pin);
                         x1   = _mm512_mul_ps(_mm512_sub_ps(h,atant),cost);
                         eai2 = _mm512_fmadd_ps(k02,x1,C078539816339744830961566084582);
                         cexp_zmm16r4(ear,eai2,&cer2,&cei);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_mul_ps(x0,sacs);
                         cer2 = _mm512_mul_ps(cer2,x1);
                         cei2 = _mm512_mul_ps(cei2,x1);
                         cpin1= _mm512_rcp14_ps(_mm512_sub_ps(cpin,C10));
                         x2   = _mm512_mul_ps(C20,_mm512_add_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x2,invn));
                         x3   = _mm512_rcp14_ps(_mm512_sub_ps(cpin,cpin2));
                         trm1 = _mm512_add_ps(cpin1,x3);
                         cmul_zmm16r4(cer1,cei1,cer2,cei2,&t0r,&t0i);
                         t0r  = _mm512_mul_ps(t0r,trm1);
                         t0i  = _mm512_mul_ps(t0i,trm1);
                         x0   = _mm512_mul_ps(C20,_mm512_sub_ps(alp,tht));
                         cpin2= xcosf(_mm512_mul_ps(x0,invn));
                         x1   = _mm512_rcp14_ps(cpin2);
                         trm2 = _mm512_add_ps(cpin1,x1);
                         x2   = _mm512_fmadd_ps(cost,_mm512_mul_ps(k02,
                                                               _mm512_add_ps(h,atant)));
                         eai3 = _mm512_add_ps(C078539816339744830961566084582,x2);
                         cexp_zmm16r4(ear,ea3,&cer3,&cei3);
                         x0   = _mm512_div_ps(spin,_mm512_mul_ps(n,sk02));
                         x1   = _mm512_sqrt_ps(_mm512_mul_ps(gms::math::
                                                                  negate_zmm16r4(a2),csct));
                         x2   = _mm512_mul_ps(x0,x1);
                         cer3 = _mm512_mul_ps(_mm512_mul_ps(cer3,x2),trm2);
                         cei3 = _mm512_mul_ps(_mm512_mul_ps(cei3,x2),trm2);
                         cmul_zmm16r4(t0r,t0i,cer3,cei3,&t1r,&t1i);
                         rcs  = cabs_zmm16r4(t1r,t1i);
                         return (rcs);
	        }
	        */
	        
	        
	        /*
	             Model 9B4 (Peake's Model)
	             Model resembling many natural grass-like structures like
	             forests,grass,wheat fields, etc.
	             Helper formula coefficient B(gamma).
	             Formula 9.1-37
	        */
	        
	        
	        
	          
	           __m512 coef_Bg_f9137_zmm16r4(const __m512 A,
	                                        const __m512 N,
	                                        const __m512 k0,
	                                        const __m512 epsr,
	                                        const __m512 epsi,
	                                        const __m512 thti,
	                                        const __m512 thts,
	                                        const __m512 phis,
	                                        const int pol) {
	                                        
	                  const __m512 C06          = _mm512_set1_ps(0.6f);
	                  const __m512 C01875       = _mm512_set1_ps(0.1875f); // 3/16
	                  const __m512 C87964594300514210676954014731826 = 
	                                            = _mm512_set1_ps(87.964594300514210676954014731826f);
	                  const __m512 C20          = _mm512_set1_ps(2.0f);
	                  const __m512 C10          = _mm512_set1_ps(1.0f);
	                  const __m512 C30          = _mm512_set1_ps(3.0f);
	                  register __m512 Bg,t,t2,cthti,cthts,sthti,sthts,cphis;
	                  register __m512 AN,Ak0,num,den,alp,x0,x1,x2,x3,x4,secti;
	                  AN    = _mm512_mul_ps(A,N);
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x1    = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  x2    = _mm512_fmadd_ps(epsi,epsi,
	                                               _mm512_mul_ps(x1,x1));
	                  t2    = _mm512_mul_ps(t,t);
	                  secti = _mm512_rcp14_ps(cthti);
	                  sthti = xsinf(thti);
	                  x0    = _mm512_fmadd_ps(t2,C30,C10);
	                  cthts = xcosf(thts);
	                  Ak0   = _mm512_mul_ps(A,k0);
	                  x1    = _mm512_mul_ps(AN,_mm512_mul_ps(Ak0,AK0));
	                  num   = _mm512_mul_ps(x1,x2);
	                  if(pol == 0) {
	                     x1 = _mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(x1,x0);
	                     alp= _mm512_mul_ps(k0,x2);
	                  }
	                  else if(pol == 1) {
	                     x1 = mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(sthti,sthti);
	                     x3 = _mm512_sub_ps(c10,t2);
	                     alp= _mm512_fmadd_ps(x1,x0,_mm512_mul_ps(x2,x3));
	                     alp= _mm512_mul_ps(k0,alp);
	                  }
	                  x0 = _mm512_div_ps(alp,k0);
	                  x2 = _mm512_add_ps(cthti,cthts);
	                  x1 = _mm512_fmadd_ps(C06,_mm512_mul_ps(x0,x0),
	                                                     _mm512_mul_ps(C30,
	                                                                   _mm512_mul_ps(x2,x2)));
	                  x3 = _mm512_fmadd_ps(sthti,sthti,_mm512_mul_ps(sthts,sthts));
	                  x4 = _mm512_mul_ps(C20,_mm512_mul_ps(sthti,sthts));
	                  x0 = _mm512_mul_ps(x4,cthts);
	                  den= _mm512_mul_ps(C87964594300514210676954014731826,
	                                                             _mm512_add_ps(x1,x0));
	                  
	                  Bg = _mm512_div_ps(num,den);
	                  return (Bg);
	       }
	       
	       
	       
	        
	           __m512 coef_Bg_f9137_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pA,
	                                          const float * __restrict __ATTR_ALIGN__(64) pN,
	                                          const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                          const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                          const int pol) {
	                         
	                  register __m512 A   = _mm512_load_ps(&pA[0]);
	                  register __m512 N   = _mm512_load_ps(&pN[0]); 
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 thti= _mm512_load_ps(&pthti[0]);
	                  register __m512 thts= _mm512_load_ps(&pthts[0]);
	                  register __m512 phis= _mm512_load_ps(&pphis[0]);              
	                  const __m512 C06          = _mm512_set1_ps(0.6f);
	                  const __m512 C01875       = _mm512_set1_ps(0.1875f); // 3/16
	                  const __m512 C87964594300514210676954014731826 = 
	                                            = _mm512_set1_ps(87.964594300514210676954014731826f);
	                  const __m512 C20          = _mm512_set1_ps(2.0f);
	                  const __m512 C10          = _mm512_set1_ps(1.0f);
	                  const __m512 C30          = _mm512_set1_ps(3.0f);
	                  register __m512 Bg,t,t2,cthti,cthts,sthti,sthts,cphis;
	                  register __m512 AN,Ak0,num,den,alp,x0,x1,x2,x3,x4,secti;
	                  AN    = _mm512_mul_ps(A,N);
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x1    = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  x2    = _mm512_fmadd_ps(epsi,epsi,
	                                               _mm512_mul_ps(x1,x1));
	                  t2    = _mm512_mul_ps(t,t);
	                  secti = _mm512_rcp14_ps(cthti);
	                  sthti = xsinf(thti);
	                  x0    = _mm512_fmadd_ps(t2,C30,C10);
	                  cthts = xcosf(thts);
	                  Ak0   = _mm512_mul_ps(A,k0);
	                  x1    = _mm512_mul_ps(AN,_mm512_mul_ps(Ak0,AK0));
	                  num   = _mm512_mul_ps(x1,x2);
	                  if(pol == 0) {
	                     x1 = _mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(x1,x0);
	                     alp= _mm512_mul_ps(k0,x2);
	                  }
	                  else if(pol == 1) {
	                     x1 = mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(sthti,sthti);
	                     x3 = _mm512_sub_ps(c10,t2);
	                     alp= _mm512_fmadd_ps(x1,x0,_mm512_mul_ps(x2,x3));
	                     alp= _mm512_mul_ps(k0,alp);
	                  }
	                  x0 = _mm512_div_ps(alp,k0);
	                  x2 = _mm512_add_ps(cthti,cthts);
	                  x1 = _mm512_fmadd_ps(C06,_mm512_mul_ps(x0,x0),
	                                                     _mm512_mul_ps(C30,
	                                                                   _mm512_mul_ps(x2,x2)));
	                  x3 = _mm512_fmadd_ps(sthti,sthti,_mm512_mul_ps(sthts,sthts));
	                  x4 = _mm512_mul_ps(C20,_mm512_mul_ps(sthti,sthts));
	                  x0 = _mm512_mul_ps(x4,cthts);
	                  den= _mm512_mul_ps(C87964594300514210676954014731826,
	                                                             _mm512_add_ps(x1,x0));
	                  
	                  Bg = _mm512_div_ps(num,den);
	                  return (Bg);
	       }
	       
	       
	          
	           __m512 coef_Bg_f9137_zmm16r4_u(const float * __restrict  pA,
	                                          const float * __restrict  pN,
	                                          const float * __restrict  pk0,
	                                          const float * __restrict  pepsr,
	                                          const float * __restrict  pepsi,
	                                          const float * __restrict  pthti,
	                                          const float * __restrict  pthts,
	                                          const float * __restrict  pphis,
	                                          const int pol) {
	                         
	                  register __m512 A   = _mm512_loadu_ps(&pA[0]);
	                  register __m512 N   = _mm512_loadu_ps(&pN[0]); 
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 thti= _mm512_loadu_ps(&pthti[0]);
	                  register __m512 thts= _mm512_loadu_ps(&pthts[0]);
	                  register __m512 phis= _mm512_loadu_ps(&pphis[0]);              
	                  const __m512 C06          = _mm512_set1_ps(0.6f);
	                  const __m512 C01875       = _mm512_set1_ps(0.1875f); // 3/16
	                  const __m512 C87964594300514210676954014731826 = 
	                                            = _mm512_set1_ps(87.964594300514210676954014731826f);
	                  const __m512 C20          = _mm512_set1_ps(2.0f);
	                  const __m512 C10          = _mm512_set1_ps(1.0f);
	                  const __m512 C30          = _mm512_set1_ps(3.0f);
	                  register __m512 Bg,t,t2,cthti,cthts,sthti,sthts,cphis;
	                  register __m512 AN,Ak0,num,den,alp,x0,x1,x2,x3,x4,secti;
	                  AN    = _mm512_mul_ps(A,N);
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x1    = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  x2    = _mm512_fmadd_ps(epsi,epsi,
	                                               _mm512_mul_ps(x1,x1));
	                  t2    = _mm512_mul_ps(t,t);
	                  secti = _mm512_rcp14_ps(cthti);
	                  sthti = xsinf(thti);
	                  x0    = _mm512_fmadd_ps(t2,C30,C10);
	                  cthts = xcosf(thts);
	                  Ak0   = _mm512_mul_ps(A,k0);
	                  x1    = _mm512_mul_ps(AN,_mm512_mul_ps(Ak0,AK0));
	                  num   = _mm512_mul_ps(x1,x2);
	                  if(pol == 0) {
	                     x1 = _mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(x1,x0);
	                     alp= _mm512_mul_ps(k0,x2);
	                  }
	                  else if(pol == 1) {
	                     x1 = mm512_mul_ps(_mm512_mul_ps(C01875,AN),
	                                                  _mm512_mul_ps(epsi,secti));
	                     x2 = _mm512_mul_ps(sthti,sthti);
	                     x3 = _mm512_sub_ps(c10,t2);
	                     alp= _mm512_fmadd_ps(x1,x0,_mm512_mul_ps(x2,x3));
	                     alp= _mm512_mul_ps(k0,alp);
	                  }
	                  x0 = _mm512_div_ps(alp,k0);
	                  x2 = _mm512_add_ps(cthti,cthts);
	                  x1 = _mm512_fmadd_ps(C06,_mm512_mul_ps(x0,x0),
	                                                     _mm512_mul_ps(C30,
	                                                                   _mm512_mul_ps(x2,x2)));
	                  x3 = _mm512_fmadd_ps(sthti,sthti,_mm512_mul_ps(sthts,sthts));
	                  x4 = _mm512_mul_ps(C20,_mm512_mul_ps(sthti,sthts));
	                  x0 = _mm512_mul_ps(x4,cthts);
	                  den= _mm512_mul_ps(C87964594300514210676954014731826,
	                                                             _mm512_add_ps(x1,x0));
	                  
	                  Bg = _mm512_div_ps(num,den);
	                  return (Bg);
	       }
	       
	       
	       /*
	             Model 9B4 (Peake's Model)
	             Model resembling many natural grass-like structures like
	             forests,grass,wheat fields, etc.
	             Bistatic RCS (hh) polarized per unit surface area.
	             Formula 9.1-33
	       
	       */
	       
	       
	       
	           __m512 rcs_hh_f9133_zmm16r4( const __m512 A,
	                                        const __m512 N,
	                                        const __m512 k0,
	                                        const __m512 epsr,
	                                        const __m512 epsi,
	                                        const __m512 thti,
	                                        const __m512 thts,
	                                        const __m512 phis,
	                                        const int pol) {
	                    
	                  const __m512 C10 = _mm512_set1_ps(1.0f);                    
	                  const __m512 C30 = _mm512_set1_ps(3.0f);
	                  const __m512 C20 = _mm512_set1_ps(2.0f);
	                  const __m512 C80 = _mm512_set1_ps(8.0f);
	                  const __m512 C100= _mm512_set1_ps(10.0f);
	                  const __m512 C240= _mm512_set1_ps(24.0f);
	                  const __m512 C230= _mm512_set1_ps(23.0f);
	                  register rcs,Bg,sphis,x0,t,t2,trm1,trm2,trm3;
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x0    = xsinf(phis);
	                  Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                  t2    = _mm512_mul_ps(t,t);
	                  sphis = _mm512_mul_ps(x0,x0); 
	                  trm1  = _mm512_sub_ps(C30,_mm512_mul_ps(C20,sphis));
	                  trm2  = _mm512_mul_ps(t,_mm512_sub_ps(C80,
	                                                      _mm512_mul_ps(C100,sphis)));
	                  trm3  = _mm512_mul_ps(t2,_mm512_sub_ps(C240,
	                                                      _mm512_mul_ps(C230,sphis)));
	                  x0    = _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                  rcs   = _mm512_mul_ps(Bg,x0);
	                  return (rcs);                             
	       }
	       
	       
	       
	          
	           __m512 rcs_hh_f9133_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pA,
	                                          const float * __restrict __ATTR_ALIGN__(64) pN,
	                                          const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                          const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                          const int pol) {
	                         
	                  register __m512 A   = _mm512_load_ps(&pA[0]);
	                  register __m512 N   = _mm512_load_ps(&pN[0]); 
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 thti= _mm512_load_ps(&pthti[0]);
	                  register __m512 thts= _mm512_load_ps(&pthts[0]);
	                  register __m512 phis= _mm512_load_ps(&pphis[0]); 
	                    
	                  const __m512 C10 = _mm512_set1_ps(1.0f);                    
	                  const __m512 C30 = _mm512_set1_ps(3.0f);
	                  const __m512 C20 = _mm512_set1_ps(2.0f);
	                  const __m512 C80 = _mm512_set1_ps(8.0f);
	                  const __m512 C100= _mm512_set1_ps(10.0f);
	                  const __m512 C240= _mm512_set1_ps(24.0f);
	                  const __m512 C230= _mm512_set1_ps(23.0f);
	                  register rcs,Bg,sphis,x0,t,t2,trm1,trm2,trm3;
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x0    = xsinf(phis);
	                  Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                  t2    = _mm512_mul_ps(t,t);
	                  sphis = _mm512_mul_ps(x0,x0); 
	                  trm1  = _mm512_sub_ps(C30,_mm512_mul_ps(C20,sphis));
	                  trm2  = _mm512_mul_ps(t,_mm512_sub_ps(C80,
	                                                      _mm512_mul_ps(C100,sphis)));
	                  trm3  = _mm512_mul_ps(t2,_mm512_sub_ps(C240,
	                                                      _mm512_mul_ps(C230,sphis)));
	                  x0    = _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                  rcs   = _mm512_mul_ps(Bg,x0);
	                  return (rcs);                             
	       }
	       
	       
	       
	         
	           __m512 rcs_hh_f9133_zmm16r4_u( const float * __restrict pA,
	                                          const float * __restrict pN,
	                                          const float * __restrict pk0,
	                                          const float * __restrict pepsr,
	                                          const float * __restrict pepsi,
	                                          const float * __restrict pthti,
	                                          const float * __restrict pthts,
	                                          const float * __restrict pphis,
	                                          const int pol) {
	                         
	                  register __m512 A   = _mm512_loadu_ps(&pA[0]);
	                  register __m512 N   = _mm512_loadu_ps(&pN[0]); 
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 thti= _mm512_loadu_ps(&pthti[0]);
	                  register __m512 thts= _mm512_loadu_ps(&pthts[0]);
	                  register __m512 phis= _mm512_loadu_ps(&pphis[0]); 
	                    
	                  const __m512 C10 = _mm512_set1_ps(1.0f);                    
	                  const __m512 C30 = _mm512_set1_ps(3.0f);
	                  const __m512 C20 = _mm512_set1_ps(2.0f);
	                  const __m512 C80 = _mm512_set1_ps(8.0f);
	                  const __m512 C100= _mm512_set1_ps(10.0f);
	                  const __m512 C240= _mm512_set1_ps(24.0f);
	                  const __m512 C230= _mm512_set1_ps(23.0f);
	                  register rcs,Bg,sphis,x0,t,t2,trm1,trm2,trm3;
	                  t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                  x0    = xsinf(phis);
	                  Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                  t2    = _mm512_mul_ps(t,t);
	                  sphis = _mm512_mul_ps(x0,x0); 
	                  trm1  = _mm512_sub_ps(C30,_mm512_mul_ps(C20,sphis));
	                  trm2  = _mm512_mul_ps(t,_mm512_sub_ps(C80,
	                                                      _mm512_mul_ps(C100,sphis)));
	                  trm3  = _mm512_mul_ps(t2,_mm512_sub_ps(C240,
	                                                      _mm512_mul_ps(C230,sphis)));
	                  x0    = _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                  rcs   = _mm512_mul_ps(Bg,x0);
	                  return (rcs);                             
	       }
	       
	       
	        
	       /*
	             Model 9B4 (Peake's Model)
	             Model resembling many natural grass-like structures like
	             forests,grass,wheat fields, etc.
	             Bistatic RCS (vh) polarized per unit surface area.
	             Formula 9.1-34
	       
	       */
	       
	       
	        
	           __m512 rcs_vh_f9134_zmm16r4( const __m512 A,
	                                        const __m512 N,
	                                        const __m512 k0,
	                                        const __m512 epsr,
	                                        const __m512 epsi,
	                                        const __m512 thti,
	                                        const __m512 thts,
	                                        const __m512 phis,
	                                        const int pol) {
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thts);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thts);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	         
	       
	           __m512 rcs_vh_f9134_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pA,
	                                          const float * __restrict __ATTR_ALIGN__(64) pN,
	                                          const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                          const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                          const int pol) {
	                         
	                    register __m512 A   = _mm512_load_ps(&pA[0]);
	                    register __m512 N   = _mm512_load_ps(&pN[0]); 
	                    register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                    register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                    register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                    register __m512 thti= _mm512_load_ps(&pthti[0]);
	                    register __m512 thts= _mm512_load_ps(&pthts[0]);
	                    register __m512 phis= _mm512_load_ps(&pphis[0]); 
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thts);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thts);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	      
	           __m512 rcs_vh_f9134_zmm16r4_u( const float * __restrict  pA,
	                                          const float * __restrict  pN,
	                                          const float * __restrict  pk0,
	                                          const float * __restrict  pepsr,
	                                          const float * __restrict  pepsi,
	                                          const float * __restrict  pthti,
	                                          const float * __restrict  pthts,
	                                          const float * __restrict  pphis,
	                                          const int pol) {
	                         
	                    register __m512 A   = _mm512_loadu_ps(&pA[0]);
	                    register __m512 N   = _mm512_loadu_ps(&pN[0]); 
	                    register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                    register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                    register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                    register __m512 thti= _mm512_loadu_ps(&pthti[0]);
	                    register __m512 thts= _mm512_loadu_ps(&pthts[0]);
	                    register __m512 phis= _mm512_loadu_ps(&pphis[0]); 
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thts);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thts);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	           /*
	             Model 9B4 (Peake's Model)
	             Model resembling many natural grass-like structures like
	             forests,grass,wheat fields, etc.
	             Bistatic RCS (hv) polarized per unit surface area.
	             Formula 9.1-35
	       
	       */
	       
	       
	         
	           __m512 rcs_hv_f9135_zmm16r4( const __m512 A,
	                                        const __m512 N,
	                                        const __m512 k0,
	                                        const __m512 epsr,
	                                        const __m512 epsi,
	                                        const __m512 thti,
	                                        const __m512 thts,
	                                        const __m512 phis,
	                                        const int pol) {
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thti);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thti);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	         
	          
	           __m512 rcs_hv_f9135_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) pA,
	                                          const float * __restrict __ATTR_ALIGN__(64) pN,
	                                          const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                          const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                          const int pol) {
	                         
	                    register __m512 A   = _mm512_load_ps(&pA[0]);
	                    register __m512 N   = _mm512_load_ps(&pN[0]); 
	                    register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                    register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                    register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                    register __m512 thti= _mm512_load_ps(&pthti[0]);
	                    register __m512 thts= _mm512_load_ps(&pthts[0]);
	                    register __m512 phis= _mm512_load_ps(&pphis[0]); 
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thti);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thti);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	        
	           __m512  rcs_hv_f9135_zmm16r4_u(const float * __restrict pA,
	                                          const float * __restrict  pN,
	                                          const float * __restrict  pk0,
	                                          const float * __restrict  pepsr,
	                                          const float * __restrict  pepsi,
	                                          const float * __restrict  pthti,
	                                          const float * __restrict  pthts,
	                                          const float * __restrict  pphis,
	                                          const int pol) {
	                         
	                    register __m512 A   = _mm512_loadu_ps(&pA[0]);
	                    register __m512 N   = _mm512_loadu_ps(&pN[0]); 
	                    register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                    register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                    register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                    register __m512 thti= _mm512_loadu_ps(&pthti[0]);
	                    register __m512 thts= _mm512_loadu_ps(&pthts[0]);
	                    register __m512 phis= _mm512_loadu_ps(&pphis[0]); 
	                     
	                    const __m512 C10 = _mm512_set1_ps(1.0f);                             
	                    const __m512 C100= _mm512_set1_ps(10.0f);
	                    const __m512 C20 = _mm512_set1_ps(2.0f);   
	                    const __m512 C230= _mm512_set1_ps(23.0f); 
	                    register __m512 rcs,trm1,trm2,trm3,trm4;
	                    register __m512 Bg,sthts,cthts,sphis,x0,x1,t,t2;
	                    t     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));
	                    x0    = xsinf(phis);
	                    Bg    = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol);
	                    t2    = _mm512_mul_ps(t,t);  
	                    x1    = xcosf(thti);
	                    sphis = _mm512_mul_ps(x0,x0); 
	                    cthts = _mm512_mul_ps(x1,x1);
	                    x0    = xsinf(thti);
	                    sthts = _mm512_mul_ps(x0,x0);
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);  
	                    trm1= _mm512_fmadd_ps(sthts,_mm512_mul_ps(C20,cthts),x1);
	                    x0  = _mm512_sub_ps(gms::math::negate_zmm16r4(C20),
	                                                          _mm512_mul_ps(C40,sthts));
	                    trm2= _mm512_mul_ps(t,
	                                     _mm512_fmadd_ps(sphis,
	                                                    _mm512_mul_ps(C100,cthts),x0));
	                    x1  = _mm512_fmadd_ps(sthts,C20,C10);
	                    trm3= _mm512_mul_ps(t2,
	                                      _mm512_fmadd_ps(sphis,
	                                                     _mm512_mul_ps(cthts,C230),x1));
	                    trm4= _mm512_add_ps(trm1,_mm512_add_ps(trm2,trm3));
	                    rcs = _mm512_mul_ps(Bg,trm4);
	                    return (rcs);                
	         }
	         
	         
	            /*
	             Model 9B4 (Peake's Model)
	             Model resembling many natural grass-like structures like
	             forests,grass,wheat fields, etc.
	             Bistatic RCS (vv) polarized per unit surface area.
	             Formula 9.1-36
	       
	       */
	       
	       
	          
	           __m512 rcs_vv_f9136_zmm16r4( const __m512 A,
	                                        const __m512 N,
	                                        const __m512 k0,
	                                        const __m512 epsr,
	                                        const __m512 epsi,
	                                        const __m512 thti,
	                                        const __m512 thts,
	                                        const __m512 phis,
	                                        const int pol) {
	                                        
	                const __m512 C10 = _mm512_set1_ps(1.0f);     
	                const __m512 C20 = _mm512_set1_ps(2.0f);   
	                const __m512 C30 = _mm512_set1_ps(3.0f);
	                const __m512 C120= _mm512_set1_ps(12.0f);
	                const __m512 C140= _mm512_set1_ps(14.0f);
	                const __m512 C350= _mm512_set1_ps(35.0f);
	                register __m512 t,t2,x0,x1,x2,x3,cthti,cthts;
	                register __m512 sphis,cphis,sthts,cthts;
	                register __m512 trm1,trm2,trm3,trm4;
	                register __m512 rcs,Bg,cterm,sterm,sctrm;
	                x0     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));   
	                t      = _mm512_sub_ps(C10,x0);
	                t2     = _mm512_sub_ps(C10,_mm512_mul_ps(x0,x0));
	                Bg     = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol); 
	                sphis  = xsinf(phis);
	                cphis  = xcosf(phis);
	                cthti  = xcosf(thti);
	                sthti  = xsinf(thti);
	                cthts  = xcosf(thts);
	                cterm  = _mm512_mul_ps(cthti,_mm512_mul_ps(cthts,cphis));
	                sthts  = xsinf(thts);
	                sterm  = _mm512_mul_ps(sthti,sthts);
	                sctrm  = _mm512_sub_ps(sterm,cterm);
	                x0     = _mm512_mul_ps(sphis,sphis);
	                x1     = _mm512_mul_ps(cthts,cthts);
	                x2     = _mm512_mul_ps(C30,_mm512_mul_ps(cthti,cthti));
	                x3     = _mm512_sub_ps(C30,_mm512_mul_ps(x0,
	                                                    _mm512_mul_ps(x1,x2)));
	                trm1   = _mm512_fmadd_ps(t2,x3,sctrm);
	                trm2   = _mm512_mul_ps(C120,_mm512_mul_ps(t2,sterm));
	                x0     = _mm512_fmsub_ps(C30,sterm,cterm);
	                trm3   = _mm512_mul_ps(C140,_mm512_mul_ps(t,x0));
	                trm4   = _mm512_mul_ps(_mm512_mul_ps(C350,t2),sctrm);
	                x1     = _mm512_mul_ps(trm1,trm2);
	                x2     = _mm512_add_ps(x1,_mm512_add_ps(trm3,trm4));
	                rcs    = _mm512_mul_ps(Bg,x2);
	                return (rcs);
	         }
	         
	         
	         
	         
	           __m512 rcs_vv_f9136_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) pA,
	                                          const float * __restrict __ATTR_ALIGN__(64) pN,
	                                          const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                          const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                          const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                          const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                          const int pol ) {
	                                      
	                register __m512 A   = _mm512_load_ps(&pA[0]);
	                register __m512 N   = _mm512_load_ps(&pN[0]); 
	                register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                register __m512 thti= _mm512_load_ps(&pthti[0]);
	                register __m512 thts= _mm512_load_ps(&pthts[0]);
	                register __m512 phis= _mm512_load_ps(&pphis[0]);   
	                const __m512 C10 = _mm512_set1_ps(1.0f);     
	                const __m512 C20 = _mm512_set1_ps(2.0f);   
	                const __m512 C30 = _mm512_set1_ps(3.0f);
	                const __m512 C120= _mm512_set1_ps(12.0f);
	                const __m512 C140= _mm512_set1_ps(14.0f);
	                const __m512 C350= _mm512_set1_ps(35.0f);
	                register __m512 t,t2,x0,x1,x2,x3,cthti,cthts;
	                register __m512 sphis,cphis,sthts,cthts;
	                register __m512 trm1,trm2,trm3,trm4;
	                register __m512 rcs,Bg,cterm,sterm,sctrm;
	                x0     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));   
	                t      = _mm512_sub_ps(C10,x0);
	                t2     = _mm512_sub_ps(C10,_mm512_mul_ps(x0,x0));
	                Bg     = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol); 
	                sphis  = xsinf(phis);
	                cphis  = xcosf(phis);
	                cthti  = xcosf(thti);
	                sthti  = xsinf(thti);
	                cthts  = xcosf(thts);
	                cterm  = _mm512_mul_ps(cthti,_mm512_mul_ps(cthts,cphis));
	                sthts  = xsinf(thts);
	                sterm  = _mm512_mul_ps(sthti,sthts);
	                sctrm  = _mm512_sub_ps(sterm,cterm);
	                x0     = _mm512_mul_ps(sphis,sphis);
	                x1     = _mm512_mul_ps(cthts,cthts);
	                x2     = _mm512_mul_ps(C30,_mm512_mul_ps(cthti,cthti));
	                x3     = _mm512_sub_ps(C30,_mm512_mul_ps(x0,
	                                                    _mm512_mul_ps(x1,x2)));
	                trm1   = _mm512_fmadd_ps(t2,x3,sctrm);
	                trm2   = _mm512_mul_ps(C120,_mm512_mul_ps(t2,sterm));
	                x0     = _mm512_fmsub_ps(C30,sterm,cterm);
	                trm3   = _mm512_mul_ps(C140,_mm512_mul_ps(t,x0));
	                trm4   = _mm512_mul_ps(_mm512_mul_ps(C350,t2),sctrm);
	                x1     = _mm512_mul_ps(trm1,trm2);
	                x2     = _mm512_add_ps(x1,_mm512_add_ps(trm3,trm4));
	                rcs    = _mm512_mul_ps(Bg,x2);
	                return (rcs);
	         }
	         
	         
	         
	           
	           __m512 rcs_vv_f9136_zmm16r4_u( const float * __restrict  pA,
	                                          const float * __restrict  pN,
	                                          const float * __restrict  pk0,
	                                          const float * __restrict  pepsr,
	                                          const float * __restrict  pepsi,
	                                          const float * __restrict  pthti,
	                                          const float * __restrict  pthts,
	                                          const float * __restrict  pphis,
	                                          const int pol ) {
	                                      
	                register __m512 A   = _mm512_loadu_ps(&pA[0]);
	                register __m512 N   = _mm512_loadu_ps(&pN[0]); 
	                register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                register __m512 thti= _mm512_loadu_ps(&pthti[0]);
	                register __m512 thts= _mm512_loadu_ps(&pthts[0]);
	                register __m512 phis= _mm512_loadu_ps(&pphis[0]);   
	                const __m512 C10 = _mm512_set1_ps(1.0f);     
	                const __m512 C20 = _mm512_set1_ps(2.0f);   
	                const __m512 C30 = _mm512_set1_ps(3.0f);
	                const __m512 C120= _mm512_set1_ps(12.0f);
	                const __m512 C140= _mm512_set1_ps(14.0f);
	                const __m512 C350= _mm512_set1_ps(35.0f);
	                register __m512 t,t2,x0,x1,x2,x3,cthti,cthts;
	                register __m512 sphis,cphis,sthts,cthts;
	                register __m512 trm1,trm2,trm3,trm4;
	                register __m512 rcs,Bg,cterm,sterm,sctrm;
	                x0     = _mm512_div_ps(C20,_mm512_add_ps(C10,epsr));   
	                t      = _mm512_sub_ps(C10,x0);
	                t2     = _mm512_sub_ps(C10,_mm512_mul_ps(x0,x0));
	                Bg     = coef_Bg_f9137_zmm16r4(A,N,k0,epsr,epsi,thti,thts,phis,pol); 
	                sphis  = xsinf(phis);
	                cphis  = xcosf(phis);
	                cthti  = xcosf(thti);
	                sthti  = xsinf(thti);
	                cthts  = xcosf(thts);
	                cterm  = _mm512_mul_ps(cthti,_mm512_mul_ps(cthts,cphis));
	                sthts  = xsinf(thts);
	                sterm  = _mm512_mul_ps(sthti,sthts);
	                sctrm  = _mm512_sub_ps(sterm,cterm);
	                x0     = _mm512_mul_ps(sphis,sphis);
	                x1     = _mm512_mul_ps(cthts,cthts);
	                x2     = _mm512_mul_ps(C30,_mm512_mul_ps(cthti,cthti));
	                x3     = _mm512_sub_ps(C30,_mm512_mul_ps(x0,
	                                                    _mm512_mul_ps(x1,x2)));
	                trm1   = _mm512_fmadd_ps(t2,x3,sctrm);
	                trm2   = _mm512_mul_ps(C120,_mm512_mul_ps(t2,sterm));
	                x0     = _mm512_fmsub_ps(C30,sterm,cterm);
	                trm3   = _mm512_mul_ps(C140,_mm512_mul_ps(t,x0));
	                trm4   = _mm512_mul_ps(_mm512_mul_ps(C350,t2),sctrm);
	                x1     = _mm512_mul_ps(trm1,trm2);
	                x2     = _mm512_add_ps(x1,_mm512_add_ps(trm3,trm4));
	                rcs    = _mm512_mul_ps(Bg,x2);
	                return (rcs);
	         }
	         
	         
	         
	        /*
	            Gaussian surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (vv) polarization.
	            Formula 9.1-74
	        */
	        
	       
	           __m512 rcs_vv_f9174_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti,
	                                       const __m512 epsr,
	                                       const __m512 epsi,
	                                       const __m512 mur,
	                                       const __m512 mui) {
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	           __m512 rcs_vv_f9174_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                         const float * __restrict __ATTR_ALIGN__(64) ph,
	                                         const float * __restrict __ATTR_ALIGN__(64) pl,
	                                         const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmur,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmui) {
	                        
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_load_ps(&pmur[0]);
	                  register __m512 mui = _mm512_load_ps(&pmui[0]);               
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                   __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	        
	           __m512 rcs_vv_f9174_zmm16r4_u(const float * __restrict  pk0,
	                                         const float * __restrict  ph,
	                                         const float * __restrict  pl,
	                                         const float * __restrict  pthti,
	                                         const float * __restrict  pepsr,
	                                         const float * __restrict  pepsi,
	                                         const float * __restrict  pmur,
	                                         const float * __restrict  pmui) {
	                        
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_loadu_ps(&pmur[0]);
	                  register __m512 mui = _mm512_loadu_ps(&pmui[0]);               
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                   __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	        /*
	            Gaussian surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (hh) polarization.
	            Formula 9.1-75
	        */
	        
	        
	         
	           __m512 rcs_hh_f9175_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti,
	                                       const __m512 epsr,
	                                       const __m512 epsi,
	                                       const __m512 mur,
	                                       const __m512 mui) {
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	         
	           __m512 rcs_hh_f9175_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                         const float * __restrict __ATTR_ALIGN__(64) ph,
	                                         const float * __restrict __ATTR_ALIGN__(64) pl,
	                                         const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmur,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmui) {
	                        
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_load_ps(&pmur[0]);
	                  register __m512 mui = _mm512_load_ps(&pmui[0]);  
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	        
	           __m512 rcs_hh_f9175_zmm16r4_u(  const float * __restrict  pk0,
	                                         const float * __restrict  ph,
	                                         const float * __restrict  pl,
	                                         const float * __restrict  pthti,
	                                         const float * __restrict  pepsr,
	                                         const float * __restrict  pepsi,
	                                         const float * __restrict  pmur,
	                                         const float * __restrict  pmui) {
	                        
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_loadu_ps(&pmur[0]);
	                  register __m512 mui = _mm512_loadu_ps(&pmui[0]);  
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_mul_ps(k02,_mm512_mul_ps(l2,sthti));   
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C40,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	         /*
	            Gaussian surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (hv) polarization.
	            Formula 9.1-76
	        */
	        
	        
	         
	           __m512 rcs_hv_f9176_zmm16r4() { 
	           
	                return _mm512_setzero_ps();
	         } 
	         
	         
	         
	         /*
	            Exponential surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (vv) polarization.
	            Formula 9.1-77
	        */
	        
	        
	         
	           __m512 rcs_vv_f9177_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti,
	                                       const __m512 epsr,
	                                       const __m512 epsi,
	                                       const __m512 mur,
	                                       const __m512 mui) {
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  const __m512 C150 = _mm512_set1_ps(1.5f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_fmadd_pd(_mm512_mul_pd(sthti,l2),
	                                          _mm512_mul_pd(k0,C40),C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  x3    = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  inve  = _mm512_rcp14_ps(x3);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	        
	           __m512 rcs_vv_f9177_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                         const float * __restrict __ATTR_ALIGN__(64) ph,
	                                         const float * __restrict __ATTR_ALIGN__(64) pl,
	                                         const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmur,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmui) {
	                        
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_load_ps(&pmur[0]);
	                  register __m512 mui = _mm512_load_ps(&pmui[0]); 
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  const __m512 C150 = _mm512_set1_ps(1.5f);
	                  __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_fmadd_pd(_mm512_mul_pd(sthti,l2),
	                                          _mm512_mul_pd(k0,C40),C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  x3    = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  inve  = _mm512_rcp14_ps(x3);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	          
	           __m512 rcs_vv_f9177_zmm16r4_u(const float * __restrict  pk0,
	                                         const float * __restrict  ph,
	                                         const float * __restrict  pl,
	                                         const float * __restrict  pthti,
	                                         const float * __restrict  pepsr,
	                                         const float * __restrict  pepsi,
	                                         const float * __restrict  pmur,
	                                         const float * __restrict  pmui) {
	                        
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_loadu_ps(&pmur[0]);
	                  register __m512 mui = _mm512_loadu_ps(&pmui[0]); 
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  const __m512 C150 = _mm512_set1_ps(1.5f);
	                  __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 epsrm1,epsim1;
	                  register __m512 epsr2,epsi2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,murm1,muim1,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsr,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsi,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(t0r,t0i,t0r,t0i,epsrm1,epsim1);
	                  arg   = _mm512_fmadd_pd(_mm512_mul_pd(sthti,l2),
	                                          _mm512_mul_pd(k0,C40),C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  x3    = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  inve  = _mm512_rcp14_ps(x3);
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  epsrm1= _mm512_fmadd_ps(epsrm1,sthti,t1r);
	                  epsim1= _mm512_fmadd_ps(epsim1,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(epsr,cthti);
	                  x1    = _mm512_mul_ps(epsi,cthti);
	                  cmul_zmm16r4(epsr,epsi,epsr,epsi,&epsr2,&epsi2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(epsr2,epsi2,murm1,muim1,&x2,&x3);
	                  epsrm1 = _mm512_sub_ps(epsrm1,x2);
	                  epsim1 = _mm512_sub_ps(epsim1,x3);
	                  cdiv_zmm16r4(epsrm1,epsim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	         /*
	            Exponential surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (hh) polarization.
	            Formula 9.1-78
	        */
	        
	        
	        
	         
	           __m512 rcs_hh_f9178_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti,
	                                       const __m512 epsr,
	                                       const __m512 epsi,
	                                       const __m512 mur,
	                                       const __m512 mui) {
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  x3    = _mm512_mul_ps(C40,x0);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_fmadd_ps(_mm512_mul_ps(sthti,l2),x3,C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	         
	           __m512 rcs_hh_f9178_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                         const float * __restrict __ATTR_ALIGN__(64) ph,
	                                         const float * __restrict __ATTR_ALIGN__(64) pl,
	                                         const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsr,
	                                         const float * __restrict __ATTR_ALIGN__(64) pepsi,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmur,
	                                         const float * __restrict __ATTR_ALIGN__(64) pmui) {
	                        
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);
	                  register __m512 epsr= _mm512_load_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_load_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_load_ps(&pmur[0]);
	                  register __m512 mui = _mm512_load_ps(&pmui[0]); 
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  x3    = _mm512_mul_ps(C40,x0);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_fmadd_ps(_mm512_mul_ps(sthti,l2),x3,C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	       
	         
	           __m512 rcs_hh_f9178_zmm16r4_u(const float * __restrict  pk0,
	                                         const float * __restrict  ph,
	                                         const float * __restrict  pl,
	                                         const float * __restrict  pthti,
	                                         const float * __restrict  pepsr,
	                                         const float * __restrict  pepsi,
	                                         const float * __restrict  pmur,
	                                         const float * __restrict  pmui) {
	                        
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);
	                  register __m512 epsr= _mm512_loadu_ps(&pepsr[0]);
	                  register __m512 epsi= _mm512_loadu_ps(&pepsi[0]);
	                  register __m512 mur = _mm512_loadu_ps(&pmur[0]);
	                  register __m512 mui = _mm512_loadu_ps(&pmui[0]); 
	                                       
	                  const __m512 C10  = _mm512_set1_ps(1.0f);
	                  const __m512 C40  = _mm512_set1_ps(4.0f);
	                  const __m512 C80  = _mm512_set1_ps(8.0f);
	                  register __m512 k04,h2,l2,x0,x1,x2,x3,cthti,sthti;
	                  register __m512 murm1,muim1,murm1s,muim1s;
	                  register __m512 mur2,mui2,t0r,t0i,t1r,t1i;
	                  register __m512 t2r,t2i,inve,t3r,t3i;
	                  register __m512 rcs,cabs,arg,earg,frac;
	                  h2    = _mm512_mul_ps(h,h);
	                  t0r   = _mm512_sub_ps(epsi,C10);
	                  cthti = xcosf(thti);
	                  t0i   = _mm512_sub_ps(epsr,C10);
	                  murm1 = _mm512_sub_ps(mur,C10);
	                  x0    = _mm512_mul_ps(k0,k0);
	                  muim1 = _mm512_mul_ps(mui,C10);
	                  x3    = _mm512_mul_ps(C40,x0);
	                  l2    = _mm512_mul_ps(l,l);
	                  sthti = xsinf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  sthti = _mm512_mul_ps(sthti,sthti);
	                  cmul_zmm16r4(murm1,muim1,murm1,muim1,&murm1s,&muim1s);
	                  arg   = _mm512_fmadd_ps(_mm512_mul_ps(sthti,l2),x3,C10);
	                  x0    = _mm512_mul_ps(cthti,cthti);
	                  earg  = _mm512_mul_ps(arg,_mm512_sqrt_ps(arg));
	                  x1    = _mm512_mul_ps(x0,x0);
	                  x2    = _mm512_mul_ps(C80,k04);
	                  frac  = _mm512_mul_ps(_mm512_mul_ps(x2,h2),
	                                        _mm512_mul_ps(l2,x1));
	                  cmul_zmm16r4(epsr,epsi,mur,mui,&t1r,&t1i);
	                  murm1s= _mm512_fmadd_ps(murm1s,sthti,t1r);
	                  muim1s= _mm512_fmadd_ps(muim1s,sthti,t1i);
	                  t1r   = _mm512_sub_ps(t1r,sthti);
	                  t1i   = _mm512_sub_ps(t1i,sthti);
	                  csqrt_zmm16r4(t1r,t1i,&t2r,&t2i);
	                  x0    = _mm512_mul_ps(mur,cthti);
	                  x1    = _mm512_mul_ps(mui,cthti);
	                  inve  = _mm512_rcp14_ps(earg);
	                  cmul_zmm16r4(mur,mui,mur,mui,&mur2,&mui2);
	                  x0    = _mm512_add_ps(x0,t2r);
	                  x1    = _mm512_add_ps(x1,t2i);
	                  cmul_zmm16r4(x0,x1,x0,x1,&t3r,&t3i);//denom
	                  cmul_zmm16r4(mur2,mui2,t0r,t0i,&x2,&x3);
	                  murm1 = _mm512_sub_ps(murm1,x2);
	                  muim1 = _mm512_sub_ps(muim1,x3);
	                  cdiv_zmm16r4(murm1,muim1,t3r,t3i,&t0r,&t0i); // ratio (complex).
	                  cabs = cabs_zmm16r4(t0r,t0i);
	                  rcs  = _mm512_mul_ps(frac,_mm512_mul_ps(cabs,inve));
	                  return (rcs);
	       }
	       
	       
	         /*
	            Gaussian surface-height correlation
	            coefficient of average backscattering RCS 
	            per unit area.
	            RCS (hv) polarization.
	            Formula 9.1-79
	        */
	        
	        
	         
	           __m512 rcs_hv_f9179_zmm16r4() { 
	           
	                return _mm512_setzero_ps();
	         } 
	         
	         
	         /*
	                Scattering matrix elements for
	                a perfectly conducting surface.
	                Formula: 9.1-80
	         */
	         
	         
	         
	           __m512 a_vv_f9180_zmm16r4(const __m512 thti,
	                                         const __m512 thts,
	                                         const __m512 phis) {
	                                         
	                  register __m512 sthti,sthts,cthti,cthts,cphis;
	                  register __m512 num,den,avv;  
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  cphis = xcosf(phis);
	                  cthts = xcosf(thts);
	                  sthts = xsinf(thts);
	                  num   = _mm512_fmsub_ps(sthti,sthts,cphis);
	                  den   = _mm512_mul_ps(cthti,cthts);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);        
	          }
	          
	          
	          
	        
	           __m512 a_vv_f9180_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) pthti,
	                                         const float * __restrict __ATTR_ALIGN__(64) pthts,
	                                         const float * __restrict __ATTR_ALIGN__(64) pphis) {
	                     
	                  register __m512 thti = _mm512_load_ps(&pthti[0]);
	                  register __m512 thts = _mm512_load_ps(&pthts[0]);
	                  register __m512 phis = _mm512_load_ps(&phis[0]);                    
	                  register __m512 sthti,sthts,cthti,cthts,cphis;
	                  register __m512 num,den,avv;  
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  cphis = xcosf(phis);
	                  cthts = xcosf(thts);
	                  sthts = xsinf(thts);
	                  num   = _mm512_fmsub_ps(sthti,sthts,cphis);
	                  den   = _mm512_mul_ps(cthti,cthts);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);        
	          }
	          
	          
	          
	        
	           __m512 a_vv_f9180_zmm16r4_u(  const float * __restrict  pthti,
	                                         const float * __restrict  pthts,
	                                         const float * __restrict  pphis) {
	                     
	                  register __m512 thti = _mm512_loadu_ps(&pthti[0]);
	                  register __m512 thts = _mm512_loadu_ps(&pthts[0]);
	                  register __m512 phis = _mm512_loadu_ps(&phis[0]);                    
	                  register __m512 sthti,sthts,cthti,cthts,cphis;
	                  register __m512 num,den,avv;  
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  cphis = xcosf(phis);
	                  cthts = xcosf(thts);
	                  sthts = xsinf(thts);
	                  num   = _mm512_fmsub_ps(sthti,sthts,cphis);
	                  den   = _mm512_mul_ps(cthti,cthts);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);        
	          }
	          
	          
	          /*
	                Scattering matrix elements for
	                a perfectly conducting surface.
	                Formula: 9.1-81
	         */
	         
	         
	        
	           __m512 a_hv_f9181_zmm16r4(const __m512 phis,
	                                     const __m512 thti) {
	                                     
	                  register __m512 sphis,cthti;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthti = xcosf(thti);
	                  ahv   = _mm512_div_ps(sphis,cthti);
	                  return (ahv);                           
	         }
	         
	         
	        
	           __m512 a_hv_f9181_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                     const float * __restrict __ATTR_ALIGN__(64) pthti) {
	                                     
	                  register __m512 thti = _mm512_load_ps(&pthti[0]);
	                  register __m512 phis = _mm512_load_ps(&phis[0]); 
	                  register __m512 sphis,cthti;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthti = xcosf(thti);
	                  ahv   = _mm512_div_ps(sphis,cthti);
	                  return (ahv);                           
	         }
	          
	       
	        
	         
	           __m512 a_hv_f9181_zmm16r4_u(const float * __restrict pphis,
	                                     const float * __restrict  pthti) {
	                                     
	                  register __m512 thti = _mm512_loadu_ps(&pthti[0]);
	                  register __m512 phis = _mm512_loadu_ps(&phis[0]); 
	                  register __m512 sphis,cthti;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthti = xcosf(thti);
	                  ahv   = _mm512_div_ps(sphis,cthti);
	                  return (ahv);                           
	         }
	         
	         
	            /*
	                Scattering matrix elements for
	                a perfectly conducting surface.
	                Formula: 9.1-82
	         */
	         
	         
	       
	           __m512 a_hh_f9182_zmm16r4(const __m512 phis) {
	                 
	                  register __m512 cphis,ahh;
	                  cphis = xcosf(phis);
	                  ahh   = negate_zmm16r4(cphis);
	                  return (ahh);
	          }
	          
	          
	          
	           __m512 a_hh_f9182_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pphis) {
	                 
	                  register __m512 phis = _mm512_load_ps(&pphis[0]);
	                  register __m512 cphis,ahh;
	                  cphis = xcosf(phis);
	                  ahh   = negate_zmm16r4(cphis);
	                  return (ahh);
	          }
	        
	       
	       
	           __m512 a_hh_f9182_zmm16r4_u(const float * __restrict  pphis) {
	                 
	                  register __m512 phis = _mm512_loadu_ps(&pphis[0]);
	                  register __m512 cphis,ahh;
	                  cphis = xcosf(phis);
	                  ahh   = negate_zmm16r4(cphis);
	                  return (ahh);
	          }
	          
	          
	             /*
	                Scattering matrix elements for
	                a perfectly conducting surface.
	                Formula: 9.1-83
	         */
	         
	         
	       
	           __m512 a_vh_f9183_zmm16r4(const __m512 phis,
	                                     const __m512 thts) {
	                                     
	                  register __m512 sphis,cthts;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthts = xcosf(thti);
	                  ahv   = negate_zmm16r4(_mm512_div_ps(sphis,cthts));
	                  return (ahv);                           
	         }
	         
	         
	         
	         
	           __m512 a_vh_f9183_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pphis,
	                                       const float * __restrict __ATTR_ALIGN__(64) pthts) {
	                         
	                  register __m512 phis = _mm512_load_ps(&pphis[0]);
	                  register __m512 thts = _mm512_load_ps(&pphis[0]);            
	                  register __m512 sphis,cthts;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthts = xcosf(thti);
	                  ahv   = negate_zmm16r4(_mm512_div_ps(sphis,cthts));
	                  return (ahv);                           
	         }
	         
	        
	           __m512 a_vh_f9183_zmm16r4_u(const float * __restrict  pphis,
	                                       const float * __restrict pthts) {
	                         
	                  register __m512 phis = _mm512_loadu_ps(&pphis[0]);
	                  register __m512 thts = _mm512_loadu_ps(&pphis[0]);            
	                  register __m512 sphis,cthts;
	                  register __m512 ahv;
	                  sphis = xsinf(phis);
	                  cthts = xcosf(thti);
	                  ahv   = negate_zmm16r4(_mm512_div_ps(sphis,cthts));
	                  return (ahv);                           
	         }
	         
	         
	         /*
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Formula: 9.1-84 
	         */
	         
	         
	        
	           __m512 a_vv_f9184_zmm16r4(const __m512 thti) {
	           
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 sthti,cthti,num,den;
	                  register __m512 avv;
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  num   = _mm512_fmadd_ps(sthti,sthti,C10);
	                  den   = _mm512_mul_ps(cthti,cthti);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);
	           }
	           
	           
	          
	           __m512 a_vv_f9184_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pthti) {
	           
	                  register __m512 thti = _mm512_load_ps(&pthti[0]);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 sthti,cthti,num,den;
	                  register __m512 avv;
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  num   = _mm512_fmadd_ps(sthti,sthti,C10);
	                  den   = _mm512_mul_ps(cthti,cthti);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);
	           }
	           
	           
	         
	           __m512 a_vv_f9184_zmm16r4_u(const float * __restrict  pthti) {
	           
	                  register __m512 thti = _mm512_loadu_ps(&pthti[0]);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 sthti,cthti,num,den;
	                  register __m512 avv;
	                  sthti = xsinf(thti);
	                  cthti = xcosf(thti);
	                  num   = _mm512_fmadd_ps(sthti,sthti,C10);
	                  den   = _mm512_mul_ps(cthti,cthti);
	                  avv   = _mm512_div_ps(num,den);
	                  return (avv);
	           }
	           
	           
	           
	         /*
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Formula: 9.1-85
	         */                  
	         
	         
	         
	           __m512 a_hh_f9185_zmm16r4() {
	           
	                  return _mm512_set1_ps(1.0f);
	           }  
	           
	           
	            /*
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Formula: 9.1-86
	         */   
	         
	         
	        
	           __m512 a_vh_f9186_zmm16r4() {
	           
	                  return _mm512_setzero_ps();
	           }  
	           
	           
	         /*
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Average backscattering RCS per unit area.
	              Gaussian surface height correlation coefficient.
	              Formula: 9.1-87
	         */
	         
	         
	         
	        
	           __m512 rcs_vv_f9187_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti) {
	                                       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  strm  = _mm512_fmadd_pd(x1,x1,C10);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(strm,strm);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(x1,inve));
	                  return (rcs);
	         }
	           
	           
	       
	           __m512 rcs_vv_f9187_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                       const float * __restrict __ATTR_ALIGN__(64) ph,
	                                       const float * __restrict __ATTR_ALIGN__(64) pl,
	                                       const float * __restrict __ATTR_ALIGN__(64) pthti) {
	                             
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);   
	                  register __m512 thti= _mm512_load_ps(&pthti[0]);       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  strm  = _mm512_fmadd_pd(x1,x1,C10);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(strm,strm);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(x1,inve));
	                  return (rcs);
	         }
	           
	            
	         
	          
	           __m512 rcs_vv_f9187_zmm16r4_u(const float * __restrict  pk0,
	                                         const float * __restrict  ph,
	                                         const float * __restrict  pl,
	                                         const float * __restrict  pthti) {
	                             
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);   
	                  register __m512 thti= _mm512_loadu_ps(&pthti[0]);       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  strm  = _mm512_fmadd_pd(x1,x1,C10);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  earg  = xexpf(arg);
	                  x1    = _mm512_mul_ps(strm,strm);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(x1,inve));
	                  return (rcs);
	         }
	         
	         
	          /*
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Average backscattering RCS per unit area.
	              Gaussian surface height correlation coefficient.
	              Formula: 9.1-88
	         */
	         
	         
	         
	           __m512 rcs_hh_f9188_zmm16r4(const __m512 k0,
	                                       const __m512 h,
	                                       const __m512 l,
	                                       const __m512 thti) {
	                                       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti,cthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  strm  = xcosf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  x1    = _mm512_mul_ps(strm,strm);
	                  earg  = xexpf(arg);
	                  cthti = _mm512_mul_ps(x1,x1);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(cthti,inve));
	                  return (rcs);
	         }
	         
	         
	        
	           __m512 rcs_hh_f9188_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pk0,
	                                       const float * __restrict __ATTR_ALIGN__(64) ph,
	                                       const float * __restrict __ATTR_ALIGN__(64) pl,
	                                       const float * __restrict __ATTR_ALIGN__(64) pthti) {
	                             
	                  register __m512 k0  = _mm512_load_ps(&pk0[0]);
	                  register __m512 h   = _mm512_load_ps(&ph[0]);
	                  register __m512 l   = _mm512_load_ps(&pl[0]);   
	                  register __m512 thti= _mm512_load_ps(&pthti[0]); 
	                                       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti,cthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  strm  = xcosf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  x1    = _mm512_mul_ps(strm,strm);
	                  earg  = xexpf(arg);
	                  cthti = _mm512_mul_ps(x1,x1);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(cthti,inve));
	                  return (rcs);
	         }
	         
	         
	        
	           __m512 rcs_hh_f9188_zmm16r4_u(const float * __restrict  pk0,
	                                       const float * __restrict  ph,
	                                       const float * __restrict  pl,
	                                       const float * __restrict  pthti) {
	                             
	                  register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
	                  register __m512 h   = _mm512_loadu_ps(&ph[0]);
	                  register __m512 l   = _mm512_loadu_ps(&pl[0]);   
	                  register __m512 thti= _mm512_loadu_ps(&pthti[0]); 
	                                       
	                  const __m512 C40 = _mm512_set1_ps(4.0f);
	                  const __m512 C10 = _mm512_set1_ps(1.0f);
	                  register __m512 k04,x0,x1,l2,h2,sthti,cthti;
	                  register __m512 rcs,arg,earg,inve,strm,trm;
	                  x0    = _mm512_mul_ps(k0,k0);
	                  l2    = _mm512_mul_ps(l,l);
	                  strm  = xcosf(thti);
	                  k04   = _mm512_mul_ps(x0,x0);
	                  h2    = _mm512_mul_ps(h,h);
	                  x1    = xsinf(thti);
	                  x0    = _mm512_mul_ps(C40,k04);
	                  sthti = _mm512_mul_ps(x1,x1);
	                  arg   = _mm512_mul_ps(_mm512_mul_ps(k0,k0),
	                                        _mm512_mul_ps(sthti,l2));
	                  trm   = _mm512_mul_ps(_mm512_mul_ps(l2,h2,x0));
	                  x1    = _mm512_mul_ps(strm,strm);
	                  earg  = xexpf(arg);
	                  cthti = _mm512_mul_ps(x1,x1);
	                  inve  = _mm512_rcp14_ps(earg);
	                  rcs   = _mm512_mul_ps(trm,_mm512_mul_ps(cthti,inve));
	                  return (rcs);
	         }
	         
	         
	         /*
	              
	              Backscattering from a perfectly conducting surface
	              Theta (inc) == theta (scat) , phi (scat) = 180 (grad).
	              Average backscattering RCS per unit area.
	              Gaussian surface height correlation coefficient.
	              Formula: 9.1-89
	           
	         */
	         
	         
	        
	           __m512 rcs_vhhv_f9189_zmm16r4() {
	           
	                  return (_mm512_setzero_ps()); 
	          }
	          
	          
	          
	           
	      
	                                    
	        
                 
                 
                 
               
               
 





















