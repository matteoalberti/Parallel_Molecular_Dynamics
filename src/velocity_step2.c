#include "velocity_step2.h"
#include "md_struct.h"
#include "constants.h"


void vel_step2(mdsys_t *sys){
int i;
double vconst = 0.5 * sys->dt /(mvsq2e * sys->mass);

     /* second part: propagate velocities by another half step */
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += vconst * sys->fx[i];
        sys->vy[i] += vconst * sys->fy[i];
        sys->vz[i] += vconst * sys->fz[i];
    }
} 
