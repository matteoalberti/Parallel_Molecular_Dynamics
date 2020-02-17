#include "mpi_functions.h"
#include "md_struct.h"
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI

void initialize_mpi ( mdsys_t * sys ) {

#ifdef USE_MPI
  int * argc_fake;
  char *** argv_fake;
  MPI_Init( argc_fake, argv_fake );
  MPI_Comm_size( MPI_COMM_WORLD, &sys->nps );
  MPI_Comm_rank( MPI_COMM_WORLD, &sys->rank );
#else
  sys->rank = 0;
  sys->nps = 1;
#endif //USE_MPI

  return;

}

void finalize_mpi () {

#ifdef USE_MPI
  MPI_Finalize();
#endif //USE_MPI

  return;

}
