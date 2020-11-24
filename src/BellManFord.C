#include "Basic.h"
#include "AllEnv.h"
#include "Path.h"
#include "BellManFord.h"
#include <chrono>
#include <future>
//#include <execution>

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
				Relax( rtr, next, changes, remove );
			}
		}

		count++;

		if (!changes)
			doNextRound = false;

		if ( count > int(allroutes.size()))
			doNextRound = false;
	}

}


Path* BellManFord::backTrackPath(Route* dest, bool includeSink)
{
	Path* path = new Path();

	if (includeSink)
	{
		path->addRoute(dest);
		dest->visited(true);
	}

	Route* rtr = dest->getPreviousRoute();

	while (rtr->getPreviousRoute())
	{
		path->addRoute(rtr);
		rtr->visited(true);
		rtr = rtr->getPreviousRoute();
	}

	return path;
}

void BellManFord::resetRouteValues(vector<Route*>& allroutes, Route* source, bool visitedNode)
{
	for (Route* rtr: allroutes)
	{
		rtr->spCost(1000000);
		rtr->setPreviousRoute(nullptr);
		if ( visitedNode ) rtr->visited(false);
		if ( visitedNode ) rtr->reducedCost(rtr->getProfit());
	}
	source->spCost(0);
}


int BellManFord::getAllCoveringPaths()
{
	auto start = high_resolution_clock::now();
	cout<< "Starting to create Covering Paths" <<endl;
	vector<Route*> allrts = allenv->getAllRoutes();
	Route* source = allrts.front();
	Route* sink = allrts.back();

	int count = 0;
	int ith = 0;
	int oldid = _id;
	int toCover = int(allrts.size()-2);
	while (count < toCover )
	{
		BellManFordSearch(allrts, true);
		double capDual = allenv->getCapacityDual();
		Path* path = backTrackPath( sink, false );
		count += path->getPath().size();

		if ( (path->getReducedProfit() - capDual > 0) &&
				!allenv->doesPathExists(path) )
		{
			allenv->AddPath(path);
			path->setId(_id++);
			path->buildIncidenceRelation();
			resetRouteValues(allrts, source);
			ith++;
		}
		else
		{
			delete path;
		}
	}
	resetRouteValues(allrts, source, true);
	
	auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"No of Paths Created "<< ith <<" execution time " << duration.count() <<" ms." <<endl;
	return _id-oldid;
}


void BellManFord::Relax(Route* rtr, Route* next, bool& changes, bool& remove)
{
	if( remove && next->visited() ) return;
	double dv = rtr->spCost() - next->reducedCost();
	if  (dv < next->spCost())
	{
		next->spCost(dv);
		next->setPreviousRoute(rtr);
		changes = true;
	}
}


int BellManFord::getPositivePaths()
{
	int count =0 ;
	auto start = high_resolution_clock::now();
	cout<< "Starting BellManFord" <<endl;
	vector<Route*> allrts = allenv->getAllRoutes();
	Route* source = allrts.front();
	//Route* sink = allrts.back();

	BellManFordSearch(allrts, false);
	double capDual = allenv->getCapacityDual();
	//cout << "Cap Dual is " << capDual <<endl;
	for (Route* rtr: allrts)
	{
		if( rtr->isDepot() ) continue;

		Path* path = backTrackPath( rtr );
		if ( path->getReducedProfit() - capDual > 0 )
		{
			if (allenv->doesPathExists(path)) return count;

			allenv->AddPath(path);
			path->setId(_id++);
			path->buildIncidenceRelation();
			count++;
			//cout << *path <<endl;
		}
		else
		{
			delete path;
		}
	}
	resetRouteValues(allrts, source, true);
	auto stop = high_resolution_clock::now();
	duration<double, milli> duration = stop - start;
	cout <<"Get Positive Paths Execution time " << duration.count() <<" ms." <<endl;
	return count;
}

