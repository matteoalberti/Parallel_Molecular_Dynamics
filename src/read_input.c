#include <stdio.h>
#include <string.h>
#include <read_input.h>
#include <getline.h>
#include <stdlib.h>
#include <stdlib.h>


void read_input(mdsys_t *sys, char* restfile, char* trajfile, char* ergfile, int* nprint){
/* read input file */
    char line[BLEN];
    
    if(get_a_line(stdin,line)) exit(1);
    sys->natoms=atoi(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->mass=atof(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->epsilon=atof(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->sigma=atof(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->rcut=atof(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->box=atof(line);
    if(get_a_line(stdin,restfile)) exit(1);
    if(get_a_line(stdin,trajfile)) exit(1);
    if(get_a_line(stdin,ergfile)) exit(1);
    if(get_a_line(stdin,line)) exit(1);
    sys->nsteps=atoi(line);
    if(get_a_line(stdin,line)) exit(1);
    sys->dt=atof(line);
    if(get_a_line(stdin,line)) exit(1);
    *nprint=atoi(line);
    
}
