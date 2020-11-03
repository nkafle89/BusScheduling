#include "Basic.h"
#include "AllEnv.h"
#include "Path.h"
#include "BellManFord.h"
#include <chrono>
using namespace std::chrono;
using namespace std;

void BellManFord::BellManFordSearch(vector<Route*>& allroutes, bool remove )
{
	bool doNextRound = true;
	int count = 0 ;
	while( doNextRound )
	{
		bool changes = false;
		for(Route* rtr : allroutes)
		{
			if( remove && rtr->visited() ) continue;

			vector<Route*> extndRoutes = rtr->GetExtendRoutes();
			for (Route* next : extndRoutes)
			{
				if( remove && next->visited() ) continue;

				double dv = rtr->spCost() - next->getProfit();
				if  (dv < next->spCost())
				{
					next->spCost(dv);
					next->setPreviousRoute(rtr);
					changes = true;
				}
			}
		}

		count++;

		if (!changes)
			doNextRound = false;

		if ( count > int(allroutes.size()))
			doNextRound = false;
	}

}


Path* BellManFord::backTrackPath(Route* dest)
{
	Path* path = new Path(_id++);

	Route* rtr = dest->getPreviousRoute();

	while (rtr->getPreviousRoute())
	{
		path->addRoute(rtr);
		rtr->visited(true);
		rtr->presentInPath(path);
		rtr = rtr->getPreviousRoute();
	}
	return path;
}


void BellManFord::resetRouteValues(vector<Route*>& allroutes, Route* source, bool visitedNode)
{
	for (Route* rtr: allroutes)
	{
		rtr->spCost(100000);
		rtr->setPreviousRoute(nullptr);
		if ( visitedNode ) rtr->visited(false);
	}
	source->spCost(0);
}


void BellManFord::getAllCoveringPaths()
{
	auto start = high_resolution_clock::now();
	cout<< "Starting to create Covering Paths" <<endl;
	vector<Route*> allrts = allenv->getAllRoutes();
	Route* source = allrts.front();
	Route* sink = allrts.back();

	int count = 0;
	int ith = 0;
	int toCover = int(allrts.size()-2);
	while (count < toCover )
	{
		BellManFordSearch(allrts, true);
		Path* path = backTrackPath( sink );
		count += path->getPath().size();
		allenv->AddPath(path);
		resetRouteValues(allrts, source);
		ith++;
	}
	resetRouteValues(allrts, source, true);
	
	auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"No of Paths Created "<< ith <<" execution time " << duration.count() <<" ms." <<endl;
}

