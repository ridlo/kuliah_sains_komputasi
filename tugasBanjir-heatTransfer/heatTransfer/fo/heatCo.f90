program heatco
! program untuk menghitung heat transfer pada konduktor
! menggunakan Shooting Method with Runge-Kutta (RK4)
! ndim      array dimension,
! imax      jumlah grid,
! x         variable bebas, x(i)
! y         variable terikat, y(i)
! z         turunan pertama dy/dx, z(i)
! y1, z1    boundary condition kiri
! y2, z2    boundary condition kanan
! by, bz    flag untuk boundary di kanan: 0.0 or 1.0
! za, zb    tebakan pertama dan kedua untuk nilai z
! dx        grid increment
! iter      maximum number of iteration (shoot)
! tol       convergence tolerance
! iw        intermediate results output flag: 0 None, 1 some, 2 all

            dimension x(9), y(9), z(9)
            data ndim, imax, iter, tol, iw / 9, 5, 3, 1.0e-6, 1 /
            data (x(i), i=1,5), dx / 0.0, 0.25, 0.50, 0.75, 1.00, 0.25 /
            data y(1), za, zb / 0.0, 7.5, 12.5 /
            data by, bz, y1, z1, y2, z2 / 1.0, 0.0, 0.0, 0.0, 100.0, 0.0 /
            write (6, 1000)
            call shoot(ndim, imax, x, y, z, by, bz, y1, z1, y2, z2, za, zb, dx, iter, tol, iw)
            if (iw.ne.1) write (6, 1010) (i, x(i), y(i), z(i), i=1, imax)
            stop
1000 format ('Shooting method'/' '/' i', 7x, 'x', 12x, 'y', 12x, 'z' /' ')
1010 format (i3, 3f13.6)
1020 format (' ')
     end
     
     subroutine shoot(ndim, imax, x, y, z, by, bz, y1, z1, y2, z2, za, zb, dx, iter, tol, iw)
! The shooting method
     dimension x(ndim), y(ndim), z(ndim)
     rhs = by*y2+bz*z2
     z(1) = za
     do it = 1, iter
         call rk2 (ndim, imax, x, y, z, dx, iw)
         if (iw.gt.1) write (6, 1000)
         if (iw.gt.0) write (6, 1010) (i, x(i), y(i), z(i), i=1,imax)
         if (iw.gt.0) write (6, 1000)
         if (it.eq.1) then
             rhs1 = by*y(imax) + bz*z(imax)
             z(1) = zb
         else
             rhs2 = by*y(imax) + bz*z(imax)
             if (abs(rhs2-rhs1).le.tol) return
             zb = z(1)
             slope = (rhs2-rhs1)/(zb-za)
             za = zb
             rhs1=rhs2
             z(1) = z(1) + (rhs-rhs2)/slope
         endif
     end do
     
     if (iter.gt.3) write (6, 1020) iter
     return

1000 format (' ')
1010 format (i3, 3f13.6)
1020 format (' '/' The solution failed to cenvergence, iter = ', i3)
     end

     subroutine rk2 (ndim, imax, x, y, z, dx, iw)
! Runge-Kutta fourth-order
     dimension x(ndim), y(ndim), z(ndim)
     do i = 2, imax
         dy1 = dx*z(i-1)
         dz1 = dx*f(x(i-1), y(i-1), z(i-1))
         dy2 = dx*(z(i-1)+dz1/2.0)
         dz2 = dx*f(x(i-1)+dx/2.0, y(i-1)+dy1/2.0, z(i-1)+dz1/2.0)
         dy3 = dx*(z(i-1)+dz2/2.0)
         dz3 = dx*f(x(i-1)+dx/2.0, y(i-1)+dy2/2.0, z(i-1)+dz2/2.0)
         dy4 = dx*(z(i-1)+dz3)
         dz4 = dx*f(x(i-1)+dx, y(i-1)+dy3, z(i-1)+dz3)

         y(i) = y(i-1) + (dy1 + 2.0*(dy2+dy3) + dy4)/6.0
         z(i) = z(i-1) + (dz1 + 2.0*(dz2+dz3) + dz4)/6.0

         if (iw.eq.2) write (6, 1000) i, dy1, dy2, dy3, dy4, y(i)
         if (iw.eq.2) write (6, 1000) i, dz1, dz2, dz3, dz4, z(i) 
     end do
     return

1000 format (i3, 5f13.6)
     end

     function f(x, y, z)
! fungsi turunannya
! p = koefisien dari yp di ODE
! q = koefisien dari y di ODE
! nonhomogenious term -> fx
     data p, q, fx / 0.0, -16.0, 0.0 /
     f = fx-p*z-q*y
     return
     end

end program heatco    
