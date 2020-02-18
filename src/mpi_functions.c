#include "mpi_functions.h"
#include "md_struct.h"
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include "stdlib.h"

void initialize_mpi ( mdsys_t * sys ) {

#ifdef USE_MPI
//  int * argc_fake;
 // char *** argv_fake;
  MPI_Init(NULL,NULL);
  MPI_Comm_size( MPI_COMM_WORLD, &sys->nps );
  MPI_Comm_rank( MPI_COMM_WORLD, &sys->rank );
#else
  sys->rank = 0;
  sys->nps = 1;
#endif //USE_MPI

  return;

}

void allocate_cs ( mdsys_t * sys ) {
#ifdef USE_MPI
    sys->cx = (double *) malloc( sys->natoms * sizeof(double) );
	  sys->cy = (double *) malloc( sys->natoms * sizeof(double) );
	  sys->cz = (double *) malloc( sys->natoms * sizeof(double) );
#endif
}


void free_cs ( mdsys_t * sys ) {
#ifdef USE_MPI
    free( sys->cx );
    free( sys->cy );
    free( sys->cz );
#endif
}

void finalize_mpi () {
  
#ifdef USE_MPI
  MPI_Finalize();
#endif //USE_MPI

  return;  

}
