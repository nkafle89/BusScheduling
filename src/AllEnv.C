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
		string name = "Coverage_Rtr_" + to_string(rtr->getId());
		LinearExpr pathSum;
		for (Path* path: rtr->presentInPath())
		{
			pathSum += path->getVar();
		}
		MPConstraint* row = solver->MakeRowConstraint(pathSum <= 1.0, name);
		rtr->setRow(row);
	}
}


void AllEnv::createPathVariables()
{
	MPSolver* solver = getSolver();
	for (Path* path: _allpaths)
	{
		if (!path->getVar())
		{
			string name = "X" + to_string(path->getId());
			MPVariable* const x = solver->MakeVar(0.0, 1, false, name);
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
	_capConst=solver->MakeRowConstraint(Caps <= 5.0, name);
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
