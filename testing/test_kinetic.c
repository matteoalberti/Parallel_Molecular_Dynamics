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
    double test_ekin;

    /* precision parameter */
    long double eps = 1e-10;

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


//*************************TEST1*************
    /* particle one */
    sys.vx[0] = 0.;
    sys.vy[0] = 0.;
    sys.vz[0] = 0.;

    /* particle two */
    sys.vx[1] = 0.;
    sys.vy[1] = 0.;
    sys.vz[1] = 0.;

    /* zero energy and forces */
    sys.epot=0.0;
    sys.ekin=0.0;

    /* Test value energy*/
    test_ekin = 0.;

    ekin(&sys);

    printf("\n***Test-1 unit for Kinetic Energy***\n");
    printf("Initial particle velocity:\n");

    printf("v1=(%.8f, %.8f, %.8f),\n",sys.vx[0], sys.vy[0], sys.vz[0]); 
    printf(" v2=(%.8f, %.8f, %.8f)\n",sys.vx[1], sys.vy[1], sys.vz[1]); 

    if((sys.ekin - test_ekin) <= eps) 
    printf("Test-1 on kinetic energy successful!\n");
    else{
      printf("Test-1 on kinetic energy failed!\n");
      exit(1);
    };
//====================================================================

//*************************TEST2*************
    /* particle one */
    sys.vx[0] = 1.;
    sys.vy[0] = 1.;
    sys.vz[0] = 1.;

    /* particle two */
    sys.vx[1] = 0.;
    sys.vy[1] = 0.;
    sys.vz[1] = 0.;

    /* zero energy and forces */
    sys.epot=0.0;
    sys.ekin=0.0;

    /* Test value energy*/
    test_ekin = 143217.01721781;

    ekin(&sys);

    printf("\n***Test-2 unit for Kinetic Energy***\n");
    printf("Initial particle velocity:\n");

    printf("v1=(%.8f, %.8f, %.8f),\n",sys.vx[0], sys.vy[0], sys.vz[0]); 
    printf(" v2=(%.8f, %.8f, %.8f)\n",sys.vx[1], sys.vy[1], sys.vz[1]); 

    if((sys.ekin - test_ekin) <= eps) 
    printf("Test-2 on kinetic energy successful!\n");
    else{
      printf("Test-2 on kinetic energy failed!\n");
      exit(1);
    };
//====================================================================
//*************************TEST3*************
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

    /* Test value energy*/
    test_ekin = 1909560229.57079720;

    ekin(&sys);

    printf("\n***Test-3 unit for Kinetic Energy***\n");
    printf("Initial particle velocity:\n");

    printf("v1=(%.8f, %.8f, %.8f),\n",sys.vx[0], sys.vy[0], sys.vz[0]); 
    printf(" v2=(%.8f, %.8f, %.8f)\n",sys.vx[1], sys.vy[1], sys.vz[1]); 

    if((sys.ekin - test_ekin) <= eps) 
    printf("Test-3 on kinetic energy successful!\n");
    else{
      printf("Test-3 on kinetic energy failed!\n");
      exit(1);
    };
//====================================================================

    free(sys.vx);
    free(sys.vy);
    free(sys.vz);

return 0;

}
