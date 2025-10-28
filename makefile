build:
	rm -f a.out
	mpic++ main.cpp mainp.cpp workerp.cpp -Wno-write-strings 

run:
	mpiexec -n 4 a.out

run8:
	mpiexec -n 8 a.out

submit:
	/gradescope/gs submit 1130318 7060320 *.cpp

