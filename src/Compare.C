#include "Compare.h"

bool CompareRoutesByDayTypeShift( Route* rt1, Route* rt2)
{ //This is wrong. rewrite being more explicit

	if (rt1->getDay() < rt2->getDay()) return true;
	if (rt2->getDay() < rt1->getDay()) return false;

	if (rt1->getBusType() < rt2->getBusType()) return true;
	if (rt2->getBusType() < rt1->getBusType()) return false;

	if (rt1->getSchType() < rt2->getSchType() ) return true;
	if (rt2->getSchType() < rt1->getSchType() ) return false;

	if (rt1->getDepDT() < rt2->getDepDT()) return true;
	if (rt2->getDepDT() < rt1->getDepDT()) return false;

	if (rt1->getOrigin() < rt2->getOrigin()) return true;
	if (rt2->getOrigin() < rt1->getOrigin()) return false;

	if (rt1->getDest() < rt2->getDest()) return true;
	if (rt2->getDest() < rt1->getDest()) return false;

	if (rt1->getArrDT() < rt2->getArrDT()) return true;
	if (rt2->getArrDT() < rt1->getArrDT()) return false;

	return false;
}


bool CompareBySPCost(Route* rt1, Route* rt2)
{
	return (rt1->spCost() < rt2->spCost());
}
