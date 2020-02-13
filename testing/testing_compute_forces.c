#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "compute_forces.h"
#include "helper.h"
#include "constants.h"

/*struct _mdsys {
 *     int natoms,nfi,nsteps;
 *     double dt, mass, epsilon, sigma, box, rcut;
 *     double ekin, epot, temp;
 *     double *rx, *ry, *rz;
 *     double *vx, *vy, *vz;
 *     double *fx, *fy, *fz;
 *
 *3                 # natoms
 *39.948            # mass in AMU
 *0.2379            # epsilon in kcal/mol
 *3.405             # sigma in angstrom
 *8.5               # rcut in angstrom
 *17.1580            # box length (in angstrom)
 *argon_3.rest      # restart
 *argon_3.xyz       # trajectory
 *argon_3.dat       # energies
 *10000             # nr MD steps
 *5.0               # MD time step (in fs)
 *100               # output print frequency
 */

int main(){
	mdsys_t sys;
	sys.natoms=3;
	sys.mass=39.948;
	sys.epsilon=0.2379;
	sys.sigma=3.405;
	sys.rcut=8.5;
	sys.box=17.1580;
	sys.nsteps=1000;
	sys.dt=5.0;
	sys.nfi=0;

	/* allocate memory */
	sys.rx=(double *)malloc(sys.natoms*sizeof(double));
	sys.ry=(double *)malloc(sys.natoms*sizeof(double));
	sys.rz=(double *)malloc(sys.natoms*sizeof(double));
	
	sys.vx=(double *)malloc(sys.natoms*sizeof(double));
	sys.vy=(double *)malloc(sys.natoms*sizeof(double));
	sys.vz=(double *)malloc(sys.natoms*sizeof(double));
	
	sys.fx=(double *)calloc(sys.natoms,sizeof(double));
	sys.fy=(double *)calloc(sys.natoms,sizeof(double));
	sys.fz=(double *)calloc(sys.natoms,sizeof(double));

	//Set position of atoms - r[0] r[1] fixed on ax,ay and sigma distance between az | r[2] outside
	sys.rx[0]=1;
        sys.ry[0]=1;	
	sys.rz[0]=1;

	sys.rx[1]=1;
	sys.ry[1]=1;
	sys.rz[1]=4.405;

	sys.rx[2]=29.19613239880890;
	sys.ry[2]=-30.97120493339350;
	sys.rz[2]=-17.97120493339350;

	//Execute 
	force(&sys);
	
	printf("r[0] r[1] fixed on axis x,y and sigma distance on axis z | r[2] out of the box\n");
	for (int i=0; i<sys.natoms; ++i) {
		printf("Fx  %20.8f %20.8f %20.8f\n", sys.fx[i], sys.fy[i], sys.fz[i]);
		}	
	printf("Epot %20.8f\n\n", sys.epot);	
	

	//Set position of atoms - r[0] r[1] fixed on ax,ay and sigma distance between az | r[2] inside
	sys.rx[0]=1;
        sys.ry[0]=1;	
	sys.rz[0]=1;

	sys.rx[1]=1;
	sys.ry[1]=1;
	sys.rz[1]=4.405;

	sys.rx[2]=2.19;
	sys.ry[2]=-3.90;
	sys.rz[2]=-4.9350;

	//Execute 
	force(&sys);
	
	printf("r[0] r[1] fixed on axis x,y and sigma distance on axis z | r[2] inside the box\n");
	for (int i=0; i<sys.natoms; ++i) {
		printf("Fx  %20.8f %20.8f %20.8f\n", sys.fx[i], sys.fy[i], sys.fz[i]);
		}	
	printf("Epot %20.8f\n\n", sys.epot);	
	

}

