#ifndef MD_STRUCTURE_H
#define MD_STRUCTURE_H
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include "constants.h"

/* structure to hold the complete information
 * about the MD system */
struct _mdsys {
    int natoms,nfi,nsteps;
    int rank,nps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
	#ifdef USE_MPI
	  double *cx, *cy, *cz;
	#endif //USE_MPI
};
typedef struct _mdsys mdsys_t;

#endif
