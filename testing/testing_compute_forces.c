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
 *2.5               # rcut in angstrom
 *5.1964            # box length (in angstrom)
 *argon_3.rest      # restart
 *argon_3.xyz       # trajectory
 *argon_3.dat       # energies
 *10000             # nr MD steps
 *5.0               # MD time step (in fs)
 *100               # output print frequency
 */

int main(argc, char **argv){
	mdsys_t sys:
	sys.natoms=atoi(3)
	sys.mass=atoi(39.948)
	sys.epsilon=atoi(0.2379)
	sys.sigma=atoi(3.405)
	sys.rcut=2.5
	sys.box=5.1964
	sys.nsteps=1000
	sys.dt=5.0

	/* allocate memory */
	sys.rx=(double *)malloc(sys.natoms*sizeof(double));
	sys.ry=(double *)malloc(sys.natoms*sizeof(double));
	sys.rz=(double *)malloc(sys.natoms*sizeof(double));
	
	sys.vx=(double *)malloc(sys.natoms*sizeof(double));
	sys.vy=(double *)malloc(sys.natoms*sizeof(double));
	sys.vz=(double *)malloc(sys.natoms*sizeof(double));
	
	sys.fx=(double *)malloc(sys.natoms*sizeof(double));
	sys.fy=(double *)malloc(sys.natoms*sizeof(double));
	sys.fz=(double *)malloc(sys.natoms*sizeof(double));


	sys.rx[0]=1.06574058650169;
        sys.ry[0]=-3.33432278188177;	
	sys.rz[0]=-2.59038677851747;

	sys.vx[0]=
	sys.vy[0]=
	sys.vz[0]=

	sys.rx[1]=4.19613239880890;
	sys.ry[1]=-4.97120493339350;
	sys.rz[1]=-4.97120493339350;

	sys.vx[1]=
	sys.vy[1]=
	sys.vz[1]=

	sys.rx[2]=6.18023614761844;
	sys.ry[2]=-14.4087233421704;
	sys.rz[2]=5.66497231845133;

	sys.vx[2]=
	sys.vy[2]=
	sys.vz[2]=

	for (i=0; i<sys.natoms; ++i) {
		fscanf(fp,"%lf%lf%lf",sys.vx+i, sys.vy+i, sys.vz+i);
	}

}

