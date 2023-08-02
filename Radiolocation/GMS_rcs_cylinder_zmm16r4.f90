



!/*MIT License
!Copyright (c) 2020 Bernard Gingold
!Permission is hereby granted, free of charge, to any person obtaining a copy
!of this software and associated documentation files (the "Software"), to deal
!in the Software without restriction, including without limitation the rights
!to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
!copies of the Software, and to permit persons to whom the Software is
!furnished to do so, subject to the following conditions:
!The above copyright notice and this permission notice shall be included in all
!copies or substantial portions of the Software.
!THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
!IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
!FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
!AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
!LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
!OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
!SOFTWARE.
!*/

module rcs_cylinder_zmm16r4


!===================================================================================85
 !---------------------------- DESCRIPTION ------------------------------------------85
 !
 !
 !
 !          Module  name:
 !                         rcs_cylinder_zmm16r4
 !          
 !          Purpose:
 !                        Various characteristics of analytically derived Radar
 !                        Cross Section of cylindrical objects  
 !                        Based  on George T. Ruck, Donald E. Barrick , William D. Stuart , 
 !                        - "Radar Cross Section Handbook 1 and 2" (1970, Kluwer Academic Plenum Publishers) 
 !                        This module contains only explicitly vectorized (SIMD)
 !                        
 !          History:
 !                        Date: 08-07-2023
 !                        Time: 14:21 GMT+2
 !                        
 !          Version:
 !
 !                      Major: 1
 !                      Minor: 0
 !                      Micro: 0
 !
 !          Author:  
 !                      Bernard Gingold
 !          
 !                 
 !          References:
 !         
 !                      George T. Ruck, Donald E. Barrick , William D. Stuart
 !                      Radar Cross Section Handbook 1 and 2" (1970, Kluwer Academic Plenum Publishers)     
 !         
 !          E-mail:
 !                  
 !                      beniekg@gmail.com
!==================================================================================85
    ! Tab:5 col - Type and etc.. definitions
    ! Tab:10,11 col - Type , function and subroutine code blocks.

    use mod_kinds,    only : i4,sp
    use mod_vectypes, only : ZMM16r4_t
    use avx512_cvec16_v2
    
    public
    implicit none
    
     ! Major version
     integer(kind=i4),  parameter :: RCS_CYLINDER_ZMM16R4_MAJOR = 1
     ! Minor version
     integer(kind=i4),  parameter :: RCS_CYLINDER_ZMM16R4_MINOR = 0
     ! Micro version
     integer(kind=i4),  parameter :: RCS_CYLINDER_ZMM16R4_MICRO = 0
     ! Full version
     integer(kind=i4),  parameter :: RCS_CYLINDER_ZMM16R4_FULLVER =   &
            1000*RCS_CYLINDER_ZMM16R4_MAJOR+100*RCS_CYLINDER_ZMM16R4_MINOR+10*RCS_CYLINDER_ZMM16R4_MICRO
     ! Module creation date
     character(*),        parameter :: RCS_CYLINDER_ZMM16R4_CREATE_DATE = "18-07-2022 14:30 +00200 (TUE 18 JUL 2023 GMT+2)"
     ! Module build date
     character(*),        parameter :: RCS_CYLINDER_ZMM16R4_BUILD_DATE  = __DATE__ " " __TIME__
     ! Module author info
     character(*),        parameter :: RCS_CYLINDER_ZMM16R4_AUTHOR      = "Programmer: Bernard Gingold, contact: beniekg@gmail.com"
     ! Short description
     character(*),        parameter :: RCS_CYLINDER_ZMM16R4_SYNOPSIS    = "Analytical Cylindrical objects RCS characteristics and models explicitly vectorized (SIMD)."
    
