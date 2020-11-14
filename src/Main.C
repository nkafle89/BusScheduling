#include <iostream>
#include "Utils.h"
#include "AllEnv.h"
#include "Problem.h"
#include "Compare.h"
#include "BellManFord.h"
#include <future>
#include <fstream>

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

    MPSolver solver("Problem", MPSolver::CLP_LINEAR_PROGRAMMING); //SCIP_MIXED_INTEGER_PROGRAMMING

    allenv = new AllEnv(&solver);
    
    InitializeScenario(argc, argv);
    ReadInputFiles();
    CreateExtendMap();
    cout<< "Solving Bus Routing problem..."<< endl;

    ColumnGeneration();
}
