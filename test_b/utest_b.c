/*
 * Unit test B
 * b) compute one full step time integration for given forces and velocities (no call to force())
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "compute_forces.h"
#include "helper.h"
#include "kinetic.h"
#include "output.h"
#include "velocity.h"
#include "md_struct.h"
#include "getline.h"

/* main */
int main()
{
mdsys_t sys;

double tol_test    =  1e-7;
int    natoms_test =  3;
double mdt_test    =  10;
double mass_test   =  1;
double sigma_test  =  1;
double eps_test    =  0.1;
double rcut_test   =  5;
double box_test    =  20;


double vx_test, vy_test, vz_test;
double fx_test, fy_test, fz_test;
double rx_test, ry_test, rz_test;
double ffac_test, r_test;

 /* read input file */
    sys.natoms  = natoms_test;
    sys.mass    = mass_test;
    sys.epsilon = eps_test;
    sys.sigma   = sigma_test;
    sys.rcut    = rcut_test;
    sys.box     = box_test ;
/*  
    if(get_a_line(stdin,restfile)) return 1;
    if(get_a_line(stdin,trajfile)) return 1;
    if(get_a_line(stdin,ergfile)) return 1;
*/ 
    sys.nsteps=1000;
    sys.dt=5;
    int nprint=100;





    sys.rx=(double *)malloc(natoms_test*sizeof(double));
    sys.ry=(double *)malloc(natoms_test*sizeof(double));
    sys.rz=(double *)malloc(natoms_test*sizeof(double));
    sys.vx=(double *)malloc(natoms_test*sizeof(double));
    sys.vy=(double *)malloc(natoms_test*sizeof(double));
    sys.vz=(double *)malloc(natoms_test*sizeof(double));
    sys.fx=(double *)malloc(natoms_test*sizeof(double));
    sys.fy=(double *)malloc(natoms_test*sizeof(double));
    sys.fz=(double *)malloc(natoms_test*sizeof(double));

double rx_inp_out = {1, 1, 29.19613239880890};
double ry_inp_out = {1, 1, -30.97120493339350};
double rz_inp_out = {1, 4.405, -17.97120493339350};

double rx_inp_in = {1, 1, 2.19613239880890};
double ry_inp_in = {1, 1, -3.97120493339350};
double rz_inp_in = {1, 4.405, -4.97120493339350};

for (int i=0; i<natoms_test; ++i) {

fx_test = 0;
fy_test = 0;
fz_test = 0;

vx_test = 0;
vy_test = 0;
vz_test = 0;

sys.fx[i] = 0;
sys.fy[i] = 0;
sys.fz[i] = 0;

sys.vx[i] = 0;
sys.vy[i] = 0;
sys.vz[i] = 0;


rx_test = rx_inp_out[i];
ry_test = ry_inp_out[i];
rz_test = rz_inp_out[i];

sys.rx[i] = rx_inp_out[i];
sys.ry[i] = ry_inp_out[i];
sys.rz[i] = rz_inp_out[i];

rx_test += mdt_test  * vx_test;
ry_test += mdt_test  * vy_test;
rz_test += mdt_test  * vz_test;

r_test = sqrt(rx_test * rx_test + ry_test * ry_test + rz_test * rz_test);

ffac_test = - 0.4 * eps_test / r_test * (-12.0 * pow(sigma_test/r_test,12.0) + 6 * pow(sigma_test/r_test,6.0));


fx_test = ffac_test * rx_test/r_test;
fy_test = ffac_test * ry_test/r_test;
fz_test = ffac_test * rz_test/r_test;

vx_test = mdt_test  * fx_test/ mass_test * mvsq2e;
vy_test = mdt_test  * fy_test/ mass_test * mvsq2e;
vz_test = mdt_test  * fz_test/ mass_test * mvsq2e;

 velverlet(&sys);

    if  ( fabs( sys.vx[i] - vx_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.vx[i], vx_test);

    if  ( fabs( sys.vy[i] - vy_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.vy[i], vy_test);

    if  ( fabs( sys.vz[i] - vz_test )  > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.vz[i], vz_test);


    if  ( fabs( sys.rx[i] - rx_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.rx[i], rx_test);

    if  ( fabs( sys.ry[i] - ry_test )  > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.ry[i], ry_test);

    if  ( fabs( sys.rz[i] - rz_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, sys.rz[i], rz_test);



/*PART TO COMPARE FORCES WITHOUT CALLING FOR FORCE() FUNCTION*/

double r_e = sqrt(sys.rx[i] * sys.rx[i] + sys.ry[i] * sys.ry[i] + sys.rz[i] * sys.rz[i]);


double ffac_e = -4.0*sys.epsilon*(-12.0*pow(sys.sigma/r_e,12.0)/r_e
                                         +6*pow(sys.sigma/r_e,6.0)/r_e);

double fx_e, fy_e, fz_e;
fx_e = 0;
fy_e = 0;
fz_e = 0;

fx_e = ffac_e * sys.rx[i] / r_e;
fy_e = ffac_e * sys.ry[i] / r_e;
fz_e = ffac_e * sys.rz[i] / r_e;

velverlet_step2(&sys);

    if  ( fabs( fx_e - fx_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, fx_e, fx_test);

    if  ( fabs( fy_e - fy_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, fy_e, fy_test);

    if  ( fabs( fz_e - fz_test ) > tol_test)
    printf("Calculation ERROE:  for %d particle.\nExpected %f \n Get %f", i, fz_e, fz_test);


    }

  /**********************NATA_B****************************/


}
