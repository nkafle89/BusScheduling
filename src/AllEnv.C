#include "AllEnv.h"
#include "Compare.h"

using namespace std;
using namespace operations_research;

void AllEnv::createRouteCovConstraint()
{
	MPSolver* solver = getSolver();
	for(Route* rtr: _allRoutes)
	{
		if (rtr->isDepot()) continue;

		//if (!rtr->getRow())
		{
			string name = "Coverage_Rtr_" + to_string(rtr->getId());
			LinearExpr pathSum;
			for (Path* path: rtr->presentInPath())
			{
				//cout << *path <<endl;
				pathSum += path->getVar();
			}
			//cout << pathSum <<endl;
			MPConstraint* row = solver->MakeRowConstraint(pathSum <= 1.0, name);
			rtr->setRow(row);
		}
	}
}


void AllEnv::createPathVariables()
{
	MPSolver* solver = getSolver();
	for (Path* path: _allpaths)
	{
		//if (!path->getVar())
		{
			string name = "X" + to_string(path->getId());
			MPVariable* const x = solver->MakeNumVar(0.0, solver->infinity(), name);
			path->setVar(x);
		}
	}
}

void AllEnv::createCapConstraint()
{
	MPSolver* solver = getSolver();
	string name = "CapConst";
	LinearExpr Caps;
	for (Path* path: _allpaths)
	{
		Caps += path->getVar();
	}
	_capConst=solver->MakeRowConstraint(Caps <= 300.0, name);
}

void AllEnv::setObj()
{
	MPSolver* solver = getSolver();
	MPObjective* const objective = solver->MutableObjective();
	for (Path* path: _allpaths)
	{
		objective->SetCoefficient(path->getVar(), path->getProfit());
	}
	objective->SetMaximization();
}

bool AllEnv::doesPathExists(Path* path)
{
	int sz = path->getPath().size();
	double profit = path->getProfit();

	auto it = _profitPathMap.equal_range(profit);

	for (auto itr = it.first; itr != it.second; ++itr)
	{
		if ( sz == int(itr->second->getPath().size()) )
		{
			if ( itr->second->getPath() == path->getPath() )
				return true;
		}
	}
	_profitPathMap.insert({ profit , path });
	return false;
}

BellManFord* AllEnv::getBellManFord()
{
	if (_bellman)
	{
		return _bellman;
	}
	else
	{
		_bellman = new BellManFord;
		return _bellman;
	}
}