#ifndef __RCS_CYLINDER_PF_CACHE_HINT__
#define __RCS_CYLINDER_PF_CACHE_HINT__ 1
#endif 
    
     contains
     
     
                   !/* 
                   !      Low frequency scattering widths (k0a << 1).
                   !      Backscatter scattering width for E-field 
                   !      cylinder-parallel,formula 4.1-19
                   ! */
                   
                   
             pure function rcs_f419_zmm16r4(a,k0a) result(rcs)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! locals
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 =             &
                                                 ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C2467401100272339654708622749969 =             &
                                                 ZMM16r4_t(2.467401100272339654708622749969_sp)
                   type(ZMM16r4_t), parameter :: C08905  = ZMM16r4_t(0.8905_sp)
                   ZMM16r4_t, automatic :: num,arg,ln,ln2,den
                   num.v = a.v*C9869604401089358618834490999876.v
                   arg.v = k0a.v*C08905.v
                   ln.v  = log(arg.v)
                   ln2.v = ln.v*ln.v
                   den.v = k0a.v*ln2.v+C2467401100272339654708622749969.v
                   rcs.v = num.v/den.v
             end function rcs_f419_zmm16r4
             
             
             subroutine rcs_f419_zmm16r4_unroll16x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4_unroll16x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f419_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<16) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                        a0.v         = pa(i+8).v
                        k0a0.v       = pk0a(i+8).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+8).v  = rcs0.v  
                        a1.v         = pa(i+9).v
                        k0a1.v       = pk0a(i+9).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+9).v  = rcs1.v 
                        a2.v         = pa(i+10).v
                        k0a2.v       = pk0a(i+10).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+10).v = rcs2.v
                        a3.v         = pa(i+11).v
                        k0a3.v       = pk0a(i+11).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+11).v = rcs3.v  
                        a0.v         = pa(i+12).v
                        k0a0.v       = pk0a(i+12).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+12).v = rcs0.v  
                        a1.v         = pa(i+13).v
                        k0a1.v       = pk0a(i+13).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+13).v = rcs1.v 
                        a2.v         = pa(i+14).v
                        k0a2.v       = pk0a(i+14).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+14).v = rcs2.v
                        a3.v         = pa(i+15).v
                        k0a3.v       = pk0a(i+15).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+15).v = rcs3.v                      
                   end do
             end subroutine rcs_f419_zmm16r4_unroll16x


             subroutine rcs_f419_zmm16r4_unroll12x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4_unroll12x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f419_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<12) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                        a0.v         = pa(i+8).v
                        k0a0.v       = pk0a(i+8).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+8).v  = rcs0.v  
                        a1.v         = pa(i+9).v
                        k0a1.v       = pk0a(i+9).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+9).v  = rcs1.v 
                        a2.v         = pa(i+10).v
                        k0a2.v       = pk0a(i+10).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+10).v = rcs2.v
                        a3.v         = pa(i+11).v
                        k0a3.v       = pk0a(i+11).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+11).v = rcs3.v  
                    end do
             end subroutine rcs_f419_zmm16r4_unroll12x
             
             
             subroutine rcs_f419_zmm16r4_unroll8x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4_unroll8x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f419_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<8) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                    end do
             end subroutine rcs_f419_zmm16r4_unroll8x
             
             
             subroutine rcs_f419_zmm16r4_unroll4x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f419_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<4) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f419_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f419_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f419_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                    end do
             end subroutine rcs_f419_zmm16r4_unroll4x
             
             
             subroutine rcs_f419_zmm16r4_rolled(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f419_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: rcs_f419_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f419_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0
                   type(ZMM16r4_t), automatic :: k0a0
                   type(ZMM16r4_t), automatic :: rcs0
                   integer(kind=i4) :: i
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f419_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                     end do
             end subroutine rcs_f419_zmm16r4_rolled
             
             
             
             ! /* 
             !           Low frequency scattering widths (k0a << 1).
             !            Backscatter scattering width for H-field 
             !            cylinder-parallel,formula 4.1-20
             !       */
             
             
             pure function rcs_f4120_zmm16r4(a,k0a) result(rcs)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 = &
                                             ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C225 = ZMM16r4_t(2.25_sp)
                   type(ZMM16r4_t), automatic :: pi2a,k0a3,t0
                   k0a3.v = k0a.v*k0a.v*k0a.v
                   t0.v   = C225.v*k0a3.v
                   pi2a.v = a.v*C9869604401089358618834490999876.v
                   rcs.v  = pi2a.v*t0.v
             end function rcs_f4120_zmm16r4
             
             
             subroutine rcs_f4120_zmm16r4_unroll16x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4_unroll16x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         a0.v      = pa(i).v
                         k0a.v     = pk0a(i).v
                         rcs.v     = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i).v = rcs.v
                      end do
                      if(n<16) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                    
                         a0.v        = pa(i+0).v
                         k0a.v       = pk0a(i+0).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+0).v = rcs.v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+2).v = rcs2.v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+3).v = rcs3.v
                         a0.v        = pa(i+4).v
                         k0a.v       = pk0a(i+4).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+4).v = rcs.v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+6).v = rcs2.v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+7).v = rcs3.v
                         a0.v        = pa(i+8).v
                         k0a.v       = pk0a(i+8).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+8).v = rcs.v
                         a1.v        = pa(i+9).v
                         k0a1.v      = pk0a(i+9).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+9).v = rcs1.v
                         a2.v        = pa(i+10).v
                         k0a2.v      = pk0a(i+10).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+10).v = rcs2.v
                         a3.v        = pa(i+11).v
                         k0a3.v      = pk0a(i+11).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+11).v = rcs3.v
                         a0.v        = pa(i+12).v
                         k0a.v       = pk0a(i+12).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+12).v = rcs.v
                         a1.v        = pa(i+13).v
                         k0a1.v      = pk0a(i+13).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+13).v = rcs1.v
                         a2.v        = pa(i+14).v
                         k0a2.v      = pk0a(i+14).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+14).v = rcs2.v
                         a3.v        = pa(i+15).v
                         k0a3.v      = pk0a(i+15).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+15).v = rcs3.v
                   end do
             end subroutine rcs_f4120_zmm16r4_unroll16x
             
             
             subroutine rcs_f4120_zmm16r4_unroll12x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4_unroll12x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         a0.v      = pa(i).v
                         k0a.v     = pk0a(i).v
                         rcs.v     = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i).v = rcs.v
                      end do
                      if(n<12) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                    
                         a0.v        = pa(i+0).v
                         k0a.v       = pk0a(i+0).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+0).v = rcs.v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+2).v = rcs2.v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+3).v = rcs3.v
                         a0.v        = pa(i+4).v
                         k0a.v       = pk0a(i+4).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+4).v = rcs.v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+6).v = rcs2.v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+7).v = rcs3.v
                         a0.v        = pa(i+8).v
                         k0a.v       = pk0a(i+8).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+8).v = rcs.v
                         a1.v        = pa(i+9).v
                         k0a1.v      = pk0a(i+9).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+9).v = rcs1.v
                         a2.v        = pa(i+10).v
                         k0a2.v      = pk0a(i+10).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+10).v = rcs2.v
                         a3.v        = pa(i+11).v
                         k0a3.v      = pk0a(i+11).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+11).v = rcs3.v
                     end do
             end subroutine rcs_f4120_zmm16r4_unroll12x
             

             subroutine rcs_f4120_zmm16r4_unroll8x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4_unroll8x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         a0.v      = pa(i).v
                         k0a.v     = pk0a(i).v
                         rcs.v     = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i).v = rcs.v
                      end do
                      if(n<8) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                    
                         a0.v        = pa(i+0).v
                         k0a.v       = pk0a(i+0).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+0).v = rcs.v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+2).v = rcs2.v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+3).v = rcs3.v
                         a0.v        = pa(i+4).v
                         k0a.v       = pk0a(i+4).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+4).v = rcs.v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+6).v = rcs2.v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+7).v = rcs3.v
                     end do
             end subroutine rcs_f4120_zmm16r4_unroll8x
             

             subroutine rcs_f4120_zmm16r4_unroll4x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         a0.v      = pa(i).v
                         k0a.v     = pk0a(i).v
                         rcs.v     = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i).v = rcs.v
                      end do
                      if(n<4) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                    
                         a0.v        = pa(i+0).v
                         k0a.v       = pk0a(i+0).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+0).v = rcs.v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4120_zmm16r4(a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4120_zmm16r4(a2,k0a2)
                         prcs(i+2).v = rcs2.v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4120_zmm16r4(a03,k0a3)
                         prcs(i+3).v = rcs3.v
                      end do
             end subroutine rcs_f4120_zmm16r4_unroll4x
             
         
             subroutine rcs_f4120_zmm16r4_rolled(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4120_zmm16r4_rolled
                   !dir$ attributes forceinline :: rcs_f4120_zmm16r4_rolled
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4120_zmm16r4_rolled
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16r4_t), automatic :: a0
                   type(ZMM16r4_t), automatic :: k0a0
                   type(ZMM16r4_t), automatic :: rcs0
                   integer(kind=i4) :: i
                  
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                    
                         a0.v        = pa(i+0).v
                         k0a.v       = pk0a(i+0).v
                         rcs.v       = rcs_f4120_zmm16r4(a0,k0a)
                         prcs(i+0).v = rcs.v
                     end do
             end subroutine rcs_f4120_zmm16r4_rolled
             
             
             ! /*
             !           Bistatic scattering widths, E-field cylinder axis-parallel
             !           Formula 4.1-21
             !      */
             
             pure function rcs_f4121_zmm16r4(a,k0a) result(rcs)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4121_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4121_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4121_zmm16r4
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   rcs = rcs_f4120_zmm16r4(a,k0a)
             end function rcs_f4121_zmm16r4
             
             
              !/*
              !          Bistatic scattering widths, H-field cylinder axis-parallel
              !          Formula 4.1-22
              !     */ 
              
              
              pure function rcs_f4122_zmm16r4(phi,a,k0a) result(rcs)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4 
                   type(ZMM16r4_t),   intent(in) :: phi
                   type(ZMM16r4_t),   intent(in) :: a
                   type(ZMM16r4_t),   intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 = &
                                              ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C05 = ZMM16r4_t(0.5_sp)
                   type(ZMM16r4_t), automatic :: pi2a,k0a3,cosp,frac,sqr
                   pi2a.v = a.v*C9869604401089358618834490999876.v
                   k0a3.v = k0a.v*k0a.v*k0a.v
                   cosp.v = cos(phi.v)
                   frac.v = C05.v*cosp.v
                   sqr.v  = frac.v*frac.v
                   rcs.v  = pi2a.v*k0a3.v*sqr.v
              end function rcs_f4122_zmm16r4
              
              
              subroutine rcs_f4122_zmm16r4_unroll16x(pphi,pa,pk0a,prcs,n,PF_DIST)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4_unroll16x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pphi
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: phi0,phi1,phi2,phi3
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         phi0.v    = pphi(i).v
                         a0.v      = pa(i).v
                         k0a0.v    = pk0a(i).v
                         rcs0.v    = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i).v = rcs0.v
                      end do
                      if(n<16) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ assume_aligned pphi:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                  
                         phi0.v      = pphi(i+0).v
                         a0.v        = pa(i+0).v
                         k0a0.v      = pk0a(i+0).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+0).v = rcs0.v
                         phi1.v      = pphi(i+1).v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         phi2.v      = pphi(i+2).v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+2).v = rcs2.v   
                         phi3.v      = pphi(i+3).v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+3).v = rcs3.v
                         phi0.v      = pphi(i+4).v
                         a0.v        = pa(i+4).v
                         k0a0.v      = pk0a(i+4).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+4).v = rcs0.v
                         phi1.v      = pphi(i+5).v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         phi2.v      = pphi(i+6).v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+6).v = rcs2.v   
                         phi3.v      = pphi(i+7).v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+7).v = rcs3.v
                         phi0.v      = pphi(i+8).v
                         a0.v        = pa(i+8).v
                         k0a0.v      = pk0a(i+8).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+8).v = rcs0.v
                         phi1.v      = pphi(i+9).v
                         a1.v        = pa(i+9).v
                         k0a1.v      = pk0a(i+9).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+9).v = rcs1.v
                         phi2.v      = pphi(i+10).v
                         a2.v        = pa(i+10).v
                         k0a2.v      = pk0a(i+10).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+10).v= rcs2.v   
                         phi3.v      = pphi(i+11).v
                         a3.v        = pa(i+11).v
                         k0a3.v      = pk0a(i+11).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+11).v = rcs3.v
                         phi0.v      = pphi(i+12).v
                         a0.v        = pa(i+12).v
                         k0a0.v      = pk0a(i+12).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+12).v = rcs0.v
                         phi1.v      = pphi(i+13).v
                         a1.v        = pa(i+13).v
                         k0a1.v      = pk0a(i+13).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+13).v = rcs1.v
                         phi2.v      = pphi(i+14).v
                         a2.v        = pa(i+14).v
                         k0a2.v      = pk0a(i+14).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+14).v = rcs2.v   
                         phi3.v      = pphi(i+15).v
                         a3.v        = pa(i+15).v
                         k0a3.v      = pk0a(i+15).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+15).v = rcs3.v
                  end do
              end subroutine rcs_f4122_zmm16r4_unroll16x
              
             
              subroutine rcs_f4122_zmm16r4_unroll12x(pphi,pa,pk0a,prcs,n,PF_DIST)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4_unroll12x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pphi
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: phi0,phi1,phi2,phi3
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         phi0.v    = pphi(i).v
                         a0.v      = pa(i).v
                         k0a0.v    = pk0a(i).v
                         rcs0.v    = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i).v = rcs0.v
                      end do
                      if(n<12) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ assume_aligned pphi:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                  
                         phi0.v      = pphi(i+0).v
                         a0.v        = pa(i+0).v
                         k0a0.v      = pk0a(i+0).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+0).v = rcs0.v
                         phi1.v      = pphi(i+1).v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         phi2.v      = pphi(i+2).v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+2).v = rcs2.v   
                         phi3.v      = pphi(i+3).v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+3).v = rcs3.v
                         phi0.v      = pphi(i+4).v
                         a0.v        = pa(i+4).v
                         k0a0.v      = pk0a(i+4).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+4).v = rcs0.v
                         phi1.v      = pphi(i+5).v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         phi2.v      = pphi(i+6).v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+6).v = rcs2.v   
                         phi3.v      = pphi(i+7).v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+7).v = rcs3.v
                         phi0.v      = pphi(i+8).v
                         a0.v        = pa(i+8).v
                         k0a0.v      = pk0a(i+8).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+8).v = rcs0.v
                         phi1.v      = pphi(i+9).v
                         a1.v        = pa(i+9).v
                         k0a1.v      = pk0a(i+9).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+9).v = rcs1.v
                         phi2.v      = pphi(i+10).v
                         a2.v        = pa(i+10).v
                         k0a2.v      = pk0a(i+10).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+10).v= rcs2.v   
                         phi3.v      = pphi(i+11).v
                         a3.v        = pa(i+11).v
                         k0a3.v      = pk0a(i+11).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+11).v = rcs3.v
                      end do
              end subroutine rcs_f4122_zmm16r4_unroll12x
              

              subroutine rcs_f4122_zmm16r4_unroll8x(pphi,pa,pk0a,prcs,n,PF_DIST)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4_unroll8x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pphi
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: phi0,phi1,phi2,phi3
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         phi0.v    = pphi(i).v
                         a0.v      = pa(i).v
                         k0a0.v    = pk0a(i).v
                         rcs0.v    = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i).v = rcs0.v
                      end do
                      if(n<8) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ assume_aligned pphi:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                  
                         phi0.v      = pphi(i+0).v
                         a0.v        = pa(i+0).v
                         k0a0.v      = pk0a(i+0).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+0).v = rcs0.v
                         phi1.v      = pphi(i+1).v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         phi2.v      = pphi(i+2).v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+2).v = rcs2.v   
                         phi3.v      = pphi(i+3).v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+3).v = rcs3.v
                         phi0.v      = pphi(i+4).v
                         a0.v        = pa(i+4).v
                         k0a0.v      = pk0a(i+4).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+4).v = rcs0.v
                         phi1.v      = pphi(i+5).v
                         a1.v        = pa(i+5).v
                         k0a1.v      = pk0a(i+5).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+5).v = rcs1.v
                         phi2.v      = pphi(i+6).v
                         a2.v        = pa(i+6).v
                         k0a2.v      = pk0a(i+6).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+6).v = rcs2.v   
                         phi3.v      = pphi(i+7).v
                         a3.v        = pa(i+7).v
                         k0a3.v      = pk0a(i+7).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+7).v = rcs3.v
                     end do
              end subroutine rcs_f4122_zmm16r4_unroll8x
              

              subroutine rcs_f4122_zmm16r4_unroll4x(pphi,pa,pk0a,prcs,n,PF_DIST)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pphi
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: phi0,phi1,phi2,phi3
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         phi0.v    = pphi(i).v
                         a0.v      = pa(i).v
                         k0a0.v    = pk0a(i).v
                         rcs0.v    = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i).v = rcs0.v
                      end do
                      if(n<4) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ assume_aligned pphi:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                  
                         phi0.v      = pphi(i+0).v
                         a0.v        = pa(i+0).v
                         k0a0.v      = pk0a(i+0).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+0).v = rcs0.v
                         phi1.v      = pphi(i+1).v
                         a1.v        = pa(i+1).v
                         k0a1.v      = pk0a(i+1).v
                         rcs1.v      = rcs_f4122_zmm16r4(phi1,a1,k0a1)
                         prcs(i+1).v = rcs1.v
                         phi2.v      = pphi(i+2).v
                         a2.v        = pa(i+2).v
                         k0a2.v      = pk0a(i+2).v
                         rcs2.v      = rcs_f4122_zmm16r4(phi2,a2,k0a2)
                         prcs(i+2).v = rcs2.v   
                         phi3.v      = pphi(i+3).v
                         a3.v        = pa(i+3).v
                         k0a3.v      = pk0a(i+3).v
                         rcs3.v      = rcs_f4122_zmm16r4(phi3,a3,k0a3)
                         prcs(i+3).v = rcs3.v
                         phi0.v      = pphi(i+4).v
                         a0.v        = pa(i+4).v
                         k0a0.v      = pk0a(i+4).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+4).v = rcs0.v
                     end do
              end subroutine rcs_f4122_zmm16r4_unroll4x
              

              subroutine rcs_f4122_zmm16r4_rolled(pphi,pa,pk0a,prcs,n,PF_DIST)
              
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4122_zmm16r4_rolled
                   !dir$ attributes forceinline :: rcs_f4122_zmm16r4_rolled
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4122_zmm16r4_rolled
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pphi
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out):: prcs
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: phi0
                   type(ZMM16r4_t), automatic :: a0,
                   type(ZMM16r4_t), automatic :: k0a0
                   type(ZMM16r4_t), automatic :: rcs0
                   integer(kind=i4) :: i
                  
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ assume_aligned pphi:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pphi(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif                  
                         phi0.v      = pphi(i+0).v
                         a0.v        = pa(i+0).v
                         k0a0.v      = pk0a(i+0).v
                         rcs0.v      = rcs_f4122_zmm16r4(phi0,a0,k0a0)
                         prcs(i+0).v = rcs0.v
                     end do
              end subroutine rcs_f4122_zmm16r4_rolled
              
              
               ! /*
               !        Forward scattering widths, E-field.
               !        Formula 4.1-23
               !    */
               
               pure function rcs_f4123_zmm16r4(a,k0a) result(rcs)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4123_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4123_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4123_zmm16r4
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   rcs = rcs_f4120_zmm16r4(a,k0a)
               end function rcs_f4123_zmm16r4
               
               
               !/*
               !        Forward scattering widths, H-field.
               !        Formula 4.1-24
               !    */
               
               pure function rcs_f4124_zmm16r4(a,k0a) result(rcs)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 = &
                                                   ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C025 = ZMM16r4_t(0.25_sp)
                   type(ZMM16r4_t), automatic :: pi2a,k0a3
                   k0a3.v = k0a.v*k0a.v*k0a.v
                   pi2a.v = C9869604401089358618834490999876.v*a.v
                   rcs.v  = pi2a.v*k0a3.v*C025.v
               end function rcs_f4124_zmm16r4
               
               
               subroutine rcs_f4124_zmm16r4_unroll16x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4_unroll16x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f4124_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<16) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                        a0.v         = pa(i+8).v
                        k0a0.v       = pk0a(i+8).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+8).v  = rcs0.v  
                        a1.v         = pa(i+9).v
                        k0a1.v       = pk0a(i+9).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+9).v  = rcs1.v 
                        a2.v         = pa(i+10).v
                        k0a2.v       = pk0a(i+10).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+10).v = rcs2.v
                        a3.v         = pa(i+11).v
                        k0a3.v       = pk0a(i+11).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+11).v = rcs3.v  
                        a0.v         = pa(i+12).v
                        k0a0.v       = pk0a(i+12).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+12).v = rcs0.v  
                        a1.v         = pa(i+13).v
                        k0a1.v       = pk0a(i+13).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+13).v = rcs1.v 
                        a2.v         = pa(i+14).v
                        k0a2.v       = pk0a(i+14).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+14).v = rcs2.v
                        a3.v         = pa(i+15).v
                        k0a3.v       = pk0a(i+15).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+15).v = rcs3.v                      
                   end do
             end subroutine rcs_f4124_zmm16r4_unroll16x
             
             
             subroutine rcs_f4124_zmm16r4_unroll12x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4_unroll12x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f4124_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<12) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                        a0.v         = pa(i+8).v
                        k0a0.v       = pk0a(i+8).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+8).v  = rcs0.v  
                        a1.v         = pa(i+9).v
                        k0a1.v       = pk0a(i+9).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+9).v  = rcs1.v 
                        a2.v         = pa(i+10).v
                        k0a2.v       = pk0a(i+10).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+10).v = rcs2.v
                        a3.v         = pa(i+11).v
                        k0a3.v       = pk0a(i+11).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+11).v = rcs3.v  
                     end do
             end subroutine rcs_f4124_zmm16r4_unroll12x
             

             subroutine rcs_f4124_zmm16r4_unroll8x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4_unroll8x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f4124_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<8) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                        a0.v         = pa(i+4).v
                        k0a0.v       = pk0a(i+4).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+4).v  = rcs0.v  
                        a1.v         = pa(i+5).v
                        k0a1.v       = pk0a(i+5).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+5).v  = rcs1.v 
                        a2.v         = pa(i+6).v
                        k0a2.v       = pk0a(i+6).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+6).v  = rcs2.v
                        a3.v         = pa(i+7).v
                        k0a3.v       = pk0a(i+7).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+7).v  = rcs3.v  
                    end do
             end subroutine rcs_f4124_zmm16r4_unroll8x
               
               
             subroutine rcs_f4124_zmm16r4_unroll4x(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,a1,a2,a3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: rcs0,rcs1,rcs2,rcs3
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         a0.v       = pa(i).v
                         k0a0.v     = pk0a(i).v
                         rcs0       = rcs_f4124_zmm16r4(a0,k0a0)
                         prcs(i).v  = rcs0.v
                      end do
                      if(n<4) return
                   end if
                   m1=m+1
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                        a1.v         = pa(i+1).v
                        k0a1.v       = pk0a(i+1).v
                        rcs1         = rcs_f4124_zmm16r4(a1,k0a1)
                        prcs(i+1).v  = rcs1.v 
                        a2.v         = pa(i+2).v
                        k0a2.v       = pk0a(i+2).v
                        rcs2         = rcs_f4124_zmm16r4(a2,k0a2)
                        prcs(i+2).v  = rcs2.v  
                        a3.v         = pa(i+3).v
                        k0a3.v       = pk0a(i+3).v
                        rcs3         = rcs_f4124_zmm16r4(a3,k0a3)
                        prcs(i+3).v  = rcs3.v  
                   end do
             end subroutine rcs_f4124_zmm16r4_unroll4x
               
                 
             subroutine rcs_f4124_zmm16r4_rolled(pa,pk0a,prcs,n,PF_DIST)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4124_zmm16r4_rolled
                   !dir$ attributes forceinline :: rcs_f4124_zmm16r4_rolled
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4124_zmm16r4_rolled
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pa
                   type(ZMM16r4_t), dimension(1:n), intent(in)    :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(out)   :: prcs 
                   integer(kind=i4)               , intent(in)    :: n
                   integer(kind=i4)               , intent(in)    :: PF_DIST
                   ! Locals
                   type(ZMM16r4_t), automatic :: a0,
                   type(ZMM16r4_t), automatic :: k0a0
                   type(ZMM16r4_t), automatic :: rcs0
                   integer(kind=i4) :: i
                 
                    !dir$ assume_aligned pa:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned prcs:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                   do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)   
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(pa(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.) 
#endif       
                        a0.v         = pa(i+0).v
                        k0a0.v       = pk0a(i+0).v
                        rcs0         = rcs_f4124_zmm16r4(a0,k0a0)
                        prcs(i+0).v  = rcs0.v  
                    end do
             end subroutine rcs_f4124_zmm16r4_rolled
             
             
             !/*
             !             Surface currents (k0a << 1), for long cylinder (wire).
             !             E-field cylinder axis parallel.
             !             Formula 4.1-25
             !          */ 
             
             
             pure function Kz_f4125_zmm16r4(eps0,mu0,E,k0a) result(Kz)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4
                   use mod_vecconsts, only : v16_0
                   real(kind=sp),   intent(in) :: eps0
                   real(kind=sp),   intent(in) :: mu0
                   type(ZMM16c4),   intent(in) :: E
                   type(ZMM164r_t), intent(in) :: k0a
                   type(ZMM16c4) :: Kz
                   ! Locals
                   type(ZMM16r4_t), parameter :: C157079632679489661923132169164 = 
                                         ZMM16r4_t(1.57079632679489661923132169164_sp)
                   type(ZMM16r4_t), parameter :: C08905 = ZMM16r4_t(0.8905_sp)
                   type(ZMM16c4),   automatic :: t0,t1,div
                   type(ZMM164r_t), automatic :: veps0,vmu0
                   type(ZMM16r4_t), automatic :: lna,ln
                   type(ZMM16r4_t), automatic :: x0
                   veps0 = ZMM16r4_t(eps0)
                   lna.v = k0a.v*C08905.v
                   vmu0  = ZMM16r4_t(mu0)
                   ln.v  = log(lna.v)
                   x0.v  = veps0.v/vmu0.v
                   t0.re = v16_0.v
                   t0.im = sqrt(x0.v)
                   t1.re = k0a.v*ln.v
                   t1.im = C157079632679489661923132169164.v
                   div   = E/t1
                   Kz    = div*t0
             end function Kz_f4125_zmm16r4
             
             
             subroutine Kz_f4125_zmm16r4_unroll16x(peps0,pmu0,pE,pk0a,pKz,PF_DIST1, &
                                                   n,PF_DIST1,PF_DIST2)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4_unroll16x
                   real(kind=sp),   dimension(1:n), intent(in) :: peps0
                   real(kind=sp),   dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pKz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST1
                   integer(kind=i4),                intent(in) :: PF_DIST2
                   ! Locals
                   type(ZMM16c4),   automatic :: Kz0,Kz1,Kz2,Kz3
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   real(kind=sp),   automatic :: eps00,eps01,eps02,eps03
                   real(kind=sp),   automatic :: mu00,mu01,mu02,mu03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         eps00  = peps0(i)
                         mu00   = pmu0(i)
                         E0.v   = pE(i).v
                         k0a0.v = pk0a(i).v
                         Kz0    = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i) = Kz0
                      end do
                      if(n<16) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pKz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                 do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif                 
                         eps00    = peps0(i+0)
                         mu00     = pmu0(i+0)
                         E0.v     = pE(i+0).v
                         k0a0.v   = pk0a(i+0).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+0) = Kz0 
                         eps01    = peps0(i+1)
                         mu01     = pmu0(i+1)
                         E1.v     = pE(i+1).v
                         k0a1.v   = pk0a(i+1).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+1) = Kz1 
                         eps02    = peps0(i+2)
                         mu02     = pmu0(i+2)
                         E2.v     = pE(i+2).v
                         k0a2.v   = pk0a(i+2).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+2) = Kz2
                         eps03    = peps0(i+3)
                         mu03     = pmu0(i+3)
                         E3.v     = pE(i+3).v
                         k0a3.v   = pk0a(i+3).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+3) = Kz3  
                         eps00    = peps0(i+4)
                         mu00     = pmu0(i+4)
                         E0.v     = pE(i+4).v
                         k0a0.v   = pk0a(i+4).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+4) = Kz0 
                         eps01    = peps0(i+5)
                         mu01     = pmu0(i+5)
                         E1.v     = pE(i+5).v
                         k0a1.v   = pk0a(i+5).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+5) = Kz1 
                         eps02    = peps0(i+6)
                         mu02     = pmu0(i+6)
                         E2.v     = pE(i+6).v
                         k0a2.v   = pk0a(i+6).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+6) = Kz2
                         eps03    = peps0(i+7)
                         mu03     = pmu0(i+7)
                         E3.v     = pE(i+7).v
                         k0a3.v   = pk0a(i+7).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+7) = Kz3  
                         eps00    = peps0(i+8)
                         mu00     = pmu0(i+8)
                         E0.v     = pE(i+8).v
                         k0a0.v   = pk0a(i+8).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+8) = Kz0 
                         eps01    = peps0(i+9)
                         mu01     = pmu0(i+9)
                         E1.v     = pE(i+9).v
                         k0a1.v   = pk0a(i+9).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+9) = Kz1 
                         eps02    = peps0(i+10)
                         mu02     = pmu0(i+10)
                         E2.v     = pE(i+10).v
                         k0a2.v   = pk0a(i+10).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+10) = Kz2
                         eps03    = peps0(i+11)
                         mu03     = pmu0(i+11)
                         E3.v     = pE(i+11).v
                         k0a3.v   = pk0a(i+11).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+11) = Kz3  
                         eps00    = peps0(i+12)
                         mu00     = pmu0(i+12)
                         E0.v     = pE(i+12).v
                         k0a0.v   = pk0a(i+12).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+12) = Kz0 
                         eps01    = peps0(i+13)
                         mu01     = pmu0(i+13)
                         E1.v     = pE(i+13).v
                         k0a1.v   = pk0a(i+13).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+13) = Kz1 
                         eps02    = peps0(i+14)
                         mu02     = pmu0(i+14)
                         E2.v     = pE(i+14).v
                         k0a2.v   = pk0a(i+14).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+14) = Kz2
                         eps03    = peps0(i+15)
                         mu03     = pmu0(i+15)
                         E3.v     = pE(i+15).v
                         k0a3.v   = pk0a(i+15).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+15) = Kz3  
                 end do
             end subroutine Kz_f4125_zmm16r4_unroll16x
             
             
             subroutine Kz_f4125_zmm16r4_unroll12x(peps0,pmu0,pE,pk0a,pKz,PF_DIST1, &
                                                   n,PF_DIST1,PF_DIST2)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4_unroll12x
                   real(kind=sp),   dimension(1:n), intent(in) :: peps0
                   real(kind=sp),   dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pKz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST1
                   integer(kind=i4),                intent(in) :: PF_DIST2
                   ! Locals
                   type(ZMM16c4),   automatic :: Kz0,Kz1,Kz2,Kz3
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   real(kind=sp),   automatic :: eps00,eps01,eps02,eps03
                   real(kind=sp),   automatic :: mu00,mu01,mu02,mu03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         eps00  = peps0(i)
                         mu00   = pmu0(i)
                         E0.v   = pE(i).v
                         k0a0.v = pk0a(i).v
                         Kz0    = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i) = Kz0
                      end do
                      if(n<12) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pKz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                 do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif                 
                         eps00    = peps0(i+0)
                         mu00     = pmu0(i+0)
                         E0.v     = pE(i+0).v
                         k0a0.v   = pk0a(i+0).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+0) = Kz0 
                         eps01    = peps0(i+1)
                         mu01     = pmu0(i+1)
                         E1.v     = pE(i+1).v
                         k0a1.v   = pk0a(i+1).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+1) = Kz1 
                         eps02    = peps0(i+2)
                         mu02     = pmu0(i+2)
                         E2.v     = pE(i+2).v
                         k0a2.v   = pk0a(i+2).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+2) = Kz2
                         eps03    = peps0(i+3)
                         mu03     = pmu0(i+3)
                         E3.v     = pE(i+3).v
                         k0a3.v   = pk0a(i+3).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+3) = Kz3  
                         eps00    = peps0(i+4)
                         mu00     = pmu0(i+4)
                         E0.v     = pE(i+4).v
                         k0a0.v   = pk0a(i+4).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+4) = Kz0 
                         eps01    = peps0(i+5)
                         mu01     = pmu0(i+5)
                         E1.v     = pE(i+5).v
                         k0a1.v   = pk0a(i+5).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+5) = Kz1 
                         eps02    = peps0(i+6)
                         mu02     = pmu0(i+6)
                         E2.v     = pE(i+6).v
                         k0a2.v   = pk0a(i+6).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+6) = Kz2
                         eps03    = peps0(i+7)
                         mu03     = pmu0(i+7)
                         E3.v     = pE(i+7).v
                         k0a3.v   = pk0a(i+7).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+7) = Kz3  
                         eps00    = peps0(i+8)
                         mu00     = pmu0(i+8)
                         E0.v     = pE(i+8).v
                         k0a0.v   = pk0a(i+8).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+8) = Kz0 
                         eps01    = peps0(i+9)
                         mu01     = pmu0(i+9)
                         E1.v     = pE(i+9).v
                         k0a1.v   = pk0a(i+9).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+9) = Kz1 
                         eps02    = peps0(i+10)
                         mu02     = pmu0(i+10)
                         E2.v     = pE(i+10).v
                         k0a2.v   = pk0a(i+10).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+10) = Kz2
                         eps03    = peps0(i+11)
                         mu03     = pmu0(i+11)
                         E3.v     = pE(i+11).v
                         k0a3.v   = pk0a(i+11).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+11) = Kz3  
                     end do
             end subroutine Kz_f4125_zmm16r4_unroll12x
             
             
             subroutine Kz_f4125_zmm16r4_unroll8x(peps0,pmu0,pE,pk0a,pKz,PF_DIST1, &
                                                   n,PF_DIST1,PF_DIST2)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4_unroll8x
                   real(kind=sp),   dimension(1:n), intent(in) :: peps0
                   real(kind=sp),   dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pKz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST1
                   integer(kind=i4),                intent(in) :: PF_DIST2
                   ! Locals
                   type(ZMM16c4),   automatic :: Kz0,Kz1,Kz2,Kz3
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   real(kind=sp),   automatic :: eps00,eps01,eps02,eps03
                   real(kind=sp),   automatic :: mu00,mu01,mu02,mu03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         eps00  = peps0(i)
                         mu00   = pmu0(i)
                         E0.v   = pE(i).v
                         k0a0.v = pk0a(i).v
                         Kz0    = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i) = Kz0
                      end do
                      if(n<8) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pKz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                 do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif                 
                         eps00    = peps0(i+0)
                         mu00     = pmu0(i+0)
                         E0.v     = pE(i+0).v
                         k0a0.v   = pk0a(i+0).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+0) = Kz0 
                         eps01    = peps0(i+1)
                         mu01     = pmu0(i+1)
                         E1.v     = pE(i+1).v
                         k0a1.v   = pk0a(i+1).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+1) = Kz1 
                         eps02    = peps0(i+2)
                         mu02     = pmu0(i+2)
                         E2.v     = pE(i+2).v
                         k0a2.v   = pk0a(i+2).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+2) = Kz2
                         eps03    = peps0(i+3)
                         mu03     = pmu0(i+3)
                         E3.v     = pE(i+3).v
                         k0a3.v   = pk0a(i+3).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+3) = Kz3  
                         eps00    = peps0(i+4)
                         mu00     = pmu0(i+4)
                         E0.v     = pE(i+4).v
                         k0a0.v   = pk0a(i+4).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+4) = Kz0 
                         eps01    = peps0(i+5)
                         mu01     = pmu0(i+5)
                         E1.v     = pE(i+5).v
                         k0a1.v   = pk0a(i+5).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+5) = Kz1 
                         eps02    = peps0(i+6)
                         mu02     = pmu0(i+6)
                         E2.v     = pE(i+6).v
                         k0a2.v   = pk0a(i+6).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+6) = Kz2
                         eps03    = peps0(i+7)
                         mu03     = pmu0(i+7)
                         E3.v     = pE(i+7).v
                         k0a3.v   = pk0a(i+7).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+7) = Kz3  
                     end do
             end subroutine Kz_f4125_zmm16r4_unroll8x
             
             
             subroutine Kz_f4125_zmm16r4_unroll4x(peps0,pmu0,pE,pk0a,pKz,PF_DIST1, &
                                                   n,PF_DIST1,PF_DIST2)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4_unroll4x
                   real(kind=sp),   dimension(1:n), intent(in) :: peps0
                   real(kind=sp),   dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pKz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST1
                   integer(kind=i4),                intent(in) :: PF_DIST2
                   ! Locals
                   type(ZMM16c4),   automatic :: Kz0,Kz1,Kz2,Kz3
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   real(kind=sp),   automatic :: eps00,eps01,eps02,eps03
                   real(kind=sp),   automatic :: mu00,mu01,mu02,mu03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         eps00  = peps0(i)
                         mu00   = pmu0(i)
                         E0.v   = pE(i).v
                         k0a0.v = pk0a(i).v
                         Kz0    = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i) = Kz0
                      end do
                      if(n<4) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pKz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                 do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif                 
                         eps00    = peps0(i+0)
                         mu00     = pmu0(i+0)
                         E0.v     = pE(i+0).v
                         k0a0.v   = pk0a(i+0).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+0) = Kz0 
                         eps01    = peps0(i+1)
                         mu01     = pmu0(i+1)
                         E1.v     = pE(i+1).v
                         k0a1.v   = pk0a(i+1).v
                         Kz1      = Kz_f4125_zmm16r4(eps01,mu01,E1,k0a1)
                         pKz(i+1) = Kz1 
                         eps02    = peps0(i+2)
                         mu02     = pmu0(i+2)
                         E2.v     = pE(i+2).v
                         k0a2.v   = pk0a(i+2).v
                         Kz2      = Kz_f4125_zmm16r4(eps02,mu02,E2,k0a2)
                         pKz(i+2) = Kz2
                         eps03    = peps0(i+3)
                         mu03     = pmu0(i+3)
                         E3.v     = pE(i+3).v
                         k0a3.v   = pk0a(i+3).v
                         Kz3      = Kz_f4125_zmm16r4(eps03,mu03,E3,k0a3)
                         pKz(i+3) = Kz3  
                     end do
             end subroutine Kz_f4125_zmm16r4_unroll4x
                

             subroutine Kz_f4125_zmm16r4_rolled(peps0,pmu0,pE,pk0a,pKz,PF_DIST1, &
                                                   n,PF_DIST1,PF_DIST2)
             
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kz_f4125_zmm16r4_rolled
                   !dir$ attributes forceinline :: Kz_f4125_zmm16r4_rolled
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kz_f4125_zmm16r4_rolled
                   real(kind=sp),   dimension(1:n), intent(in) :: peps0
                   real(kind=sp),   dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pKz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST1
                   integer(kind=i4),                intent(in) :: PF_DIST2
                   ! Locals
                   type(ZMM16c4),   automatic :: Kz0
                   type(ZMM16c4),   automatic :: E0
                   type(ZMM16r4_t), automatic :: k0a0
                   real(kind=sp),   automatic :: eps00
                   real(kind=sp),   automatic :: mu00
                   integer(kind=i4) :: i
                 
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pKz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                 do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T1,.true.,.false.) 
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST1),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST2),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif                 
                         eps00    = peps0(i+0)
                         mu00     = pmu0(i+0)
                         E0.v     = pE(i+0).v
                         k0a0.v   = pk0a(i+0).v
                         Kz0      = Kz_f4125_zmm16r4(eps00,mu00,E0,k0a0)
                         pKz(i+0) = Kz0 
                     end do
             end subroutine Kz_f4125_zmm16r4_rolled
             
             
             !/*
             !            Surface currents (k0a << 1), for long cylinder (wire).
             !             H-field cylinder axis parallel.
             !             Formula 4.1-26
             !      */
             
             pure function Kph_f4126_zmm16r4(H) result(Kph)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Kph_f4126_zmm16r4
                   !dir$ attributes forceinline :: Kph_f4126_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Kph_f4126_zmm16r4
                   type(ZMM16c4),  intent(in) :: H
                   type(ZMM16c4) :: Kph
                   ! Locals
                   type(ZMM16c4), automatic :: I
                   I.re = -1.0_sp
                   I.im = -1.0_sp
                   Kph  = I*H
             end function Kph_f4126_zmm16r4
             
             
              !/*
              !          The toal current along the wire.
              !         Formula 4.1-27 
              !!
              !!     */   
            
             pure function Iz_f4127_zmm16r4(eps0,mu0,E,k0a,k0) result(Iz)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_neg1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16c4),    intent(in) :: E
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: k0
                   type(ZMM16c4) :: Iz
                   ! Locals
                   type(ZMM16c4),   automatic :: t0,t1
                   type(ZMM16c4),   automatic :: t2,div
                   type(ZMM16r4_t), automatic :: sqr
                   type(ZMM16r4_t), automatic :: lna,ln
                   type(ZMM16r4_t), parameter :: C6283185307179586476925286766559 =    &
                                        ZMM16r4_t(6.283185307179586476925286766559_sp) ! 2*PI
                   type(ZMM16r4_t), parameter :: C157079632679489661923132169164  =    &
                                        ZMM16r4_t(1.57079632679489661923132169164_sp)  ! PI/2
                   type(ZMM16r4_t), parameter :: C08905 = ZMM16r4_t(0.8905_sp)
                   lna.v  = k0a.v*C08905.v
                   t0.re  = v16_0.v
                   t2     = E*C6283185307179586476925286766559
                   sqr.v  = sqrt(eps0.v/mu0.v)
                   t1.im  = v16_neg1.v*C157079632679489661923132169164.v  
                   ln.v   = log(lna.v)
                   t0.im  = v16_neg1.v*sqr.v
                   div    = t2/t1
                   Iz     = t0*div
             end function Iz_f4127_zmm16r4


             subroutine Iz_f4127_zmm16r4_unroll16x(peps0,pmu0,pE,pk0a,
                                                   pk0,pIz,n,PF_DIST)
                                                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4_unroll16x
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4_unroll16x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4_unroll16x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: peps0
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0
                   type(ZMM16c4),   dimension(1:n), intent(out):: pIz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   !type(ZMM16c4),   automatic :: Iz0,Iz1,Iz2,Iz3
                   type(ZMM16r4_t), automatic :: eps00,eps01,eps02,eps03
                   type(ZMM16r4_t), automatic :: mu00,mu01,mu02,mu03
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: k00,k01,k02,k03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,16)
                   if(m/=0) then
                      do i=1,m
                         eps00.v  = peps0(i).v
                         mu00.v   = pmu0(i).v
                         E0.re    = pE(i).re
                         E0.im    = pE(i).im
                         k0a0.v   = pk0a(i).v
                         k00.v    = pk0(i).v
                         pIz(i)   = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                      end do
                      if(n<16) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pk0:64
                    !dir$ assume_aligned pIz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,16
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.) 
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif         
                         eps00.v  = peps0(i+0).v
                         mu00.v   = pmu0(i+0).v
                         E0.re    = pE(i+0).re
                         E0.im    = pE(i+0).im
                         k0a0.v   = pk0a(i+0).v
                         k00.v    = pk0(i+0).v
                         pIz(i+0) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+1).v
                         mu01.v   = pmu0(i+1).v
                         E1.re    = pE(i+1).re
                         E1.im    = pE(i+1).im
                         k0a1.v   = pk0a(i+1).v
                         k01.v    = pk0(i+1).v
                         pIz(i+1) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+2).v
                         mu02.v   = pmu0(i+2).v
                         E2.re    = pE(i+2).re
                         E2.im    = pE(i+2).im
                         k0a2.v   = pk0a(i+2).v
                         k02.v    = pk0(i+2).v
                         pIz(i+2) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+3).v
                         mu03.v   = pmu0(i+3).v
                         E3.re    = pE(i+3).re
                         E3.im    = pE(i+3).im
                         k0a3.v   = pk0a(i+3).v
                         k03.v    = pk0(i+3).v
                         pIz(i+3) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps00.v  = peps0(i+4).v
                         mu00.v   = pmu0(i+4).v
                         E0.re    = pE(i+4).re
                         E0.im    = pE(i+4).im
                         k0a0.v   = pk0a(i+4).v
                         k00.v    = pk0(i+4).v
                         pIz(i+4) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+5).v
                         mu01.v   = pmu0(i+5).v
                         E1.re    = pE(i+5).re
                         E1.im    = pE(i+5).im
                         k0a1.v   = pk0a(i+5).v
                         k01.v    = pk0(i+5).v
                         pIz(i+5) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+6).v
                         mu02.v   = pmu0(i+6).v
                         E2.re    = pE(i+6).re
                         E2.im    = pE(i+6).im
                         k0a2.v   = pk0a(i+6).v
                         k02.v    = pk0(i+6).v
                         pIz(i+6) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+7).v
                         mu03.v   = pmu0(i+7).v
                         E3.re    = pE(i+7).re
                         E3.im    = pE(i+7).im
                         k0a3.v   = pk0a(i+7).v
                         k03.v    = pk0(i+7).v
                         pIz(i+7) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps00.v  = peps0(i+8).v
                         mu00.v   = pmu0(i+8).v
                         E0.re    = pE(i+8).re
                         E0.im    = pE(i+8).im
                         k0a0.v   = pk0a(i+8).v
                         k00.v    = pk0(i+8).v
                         pIz(i+8) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+9).v
                         mu01.v   = pmu0(i+9).v
                         E1.re    = pE(i+9).re
                         E1.im    = pE(i+9).im
                         k0a1.v   = pk0a(i+9).v
                         k01.v    = pk0(i+9).v
                         pIz(i+9) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+10).v
                         mu02.v   = pmu0(i+10).v
                         E2.re    = pE(i+10).re
                         E2.im    = pE(i+10).im
                         k0a2.v   = pk0a(i+10).v
                         k02.v    = pk0(i+10).v
                         pIz(i+10) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+11).v
                         mu03.v   = pmu0(i+11).v
                         E3.re    = pE(i+11).re
                         E3.im    = pE(i+11).im
                         k0a3.v   = pk0a(i+11).v
                         k03.v    = pk0(i+11).v
                         pIz(i+11) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps03.v  = peps0(i+12).v
                         mu03.v   = pmu0(i+12).v
                         E3.re    = pE(i+12).re
                         E3.im    = pE(i+12).im
                         k0a3.v   = pk0a(i+12).v
                         k03.v    = pk0(i+12).v
                         pIz(i+12) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps03.v  = peps0(i+13).v
                         mu03.v   = pmu0(i+13).v
                         E3.re    = pE(i+13).re
                         E3.im    = pE(i+13).im
                         k0a3.v   = pk0a(i+13).v
                         k03.v    = pk0(i+13).v
                         pIz(i+13) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps03.v  = peps0(i+14).v
                         mu03.v   = pmu0(i+14).v
                         E3.re    = pE(i+14).re
                         E3.im    = pE(i+14).im
                         k0a3.v   = pk0a(i+14).v
                         k03.v    = pk0(i+14).v
                         pIz(i+14) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps03.v  = peps0(i+15).v
                         mu03.v   = pmu0(i+15).v
                         E3.re    = pE(i+15).re
                         E3.im    = pE(i+15).im
                         k0a3.v   = pk0a(i+15).v
                         k03.v    = pk0(i+15).v
                         pIz(i+15) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                  end do
             end subroutine Iz_f4127_zmm16r4_unroll16x
             
             
             subroutine Iz_f4127_zmm16r4_unroll12x(peps0,pmu0,pE,pk0a,
                                                   pk0,pIz,n,PF_DIST)
                                                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4_unroll12x
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4_unroll12x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4_unroll12x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: peps0
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0
                   type(ZMM16c4),   dimension(1:n), intent(out):: pIz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   !type(ZMM16c4),   automatic :: Iz0,Iz1,Iz2,Iz3
                   type(ZMM16r4_t), automatic :: eps00,eps01,eps02,eps03
                   type(ZMM16r4_t), automatic :: mu00,mu01,mu02,mu03
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: k00,k01,k02,k03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,12)
                   if(m/=0) then
                      do i=1,m
                         eps00.v  = peps0(i).v
                         mu00.v   = pmu0(i).v
                         E0.re    = pE(i).re
                         E0.im    = pE(i).im
                         k0a0.v   = pk0a(i).v
                         k00.v    = pk0(i).v
                         pIz(i)   = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                      end do
                      if(n<12) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pk0:64
                    !dir$ assume_aligned pIz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,12
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.) 
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif         
                         eps00.v  = peps0(i+0).v
                         mu00.v   = pmu0(i+0).v
                         E0.re    = pE(i+0).re
                         E0.im    = pE(i+0).im
                         k0a0.v   = pk0a(i+0).v
                         k00.v    = pk0(i+0).v
                         pIz(i+0) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+1).v
                         mu01.v   = pmu0(i+1).v
                         E1.re    = pE(i+1).re
                         E1.im    = pE(i+1).im
                         k0a1.v   = pk0a(i+1).v
                         k01.v    = pk0(i+1).v
                         pIz(i+1) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+2).v
                         mu02.v   = pmu0(i+2).v
                         E2.re    = pE(i+2).re
                         E2.im    = pE(i+2).im
                         k0a2.v   = pk0a(i+2).v
                         k02.v    = pk0(i+2).v
                         pIz(i+2) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+3).v
                         mu03.v   = pmu0(i+3).v
                         E3.re    = pE(i+3).re
                         E3.im    = pE(i+3).im
                         k0a3.v   = pk0a(i+3).v
                         k03.v    = pk0(i+3).v
                         pIz(i+3) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps00.v  = peps0(i+4).v
                         mu00.v   = pmu0(i+4).v
                         E0.re    = pE(i+4).re
                         E0.im    = pE(i+4).im
                         k0a0.v   = pk0a(i+4).v
                         k00.v    = pk0(i+4).v
                         pIz(i+4) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+5).v
                         mu01.v   = pmu0(i+5).v
                         E1.re    = pE(i+5).re
                         E1.im    = pE(i+5).im
                         k0a1.v   = pk0a(i+5).v
                         k01.v    = pk0(i+5).v
                         pIz(i+5) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+6).v
                         mu02.v   = pmu0(i+6).v
                         E2.re    = pE(i+6).re
                         E2.im    = pE(i+6).im
                         k0a2.v   = pk0a(i+6).v
                         k02.v    = pk0(i+6).v
                         pIz(i+6) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+7).v
                         mu03.v   = pmu0(i+7).v
                         E3.re    = pE(i+7).re
                         E3.im    = pE(i+7).im
                         k0a3.v   = pk0a(i+7).v
                         k03.v    = pk0(i+7).v
                         pIz(i+7) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps00.v  = peps0(i+8).v
                         mu00.v   = pmu0(i+8).v
                         E0.re    = pE(i+8).re
                         E0.im    = pE(i+8).im
                         k0a0.v   = pk0a(i+8).v
                         k00.v    = pk0(i+8).v
                         pIz(i+8) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+9).v
                         mu01.v   = pmu0(i+9).v
                         E1.re    = pE(i+9).re
                         E1.im    = pE(i+9).im
                         k0a1.v   = pk0a(i+9).v
                         k01.v    = pk0(i+9).v
                         pIz(i+9) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+10).v
                         mu02.v   = pmu0(i+10).v
                         E2.re    = pE(i+10).re
                         E2.im    = pE(i+10).im
                         k0a2.v   = pk0a(i+10).v
                         k02.v    = pk0(i+10).v
                         pIz(i+10) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+11).v
                         mu03.v   = pmu0(i+11).v
                         E3.re    = pE(i+11).re
                         E3.im    = pE(i+11).im
                         k0a3.v   = pk0a(i+11).v
                         k03.v    = pk0(i+11).v
                         pIz(i+11) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                     end do
             end subroutine Iz_f4127_zmm16r4_unroll12x
             

             subroutine Iz_f4127_zmm16r4_unroll8x(peps0,pmu0,pE,pk0a,
                                                   pk0,pIz,n,PF_DIST)
                                                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4_unroll8x
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4_unroll8x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4_unroll8x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: peps0
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0
                   type(ZMM16c4),   dimension(1:n), intent(out):: pIz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   !type(ZMM16c4),   automatic :: Iz0,Iz1,Iz2,Iz3
                   type(ZMM16r4_t), automatic :: eps00,eps01,eps02,eps03
                   type(ZMM16r4_t), automatic :: mu00,mu01,mu02,mu03
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: k00,k01,k02,k03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,8)
                   if(m/=0) then
                      do i=1,m
                         eps00.v  = peps0(i).v
                         mu00.v   = pmu0(i).v
                         E0.re    = pE(i).re
                         E0.im    = pE(i).im
                         k0a0.v   = pk0a(i).v
                         k00.v    = pk0(i).v
                         pIz(i)   = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                      end do
                      if(n<8) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pk0:64
                    !dir$ assume_aligned pIz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,8
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.) 
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif         
                         eps00.v  = peps0(i+0).v
                         mu00.v   = pmu0(i+0).v
                         E0.re    = pE(i+0).re
                         E0.im    = pE(i+0).im
                         k0a0.v   = pk0a(i+0).v
                         k00.v    = pk0(i+0).v
                         pIz(i+0) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+1).v
                         mu01.v   = pmu0(i+1).v
                         E1.re    = pE(i+1).re
                         E1.im    = pE(i+1).im
                         k0a1.v   = pk0a(i+1).v
                         k01.v    = pk0(i+1).v
                         pIz(i+1) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+2).v
                         mu02.v   = pmu0(i+2).v
                         E2.re    = pE(i+2).re
                         E2.im    = pE(i+2).im
                         k0a2.v   = pk0a(i+2).v
                         k02.v    = pk0(i+2).v
                         pIz(i+2) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+3).v
                         mu03.v   = pmu0(i+3).v
                         E3.re    = pE(i+3).re
                         E3.im    = pE(i+3).im
                         k0a3.v   = pk0a(i+3).v
                         k03.v    = pk0(i+3).v
                         pIz(i+3) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                         eps00.v  = peps0(i+4).v
                         mu00.v   = pmu0(i+4).v
                         E0.re    = pE(i+4).re
                         E0.im    = pE(i+4).im
                         k0a0.v   = pk0a(i+4).v
                         k00.v    = pk0(i+4).v
                         pIz(i+4) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+5).v
                         mu01.v   = pmu0(i+5).v
                         E1.re    = pE(i+5).re
                         E1.im    = pE(i+5).im
                         k0a1.v   = pk0a(i+5).v
                         k01.v    = pk0(i+5).v
                         pIz(i+5) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+6).v
                         mu02.v   = pmu0(i+6).v
                         E2.re    = pE(i+6).re
                         E2.im    = pE(i+6).im
                         k0a2.v   = pk0a(i+6).v
                         k02.v    = pk0(i+6).v
                         pIz(i+6) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+7).v
                         mu03.v   = pmu0(i+7).v
                         E3.re    = pE(i+7).re
                         E3.im    = pE(i+7).im
                         k0a3.v   = pk0a(i+7).v
                         k03.v    = pk0(i+7).v
                         pIz(i+7) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                     end do
             end subroutine Iz_f4127_zmm16r4_unroll8x
             
             
             subroutine Iz_f4127_zmm16r4_unroll4x(peps0,pmu0,pE,pk0a,
                                                   pk0,pIz,n,PF_DIST)
                                                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4_unroll4x
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4_unroll4x
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4_unroll4x
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: peps0
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0
                   type(ZMM16c4),   dimension(1:n), intent(out):: pIz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16c4),   automatic :: E0,E1,E2,E3
                   !type(ZMM16c4),   automatic :: Iz0,Iz1,Iz2,Iz3
                   type(ZMM16r4_t), automatic :: eps00,eps01,eps02,eps03
                   type(ZMM16r4_t), automatic :: mu00,mu01,mu02,mu03
                   type(ZMM16r4_t), automatic :: k0a0,k0a1,k0a2,k0a3
                   type(ZMM16r4_t), automatic :: k00,k01,k02,k03
                   integer(kind=i4) :: i,m,m1
                   m = mod(n,4)
                   if(m/=0) then
                      do i=1,m
                         eps00.v  = peps0(i).v
                         mu00.v   = pmu0(i).v
                         E0.re    = pE(i).re
                         E0.im    = pE(i).im
                         k0a0.v   = pk0a(i).v
                         k00.v    = pk0(i).v
                         pIz(i)   = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                      end do
                      if(n<4) return
                   end if
                   m1 = m+1
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pk0:64
                    !dir$ assume_aligned pIz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=m1,n,4
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.) 
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif         
                         eps00.v  = peps0(i+0).v
                         mu00.v   = pmu0(i+0).v
                         E0.re    = pE(i+0).re
                         E0.im    = pE(i+0).im
                         k0a0.v   = pk0a(i+0).v
                         k00.v    = pk0(i+0).v
                         pIz(i+0) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                         eps01.v  = peps0(i+1).v
                         mu01.v   = pmu0(i+1).v
                         E1.re    = pE(i+1).re
                         E1.im    = pE(i+1).im
                         k0a1.v   = pk0a(i+1).v
                         k01.v    = pk0(i+1).v
                         pIz(i+1) = Iz_f4127_zmm16r4(eps01,mu01,E1,k0a1,k01)
                         eps02.v  = peps0(i+2).v
                         mu02.v   = pmu0(i+2).v
                         E2.re    = pE(i+2).re
                         E2.im    = pE(i+2).im
                         k0a2.v   = pk0a(i+2).v
                         k02.v    = pk0(i+2).v
                         pIz(i+2) = Iz_f4127_zmm16r4(eps02,mu02,E2,k0a2,k02)
                         eps03.v  = peps0(i+3).v
                         mu03.v   = pmu0(i+3).v
                         E3.re    = pE(i+3).re
                         E3.im    = pE(i+3).im
                         k0a3.v   = pk0a(i+3).v
                         k03.v    = pk0(i+3).v
                         pIz(i+3) = Iz_f4127_zmm16r4(eps03,mu03,E3,k0a3,k03)
                      end do
             end subroutine Iz_f4127_zmm16r4_unroll4x
             
             
             subroutine Iz_f4127_zmm16r4_rolled(peps0,pmu0,pE,pk0a,
                                                pk0,pIz,n,PF_DIST)
                                                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Iz_f4127_zmm16r4_rolled
                   !dir$ attributes forceinline :: Iz_f4127_zmm16r4_rolled
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Iz_f4127_zmm16r4_rolled
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: peps0
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pmu0
                   type(ZMM16c4),   dimension(1:n), intent(in) :: pE
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0a
                   type(ZMM16r4_t), dimension(1:n), intent(in) :: pk0
                   type(ZMM16c4),   dimension(1:n), intent(out):: pIz
                   integer(kind=i4),                intent(in) :: n
                   integer(kind=i4),                intent(in) :: PF_DIST
                   !Locals
                   type(ZMM16c4),   automatic :: E0
                   !type(ZMM16c4),   automatic :: Iz0,Iz1,Iz2,Iz3
                   type(ZMM16r4_t), automatic :: eps00
                   type(ZMM16r4_t), automatic :: mu00
                   type(ZMM16r4_t), automatic :: k0a0
                   type(ZMM16r4_t), automatic :: k00
                   integer(kind=i4) :: i
                  
                    !dir$ assume_aligned peps0:64
                    !dir$ assume_aligned pmu0:64
                    !dir$ assume_aligned pE:64
                    !dir$ assume_aligned pk0a:64
                    !dir$ assume_aligned pk0:64
                    !dir$ assume_aligned pIz:64
                    !dir$ vector aligned
                    !dir$ ivdep
                    !dir$ vector vectorlength(4)
                    !dir$ vector multiple_gather_scatter_by_shuffles 
                    !dir$ vector always
                  do i=1,n
