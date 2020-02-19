/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "compute_forces.h"
#include "helper.h"
#include "kinetic.h"
#include "output.h"
#include "velocity_step1.h"
#include "velocity_step2.h"
#include "md_struct.h"
#include "getline.h"
#include "read_input.h"
#include "mpi_functions.h"
#include "timer.h"

#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI

/* main */
int main()
{
    int nprint, i;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN];
    FILE *fp,*traj,*erg;
    double t_start, t_end;
    mdsys_t sys;

    //Initialize MPI
    initialize_mpi( &sys );

    //READING DATA and if MPI is definite Broadcast
    if (sys.rank==0){
    read_input(&sys, restfile, trajfile, ergfile, &nprint);}
    
#ifdef USE_MPI
    broadcast_values(&sys);
#endif //USE_MPI
    
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
#ifdef USE_MPI
    // only for mpi
    sys.cx = (double *) malloc( sys.natoms * sizeof(double) );
    sys.cy = (double *) malloc( sys.natoms * sizeof(double) );
    sys.cz = (double *) malloc( sys.natoms * sizeof(double) );
#endif //USE_MPI

    /* read restart */
    if (sys.rank==0){
    fp=fopen(restfile,"r");
    if(fp) {
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.rx+i, sys.ry+i, sys.rz+i);
        }
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.vx+i, sys.vy+i, sys.vz+i);
        }
        fclose(fp);
        azzero(sys.fx, sys.natoms);
        azzero(sys.fy, sys.natoms);
        azzero(sys.fz, sys.natoms);
    } else {
        perror("cannot read restart file");
        return 3;
    }
    }
    #ifdef USE_MPI
    broadcast_arrays(&sys);
    #endif

    /* initialize forces and energies.*/
    sys.nfi=0;
    force(&sys);
    if (sys.rank==0){
    ekin(&sys);
    }
    if ( sys.rank == 0 ) {
    erg=fopen(ergfile,"w");
    traj=fopen(trajfile,"w");

    printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
    printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");

    output(&sys, erg, traj); 
    }

    if(!sys.rank) t_start = timer_seconds(); 

    /**************************************************/
    /* main MD loop */
  //  nprint=1;

    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

        /* write output, if requested */
        if (( sys.rank == 0 ) && (sys.nfi % nprint) == 0)
            output(&sys, erg, traj);

        /* propagate system and recompute energies */
       
        if (sys.rank == 0){
          vel_step1(&sys);}
          
        force(&sys);
        
       if (sys.rank == 0){
        vel_step2(&sys);
        ekin(&sys);}
    }
    /**************************************************/

    if(!sys.rank) {
	t_end = timer_seconds(); 
	printf("Elapsed time %f \n",t_end - t_start);
    }

    /* clean up: close files, free memory */
    if ( sys.rank == 0 ) {
    printf("Simulation Done.\n");
    printf("Time to solution : %f\n", sys.t_elapsed_slow);
    fclose(erg);
    fclose(traj);
    }

    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
    #ifdef USE_MPI
    // free support
    free( sys.cx );
    free( sys.cy );
    free( sys.cz );
    #endif //USE_MPI


    finalize_mpi(&sys);

    return 0;
}
