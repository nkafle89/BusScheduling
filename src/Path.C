#include "Path.h"
#include "sstream"
#include <iostream>

using namespace std;

Path::Path()
{
	_profit = 0;
	_reducedprofit = 0;
}

void Path::addRoute( Route* rtr )
{
	_path.push_back(rtr);
	incrProfit( rtr->getProfit() );
	incrReducedProfit( rtr->reducedCost() );
}

void Path::buildIncidenceRelation(Path* path)
{
	vector<Route*> allroutes = path->getPath();
	for (Route* rtr: allroutes)
	{
		rtr->presentInPath(path);
	}
}

ostream& operator<<(ostream& os, Path& path)
{
	vector<Route*> rtrs = path.getPath();
	os << "Path " << path.getId() << " Profit " << path.getProfit() << " Reduced Profit "
			<< path.getReducedProfit() << endl;
	for (Route* rtr: rtrs)
	{
		os<< *rtr;
	}
	//os << "Profit = " << path.getProfit() <<endl;
	return os;
}
