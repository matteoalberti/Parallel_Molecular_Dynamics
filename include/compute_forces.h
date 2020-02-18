#ifndef COMPUTE_FORCES_H
#define COMPUTE_FORCES_H

#include "md_struct.h"
#include "helper.h"
#include "constants.h"

#if defined(_OPENMP)
#include <omp.h>
#endif

void force(mdsys_t *sys) ;

#endif
