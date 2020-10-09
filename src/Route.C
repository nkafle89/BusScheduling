#include "Route.h"
#include "sstream"
#include <iostream>


Route::Route(string& origin, string& destination, string& busType, ptime& depDT, 
                ptime& arrDT, string& profit, string& schType) 
{
    double prft;
    istringstream(profit) >> prft;

    setOrigin(origin);
    setDest(destination);
    setBusType(busType);
    setDepDT(depDT);
    setArrDT(arrDT);
    setProfit(prft);
    setSchType(schType);
}
