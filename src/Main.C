#include <iostream>
#include "Utils.h"
#include "AllEnv.h"
#include "Problem.h"
#include "Compare.h"
#include "BellManFord.h"
using namespace std;
using namespace operations_research;

AllEnv* allenv;

int main(int argc, char* argv[])
{
    cout<<"No of args "<<argc<< endl;

    for (int i=0; i<argc; ++i)
    {
        cout<< i << " th arg is: " << argv[i] << endl;
    }

    MPSolver solver("Problem", MPSolver::SCIP_MIXED_INTEGER_PROGRAMMING);
    allenv = new AllEnv(&solver);
    
    InitializeScenario(argc, argv);
    ReadInputFiles();
    CreateExtendMap();

    BellManFord* bellman = new BellManFord;
    bellman->getAllCoveringPaths();

    vector<Path*> allp = allenv->getAllPaths();

    for (Path* path : allp)
    {
    	cout << "Path ID "<< path->getId() <<endl;
    }

	operations_research::BuildandSolveMIP();
    cout<< "Solving Bus Routing problem..."<< endl;
}
