#include "Path.h"
#include "sstream"
#include <iostream>

using namespace std;

Path::Path()
{
	_profit = 0;
	_reducedprofit = 0;
}

Path::Path(vector<Route*> routes)
{
	_profit = 0;
	_reducedprofit = 0;
	for(Route* rtr: routes)
	{
		addRoute(rtr);
	}
}

void Path::addRoute( Route* rtr )
{
	_path.push_back(rtr);
	incrProfit( rtr->getProfit() );
	incrReducedProfit( rtr->reducedCost() );
}

void Path::buildIncidenceRelation()
{
	vector<Route*> allroutes = this->getPath();
	for (Route* rtr: allroutes)
	{
		rtr->presentInPath(this);
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
