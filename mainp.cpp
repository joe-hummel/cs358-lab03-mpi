/*mainp.cpp*/

//
// Main MPI process that coordinates the prefix sum calculation.
//
// YOUR NAME
// Northwestern University
//

#include <iostream>
#include <mpi.h>

using namespace std;


// 
// mainp:
//
// Denotes the main process, with process id ("rank") of 0. The total # 
// of processes launches is given by numProcs. The main process is passed
// the array of N data values, which is sends out to the worker processes
// and eventually collects the results and stores them into array B. The
// main process also processes the first block of N/numProcs elements and
// computes the prefix sum for this block.
//
void mainp(int A[], int B[], int N, int numProcs)
{

}
