/*
compute kinetic energy for given velocities and mass
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "md_struct.h"
#include "kinetic.h"
#include "constants.h"


/* main */
int main()
{

    /* initialize mdsys structure */
    mdsys_t sys;
   
    /* counting variables */
    sys.natoms = 2;               // natoms
    sys.nfi=0;
    sys.nsteps = 10000;             // nr MD steps

    /* physical variables */
    sys.mass = 39.948;            // mass in AMU
    sys.epsilon = 0.2379;         // epsilon in kcal/mol
    sys.sigma = 3.405;            // sigma in angstrom
    sys.rcut = 8.5;               // rcut in angstrom
    sys.box = 17.1580;            // box length (in angstrom)
    sys.dt=5.0;                    // MD time step (in fs)

    /* allocate memory */
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));

    /* particle one */
    sys.vx[0] = 1e2;
    sys.vy[0] = 0.;
    sys.vz[0] = -1e2;

    /* particle two */
    sys.vx[1] = -1e2;
    sys.vy[1] = 0.;
    sys.vz[1] = 1e2;

    /* zero energy and forces */
    sys.epot=0.0;
    sys.ekin=0.0;

    ekin(&sys);

    printf("***Test unit for Kinetic Energy***\n");
    printf("Initial particle velocity: \n");

    printf("v1x=%f  v1y=%f  v1z=%f\n",sys.vx[0], sys.vy[0], sys.vz[0]); 
    printf("v2x=%.8f  v2y=%.8f  v2z=%.8f\n",sys.vx[1], sys.vy[1], sys.vz[1]); 

    printf("Initial Kinetic energy: ");
    printf(" %20.8f\n", sys.ekin);

    free(sys.vx);
    free(sys.vy);
    free(sys.vz);

return 0;

}
