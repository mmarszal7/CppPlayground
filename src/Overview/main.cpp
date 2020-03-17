#include <stdio.h>

int runBasic();
int runAdvanced();
int runContainers();
int runAdvancedContainers();
int runFunctional();
int runPointers();
int runRegex();
int runThreads();

// Execution of code starts in the main function
// argc and argv is optional data that could be passed
// to the program if it was executed in a terminal
// argc : Number of arguments passed
// argv : Array pointers to strings
int main(int argc, char** argv)
{
	runBasic();
	//runAdvanced();
	//runContainers();
	//runAdvancedContainers();
	//runFunctional();
	//runPointers();
	//runRegex();
	//runThreads();

	return 0;
}