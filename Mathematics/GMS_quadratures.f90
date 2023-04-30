

module mod_quadratures


!===================================================================================85
 !---------------------------- DESCRIPTION ------------------------------------------85
 !
 !
 !
 !          Module  name:
 !                         mod_quadratures
 !          
 !          Purpose:
 !                   Modern version of Quadpack oscillatory integrators
 !                   
 !                     
 !          History:
 !                        Date: 11-05-2019
 !                        Time: 16:52 GMT+2
 !          
 !          Version:
 !
 !                      Major: 1
 !                      Minor: 0
 !                      Micro: 0
 !
 !    
 !          Author: 
 !                piessens,robert,appl. math. & progr. div. - k.u.leuven
 !                de doncker,elise,appl. math. & progr. div. - k.u.leuven
 !          
 !          ! Modified by:
 !                           Bernard Gingold on 11-05-2019 16:52 GMT+2
 !          
 !         
 !          E-mail:
 !                  
 !                      beniekg@gmail.com
 !==================================================================================85

 ! Tab:5 col - Type and etc.. definitions
 ! Tab:10,11 col - Type , function and subroutine code blocks.

     use mod_kinds, only : int4, dp
     use modprint_error, only : print_non_fatal_error
     implicit none

   contains

     subroutine dqawo(f,a,b,omega,integr,epsabs,epsrel,res,abserr, &
                      neval,ier,leniw,maxp1,lenw,last,iwork,work)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqawo
!              automatic integrator, special-purpose,
!c             integrand with oscillatory cos or sin factor,
!c             clenshaw-curtis method, (end point) singularities,
!c             extrapolation, globally adaptive
!              the routine calculates an approximation result to a given
!c             definite integral i=integral of f(x)*w(x) over (a,b)
!c             where w(x) = cos(omega*x)
!c             or w(x) = sin(omega*x),
!c             hopefully satisfying following claim for accuracy
!c             abs(i-result).le.max(epsabs,epsrel*abs(i)).
           interface
              function f(x) result(v)
                real(kind=dp), intent(in) :: x
                real(kind=dp) :: v
              end function f
           end interface
           real(kind=dp),                        intent(in)    :: a
           real(kind=dp),                        intent(in)    :: b
           real(kind=dp),                        intent(in)    :: omega
           integer(kind=int4),                   intent(in)    :: integr
           real(kind=dp),                        intent(in)    :: epsabs
           real(kind=dp),                        intent(in)    :: epsrel
           real(kind=dp),                        intent(out)   :: res
           real(kind=dp),                        intent(out)   :: abserr
           integer(kind=int4),                   intent(out)   :: neval
           integer(kind=int4),                   intent(inout) :: ier
           integer(kind=int4),                   intent(in)    :: leniw
           integer(kind=int4),                   intent(in)    :: maxp1
           integer(kind=int4),                   intent(in)    :: lenw
           integer(kind=int4),                   intent(iout)  :: last
           integer(kind=int4), dimension(leniw), intent(inout) :: iwork
           real(kind=dp),      dimension(lenw),  intent(in)    :: work
           ! Locals
           integer(kind=int4), automatic :: limit
           integer(kind=int4), automatic :: lvl,l1,l2,l3,l4,momcom
           ! Exec code ....
           ier = 6
           neval = 0
           last  = 0
           res = 0.0_dp
           abserr = 0.0_dp
           if(leniw.lt.2.or.maxp1.lt.1.or.lenw.lt. &
             (leniw*2+maxp1*25)) then
              goto 10
           end if
           limit = leniw/2
           l1 = limit+1
           l2 = limit+l1
           l3 = limit+l2
           l4 = limit+l3
           call DQAWOE(f,a,b,omega,integr,epsabs,epsrel,limit,1,maxp1,res,&
                       abserr,neval,ier,last,work(1),work(l1),work(l2),work(l3),&
                       iwork(1),iwork(l1),momcom,work(l4))
           lvl = 6
