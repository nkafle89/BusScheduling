#include "AllEnv.h"
#include "Basic.h"
#include "Problem.h"


void ColumnGeneration()
{
	BellManFord* bellman = allenv->getBellManFord();
	MPSolver* solver = allenv->getSolver();
	MPSolverParameters params;
	MPSolverParameters::IntegerParam iparms = MPSolverParameters::IntegerParam::LP_ALGORITHM;
	params.SetIntegerParam(iparms, MPSolverParameters::LpAlgorithmValues::BARRIER);

	bool loopAgain = true;
	while (loopAgain)
	{
		int added = bellman->getPositivePaths();
		if (added)
		{
			allenv->createPathVariables();
			allenv->createRouteCovConstraint();
			allenv->createCapConstraint();
			allenv->setObj();

			solver->Solve(params);

			std::vector<Route*>  allroutes = allenv->getAllRoutes();
			for (Route* rtr: allroutes)
			{
				if (rtr->getRow())
				{
					double dual = rtr->getRow()->dual_value();
					if(dual>0.01) rtr->reducedCost(rtr->getProfit()- dual);
				}
			}
		}
		else
		{
			loopAgain = false;
		}
	}
}
