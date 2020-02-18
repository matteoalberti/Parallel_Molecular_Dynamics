#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "compute_forces.h"
#include "helper.h"

#include "constants.h"

/* compute forces */
void force(mdsys_t *sys)
{
    double rsq,rcsq,ffac;
    double rx,ry,rz;
    int i;

    /* zero energy and forces */
    sys->epot=0.0;
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    double c12  =  4.0*sys->epsilon*pow(sys->sigma,12.0);
    double c6   = -4.0*sys->epsilon*pow(sys->sigma,6.0);
    rcsq =   sys->rcut * sys->rcut;

    for(i=0; i < (sys->natoms)-1; ++i) {
        for(int j=i+1; j < sys->natoms; ++j) {
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            /* particles have no interactions with themselves */
        /*    if (i==j) continue;
 *                */
            rsq = rx*rx + ry*ry + rz*rz;

            /* compute force and energy if within cutoff */
            if (rsq < rcsq) {
                double r6, rinv;
                rinv = 1.0/rsq;
                r6   = rinv*rinv*rinv;
                ffac = (c12*12.0*r6 + 6.0*c6)*r6*rinv;

                sys->epot  += r6*(c12*r6 + c6) ;

                sys->fx[i] += rx*ffac;
                sys->fy[i] += ry*ffac;
                sys->fz[i] += rz*ffac;

                sys->fx[j] -= rx*ffac;
                sys->fy[j] -= ry*ffac;
                sys->fz[j] -= rz*ffac;

            }
        }
    }
}

