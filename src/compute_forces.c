#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "compute_forces.h"
#include "helper.h"
#include "timer.h"

#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI

#ifdef _OPENMP
#include <omp.h>
#endif //_OPENMP


/* compute forces */
void force(mdsys_t *sys) 
{
    double r,ffac;
    double rx,ry,rz;
    int i,j;
    double epot = 0.0;
    sys-> t_elapsed = 0;
    sys-> t_elapsed_slow = 0;
    sys->epot=0.0;

    /* zero energy and forces */
#ifdef USE_MPI
    azzero(sys->cx,sys->natoms);
    azzero(sys->cy,sys->natoms);
    azzero(sys->cz,sys->natoms);
    
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    /* communicate to all the processes previous step update of positions */
    MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
#else
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);
#endif //USE_MPI


#ifdef USE_MPI
    for(i=sys->rank; i < (sys->natoms) ; i+=sys->nps) {
     // ii=i+sys->rank;
    //  if (ii > (sys->natoms - 1)) break;
      for(j=i+1; j < (sys->natoms); ++j) {
#else

#pragma omp parallel for schedule(dynamic) private(i, j, r, rx, ry, rz, ffac) reduction(+ : epot) 
    for(i=0; i < (sys->natoms); ++i) {
        for(j=i+1; j < (sys->natoms); ++j) {
            
#endif      
            
            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);
      
            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)
                                         +6*pow(sys->sigma/r,6.0))/(r*r);
                
                epot += 4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                               -pow(sys->sigma/r,6.0));
                rx *= ffac;
                ry *= ffac;
                rz *= ffac;

#ifdef USE_MPI
                sys->t_elapsed_start = timer_seconds();
                sys->cx[i] += rx;
                sys->cy[i] += ry;
                sys->cz[i] += rz;
                sys->cx[j] -= rx;
                sys->cy[j] -= ry;
                sys->cz[j] -= rz;
                sys->t_elapsed += timer_seconds() - sys->t_elapsed_start;
#else                
           
        fx[i] += rx;
        fy[i] += ry;
        fz[i] += rz;

#pragma omp atomic
        fx[j] -= rx;
#pragma omp atomic
        fy[j] -= ry;
#pragma omp atomic
        fz[j] -= rz;
  		
#endif
              
            }
        }
    }

#ifdef USE_MPI
    MPI_Reduce( sys->cx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    MPI_Reduce( sys->cy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    MPI_Reduce( sys->cz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    MPI_Reduce( &epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    MPI_Reduce( &sys->t_elapsed, &sys->t_elapsed_slow, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    
#else
    sys->epot=epot;
#endif //USE_MPI
	return;
}
