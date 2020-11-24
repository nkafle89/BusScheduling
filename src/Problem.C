#include "AllEnv.h"
#include "Basic.h"
#include "Problem.h"
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

void ColumnGeneration()
{
	BellManFord* bellman = allenv->getBellManFord();
	MPSolver* solver = allenv->getSolver();
	MPSolverParameters params;
	MPSolverParameters::IntegerParam iparms = MPSolverParameters::IntegerParam::LP_ALGORITHM;
	params.SetIntegerParam(iparms, MPSolverParameters::LpAlgorithmValues::PRIMAL);

	bool loopAgain = true;
	int loopCount = 0;
	while (loopAgain && loopCount <=50)
	{
		loopCount++;
		int added = 0;
		if (loopCount==1)
		{
			added = bellman->getAllCoveringPaths();
		}
		else
		{
			added = bellman->getAllCoveringPaths();
			//added = bellman->getPositivePaths();
		}

		cout << "Added " << added << " routes." << endl;
		if (added)
		{
			solver->Clear();
			auto start = high_resolution_clock::now();
			allenv->createPathVariables();

			allenv->createRouteCovConstraint();
			allenv->createCapConstraint();
			allenv->setObj();
			auto stop = high_resolution_clock::now();
			duration<double, milli> duration = stop - start;
			cout <<"Writing LP took "<< duration.count() <<" ms." <<endl;

			solver->Solve(params);

			auto stop2 = high_resolution_clock::now();
			duration = stop2 - stop;
			cout <<"Solving LP took "<< duration.count() <<" ms." <<endl;

			string lpfile;
			solver->ExportModelAsLpFormat(false, &lpfile);

			ofstream file("./filename.lp");

			file << lpfile;

			allenv->setCapcaityDual( allenv->getCapConst()->dual_value() );

			std::vector<Route*>  allroutes = allenv->getAllRoutes();
			for (Route* rtr: allroutes)
			{
				if (rtr->getRow())
				{
					double dual = rtr->getRow()->dual_value();
					//cout << "Dual " << dual <<endl;
					if(dual>0.01)
					{
						rtr->reducedCost(rtr->getProfit()- dual);
						//cout << "Dual " << dual <<endl;
					}
				}
			}
		}
		else
		{
			loopAgain = false;
		}
		cout << "CG loop count "<< loopCount;
		cout << " Objective is "  << solver->MutableObjective()->Value() << endl;
	}
}


void generateAllPaths() //only good for 1 day problem
{
	auto start = high_resolution_clock::now();
	cout<< "Starting to generate all paths" <<endl;

	map<const int, vector<vector<Route*>> > lengthPathMap;

	int id =0;
	for(Route* rtr : allenv->getAllRoutes())
	{
		if (rtr->isDepot()) continue;
		vector<Route*> path_i{ rtr };
		Path* path = new Path(path_i);
		path->setId(id++);
		path->buildIncidenceRelation();
		lengthPathMap[0].push_back(path_i);
		allenv->AddPath(path);
	}

	for (int i = 1; i< 10 ; ++i)
	{
		for (vector<Route*> path:lengthPathMap[i-1])
		{
			Route* last = path.back();

			vector<Route*> canextd = last->GetExtendRoutes();

			for (Route* rtr: canextd)
			{
				if (!rtr->isDepot())
				{
					vector<Route*> path2 = path;
					path2.push_back(rtr);
					Path* newPath = new Path(path2);
					newPath->setId(id++);
					newPath->buildIncidenceRelation();
					allenv->AddPath(newPath);
					lengthPathMap[i].push_back(path2);
					//cout<<*newPath<<endl;
				}
			}
		}
	}

	auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"No of Paths Created "<< allenv->getAllPaths().size() <<
			" execution time " << duration.count() <<" ms." <<endl;
}

