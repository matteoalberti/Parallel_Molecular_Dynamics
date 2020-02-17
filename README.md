This package contains simplified MD code with multi-threading
parallelization for simulating atoms with a Lennard-Jones potential.

The bundled makefiles are set up to compile the executable once
with OpenMP disabled and once with OpenMP enabled with each build
placing the various object files in separate directories.

The examples directory contains 3 sets of example input decks
and the reference directory the corresponding outputs.
HI! 

### Usage instructions: 

!!! always `make clean` before anything

#### to use python: 

 - `make shared` to create shared libraries for serial version 
 - `make shared_mpi` to create shared libraries for mpi version 
 - `make shared_openmp` to create shared libraries for openmp version 
 - `make shared_mpi_openmp` to create shared libraries for mixed version
 
 Then the go to the `examples` folder (or any subfolder where you place `.inp` files) and run `pytho3 ../ljmd.py < INPUT_FILE` to execute.
 
#### to use non-python version:

 -  `make` -  will create the simplest possible executable (currently the default target)
 - `make mpi` -  the executable for shared_mpi
 - `make openmpi`  - the executable with `openmp` enabled
 - `make mpi_openmp` -  the executable with both `mpi` and `openmp` enabled
 
 Then go to the `examples` folder (or any subfolder where you place `.inp` files) and run `../ljmd.x < INPUT_FILE` to execute for non-mpi.
 
 
#### regression checks

For now only work for non-mpi:

  - `make check` to check python (after `make shared` or `make shared_openmp`)
  - `make check_c` to check c code (after `make` or `make openmp`)

 
 
 
