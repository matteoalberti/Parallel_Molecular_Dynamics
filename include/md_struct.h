#ifndef MD_STRUCTURE_H
#define MD_STRUCTURE_H
#include "constants.h"

#if defined(_OPENMP)
#include <omp.h>
#endif

/* structure to hold the complete information
 * about the MD system */
struct _mdsys {
    int natoms,nfi,nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;

#if defined(_OPENMP)
    int nthreads = omp_get_num_threads();
#else 
    int nthreads = 1;
#endif

};
typedef struct _mdsys mdsys_t;

#endif
