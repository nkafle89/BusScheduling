#include "Path.h"
#include "sstream"
#include <iostream>

using namespace std;

Path::Path(int id)
{
	_profit = 0;
	_id = id;
}

void Path::addRoute( Route* rtr )
{
	_path.push_back(rtr);
	incrProfit( rtr->getProfit() );
}

ostream& operator<<(ostream& os, Path& path)
{
	vector<Route*> rtrs = path.getPath();
	for (Route* rtr: rtrs)
	{
		os<< *rtr << "<=="<<endl;
	}
	os << "Profit = " << path.getProfit() <<endl;
	return os;
}
