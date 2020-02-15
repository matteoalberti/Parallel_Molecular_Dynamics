#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "compute_forces.h"
#include "helper.h"

#include "constants.h"

/* compute forces */
void force(mdsys_t *sys) 
{
    double r,ffac;
    double rx,ry,rz;
    double * fx, *fy, *fz;
    int i,j;
    double epot = 0.0;


    /* zero energy and forces */
	#ifdef USE_MPI

	  fx = sys->cx;
	  fy = sys->cy;
	  fz = sys->cz;

	  /* communicate to all the processes previous step update of positions */
	  MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
	  MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
	  MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );

	#else
	  /* sys->epot=0.0; */
	  fx = sys->fx;
	  fy = sys->fy;
	  fz = sys->fz;
	#endif //USE_MPI

    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    for(i=0; i < (sys->natoms); ++i) {
        for(j=0; j < (sys->natoms); ++j) {

            /* particles have no interactions with themselves */
            if (i==j) continue;
            
            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);
      
            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);
                
                sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                               -pow(sys->sigma/r,6.0));

                sys->fx[i] += rx/r*ffac;
                sys->fy[i] += ry/r*ffac;
                sys->fz[i] += rz/r*ffac;
            }
        }
    }
	#ifdef USE_MPI
	  MPI_Reduce( fx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
	  MPI_Reduce( fy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
	  MPI_Reduce( fz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
	  MPI_Reduce( &epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
	#else
	  sys->epot = epot;
	#endif //USE_MPI
	return;
}
