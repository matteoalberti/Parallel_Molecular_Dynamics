
deafult: all_py

all_c: test_input_c test_kinetic_c test_force_c

all_py: 
	cd .. && make clean
	cd .. && make shared
	python3 test_input.py < argon_108.inp	
	python3 test_force.py
	python3 test_kinetic.py

test_input_c: 
	make -f Makefile.test_input
	./test_input.x < argon_108.inp
	
test_kinetic_c:
	make -f Makefile.test_kinetic
	./test_kinetic.x
	
test_force_c:
	make -f Makefile.test_force
	./test_force.x

test_input:
	cd .. && make clean
	cd .. && make shared
	python3 test_input.py < argon_108.inp	
	
test_force:
	cd .. && make clean
	cd .. && make shared
	python3 test_force.py
	
test_kinetic:
	cd .. && make clean
	cd .. && make shared
	python3 test_kinetic.py
	
clean: 
	rm -rf *.o *.x *.so
