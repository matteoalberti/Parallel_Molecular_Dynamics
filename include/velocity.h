#ifndef VELOCITY_H
#define VELOCITY_H
#include "compute_forces.h"
#include "md_struct.h"
#include "constants.h"

void velverlet(mdsys_t *sys);
void velverlet_step2(mdsys_t *sys);
void velverlet_step1(mdsys_t *sys);
#endif
