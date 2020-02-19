#ifndef MD_STRUCTURE_H
#define MD_STRUCTURE_H
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include "constants.h"

#ifdef _OPENMP
#include <omp.h>
#endif //_OPENMP

/* structure to hold the complete information
 * about the MD system */
struct _mdsys {
    int natoms,nfi,nsteps;
    int rank,nps,Nloc;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
	double *cx, *cy, *cz;
    double t_elapsed,t_elapsed_start, t_elapsed_slow;

};
typedef struct _mdsys mdsys_t;

#endif
