#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "compute_forces.h"
#include "helper.h"

#ifdef USE_MPI
#include "timer.h"
#include <mpi.h>
#endif //USE_MPI

#ifdef _OPENMP
#include <omp.h>
#endif //_OPENMP

double pbc2(double x, const double boxby2)
{
    while (x >  boxby2) x -= 2.0*boxby2;
    while (x < -boxby2) x += 2.0*boxby2;
    return x;
}

/* compute forces */
void force(mdsys_t *sys) 
{
    double rsq, ffac;
    double rx,ry,rz;
    double rcsq =  sys->rcut * sys->rcut;
    int i,j;
    sys-> t_elapsed = 0;
    sys-> t_elapsed_slow = 0;

#ifdef USE_MPI
    /* communicate to all the processes previous step update of positions */
    MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    
    azzero(sys->cx,sys->natoms);
    azzero(sys->cy,sys->natoms);
    azzero(sys->cz,sys->natoms);
#endif//USE_MPI

    /* zero energy and forces */
    double epot = 0.0;
    sys->epot=0.0;
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    double sigma=sys->sigma;
    double sigma6 = sigma* sigma* sigma*sigma* sigma* sigma;
    double c12    =  4.0*sys->epsilon*sigma6*sigma6;
    double c6     = -4.0*sys->epsilon*sigma6;
    
#ifdef USE_MPI
    for(i=sys->rank; i < (sys->natoms) ; i+=sys->nps) {
      for(j=i+1; j < (sys->natoms); ++j) {
#else

#pragma omp parallel for schedule(dynamic) private(i, j, rsq, rx, ry, rz, ffac) reduction(+ : epot) 
    for(i=0; i < (sys->natoms) - 1; ++i) {

	double fx_i, fy_i, fz_i;
        fx_i = fy_i = fz_i = 0.0;

        for(j= i+1 ; j < (sys->natoms); ++j) {
            
#endif//USE_MPI      
            
            /* get distance between particle i and j */
            rx=pbc2(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc2(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc2(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            rsq = rx*rx + ry*ry + rz*rz;
      
            /* compute force and energy if within cutoff */
            if (rsq < rcsq) {
    
                double r6, rinv;
                rinv = 1.0/rsq;
                r6   = rinv*rinv*rinv;
                ffac = (c12*12.0*r6 + 6.0*c6)*r6*rinv;

                epot  += r6*(c12*r6 + c6) ;

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
           }
        }
  		
#else// USE_MPI
               
		fx_i += rx;
		fy_i += ry;
		fz_i += rz;           
		
#pragma omp atomic
		sys->fx[j] -= rx;
#pragma omp atomic
        	sys->fy[j] -= ry;
#pragma omp atomic
	        sys->fz[j] -= rz;
           }
        }

#pragma omp atomic
		sys->fx[i] += fx_i;
#pragma omp atomic
		sys->fy[i] += fy_i;
#pragma omp atomic
		sys->fz[i] += fz_i;
  		
#endif //USE_MPI         
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