#if (__RCS_CYLINDER_PF_CACHE_HINT__) == 1
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T0,.true.,.false.)
#elif (__RCS_CYLINDER_PF_CACHE_HINT__) == 2   
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.) 
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T1,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 3
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_T2,.true.,.false.)
#elif (_RCS_CYLINDER_PF_CACHE_HINT__) == 4
                       call mm_prefetch(peps0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pmu0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pE(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0a(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
                       call mm_prefetch(pk0(i+PF_DIST),FOR_K_PREFETCH_NTA,.true.,.false.)
#endif         
                         eps00.v  = peps0(i+0).v
                         mu00.v   = pmu0(i+0).v
                         E0.re    = pE(i+0).re
                         E0.im    = pE(i+0).im
                         k0a0.v   = pk0a(i+0).v
                         k00.v    = pk0(i+0).v
                         pIz(i+0) = Iz_f4127_zmm16r4(eps00,mu00,E0,k0a0,k00)
                     end do
             end subroutine Iz_f4127_zmm16r4_rolled
             
             
              ! /*
              !          Approximation for upper-middle and high-frequency region
              !          (k0a > 2).
              !          Bistatic creeping wave approximation for resonance region
              !          (0<<phi<pi/2, k0a > 2)
              !          Electric-field.
              !      */
              
              
              pure function EO_f4129_zmm16r4(phi2,a,r,k0,k0a,E) result(EO)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: EO_f4129_zmm16r4
                   !dir$ attributes forceinline :: EO_f4129_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: EO_f4129_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16r4_t),  intent(in) :: phi2
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: r
                   type(ZMM16r4_t),  intent(in) :: k0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4),    intent(in) :: E
                   type(ZMM16c4) :: E0
                   ! Locals
                   type(ZMM16r4_t), parameter :: C0375     = ZMM16r4_t(0.375_sp)
                   type(ZMM16r4_t), parameter :: C01171875 = ZMM16r4_t(0.1171875_sp)
                   type(ZMM16r4_t), parameter :: C40       = ZMM16r4_t(4.0_sp)
                   type(ZMM16r4_t), parameter :: C80       = ZMM16r4_t(8.0_sp)
                   type(ZMM16r4_t), parameter :: C330      = ZMM16r4_t(33.0_sp)
                   type(ZMM16r4_t), parameter :: C50       = ZMM16r4_t(5.0_sp)
                   type(ZMM16r4_t), parameter :: C10       = ZMM16r4_t(1.0_sp)
                   type(ZMM16c4),   automatic :: tc0,tc1
                   type(ZMM16c4),   automatic :: ce,ex
                   type(ZMM16c4),   automatic :: tc2
                   type(ZMM16r4_t), automatic :: t0,t1,t2,cosf2
                   type(ZMM16r4_t), automatic :: t3,t4,t5,k0a2
                   type(ZMM16r4_t), automatic :: cos4f2,k0as,fac,a2
                   type(ZMM16r4_t), automatic :: cos2f2,cos4f2,r2,ear
                   cosf2.v  = cos(phi2.v)
                   k0a2.v   = k0a.v+k0a.v
                   r2.v     = r.v*r.v
                   a2.v     = a.v*a.v
                   cos2f2.v = cosf2.v*cosf2.v
                   k0as.v   = k0a.v*k0a.v
                   cos4f2.v = cos2f2.v*cos2f2.v
                   t0.v     = a.v*cosf2.v
                   t1.v     = t0.v/r2.v
                   ear.v    = k0.v*r.v-(a2.v*cosf2.v)
                   fac.v    = sqrt(t1.v)
                   tc0.re   = v16_0.v
                   tc0.im   = ear.v
                   ce       = cexp_c16(tc0)
                   t3.v     = v16_1.v/cos2f2.v
                   tc1      = tc0*ce
                   t3.v     = t3.v*C0375.v
                   t0.v     = C40.v*k0as.v*cos2f2.v
                   t4.v     = v16_1.v/t0.v
                   t1.v     = C80.v*cos2f2.v
                   t2.v     = C01171875.v*(C330.v/t1.v)
                   t0.v     = C70.v/cos4f2.v
                   !tc2.re   = v16_0.v
                   tc2.im   = v16_1.v/(k0a2.v*cosf2.v)
                   tc2.re   = C10.v
                   tc2.im   = C10.v+tc2.im
                   ex       = E*tc1
                   t5.v     = t4.v*(t2.v+t0.v)
                   tc2      = tc2+t5
                   E0       = ex*tc2
              end function EO_f4129_zmm16r4
              
              
              ! /*
              !         Approximation for upper-middle and high-frequency region
              !          (k0a > 2).
              !          Bistatic creeping wave approximation for resonance region
              !          (0<<phi<pi/2, k0a > 2)
              !          Magnetic-field.
              !      */
              
               pure function HO_f4131_zmm16r4(phi2,a,r,k0,k0a,H) result(HO)
                  
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: HO_f4131_zmm16r4
                   !dir$ attributes forceinline :: HO_f4131_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: HO_f4131_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16r4_t),  intent(in) :: phi2
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: r
                   type(ZMM16r4_t),  intent(in) :: k0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4),    intent(in) :: H
                   type(ZMM16c4) :: H0
                   ! Locals
                   type(ZMM16r4_t), parameter :: C0375     = ZMM16r4_t(0.375_sp)
                   type(ZMM16r4_t), parameter :: C01171875 = ZMM16r4_t(0.1171875_sp)
                   type(ZMM16r4_t), parameter :: C40       = ZMM16r4_t(4.0_sp)
                   type(ZMM16r4_t), parameter :: C80       = ZMM16r4_t(8.0_sp)
                   type(ZMM16r4_t), parameter :: C330      = ZMM16r4_t(33.0_sp)
                   type(ZMM16r4_t), parameter :: C50       = ZMM16r4_t(5.0_sp)
                   type(ZMM16r4_t), parameter :: C10       = ZMM16r4_t(1.0_sp)
                   type(ZMM16c4),   automatic :: tc0,tc1
                   type(ZMM16c4),   automatic :: ce,hx
                   type(ZMM16c4),   automatic :: tc2
                   type(ZMM16r4_t), automatic :: t0,t1,t2,cosf2
                   type(ZMM16r4_t), automatic :: t3,t4,t5,k0a2
                   type(ZMM16r4_t), automatic :: cos4f2,k0as,fac,a2
                   type(ZMM16r4_t), automatic :: cos2f2,cos4f2,r2,ear
                   cosf2.v  = cos(phi2.v)
                   k0a2.v   = k0a.v+k0a.v
                   r2.v     = r.v*r.v
                   a2.v     = a.v*a.v
                   cos2f2.v = cosf2.v*cosf2.v
                   k0as.v   = k0a.v*k0a.v
                   cos4f2.v = cos2f2.v*cos2f2.v
                   t0.v     = a.v*cosf2.v
                   t1.v     = t0.v/r2.v
                   ear.v    = k0.v*r.v-(a2.v*cosf2.v)
                   fac.v    = sqrt(t1.v)
                   tc0.re   = v16_0.v
                   tc0.im   = ear.v
                   ce       = cexp_c16(tc0)
                   t3.v     = v16_1.v/cos2f2.v
                   tc1      = tc0*ce
                   t3.v     = t3.v*C0375.v
                   t0.v     = C40.v*k0as.v*cos2f2.v
                   t4.v     = v16_1.v/t0.v
                   t1.v     = C80.v*cos2f2.v
                   t2.v     = C01171875.v*(C330.v/t1.v)
                   t0.v     = C70.v/cos4f2.v
                   !tc2.re   = v16_0.v
                   tc2.im   = v16_1.v/(k0a2.v*cosf2.v)
                   tc2.re   = C10.v
                   tc2.im   = C10.v-tc2.im
                   hx       = H*tc1
                   t5.v     = t4.v*(t2.v+t0.v)
                   tc2      = tc2+t5
                   H0       = hx*tc2
              end function HO_f4131_zmm16r4
              
              
               !/*
               !         Approximation for upper-middle and high-frequency region
               !         (k0a > 2).
               !         Bistatic creeping wave approximation for resonance region
               !         (0<<phi<pi/2, k0a > 2)
               !         Electric-field.
               !         Formula 4.1-30
               !     */
               
               
               pure function EC_f4130_zmm16r4(phi,a,r,k0,k0a,E) result(EC)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: EC_f4130_zmm16r4
                   !dir$ attributes forceinline :: EC_f4130_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: EC_f4130_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1,v16_pi
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: r
                   type(ZMM16r4_t),  intent(in) :: k0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4),    intent(in) :: E
                   type(ZMM16c4) :: EC
                   ! Locals
                   type(ZMM16c4),   parameter :: C09358135i1607129 = ZMM16c4(0.9358135_sp,1.607129_sp)        
                   type(ZMM16C4),   parameter :: C0057397i00994145 = ZMM16c4(0.057397_sp,0.0994145_sp)
                   type(ZMM16r4_t), parameter :: C0261799387799149436538553615273 = &
                                                    ZMM16r4_t(0.261799387799149436538553615273_sp)
                   type(ZMM16r4_t), parameter :: C0166666666666666666666666666667 = &
                                                    ZMM16r4_t(0.166666666666666666666666666667_sp)
                   type(ZMM16r4_t), parameter :: C0666666666666666666666666666667 = &
                                                    ZMM16r4_t(0.666666666666666666666666666667_sp)
                   type(ZMM16r4_t), parameter :: C1333333333333333333333333333333 = &
                                                    ZMM16r4_t(1.333333333333333333333333333333_sp)
                   type(ZMM16r4_t), parameter :: C0910721 = ZMM16r4_t(0.910721_sp)
                   type(ZMM16c4),   automatic :: e1a,ce1
                   type(ZMM16c4),   automatic :: e2a,e3a                   
                   type(ZMM16c4),   automatic :: ce2,ce3
                   type(ZMM16c4),   automatic :: tmp2,tmp3
                   type(ZMM16c4),   automatic :: Et,tmp1
                   type(ZMM16c4),   automatic :: tc0,tc1
                   type(ZMM16r4_t), automatic :: k0ai16,k0apaphi,k0apsphi,korp12
                   type(ZMM16r4_t), automatic :: k0an23,k0an43,t0,sqr,t1
                   k0ai16.v   = k0a.v*C0166666666666666666666666666667.v
                   k0apaphi.v = k0a.v*v16_pi.v+phi.v
                   e2a.re     = v16_0.v
                   e2a.im     = k0apaphi.v
                   t0.v       = k0ai16.v
                   ce2        = cexp_c16(e2a)
                   k0ai16.v   = v16_1.v/t0.v
                   k0apsphi.v = k0a.v*v16_pi.v-phi.v
                   k0rp12.v   = k0.v*r.v+C0261799387799149436538553615273.v
                   e3a.re     = v16_0.v
                   e3a.im     = k0apsphi.v
                   ce3        = cexp_c16(e3a)
                   t0.v       = a.v/(r.v*r.v)
                   sqr.v      = sqrt(t0.v)
                   Et.re      = E.re*sqr.v
                   Et.im      = E.im*sqr.v
                   t0.v       = k0a.v*C0666666666666666666666666666667.v
                   t1.v       = k0a.v*C1333333333333333333333333333333.v
                   e1a.re     = v16_0.v
                   k0an23.v   = v16_1.v/t0.v
                   e1a.im     = k0rp12
                   k0an43.v   = v16_1.v/t1.v
                   ce1        = cexp_c16(e1a)
                   tc0        = C09358135i1607129*v16_1+k0an23
                   tc1        = C0057397i00994145*k0an43
                   tmp1       = tc0-tc1
                   tmp2       = ce2*tmp1
                   tmp3       = ce3*tmp1
                   tc0        = Et*tmp2
                   EC         = tc0+tmp3
               end function EC_f4130_zmm16r4
               
               
               !  /*
               !         Approximation for upper-middle and high-frequency region
               !         (k0a > 2).
               !         Bistatic creeping wave approximation for resonance region
               !         valid only for (0<<phi<pi/2, k0a > 2)
               !         Magnetic-field.
               !         Formula 4.1-32
               !     */
               
               
                pure function HC_f4132_zmm16r4(phi,a,r,k0,k0a,H) result(HC)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: HC_f4132_zmm16r4
                   !dir$ attributes forceinline :: HC_f4132_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: HC_f4132_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1,v16_pi
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: r
                   type(ZMM16r4_t),  intent(in) :: k0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4),    intent(in) :: H
                   type(ZMM16c4) :: HC
                   ! Locals
                   type(ZMM16c4),   parameter :: C0404308i070028   = ZMM16c4(0.404308_sp,0.70028_sp)        
                   type(ZMM16C4),   parameter :: C0072732i01259755 = ZMM16c4(0.072732_sp,-0.1259755_sp)
                   type(ZMM16r4_t), parameter :: C0261799387799149436538553615273 = &
                                                    ZMM16r4_t(0.261799387799149436538553615273_sp)
                   type(ZMM16r4_t), parameter :: C0166666666666666666666666666667 = &
                                                    ZMM16r4_t(0.166666666666666666666666666667_sp)
                   type(ZMM16r4_t), parameter :: C0666666666666666666666666666667 = &
                                                    ZMM16r4_t(0.666666666666666666666666666667_sp)
                   type(ZMM16r4_t), parameter :: C1333333333333333333333333333333 = &
                                                    ZMM16r4_t(1.333333333333333333333333333333_sp)
                   type(ZMM16r4_t), parameter :: C0910721 = ZMM16r4_t(0.910721_sp)
                   type(ZMM16c4),   automatic :: e1a,ce1
                   type(ZMM16c4),   automatic :: e2a,e3a                   
                   type(ZMM16c4),   automatic :: ce2,ce3
                   type(ZMM16c4),   automatic :: tmp2,tmp3
                   type(ZMM16c4),   automatic :: Ht,tmp1
                   type(ZMM16c4),   automatic :: tc0,tc1
                   type(ZMM16r4_t), automatic :: k0ai16,k0apaphi,k0apsphi,korp12
                   type(ZMM16r4_t), automatic :: k0an23,k0an43,t0,sqr,t1
                   k0ai16.v   = k0a.v*C0166666666666666666666666666667.v
                   k0apaphi.v = k0a.v*v16_pi.v+phi.v
                   e2a.re     = v16_0.v
                   e2a.im     = k0apaphi.v
                   t0.v       = k0ai16.v
                   ce2        = cexp_c16(e2a)
                   k0ai16.v   = v16_1.v/t0.v
                   k0apsphi.v = k0a.v*v16_pi.v-phi.v
                   k0rp12.v   = k0.v*r.v+C0261799387799149436538553615273.v
                   e3a.re     = v16_0.v
                   e3a.im     = k0apsphi.v
                   ce3        = cexp_c16(e3a)
                   t0.v       = a.v/(r.v*r.v)
                   sqr.v      = sqrt(t0.v)
                   Ht.re      = H.re*sqr.v
                   Ht.im      = H.im*sqr.v
                   t0.v       = k0a.v*C0666666666666666666666666666667.v
                   t1.v       = k0a.v*C1333333333333333333333333333333.v
                   e1a.re     = v16_0.v
                   k0an23.v   = v16_1.v/t0.v
                   e1a.im     = k0rp12
                   k0an43.v   = v16_1.v/t1.v
                   ce1        = cexp_c16(e1a)
                   tc0        = C0404308i070028*v16_1+k0an23
                   tc1        = C0072732i01259755*k0an43
                   tmp1       = tc0-tc1
                   tmp2       = ce2*tmp1
                   tmp3       = ce3*tmp1
                   tc0        = Ht*tmp2
                   HC         = tc0+tmp3
               end function HC_f4132_zmm16r4
               
               
                ! /*
                ! !
                !       Backscattering creeping-wave approximation for resonance region
                !       (phi == 0, k0a > 2).
                !       Optical wave component e-field, formula 4.1-33
                !   */
                
                
                pure function EO_f4133_zmm16r4(E,a,r,k0,k0a) result(EO)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: EO_f4133_zmm16r4
                   !dir$ attributes forceinline :: EO_f4133_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: EO_f4133_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: E
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16c4) :: EO
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C160 = ZMM16r4_t(16.0_sp)
                   type(ZMM16r4_t),  parameter :: C50  = ZMM16r4_t(5.0_sp)
                   type(ZMM16r4_t),  parameter :: C1270= ZMM16r4_t(127.0_sp)
                   type(ZMM16r4_t),  parameter :: C5120= ZMM16r4_t(512.0_sp)
                   type(ZMM16c4),    automatic :: ea,ce,fac
                   type(ZMM16c4),    automatic :: tc0,ce1
                   type(ZMM16r4_t),  automatic :: r2,k0a2,k0r,k0as
                   type(ZMM16r4_t),  automatic :: t0,t1,t2,t3
                   r2.v   = r.v+r.v
                   k0a2.v = k0a.v+k0a.v
                   t1.v   = a.v/r2.v
                   k0r.v  = k0.v*r.v
                   ea.im  = v16_0.v
                   t0.v   = k0r.v-k0a2.v
                   ea.re  = t0.v
                   t2.v   = sqrt(t1.v)
                   k0as.v = k0a.v*k0a.v
                   fac    = E*t2
                   ce     = cexp_c16(ea)
                   t1.v   = C160.v*k0a.v
                   t2.v   = C5120.v*k0as.v
                   tc0.re = C50.v/t1.v
                   tc0.im = v16_0.v
                   t3.v   = C1270.v/t2.v
                   tc0.re = C10.v+tc0.re
                   tc0.re = t3.v+tc0.re
                   ce1    = fac*ce
                   EO     = ce1*tc0
               end function EO_f4133_zmm16r4
               
              
              !  /*
              !!
              !         Backscattering creeping-wave approximation for resonance region
              !         (phi == 0, k0a > 2).
              !         Optical wave component h-field, formula 4.1-35
              !     */
                                             
              
              pure function HO_f4135_zmm16r4(H,a,r,k0,k0a) result(HO)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: HO_f4135_zmm16r4
                   !dir$ attributes forceinline :: HO_f4135_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: HO_f4135_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: H
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16c4) :: HO
                   !Locals
                   type(ZMM16r4_t),  parameter :: C160 = ZMM16r4_t(16.0_sp)
                   type(ZMM16r4_t),  parameter :: C110 = ZMM16r4_t(11.0_sp)
                   type(ZMM16r4_t),  parameter :: C3530= ZMM16r4_t(353.0_sp)
                   type(ZMM16r4_t),  parameter :: C5120= ZMM16r4_t(512.0_sp)
                   type(ZMM16c4),    automatic :: ea,ce,fac
                   type(ZMM16c4),    automatic :: tc0,ce1
                   type(ZMM16r4_t),  automatic :: r2,k0a2,k0r,k0as
                   type(ZMM16r4_t),  automatic :: t0,t1,t2,t3
                   r2.v   = r.v+r.v
                   k0a2.v = k0a.v+k0a.v
                   t1.v   = a.v/r2.v
                   k0r.v  = k0.v*r.v
                   ea.im  = v16_0.v
                   t0.v   = k0r.v-k0a2.v
                   ea.re  = t0.v
                   t2.v   = sqrt(t1.v)
                   k0as.v = k0a.v*k0a.v
                   fac    = H*t2
                   ce     = cexp_c16(ea)
                   t1.v   = C160.v*k0a.v
                   t2.v   = C5120.v*k0as.v
                   tc0.re = C110.v/t1.v
                   tc0.im = v16_0.v
                   t3.v   = C3530.v/t2.v
                   tc0.re = v16_1.v-tc0.re
                   tc0.re = t3.v+tc0.re
                   ce1    = fac*ce
                   HO     = ce1*tc0
              end function HO_f4135_zmm16r4
             
             
              !  /*
              !!
              !         Backscattering creeping-wave approximation for resonance region
              !         (phi == 0, k0a > 2).
              !         Creeping wave component e-field, formula 4.1-34
              !     */
              
              
              pure function EC_f4134_zmm16r4(E,a,r,k0) result(EC)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: EC_f4134_zmm16r4
                   !dir$ attributes forceinline :: EC_f4134_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: EC_f4134_zmm16r4 
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: E
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16c4) :: EC
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  = &
                                                     ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C0261799387799149436538553615273 = &
                                                     ZMM16r4_t(0.261799387799149436538553615273_sp)
                   type(ZMM16r4_t), parameter :: C2939945 = ZMM16r4_t(2.939945_sp)
                   type(ZMM16r4_t), parameter :: C0180318 = ZMM16r4_t(0.180318_sp)
                   type(ZMM16r4_t), parameter :: C0333333333333333333333333333333333333 = &
                                                     ZMM16r4_t(0.333333333333333333333333333333333333_sp)
                   type(ZMM16r4_t), parameter :: C1821442 = ZMM16r4_t(1.821442_sp)
                   type(ZMM16r4_t), parameter :: C5048945 = ZMM16r4_t(-5.048945_sp)
                   type(ZMM16r4_t), parameter :: C0312320 = ZMM16r4_t(0.312320_sp)
                   type(ZMM16r4_t), parameter :: C0166666666666666666666666666667  = &
                                                     ZMM16r4_t(0.166666666666666666666666666667_sp)
                   type(ZMM16c4),   automatic :: tc0,e1a
                   type(ZMM16c4),   automatic :: ce1,frac
                   type(ZMM16r4_t), automatic :: k0r,k0a
                   type(ZMM16r4_t), automatic :: k0a13,k0an13
                   type(ZMM16r4_t), automatic :: k0an16,r2
                   type(ZMM16r4_t), automatic :: t0,t1
                   type(ZMM16r4_t), automatic :: exar,rex   
                   k0r.v   = k0.v*r.v
                   k0a.v   = k0.v*a.v
                   k0a13.v = k0a.v**C0333333333333333333333333333333333333.v
                   r2.v    = r.v+r.v
                   t1.v    = k0a.v**C0166666666666666666666666666667.v
                   t0.v    = a.v/r2.v
                   k0an16.v= v16_1.v/t1.v
                   t2.v    = sqrt(t0.v)
                   frac    = E*t2
                   t0.v    = C2939945.v*k0a13.v-(C0180318.v*k0an13.v)
                   t1.v    = k0a.v*C314159265358979323846264338328.v+ &
                             (C0261799387799149436538553615273.v+t0.v)
                   e1a.im  = v16_0.v
                   t1.v    = k0r.v+t1.v
                   e1a.re  = t1.v
                   ce1     = cexp_c16(e1a)
                   exar.v  = C5048945.v*k0a13.v-(C0312320.v*k0an13.v)
                   t1.v    = C1821442.v*k0an16.v
                   t2.v    = exp(exar.v)
                   rex.v   = v16_1.v/t2.v
                   tc0     = frac*ce1 
                   rex.v   = rex.v*t1.v
                   EC      = tc0*rex
              end function EC_f4134_zmm16r4
              
              
              !  /*
              !!
              !         Backscattering creeping-wave approximation for resonance region
              !         (phi == 0, k0a > 2).
              !         Creeping wave component h-field, formula 4.1-36
              !     */
              
              
              pure function HC_f4136_zmm16r4(H,a,r,k0) result(HC)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: HC_f4136_zmm16r4
                   !dir$ attributes forceinline :: HC_f4136_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: HC_f4136_zmm16r4 
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: H
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16c4) :: HC
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  = &
                                                     ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C0261799387799149436538553615273 = &
                                                     ZMM16r4_t(0.261799387799149436538553615273_sp)
                   type(ZMM16r4_t), parameter :: C12701695 = ZMM16r4_t(1.2701695_sp)
                   type(ZMM16r4_t), parameter :: C02284945 = ZMM16r4_t(0.2284945_sp)
                   type(ZMM16r4_t), parameter :: C0333333333333333333333333333333333333 = &
                                                     ZMM16r4_t(0.333333333333333333333333333333333333_sp)
                   type(ZMM16r4_t), parameter :: C3063830 = ZMM16r4_t(3.063830_sp)
                   type(ZMM16r4_t), parameter :: C2200000 = ZMM16r4_t(-2.200000_sp)
                   type(ZMM16r4_t), parameter :: C03957635 = ZMM16r4_t(0.3957635_sp)
                   type(ZMM16r4_t), parameter :: C0166666666666666666666666666667  = &
                                                     ZMM16r4_t(0.166666666666666666666666666667_sp)
                   type(ZMM16c4),   automatic :: tc0,e1a
                   type(ZMM16c4),   automatic :: ce1,frac
                   type(ZMM16r4_t), automatic :: k0r,k0a
                   type(ZMM16r4_t), automatic :: k0a13,k0an13
                   type(ZMM16r4_t), automatic :: k0an16,r2
                   type(ZMM16r4_t), automatic :: t0,t1
                   type(ZMM16r4_t), automatic :: exar,rex   
                   k0r.v   = k0.v*r.v
                   k0a.v   = k0.v*a.v
                   k0a13.v = k0a.v**C0333333333333333333333333333333333333.v
                   r2.v    = r.v+r.v
                   t1.v    = k0a.v**C0166666666666666666666666666667.v
                   t0.v    = a.v/r2.v
                   k0an16.v= v16_1.v/t1.v
                   t2.v    = sqrt(t0.v)
                   frac    = H*t2
                   t0.v    = C12701695.v*k0a13.v-(C02284945.v*k0an13.v)
                   t1.v    = k0a.v*C314159265358979323846264338328.v+ &
                             (C0261799387799149436538553615273.v+t0.v)
                   e1a.im  = v16_0.v
                   t1.v    = k0r.v+t1.v
                   e1a.re  = t1.v
                   ce1     = cexp_c16(e1a)
                   exar.v  = C2200000.v*k0a13.v-(C03957635.v*k0an13.v)
                   t1.v    = C3063830.v*k0an16.v
                   t2.v    = exp(exar.v)
                   rex.v   = v16_1.v/t2.v
                   tc0     = frac*ce1 
                   rex.v   = rex.v*t1.v
                   HC      = tc0*rex
              end function HC_f4136_zmm16r4
              
              
              !  /*
              !          Bistatic scattering width in high frequency limit (k0a > 20)
              !          for |PI-phi| > k0a^0.3
              !          Formula 4.1-37
              !      */
              
              pure function rcs_f4137_zmm16r4(a,phi2) result(rcs)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4137_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4137_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4137_zmm16r4
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t), intent(in) :: phi2
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  = &
                                                     ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), automatic :: cosp2,t0
                   cosp2.v = cos(phi2.v)
                   t0.v    = a.v*cosp2.v
                   rcs.v   = C314159265358979323846264338328.v*t0.v
              end function rcs_f4137_zmm16r4
              
              
              !    /*
              !           Backscattering Width in High-Frequency Limit (k0a > 20)
              !            Formula 4.1-38
              !       */
              
              
              pure function rcs_f4138_zmm16r4(a) result(rcs)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4138_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4138_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4138_zmm16r4
                   type(ZMM16r4_t), intent(in) :: a
                   type(ZMM16r4_t) :: rcs
                   ! LOcals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  = &
                                                     ZMM16r4_t(3.14159265358979323846264338328_sp)
                   rcs.v = a.v*C314159265358979323846264338328.v
              end function rcs_f4138_zmm16r4
              
              
               ! /*
               !          Forward scattering widths and pattern in high-frequency limit
               !          (k0a>20.0)
               !          Formula 4.1-40, RCS.
               !      */
               
               pure function rcs_f4140_zmm16r4(k0a,alpha) result(rcs)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4140_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4140_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4140_zmm16r4 
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: alpha
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C40 = ZMM16r4_t(4.0_sp)
                   type(ZMM16r4_t), automatic :: sinc,k0alp
                   type(ZMM16r4_t), automatic :: k0as,t0
                   k0alp.v = k0a.v*alpha.v
                   t0.v    = sin(k0alp.v)
                   sinc.v  = t0.v/k0alp.v
                   k0as.v  = C40.v*k0a.v*k0a.v
                   rcs.v   = k0as.v*sinc.v*sinc.v
               end function rcs_f4140_zmm16r4
               
               
               !  /*
               !          Forward scattering widths and pattern in high-frequency limit
               !          (k0a>20.0), forward scattered (diffracted) e-field
               !          Formula 4.1-39.
               !!
               !        */
               
               pure function Es_f4139_zmm16r4(E,r,k0,alp,k0a) result(Es)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Es_f4139_zmm16r4
                   !dir$ attributes forceinline :: Es_f4139_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Es_f4139_zmm16r4
                   use mod_vecconsts, only : v16_0
                   type(ZMM16c4),   intent(in) :: E
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: alp
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16c4) :: Es
                   ! Locals
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: fac,ar
                   type(ZMM16C4),   automatic :: tc0,ce
                   type(ZMM16r4_t), automatic :: k0as2,k0r,k0alp
                   type(ZMM16r4_t), automatic :: sinc,div,t0
                   k0r.v   = k0.v*r.v
                   k0alp.v = k0a.v*alp.v
                   k0as2.v = c20.v+k0a.v*k0a.v
                   div.v   = k0as.v/C078539816339744830961566084582.v
                   ar.im   = v16_0.v
                   t0.v    = sin(k0alp.v)
                   ar.re   = k0r.v-C078539816339744830961566084582.v
                   sinc.v  = t0.v/k0alp.v
                   ce      = cexp_c16(ar)
                   t0.v    = sqrt(div.v)
                   fac     = E*t0
                   tc0     = ce*sinc
                   Es      = fac*tc0
               end function Es_f4139_zmm16r4
               
               
               !  /*
               !          Forward scattering widths and pattern in high-frequency limit
               !          (k0a>20.0), constant angle (alpha=0)
               !          Formula 4.1-41, RCS.
               !      */
               
               
               pure function rcs_f4141_zmm16r4(k0a) result(rcs)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4141_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4141_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4141_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :; C40 = ZMM16r4_t(4.0_sp)
                   rcs.v = C40.v*k0a.v*k0a.v 
               end function rcs_f4141_zmm16r4
               
               
               
               !    /*
               !         Approximations for the low frequency region (k0a<<1,k1a<<1)
               !         Scattered far-zone e-field, formula 4.1-45
               !     */
               
               
               pure function Es_f4145_zmm16r4(EI,r,k0,k0a,phi,  &
                                              eps0,eps1,mu0,mu1) result(Es)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Es_f4145_zmm16r4
                   !dir$ attributes forceinline :: Es_f4145_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Es_f4145_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: EI
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: eps0
                   type(ZMM16r4_t), intent(in) :: eps1
                   type(ZMM16r4_t), intent(in) :: mu0
                   type(ZMM16r4_t), intent(in) :: mu1
                   type(ZMM16c4) :: Es
                   !Locals
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), parameter :: C05 = ZMM16r4_t(0.5_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C1253314137315500251207882642406 = &
                                                       ZMM16r4_t(1.253314137315500251207882642406_sp)
                   type(ZMM16c4),   automatic :: frac,ea
                   type(ZMM16c4),   automatic :: ce,tc0
                   type(ZMM16r4_t), automatic :: k0r,k0as,k0as2,t0
                   type(ZMM16r4_t), automatic :: t1,cosp,t2,sk0r
                   type(ZMM16r4_t), automatic :: t3,mul
                   k0r.v   = k0.v*r.v
                   k0as.v  = k0a.v*k0a.v
                   k0as2.v = C05.v*k0as.v
                   sk0r.v  = sqrt(k0r.v)
                   frac    = EI*C1253314137315500251207882642406.v
                   cosp.v  = cos(phi)
                   ea.re   = k0r.v-C078539816339744830961566084582.v
                   t0.v    = (eps1.v/eps0.v)-v16_1.v
                   ea.im   = v16_0.v
                   t1.v    = (mu1.v-mu0.v)/(mu1.v+mu0.v)
                   t2.v    = t1.v+t1.v
                   ce      = cexp_c16(ea)
                   t1.v    = t2.v*cosp.v
                   ce.re   = ce.re/sk0r.v
                   t3.v    = t0.v-t1.v
                   ce.im   = ce.im/sk0r.v
                   mul.v   = k0as2.v*t3.v
                   tc0     = ce*mul
                   Es      = frac*tc0
               end function Es_f4145_zmm16r4
               
               
               ! /*
               !         Approximations for the low frequency region (k0a<<1,k1a<<1)
               !         Scattered far-zone h-field, formula 4.1-46
               !     */
               
               pure function Hs_f4146_zmm16r4(HI,r,k0,k0a,phi,  &
                                              eps0,eps1,mu0,mu1) result(Hs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Hs_f4146_zmm16r4
                   !dir$ attributes forceinline :: Hs_f4146_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Hs_f4146_zmm16r4
                   use mod_vecconsts, only : v16_0,v16_1
                   type(ZMM16c4),   intent(in) :: HI
                   type(ZMM16r4_t), intent(in) :: r
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: k0a
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: eps0
                   type(ZMM16r4_t), intent(in) :: eps1
                   type(ZMM16r4_t), intent(in) :: mu0
                   type(ZMM16r4_t), intent(in) :: mu1
                   type(ZMM16c4) :: Hs
                   !Locals
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), parameter :: C05 = ZMM16r4_t(0.5_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C1253314137315500251207882642406 = &
                                                       ZMM16r4_t(1.253314137315500251207882642406_sp)
                   type(ZMM16c4),   automatic :: frac,ea
                   type(ZMM16c4),   automatic :: ce,tc0
                   type(ZMM16r4_t), automatic :: k0r,k0as,k0as2,t0
                   type(ZMM16r4_t), automatic :: t1,cosp,t2,sk0r
                   type(ZMM16r4_t), automatic :: t3,mul
                   k0r.v   = k0.v*r.v
                   k0as.v  = k0a.v*k0a.v
                   k0as2.v = C05.v*k0as.v
                   sk0r.v  = sqrt(k0r.v)
                   frac    = HI*C1253314137315500251207882642406.v
                   cosp.v  = cos(phi)
                   ea.re   = k0r.v-C078539816339744830961566084582.v
                   t0.v    = (mu1.v/mu0.v)-v16_1.v
                   ea.im   = v16_0.v
                   t1.v    = (eps1.v-eps0.v)/(eps1.v+eps0.v)
                   t2.v    = t1.v+t1.v
                   ce      = cexp_c16(ea)
                   t1.v    = t2.v*cosp.v
                   ce.re   = ce.re/sk0r.v
                   t3.v    = t0.v-t1.v
                   ce.im   = ce.im/sk0r.v
                   mul.v   = k0as2.v*t3.v
                   tc0     = ce*mul
                   Hs      = frac*tc0
               end function Hs_f4146_zmm16r4
               
               
               !/*
               !       Bistatic scattering width (k0a<<1, k1a<<1) at the angle 'phi'
               !       Formula 4.1-47
               !!
               !    */ 
               
               pure function rcs_f4147_zmm16r4(a,k0a,phi,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4147_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4147_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4147_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,cosp,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   cosp.v  = cos(phi.v)
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = eps1.v/eps0.v-v16_1.v
                   t1.v    = mu1.v-mu0.v
                   t2.v    = mu1.v+mu0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v*cosp.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4147_zmm16r4
               
               
               ! /*
               !       Bistatic scattering width (k0a<<1, k1a<<1) at the angle 'phi'
               !       Formula 4.1-48
               !!
               !    */   
               
               pure function rcs_f4148_zmm16r4(a,k0a,phi,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4148_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4148_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4148_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,cosp,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   cosp.v  = cos(phi.v)
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = mu1.v/mu0.v-v16_1.v
                   t1.v    = eps1.v-eps0.v
                   t2.v    = eps1.v+eps0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v*cosp.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4148_zmm16r4
               
               
               ! /*
               !          Backscattering width (k0a<<1,k1a<<1), when phi = 0
               !          Formula 4.1-49
               !     */ 
               
               pure function rcs_f4149_zmm16r4(a,k0a,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4149_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4149_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4149_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = eps1.v/eps0.v-v16_1.v
                   t1.v    = mu1.v-mu0.v
                   t2.v    = mu1.v+mu0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4149_zmm16r4
               
               
              !  /*
              !           Backscattering width (k0a<<1,k1a<<1), when phi = 0
              !           Formula 4.1-50
              !      */ 
              
               pure function rcs_f4150_zmm16r4(a,k0a,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4150_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4150_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4150_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = mu1.v/mu0.v-v16_1.v
                   t1.v    = eps1.v-eps0.v
                   t2.v    = eps1.v+eps0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4150_zmm16r4
               
               
              ! /*
              !           Forward scattering width (k0a<<1, k1a<<1), phi = pi
              !           Formula 4.1-51
              !       */ 
              
                pure function rcs_f4151_zmm16r4(a,k0a,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4151_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4151_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4151_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = eps1.v/eps0.v-v16_1.v
                   t1.v    = mu1.v-mu0.v
                   t2.v    = mu1.v+mu0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4151_zmm16r4
               
               
               ! /*
               !          Forward scattering width (k0a<<1, k1a<<1), phi = pi
               !          Formula 4.1-52
               !      */
              
              
               pure function rcs_f4152_zmm16r4(a,k0a,eps1,   &
                                          eps0,mu1,mu0) result(rcs)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4152_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4152_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4152_zmm16r4
                   use mod_veconsts, only : v16_1
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: eps1
                   type(ZMM16r4_t),  intent(in) :: eps0
                   type(ZMM16r4_t),  intent(in) :: mu1
                   type(ZMM16r4_t),  intent(in) :: mu0
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328  =
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), automatic :: t0,t1,k0a3,epst
                   type(ZMM16r4_t), automatic :: mut,sqr
                   type(ZMM16r4_t), automatic :: t2,diff
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   t0.v    = C078539816339744830961566084582.v* &
                             C314159265358979323846264338328.v*a.v
                   epst.v  = mu1.v/mu0.v-v16_1.v
                   t1.v    = eps1.v-eps0.v
                   t2.v    = eps1.v+eps0.v
                   mut.v   = C20.v*(t1.v/t2.v)
                   diff.v  = epst.v-mut.v
                   sqr.v   = diff.v*diff.v
                   rcs.v   = t0.v*k0a3.v*sqr.v
               end function rcs_f4152_zmm16r4
               
               
               ! /*
               !            Fresnel reflection and transmission coefficients
               !            Formula 4.1-72
               !        */
               
               
               pure function Tin_f4172_zmm16r4(mu,eps,psi) result(Tin)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tin_f4172_zmm16r4
                   !dir$ attributes forceinline :: Tin_f4172_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tin_f4172_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),    intent(in) :: mu
                   type(ZMM16c4),    intent(in) :: eps
                   type(ZMM16r4_t),  intent(in) :: psi
                   type(ZMM16c4)  :: Tin
                   ! Locals
                   type(ZMM16c4),  automatic :: div,sq1
                   type(ZMM16c4),  automatic :: sq2,mul
                   type(ZMM16c4),  automatic :: tc0,tc1
                   type(ZMM16c4),  automatic :: tc2,tc3
                   type(ZMM16r4_t),automatic :: sin2p,cosp
                   type(ZMM16r4_t),automatic :: t0,t1
                   div    = mu/eps
                   t0.v   = sin(psi.v)
                   cosp.v = cos(psi.v)
                   sin2p.v= t0.v*t0.v
                   t1.v   = v16_1.v-sin2p.v
                   mul    = mu*eps
                   sq1    = csqrt_c16(div)
                   tc0    = t1/mul
                   sq2    = csqrt_c16(tc0)
                   tc2.re = sq1.re+sq1.re
                   tc2.im = v16_0.v
                   tc1    = tc2*sq2
                   tc3    = sq1*sq2
                   tc3.re = cosp.v+tc3.re
                   tc3.im = v16_0.v
                   Tin    = tc1/tc3
               end function Tin_f4172_zmm16r4
               
               
               ! /*
               !            Fresnel reflection and transmission coefficients
               !            Formula 4.1-73
               !        */
               
               pure function Tin_f4173_zmm16r4(mu,eps,psi) result(Tin)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tin_f4173_zmm16r4
                   !dir$ attributes forceinline :: Tin_f4173_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tin_f4173_zmm16r4 
                   use mod_vecconsts, only : v16_1
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16c4) :: Tin
                   ! Locals
                   type(ZMM16c4),  automatic :: div,sq1
                   type(ZMM16c4),  automatic :: sq2,mul
                   type(ZMM16c4),  automatic :: tc0
                   type(ZMM16r4_t),automatic :: cosp,cos2p
                   type(ZMM16r4_t),automatic :: sinp,sin2p
                   type(ZMM16r4_t),automatic :: msp1
                   mul    = mu*esp
                   cosp.v = cos(psi.v)
                   div    = eps/mu
                   sinp.v = sin(psi.v)
                   cos2p.v= cosp.v+cosp.v
                   sin2p.v= sinp.v+sinp.v
                   msp1.v = v16_1.v-sin2p.v
                   sq1    = csqrt_c16(div)
                   tc0    = msp1/mul
                   sq2    = csqrt_c16(tc0)
                   Tin    = sq1*sq2+cosp
               end function Tin_f4173_zmm16r4
               
               
              
                 !   /*
                 !          Fresnel reflection and transmission coefficients
                 !          Formula 4.1-74
                 !      */
                 
               pure function Tout_f4174_zmm16r4(mu,eps,psi) result(Tout)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tout_f4174_zmm16r4
                   !dir$ attributes forceinline :: Tout_f4174_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tout_f4174_zmm16r4 
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16c4) :: Tout
                   ! Locals
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16c4),   automatic :: div,sq1
                   type(ZMM16c4),   automatic :: sq2,mul
                   type(ZMM16c4),   automatic :: tc0,tc1
                   type(ZMM16c4),   automatic :: num,den
                   type(ZMM16r4_t), automatic :: cosp,sinp
                   type(ZMM16r4_t), automatic :: sin2p,t0
                   div    = eps/mu
                   cosp.v = cos(psi.v)
                   mul    = eps*mu
                   sinp.v = sin(psi.v)
                   sq1    = csqrt_c16(div)
                   sin2p.v= sinp.v*sinp.v
                   t0.v   = mul.re*sinp.v
                   tc0.re = v16_1.v-t0.v
                   tc0.im = t0.v
                   sq2    = csqrt_c16(tc0)
                   tc1    = sq1*tc0
                   num.re = C20.v*tc1.re
                   num.im = C20.v*tc1.im
                   den.re = cosp.v+tc1.re
                   den.im = v16_0.v
                   Tout   = num/den
               end function Tout_f4174_zmm16r4
               
               
               
               !    /*
               !            Fresnel reflection and transmission coefficients
               !            Formula 4.1-75
               !        */
               
               pure function Tout_f4175_zmm16r4(mu,eps,psi) result(Tout)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tout_f4175_zmm16r4
                   !dir$ attributes forceinline :: Tout_f4175_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tout_f4175_zmm16r4  
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16c4) :: Tout
                   type(ZMM16c4),   automatic :: div,sq1
                   type(ZMM16c4),   automatic :: sq2,mul
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16c4),   automatic :: num,den
                   type(ZMM16r4_t), automatic :: cosp,sinp
                   type(ZMM16r4_t), automatic :: sin2p,cos2p
                   div    = mu/eps
                   cosp.v = cos(psi.v)
                   mul    = eps*mu
                   sinp.  = sin(psi.v)
                   cos2p.v= cosp.v+cosp.v
                   sq2    = csqrt_c16(div)
                   sin2p.v= sinp.v*sinp.v
                   tc0.re = v16_1.v-mul.re*sin2p.v
                   tc0.im = mul.im*sin2p.v
                   sq1    = csqrt_c16(tc0)
                   den    = sq1*sq2
                   den.re = den.re+cosp.v
                   Tout   = cos2p/den
               end function Tout_f4175_zmm16r4
               
               
               !  /*
               !            Fresnel reflection and transmission coefficients
               !            Formula 4.1-76
               !     */
               
               pure function Rin_f4176_zmm16r4(mu,eps,psi) result(Rin)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Rin_f4176_zmm16r4
                   !dir$ attributes forceinline :: Rin_f4176_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Rin_f4176_zmm16r4  
                   use mod_vecconsts, only : v16_1
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16c4) :: Rin
                   ! Locals
                   type(ZMM16c4),   automatic :: div,mul
                   type(ZMM16c4),   automatic :: den,num
                   type(ZMM16c4),   automatic :: sq1,sq2
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16r4_t), automatic :: cosp,sinp
                   type(ZMM16r4_t), automatic :: sin2p
                   div    = mu/eps
                   sinp.v = sin(psi.v)
                   mul    = mu*eps
                   sq2    = csqrt_c16(div)
                   sin2p.v= sinp.v+sinp.v
                   tc0    = sin2p/mul
                   cosp.v = cos(psi.v)
                   tc0.re = v16_1.v-tc0.re
                   tc0.im = -tc0.im
                   sq1    = csqrt_c16(tc0)
                   sq2.re = cosp.v*sq2.re
                   sq2.im = cosp.v*sq2.im
                   num    = sq2-sq1
                   den    = sq2+sq1
                   Rin    = num/den
               end function Rin_f4176_zmm16r4
               
               
                !  /*
                !           Fresnel reflection and transmission coefficients
                !           Formula 4.1-77
                !    */

               pure function Rin_f4177_zmm16r4(mu,eps,psi) result(Rin)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Rin_f4177_zmm16r4
                   !dir$ attributes forceinline :: Rin_f4177_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Rin_f4177_zmm16r4  
                   use mod_vecconsts, only : v16_1
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16c4) :: Rin
                   ! Locals
                   type(ZMM16c4),   automatic :: div,mul
                   type(ZMM16c4),   automatic :: den,num
                   type(ZMM16c4),   automatic :: sq1,sq2
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16r4_t), automatic :: cosp,sinp
                   type(ZMM16r4_t), automatic :: sin2p
                   div    = mu/eps
                   sinp.v = sin(psi.v)
                   mul    = mu*eps
                   sq2    = csqrt_c16(div)
                   sin2p.v= sinp.v+sinp.v
                   cosp.v = cos(psi.v)
                   tc0    = mul*sin2p
                   tc0.re = v16_1.v-tc0.re
                   sq1    = csqrt_c16(tc0)
                   sq2.re = cosp.v*sq2.re
                   sq2.im = cosp.v*sq2.im
                   num    = sq2-sq1
                   den    = sq2+sq1
                   Rin    = num/den
               end function Rin_f4177_zmm16r4
               
               
               ! /*
               !           Specular rays reflection
               !           Formula 4.1-64
               !       */
               
               pure function Rext_f4164_zmm16r4(mu,eps) result(Rext)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Rext_f4164_zmm16r4
                   !dir$ attributes forceinline :: Rext_f4164_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Rext_f4164_zmm16r4
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4) :: Rext
                   ! Locals
                   type(ZMM16c4),  automatic :: sq1,sq2
                   type(ZMM16c4),  automatic :: dif,summ
                   sq1  = csqrt_c16(mu)
                   sq2  = csqrt_c16(eps)
                   dif  = sq1-sq2
                   summ = sq1+sq2 
                   Rext = dif/summ
               end function Rext_f4164_zmm16r4
               
               
                ! /*
                !!
                !         Axial rays, when phi = 0
                !         Formula 4.1-67
                !    */
                
                pure function Tin_f4167_zmm16r4(mu,eps) result(Tin)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tin_f4167_zmm16r4
                   !dir$ attributes forceinline :: Tin_f4167_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tin_f4167_zmm16r4
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4) :: Tin
                   ! Locals
                   type(ZMM16c4),  automatic :: sq1,sq2
                   type(ZMM16c4),  automatic :: summ,mu2
                   sq1  = csqrt_c16(mu)
                   mu2  = sq1+sq1
                   sq2  = csqrt_c16(eps)
                   summ = sq1+sq2
                   Tin  = mu2/summ
                end function Tin_f4167_zmm16r4
                
                
                  !/*
                  !        Axial rays, when phi = 0
                  !        Formula 4.1-68
                  ! */
                  
                pure function Tout_f4168_zmm16r4(mu,eps) result(Tout)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Tout_f4168_zmm16r4
                   !dir$ attributes forceinline :: Tout_f4168_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Tout_f4168_zmm16r4
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4) :: Tout
                   ! Locals
                   type(ZMM16c4),  automatic :: sq1,sq2
                   type(ZMM16c4),  automatic :: summ,eps2
                   sq1  = csqrt_c16(eps)
                   eps2 = sq1+sq1
                   sq2  = csqrt_c16(mu)
                   summ = sq1+sq2
                   Tout = eps2/summ
                end function Tout_f4168_zmm16r4
                
                
                 !/*
                 !         Axial rays, when phi = 0
                 !         Formula 4.1-69
                 !  */
                 
                pure function Rint_f4169_zmm16r4(mu,eps) result(Rint)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Rint_f4169_zmm16r4
                   !dir$ attributes forceinline :: Rint_f4169_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Rint_f4169_zmm16r4
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4) :: Rint
                   ! Locals
                   type(ZMM16r4_t), parameter :: Cn10 = ZMM16r4_t(-1.0_sp)
                   type(ZMM16c4),   automatic :: tc0
                   tc0  = Rext_f4164_zmm16r4(mu,eps)
                   Rint = tc0*Cn10
                end function Rint_f4169_zmm16r4
                
                
                 !  /*
                 !      Backscatter widths in high-frequency limit.
                 !      Phi = 0, formula 4.1-91,for k1a>5.
                 !   */
                 
                pure function rcs_f4191_zmm16r4(a,mu,eps) result(rcs)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4191_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4191_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4191_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16c4),    intent(in) :: mu
                   type(ZMM16c4),    intent(in) :: eps
                   type(ZMM16r4_t) :: rcs
                   ! LOcals
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328 = &
                                                    ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16r4_t), automatic :: cab
                   tc0   = Rext_f4164_zmm16r4(mu,eps)
                   cab   = cabs_c16(tc0)
                   rcs.v = cab.v*C314159265358979323846264338328.v*a.v
                end function rcs_f4191_zmm16r4
                
                
                !  /*
                !         Bistatic scattering width (k0a0<<1, k1a0<<1), function of phi angle.
                !         Formula 4.1-104
                !      */
                
                pure function rcs_f41104_zmm16r4(a0,a1,k0a0,phi,mu1,  &
                                                 mu0,eps1,eps0)     result(rcs)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f41104_zmm16r4
                   !dir$ attributes forceinline :: rcs_f41104_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f41104_zmm16r4
                   use mod_vecconsts, inly : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16c4),    intent(in) :: mu1
                   type(ZMM16c4),    intent(in) :: mu0
                   type(ZMM16c4),    intent(in) :: eps1
                   type(ZMM16c4),    intent(in) :: eps0
                   type(ZMM16r4_t) :: rcs
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328 = &
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16c4),   automatic :: div,e1m
                   type(ZMM16c4),   automatic :: tc1,tc0
                   type(ZMM16c4),   automatic :: e0m,div2
                   type(ZMM16c4),   automatic :: num,den
                   type(ZMM16r4_t), automatic :: pia,k0a03
                   type(ZMM16r4_t), automatic :: a1a0,pa1
                   type(ZMM16r4_t), automatic :: ma1,cab
                   type(ZMM16r4_t), automatic :: cosp,frac
                   type(ZMM16r4_t), automatic :: a1a0s
                   k0a03.v =  k0a.v*k0a.v*k0a.v
                   pia.v   =  C314159265358979323846264338328.v*a.v
                   cosp.v  = cos(phi.v)
                   frac.v  = pia.v*C078539816339744830961566084582.v*k0a03.v
                   a1a0.v  = a1.v/a0.v
                   a1a0s.v = a1a0.v*a1a0.v
                   pa1.v   = v16_1.v+a1a0s.v
                   e1m     = eps1*pa1
                   ma1.v   = v16_1.v-a1a0s.v
                   div     = mu1/mu0
                   e0m     = eps0*ma1
                   tc0     = (div*ma1)-v16_1
                   num     = e1m-e0m
                   den     = e1m+e0m
                   div2    = num/den
                   div2    = C20*div2*cosp
                   tc1     = tc0-div2
                   cab     = cabs_c16(tc1)
                   rcs.v   = frac.v*cab.v
                end function rcs_f41104_zmm16r4
                
                
                 ! /*
                 !        Backscattering  width (k0a0<<1, k1a0<<1), phi = 0
                 !        Formula 4.1-105
                 ! */
                 
                pure function rcs_f41105_zmm16r4(a0,a1,k0a0,mu1,  &
                                                 mu0,eps1,eps0)     result(rcs)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f41105_zmm16r4
                   !dir$ attributes forceinline :: rcs_f41105_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f41105_zmm16r4
                   use mod_vecconsts, inly : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: mu1
                   type(ZMM16c4),    intent(in) :: mu0
                   type(ZMM16c4),    intent(in) :: eps1
                   type(ZMM16c4),    intent(in) :: eps0
                   type(ZMM16r4_t) :: rcs
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328 = &
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16c4),   automatic :: div,e1m
                   type(ZMM16c4),   automatic :: tc1,tc0
                   type(ZMM16c4),   automatic :: e0m,div2
                   type(ZMM16c4),   automatic :: num,den
                   type(ZMM16r4_t), automatic :: pia,k0a03
                   type(ZMM16r4_t), automatic :: a1a0,pa1
                   type(ZMM16r4_t), automatic :: ma1,cab
                   type(ZMM16r4_t), automatic :: frac,a1a0s
                   k0a03.v =  k0a.v*k0a.v*k0a.v
                   pia.v   =  C314159265358979323846264338328.v*a.v
                   frac.v  = pia.v*C078539816339744830961566084582.v*k0a03.v
                   a1a0.v  = a1.v/a0.v
                   a1a0s.v = a1a0.v*a1a0.v
                   pa1.v   = v16_1.v+a1a0s.v
                   e1m     = eps1*pa1
                   ma1.v   = v16_1.v-a1a0s.v
                   div     = mu1/mu0
                   e0m     = eps0*ma1
                   tc0     = (div*ma1)-v16_1
                   num     = e1m-e0m
                   den     = e1m+e0m
                   div2    = num/den
                   div2    = C20*div2
                   tc1     = tc0-div2
                   cab     = cabs_c16(tc1)
                   rcs.v   = frac.v*cab.v
                end function rcs_f41105_zmm16r4  
                
                
                !/*
                !      Forward scattering width (k0a0<<1, k1a0<<1), phi = pi.
                !      Formula 4.1-106
                ! */
                
                pure function rcs_f41106_zmm16r4(a0,a1,k0a0,mu1,  &
                                                 mu0,eps1,eps0)     result(rcs)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f41106_zmm16r4
                   !dir$ attributes forceinline :: rcs_f41106_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f41106_zmm16r4
                   use mod_vecconsts, inly : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: mu1
                   type(ZMM16c4),    intent(in) :: mu0
                   type(ZMM16c4),    intent(in) :: eps1
                   type(ZMM16c4),    intent(in) :: eps0
                   type(ZMM16r4_t) :: rcs
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C314159265358979323846264338328 = &
                                                       ZMM16r4_t(3.14159265358979323846264338328_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16c4),   automatic :: div,e1m
                   type(ZMM16c4),   automatic :: tc1,tc0
                   type(ZMM16c4),   automatic :: e0m,div2
                   type(ZMM16c4),   automatic :: num,den
                   type(ZMM16r4_t), automatic :: pia,k0a03
                   type(ZMM16r4_t), automatic :: a1a0,pa1
                   type(ZMM16r4_t), automatic :: ma1,cab
                   type(ZMM16r4_t), automatic :: frac,a1a0s
                   k0a03.v =  k0a.v*k0a.v*k0a.v
                   pia.v   =  C314159265358979323846264338328.v*a.v
                   frac.v  = pia.v*C078539816339744830961566084582.v*k0a03.v
                   a1a0.v  = a1.v/a0.v
                   a1a0s.v = a1a0.v*a1a0.v
                   pa1.v   = v16_1.v+a1a0s.v
                   e1m     = eps1*pa1
                   ma1.v   = v16_1.v-a1a0s.v
                   div     = mu1/mu0
                   e0m     = eps0*ma1
                   tc0     = (div*ma1)-v16_1
                   num     = e1m-e0m
                   den     = e1m+e0m
                   div2    = num/den
                   div2    = C20*div2
                   tc1     = tc0+div2
                   cab     = cabs_c16(tc1)
                   rcs.v   = frac.v*cab.v
                end function rcs_f41106_zmm16r4  
                
                
                 !/*
                 !      Hollow cylindrical shell.
                 !      Approximations for the low frequency region
                 ! !     (k0a0<<1, k1a0<<1).
                 !      Formula 4.1-124
                 ! */
                 
                pure function A0_f41124_zmm16r4(a1,a0,k0a0,eps1,eps0) result(A0)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: A0_f41124_zmm16r4
                   !dir$ attributes forceinline :: A0_f41124_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: A0_f41124_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: eps1
                   type(ZMM16c4),    intent(in) :: eps0
                   type(ZMM16c4) :: A0
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: frac,div
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16r4_t), automatic :: k0a02,a1a0
                   type(ZMM16r4_t), automatic :: a1a0s,ma1
                   k0a02.v  = k0a.v*k0a.v
                   a1a0.v   = a1.v/a0.v
                   a1a0s.v  = a1a0.v*a1a0.v
                   frac.re  = C078539816339744830961566084582.v*k0a02.v
                   ma1.v    = v16_1.v-a1a0s.v
                   frac.im  = v16_0.v
                   div      = eps1/eps0
                   div      = div-v16_1
                   tc0      = div*ma1
                   A0       = frac*tc0
                end function A0_f41124_zmm16r4
                
                 !/*
                 !!
                 !      Hollow cylindrical shell.
                 !      Approximations for the low frequency region
                 !      (k0a0<<1, k1a0<<1).
                 !      Formula 4.1-126
                 !  */
                 
               pure function B0_f41126_zmm16r4(a1,a0,k0a0,mu1,mu0) result(B0)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: B0_f41126_zmm16r4
                   !dir$ attributes forceinline :: B0_f41126_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: B0_f41126_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: mu1
                   type(ZMM16c4),    intent(in) :: mu0
                   type(ZMM16c4) :: B0
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: frac,div
                   type(ZMM16c4),   automatic :: tc0
                   type(ZMM16r4_t), automatic :: k0a02,a1a0
                   type(ZMM16r4_t), automatic :: a1a0s,ma1
                   k0a02.v  = k0a.v*k0a.v
                   a1a0.v   = a1.v/a0.v
                   a1a0s.v  = a1a0.v*a1a0.v
                   frac.re  = C078539816339744830961566084582.v*k0a02.v
                   ma1.v    = v16_1.v-a1a0s.v
                   frac.im  = v16_0.v
                   div      = mu1/mu0
                   div      = div-v16_1
                   tc0      = div*ma1
                   B0       = frac*tc0
                end function B0_f41126_zmm16r4
                
                
                 !/*
                 ! !
                 !         Hollow cylindrical shell.
                 !         Approximations for the low frequency region
                 !         (k0a0<<1, k1a0<<1).
                 !          Formula 4.1-125
                 !   */
                 
                pure function A1_f41125_zmm16r4(a1,a0,k0a0,mu,mu0) result(A1)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: A1_f41125_zmm16r4
                   !dir$ attributes forceinline :: A1_f41125_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: A1_f41125_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: mu1
                   type(ZMM16c4),    intent(in) :: mu0
                   type(ZMM16c4) :: A1
                   ! Locals
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: rat,div
                   type(ZMM16c4),   automatic :: divs,tc1
                   type(ZMM16c4),   automatic :: sqp,sqm
                   type(ZMM16c4),   automatic :: tc0,num
                   type(ZMM16c4),   automatic :: den,facr
                   type(ZMM16r4_t), automatic :: k0a2,a1a0
                   type(ZMM16c4_t), automatic :: a1a0s,ma1
                   a1a0.v   = a1.v/a0.v
                   k0a2.v   = k0a.v*k0a.v
                   frac.im  = v16_0.v
                   frac.re  = C078539816339744830961566084582.v*k0a2.v
                   div      = mu1/mu0
                   a1a0s.v  = a1a0.v*a1a0.v
                   ma1.v    = v16_1.v-a1a0s.v
                   divs     = div*div
                   divs     = divs-v16_1
                   tc0.re   = div.re+v16_1.v
                   tc0.im   = v16_0.v
                   num      = divs*ma1
                   sqp      = tc0*tc0
                   tc1.re   = div.re-v16_1.v
                   tc1.im   = v16_0.v
                   sqm      = tc1*tc1
                   sqm      = sqm*a1a02
                   den      = sqp*sqm
                   rat      = num/den
                   A1       = frac*rat
                end function A1_f41125_zmm16r4
                
                !  /*
                !!
                !          Hollow cylindrical shell.
                !          Approximations for the low frequency region
                !          (k0a0<<1, k1a0<<1).
                !           Formula 4.1-127
                !    */
                
                pure function B1_f41127_zmm16r4(a1,a0,k0a0,eps0,eps1) result(A1)
                      
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: B1_f41127_zmm16r4
                   !dir$ attributes forceinline :: B1_f41127_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: B1_f41127_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: a1
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16c4),    intent(in) :: eps0
                   type(ZMM16c4),    intent(in) :: eps1
                   type(ZMM16c4) :: B1
                   ! Locals
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: rat,div
                   type(ZMM16c4),   automatic :: divs,tc1
                   type(ZMM16c4),   automatic :: sqp,sqm
                   type(ZMM16c4),   automatic :: tc0,num
                   type(ZMM16c4),   automatic :: den,facr
                   type(ZMM16r4_t), automatic :: k0a2,a1a0
                   type(ZMM16c4_t), automatic :: a1a0s,ma1
                   a1a0.v   = a1.v/a0.v
                   k0a2.v   = k0a.v*k0a.v
                   frac.im  = v16_0.v
                   frac.re  = C078539816339744830961566084582.v*k0a2.v
                   div      = eps1/eps0
                   a1a0s.v  = a1a0.v*a1a0.v
                   ma1.v    = v16_1.v-a1a0s.v
                   divs     = div*div
                   divs     = divs-v16_1
                   tc0.re   = div.re+v16_1.v
                   tc0.im   = v16_0.v
                   num      = divs*ma1
                   sqp      = tc0*tc0
                   tc1.re   = div.re-v16_1.v
                   tc1.im   = v16_0.v
                   sqm      = tc1*tc1
                   sqm      = sqm*a1a02
                   den      = sqp*sqm
                   rat      = num/den
                   B1       = frac*rat
                end function B1_f41127_zmm16r4
                
                !  /*
                !!
                !          Low-frequncy approximations (k0a<0.2)
                !          Cylindrical Luneberg lens (k0a<0.2).
                !          Formula 4.1-162
                !     */
                
                pure function A0_f41162_zmm16r4(k0a) result(A0)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: A0_f41162_zmm16r4
                   !dir$ attributes forceinline :: A0_f41162_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: A0_f41162_zmm16r4
                   use mod_vecconsts, only : v16_0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4) :: A0
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C05 = ZMM16r4_t(0.5_sp)
                   ! Locals
                   type(ZMM16r4_t), automatic :: k0a2,k0ah
                   k0a2.v = k0a.v*k0a.v
                   k0ah.v = C05.v*k0a2.v
                   A0.re  = C078539816339744830961566084582.v*k0ah.v
                   A0.im  = v16_0.v
                end function A0_f41162_zmm16r4
                
                
                pure function B1_f41162_zmm16r4(k0a) result(B1)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: B1_f41162_zmm16r4
                   !dir$ attributes forceinline :: B1_f41162_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: B1_f41162_zmm16r4
                   use mod_vecconsts, only : v16_0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4) :: B1
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582 = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C18992 = ZMM16r4_t(1.8992_sp)
                   ! Locals
                   type(ZMM16r4_t), automatic :: k0a2,k0ah
                   k0a2.v = k0a.v*k0a.v
                   k0ah.v = C18992.v*k0a2.v
                   B1.re  = C078539816339744830961566084582.v*k0ah.v
                   B1.im  = v16_0.v
                end function B1_f41162_zmm16r4
                
                !  /*
                !          Low-frequncy approximations (k0a<0.2)
                !          Cylindrical Luneberg lens (k0a<0.2).  
                !          Scattering widths.
                !          Formula 4.1-163
                ! !     */
                
                pure function rcs_f41163_zmm16r4(a,k0a) result(rcs)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f41163_zmm16r4
                   !dir$ attributes forceinline :: rcs_f41163_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f41163_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 = &
                                                          ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C00625 = ZMM16r4_t(0.0625_SP)
                   ! Locals
                   type(ZMM16r4_t), automatic :: t0,k0a3
                   t0.v   = C9869604401089358618834490999876.v*a.v
                   k0a3.v = k0a.v*k0a.v*k0a.v
                   rcs.v  = k0a3.v*t0.v
                end function rcs_f41163_zmm16r4
                
                ! /*
                !          Low-frequncy approximations (k0a<0.2)
                !          Cylindrical Luneberg lens (k0a<0.2).  
                !          Scattering widths.
                !          Formula 4.1-164
                !      */
                
                pure function rcs_f41164_zmm16r4(a,k0a,phi) result(rcs)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f41164_zmm16r4
                   !dir$ attributes forceinline :: rcs_f41164_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f41164_zmm16r4 
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t) :: rcs
                   type(ZMM16r4_t), parameter :: C9869604401089358618834490999876 = &
                                                           ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t), parameter :: C003607 = ZMM16r4_t(0.03607_sp)
                   type(ZMM16r4_t), automatic :: t0,cosp,k0a3,cos2p
                   k0a3.v  = k0a.v*k0a.v*k0a.v
                   cosp.v  = cos(phi.v)
                   t0.v    = C003607.v*C9869604401089358618834490999876.v*a.v
                   cos2p.v = cosp.v*cosp.v
                   rcs.v   = t0.v*k0a3.v*cos2p.v
                end function rcs_f41164_zmm16r4
                
                !   /*
                !!
                !      Cylindrical Eaton-Lippman Lens, (k0a<0.2)
                !      Formulae 4.1-165
                !  */
                
                pure function A0_f41165_zmm16r4(k0a) result(A0)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: A0_f41165_zmm16r4
                   !dir$ attributes forceinline :: A0_f41165_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: A0_f41165_zmm16r4
                   use mod_vecconsts, only : v16_0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4)  :: A0
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582 = &
                                                        ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t),  automatic :: k0a2
                   k0a2.v  = k0a.v*ka0.v 
                   A0.re   = C078539816339744830961566084582.v*k0a2.v
                   A0.im   = v16_0
                end function A0_f41165_zmm16r4
                
                pure function B1_f41165_zmm16r4(k0a) result(B1)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: B1_f41165_zmm16r4
                   !dir$ attributes forceinline :: B1_f41165_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: B1_f41165_zmm16r4
                   use mod_vecconsts, only : v16_0
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16c4)  :: B1
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582 = &
                                                            ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t),  parameter :: C043616 = ZMM16r4_t(0.43616_sp)
                   type(ZMM16r4_t),  automatic :: k0a2,t0
                   k0a2.v  = k0a.v*ka0.v 
                   t0.v    = C043616.v*k0a2.v
                   B1.re   = C078539816339744830961566084582.v*t0.v
                   B1.im   = v16_0
                end function B1_f41165_zmm16r4
                
                ! /*
                !!
                !       Cylindrical Eaton-Lippman Lens, (k0a<0.2) 
                !       Scattering widths.
                !       Formula: 1.4-166
                !   */
                
                pure function rcs_f14166_zmm16r4(a,k0a) result(rcs)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f14166_zmm16r4
                   !dir$ attributes forceinline :: rcs_f14166_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f14166_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C9869604401089358618834490999876 = &
                                                         ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t),  parameter :: C025 = ZMM16r4_t(0.25_sp)
                   type(ZMM16r4_t),  automatic :: a4,k0a3
                   a4.v   = a.v*C025.v
                   k0a3.v = k0a.v*k0a.v*k0a.v
                   rcs.v  = k0a3.v*C9869604401089358618834490999876.v*a4.v
                end function rcs_f14166_zmm16r4
                
                 ! /*
                 !!
                 !      Cylindrical Eaton-Lippman Lens, (k0a<0.2) 
                 !      Scattering widths.
                 !      Formula: 1.4-167
                 !  */
                 
                 pure function rcs_f14167_zmm16r4(a,k0a,phi) result(rcs)
                     
                    !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f14167_zmm16r4
                   !dir$ attributes forceinline :: rcs_f14167_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f14167_zmm16r4
                   type(ZMM16r4_t),  intent(in) :: a
                   type(ZMM16r4_t),  intent(in) :: k0a
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16r4_t) :: rcs
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C9869604401089358618834490999876 = &
                                                             ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t),  parameter :: C019024 =  ZMM16r4_t(0.19024_sp)
                   type(ZMM16r4_t),  automatic :: cosp,cos2p,k0a3,t0,t1
                   k0a3.v = k0a.v*k0a3.v*k0a.v
                   cosp.v = cos(phi.v)
                   t0.v   = C019024.v*C9869604401089358618834490999876.v
                   t1.v   = a.v*k0a3.v
                   cos2p.v= cosp.v*cosp.v
                   rcs.v  = t0.v*t1.v*cos2p.v
                 end function rcs_f14167_zmm16r4
                 
                !  /*
                !!
                !        Infinitely long cylinder.
                !        Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
                !        TM-incident E-field.
                !        Formula 4.2-48
                !    */
                
                pure function Ez_f4248_zmm16r4(E0,psi,phi,k0,z,r,      &
                                               a0,eps,mu)         result(Ez)
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Ez_f4248_zmm16r4
                   !dir$ attributes forceinline :: Ez_f4248_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Ez_f4248_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: E0
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: k0
                   type(ZMM16r4_t), intent(in) :: z
                   type(ZMM16r4_t), intent(in) :: a0
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Ez
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C0886226925452758013649083741671 =   &
                                                         ZMM16r4_t(0.886226925452758013649083741671_sp)
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582  =   &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t),  parameter :: C05 =  ZMM16r4_t(0.5_sp)
                   type(ZMM16r4_t),  parameter :: C20 =  ZMM16r4_t(2.0_sp)
                   type(ZMM16c4),    automatic :: epsp1,epsm1
                   type(ZMM16c4),    automatic :: mup1,mum1
                   type(ZMM16c4),    automatic :: mul1,mul2
                   type(ZMM16c4),    automatic :: mul3,tc0
                   type(ZMM16c4),    automatic :: tc1,tc2
                   type(ZMM16c4),    automatic :: ea,ce
                   type(ZMM16c4),    automatic :: frac,fre
                   type(ZMM16c4),    automatic :: div1,div2
                   type(ZMM16c4),    automatic :: num
                   type(ZMM16r4_t),  automatic :: k0r,k0z,k0a0,cosp
                   type(ZMM16r4_t),  automatic :: cosps,cos2ps,sinps,sin2ps
                   type(ZMM16r4_t),  automatic :: k0a02,scosps
                   k0r.v   = k0.v*r.v
                   k0z.v   = k0.v*z.v
                   k0a0.v  = k0.v*a0.v
                   cosp.v  = cos(phi.v)
                   k0a02.v = C05.v*k0a0.v*k0a0.v
                   epsp1   = epsr+v16_1
                   ea.re   = v16_0.v
                   cosps.v = cos(psi.v)
                   epsm1   = epsr-v16_1
                   scosps.v= sqrt(cosps.v)
                   sinps.v = sin(psi.v)
                   mup1    = mu+v16_1
                   cos2ps.v= cosps.v*cosps.v
                   mum1    = mu-v16_1
                   mul1    = epsr*mum1
                   sin2ps.v= sinps.v*sinps.v
                   t0.v    = k0z.v*sinps.v+k0r.v*cosps.v+ &
                                 0.78539816339744830961566084582.v
                   ea.re   = t0.v
                   t1.v    = sqrt(k0r.v)
                   ce      = cexp_c16(ea)
                   frac    = E0*scosps
                   fre     = frac*ce
                   div1    = C0886226925452758013649083741671.v*(fre/t1)
                   mul2    = epsm1*mup1
                   mul3    = epsr1*mup1
                   tc0     = epsm1*cos2ps
                   num     = mul2*sin2ps+mul1
                   div2    = num/mul3
                   tc1     = C20*(div2/cosp)
                   tc2     = k0a02*(tc0-tc1)
                   Ez      = div1*tc2
                end function Ez_f4248_zmm16r4 
                
                 ! /*
                 !!
                 !        Infinitely long cylinder.
                 !        Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
                 !        TM-incident E-field.
                 !        Formula 4.2-49
                 !   */
                 
                pure function Eph_f4249_zmm16r4(E0,k0z,k0r,k0a0,psi,phi,eps,mu) result(Eph)
                     
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Eph_f4249_zmm16r4
                   !dir$ attributes forceinline :: Eph_f4249_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Eph_f4249_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: E0
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Eph
                   ! Locals
                   type(ZMM16r4_t), parameter :: C2506628274631000502415765284811 = &
                                                         ZMM16r4_t(2.506628274631000502415765284811_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),   automatic :: ea,ce
                   type(ZMM16c4),   automatic :: frac,tc0
                   type(ZMM16c4),   automatic :: mul,emum1
                   type(ZMM16c4),   automatic :: epsp1,mup1
                   type(ZMM16c4),   automatic :: tc1
                   type(ZMM16r4_t), automatic :: den,t0
                   type(ZMM16r4_t), automatic :: cosp,sinps
                   type(ZMM16r4_t), automatic :: sinph,k0a02
                   type(ZMM16r4_t), automatic :: cosps,sinpsp
                   k0a02.v   = k0a0.v*k0a0.v
                   cosp.v    = cos(phi.v)
                   ea.im     = v16_v0.v
                   t0.v      = k0r.v*cosp.v
                   emum1     = eps*mu
                   den.v     = sqrt(t0.v)
                   emum1     = emum1-v16_1
                   epsp1     = eps-v16_1
                   sinps.v   = sin(psi.v)
                   mup1      = mu+v16_1
                   sinph.v   = sin(phi.v)
                   cosps.v   = cos(psi.v)
                   t0.v      = k0z.v*sinps.v+k0r.v*cosp.v+ &
                               C078539816339744830961566084582.v
                   ea.re     = t0.v
                   ce        = cexp_c16(ea)
                   frac      = E0*ce
                   frac      = frac/den
                   tc0       = C2506628274631000502415765284811*frac*k0a02
                   mul       = epsp1*mup1
                   tc1       = emum1/mul
                   tc1       = sinpsp*tc1
                   Eph       = frac*tc1
                end function Eph_f4249_zmm16r4
                
               !   /*
               !          Infinitely long cylinder.
               !          Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !          TM-incident H-field.
               !          Formula 4.2-50
               !!
               !   */
               
               pure function Hz_f4250_zmm16r4(E0,k0z,k0r,k0a0,psi,phi,eps,mu) result(Hz)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Hz_f4250_zmm16r4
                   !dir$ attributes forceinline :: Hz_f4250_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Hz_f4250_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: E0
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Hz
                   ! Locals
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C000001763712109284471382861586  = &
                                                         ZMM16r4_t(0.00001763712109284471382861586_sp)
                   type(ZMM16c4),   automatic :: ea,ce
                   type(ZMM16c4),   automatic :: frac,tc0
                   type(ZMM16c4),   automatic :: mul,emum1
                   type(ZMM16c4),   automatic :: epsp1,mup1
                   type(ZMM16c4),   automatic :: tc1
                   type(ZMM16r4_t), automatic :: den,t0,scosp,cosp
                   type(ZMM16r4_t), automatic :: sinps,sinph,k0a02,cosps
                   type(ZMM16r4_t), automatic :: sinpsp
                   k0a02.v  = k0a0.v*k0a0.v
                   cosp.v   = cos(phi.v)
                   ea.im    = v16_0.v
                   emum1    = eps*mu
                   den.v    = sqrt(k0r.v)
                   emum1    = emum1-v16_1
                   epsp1    = eps+v16_1
                   sinps.v  = sin(psi.v)
                   mup1     = mu+v16_1
                   sinph.v  = sin(phi.v)
                   t0.v     = k0a.v*sinps.v+k0r.v*cosp.v+  &
                              C078539816339744830961566084582.v
                   cosps.v  = cos(psi.v)
                   scosp.v  = sqrt(cosp.v)
                   sinpsp.v = sinps.v*sinph.v
                   ea.re    = t0.v
                   ce       = cexp_c16(ea)
                   ce       = scosp*ce
                   frac     = E0*ce
                   frac     = frac/den
                   tc0      = C000001763712109284471382861586*frac*k0a02
                   mul      = epsp1*mup1
                   tc1      = emum1/mul
                   tc1      = sinpsp*tc1
                   Hz       = frac*tc1
               end function Hz_f4250_zmm16r4
               
               ! /*
               !          Infinitely long cylinder.
               !          Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !          TE-incident H-field.
               !          Formula 4.2-52
               !!
               !    */
               
               pure function Hz_f4252_zmm16r4(H0,psi,phi,k0r,k0z,k0a0,eps,mu) result(Hz)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Hz_f4252_zmm16r4
                   !dir$ attributes forceinline :: Hz_f4252_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Hz_f4252_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: H0
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Hz
                   ! Locals
                   type(ZMM16r4_t), parameter :: C1253314137315500251207882642406 = &
                                                       ZMM16r4_t(1.253314137315500251207882642406_sp)
                   type(ZMM16r4_t), parameter :: C078539816339744830961566084582  = &
                                                       ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t), parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t), parameter :: C05 = ZMM16r4_t(0.5_sp)
                   type(ZMM16c4),   automatic :: mul,mul2
                   type(ZMM16c4),   automatic :: mul3,tc0
                   type(ZMM16c4),   automatic :: tc1,mum1
                   type(ZMM16c4),   automatic :: epsm1,num
                   type(ZMM16c4),   automatic :: mup1,epsp1
                   type(ZMM16c4),   automatic :: mucs,frac
                   type(ZMM16c4),   automatic :: ea,ce
                   type(ZMM16r4_t), automatic :: scosps,sinps
                   type(ZMM16r4_t), automatic :: cosps,k0a02
                   type(ZMM16r4_t), automatic :: sk0r,cos2ps
                   type(ZMM16r4_t), automatic :: sin2ps,cosp
                   type(ZMM16r4_t), automatic :: t0
                   cosps.v   = cos(psi.v)
                   k0a02.v   = C05.v*k0a.v*k0a.v
                   scosps.v  = sqrt(cosps.v)
                   cos2ps.v  = cosps.v*cosps.v
                   sinps.v   = sin(psi.v)
                   t0.v      = k0z.v*sinps.v+k0r.v*cosps.v+ &
                               C078539816339744830961566084582.v
                   ea.im     = v116_0.v
                   ea.re     = t0.v
                   cosp.v    = cos(phi.v)
                   ce        = cexp_c16(ea)
                   mum1      = mu-v16_1
                   frac      = H0*scosps
                   epsm1     = eps-v16_1
                   mup1      = mu+v16_1
                   epsp1     = eps+v16_1
                   tc0       = frac*ce
                   mucs      = mum1*cos2ps
                   tc0       = C1253314137315500251207882642406*(tc0/sk0r)
                   mul1      = epsm1*mup1
                   tc0       = tc0*k0a02
                   mul2      = epsp1*mum1
                   num       = mul2*sin2ps+mul1
                   mul3      = epsp1*mup1
                   tc1       = num/mul3
                   tc1       = C20*tc1*cosp
                   mucs      = mucs-tc1
                   Hz        = tc0*mucs
               end function Hz_f4252_zmm16r4
               
               !  /*
               !          Infinitely long cylinder.
               !          Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !          TE-incident E-field.
               !          Formula 4.2-55
               !!
               !    */
               
               pure function Eph_f4255_zmm16r4(H0,psi,phi,k0r,k0z,k0a0,eps,mu) result(Ep)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Eph_f4255_zmm16r4
                   !dir$ attributes forceinline :: Eph_f4255_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Eph_f4255_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: H0
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Ep
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C000001763712109284471382861586 = &
                                                         ZMM16r4_t(0.00001763712109284471382861586_sp)
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582 = &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t),  parameter :: C20 =  ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t),  parameter :: C05 =  ZMM16r4_t(0.5_sp)
                   type(ZMM16c4),    automatic :: mul1,mul2
                   type(ZMM16c4),    automatic :: mul3,tc0
                   type(ZMM16c4),    automatic :: tc1,mum1
                   type(ZMM16c4),    automatic :: epsm1,num
                   type(ZMM16c4),    automatic :: mup1,epsp1
                   type(ZMM16c4),    automatic :: mucs,frac
                   type(ZMM16c4),    automatic :: ea,ce
                   type(ZMM16r4_t),  automatic :: sinps,cosps
                   type(ZMM16r4_t),  automatic :: k0a02,sk0r
                   type(ZMM16r4_t),  automatic :: cos2ps,sin2ps
                   type(ZMM16r4_t),  automatic :: cosp,t0
                   k0a2.v   = C05.v*k0a.v*k0a.v
                   cosps.v  = cos(psi.v)
                   frac     = H0
                   ea.im    = v16_0.v
                   sinps.v  = sin(psi.v)
                   cos2ps.v = cosps.v*cosps.v
                   t0.v     = k0z.v*sinps.v+k0r.v*cosps.v+ &
                              C078539816339744830961566084582.v
                   sk0r.v   = sqrt(k0r.v*cosps.v)
                   ea.re    = t0.v
                   ce       = cexp_c16(ea)
                   cosp.v   = cos(phi.v)
                   mum1     = mu-v16_1
                   epsm1    = eps-v16_1
                   epsp1    = eps+v16_1
                   mup1     = mu+v16_1
                   tc0      = frac*ce
                   mucs     = mum1*cos2ps
                   tc0      = C000001763712109284471382861586*(tc0/sk0r)
                   mul1     = epsm1*mup1
                   tc0      = tc0*k0a02
                   mul2     = epsp1*mum1
                   num      = mul2*sinps+mul1
                   mul3     = epsp1*mup1
                   tc1      = num/mul3
                   tc1      = C20*tc1*cosp
                   mucs     = mucs-tc1
                   Ep       = tc0*mucs                          
               end function Eph_f4255_zmm16r4
               
               ! /*
               !          Infinitely long cylinder.
               !          Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !          TE-incident H-field.
               !          Formula 4.2-53
               ! !
               !   */
               
               pure function Hph_f4253_zmm16r4(H0,k0z,k0r,psi,phi,k0a0,eps,mu) result(Hp)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Hph_f4253_zmm16r4
                   !dir$ attributes forceinline :: Hph_f4253_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Hph_f4253_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: H0
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Hp
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582 = &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16r4_t),  parameter :: C2506628274631000502415765284811 = &
                                                         ZMM16r4_t(2.506628274631000502415765284811_sp)
                   type(ZMM16c4),    automatic :: mul1,mul2
                   type(ZMM16c4),    automatic :: div,epsp1
                   type(ZMM16c4),    automatic :: mup1,frac
                   type(ZMM16c4),    automatic :: ea,ce
                   type(ZMM16c4),    automatic :: tc0
                   type(ZMM16r4_t),  automatic :: sinps,cosps
                   type(ZMM16r4_t),  automatic :: scpk0r,sinph
                   type(ZMM16r4_t),  automatic :: k0a02,spsph
                   k0a02.v   = k0a.v*k0a.v
                   sinps.v   = sin(psi.v)
                   ea.im     = v16_0.v
                   cosps.v   = cos(psi.v)
                   ea.re     = k0z.v*sinps.v+k0r.v*cosps.v+ &
                               C078539816339744830961566084582.v
                   sinph.v   = sin(phi.v)
                   ce        = cexp_c16(ea)
                   scpk0r.v  = sqrt(k0r.v*cosps.v)
                   frac      = H0*cer
                   spsph.v   = sinps.v*sinph.v
                   epsp1     = eps+v16_1
                   mup1      = mu+v16_1
                   mul1      = eps*mu
                   mul1      = mul1-v16_1
                   tc0       = C2506628274631000502415765284811*(frac/scpk0r)
                   mul2      = epsp1*mup1
                   div       = mul1/mul2
                   tc0       = tc0*k0a02
                   div       = div*spsph
                   Hp        = tc0*div
               end function Hph_f4253_zmm16r4
               
               !   /*
               !          Infinitely long cylinder.
               !          Scattered fields (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !          TE-incident E-field.
               !          Formula 4.2-54
               !!
               !    */
               
               pure function Ez_f4254_zmm16r4(H0,k0z,k0r,psi,phi,k0a0,eps,mu) result(Hp)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: Ez_f4254_zmm16r4
                   !dir$ attributes forceinline :: Ez_f4254_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: Ez_f4254_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16c4),   intent(in) :: H0
                   type(ZMM16r4_t), intent(in) :: k0z
                   type(ZMM16r4_t), intent(in) :: k0r
                   type(ZMM16r4_t), intent(in) :: psi
                   type(ZMM16r4_t), intent(in) :: phi
                   type(ZMM16r4_t), intent(in) :: k0a0
                   type(ZMM16c4),   intent(in) :: eps
                   type(ZMM16c4),   intent(in) :: mu
                   type(ZMM16c4) :: Ez
                   ! Locals
                   type(ZMM16r4_t),  parameter :: C000001763712109284471382861586 = &
                                                         ZMM16r4_t(0.00001763712109284471382861586_sp)
                   type(ZMM16r4_t),  parameter :: C078539816339744830961566084582 = &
                                                         ZMM16r4_t(0.78539816339744830961566084582_sp)
                   type(ZMM16c4),    automatic :: mul1,mul2
                   type(ZMM16c4),    automatic :: div,epsp1
                   type(ZMM16c4),    automatic :: mup1,frac
                   type(ZMM16c4),    automatic :: ea,ce
                   type(ZMM16c4),    automatic :: tc0
                   type(ZMM16r4_t),  automatic :: sinps,cosps
                   type(ZMM16r4_t),  automatic :: scpk0r,sinph
                   type(ZMM16r4_t),  automatic :: k0a02,spsph
                   k0a02.v  = k0a.v*k0a.v
                   sinps.v  = sin(psi.v)
                   ea.im    = v16_0.v
                   cosps.v  = cos(psi.v)
                   ea.re    = k0z.v*sinps.v+k0r.v*cosps.v+ &
                              C078539816339744830961566084582.v
                   ce       = cexp_c16(ea)
                   scpk0r.v = sqrt(k0r.v)
                   frac     = H0*ce
                   sinph.v  = sin(phi.v)
                   frac     = frac*cosps
                   spsph.v  = sinps.v*sinph.v
                   mup1     = mu+v16_1
                   epsp1    = eps+v16_1
                   mul1     = eps*mu
                   tc0      = C000001763712109284471382861586*(frac/scpk0r)
                   mul1     = mul1-v16_1
                   mul2     = epsp1*mup1
                   div      = mul1/mul2
                   tc0      = tc0*k0a02
                   div      = div*spsph
                   Ez       = tc0*div
               end function Ez_f4254_zmm16r4
               
               ! /*
               !      Bistatic scattering width for (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !      Infinitely long cylinder.
               !      TM-incident.
               !      Formula 4.2-56
               !  */
               
               pure function rcs_f4256_zmm16r4(a0,k0a0,psi,phi,eps,mu) result(rcs)
                    
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4256_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4256_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4256_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16r4_t),  intent(in) :: psi
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16c4),    intent(in) :: eps
                   type(ZMM16c4),    intent(in) :: mu
                   type(ZMM16r4_t) :: rcs
                   ! LOcals
                   type(ZMM16r4_t),  parameter :: C9869604401089358618834490999876 = &
                                                        ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t),  parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t),  parameter :: C40 = ZMM16r4_t(4.0_sp)
                   type(ZMM16c4),    automatic :: tc0,tc1
                   type(ZMM16c4),    automatic :: epsm1,epsp1
                   type(ZMM16c4),    automatic :: mum1,mup1
                   type(ZMM16c4),    automatic :: num,epscps
                   type(ZMM16c4),    automatic :: div,mul1
                   type(ZMM16c4),    automatic :: mul2,mul3
                   type(ZMM16r4_t),  automatic :: k0a03,frac,cosp,cos2p
                   type(ZMM16r4_t),  automatic :: cosps,sinps,sin2ps,spia
                   type(ZMM16r4_t),  automatic :: t0,cab
                   spia.v   = a0.v*C9869604401089358618834490999876.v
                   cosps.v  = cos(psi.v)
                   k0a03.v  = k0a0.v*k0a0.v*k0a0.v
                   epsm1    = eps-v16_1
                   sinps.v  = sin(psi.v)
                   cos2ps.v = cosps.v*cosps.v
                   mum1     = mu-v16_1
                   epsp1    = eps+v16_1
                   cosp.v   = cos(phi.v)
                   sin2ps.v = sinps.v*sinps.v
                   mup1     = mu+v16_1
                   t0.v     = C40.v*cos2ps.v
                   frac.v   = C9869604401089358618834490999876.v/t0.v
                   epscps   = epsm1*cos2ps
                   frac.v   = frac.v*k0a03.v
                   mul1     = epsp1*mum1
                   mul2     = epsm1*mup1
                   num      = mul2*sinps*mul1
                   mul3     = epsp1*mup1
                   div      = num/mul3
                   tc0      = C20*div*cosp
                   tc1      = epscps-tc0
                   cab.v    = cabs_c16(tc1)
                   rcs.v    = cab.v*frac.v
               end function rcs_f4256_zmm16r4
               
               !  /*
               !      Bistatic scattering width for (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !      Infinitely long cylinder.
               !      TE-incident.
               !      Formula 4.2-58
               !  */
               
               pure function rcs_f4258_zmm16r4(a0,k0a0,psi,phi,eps,mu) result(rcs)
                   
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4258_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4258_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4258_zmm16r4
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16r4_t),  intent(in) :: psi
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16c4),    intent(in) :: eps
                   type(ZMM16c4),    intent(in) :: mu
                   type(ZMM16r4_t) :: rcs
                   ! LOcals
                   type(ZMM16r4_t),  parameter :: C9869604401089358618834490999876 = &
                                                        ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t),  parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t),  parameter :: C40 = ZMM16r4_t(4.0_sp)
                   type(ZMM16c4),    automatic :: tc0,tc1
                   type(ZMM16c4),    automatic :: epsm1,epsp1
                   type(ZMM16c4),    automatic :: mum1,mup1
                   type(ZMM16c4),    automatic :: num,mucps
                   type(ZMM16c4),    automatic :: div,mul1
                   type(ZMM16c4),    automatic :: mul2,mul3
                   type(ZMM16r4_t),  automatic :: k0a03,frac,cosp,cos2p
                   type(ZMM16r4_t),  automatic :: cosps,sinps,sin2ps,spia
                   type(ZMM16r4_t),  automatic :: t0,cab
                   spia.v   = a0.v*C9869604401089358618834490999876.v
                   cosps.v  = cos(psi.v)
                   k0a03.v  = k0a0.v*k0a0.v*k0a0.v
                   epsm1    = eps-v16_1
                   sinps.v  = sin(psi.v)
                   cos2ps.v = cosps.v*cosps.v
                   mum1     = mu-v16_1
                   epsp1    = eps+v16_1
                   cosp.v   = cos(phi.v)
                   sin2ps.v = sinps.v*sinps.v
                   mup1     = mu+v16_1
                   t0.v     = C40.v*cos2ps.v
                   frac.v   = C9869604401089358618834490999876.v/t0.v
                   mucps    = mum1*cos2ps
                   frac.v   = frac.v*k0a03.v
                   mul1     = epsp1*mum1
                   mul2     = epsm1*mup1
                   num      = mul2*sinps*mul1
                   mul3     = epsp1*mup1
                   div      = num/mul3
                   tc0      = C20*div*cosp
                   tc1      = mucps-tc0
                   cab.v    = cabs_c16(tc1)
                   rcs.v    = cab.v*frac.v
               end function rcs_f4258_zmm16r4
               
               ! /*
               ! !
               !            Bistatic scattering width for (k0a0 sqrt(epsr*mur-sin^2(Psi) < 0.5)
               !            Infinitely long cylinder.
               !            TM-incident.
               !            Formula 4.2-57
               !      */
               
               pure function rcs_f4257_zmm16r4(a0,k0a0,psi,phi,eps,mu) result(rcs)
               
                   !dir$ optimize:3
                   !dir$ attributes code_align : 32 :: rcs_f4257_zmm16r4
                   !dir$ attributes forceinline :: rcs_f4257_zmm16r4
                   !dir$ attributes optimization_parameter:"target_arch=skylake-avx512" :: rcs_f4257_zmm16r4 
                   use mod_vecconsts, only : v16_1,v16_0
                   type(ZMM16r4_t),  intent(in) :: a0
                   type(ZMM16r4_t),  intent(in) :: k0a0
                   type(ZMM16r4_t),  intent(in) :: psi
                   type(ZMM16r4_t),  intent(in) :: phi
                   type(ZMM16c4),    intent(in) :: eps
                   type(ZMM16c4),    intent(in) :: mu
                   type(ZMM16r4_t) :: rcs
                   ! LOcals
                   type(ZMM16r4_t),  parameter :: C9869604401089358618834490999876 = &
                                                        ZMM16r4_t(9.869604401089358618834490999876_sp)
                   type(ZMM16r4_t),  parameter :: C20 = ZMM16r4_t(2.0_sp)
                   type(ZMM16r4_t),  parameter :: C40 = ZMM16r4_t(4.0_sp)
                   type(ZMM16c4),    automatic :: div,mul1
                   type(ZMM16c4),    automatic :: mul2,epsp1
                   type(ZMM16c4),    automatic :: mup1
                   type(ZMM16r4_t),  automatic :: spi4,cos2ps,sinps,sinp
                   type(ZMM16r4_t),  automatic :: k0a03,frac,t0,cab
                   k0a03.v   = k0a0.v*k0a0.v*k0a0.v
                   epsp1     = eps+v16_1
                   cosps.v   = cos(psi.v)
                   spi4.v    = C9869604401089358618834490999876.v* &
                               a0.v*a0.v
                   mup1      = mu1+v16_1
                   cos2ps.v  = cosps.v*cosps.v
                   spi4.v    = C40.v*spi4.v
                   mul1      = eps*mu
                   sinps.v   = sin(psi.v)
                   mul1      = mul1-v16_1
                   sinp.v    = sin(phi.v)
                   mul2      = epsp1*mup1
                   frac.v    = k0a03.v*(spi4.v/cos2ps.v)
                   t0.v      = sinps.v*sinp.v
                   div       = mul1/mul2
                   div       = div*t0
                   cab       = cabs_c16(div)
                   rcs.v     = frac.v*cab.v
               end function rcs_f4257_zmm16r4
                                               



                
               
                 
                

                 

                
                
                

 




end module rcs_cylinder_zmm16r4
