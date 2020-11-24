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
/*		string Pathfile;
		ofstream pfile("./allPaths");
		for (int i =0; i<allenv->getAllPaths().size(); ++i )
		{
			pfile<<*(allenv->getAllPaths().at(i))<<endl;
		}*/


		allenv->createPathVariables();
		allenv->createRouteCovConstraint();
		allenv->createCapConstraint();
		allenv->setObj();

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
		ofstream file("./tl.lp");
		file << lpfile;
		exit(1);
    }


    ColumnGeneration();

    auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"Total Time from Start to End "<< duration.count() <<" ms." <<endl;
}
