#ifndef KINETIC_ENERGY_H
#define KINETIC_ENERGY_H
#include "md_struct.h"
#include "constants.h"

#if defined(_OPENMP)
#include <omp.h>
#endif

void ekin(mdsys_t *sys);

#endif
