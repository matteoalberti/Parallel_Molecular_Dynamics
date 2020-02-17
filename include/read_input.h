#ifndef READ_INPUT_H
#define READ_INPUT_H
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI

#include "md_struct.h"

void read_input(mdsys_t *sys, char* restfile, char* trajfile, char* ergfile, int* nprint);
void broadcast_values( mdsys_t * sys );
void broadcast_arrays( mdsys_t * sys );
#endif
