#include "velocity_step1.h"
#include "md_struct.h"
#include "constants.h"


void vel_step1(mdsys_t *sys){
int i;
double vconst = 0.5 * sys->dt /(mvsq2e * sys->mass);

    /* first part: propagate velocities by half and positions by full step */
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += vconst * sys->fx[i];
        sys->vy[i] += vconst * sys->fy[i];
        sys->vz[i] += vconst * sys->fz[i];
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];
    }
}
