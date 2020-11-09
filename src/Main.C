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
    MPSolverParameters params;
    MPSolverParameters::IntegerParam iparms = MPSolverParameters::IntegerParam::LP_ALGORITHM;
    params.SetIntegerParam(iparms, MPSolverParameters::LpAlgorithmValues::PRIMAL);

    allenv = new AllEnv(&solver);
    
    InitializeScenario(argc, argv);
    ReadInputFiles();
    CreateExtendMap();


    BellManFord* bellman = new BellManFord;
    bellman->getPositivePaths();
    		//getAllCoveringPaths();

    allenv->createPathVariables();
    allenv->createRouteCovConstraint();
    allenv->createCapConstraint();
    allenv->setObj();

    const MPSolver::ResultStatus result_status = solver.Solve(params);

    cout << result_status <<endl;
    cout << "Objective Value " << allenv->getSolver()->MutableObjective()->Value() <<endl;
    string lpfile;
    allenv->getSolver()->ExportModelAsLpFormat(false, &lpfile);

    ofstream file("./filename.lp");

    file << lpfile;

    vector<Path*> allp = allenv->getAllPaths();

    for (Path* path : allp)
    {
    	if (path->getVar()->solution_value()>0.01)
    	{
    		cout << "Solution Value is " << path->getVar()->solution_value() <<endl;
    		cout<< *path<<endl;
    		cout << path->getId()<< ","<< path->getProfit()<< "   ";
    		cout << path->getId() << " RC " << path->getVar()->reduced_cost() << endl;
    	}
    }

    for (Route* rtr: allenv->getAllRoutes())
    {
    	if (rtr->getRow())
    	{
			if(rtr->getRow()->dual_value()>0.01)
				cout << "Dual Vars "<< rtr->getId() <<" " << rtr->getRow()->dual_value() <<endl;
    	}
    }

    cout << "Dual Vars Cap "<< allenv->getCapConst()->dual_value()<<endl;


	//operations_research::BuildandSolveMIP();
    cout<< "Solving Bus Routing problem..."<< endl;
}
