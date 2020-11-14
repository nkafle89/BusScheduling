#include "Route.h"
#include "sstream"
#include <iostream>
#include "Utils.h"

using namespace std;
using namespace boost::posix_time;

Route::Route(int id, string& origin, string& destination, string& busType, ptime& depDT,
                ptime& arrDT, string& profit, string& schType, int& day, bool isdepot)
{
    double prft;
    istringstream(profit) >> prft;

    _id =id;
    setOrigin(origin);
    setDest(destination);
    setBusType(busType);
    setDepDT(depDT);
    setArrDT(arrDT);
    setProfit(prft);
    setSchType(schType);
    setDay(day);
    isDepot(isdepot);

    _reducedCost = prft;
    _visited = false;
    _previous = nullptr;
    _spcost = (origin=="Origin") ? 0: 100000;
}


ostream& operator<<(ostream& os, Route& route)
{
	os << fixed << route.getId() << "  ";
	os << route.getDay() << "  ";
	os << route.getBusType() << "  ";
	os << route.getSchType() << "  ";
	os << route.getDepDT() << "  ";
	os << route.getArrDT() << "  ";
	os << route.getOrigin()<< "  ";
	os << route.getDest()<< "  ";
	//os << route.getProfit() << "  ";
	//os << route.spCost() << "  ";
	os << endl;

	return os;
}


