
#include "GMS_config.fpp"

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


module radio_refractivity_3D_xmm4r4




!===================================================================================85
 !---------------------------- DESCRIPTION ------------------------------------------85
 !
 !
 !
 !          Module  name: 
 !                         radio_refractivity_3D_xmm4r4
 !          
 !          Purpose:
 !                      ITU-R P.453-11 - radio refractivity index calculation (vectorized version) of dimension 3D.
 !                        
 !          History:
 !                        Date: 26-12-2024
 !                        Time: 07:47PM GMT+2
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
 !          References:
 !         
 !                          RECOMMENDATION ITU-R P.453-11
 !                          The radio refractive index: its formula and refractivity data
 !                          (Question ITU-R 201/3)
 !         
 !          E-mail:
 !                  
 !                      beniekg@gmail.com
!==================================================================================85
    ! Tab:5 col - Type and etc.. definitions
    ! Tab:10,11 col - Type , function and subroutine code blocks.

    use mod_kinds,              only : i4,sp
    use mod_vectypes,           only : XMM4r4_t
    use radio_refractivity_ref, only :  refractivity_index_n_r4

    public
    implicit none
    
    
      ! Major version
     integer(kind=i4),  parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_MAJOR = 1
     ! Minor version
     integer(kind=i4),  parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_MINOR = 0
     ! Micro version
     integer(kind=i4),  parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_MICRO = 0
     ! Full version
     integer(kind=i4),  parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_FULLVER =   &
            1000*RADIO_REFRACTIVITY_3D_XMM4R4_MAJOR+100*RADIO_REFRACTIVITY_3D_XMM4R4_MINOR+10*RADIO_REFRACTIVITY_3D_XMM4R4_MICRO
     ! Module creation date
     character(*),        parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_CREATE_DATE = "26-12-2024 07:47AM +00200 (THR 26 DEC 2024 GMT+2)"
     ! Module build date
     character(*),        parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_BUILD_DATE  = __DATE__ " " __TIME__
     ! Module author info
     character(*),        parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_AUTHOR      = "Programmer: Bernard Gingold, contact: beniekg@gmail.com"
     ! Short description
     character(*),        parameter :: RADIO_REFRACTIVITY_3D_XMM4R4_SYNOPSIS  = "ITU-R P.453-11 - radio refractivity index calculation (vectorized version) 3D." 
     
     integer(kind=i4), parameter, private :: XMM_LEN = 4

     contains


subroutine radio_refractivity_index_3D_v128_32x4_ps(tc,Tk,Pd,P,H,nref,its,ite,   &
                                                    kts,kte,jts,jte,water_or_ice)
#if defined(__ICC) || defined(__INTEL_COMPILER)    
        !DIR$ ATTRIBUTES CODE_ALIGN : 32 :: radio_refractivity_index_3D_v128_32x4_ps
        !DIR$ OPTIMIZE : 3
        !DIR$ ATTRIBUTES OPTIMIZATION_PARAMETER: TARGET_ARCH=skylake_avx512 :: radio_refractivity_index_3D_v128_32x4_ps
