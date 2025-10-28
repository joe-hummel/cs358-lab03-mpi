/*main.cpp*/

//
// MPI program to compute prefix sum from a file of integers, writing
// the results to an output file.
//
// YOUR NAME
// Northwestern University
//

#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>

using namespace std;


// 
// function prototypes:
// 
void mainp(int A[], int B[], int N, int numProcs);  /*mainp.cpp*/
void workerp(int myRank, int numProcs);    /*workerp.cpp*/

bool getFilenames(int argc, char* argv[], string& inputfile, string& outputfile);
int* readData(string inputfile, int& N, int numProcs);
void writeData(string outputfile, int A[], int N);


//
// main:
// 
int main(int argc, char* argv[])
{
  int myRank, numProcs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  if (myRank == 0) { 
    //
    // main process:
    //
    string inputfile, outputfile;

    if (!getFilenames(argc, argv, inputfile, outputfile))
      return 0;

    int  N;
    int* A = readData(inputfile, N, numProcs);

    if (A == nullptr) {
      cout << "**ERROR: unable to open input file '" << inputfile << "'" << endl;
      return 0;
    }

    int* B = new int[N];

    mainp(A, B, N, numProcs);

    writeData(outputfile, B, N);

    delete[] A;
    delete[] B;
  }
  else { 
    //
    // worker processes:
    //
    workerp(myRank, numProcs);
  }

  MPI_Finalize();
  return 0;
}


//
// readData
//
// Reads the data from the given input file, where the first
// line is assumed to be the value N. N is then adjusted to
// be evenly-divisible by numProcs. A pointer to an array 
// containing the N values is returned.
//
// If the file cannot be opened, nullptr is returned.
// 
int* readData(string inputfile, int& N, int numProcs)
{
  ifstream infile;
  infile.open(inputfile);
  if (infile.fail())
    return nullptr;

  cout << "**Reading from '" << inputfile << "'..." << endl;

  // first line is N:
  infile >> N;

  //
  // make sure N is evenly divisible by numProcs:
  // 
  int rem = N % numProcs;
  if (rem > 0)
    N = N - rem;

  cout << "  N: " << N << endl;

  //
  // allocate array and read N values:
  //
  int* A = new int[N];
  
  for (int i=0; i<N; i++)
    infile >> A[i];

  //
  // for debugging purposes, output first and last 3 values:
  //
  cout << "  " 
       << A[0] << ", "
       << A[1] << ", "
       << A[2] << ", ..., "
       << A[N-3] << ", " 
       << A[N-2] << ", " 
       << A[N-1] << endl;

  return A;
}


//
// writeData
//
// Writes the N values in the array to the given output file.
//
void writeData(string outputfile, int B[], int N)
{
  cout << "**Writing to '" << outputfile << "'..." << endl;
}


//
// getFilenames
//
// Looks at the command-line arguments, and if there are 2 present, assumes
// these denote the input and output filenames. If no command-line args are
// present, the filenames are set to "input.txt" and "output.txt". Returns
// true if successful, false if the # of command-line args is incorrect.
//
bool getFilenames(int argc, char* argv[], string& inputfile, string& outputfile)
{
  
  if (argc == 3) { // passed filenames
    inputfile = string(argv[1]);
    outputfile = string(argv[2]);
  }
  else if (argc == 1) {
    inputfile = "input.txt";
    outputfile = "output.txt";
  }
  else {
    cout << "**ERROR: invalid number of command-line arguments" << endl;
    cout << "**USAGE: a.out [inputfilename outputfilename]" << endl;
    return false;
  }

  return true;
}

