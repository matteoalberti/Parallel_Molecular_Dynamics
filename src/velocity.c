#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "velocity.h"
#include "compute_forces.h"
#include "md_struct.h"
#include "constants.h"


/* velocity verlet */
void velverlet(mdsys_t *sys)
{
    int i;

    /* first part: propagate velocities by half and positions by full step */
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];
    }

    /* compute forces and potential energy */
    force(sys);

    /* second part: propagate velocities by another half step */
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
}


/*ATTENTION ON velverlet_step2
	Here some problems can show up!
	Becouse to make in looks simple I (punch Natalia) 
	skiped some boundary conditions from compute_forces.c
	and helper.c files (pbc and azzero functions) 
	So... BE CAREFUL
*/

void velverlet_step2(mdsys_t *sys)
{
    int i, j;
    double r,ffac;

    /* first part: propagate velocities by half and positions by full step */
    for (i=0; i<sys->natoms; ++i) {
	sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];

	for(j=0; j < (sys->natoms); ++j) {	
	
	if(sys->rx[i] - sys->rx[j] > 0.5*sys->box)
		 sys->rx[i]  -= sys->box;
		else sys->rx[i]  += sys->box;

       if(sys->ry[i] - sys->ry[j] > 0.5*sys->box)
                 sys->ry[i]  -= sys->box;
                else sys->ry[i]  += sys->box;

	if(sys->rz[i] - sys->rz[j] > 0.5*sys->box)
                 sys->rz[i]  -= sys->box;
                else sys->rz[i]  += sys->box;

   			 }
		}

	r = sqrt(sys->rx[i] * sys->rx[i] + sys->ry[i] * sys->ry[i] + sys->rz[i] * sys->rz[i]);
	ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);
	
                sys->fx[i] += sys->rx[i]/r*ffac;
                sys->fy[i] += sys->ry[i]/r*ffac;
                sys->fz[i] += sys->rz[i]/r*ffac;

    /* second part: propagate velocities by another half step */
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
}



void velverlet_step1(mdsys_t *sys)
{
    int i, j;
    double r,ffac;

    /* first part: propagate velocities by half and positions by full step */
    for (i=0; i<sys->natoms; ++i) { 
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];
        

        r = sqrt(sys->rx[i] * sys->rx[i] + sys->ry[i] * sys->ry[i] + sys->rz[i] * sys->rz[i]);
        ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);

                sys->fx[i] += sys->rx[i]/r*ffac;
                sys->fy[i] += sys->ry[i]/r*ffac;
                sys->fz[i] += sys->rz[i]/r*ffac;

    /* second part: propagate velocities by another half step */
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
	sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;

  }
}
