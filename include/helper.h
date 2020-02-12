#ifndef HELPER_FUNCTION_H
#define HELPER_FUNCTION_H
#include "md_struct.h"
#include "constants.h"

static int get_a_line(FILE *fp, char *buf);
static void azzero(double *d, const int n);
static double pbc(double x, const double boxby2);

#endif
