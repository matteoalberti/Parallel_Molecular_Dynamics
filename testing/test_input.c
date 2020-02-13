#include <stdio.h>
#include <string.h>
#include "md_struct.h"
#include "read_input.h"
#include "math.h"
#include <string.h>

int main(){
/*
 The input file to test on will be 
argon_108.inp :
108               # natoms
39.948            # mass in AMU
0.2379            # epsilon in kcal/mol
3.405             # sigma in angstrom
8.5               # rcut in angstrom
17.1580           # box length (in angstrom)
argon_108.rest    # restart
argon_108.xyz     # trajectory
argon_108.dat     # energies
10000             # nr MD steps
5.0               # MD time step (in fs)
100               # output print frequency
*/
int nprint;
char restfile[14], trajfile[13], ergfile[13];

mdsys_t sys;

read_input(&sys, restfile, trajfile, ergfile, &nprint);
char  str1[14] ="argon_108.rest";
char  str2[13]="argon_108.xyz";
char  str3[13]="argon_108.dat";

if (sys.natoms != 108 ) { printf(" The read input function has failed at atoms number\n"); return 1;};
if (fabs(sys.mass- 39.948)> 1e-15) { printf("The read input function has failed at mass\n"); return 1;};
if (fabs(sys.epsilon - 0.2379)> 1e-15) { printf("The read input function has failed at epsilon\n"); return 1;};
if (fabs(sys.sigma - 3.405)> 1e-15) { printf("The read input function has failed at sigma \n"); return 1;};
if (fabs(sys.rcut - 8.5)> 1e-15) { printf("The read input function has failed\n"); return 1;};
if (fabs(sys.box - 17.1580)> 1e-15) { printf("The read input function has failed at box\n"); return 1;};
if (sys.nsteps!=10000) { printf("The read input function has failed at steps number\n"); return 1;};
if (fabs(sys.dt-5.0)>1e-15) { printf("The read input function has failed at time step\n"); return 1;};
if ( nprint != 100) { printf("The read input function has failed at nprint\n"); return 1;};
if (!strcmp(restfile, str1)) { printf("The read input function has failed at first filename\n"); return 1;};
if (!strcmp(trajfile, str2)) { printf("The read input function has failed at second filename\n"); return 1;};
if (!strcmp(ergfile, str3)) { printf("The read input function has failed at 3rd filename\n"); return 1;};

printf("The read input function works correctly\n"); 

return 0;

}