#endif  
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: tc 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Tk 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Pd 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: P 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: H 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(out):: nref 
      integer(kind=i4),                                  intent(in) :: its 
      integer(kind=i4),                                  intent(in) :: ite 
      integer(kind=i4),                                  intent(in) :: kts 
      integer(kind=i4),                                  intent(in) :: kte 
      integer(kind=i4),                                  intent(in) :: jts 
      integer(kind=i4),                                  intent(in) :: jte   
      integer(kind=i4),                                  intent(in) :: water_or_ice ! 0 for water, 1 for ice
        ! Locals
      character(*),   parameter :: sub_name   = 'radio_refractivity_index_3D_v128_32x4_ps'
      type(XMM4r4_t), parameter :: va_wat     = XMM4r4_t(6.1121_sp)
      type(XMM4r4_t), parameter :: vb_wat     = XMM4r4_t(18.678_sp)
      type(XMM4r4_t), parameter :: vc_wat     = XMM4r4_t(257.14_sp)
      type(XMM4r4_t), parameter :: vd_wat     = XMM4r4_t(234.5_sp)
        ! Ice constants
      type(XMM4r4_t), parameter :: va_ice     = XMM4r4_t(6.1125_sp)
      type(XMM4r4_t), parameter :: vb_ice     = XMM4r4_t(23.036_sp)
      type(XMM4r4_t), parameter :: vc_ice     = XMM4r4_t(279.82_sp)
      type(XMM4r4_t), parameter :: vd_ice     = XMM4r4_t(333.7_sp)
      type(XMM4r4_t), parameter :: vC1        = XMM4r4_t(1.0_sp)
      type(XMM4r4_t), parameter :: vC0001     = XMM4r4_t(0.0001_sp)
      type(XMM4r4_t), parameter :: vC72       = XMM4r4_t(7.2_sp)
      type(XMM4r4_t), parameter :: vC22       = XMM4r4_t(2.2_sp)
      type(XMM4r4_t), parameter :: vC00320    = XMM4r4_t(0.00320_sp)
      type(XMM4r4_t), parameter :: vC00382    = XMM4r4_t(0.00382_sp)
      type(XMM4r4_t), parameter :: vC00000059 = XMM4r4_t(0.0000059_sp)
      type(XMM4r4_t), parameter :: vC00000064 = XMM4r4_t(0.0000064_sp)
      type(XMM4r4_t), parameter :: vC001      = XMM4r4_t(0.01_sp)
      type(XMM4r4_t), parameter :: vC766      = XMM4r4_t(76.6_sp)
      type(XMM4r4_t), parameter :: vC720      = XMM4r4_t(72.0_sp)
      type(XMM4r4_t), parameter :: vC3750000  = XMM4r4_t(3750000.0_sp)
      type(XMM4r4_t), parameter :: vC0000001  = XMM4r4_t(0.000001_sp)
      real(kind=sp), parameter    :: a_wat = 6.1121_sp
      real(kind=sp), parameter    :: b_wat = 18.678_sp
      real(kind=sp), parameter    :: c_wat = 257.14_sp
      real(kind=sp), parameter    :: d_wat = 234.5_sp
        ! Ice constants
      real(kind=sp), parameter    :: a_ice = 6.1125_sp
      real(kind=sp), parameter    :: b_ice = 23.036_sp
      real(kind=sp), parameter    :: c_ice = 279.82_sp
      real(kind=sp), parameter    :: d_ice = 333.7_sp
      real(kind=sp), parameter    :: C1    = 1.0_sp
      real(kind=sp), parameter    :: C0001 = 0.0001_sp
      type(XMM4r4_t), automatic   :: vef_wat, vef_ice, vnum, vden 
      type(XMM4r4_t), automatic   :: vtt, vtd, ves, vPdT, vTk
      type(XMM4r4_t), automatic   :: veT, veTT, ve, vn_tmp
      type(XMM4r4_t), automatic   :: vtc, vP, vH, vtmp1, vtmp2 
      real(kind=dp), automatic    :: ef_wat, ef_ice, num, den
      real(kind=dp), automatic    :: tt, td, es
      real(kind=sp), automatic    :: PdT, eT, eTT, e, n_tmp
      real(kind=sp), automatic    :: a1,a2,a3,a4,a5,a6
      integer(i4),     automatic  :: j,k,i,ii,iii  
      integer(i4),     automatic  :: idx1,idx2,idx3,idx4
      integer(i4),     automatic  :: idx5,idx6,idx7,idx8
      integer(i4),     automatic  :: idx9,idx10,idx11,idx12 
      integer(i4),     automatic  :: idx13,idx14,idx15,idx16
        integer(i4),     automatic  :: idx17,idx18,idx19,idx20
        integer(i4),     automatic  :: idx21,idx22,idx23,idx24
        integer(i4),     automatic  :: idx25,idx26,idx27,idx28
        integer(i4),     automatic  :: idx29,idx30,idx31
        integer(i4),     automatic  :: j_dif,k_dif,i_dif
        logical(i4),     automatic  :: j_dif_eq_1,k_dif_eq_1
        logical(i4),     automatic  :: i_dif_le_4,i_dif_le_128

      j_dif        = jte-jts
      k_dif        = kte-kts 
      i_dif        = ite-its 
      j_dif_eq_1   = j_dif .eq. 1
      k_dif_eq_1   = k_dif .eq. 1
      i_dif_le_4   = (i_dif .gt. 1) && (i_dif .le. 4)
      i_dif_le_128 = (i_dif .gt. 4) && (i_dif .le. 128)
      if(water_or_ice == 0) then 
           
         if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
                   do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                  vT.v(ii)      = tc(i+ii,k,j)
                                  vP.v(ii)      = P(i+ii,k,j)
                                  vH.v(ii)      = H(i+ii,k,j)
                                  vTk.v(ii)     = Tk(i+ii,k,j) 
                                  vPdT.v(ii)    = Pd(i+ii,k,j)
                                  vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                  vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                                  vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                                  vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                                  vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                                  vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                                  vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                  ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                  ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                  vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                  veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                  veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                  vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                                  nref(i+ii,k,j)= vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                              do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                     nref(iii,k,j) = a6  
                                end do
                           end do 
                        end do
                     end do 
                     return 
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                    
                  do j=jts, jte 
                     do k=kts, kte 
                        do i=its, iand(ite-1,inot(3)),XMM_LEN*32 
                                call mm_prefetch(tc(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                           do ii=0, 3 
                   
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx8          = i+8*XMM_LEN+ii
                             vT.v(ii)      = tc(idx8,k,j)
                             vP.v(ii)      = P(idx8,k,j)
                             vH.v(ii)      = H(idx8,k,j)
                             vTk.v(ii)     = Tk(idx8,k,j) 
                             vPdT.v(ii)    = Pd(idx8,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx8,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx9          = i+9*XMM_LEN+ii
                             vT.v(ii)      = tc(idx9,k,j)
                             vP.v(ii)      = P(idx9,k,j)
                             vH.v(ii)      = H(idx9,k,j)
                             vTk.v(ii)     = Tk(idx9,k,j) 
                             vPdT.v(ii)    = Pd(idx9,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx9,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx10         = i+10*XMM_LEN+ii
                             vT.v(ii)      = tc(idx10,k,j)
                             vP.v(ii)      = P(idx10,k,j)
                             vH.v(ii)      = H(idx10,k,j)
                             vTk.v(ii)     = Tk(idx10,k,j) 
                             vPdT.v(ii)    = Pd(idx10,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx10,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx11          = i+11*XMM_LEN+ii
                             vT.v(ii)      = tc(idx11,k,j)
                             vP.v(ii)      = P(idx11,k,j)
                             vH.v(ii)      = H(idx11,k,j)
                             vTk.v(ii)     = Tk(idx11,k,j) 
                             vPdT.v(ii)    = Pd(idx11,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx11,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx12          = i+12*XMM_LEN+ii
                             vT.v(ii)      = tc(idx12,k,j)
                             vP.v(ii)      = P(idx12,k,j)
                             vH.v(ii)      = H(idx12,k,j)
                             vTk.v(ii)     = Tk(idx12,k,j) 
                             vPdT.v(ii)    = Pd(idx12,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx12,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx13         = i+13*XMM_LEN+ii
                             vT.v(ii)      = tc(idx13,k,j)
                             vP.v(ii)      = P(idx13,k,j)
                             vH.v(ii)      = H(idx13,k,j)
                             vTk.v(ii)     = Tk(idx13,k,j) 
                             vPdT.v(ii)    = Pd(idx13,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx13,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx14         = i+14*XMM_LEN+ii
                             vT.v(ii)      = tc(idx14,k,j)
                             vP.v(ii)      = P(idx14,k,j)
                             vH.v(ii)      = H(idx14,k,j)
                             vTk.v(ii)     = Tk(idx14,k,j) 
                             vPdT.v(ii)    = Pd(idx14,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx14,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx15         = i+15*XMM_LEN+ii
                             vT.v(ii)      = tc(idx15,k,j)
                             vP.v(ii)      = P(idx15,k,j)
                             vH.v(ii)      = H(idx15,k,j)
                             vTk.v(ii)     = Tk(idx15,k,j) 
                             vPdT.v(ii)    = Pd(idx15,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx15,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx16         = i+16*XMM_LEN+ii
                             vT.v(ii)      = tc(idx16,k,j)
                             vP.v(ii)      = P(idx16,k,j)
                             vH.v(ii)      = H(idx16,k,j)
                             vTk.v(ii)     = Tk(idx16,k,j) 
                             vPdT.v(ii)    = Pd(idx16,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx16,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx17         = i+17*XMM_LEN+ii
                             vT.v(ii)      = tc(idx17,k,j)
                             vP.v(ii)      = P(idx17,k,j)
                             vH.v(ii)      = H(idx17,k,j)
                             vTk.v(ii)     = Tk(idx17,k,j) 
                             vPdT.v(ii)    = Pd(idx17,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx17,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx18         = i+18*XMM_LEN+ii
                             vT.v(ii)      = tc(idx18,k,j)
                             vP.v(ii)      = P(idx18,k,j)
                             vH.v(ii)      = H(idx18,k,j)
                             vTk.v(ii)     = Tk(idx18,k,j) 
                             vPdT.v(ii)    = Pd(idx18,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx18,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx19         = i+19*XMM_LEN+ii
                             vT.v(ii)      = tc(idx19,k,j)
                             vP.v(ii)      = P(idx19,k,j)
                             vH.v(ii)      = H(idx19,k,j)
                             vTk.v(ii)     = Tk(idx19,k,j) 
                             vPdT.v(ii)    = Pd(idx19,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx19,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx20         = i+20*XMM_LEN+ii
                             vT.v(ii)      = tc(idx20,k,j)
                             vP.v(ii)      = P(idx20,k,j)
                             vH.v(ii)      = H(idx20,k,j)
                             vTk.v(ii)     = Tk(idx20,k,j) 
                             vPdT.v(ii)    = Pd(idx20,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx20,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx21         = i+21*XMM_LEN+ii
                             vT.v(ii)      = tc(idx21,k,j)
                             vP.v(ii)      = P(idx21,k,j)
                             vH.v(ii)      = H(idx21,k,j)
                             vTk.v(ii)     = Tk(idx21,k,j) 
                             vPdT.v(ii)    = Pd(idx21,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx21,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx22         = i+22*XMM_LEN+ii
                             vT.v(ii)      = tc(idx22,k,j)
                             vP.v(ii)      = P(idx22,k,j)
                             vH.v(ii)      = H(idx22,k,j)
                             vTk.v(ii)     = Tk(idx22,k,j) 
                             vPdT.v(ii)    = Pd(idx22,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx22,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx23         = i+23*XMM_LEN+ii
                             vT.v(ii)      = tc(idx23,k,j)
                             vP.v(ii)      = P(idx23,k,j)
                             vH.v(ii)      = H(idx23,k,j)
                             vTk.v(ii)     = Tk(idx23,k,j) 
                             vPdT.v(ii)    = Pd(idx23,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx23,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx24         = i+24*XMM_LEN+ii
                             vT.v(ii)      = tc(idx24,k,j)
                             vP.v(ii)      = P(idx24,k,j)
                             vH.v(ii)      = H(idx24,k,j)
                             vTk.v(ii)     = Tk(idx24,k,j) 
                             vPdT.v(ii)    = Pd(idx24,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx24,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx25         = i+25*XMM_LEN+ii
                             vT.v(ii)      = tc(idx25,k,j)
                             vP.v(ii)      = P(idx25,k,j)
                             vH.v(ii)      = H(idx25,k,j)
                             vTk.v(ii)     = Tk(idx25,k,j) 
                             vPdT.v(ii)    = Pd(idx25,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx25,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx26         = i+26*XMM_LEN+ii
                             vT.v(ii)      = tc(idx26,k,j)
                             vP.v(ii)      = P(idx26,k,j)
                             vH.v(ii)      = H(idx26,k,j)
                             vTk.v(ii)     = Tk(idx26,k,j) 
                             vPdT.v(ii)    = Pd(idx26,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx26,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx27         = i+27*XMM_LEN+ii
                             vT.v(ii)      = tc(idx27,k,j)
                             vP.v(ii)      = P(idx27,k,j)
                             vH.v(ii)      = H(idx27,k,j)
                             vTk.v(ii)     = Tk(idx27,k,j) 
                             vPdT.v(ii)    = Pd(idx27,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx27,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx28         = i+28*XMM_LEN+ii
                             vT.v(ii)      = tc(idx28,k,j)
                             vP.v(ii)      = P(idx28,k,j)
                             vH.v(ii)      = H(idx28,k,j)
                             vTk.v(ii)     = Tk(idx28,k,j) 
                             vPdT.v(ii)    = Pd(idx28,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx28,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx29         = i+29*XMM_LEN+ii
                             vT.v(ii)      = tc(idx29,k,j)
                             vP.v(ii)      = P(idx29,k,j)
                             vH.v(ii)      = H(idx29,k,j)
                             vTk.v(ii)     = Tk(idx29,k,j) 
                             vPdT.v(ii)    = Pd(idx29,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx29,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx30         = i+30*XMM_LEN+ii
                             vT.v(ii)      = tc(idx30,k,j)
                             vP.v(ii)      = P(idx30,k,j)
                             vH.v(ii)      = H(idx30,k,j)
                             vTk.v(ii)     = Tk(idx30,k,j) 
                             vPdT.v(ii)    = Pd(idx30,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx30,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx31         = i+31*XMM_LEN+ii
                             vT.v(ii)      = tc(idx31,k,j)
                             vP.v(ii)      = P(idx31,k,j)
                             vH.v(ii)      = H(idx31,k,j)
                             vTk.v(ii)     = Tk(idx31,k,j) 
                             vPdT.v(ii)    = Pd(idx31,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx31,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                         end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6  
                           end do
                      end do ! i
                   end do ! k
                 end do  ! j
                return 
            end if       
        else if(water_or_ice == 1) then 
             
           if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
            
                 do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                vT.v(ii)      = tc(i+ii,k,j)
                                vP.v(ii)      = P(i+ii,k,j)
                                vH.v(ii)      = H(i+ii,k,j)
                                vTk.v(ii)     = Tk(i+ii,k,j) 
                                vPdT.v(ii)    = Pd(i+ii,k,j)
                                vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                                vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                                vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                                vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                                vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                                vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                vtmp1.v(ii)   = vPdT.v(i)+veT.v(ii)+veTT.v(ii)
                                nref(i+ii,k,j)      = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                            end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endi
                             do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                                     nref(iii,k,j) = a6  
                                end do
                         end do
                      end do
                  end do 
                  return 
                  
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                  
                do j=jts, jte 
                   do k=kts, kte 
                      do i=its, iand(ite-1,inot(3)),XMM_LEN*32 
                                call mm_prefetch(tc(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+32*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                         do ii=0, 3 
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx3,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx8          = i+8*XMM_LEN+ii
                             vT.v(ii)      = tc(idx8,k,j)
                             vP.v(ii)      = P(idx8,k,j)
                             vH.v(ii)      = H(idx8,k,j)
                             vTk.v(ii)     = Tk(idx8,k,j) 
                             vPdT.v(ii)    = Pd(idx8,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx8,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx9          = i+9*XMM_LEN+ii
                             vT.v(ii)      = tc(idx9,k,j)
                             vP.v(ii)      = P(idx9,k,j)
                             vH.v(ii)      = H(idx9,k,j)
                             vTk.v(ii)     = Tk(idx9,k,j) 
                             vPdT.v(ii)    = Pd(idx9,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx9,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx10          = i+10*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx10,k,j)
                             vH.v(ii)      = H(idx10,k,j)
                             vTk.v(ii)     = Tk(idx10,k,j) 
                             vPdT.v(ii)    = Pd(idx10,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx10,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx11          = i+11*XMM_LEN+ii
                             vT.v(ii)      = tc(idx11,k,j)
                             vP.v(ii)      = P(idx11,k,j)
                             vH.v(ii)      = H(idx11,k,j)
                             vTk.v(ii)     = Tk(idx11,k,j) 
                             vPdT.v(ii)    = Pd(idx11,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx11,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx12          = i+12*XMM_LEN+ii
                             vT.v(ii)      = tc(idx12,k,j)
                             vP.v(ii)      = P(idx12,k,j)
                             vH.v(ii)      = H(idx12,k,j)
                             vTk.v(ii)     = Tk(idx12,k,j) 
                             vPdT.v(ii)    = Pd(idx12,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx12,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx13          = i+13*XMM_LEN+ii
                             vT.v(ii)      = tc(idx13,k,j)
                             vP.v(ii)      = P(idx13,k,j)
                             vH.v(ii)      = H(idx13,k,j)
                             vTk.v(ii)     = Tk(idx13,k,j) 
                             vPdT.v(ii)    = Pd(idx13,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx13,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx14          = i+14*XMM_LEN+ii
                             vT.v(ii)      = tc(idx14,k,j)
                             vP.v(ii)      = P(idx14,k,j)
                             vH.v(ii)      = H(idx14,k,j)
                             vTk.v(ii)     = Tk(idx14,k,j) 
                             vPdT.v(ii)    = Pd(idx14,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx14,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx15          = i+15*XMM_LEN+ii
                             vT.v(ii)      = tc(idx15,k,j)
                             vP.v(ii)      = P(idx15,k,j)
                             vH.v(ii)      = H(idx15,k,j)
                             vTk.v(ii)     = Tk(idx15,k,j) 
                             vPdT.v(ii)    = Pd(idx15,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx15,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx16          = i+16*XMM_LEN+ii
                             vT.v(ii)      = tc(idx16,k,j)
                             vP.v(ii)      = P(idx16,k,j)
                             vH.v(ii)      = H(idx16,k,j)
                             vTk.v(ii)     = Tk(idx16,k,j) 
                             vPdT.v(ii)    = Pd(idx16,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx16)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx17          = i+17*XMM_LEN+ii
                             vT.v(ii)      = tc(idx17,k,j)
                             vP.v(ii)      = P(idx17,k,j)
                             vH.v(ii)      = H(idx17,k,j)
                             vTk.v(ii)     = Tk(idx17,k,j) 
                             vPdT.v(ii)    = Pd(idx17,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx17,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx18          = i+18*XMM_LEN+ii
                             vT.v(ii)      = tc(idx18,k,j)
                             vP.v(ii)      = P(idx18,k,j)
                             vH.v(ii)      = H(idx18,k,j)
                             vTk.v(ii)     = Tk(idx18,k,j) 
                             vPdT.v(ii)    = Pd(idx18,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx18,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx19          = i+19*XMM_LEN+ii
                             vT.v(ii)      = tc(idx19,k,j)
                             vP.v(ii)      = P(idx19,k,j)
                             vH.v(ii)      = H(idx19,k,j)
                             vTk.v(ii)     = Tk(idx19,k,j) 
                             vPdT.v(ii)    = Pd(idx19,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx19,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx20          = i+20*XMM_LEN+ii
                             vT.v(ii)      = tc(idx20,k,j)
                             vP.v(ii)      = P(idx20,k,j)
                             vH.v(ii)      = H(idx20,k,j)
                             vTk.v(ii)     = Tk(idx20,k,j) 
                             vPdT.v(ii)    = Pd(idx20,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx20,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx21          = i+21*XMM_LEN+ii
                             vT.v(ii)      = tc(idx21,k,j)
                             vP.v(ii)      = P(idx21,k,j)
                             vH.v(ii)      = H(idx21,k,j)
                             vTk.v(ii)     = Tk(idx21,k,j) 
                             vPdT.v(ii)    = Pd(idx21,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx21,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx22          = i+22*XMM_LEN+ii
                             vT.v(ii)      = tc(idx22,k,j)
                             vP.v(ii)      = P(idx22,k,j)
                             vH.v(ii)      = H(idx22,k,j)
                             vTk.v(ii)     = Tk(idx22,k,j) 
                             vPdT.v(ii)    = Pd(idx22,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx22,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx23          = i+23*XMM_LEN+ii
                             vT.v(ii)      = tc(idx23,k,j)
                             vP.v(ii)      = P(idx23,k,j)
                             vH.v(ii)      = H(idx23,k,j)
                             vTk.v(ii)     = Tk(idx23,k,j) 
                             vPdT.v(ii)    = Pd(idx23,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx23,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx24          = i+24*XMM_LEN+ii
                             vT.v(ii)      = tc(idx24,k,j)
                             vP.v(ii)      = P(idx24,k,j)
                             vH.v(ii)      = H(idx24,k,j)
                             vTk.v(ii)     = Tk(idx24,k,j) 
                             vPdT.v(ii)    = Pd(idx24,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx24,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx25          = i+25*XMM_LEN+ii
                             vT.v(ii)      = tc(idx25,k,j)
                             vP.v(ii)      = P(idx25,k,j)
                             vH.v(ii)      = H(idx25,k,j)
                             vTk.v(ii)     = Tk(idx25,k,j) 
                             vPdT.v(ii)    = Pd(idx25,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx25,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx26          = i+26*XMM_LEN+ii
                             vT.v(ii)      = tc(idx26,k,j)
                             vP.v(ii)      = P(idx26,k,j)
                             vH.v(ii)      = H(idx26,k,j)
                             vTk.v(ii)     = Tk(idx26,k,j) 
                             vPdT.v(ii)    = Pd(idx26,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx26,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx27          = i+27*XMM_LEN+ii
                             vT.v(ii)      = tc(idx27,k,j)
                             vP.v(ii)      = P(idx27,k,j)
                             vH.v(ii)      = H(idx27,k,j)
                             vTk.v(ii)     = Tk(idx27,k,j) 
                             vPdT.v(ii)    = Pd(idx27,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx27,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx28          = i+28*XMM_LEN+ii
                             vT.v(ii)      = tc(idx28,k,j)
                             vP.v(ii)      = P(idx28,k,j)
                             vH.v(ii)      = H(idx28,k,j)
                             vTk.v(ii)     = Tk(idx28,k,j) 
                             vPdT.v(ii)    = Pd(idx28,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx28,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx29          = i+29*XMM_LEN+ii
                             vT.v(ii)      = tc(idx29,k,j)
                             vP.v(ii)      = P(idx29,k,j)
                             vH.v(ii)      = H(idx29,k,j)
                             vTk.v(ii)     = Tk(idx29,k,j) 
                             vPdT.v(ii)    = Pd(idx29,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx29,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx30          = i+30*XMM_LEN+ii
                             vT.v(ii)      = tc(idx30,k,j)
                             vP.v(ii)      = P(idx30,k,j)
                             vH.v(ii)      = H(idx30,k,j)
                             vTk.v(ii)     = Tk(idx30,k,j) 
                             vPdT.v(ii)    = Pd(idx30,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx30,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              idx31          = i+31*XMM_LEN+ii
                             vT.v(ii)      = tc(idx31,k,j)
                             vP.v(ii)      = P(idx31,k,j)
                             vH.v(ii)      = H(idx31,k,j)
                             vTk.v(ii)     = Tk(idx31,k,j) 
                             vPdT.v(ii)    = Pd(idx31,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx31,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                        end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6       
                          end do  
                    end do 
                 end do 
              end do 
            end if
        end if 
end subroutine radio_refractivity_index_3D_v128_32x4_ps


subroutine radio_refractivity_index_3D_v128_16x4_ps(tc,Tk,Pd,P,H,nref,its,ite,   &
                                                    kts,kte,jts,jte,water_or_ice)
#if defined(__ICC) || defined(__INTEL_COMPILER)    
        !DIR$ ATTRIBUTES CODE_ALIGN : 32 :: radio_refractivity_index_3D_v128_16x4_ps
        !DIR$ OPTIMIZE : 3
        !DIR$ ATTRIBUTES OPTIMIZATION_PARAMETER: TARGET_ARCH=skylake_avx512 :: radio_refractivity_index_3D_v128_16x4_ps
#endif  
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: tc 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Tk 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Pd 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: P 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: H 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(out):: nref 
      integer(kind=i4),                                  intent(in) :: its 
      integer(kind=i4),                                  intent(in) :: ite 
      integer(kind=i4),                                  intent(in) :: kts 
      integer(kind=i4),                                  intent(in) :: kte 
      integer(kind=i4),                                  intent(in) :: jts 
      integer(kind=i4),                                  intent(in) :: jte   
      integer(kind=i4),                                  intent(in) :: water_or_ice ! 0 for water, 1 for ice
        ! Locals
      character(*),   parameter :: sub_name   = 'radio_refractivity_index_3D_v128_16x4_ps'
      type(XMM4r4_t), parameter :: va_wat     = XMM4r4_t(6.1121_sp)
      type(XMM4r4_t), parameter :: vb_wat     = XMM4r4_t(18.678_sp)
      type(XMM4r4_t), parameter :: vc_wat     = XMM4r4_t(257.14_sp)
      type(XMM4r4_t), parameter :: vd_wat     = XMM4r4_t(234.5_sp)
        ! Ice constants
      type(XMM4r4_t), parameter :: va_ice     = XMM4r4_t(6.1125_sp)
      type(XMM4r4_t), parameter :: vb_ice     = XMM4r4_t(23.036_sp)
      type(XMM4r4_t), parameter :: vc_ice     = XMM4r4_t(279.82_sp)
      type(XMM4r4_t), parameter :: vd_ice     = XMM4r4_t(333.7_sp)
      type(XMM4r4_t), parameter :: vC1        = XMM4r4_t(1.0_sp)
      type(XMM4r4_t), parameter :: vC0001     = XMM4r4_t(0.0001_sp)
      type(XMM4r4_t), parameter :: vC72       = XMM4r4_t(7.2_sp)
      type(XMM4r4_t), parameter :: vC22       = XMM4r4_t(2.2_sp)
      type(XMM4r4_t), parameter :: vC00320    = XMM4r4_t(0.00320_sp)
      type(XMM4r4_t), parameter :: vC00382    = XMM4r4_t(0.00382_sp)
      type(XMM4r4_t), parameter :: vC00000059 = XMM4r4_t(0.0000059_sp)
      type(XMM4r4_t), parameter :: vC00000064 = XMM4r4_t(0.0000064_sp)
      type(XMM4r4_t), parameter :: vC001      = XMM4r4_t(0.01_sp)
      type(XMM4r4_t), parameter :: vC766      = XMM4r4_t(76.6_sp)
      type(XMM4r4_t), parameter :: vC720      = XMM4r4_t(72.0_sp)
      type(XMM4r4_t), parameter :: vC3750000  = XMM4r4_t(3750000.0_sp)
      type(XMM4r4_t), parameter :: vC0000001  = XMM4r4_t(0.000001_sp)
      real(kind=sp), parameter    :: a_wat = 6.1121_sp
      real(kind=sp), parameter    :: b_wat = 18.678_sp
      real(kind=sp), parameter    :: c_wat = 257.14_sp
      real(kind=sp), parameter    :: d_wat = 234.5_sp
        ! Ice constants
      real(kind=sp), parameter    :: a_ice = 6.1125_sp
      real(kind=sp), parameter    :: b_ice = 23.036_sp
      real(kind=sp), parameter    :: c_ice = 279.82_sp
      real(kind=sp), parameter    :: d_ice = 333.7_sp
      real(kind=sp), parameter    :: C1    = 1.0_sp
      real(kind=sp), parameter    :: C0001 = 0.0001_sp
      type(XMM4r4_t), automatic   :: vef_wat, vef_ice, vnum, vden 
      type(XMM4r4_t), automatic   :: vtt, vtd, ves, vPdT, vTk
      type(XMM4r4_t), automatic   :: veT, veTT, ve, vn_tmp
      type(XMM4r4_t), automatic   :: vtc, vP, vH, vtmp1, vtmp2 
      real(kind=dp), automatic    :: ef_wat, ef_ice, num, den
      real(kind=dp), automatic    :: tt, td, es
      real(kind=sp), automatic    :: PdT, eT, eTT, e, n_tmp
      real(kind=sp), automatic    :: a1,a2,a3,a4,a5,a6
      integer(i4),     automatic  :: j,k,i,ii,iii  
      integer(i4),     automatic  :: idx1,idx2,idx3,idx4
      integer(i4),     automatic  :: idx5,idx6,idx7,idx8
      integer(i4),     automatic  :: idx9,idx10,idx11,idx12 
      integer(i4),     automatic  :: idx13,idx14,idx15
        integer(i4),     automatic  :: j_dif,k_dif,i_dif
        logical(i4),     automatic  :: j_dif_eq_1,k_dif_eq_1
        logical(i4),     automatic  :: i_dif_le_4,i_dif_le_128

      j_dif        = jte-jts
      k_dif        = kte-kts 
      i_dif        = ite-its 
      j_dif_eq_1   = j_dif .eq. 1
      k_dif_eq_1   = k_dif .eq. 1
      i_dif_le_4   = (i_dif .gt. 1) && (i_dif .le. 4)
      i_dif_le_128 = (i_dif .gt. 4) && (i_dif .le. 128)
      if(water_or_ice == 0) then 
           
         if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
                   do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                  vT.v(ii)      = tc(i+ii,k,j)
                                  vP.v(ii)      = P(i+ii,k,j)
                                  vH.v(ii)      = H(i+ii,k,j)
                                  vTk.v(ii)     = Tk(i+ii,k,j) 
                                  vPdT.v(ii)    = Pd(i+ii,k,j)
                                  vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                  vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                                  vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                                  vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                                  vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                                  vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                                  vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                  ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                  ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                  vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                  veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                  veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                  vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                                  nref(i+ii,k,j)= vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                              do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                     nref(iii,k,j) = a6  
                                end do
                           end do 
                        end do
                     end do 
                     return 
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                    
                  do j=jts, jte 
                     do k=kts, kte 
                        do i=its, iand(ite-1,inot(3)),XMM_LEN*16 
                                call mm_prefetch(tc(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                           do ii=0, 3 
                   
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx8          = i+8*XMM_LEN+ii
                             vT.v(ii)      = tc(idx8,k,j)
                             vP.v(ii)      = P(idx8,k,j)
                             vH.v(ii)      = H(idx8,k,j)
                             vTk.v(ii)     = Tk(idx8,k,j) 
                             vPdT.v(ii)    = Pd(idx8,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx8,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx9          = i+9*XMM_LEN+ii
                             vT.v(ii)      = tc(idx9,k,j)
                             vP.v(ii)      = P(idx9,k,j)
                             vH.v(ii)      = H(idx9,k,j)
                             vTk.v(ii)     = Tk(idx9,k,j) 
                             vPdT.v(ii)    = Pd(idx9,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx9,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx10         = i+10*XMM_LEN+ii
                             vT.v(ii)      = tc(idx10,k,j)
                             vP.v(ii)      = P(idx10,k,j)
                             vH.v(ii)      = H(idx10,k,j)
                             vTk.v(ii)     = Tk(idx10,k,j) 
                             vPdT.v(ii)    = Pd(idx10,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx10,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx11          = i+11*XMM_LEN+ii
                             vT.v(ii)      = tc(idx11,k,j)
                             vP.v(ii)      = P(idx11,k,j)
                             vH.v(ii)      = H(idx11,k,j)
                             vTk.v(ii)     = Tk(idx11,k,j) 
                             vPdT.v(ii)    = Pd(idx11,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx11,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx12          = i+12*XMM_LEN+ii
                             vT.v(ii)      = tc(idx12,k,j)
                             vP.v(ii)      = P(idx12,k,j)
                             vH.v(ii)      = H(idx12,k,j)
                             vTk.v(ii)     = Tk(idx12,k,j) 
                             vPdT.v(ii)    = Pd(idx12,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx12,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx13         = i+13*XMM_LEN+ii
                             vT.v(ii)      = tc(idx13,k,j)
                             vP.v(ii)      = P(idx13,k,j)
                             vH.v(ii)      = H(idx13,k,j)
                             vTk.v(ii)     = Tk(idx13,k,j) 
                             vPdT.v(ii)    = Pd(idx13,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx13,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx14         = i+14*XMM_LEN+ii
                             vT.v(ii)      = tc(idx14,k,j)
                             vP.v(ii)      = P(idx14,k,j)
                             vH.v(ii)      = H(idx14,k,j)
                             vTk.v(ii)     = Tk(idx14,k,j) 
                             vPdT.v(ii)    = Pd(idx14,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx14,k,j)   = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx15         = i+15*XMM_LEN+ii
                             vT.v(ii)      = tc(idx15,k,j)
                             vP.v(ii)      = P(idx15,k,j)
                             vH.v(ii)      = H(idx15,k,j)
                             vTk.v(ii)     = Tk(idx15,k,j) 
                             vPdT.v(ii)    = Pd(idx15,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx15,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                            
                         end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6  
                           end do
                      end do ! i
                   end do ! k
                 end do  ! j
                return 
            end if       
        else if(water_or_ice == 1) then 
             
           if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
            
                 do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                vT.v(ii)      = tc(i+ii,k,j)
                                vP.v(ii)      = P(i+ii,k,j)
                                vH.v(ii)      = H(i+ii,k,j)
                                vTk.v(ii)     = Tk(i+ii,k,j) 
                                vPdT.v(ii)    = Pd(i+ii,k,j)
                                vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                                vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                                vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                                vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                                vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                                vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                vtmp1.v(ii)   = vPdT.v(i)+veT.v(ii)+veTT.v(ii)
                                nref(i+ii,k,j)      = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                            end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endi
                             do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                                     nref(iii,k,j) = a6  
                                end do
                         end do
                      end do
                  end do 
                  return 
                  
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                  
                do j=jts, jte 
                   do k=kts, kte 
                      do i=its, iand(ite-1,inot(3)),XMM_LEN*16 
                                call mm_prefetch(tc(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+16*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                         do ii=0, 3 
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx3,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx8          = i+8*XMM_LEN+ii
                             vT.v(ii)      = tc(idx8,k,j)
                             vP.v(ii)      = P(idx8,k,j)
                             vH.v(ii)      = H(idx8,k,j)
                             vTk.v(ii)     = Tk(idx8,k,j) 
                             vPdT.v(ii)    = Pd(idx8,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx8,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx9          = i+9*XMM_LEN+ii
                             vT.v(ii)      = tc(idx9,k,j)
                             vP.v(ii)      = P(idx9,k,j)
                             vH.v(ii)      = H(idx9,k,j)
                             vTk.v(ii)     = Tk(idx9,k,j) 
                             vPdT.v(ii)    = Pd(idx9,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx9,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx10          = i+10*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx10,k,j)
                             vH.v(ii)      = H(idx10,k,j)
                             vTk.v(ii)     = Tk(idx10,k,j) 
                             vPdT.v(ii)    = Pd(idx10,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx10,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx11          = i+11*XMM_LEN+ii
                             vT.v(ii)      = tc(idx11,k,j)
                             vP.v(ii)      = P(idx11,k,j)
                             vH.v(ii)      = H(idx11,k,j)
                             vTk.v(ii)     = Tk(idx11,k,j) 
                             vPdT.v(ii)    = Pd(idx11,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx11,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx12          = i+12*XMM_LEN+ii
                             vT.v(ii)      = tc(idx12,k,j)
                             vP.v(ii)      = P(idx12,k,j)
                             vH.v(ii)      = H(idx12,k,j)
                             vTk.v(ii)     = Tk(idx12,k,j) 
                             vPdT.v(ii)    = Pd(idx12,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx12,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx13          = i+13*XMM_LEN+ii
                             vT.v(ii)      = tc(idx13,k,j)
                             vP.v(ii)      = P(idx13,k,j)
                             vH.v(ii)      = H(idx13,k,j)
                             vTk.v(ii)     = Tk(idx13,k,j) 
                             vPdT.v(ii)    = Pd(idx13,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx13,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx14          = i+14*XMM_LEN+ii
                             vT.v(ii)      = tc(idx14,k,j)
                             vP.v(ii)      = P(idx14,k,j)
                             vH.v(ii)      = H(idx14,k,j)
                             vTk.v(ii)     = Tk(idx14,k,j) 
                             vPdT.v(ii)    = Pd(idx14,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx14,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx15          = i+15*XMM_LEN+ii
                             vT.v(ii)      = tc(idx15,k,j)
                             vP.v(ii)      = P(idx15,k,j)
                             vH.v(ii)      = H(idx15,k,j)
                             vTk.v(ii)     = Tk(idx15,k,j) 
                             vPdT.v(ii)    = Pd(idx15,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx15,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             
                        end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6       
                          end do  
                    end do 
                 end do 
              end do 
            end if
        end if 
end subroutine radio_refractivity_index_3D_v128_16x4_ps


subroutine radio_refractivity_index_3D_v128_8x4_ps(tc,Tk,Pd,P,H,nref,its,ite,   &
                                                    kts,kte,jts,jte,water_or_ice)
#if defined(__ICC) || defined(__INTEL_COMPILER)    
        !DIR$ ATTRIBUTES CODE_ALIGN : 32 :: radio_refractivity_index_3D_v128_8x4_ps
        !DIR$ OPTIMIZE : 3
        !DIR$ ATTRIBUTES OPTIMIZATION_PARAMETER: TARGET_ARCH=skylake_avx512 :: radio_refractivity_index_3D_v128_8x4_ps
#endif  
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: tc 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Tk 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: Pd 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: P 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(in) :: H 
      real(kind=sp), dimension(its:ite,kts:kte,jts:jte), intent(out):: nref 
      integer(kind=i4),                                  intent(in) :: its 
      integer(kind=i4),                                  intent(in) :: ite 
      integer(kind=i4),                                  intent(in) :: kts 
      integer(kind=i4),                                  intent(in) :: kte 
      integer(kind=i4),                                  intent(in) :: jts 
      integer(kind=i4),                                  intent(in) :: jte   
      integer(kind=i4),                                  intent(in) :: water_or_ice ! 0 for water, 1 for ice
        ! Locals
      character(*),   parameter :: sub_name   = 'radio_refractivity_index_3D_v128_8x4_ps'
      type(XMM4r4_t), parameter :: va_wat     = XMM4r4_t(6.1121_sp)
      type(XMM4r4_t), parameter :: vb_wat     = XMM4r4_t(18.678_sp)
      type(XMM4r4_t), parameter :: vc_wat     = XMM4r4_t(257.14_sp)
      type(XMM4r4_t), parameter :: vd_wat     = XMM4r4_t(234.5_sp)
        ! Ice constants
      type(XMM4r4_t), parameter :: va_ice     = XMM4r4_t(6.1125_sp)
      type(XMM4r4_t), parameter :: vb_ice     = XMM4r4_t(23.036_sp)
      type(XMM4r4_t), parameter :: vc_ice     = XMM4r4_t(279.82_sp)
      type(XMM4r4_t), parameter :: vd_ice     = XMM4r4_t(333.7_sp)
      type(XMM4r4_t), parameter :: vC1        = XMM4r4_t(1.0_sp)
      type(XMM4r4_t), parameter :: vC0001     = XMM4r4_t(0.0001_sp)
      type(XMM4r4_t), parameter :: vC72       = XMM4r4_t(7.2_sp)
      type(XMM4r4_t), parameter :: vC22       = XMM4r4_t(2.2_sp)
      type(XMM4r4_t), parameter :: vC00320    = XMM4r4_t(0.00320_sp)
      type(XMM4r4_t), parameter :: vC00382    = XMM4r4_t(0.00382_sp)
      type(XMM4r4_t), parameter :: vC00000059 = XMM4r4_t(0.0000059_sp)
      type(XMM4r4_t), parameter :: vC00000064 = XMM4r4_t(0.0000064_sp)
      type(XMM4r4_t), parameter :: vC001      = XMM4r4_t(0.01_sp)
      type(XMM4r4_t), parameter :: vC766      = XMM4r4_t(76.6_sp)
      type(XMM4r4_t), parameter :: vC720      = XMM4r4_t(72.0_sp)
      type(XMM4r4_t), parameter :: vC3750000  = XMM4r4_t(3750000.0_sp)
      type(XMM4r4_t), parameter :: vC0000001  = XMM4r4_t(0.000001_sp)
      real(kind=sp), parameter    :: a_wat = 6.1121_sp
      real(kind=sp), parameter    :: b_wat = 18.678_sp
      real(kind=sp), parameter    :: c_wat = 257.14_sp
      real(kind=sp), parameter    :: d_wat = 234.5_sp
        ! Ice constants
      real(kind=sp), parameter    :: a_ice = 6.1125_sp
      real(kind=sp), parameter    :: b_ice = 23.036_sp
      real(kind=sp), parameter    :: c_ice = 279.82_sp
      real(kind=sp), parameter    :: d_ice = 333.7_sp
      real(kind=sp), parameter    :: C1    = 1.0_sp
      real(kind=sp), parameter    :: C0001 = 0.0001_sp
      type(XMM4r4_t), automatic   :: vef_wat, vef_ice, vnum, vden 
      type(XMM4r4_t), automatic   :: vtt, vtd, ves, vPdT, vTk
      type(XMM4r4_t), automatic   :: veT, veTT, ve, vn_tmp
      type(XMM4r4_t), automatic   :: vtc, vP, vH, vtmp1, vtmp2 
      real(kind=dp), automatic    :: ef_wat, ef_ice, num, den
      real(kind=dp), automatic    :: tt, td, es
      real(kind=sp), automatic    :: PdT, eT, eTT, e, n_tmp
      real(kind=sp), automatic    :: a1,a2,a3,a4,a5,a6
      integer(i4),     automatic  :: j,k,i,ii,iii  
      integer(i4),     automatic  :: idx1,idx2,idx3,idx4
      integer(i4),     automatic  :: idx5,idx6,idx7
        integer(i4),     automatic  :: j_dif,k_dif,i_dif
        logical(i4),     automatic  :: j_dif_eq_1,k_dif_eq_1
        logical(i4),     automatic  :: i_dif_le_4,i_dif_le_128

      j_dif        = jte-jts
      k_dif        = kte-kts 
      i_dif        = ite-its 
      j_dif_eq_1   = j_dif .eq. 1
      k_dif_eq_1   = k_dif .eq. 1
      i_dif_le_4   = (i_dif .gt. 1) && (i_dif .le. 4)
      i_dif_le_128 = (i_dif .gt. 4) && (i_dif .le. 128)
      if(water_or_ice == 0) then 
           
         if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
                   do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                  vT.v(ii)      = tc(i+ii,k,j)
                                  vP.v(ii)      = P(i+ii,k,j)
                                  vH.v(ii)      = H(i+ii,k,j)
                                  vTk.v(ii)     = Tk(i+ii,k,j) 
                                  vPdT.v(ii)    = Pd(i+ii,k,j)
                                  vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                  vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                                  vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                                  vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                                  vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                                  vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                                  vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                  ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                  ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                  vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                  veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                  veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                  vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                                  nref(i+ii,k,j)= vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                              end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                              do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                     nref(iii,k,j) = a6  
                                end do
                           end do 
                        end do
                     end do 
                     return 
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                    
                  do j=jts, jte 
                     do k=kts, kte 
                        do i=its, iand(ite-1,inot(3)),XMM_LEN*8 
                                call mm_prefetch(tc(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                           do ii=0, 3 
                   
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                                                                                    
                         end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6  
                           end do
                      end do ! i
                   end do ! k
                 end do  ! j
                return 
            end if       
        else if(water_or_ice == 1) then 
             
           if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_4) then 
               do j=jts, jte 
                  do k=kts, kte 
                     do i=its, ite 
                         a1          = tc(i,k,j)
                         a2          = Tk(i,k,j)
                         a3          = Pd(i,k,j)
                         a4          = P(i,k,j)
                         a5          = H(i,k,j)
                         a6          = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                         nref(i,k,j) = a6 
                     end do
                  end do 
                end do 
                return 
         else if(j_dif_eq_1 && k_dif_eq_1 && i_dif_le_128) then 
            
                 do j=jts, jte 
                       do k=kts, kte 
                          do i=its, iand(ite-1,inot(3)),XMM_LEN 
!$omp simd linear(ii:1)  
                             do ii=0, 3 
                                vT.v(ii)      = tc(i+ii,k,j)
                                vP.v(ii)      = P(i+ii,k,j)
                                vH.v(ii)      = H(i+ii,k,j)
                                vTk.v(ii)     = Tk(i+ii,k,j) 
                                vPdT.v(ii)    = Pd(i+ii,k,j)
                                vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                                vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                                vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                                vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                                vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                                vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                                vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                                ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                                ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                                vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                                veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                                veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                                vtmp1.v(ii)   = vPdT.v(i)+veT.v(ii)+veTT.v(ii)
                                nref(i+ii,k,j)      = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                            end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endi
                             do iii=i, ite-1
                                     a1            = tc(iii,k,j)
                                     a2            = Tk(iii,k,j)
                                     a3            = Pd(iii,k,j)
                                     a4            = P(iii,k,j)
                                     a5            = H(iii,k,j)
                                     a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                                     nref(iii,k,j) = a6  
                                end do
                         end do
                      end do
                  end do 
                  return 
                  
         else if(j_dif>1 && k_dif>1 && i_dif>128) then
                  
                do j=jts, jte 
                   do k=kts, kte 
                      do i=its, iand(ite-1,inot(3)),XMM_LEN*8
                                call mm_prefetch(tc(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(P(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(H(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Tk(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
                                call mm_prefetch(Pd(i+8*XMM_LEN,k,j),FOR_K_PREFETCH_T1)
!$omp simd linear(ii:1)  
                         do ii=0, 3 
                             vT.v(ii)      = tc(i+0+ii,k,j)
                             vP.v(ii)      = P(i+0+ii,k,j)
                             vH.v(ii)      = H(i+0+ii,k,j)
                             vTk.v(ii)     = Tk(i+0+ii,k,j) 
                             vPdT.v(ii)    = Pd(i+0+ii,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii,k,j)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1,k,j)
                             vP.v(ii)      = P(idx1,k,j)
                             vH.v(ii)      = H(idx1,k,j)
                             vTk.v(ii)     = Tk(idx1,k,j) 
                             vPdT.v(ii)    = Pd(idx1,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2,k,j)
                             vP.v(ii)      = P(idx2,k,j)
                             vH.v(ii)      = H(idx2,k,j)
                             vTk.v(ii)     = Tk(idx2,k,j) 
                             vPdT.v(ii)    = Pd(idx2,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3,k,j)
                             vP.v(ii)      = P(idx3,k,j)
                             vH.v(ii)      = H(idx3,k,j)
                             vTk.v(ii)     = Tk(idx3,k,j) 
                             vPdT.v(ii)    = Pd(idx3,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx4          = i+4*XMM_LEN+ii
                             vT.v(ii)      = tc(idx4,k,j)
                             vP.v(ii)      = P(idx4,k,j)
                             vH.v(ii)      = H(idx4,k,j)
                             vTk.v(ii)     = Tk(idx4,k,j) 
                             vPdT.v(ii)    = Pd(idx4,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx4,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx5          = i+5*XMM_LEN+ii
                             vT.v(ii)      = tc(idx5,k,j)
                             vP.v(ii)      = P(idx5,k,j)
                             vH.v(ii)      = H(idx5,k,j)
                             vTk.v(ii)     = Tk(idx5,k,j) 
                             vPdT.v(ii)    = Pd(idx5,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx5,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx6          = i+6*XMM_LEN+ii
                             vT.v(ii)      = tc(idx6,k,j)
                             vP.v(ii)      = P(idx6,k,j)
                             vH.v(ii)      = H(idx6,k,j)
                             vTk.v(ii)     = Tk(idx6,k,j) 
                             vPdT.v(ii)    = Pd(idx6,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx6,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx7          = i+7*XMM_LEN+ii
                             vT.v(ii)      = tc(idx7,k,j)
                             vP.v(ii)      = P(idx7,k,j)
                             vH.v(ii)      = H(idx7,k,j)
                             vTk.v(ii)     = Tk(idx7,k,j) 
                             vPdT.v(ii)    = Pd(idx7,k,j)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(ii)*vtt.v(ii)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx7,k,j)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                                                                                      
                        end do 
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif
                           do iii=i, ite-1
                                 a1            = tc(iii,k,j)
                                 a2            = Tk(iii,k,j)
                                 a3            = Pd(iii,k,j)
                                 a4            = P(iii,k,j)
                                 a5            = H(iii,k,j)
                                 a6            = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                                 nref(iii,k,j) = a6       
                          end do  
                    end do 
                 end do 
              end do 
            end if
        end if 
end subroutine radio_refractivity_index_3D_v128_8x4_ps



subroutine radio_refractivity_index_1D_v128_4x4_ps(tc,Tk,Pd,P,H,nref,n,water_or_ice)
#if defined(__ICC) || defined(__INTEL_COMPILER)    
        !DIR$ ATTRIBUTES CODE_ALIGN : 32 :: radio_refractivity_index_1D_v128_4x4_ps
        !DIR$ OPTIMIZE : 3
        !DIR$ ATTRIBUTES OPTIMIZATION_PARAMETER: TARGET_ARCH=skylake_avx512 :: radio_refractivity_index_1D_v128_4x4_ps
#endif  
        real(kind=sp), allocatable, dimension(:), intent(in) :: tc 
        real(kind=sp), allocatable, dimension(:), intent(in) :: Tk 
        real(kind=sp), allocatable, dimension(:), intent(in) :: Pd 
        real(kind=sp), allocatable, dimension(:), intent(in) :: P 
        real(kind=sp), allocatable, dimension(:), intent(in) :: H 
        real(kind=sp), allocatable, dimension(:), intent(out):: nref 
        integer(kind=i4),                         intent(in) :: n 
        integer(kind=i4),intent(in)                          :: water_or_ice ! 0 for water, 1 for ice
        ! Locals
        character(*),   parameter :: sub_name   = 'radio_refractivity_index_1D_v128_4x4_ps'
        type(XMM4r4_t), parameter :: va_wat     = XMM4r4_t(6.1121_sp)
        type(XMM4r4_t), parameter :: vb_wat     = XMM4r4_t(18.678_sp)
        type(XMM4r4_t), parameter :: vc_wat     = XMM4r4_t(257.14_sp)
        type(XMM4r4_t), parameter :: vd_wat     = XMM4r4_t(234.5_sp)
        ! Ice constants
        type(XMM4r4_t), parameter :: va_ice     = XMM4r4_t(6.1125_sp)
        type(XMM4r4_t), parameter :: vb_ice     = XMM4r4_t(23.036_sp)
        type(XMM4r4_t), parameter :: vc_ice     = XMM4r4_t(279.82_sp)
        type(XMM4r4_t), parameter :: vd_ice     = XMM4r4_t(333.7_sp)
        type(XMM4r4_t), parameter :: vC1        = XMM4r4_t(1.0_sp)
        type(XMM4r4_t), parameter :: vC0001     = XMM4r4_t(0.0001_sp)
        type(XMM4r4_t), parameter :: vC72       = XMM4r4_t(7.2_sp)
        type(XMM4r4_t), parameter :: vC22       = XMM4r4_t(2.2_sp)
        type(XMM4r4_t), parameter :: vC00320    = XMM4r4_t(0.00320_sp)
        type(XMM4r4_t), parameter :: vC00382    = XMM4r4_t(0.00382_sp)
        type(XMM4r4_t), parameter :: vC00000059 = XMM4r4_t(0.0000059_sp)
        type(XMM4r4_t), parameter :: vC00000064 = XMM4r4_t(0.0000064_sp)
        type(XMM4r4_t), parameter :: vC001      = XMM4r4_t(0.01_sp)
        type(XMM4r4_t), parameter :: vC766      = XMM4r4_t(76.6_sp)
        type(XMM4r4_t), parameter :: vC720      = XMM4r4_t(72.0_sp)
        type(XMM4r4_t), parameter :: vC3750000  = XMM4r4_t(3750000.0_sp)
        type(XMM4r4_t), parameter :: vC0000001  = XMM4r4_t(0.000001_sp)
        real(kind=sp), parameter    :: a_wat = 6.1121_sp
        real(kind=sp), parameter    :: b_wat = 18.678_sp
        real(kind=sp), parameter    :: c_wat = 257.14_sp
        real(kind=sp), parameter    :: d_wat = 234.5_sp
        ! Ice constants
        real(kind=sp), parameter    :: a_ice = 6.1125_sp
        real(kind=sp), parameter    :: b_ice = 23.036_sp
        real(kind=sp), parameter    :: c_ice = 279.82_sp
        real(kind=sp), parameter    :: d_ice = 333.7_sp
        real(kind=sp), parameter    :: C1    = 1.0_sp
        real(kind=sp), parameter    :: C0001 = 0.0001_sp
        type(XMM4r4_t), automatic   :: vef_wat, vef_ice, vnum, vden 
        type(XMM4r4_t), automatic   :: vtt, vtd, ves, vPdT, vTk
        type(XMM4r4_t), automatic   :: veT, veTT, ve, vn_tmp
        type(XMM4r4_t), automatic   :: vtc, vP, vH, vtmp1, vtmp2 
        real(kind=dp), automatic    :: ef_wat, ef_ice, num, den
        real(kind=dp), automatic    :: tt, td, es
        real(kind=sp), automatic    :: PdT, eT, eTT, e, n_tmp
        real(kind=sp), automatic    :: a1,a2,a3,a4,a5,a6
        integer(i4),     automatic  :: i,ii,j
        integer(i4),     automatic  :: idx1,idx2,idx3

        if(water_or_ice == 0) then 
            if(n <= 0) then
               return 
            else if(n==1) then 
                 a1      = tc(0)
                 a2      = Tk(0)
                 a3      = Pd(0)
                 a4      = P(0)
                 a5      = H(0)
                 a6      = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                 nref(0) = a6 
                 return 
            else if(n>1 && n<=4) then 
!$omp simd linear(i:1)  
                  do i=0, 3 
                     vT.v(i)      = tc(i)
                     vP.v(i)      = P(i)
                     vH.v(i)      = H(i)
                     vTk.v(i)     = Tk(i) 
                     vPdT.v(i)    = Pd(i)
                     vtt.v(i)     = vT.v(i)*vT.v(i)
                     vtd.v(i)     = vT.v(i)/vd_wat.v(i)
                     vnum.v(i)    = (vb_wat.v(i)-vtd.v(i))*vT.v(i)
                     vden.v(i)    = vT.v(i)+vc_wat.v(i)
                     vtmp1.v(i)   = vC00320.v(i)+vC00000059.v(i)*vtt.v(i)
                     vtmp2.v(i)   = vC72.v(i)+vP.v(i)
                     vef_wat.v(i) = vC1.v(i)+vC0001.v(i)*vtmp2.v(i)*vtmp1.v(i)
                     ves.v(i)     = vef_wat.v(i)*va_wat.v(i)*exp(vnum.v(i)/vden.v(i))
                     ve.v(i)      = vH.v(i)*ves.v(i)*vC001.v(i)
                     vPdT.v(i)    = (vC766.v(i)*vPdT.v(i))/vTk.v(i)
                     veT.v(i)     = (vC720.v(i)*ve.v(i))/vTk.v(i)
                     veTT.v(i)    = vC3750000.v(i)*(ve.v(i)/(vTk.v(i)*vTk.v(i)))
                     vtmp1.v(i)   = vPdT.v(i)+veT.v(i)+veTT.v(i)
                     nref(i)      = vC1.v(i)+vtmp1.v(i)*vC0000001.v(i)
                  end do 
                  return 
            else if(n>4 && n<=32) then
                   do i = 0,iand(n-1,inot(3)), XMM_LEN 
!$omp simd linear(i:1)  
                        do ii=0, 3  
                             vT.v(ii)      = tc(i+ii)
                             vP.v(ii)      = P(i+ii)
                             vH.v(ii)      = H(i+ii)
                             vTk.v(ii)     = Tk(i+ii) 
                             vPdT.v(ii)    = Pd(i+ii)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+ii)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                        end do 
                   end do  
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif   
                      do j = i, n-1 
                         a1      = tc(j)
                         a2      = Tk(j)
                         a3      = Pd(j)
                         a4      = P(j)
                         a5      = H(j)   
                         nref(j) = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                      end do 
                      return 
            else if(n>32) then
                    do i = 0,iand(n-1,inot(3)), XMM_LEN*4
                       call mm_prefetch(tc(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(P(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(H(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(Tk(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(Pd(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
!$omp simd linear(i:1)  
                        do ii=0, 3  
                             vT.v(ii)      = tc(i+0+ii)
                             vP.v(ii)      = P(i+0+ii)
                             vH.v(ii)      = H(i+0+ii)
                             vTk.v(ii)     = Tk(i+0+ii) 
                             vPdT.v(ii)    = Pd(i+0+ii)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1)
                             vP.v(ii)      = P(idx1)
                             vH.v(ii)      = H(idx1)
                             vTk.v(ii)     = Tk(idx1) 
                             vPdT.v(ii)    = Pd(idx1)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2)
                             vP.v(ii)      = P(idx2)
                             vH.v(ii)      = H(idx2)
                             vTk.v(ii)     = Tk(idx2) 
                             vPdT.v(ii)    = Pd(idx2)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3)
                             vP.v(ii)      = P(idx3)
                             vH.v(ii)      = H(idx3)
                             vTk.v(ii)     = Tk(idx3) 
                             vPdT.v(ii)    = Pd(idx3)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_wat.v(ii)
                             vnum.v(ii)    = (vb_wat.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_wat.v(ii)
                             vtmp1.v(ii)   = vC00320.v(ii)+vC00000059.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC72.v(ii)+vP.v(ii)
                             vef_wat.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_wat.v(ii)*va_wat.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                        end do 
                   end do  
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif   
                      do j = i, n-1 
                         a1      = tc(j)
                         a2      = Tk(j)
                         a3      = Pd(j)
                         a4      = P(j)
                         a5      = H(j)   
                         nref(j) = refractivity_index_n_r4(a1,a2,a3,a4,a5,0)
                      end do 
                      return 
            end if
        else if(water_or_ice == 1) then 
              if(n <= 0) then
                 return 
              else if(n==1) then 
                  a1      = tc(0)
                  a2      = Tk(0)
                  a3      = Pd(0)
                  a4      = P(0)
                  a5      = H(0)
                  a6      = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                  nref(0) = a6 
                  return 
             else if(n>1 && n<=4) then 
!$omp simd linear(i:1)  
                  do i=0, 3 
                     vT.v(i)      = tc(i)
                     vP.v(i)      = P(i)
                     vH.v(i)      = H(i)
                     vTk.v(i)     = Tk(i) 
                     vPdT.v(i)    = Pd(i)
                     vtt.v(i)     = vT.v(i)*vT.v(i)
                     vtd.v(i)     = vT.v(i)/vd_ice.v(i)
                     vnum.v(i)    = (vb_ice.v(i)-vtd.v(i))*vT.v(i)
                     vden.v(i)    = vT.v(i)+vc_ice.v(i)
                     vtmp1.v(i)   = vC00382.v(i)+vC00000064.v(i)*vtt.v(i)
                     vtmp2.v(i)   = vC22.v(i)+vP.v(i)
                     vef_ice.v(i) = vC1.v(i)+vC0001.v(i)*vtmp2.v(i)*vtmp1.v(i)
                     ves.v(i)     = vef_ice.v(i)*va_ice.v(i)*exp(vnum.v(i)/vden.v(i))
                     ve.v(i)      = vH.v(i)*ves.v(i)*vC001.v(i)
                     vPdT.v(i)    = (vC766.v(i)*vPdT.v(i))/vTk.v(i)
                     veT.v(i)     = (vC720.v(i)*ve.v(i))/vTk.v(i)
                     veTT.v(i)    = vC3750000.v(i)*(ve.v(i)/(vTk.v(i)*vTk.v(i)))
                     vtmp1.v(i)   = vPdT.v(i)+veT.v(i)+veTT.v(i)
                     nref(i)      = vC1.v(i)+vtmp1.v(i)*vC0000001.v(i)
                  end do 
                  return 
            else if(n>4 && n<=32) then
                   do i = 0,iand(n-1,inot(3)), XMM_LEN 
!$omp simd linear(i:1)  
                        do ii=0, 3  
                             vT.v(ii)      = tc(i+ii)
                             vP.v(ii)      = P(i+ii)
                             vH.v(ii)      = H(i+ii)
                             vTk.v(ii)     = Tk(i+ii) 
                             vPdT.v(ii)    = Pd(i+ii)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+ii)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                        end do 
                   end do  
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif   
                      do j = i, n-1 
                         a1      = tc(j)
                         a2      = Tk(j)
                         a3      = Pd(j)
                         a4      = P(j)
                         a5      = H(j)   
                         nref(j) = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                      end do 
                      return 
            else if(n>32) then
                    do i = 0,iand(n-1,inot(3)), XMM_LEN*4
                       call mm_prefetch(tc(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(P(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(H(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(Tk(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
                       call mm_prefetch(Pd(i+4*XMM_LEN),FOR_K_PREFETCH_T1)
!$omp simd linear(i:1)  
                        do ii=0, 3  
                             vT.v(ii)      = tc(i+0+ii)
                             vP.v(ii)      = P(i+0+ii)
                             vH.v(ii)      = H(i+0+ii)
                             vTk.v(ii)     = Tk(i+0+ii) 
                             vPdT.v(ii)    = Pd(i+0+ii)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(i+0+ii)  = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx1          = i+1*XMM_LEN+ii
                             vT.v(ii)      = tc(idx1)
                             vP.v(ii)      = P(idx1)
                             vH.v(ii)      = H(idx1)
                             vTk.v(ii)     = Tk(idx1) 
                             vPdT.v(ii)    = Pd(idx1)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx1)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx2          = i+2*XMM_LEN+ii
                             vT.v(ii)      = tc(idx2)
                             vP.v(ii)      = P(idx2)
                             vH.v(ii)      = H(idx2)
                             vTk.v(ii)     = Tk(idx2) 
                             vPdT.v(ii)    = Pd(idx2)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx2)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                             idx3          = i+3*XMM_LEN+ii
                             vT.v(ii)      = tc(idx3)
                             vP.v(ii)      = P(idx3)
                             vH.v(ii)      = H(idx3)
                             vTk.v(ii)     = Tk(idx3) 
                             vPdT.v(ii)    = Pd(idx3)
                             vtt.v(ii)     = vT.v(ii)*vT.v(ii)
                             vtd.v(ii)     = vT.v(ii)/vd_ice.v(ii)
                             vnum.v(ii)    = (vb_ice.v(ii)-vtd.v(ii))*vT.v(ii)
                             vden.v(ii)    = vT.v(ii)+vc_ice.v(ii)
                             vtmp1.v(ii)   = vC00382.v(ii)+vC00000064.v(i)*vtt.v(i)
                             vtmp2.v(ii)   = vC22.v(ii)+vP.v(ii)
                             vef_ice.v(ii) = vC1.v(ii)+vC0001.v(ii)*vtmp2.v(ii)*vtmp1.v(ii)
                             ves.v(ii)     = vef_ice.v(ii)*va_ice.v(ii)*exp(vnum.v(ii)/vden.v(ii))
                             ve.v(ii)      = vH.v(ii)*ves.v(ii)*vC001.v(ii)
                             vPdT.v(ii)    = (vC766.v(ii)*vPdT.v(ii))/vTk.v(ii)
                             veT.v(ii)     = (vC720.v(ii)*ve.v(ii))/vTk.v(ii)
                             veTT.v(ii)    = vC3750000.v(ii)*(ve.v(ii)/(vTk.v(ii)*vTk.v(ii)))
                             vtmp1.v(ii)   = vPdT.v(ii)+veT.v(ii)+veTT.v(ii)
                             nref(idx3)    = vC1.v(ii)+vtmp1.v(ii)*vC0000001.v(ii)
                        end do 
                   end do  
#if defined(__ICC) || defined(__INTEL_COMPILER)
         !DIR$ LOOP COUNT MAX=4, MIN=1, AVG=2
#endif   
                      do j = i, n-1 
                         a1      = tc(j)
                         a2      = Tk(j)
                         a3      = Pd(j)
                         a4      = P(j)
                         a5      = H(j)   
                         nref(j) = refractivity_index_n_r4(a1,a2,a3,a4,a5,1)
                      end do 
                      return 
            end if
        end if 
end subroutine radio_refractivity_index_1D_v128_4x4_ps




























end module radio_refractivity_1D_xmm4r4