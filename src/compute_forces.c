#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "compute_forces.h"
#include "helper.h"

#ifdef _OPENMP
#include <omp.h>
#endif


/* compute forces */
void force(mdsys_t *sys) 
{
  double r, ffac;
  double rx, ry, rz, epot;
  int i, j;
  double *fx, *fy, *fz;

  fx = sys->fx; 
  fy = sys->fy;
  fz = sys->fz;
  
  /* zero energy and forces */
  epot=0.0;
  azzero(fx, sys->natoms );
  azzero(fy, sys->natoms );
  azzero(fz, sys->natoms );

#if _OPENMP
#pragma omp parallel reduction(+ : epot) 
  { // begin of parallel region
#pragma omp for schedule(dynamic) private(i, j, r, rx, ry, rz, ffac)  
#endif 
   for(i=0; i < (sys->natoms)-1; ++i) {

     for(j=i+1; j < (sys->natoms); ++j) {

       /* get distance between particle i and j */
       rx = pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
       ry = pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
       rz = pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
       r = sqrt(rx*rx + ry*ry + rz*rz);
   
       /* compute force and energy if within cutoff */
       if(r < sys->rcut){
         
        ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)
                                    +6*pow(sys->sigma/r,6.0))/(r*r);
           
        epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                          -pow(sys->sigma/r,6.0));

        rx *= ffac;
        ry *= ffac;
        rz *= ffac;

        fx[i] += rx;
        fy[i] += ry;
        fz[i] += rz;

#if _OPENMP
#pragma omp atomic
#endif
        fx[j] -= rx;
#if _OPENMP
#pragma omp atomic
#endif
        fy[j] -= ry;
#if _OPENMP
#pragma omp atomic
#endif
        fz[j] -= rz;
  		
       }
     }
   }
#if _OPENMP
  }// end of parallel region
#endif
   sys->epot = epot;

}
