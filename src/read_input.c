#include <stdio.h>
#include <string.h>
#include <read_input.h>
#include <getline.h>
#include <stdlib.h>
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include "md_struct.h"

void read_input(mdsys_t *sys, char* restfile, char* trajfile, char* ergfile, int* nprint){
/* read input file */
    char line[BLEN];
    if ( sys->rank == 0 ) {    
		if(get_a_line(stdin,line)) exit(1);
		sys->natoms=atoi(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->mass=atof(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->epsilon=atof(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->sigma=atof(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->rcut=atof(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->box=atof(line);
		if(get_a_line(stdin,restfile)) exit(1);
		if(get_a_line(stdin,trajfile)) exit(1);
		if(get_a_line(stdin,ergfile)) exit(1);
		if(get_a_line(stdin,line)) exit(1);
		sys->nsteps=atoi(line);
		if(get_a_line(stdin,line)) exit(1);
		sys->dt=atof(line);
		if(get_a_line(stdin,line)) exit(1);
		*nprint=atoi(line);
    }    

}

void broadcast_values ( mdsys_t * sys ) {
//to disable compile warning
  sys->natoms=sys->natoms;
#ifdef USE_MPI
  /* Broadcasting from rank 0 to all what has been read */
  MPI_Bcast( &( sys->natoms ), 1, MPI_INT, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->mass ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->epsilon ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->sigma ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->rcut ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->box ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->nsteps ), 1, MPI_INT, 0, MPI_COMM_WORLD );
  MPI_Bcast( &( sys->dt ), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
#endif //USE_MPI

  return;

}

void broadcast_arrays ( mdsys_t * sys ) {
  //to disable compile warning
  sys->natoms=sys->natoms;
#ifdef USE_MPI
  /* Broadcasting from rank 0 to all what has been read */
  MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->vx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->vy, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->vz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
#endif //USE_MPI

  return;

}

