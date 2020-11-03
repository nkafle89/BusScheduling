#include "AllEnv.h"
#include "Compare.h"

using namespace std;
using namespace operations_research;

void AllEnv::createRouteCovConstraint()
{
	MPSolver* solver = getSolver();
	for(Route* rtr: _allRoutes)
	{
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
			MPVariable* const x = solver->MakeNumVar(0.0, 1, name);
			path->setVar(x);
		}
	}

}
