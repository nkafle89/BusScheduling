#include <iostream>
#include "Utils.h"
#include "AllEnv.h"
#include "Problem.h"
#include "Compare.h"
#include "BellManFord.h"
#include <future>
#include <fstream>
#include <chrono>

using namespace std;
using namespace operations_research;
using namespace std::chrono;

AllEnv* allenv;

int main(int argc, char* argv[])
{
	auto start = high_resolution_clock::now();
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

    if (false)
    {
		generateAllPaths();
		cout << allenv->getAllPaths().size() <<endl;
		allenv->createPathVariables();
		allenv->createRouteCovConstraint();
		allenv->createCapConstraint();
		allenv->setObj();
/*		for (int i= 0; i<allenv->getAllPaths().size(); ++i )
		{
			cout << *(allenv->getAllPaths().at(i)) <<endl;
		}*/

		//cout << *(allenv->getAllPaths().at(1319228)) <<endl;
		MPSolver* solver = allenv->getSolver();
		MPSolverParameters params;
		MPSolverParameters::IntegerParam iparms = MPSolverParameters::IntegerParam::LP_ALGORITHM;
		params.SetIntegerParam(iparms, MPSolverParameters::LpAlgorithmValues::PRIMAL);

		solver->Solve(params);
		cout << "Objective is "  << solver->MutableObjective()->Value() << endl;
		auto stop = high_resolution_clock::now();
		duration<double, milli> duration = stop - start;
		cout <<"Total Time from Start to End "<< duration.count() <<" ms." <<endl;
		string lpfile;
		solver->ExportModelAsLpFormat(false, &lpfile);
		ofstream file("./total.lp");
		exit(1);
    }

    ColumnGeneration();

    {
    	for (int i=0; i<allenv->getAllPaths().size(); ++i)
    	{
    		Path* path = allenv->getAllPaths().at(i);
    		cout << "Result is " <<path->getVar()->solution_value()<<endl;
    	}
    }

    auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"Total Time from Start to End "<< duration.count() <<" ms." <<endl;
}