10         if(ier == 6) lvl = 0
           if(ier /= 0) then
              call print_non_fatal_error((" ================= Non-Fatal ================== " , &
                                            " Module: mod_quadratures, subroutine: dqawo: abnormal return from dqawo ! ",  &
                                            __LINE__,__FILE__ )
              return
           end if
     end subroutine dqawo

     subroutine dqawoe(f,a,b,omega,integr,epsabs,epsrel,limit,icall,maxp1,res, &
                       abserr,neval,ier,last,alist,blist,rlist,elist,iord,nnlog, &
                       momcom,chebmo)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqawoe
!              automatic integrator, special-purpose,
!c             integrand with oscillatory cos or sin factor,
!c             clenshaw-curtis method, (end point) singularities,
!c             extrapolation, globally adaptive
!              the routine calculates an approximation result to a given
!c             definite integral
!c             i = integral of f(x)*w(x) over (a,b)
!c             where w(x) = cos(omega*x) or w(x)=sin(omega*x),
!c             hopefully satisfying following claim for accuracy
!c             abs(i-result).le.max(epsabs,epsrel*abs(i)).
           use mod_machine_prec, only : d1mach
           interface
               function f(x) result(v)
                 real(kind=dp),  intent(in) :: x
                 real(kind=dp) :: v
               end function f
           end interface
           real(kind=dp),                             intent(in)    :: a
           real(kind=dp),                             intent(in)    :: b
           real(kind=dp),                             intent(in)    :: omega
           integer(kind=int4),                        intent(in)    :: integr
           real(kind=dp),                             intent(in)    :: epsabs
           real(kind=dp),                             intent(in)    :: epsrel
           integer(kind=int4),                        intent(in)    :: limit
           integer(kind=int4),                        intent(in)    :: icall
           integer(kind=int4),                        intent(in)    :: maxp1
           real(kind=dp),                             intent(out)   :: res
           real(kind=dp),                             intent(out)   :: abserr
           integer(kind=int4),                        intent(out)   :: neval
           integer(kind=int4),                        intent(out)   :: ier
           real(kind=dp),      dimension(limit),      intent(inout) :: alist
           real(kind=dp),      dimension(limit),      intent(inout) :: blist
           real(kind=dp),      dimension(limit),      intent(inout) :: rlist
           real(kind=dp),      dimension(limit),      intent(inout) :: elist
           integer(kind=int4), dimension(limit),      intent(inout) :: iord
           integer(kind=int4), dimension(limit),      intent(inout) :: nnlog
           integer(kind=int4),                        intent(inout) :: momcom
           real(kind=dp),      dimension(maxp1,25),   intent(inout) :: chebmo
           ! LOcals
!DIR$      ATTRIBUTES ALIGN : 64 :: rlist2
           real(kind=dp), automatic, dimension(52) :: rlist2
           real(kind=dp), automatic, dimension(3)  :: res3la
           real(kind=dp),  automatic ::  abseps,area,area1,area12,area2,a1,a2,b,b1,b2, &
                            correc,dabs,defab1,defab2,defabs,domega,dres, &
                            epmach,erlarg,erlast,errbnd,errmax,error1,    &
                            error12,error2,errsum,ertest,oflow,reseps,    &
                            small,uflow,width
           integer(kind=int4),automatic  :: id, ierro,iroff1,iroff2,iroff3,jupbnd,k,ksg, &
                ktmin,maxerr,nev,nres,nrmax,nrmom,numrl2
           logical(kind=int4), automatic :: extrap,noext,extall
           ! Exec code .....
           epmach = d1mach(4)
           ier    = 0
           neval  = 0
           last   = 0
           res    = 0.0e+00_dp
           abserr = 0.0e+00_dp
           alist(1) = a
           blist(1) = b
           rlist(1) = 0.0e+00_dp
           elist(1) = 0.0e+00_dp
           iord(1)  = 0
           nnlog(1) = 0
           if((integr.ne.1.and.integr.ne.2).or.(epsabs.le.0.0d+00.and.     &
               epsrel.lt.DMAX1(0.5d+02*epmach,0.5d-28)).or.icall.lt.1.or.  &
               maxp1.lt.1) ier = 6
           if(ier == 6) goto 999
           domega = ABS(omega)
           nrmom  = 0
           if(icall.gt.1) goto 5
           momcom = 0
5          call DQC25F(f,a,b,domega,integr,nrmom,maxp1,0,result,abserr,   &
                neval,defabs,resabs,momcom,chebmo)
           dres = ABS(res)
           errbnd = MAX(epsabs,epsrel*dres)
           rlist(1) = res
           elist(1) = abserr
           iord(1) = 1
           if(abserr.le.0.1d+03*epmach*defabs.and.abserr.gt.errbnd) ier = 2
           if(limit.eq.1) ier = 1
           if(ier.ne.0.or.abserr.le.errbnd) go to 200
           uflow = d1mach(1)
           oflow = d1mach(2)
           errmax = abserr
           maxerr = 1
           area = res
           errsum = abserr
           abserr = oflow
           nrmax = 1
           extrap = .false.
           noext = .false.
           ierro = 0
           iroff1 = 0
           iroff2 = 0
           iroff3 = 0
           ktmin = 0
           small = ABS(b-a)*0.75_dp
           nres = 0
           numrl2 = 0
           extall = .false.
           if(0.5e+00_dp*ABS(b-a)*domega.gt.0.2d+01) go to 10
           numrl2 = 1
           extall = .true.
           rlist2(1) = res
10         if(0.25_dp*ABS(b-a)*domega.le.0.2d+01) extall = .true.
           ksgn = -1
           if(dres.ge.(0.1d+01-0.5d+02*epmach)*defabs) ksgn = 1
           do 140 last = 2,limit
!c
!c           bisect the subinterval with the nrmax-th largest
!c           error estimate.
!c
                     nrmom = nnlog(maxerr)+1
                     a1 = alist(maxerr)
                     b1 = 0.5d+00*(alist(maxerr)+blist(maxerr))
                     a2 = b1
                     b2 = blist(maxerr)
                     erlast = errmax
                     call DQC25F(f,a1,b1,domega,integr,nrmom,maxp1,0,  &
                                 area1,error1,nev,resabs,defab1,momcom,chebmo)
                     neval = neval+nev
                     call DQC25F(f,a2,b2,domega,integr,nrmom,maxp1,1,  &
                                 area2,error2,nev,resabs,defab2,momcom,chebmo)
                     neval = neval+nev
!c
!c           improve previous approximations to integral
!c           and error and test for accuracy.
!c
                     area12 = area1+area2
                     erro12 = error1+error2
                     errsum = errsum+erro12-errmax
                     area = area+area12-rlist(maxerr)
                     if(defab1.eq.error1.or.defab2.eq.error2) go to 25
                     if(DABS(rlist(maxerr)-area12).gt.0.1d-04*DABS(area12)   &
                                          .or.erro12.lt.0.99d+00*errmax) go to 20
                     if(extrap) iroff2 = iroff2+1
                     if(.not.extrap) iroff1 = iroff1+1
20                   if(last.gt.10.and.erro12.gt.errmax) iroff3 = iroff3+1
25                   rlist(maxerr) = area1
                     rlist(last) = area2
                     nnlog(maxerr) = nrmom
                     nnlog(last) = nrmom
                     errbnd = MAX(epsabs,epsrel*DABS(area))
!c
!c           test for roundoff error and eventually set error flag.
!c
                     if(iroff1+iroff2.ge.10.or.iroff3.ge.20) ier = 2
                     if(iroff2.ge.5) ierro = 3
!c
!c           set error flag in the case that the number of
!c           subintervals equals limit.
!c
                     if(last.eq.limit) ier = 1
!c
!c           set error flag in the case of bad integrand behaviour
!c           at a point of the integration range.
!c
                     if(DMAX1(DABS(a1),DABS(b2)).le.(0.1d+01+0.1d+03*epmach) *  &
                       (DABS(a2)+0.1d+04*uflow)) ier = 4
!c
!c           append the newly-created intervals to the list.
!c
                     if(error2.gt.error1) go to 30
                     alist(last) = a2
                     blist(maxerr) = b1
                     blist(last) = b2
                     elist(maxerr) = error1
                     elist(last) = error2
                     go to 40
30                   alist(maxerr) = a2
                     alist(last) = a1
                     blist(last) = b1
                     rlist(maxerr) = area2
                     rlist(last) = area1
                     elist(maxerr) = error2
                     elist(last) = error1
!c
!c           call subroutine dqpsrt to maintain the descending ordering
!c           in the list of error estimates and select the subinterval
!c           with nrmax-th largest error estimate (to bisected next).
!c
40                   call DQPSRT(limit,last,maxerr,errmax,elist,iord,nrmax)
!c ***jump out of do-loop
                     if(errsum.le.errbnd) go to 170
                     if(ier.ne.0) go to 150
                     if(last.eq.2.and.extall) go to 120
                     if(noext) go to 140
                     if(.not.extall) go to 50
                     erlarg = erlarg-erlast
                     if(DABS(b1-a1).gt.small) erlarg = erlarg+erro12
                     if(extrap) go to 70
!c
!c           test whether the interval to be bisected next is the
!c           smallest interval.
!c
50                    width = DABS(blist(maxerr)-alist(maxerr))
                      if(width.gt.small) go to 140
                      if(extall) go to 60
!c
!c           test whether we can start with the extrapolation procedure
!c           (we do this if we integrate over the next interval with
!c           use of a gauss-kronrod rule - see subroutine dqc25f).
!c
                      small = small*0.5d+00
                      if(0.25d+00*width*domega.gt.0.2d+01) go to 140
                      extall = .true.
                      go to 130
60                    extrap = .true.
                      nrmax = 2
70                    if(ierro.eq.3.or.erlarg.le.ertest) go to 90
!c
!c           the smallest interval has the largest error.
!c           before bisecting decrease the sum of the errors over
!c           the larger intervals (erlarg) and perform extrapolation.
!c
                     jupbnd = last
                     if (last.gt.(limit/2+2)) jupbnd = limit+3-last
                     id = nrmax
                     do 80 k = id,jupbnd
                               maxerr = iord(nrmax)
                               errmax = elist(maxerr)
                               if(DABS(blist(maxerr)-alist(maxerr)).gt.small) go to 140
                                  nrmax = nrmax+1
80                   continue
!c
!c           perform extrapolation.
!c
90                   numrl2 = numrl2+1
                     rlist2(numrl2) = area
                     if(numrl2.lt.3) go to 110
                     call DQELG(numrl2,rlist2,reseps,abseps,res3la,nres)
                     ktmin = ktmin+1
                     if(ktmin.gt.5.and.abserr.lt.0.1d-02*errsum) ier = 5
                     if(abseps.ge.abserr) go to 100
                     ktmin = 0
                     abserr = abseps
                     res    = reseps
                     correc = erlarg
                     ertest = MAX(epsabs,epsrel*DABS(reseps))
!c ***jump out of do-loop
                     if(abserr.le.ertest) go to 150
!c
!c           prepare bisection of the smallest interval.
!c
100                  if(numrl2.eq.1) noext = .true.
                     if(ier.eq.5) go to 150
110                  maxerr = iord(1)
                     errmax = elist(maxerr)
                     nrmax = 1
                     extrap = .false.
                     small = small*0.5d+00
                     erlarg = errsum
                     go to 140
120                  small = small*0.5d+00
                     numrl2 = numrl2+1
                     rlist2(numrl2) = area
130                  ertest = errbnd
                     erlarg = errsum
140        continue
!c
!c           set the final result.
!c           ---------------------
!c
  150      if(abserr.eq.oflow.or.nres.eq.0) go to 170
           if(ier+ierro.eq.0) go to 165
           if(ierro.eq.3) abserr = abserr+correc
           if(ier.eq.0) ier = 3
           if(result.ne.0.0d+00.and.area.ne.0.0d+00) go to 160
           if(abserr.gt.errsum) go to 170
           if(area.eq.0.0d+00) go to 190
           go to 165
160        if(abserr/DABS(res).gt.errsum/DABS(area)) go to 170
!c
!c           test on divergence.
!c
165        if(ksgn.eq.(-1).and.MAX(ABS(res),ABS(area)).le.  &
               defabs*0.1d-01) go to 190
           if(0.1d-01.gt.(res/area).or.(res/area).gt.0.1d+03 &
                 .or.errsum.ge.DABS(area)) ier = 6
           go to 190
!c
!c           compute global integral sum.
!c
170        res = 0.0d+00
           do 180 k=1,last
                   res = res+rlist(k)
180        continue
           abserr = errsum
190        if (ier.gt.2) ier=ier-1
200        if (integr.eq.2.and.omega.lt.0.0d+00) res = -res
           
     end subroutine dqawoe

     subroutine dqc25f(f,a,b,omega,integr,nrmom,maxp1,ksave,res,abserr, &
                       neval,resabs,resasc,momcom,chebmo)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqc25f
!              integration rules for functions with cos or sin
!c             factor, clenshaw-curtis, gauss-kronrod
!             to compute the integral i=integral of f(x) over (a,b)
!c            where w(x) = cos(omega*x) or w(x)=sin(omega*x) and to
!c            compute j = integral of abs(f) over (a,b). for small value
!c            of omega or small intervals (a,b) the 15-point gauss-kronro
!c            rule is used. otherwise a generalized clenshaw-curtis
       !c            method is used.
           use mod_machine_prec, only : d1mach
           interface
              function f(x) result(v)
                real(kind=dp), intent(in) :: x
                real(kind=dp) :: v
              end function f
           end interface
           real(kind=dp),                      intent(in) :: a
           real(kind=dp),                      intent(in) :: b
           real(kind=dp),                      intent(in) :: omega
           integer(kind=int4),                 intent(in) :: integr
           integer(kind=int4),                 intent(in) :: nrmom
           integer(kind=int4),                 intent(in) :: maxp1
           integer(kind=int4),                 intent(in) :: ksave
           real(kind=dp),                      intent(out) :: res
           real(kind=dp),                      intent(out) :: abserr
           integer(kind=int4),                 intent(out) :: neval
           real(kind=dp),                      intent(out) :: resabs
           real(kind=dp),                      intent(out) :: resasc
           integer(kind=int4),                 intent(inout) :: momcom
           real(kind=dp), dimension(maxp1,25), intent(inout) :: chebmo
           ! LOcals
           real(kind=dp), dimension(11), parameter ::  x = [ 0.991444861373810411144557526928563_dp,    &
                                                             0.965925826289068286749743199728897_dp,    &
                                                             0.923879532511286756128183189396788_dp,    &
                                                             0.866025403784438646763723170752936_dp,    &
                                                             0.793353340291235164579776961501299_dp,    &
                                                             0.707106781186547524400844362104849_dp,    &
                                                             0.608761429008720639416097542898164_dp,    &
                                                             0.500000000000000000000000000000000_dp,    &
                                                             0.382683432365089771728459984030399_dp,    &
                                                             0.258819045102520762348898837624048_dp,    &
                                                             0.130526192220051591548406227895489  ]
           real(kind=dp), automatic, dimension(13) ::  cheb12
           real(kind=dp), automatic, dimension(25) ::  cheb24
           real(kind=dp), automatic, dimension(25) ::  d,d1,d2,fval
           real(kind=dp), automatic, dimension(28) ::  v
           real(kind=dp), automatic :: ac,an,an2,as,asap,ass,centr,conc,cons, &
                                       cospar,estc,ests,hlgth,ovflow,parint,  &
                                       par2,par22,p2,p3,p4,resc12,resc24,ress24, &
                                       sinpar
           integer(kind=int4), automatic :: i,iers,isym,j,k,ksym,m,noequ,noeq1
           external dqwgtf
!                  list of major variables
!c           -----------------------
!c
!c           centr  - mid point of the integration interval
!c           hlgth  - half-length of the integration interval
!c           fval   - value of the function f at the points
!c                    (b-a)*0.5*cos(k*pi/12) + (b+a)*0.5, k = 0, ..., 24
!c           cheb12 - coefficients of the chebyshev series expansion
!c                    of degree 12, for the function f, in the
!c                    interval (a,b)
!c           cheb24 - coefficients of the chebyshev series expansion
!c                    of degree 24, for the function f, in the
!c                    interval (a,b)
!c           resc12 - approximation to the integral of
!c                    cos(0.5*(b-a)*omega*x)*f(0.5*(b-a)*x+0.5*(b+a))
!c                    over (-1,+1), using the chebyshev series
!c                    expansion of degree 12
!c           resc24 - approximation to the same integral, using the
!c                    chebyshev series expansion of degree 24
!1c           ress12 - the analogue of resc12 for the sine
!c           ress24 - the analogue of resc24 for the sine
!c
!c
!c           machine dependent constant
!c           --------------------------
!c
!c           oflow is the largest positive magnitude.
           oflow = d1mach
           centr = 0.5e+00_dp*(b+a)
           hlgth = 0.5e+00_dp*(b-a)
           parint = omega*hlgth
!c
!c           compute the integral using the 15-point gauss-kronrod
!c           formula if the value of the parameter in the integrand
!c           is small.
!c
           if(ABS(parint).gt.0.2d+01) go to 10
           call dqk15w(f,dqwgtf,omega,p2,p3,p4,integr,a,b,res,abserr,resabs,resasc)
       
           neval = 15
           go to 170
!c
!c           compute the integral using the generalized clenshaw-
!c           curtis method.
!c
10         conc = hlgth*COS(centr*omega)
           cons = hlgth*SIN(centr*omega)
           resasc = oflow
           neval = 25
!c
!c           check whether the chebyshev moments for this interval
!c           have already been computed.
!c
           if(nrmom.lt.momcom.or.ksave.eq.1) go to 120
!                    compute a new set of chebyshev moments.

           m = momcom+1
           par2 = parint*parint
           par22 = par2+0.2d+01
           sinpar = SIN(parint)
           cospar = COS(parint)
!c
!c           compute the chebyshev moments with respect to cosine.
!c
           v(1) = 0.2d+01*sinpar/parint
           v(2) = (0.8d+01*cospar+(par2+par2-0.8d+01)*sinpar/parint)/par2
           v(3) = (0.32d+02*(par2-0.12d+02)*cospar+(0.2d+01*  &
                  ((par2-0.80d+02)*par2+0.192d+03)*sinpar)/parint)/(par2*par2)
           ac = 0.8d+01*cospar
           as = 0.24d+02*parint*sinpar
           if(DABS(parint).gt.0.24d+02) go to 30
!c
!c           compute the chebyshev moments as the solutions of a
!c           boundary value problem with 1 initial value (v(3)) and 1
!c           end value (computed using an asymptotic formula).
           !c
           noequ = 25
           noeq1 = noequ-1
           an = 0.6d+01
           do 20 k = 1,noeq1
                 an2 = an*an
                 d(k) = -0.2d+01*(an2-0.4d+01)*(par22-an2-an2)
                 d2(k) = (an-0.1d+01)*(an-0.2d+01)*par2
                 d1(k+1) = (an+0.3d+01)*(an+0.4d+01)*par2
                 v(k+3) = as-(an2-0.4d+01)*ac
                 an = an+0.2d+01
       20  continue
           an2 = an*an
           d(noequ) = -0.2d+01*(an2-0.4d+01)*(par22-an2-an2)
           v(noequ+3) = as-(an2-0.4d+01)*ac
           v(4) = v(4)-0.56d+02*par2*v(3)
           ass = parint*sinpar
           asap = (((((0.210d+03*par2-0.1d+01)*cospar-(0.105d+03*par2       &
                     -0.63d+02)*ass)/an2-(0.1d+01-0.15d+02*par2)*cospar    &
                     +0.15d+02*ass)/an2-cospar+0.3d+01*ass)/an2-cospar)/an2
           v(noequ+3) = v(noequ+3)-0.2d+01*asap*par2*(an-0.1d+01)*(an-0.2d+01)
      
!1c
!c           solve the tridiagonal system by means of gaussian
!c           elimination with partial pivoting.
!c
!c***        call to dgtsl must be replaced by call to
!c***        double precision version of linpack routine sgtsl
!c
           call dgtsl(noequ,d1,d,d2,v(4),iers)
           go to 50
            compute the chebyshev moments by means of forward
!c           recursion.
!c
30         an = 0.4d+01
           do 40 i = 4,13
           an2 = an*an
           v(i) = ((an2-0.4d+01)*(0.2d+01*(par22-an2-an2)*v(i-1)-ac)  &
           + as-par2*(an+0.1d+01)*(an+0.2d+01)*v(i-2))/               &
           (par2*(an-0.1d+01)*(an-0.2d+01))
           an = an+0.2d+01
   40      continue
   50      do 60 j = 1,13
                 chebmo(m,2*j-1) = v(j)
   60      continue
!c
!c           compute the chebyshev moments with respect to sine.
!c
           v(1) = 0.2d+01*(sinpar-parint*cospar)/par2
           v(2) = (0.18d+02-0.48d+02/par2)*sinpar/par2  &
           + (-0.2d+01+0.48d+02/par2)*cospar/parint
           ac = -0.24d+02*parint*cospar
           as = -0.8d+01*sinpar
           if(ABS(parint).gt.0.24d+02) go to 80
!c
!c           compute the chebyshev moments as the solutions of a boundary
!c           value problem with 1 initial value (v(2)) and 1 end value
!c           (computed using an asymptotic formula).
!c
           an = 0.5d+01
           do 70 k = 1,noeq1
                   an2 = an*an
                   d(k) = -0.2d+01*(an2-0.4d+01)*(par22-an2-an2)
                   d2(k) = (an-0.1d+01)*(an-0.2d+01)*par2
                   d1(k+1) = (an+0.3d+01)*(an+0.4d+01)*par2
                   v(k+2) = ac+(an2-0.4d+01)*as
                   an = an+0.2d+01
   70      continue
           an2 = an*an
           d(noequ) = -0.2d+01*(an2-0.4d+01)*(par22-an2-an2)
           v(noequ+2) = ac+(an2-0.4d+01)*as
           v(3) = v(3)-0.42d+02*par2*v(2)
           ass = parint*cospar
           asap = (((((0.105d+03*par2-0.63d+02)*ass+(0.210d+03*par2       &
                  -0.1d+01)*sinpar)/an2+(0.15d+02*par2-0.1d+01)*sinpar-   &
                   0.15d+02*ass)/an2-0.3d+01*ass-sinpar)/an2-sinpar)/an2
           v(noequ+2) = v(noequ+2)-0.2d+01*asap*par2*(an-0.1d+01)         &
           *(an-0.2d+01)
!c
!c           solve the tridiagonal system by means of gaussian
!c           elimination with partial pivoting.
!c
!c***        call to dgtsl must be replaced by call to
!c***        double precision version of linpack routine sgtsl
!c
           call dgtsl(noequ,d1,d,d2,v(3),iers)
           go to 100
!c
!c           compute the chebyshev moments by means of forward recursion.
!c
   80      an = 0.3d+01
           do 90 i = 3,12
                   an2 = an*an
                   v(i) = ((an2-0.4d+01)*(0.2d+01*(par22-an2-an2)*v(i-1)+as)   &
                          +ac-par2*(an+0.1d+01)*(an+0.2d+01)*v(i-2))           &
                          /(par2*(an-0.1d+01)*(an-0.2d+01))                                    
                   an = an+0.2d+01
   90      continue
  100      do 110 j = 1,12
                   chebmo(m,2*j) = v(j)
  110      continue
  120      if (nrmom.lt.momcom) m = nrmom+1
           if (momcom.lt.(maxp1-1).and.nrmom.ge.momcom) momcom = momcom+1
!c
!c           compute the coefficients of the chebyshev expansions
!c           of degrees 12 and 24 of the function f.
!c
           fval(1) = 0.5d+00*f(centr+hlgth)
           fval(13) = f(centr)
           fval(25) = 0.5d+00*f(centr-hlgth)
           do 130 i = 2,12
                    isym = 26-i
                    fval(i) = f(hlgth*x(i-1)+centr)
                    fval(isym) = f(centr-hlgth*x(i-1))
  130      continue
           call DQCHEB(x,fval,cheb12,cheb24)
!c
!c           compute the integral and error estimates.
!c
           resc12 = cheb12(13)*chebmo(m,13)
           ress12 = 0.0d+00
           k = 11
           do 140 j = 1,6
                   resc12 = resc12+cheb12(k)*chebmo(m,k)
                   ress12 = ress12+cheb12(k+1)*chebmo(m,k+1)
                   k = k-2
  140      continue
           resc24 = cheb24(25)*chebmo(m,25)
           ress24 = 0.0d+00
           resabs = ABS(cheb24(25))
           k = 23
           do 150 j = 1,12
                 resc24 = resc24+cheb24(k)*chebmo(m,k)
                 ress24 = ress24+cheb24(k+1)*chebmo(m,k+1)
                 resabs = ABS(cheb24(k))+DABS(cheb24(k+1))
                 k = k-2
  150      continue
           estc = ABS(resc24-resc12)
           ests = ABS(ress24-ress12)
           resabs = resabs*ABS(hlgth)
           if(integr.eq.2) go to 160
           res = conc*resc24-cons*ress24
           abserr = ABS(conc*estc)+ABS(cons*ests)
           go to 170
  160      res = conc*ress24+cons*resc24
           abserr = DABS(conc*ests)+DABS(cons*estc)
            
     end subroutine dqc25f


     subroutine dqk15w(f,w,p1,p2,p3,p4,kp,a,b,res,abserr,resabs,resasc)
       !DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqk15w
!        to compute i = integral of f*w over (a,b), with error
       !c                           estimate
       !c                       j = integral of abs(f*w) over (a,b)
           use mod_machine_prec, only : d1mach
           interface
              function f(x) result(v)
                real(kind=dp), intent(in) :: x
                real(kind=dp) :: v
              end function f
           end interface
           interface
              function w(x,omega,p2,p3,p4,integr) result(v)
                real(kind=dp), intent(in) :: x
                real(kind=dp), intent(in) :: omega
                real(kind=dp), intent(in) :: p2
                real(kind=dp), intent(in) :: p3
                real(kind=dp), intent(in) :: p4
                integer(kind=int4), intent(in) :: integr
                real(kind=dp), intent(in) :: integr
              end function w
           end interface
           real(kind=dp),      intent(in) :: p1
           real(kind=dp),      intent(in) :: p2
           real(kind=dp),      intent(in) :: p3
           real(kind=dp),      intent(in) :: p4
           integer(kind=dint4), intent(in) :: kp
           real(kind=dp),       intent(in) :: a
           real(kind=dp),       intent(in) :: b
           real(kind=dp),       intent(inout) :: res
           real(kind=dp),       intent(inout) :: abserr
           real(kind=dp),       intent(inout) :: resabs
           real(kind=dp),       intent(inout) :: resasc
           !Locals
           real(kind=dp), dimension(8), parameter :: xgk = [0.9914553711208126e+00_dp,0.9491079123427585e+00_dp, &
                                                            0.8648644233597691e+00_dp,0.7415311855993944e+00_dp, &
                                                            0.5860872354676911e+00_dp,0.4058451513773972e+00_dp, &
                                                            0.2077849550078985e+00_dp,0.0000000000000000e+00_dp]
           real(kind=dp), dimension(8), parameter :: wgk = [0.2293532201052922e-01_dp,0.6309209262997855e-01_dp,&
                                                            0.1047900103222502e+00_dp,0.1406532597155259e+00_dp,&
                                                            0.1690047266392679e+00_dp,0.1903505780647854e+00_dp,&
                                                            0.2044329400752989e+00_dp,0.2094821410847278e+00_dp]
           real(kind=dp), dimension(4), parameter :: wg  = [ 0.1294849661688697e+00_dp,0.2797053914892767e+00_dp,&
                                                             0.3818300505051889e+00_dp,0.4179591836734694e+00_dp]
           real(kind=dp), automatic, dimension(7) :: fv1,fv2
           real(kind=dp), automatic :: absc,absc1,absc2,centr,dhlgth,epmach,fc, &
                                       fsum,fval1,fval2,hlgth,resg,resk,reskh,uflow
           ! Exec code .....
           epmach = d1mach(4)
           uflow  = d1mach(1)
           centr = 0.5e+00_dp*(a+b)
           hlgth = 0.5e+00_dp*(b-a)
           dhlgth = ABS(hlgth)
!c
!c           compute the 15-point kronrod approximation to the
!c           integral, and estimate the error.
!c
           fc = f(centr)*w(centr,p1,p2,p3,p4,kp)
           resg = wg(4)*fc
           resk = wgk(8)*fc
           resabs = ABS(resk)
           fv1 = 0.0_dp
           fv2 = 0.0_dp
           do 10 j=1,3
                 jtw = j*2
                 absc = hlgth*xgk(jtw)
                 absc1 = centr-absc
                 absc2 = centr+absc
                 fval1 = f(absc1)*w(absc1,p1,p2,p3,p4,kp)
                 fval2 = f(absc2)*w(absc2,p1,p2,p3,p4,kp)
                 fv1(jtw) = fval1
                 fv2(jtw) = fval2
                 fsum = fval1+fval2
                 resg = resg+wg(j)*fsum
                 resk = resk+wgk(jtw)*fsum
                 resabs = resabs+wgk(jtw)*(ABS(fval1)+ABS(fval2))
   10      continue
           do 15 j=1,4
                 jtwm1 = j*2-1
                 absc = hlgth*xgk(jtwm1)
                 absc1 = centr-absc
                 absc2 = centr+absc
                 fval1 = f(absc1)*w(absc1,p1,p2,p3,p4,kp)
                 fval2 = f(absc2)*w(absc2,p1,p2,p3,p4,kp)
                 fv1(jtwm1) = fval1
                 fv2(jtwm1) = fval2
                 fsum = fval1+fval2
                 resk = resk+wgk(jtwm1)*fsum
                 resabs = resabs+wgk(jtwm1)*(ABS(fval1)+ABS(fval2))
     15    continue
           reskh = resk*0.5e+00_dp
           resasc = wgk(8)*DABS(fc-reskh)
           do 20 j=1,7
                resasc = resasc+wgk(j)*(ABS(fv1(j)-reskh)+ABS(fv2(j)-reskh))
   20       continue
            res = resk*hlgth
            resabs = resabs*dhlgth
            resasc = resasc*dhlgth
            abserr = ABS((resk-resg)*hlgth) 
            if(resasc.ne.0.0e+00_dp.and.abserr.ne.0.0e+00_dp)  &
                abserr = resasc*MIN(0.1e+01_dp,(0.2e+03_dp*abserr/resasc)**1.5e+00_dp)
            if(resabs.gt.uflow/(0.5e+02_dp*epmach)) abserr = MAX((epmach*0.5e+02_dp)*resabs,abserr)
      
     end subroutine dqk15w

     function dqwgtf(x,omega,p2,p3,p4,integr) result(res)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqwgtf
           real(kind=dp),      intent(in) :: x
           real(kind=dp),      intent(in) :: omega
           real(kind=dp),      intent(in) :: p2
           real(kind=dp),      intent(in) :: p3
           real(kind=dp),      intent(in) :: p4
           integer(kind=int4), intent(in) :: integr
           ! Locals/return
           real(kind=dp) :: res
           real(kind=dp), automatic :: omx
           ! Exec code ....
           omx = omega*x
           if(10 == integr) then
              res = cos(omx)
           else if(20 == integr) then
              res = sin(omx)
           end if
     end function dqwgtf

     subroutine dgtsl(n,c,d,e,b,info)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dgtsl
       integer(kind=int4),          intent(in) ::  n
       real(kind=dp), dimension(n), intent(in) :: c
       real(kind=dp), dimension(n), intent(in) :: d
       real(kind=dp), dimension(n), intent(in) :: e
       real(kind=dp), dimension(n), intent(inout) :: b
       integer(kind=int4),          intent(inout) :: info
       
!c
!c     dgtsl given a general tridiagonal matrix and a right hand
!c     side will find the solution.
!c
!c     on entry
!c
!c        n       integer
!c                is the order of the tridiagonal matrix.
!c
!c        c       double precision(n)
!c                is the subdiagonal of the tridiagonal matrix.
!c                c(2) through c(n) should contain the subdiagonal.
!c                on output c is destroyed.
!c
!c        d       double precision(n)
!c                is the diagonal of the tridiagonal matrix.
!c                on output d is destroyed.
!c
!c        e       double precision(n)
!c                is the superdiagonal of the tridiagonal matrix.
!c                e(1) through e(n-1) should contain the superdiagonal.
!c                on output e is destroyed.
!c
!c        b       double precision(n)
!c                is the right hand side vector.
!c
!c     on return
!c
!c        b       is the solution vector.
!c
!c        info    integer
!c                = 0 normal value.
!c                = k if the k-th element of the diagonal becomes
!c                    exactly zero.  the subroutine returns when
!c                    this is detected.
!c
!c     linpack. this version dated 08/14/78 .
!c     jack dongarra, argonne national laboratory.
!c
!c     no externals
!c     fortran dabs
!c
!c     internal variables
       !c
      
           integer(kind=int4), automatic ::  k,kb,kp1,nm1,nm2
           real(kind=dp), automatic ::       t
!c     begin block permitting ...exits to 100

           info = 0
           c(1) = d(1)
           nm1 = n - 1
           if (nm1 .lt. 1) go to 40
              d(1) = e(1)
              e(1) = 0.0_dp
              e(n) = 0.0_dp

            do 30 k = 1, nm1
               kp1 = k + 1

!c              find the largest of the two rowsc
               if (abs(c(kp1)) .lt. abs(c(k))) go to 10
!c
!c                 interchange row
!c
                  t = c(kp1)
                  c(kp1) = c(k)
                  c(k) = t
                  t = d(kp1)
                  d(kp1) = d(k)
                  d(k) = t
                  t = e(kp1)
                  e(kp1) = e(k)
                  e(k) = t
                  t = b(kp1)
                  b(kp1) = b(k)
                  b(k) = t
   10          continue
!c
!c              zero elements
!c
               if (c(k) .ne. 0.0_dp) go to 20
                  info = k
!c     ............exit
                  go to 100
   20          continue
               t = -c(kp1)/c(k)
               c(kp1) = d(kp1) + t*d(k)
               d(kp1) = e(kp1) + t*e(k)
               e(kp1) = 0.0_dp
               b(kp1) = b(kp1) + t*b(k)
   30       continue
   40    continue
         if (c(n) .ne. 0.0_dp) go to 50
            info = n
         go to 90
   50    continue
!c
!c           back solve
!c
            nm2 = n - 2
            b(n) = b(n)/c(n)
            if (n .eq. 1) go to 80
               b(nm1) = (b(nm1) - d(nm1)*b(n))/c(nm1)
               if (nm2 .lt. 1) go to 70
               do 60 kb = 1, nm2
                  k = nm2 - kb + 1
                  b(k) = (b(k) - d(k)*b(k+1) - e(k)*b(k+2))/c(k)
   60          continue
   70          continue
   80       continue
   90    continue
100    continue
                  
     end subroutine dgtsl

     subroutine dqcheb(x,fval,cheb12,cheb24)
!DIR$ ATTRIBUTES ALIGN:32 :: dqcheb
           real(kind=dp), dimension(11), intent(in) :: x
           real(kind=dp), dimension(25), intent(in) :: fval
           real(kind=dp), dimension(13), intent(inout) :: cheb12
           real(kind=dp), dimension(25), intent(inout) :: cheb24
           ! LOcals
           real(kind=dp), automatic, dimension(12) :: v
           real(kind=dp), automatic :: alam,alam1,alam2,part1,part2
           integer(kind=int4), automatic :: i,j
           ! Exec code ......
           do 10 i=1,12
                 j = 26-i
                 v(i) = fval(i)-fval(j)
                 fval(i) = fval(i)+fval(j)
   10      continue
           alam1 = v(1)-v(9)
           alam2 = x(6)*(v(3)-v(7)-v(11))
           cheb12(4) = alam1+alam2
           cheb12(10) = alam1-alam2
           alam1 = v(2)-v(8)-v(10)
           alam2 = v(4)-v(6)-v(12)
           alam = x(3)*alam1+x(9)*alam2
           cheb24(4) = cheb12(4)+alam
           cheb24(22) = cheb12(4)-alam
           alam = x(9)*alam1-x(3)*alam2
           cheb24(10) = cheb12(10)+alam
           cheb24(16) = cheb12(10)-alam
           part1 = x(4)*v(5)
           part2 = x(8)*v(9)
           part3 = x(6)*v(7)
           alam1 = v(1)+part1+part2
           alam2 = x(2)*v(3)+part3+x(10)*v(11)
           cheb12(2) = alam1+alam2
           cheb12(12) = alam1-alam2
           alam = x(1)*v(2)+x(3)*v(4)+x(5)*v(6)+x(7)*v(8) &
                 +x(9)*v(10)+x(11)*v(12)
           cheb24(2) = cheb12(2)+alam
           cheb24(24) = cheb12(2)-alam
           alam = x(11)*v(2)-x(9)*v(4)+x(7)*v(6)-x(5)*v(8) &
                 +x(3)*v(10)-x(1)*v(12)
           cheb24(12) = cheb12(12)+alam
           cheb24(14) = cheb12(12)-alam
           alam1 = v(1)-part1+part2
           alam2 = x(10)*v(3)-part3+x(2)*v(11)
           cheb12(6) = alam1+alam2
           cheb12(8) = alam1-alam2
           alam = x(5)*v(2)-x(9)*v(4)-x(1)*v(6) &
                 -x(11)*v(8)+x(3)*v(10)+x(7)*v(12)
           cheb24(6) = cheb12(6)+alam
           cheb24(20) = cheb12(6)-alam
           alam = x(7)*v(2)-x(3)*v(4)-x(11)*v(6)+x(1)*v(8) &
                 -x(9)*v(10)-x(5)*v(12)
           cheb24(8) = cheb12(8)+alam
           cheb24(18) = cheb12(8)-alam
           do 20 i=1,6
                 j = 14-i
                 v(i) = fval(i)-fval(j)
                 fval(i) = fval(i)+fval(j)
   20      continue
           alam1 = v(1)+x(8)*v(5)
           alam2 = x(4)*v(3)
           cheb12(3) = alam1+alam2
           cheb12(11) = alam1-alam2
           cheb12(7) = v(1)-v(5)
           alam = x(2)*v(2)+x(6)*v(4)+x(10)*v(6)
           cheb24(3) = cheb12(3)+alam
           cheb24(23) = cheb12(3)-alam
           alam = x(6)*(v(2)-v(4)-v(6))
           cheb24(7) = cheb12(7)+alam
           cheb24(19) = cheb12(7)-alam
           alam = x(10)*v(2)-x(6)*v(4)+x(2)*v(6)
           cheb24(11) = cheb12(11)+alam
           cheb24(15) = cheb12(11)-alam
           do 30 i=1,3
                 j = 8-i
                 v(i) = fval(i)-fval(j)
                 fval(i) = fval(i)+fval(j)
30         continue
           cheb12(5) = v(1)+x(8)*v(3)
           cheb12(9) = fval(1)-x(8)*fval(3)
           alam = x(4)*v(2)
           cheb24(5) = cheb12(5)+alam
           cheb24(21) = cheb12(5)-alam
           alam = x(8)*fval(2)-fval(4)
           cheb24(9) = cheb12(9)+alam
           cheb24(17) = cheb12(9)-alam
           cheb12(1) = fval(1)+fval(3)
           alam = fval(2)+fval(4)
           cheb24(1) = cheb12(1)+alam
           cheb24(25) = cheb12(1)-alam
           cheb12(13) = v(1)-v(3)
           cheb24(13) = cheb12(13)
           alam = 0.1e+01_dp/0.6e+01_dp
           do 40 i=2,12
                   cheb12(i) = cheb12(i)*alam
   40      continue
           alam = 0.5e+00_dp*alam
           cheb12(1) = cheb12(1)*alam
           cheb12(13) = cheb12(13)*alam
           do 50 i=2,24
                 cheb24(i) = cheb24(i)*alam
   50      continue
           cheb24(1) = 0.5e+00_dp*alam*cheb24(1)
           cheb24(25) = 0.5e+00_dp*alam*cheb24(25)      
     end subroutine dqcheb

     subroutine dqpsrt(limit,last,maxerr,ermax,elist,iord,nrmax)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqpsrt
           integer(kind=int4),     intent(out)              :: limit
           integer(kind=int4),     intent(out)              :: last
           integer(kind=int4),     intent(out)              :: maxerr
           real(kind=dp),          intent(out)              :: ermax
           real(kind=dp),      dimension(last), intent(out) :: elist
           integer(kind=int4), dimension(last), intent(out) :: iord
           integer(kind=int4),     intent(out)              :: nrmax
           ! LOcals
           real(kind=dp), automatic :: errmax,errmin
           integer(kind=int4), automatic :: i,ibeg,ido,isucc.j,jbnd,jupbn,k
           ! Exec cdoe .....
           if(last.gt.2) go to 10
           iord(1) = 1
           iord(2) = 2
           go to 90
!c
!c           this part of the routine is only executed if, due to a
!c           difficult integrand, subdivision increased the error
!c           estimate. in the normal case the insert procedure should
!c           start after the nrmax-th largest error estimate.
!c
   10      errmax = elist(maxerr)
           if(nrmax.eq.1) go to 30
           ido = nrmax-1
           do 20 i = 1,ido
                  isucc = iord(nrmax-1)
!c ***jump out of do-loop
           if(errmax.le.elist(isucc)) go to 30
           iord(nrmax) = isucc
           nrmax = nrmax-1
   20      continue
!c
!c           compute the number of elements in the list to be maintained
!c           in descending order. this number depends on the number of
!c           subdivisions still allowed.
!c
   30      jupbn = last
           if(last.gt.(limit/2+2)) jupbn = limit+3-last
           errmin = elist(last)
!c
!c           insert errmax by traversing the list top-down,
!c           starting comparison from the element elist(iord(nrmax+1)).
!c
           jbnd = jupbn-1
           ibeg = nrmax+1
           if(ibeg.gt.jbnd) go to 50
           do 40 i=ibeg,jbnd
                 isucc = iord(i)
!c ***jump out of do-loop
                 if(errmax.ge.elist(isucc)) go to 60
                 iord(i-1) = isucc
   40      continue
   50      iord(jbnd) = maxerr
           iord(jupbn) = last
           go to 90
!c
!c           insert errmin by traversing the list bottom-up.
!c
   60      iord(i-1) = maxerr
           k = jbnd
           do 70 j=i,jbnd
                 isucc = iord(k)
!c ***jump out of do-loop
                 if(errmin.lt.elist(isucc)) go to 80
                 iord(k+1) = isucc
                 k = k-1
   70      continue
           iord(i) = last
           go to 90
   80      iord(k+1) = last
!c
!c           set maxerr and ermax.
!c
   90      maxerr = iord(nrmax)
           ermax = elist(maxerr)
     end subroutine dqpsrt

     subroutine dqelg(n,epstab,result,abserr,res3la,nres)
!DIR$ ATTRIBUTES CODE_ALIGN:32 :: dqelg
           use mod_machine_prec, only : d1mach
           integer(kind=int4),     intent(in) :: n
           !DIR$ ASSUME_ALIGNED epstab:32
           real(kind=dp), dimension(52), intent(inout) :: epstab
           real(kind=dp),                intent(inout) :: result
           real(kind=dp),                intent(out)   :: abserr
           real(kind=dp), dimension(3),  intent(inout) :: res3la
           integer(kind=int4),           intent(inout) :: nres
            ! Locals
           real(kind=dp), automatic :: delta1,delta2,delta3,d1mach,epmach,epsinf,error,err1,err2, &
            err3,e0,e1,e1abs,e2,e3,oflow,res,ss,tol1,tol2,tol3
           integer(kind=int4), automatic :: i,ib,ib2,ie,indx,k1,k2,k3,limexp,n,neweln,num
           ! Exec code ...
           epmach = d1mach(4)
           oflow = d1mach(2)
           nres = nres+1
           abserr = oflow
           res = epstab(n)
           if(n.lt.3) go to 100
           limexp = 50
           epstab(n+2) = epstab(n)
           newelm = (n-1)/2
           epstab(n) = oflow
           num = n
           k1 = n
           do 40 i = 1,newelm
                  k2 = k1-1
                  k3 = k1-2
                  res = epstab(k1+2)
                  e0 = epstab(k3)
                  e1 = epstab(k2)
                  e2 = res
                  e1abs = ABS(e1)
                  delta2 = e2-e1
                  err2 = ABS(delta2)
                  tol2 = MAX(DABS(e2),e1abs)*epmach
                  delta3 = e1-e0
                  err3 = ABS(delta3)
                  tol3 = MAX(e1abs,ABS(e0))*epmach
                  if(err2.gt.tol2.or.err3.gt.tol3) go to 10
!c
!c           if e0, e1 and e2 are equal to within machine
!c           accuracy, convergence is assumed.
!c           result = e2
!c           abserr = abs(e1-e0)+abs(e2-e1)
!c
                  result = res
                  abserr = err2+err3
!c ***jump out of do-loop
                  go to 100
   10             e3 = epstab(k1)
                  epstab(k1) = e1
                  delta1 = e1-e3
                  err1 = ABS(delta1)
                  tol1 = MAX(e1abs,ABS(e3))*epmach
!c
!c           if two elements are very close to each other, omit
!c           a part of the table by adjusting the value of n
!c
                  if(err1.le.tol1.or.err2.le.tol2.or.err3.le.tol3) go to 20
                  ss = 0.1e+01_dp/delta1+0.1e+01_dp/delta2-0.1e+01_dp/delta3
                  epsinf = ABS(ss*e1)
!c
!c           test to detect irregular behaviour in the table, and
!c           eventually omit a part of the table adjusting the value
!c           of n.
!c
                 if(epsinf.gt.0.1e-03_dp) go to 30
   20            n = i+i-1
!c ***jump out of do-loop
                 go to 50
!c
!c           compute a new element and eventually adjust
!c           the value of result.
!c
   30           res = e1+0.1e+01_dp/ss
                epstab(k1) = res
                k1 = k1-2
                error = err2+ABS(res-e2)+err3
                if(error.gt.abserr) go to 40
                abserr = error
                result = res
   40      continue
!c
!c           shift the table.
!c
   50       if(n.eq.limexp) n = 2*(limexp/2)-1
            ib = 1
            if((num/2)*2.eq.num) ib = 2
            ie = newelm+1
            do 60 i=1,ie
                  ib2 = ib+2
                  epstab(ib) = epstab(ib2)
                  ib = ib2
   60      continue
           if(num.eq.n) go to 80
           indx = num-n+1
           do 70 i = 1,n
                 epstab(i)= epstab(indx)
                 indx = indx+1
   70      continue
   80      if(nres.ge.4) go to 90
           res3la(nres) = result
           abserr = oflow
           go to 100
!c
!c           compute error estimate
!c
   90      abserr = ABS(result-res3la(3))+ABS(result-res3la(2)) &
           + ABS(result-res3la(1))
           res3la(1) = res3la(2)
           res3la(2) = res3la(3)
           res3la(3) = result
  100      abserr = MAX(abserr,0.5e+01_dp*epmach*ABS(result))
     end subroutine dqelg


   real(kind=dp)  function hh(npt, func, ier) result(integral)

!  Half-Hermite integration, i.e. integration from 0 to infinity of

!                 f(x).exp(-x**2)

!  Arguments:-
!  NPT    = INPUT, no.of points at which the function, f(x), is
!           to be evaluated.   NPT must be between 2 and 20 incl.
!  FUNC   = INPUT, name of the user's function to supply values of f(x).
!           The function may have any name, but only the one argument, x.
!           FUNC - or whatever name you use, must be declared double
!           precision and external in the calling program.
!  IER    = OUTPUT, error indicator
!         = 0 if no error detected
!         = 1 if an illegal value was supplied for NPT.

!  N.B.  The function f(x) must have continuous derivatives of all orders
!  throughout the range of integration.   The abscissa and weights are such
!  that the approximate integral returned is accurate to about 14 decimal
!  digits if n points are used and f(x) is a polynomial of degree (2n-1) or
!  less.   The abscissae and weights supplied give slightly more accurate
!  results than those given in the two references below, which were used as
!  starting values.

!  References:-
!  Steen, M.M., Byrne, G.D. & Gelbard, E.M. (1969).   Gaussian quadrature
!    for the integrals ... .   Mathematics of Computation, v.23, 661-671.
!  Kahaner, D., Tietjen, G. & Beckman, R. (1982). Gaussian-quadrature
!    formulas for ... .   J. Statist. Comput. Simul., v.15, 155-160.

!  Programmer:   Alan Miller
!                CSIRO Division of Mathematics & Statistics
!                Private Bag 10
!                Clayton, Victoria 3169
!  e-mail: amiller @ bigpond.net.au

!  `Translated' from Fortran 77 code - 24 May 1996
!  Latest revision - 21 January 2000

!***********************************************************************

implicit none
integer(kind=i4), intent(in)  :: npt
integer(kind=i4), intent(out) :: ier
 
real(kind=dp)     :: func
external func

! Local variables
real(kind=dp)      :: xpt(209), wt(209)
real(kind=dp)      :: integral
integer(kind=i4)   :: i, ipos

DATA xpt(1:119)/ &
  0.300193931060839D+00, 0.125242104533372D+01, &                                                !2
  0.190554149798192D+00, 0.848251867544577D+00, 0.179977657841573D+01, &                         !3
  0.133776446996068D+00, 0.624324690187190D+00, 0.134253782564499D+01, 0.226266447701036D+01, &  !4
  0.100242151968216D+00, 0.482813966046201D+00, 0.106094982152572D+01, 0.177972941852026D+01, &  !5
  0.266976035608766D+01, &
  0.786006594130979D-01, 0.386739410270631D+00, 0.866429471682044D+00, 0.146569804966352D+01, &  !6
  0.217270779693900D+01, 0.303682016932287D+01, &
  0.637164846067008D-01, 0.318192018888619D+00, 0.724198989258373D+00, 0.123803559921509D+01, &  !7
  0.183852822027095D+01, 0.253148815132768D+01, 0.337345643012458D+01, &
  0.529786439318511D-01, 0.267398372167765D+00, 0.616302884182400D+00, 0.106424631211622D+01, &  !8
  0.158885586227006D+01, 0.218392115309586D+01, 0.286313388370807D+01, 0.368600716272440D+01, &
  0.449390308011905D-01, 0.228605305560523D+00, 0.532195844331623D+00, 0.927280745338049D+00, &  !9
  0.139292385519585D+01, 0.191884309919739D+01, 0.250624783400570D+01, 0.317269213348120D+01, &
  0.397889886978974D+01, &
  0.387385243256994D-01, 0.198233304012949D+00, 0.465201111814507D+00, 0.816861885591907D+00, &  !10
  0.123454132402774D+01, 0.170679814968865D+01, 0.222994008892444D+01, 0.280910374689825D+01, &
  0.346387241949537D+01, 0.425536180636561D+01, &
  0.338393212317745D-01, 0.173955727710236D+00, 0.410873840972387D+00, 0.726271784259897D+00, &  !11
  0.110386324646491D+01, 0.153229503457537D+01, 0.200578290246814D+01, 0.252435214151921D+01, &
  0.309535170986922D+01, 0.373947860994358D+01, 0.451783596718736D+01, &
  0.298897007696644D-01, 0.154204878265825D+00, 0.366143962974312D+00, 0.650881015845205D+00, &  !12
  0.994366869880792D+00, 0.138589120364956D+01, 0.181884860842823D+01, 0.229084273867285D+01, &
  0.280409679339362D+01, 0.336727070416293D+01, 0.400168347567348D+01, 0.476821628798986D+01, &
  0.266511266223847D-01, 0.137891855469939D+00, 0.328828675158344D+00, 0.587378531473706D+00, &  !13
  0.901480884535392D+00, 0.126129650258238D+01, 0.166003713190544D+01, 0.209410900418749D+01, &
  0.256320702525468D+01, 0.307091234102964D+01, 0.362669201180255D+01, 0.425220740047932D+01, &
  0.500800834323777D+01, &
  0.239567892441074D-01, 0.124240344109914D+00, 0.297338568916482D+00, 0.533329214443288D+00, &  !14
  0.821873189116935D+00, 0.115406707387441D+01, 0.152327479144572D+01, 0.192533821047710D+01, &
  0.235860076664477D+01, 0.282409375484497D+01, 0.332626935870514D+01, 0.387510499098758D+01, &
  0.449243807160692D+01, 0.523843136267529D+01, &
  0.216869426988512D-01, 0.112684196952642D+00, 0.270492620388998D+00, 0.486902289234274D+00, &  !15
  0.753043574230519D+00, 0.106093087200583D+01, 0.140425480937058D+01, 0.177864621852044D+01, &
  0.218170796284551D+01, 0.261306067251355D+01, 0.307461793949750D+01, 0.357140797746735D+01, &
  0.411373591845599D+01, 0.472351289497065D+01, 0.546048877386486D+01/
DATA xpt(120:209)/ &
  0.197536584600773D-01, 0.102802245237917D+00, 0.247397669452455D+00, 0.446696225961683D+00, &  !16
  0.693073720302000D+00, 0.979404170330730D+00, 0.129978932127704D+01, 0.164985424039743D+01, &
  0.202680815216887D+01, 0.242945049160214D+01, 0.285826652854327D+01, 0.331576927503870D+01, &
  0.380737711675590D+01, 0.434360634547017D+01, 0.494637720404839D+01, 0.567501793404192D+01, &
  0.180910833291262D-01, 0.942756133296731D-01, 0.227367679140888D+00, 0.411621543218912D+00, &  !17
  0.640465304258667D+00, 0.907557245160356D+00, 0.120744250530777D+01, 0.153586090376516D+01, &
  0.188983689868465D+01, 0.226768435443910D+01, 0.266903218379336D+01, 0.309496584156224D+01, &
  0.354841560757166D+01, 0.403506890899052D+01, 0.456557652510097D+01, 0.516182632161921D+01, &
  0.588272607689950D+01, &
  0.166490322202372D-01, 0.868590621084087D-01, 0.209868348130364D+00, 0.380820011068889D+00, &  !18
  0.594030720753567D+00, 0.843863021635420D+00, 0.112530737639273D+01, 0.143428771048619D+01, &
  0.176777393564494D+01, 0.212379869512189D+01, 0.250145945877649D+01, 0.290097223563891D+01, &
  0.332384856894201D+01, 0.377331513435006D+01, 0.425524711266144D+01, 0.478037806093043D+01, &
  0.537053657981972D+01, 0.608421686390343D+01, &
  0.153886660136205D-01, 0.803613182824543D-01, 0.194478326810452D+00, 0.353607595856074D+00, &  !19
  0.552816862912666D+00, 0.787094922636796D+00, 0.105186215045210D+01, 0.134326400045299D+01, &
  0.165829830732126D+01, 0.199484680375345D+01, 0.235167370676724D+01, 0.272844153701442D+01, &
  0.312579015345213D+01, 0.354553959918365D+01, 0.399113055980209D+01, 0.446857002866801D+01, &
  0.498863874530620D+01, 0.557308861757198D+01, 0.628001037094314D+01, &
  0.142795096999168D-01, 0.746313003921914D-01, 0.180861563058038D+00, 0.329433356064288D+00, &  !20
  0.516050543061530D+00, 0.736255457580891D+00, 0.985873575037527D+00, 0.126128901610277D+01, &
  0.155957964520966D+01, 0.187856191930298D+01, 0.221679416538765D+01, 0.257357782082628D+01, &
  0.294898974678723D+01, 0.334398137986164D+01, 0.376059993291077D+01, 0.420244260042114D+01, &
  0.467560884779448D+01, 0.519090168697500D+01, 0.576998516556776D+01, 0.647055838706458D+01/
DATA wt(1:119)/ &
  0.640529179684379D+00, 0.245697745768379D+00, &                                                !2
  0.446029770466658D+00, 0.396468266998335D+00, 0.437288879877644D-01, &                         !3
  0.325302999756919D+00, 0.421107101852062D+00, 0.133442500357520D+00, 0.637432348625728D-02, &  !4
  0.248406152028443D+00, 0.392331066652399D+00, 0.211418193076057D+00, 0.332466603513439D-01, &  !5
  0.824853344515628D-03, &
  0.196849675488598D+00, 0.349154201525395D+00, 0.257259520584421D+00, 0.760131375840057D-01, &  !6
  0.685191862513597D-02, 0.984716452019267D-04, &
  0.160609965149261D+00, 0.306319808158099D+00, 0.275527141784906D+00, 0.120630193130784D+00, &  !7
  0.218922863438067D-01, 0.123644672831056D-02, 0.110841575911059D-04, &
  0.134109188453360D+00, 0.268330754472639D+00, 0.275953397988422D+00, 0.157448282618790D+00, &  !8
  0.448141099174629D-01, 0.536793575602533D-02, 0.202063649132411D-03, 0.119259692659534D-05, &
  0.114088970242111D+00, 0.235940791223676D+00, 0.266425473630252D+00, 0.183251679101671D+00, &  !9
  0.713440493066984D-01, 0.139814184155624D-01, 0.116385272078542D-02, 0.305670214897907D-04, &
  0.123790511337534D-06, &
  0.985520975190362D-01, 0.208678066608076D+00, 0.252051688403725D+00, 0.198684340038460D+00, &  !10
  0.971984227601550D-01, 0.270244164355872D-01, 0.380464962250372D-02, 0.228886243045297D-03, &
  0.434534479845945D-05, 0.124773714818325D-07, &
  0.862207055348204D-01, 0.185767318954432D+00, 0.235826124129156D+00, 0.205850326842101D+00, &  !11
  0.119581170616438D+00, 0.431443275887789D-01, 0.886764989495983D-02, 0.927141875111555D-03, &
  0.415719321683689D-04, 0.586857646864747D-06, 0.122714514000882D-08, &
  0.762461467930431D-01, 0.166446068879474D+00, 0.219394898128707D+00, 0.207016508679094D+00, &  !12
  0.137264362796474D+00, 0.605056743489164D-01, 0.165538019564075D-01, 0.258608378835667D-02, &
  0.206237541067489D-03, 0.706650986752706D-05, 0.759131547256598D-07, 0.118195417166772D-09, &
  0.680463904418563D-01, 0.150057211706640D+00, 0.203606639691744D+00, 0.204104355198729D+00, &  !13
  0.150119228251119D+00, 0.774536315632889D-01, 0.264891667292508D-01, 0.562343031211025D-02, &
  0.683241179366847D-03, 0.424853319211805D-04, 0.113557101360564D-05, 0.946453645906370D-08, &
  0.111810461699377D-10, &
  0.612109812196030D-01, 0.136062058638519D+00, 0.188856801742046D+00, 0.198577828793095D+00, &  !14
  0.158617339225760D+00, 0.928167848032935D-01, 0.379316402929447D-01, 0.102563915568667D-01, &
  0.172277191301072D-02, 0.165956353055286D-03, 0.819589395640479D-05, 0.173876626376522D-06, &
  0.114293991639056D-08, 0.104120023691655D-11, &
  0.554433542997126D-01, 0.124027715695603D+00, 0.175290920953716D+00, 0.191488332592396D+00, &  !15
  0.163473809496946D+00, 0.105937660378078D+00, 0.500270400435842D-01, 0.164429780046165D-01, &
  0.357320679306892D-02, 0.482896942477554D-03, 0.374909051856946D-04, 0.149368597328174D-05, &
  0.255270858132649D-07, 0.134217892411487D-09, 0.956229145184876D-13/
DATA wt(120:209)/ &
  0.505246320213779D-01, 0.113608556894151D+00, 0.162921292314545D+00, 0.183562801116246D+00, &  !16
  0.165438637755610D+00, 0.116572490553503D+00, 0.619996960991566D-01, 0.239197096186835D-01, &
  0.640991442405013D-02, 0.113569531068878D-02, 0.125286221329562D-03, 0.795049571962246D-05, &
  0.259000761941506D-06, 0.361154913974278D-08, 0.153767791618984D-10, 0.867420445249463D-14, &
  0.462902182569444D-01, 0.104528587434386D+00, 0.151692844038654D+00, 0.175289523252223D+00, &  !17
  0.165194113560473D+00, 0.124758912731550D+00, 0.732500435683077D-01, 0.322890873617879D-01, &
  0.102921626932112D-01, 0.227638568842155D-02, 0.333037962863638D-03, 0.303707486255998D-04, &
  0.159468239105431D-05, 0.429767400483309D-07, 0.494454281458509D-09, 0.172326283208696D-11, &
  0.778200825411988D-15, &
  0.426142619814402D-01, 0.965666206000141D-01, 0.141519805800333D+00, 0.166987766912260D+00, &  !18
  0.163315996982125D+00, 0.130699466898224D+00, 0.833782286268739D-01, 0.411112305586427D-01, &
  0.151576539874531D-01, 0.403326905747473D-02, 0.744434183403738D-03, 0.909462923551198D-04, &
  0.693223179081282D-05, 0.304417379930170D-06, 0.685706226732795D-08, 0.657362956131057D-10, &
  0.189340654173429D-12, 0.691219900671972D-16, &
  0.393990986682379D-01, 0.895444367628123D-01, 0.132305744000463D+00, 0.158859868228014D+00, &  !19
  0.160268450441027D+00, 0.134675758617491D+00, 0.921641776964749D-01, 0.499738916193989D-01, &
  0.208459843479637D-01, 0.648435446662631D-02, 0.145409393575714D-02, 0.226202869969883D-03, &
  0.233075944706917D-04, 0.149954388953745D-05, 0.555953942746990D-07, 0.105623488322490D-08, &
  0.851137824908803D-11, 0.204347153060500D-13, 0.608418799770205D-17, &
  0.365679216320084D-01, 0.833175344016776D-01, 0.123954178541192D+00, 0.151028580007023D+00, &  !20
  0.156414467004551D+00, 0.136992234955135D+00, 0.995292472472200D-01, 0.585337706979062D-01, &
  0.271357803755605D-01, 0.964473365921540D-02, 0.255171509156881D-02, 0.486448997660902D-03, &
  0.643514517998962D-04, 0.564239148952609D-05, 0.309083652232771D-06, 0.975641105342091D-08, &
  0.157608671739272D-09, 0.107594574673723D-11, 0.216986354627585D-14, 0.531122306167733D-18/

!     Check for permissible value of NPT.

integral = 0.d0
ier = 1
if(npt < 2 .OR. npt > 20) return

!     IPOS = position of first abscissa & weight to use.

ier = 0
ipos = npt*(npt-1)/2

!     Evaluate approximation = Sum w(i).f(xi)

do i = 1, npt
   integral = integral + wt(ipos)*func(xpt(ipos))
   ipos = ipos + 1
end do
return

end function hh
         

end module mod_quadratures
