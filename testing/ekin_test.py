import mdsys_struct as md
import ctypes as ct

psys=md.mdsys()

psys.natoms = 2;             
psys.nfi=0;
psys.nsteps = 10000;      
psys.mass = 39.948;      
psys.epsilon = 0.2379;      
psys.sigma = 3.405;          
psys.rcut = 8.5;              
psys.box = 17.1580;          
psys.dt=5.0;                   


self.vx = (ct.c_double * self.natoms)()
    self.vy = (ct.c_double * self.natoms)()
    self.vz = (ct.c_double * self.natoms)()

double test_ekin;
long double eps = 1e-10;

    
 
    /* allocate memory */
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));


//*************************TEST1*************
    /* particle one */
    sys.vx[0] = 0.;
    sys.vy[0] = 0.;
    sys.vz[0] = 0.;

    /* particle two */
    sys.vx[1] = 0.;
    sys.vy[1] = 0.;
    sys.vz[1] = 0.;

    /* zero energy and forces */
    sys.epot=0.0;
    sys.ekin=0.0;

    /* Test value energy*/
    test_ekin = 0.;

    ekin(&sys);

    printf("\n***Test-1 unit for Kinetic Energy***\n");
    printf("Initial particle velocity:\n");

    printf("v1=(%.8f, %.8f, %.8f),\n",sys.vx[0], sys.vy[0], sys.vz[0]); 
    printf(" v2=(%.8f, %.8f, %.8f)\n",sys.vx[1], sys.vy[1], sys.vz[1]); 

    if((sys.ekin - test_ekin) <= eps) 
    printf("Test-1 on kinetic energy successful!\n");
    else
    printf("Test-1 on kinetic energy failed!\n");
//====================================================================
