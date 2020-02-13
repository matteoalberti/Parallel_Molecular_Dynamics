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

int main(){
	mdsys_t sys;
	sys.natoms=3;
	sys.mass=39.948;
	sys.epsilon=0.2379;
	sys.sigma=3.405;
	sys.rcut=2.5;
	sys.box=5.1964;
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

	//Set position of atoms - first 2 atoms inside last one outside
	sys.rx[0]=1.06574058650169;
        sys.ry[0]=-3.33432278188177;	
	sys.rz[0]=-2.59038677851747;

	sys.vx[1]=1.5643224621482283e-03;
	sys.vy[1]=4.8497508563925346e-04;
	sys.vz[1]=-4.3352481732883966e-04;

	sys.rx[2]=4.19613239880890;
	sys.ry[2]=-4.97120493339350;
	sys.rz[2]=-4.97120493339350;

	//Set velocity of atoms
	sys.vx[0]=1.5417020528064903e-05;
	sys.vy[0]=1.7854479210267119e-05;
	sys.vz[0]=1.0061778727049613e-03;

	sys.rx[1]=6.18023614761844;
	sys.ry[1]=-14.4087233421704;
	sys.rz[1]=5.66497231845133;

	sys.vx[2]=-7.8119282252798756e-04;
	sys.vy[2]=8.0770620385540233e-04;
	sys.vz[2]=-1.4741616364769391e-04;

	//Execute 
	force(&sys);

	for (int i=0; i<sys.natoms; ++i) {
		printf("Ar  %20.8f %20.8f %20.8f %20.8f\n", sys.fx[i], sys.fy[i], sys.fz[i]);
	
	printf("Epot %20.8f\n", sys.epot);	
	}
}

