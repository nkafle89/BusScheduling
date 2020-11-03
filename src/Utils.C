#include <fstream>
#include <iostream>
#include "AllEnv.h"
#include "Basic.h"
#include "Utils.h"
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Compare.h"
#include <chrono>

using namespace boost::posix_time;
using namespace std;

void InitializeScenario(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Specify scenario dir" << std::endl;
    }
    allenv->ScenarioDir(argv[1]);
    
    cout<<"Setting Scenario dir to be: "<<allenv->ScenarioDir() <<endl;
};

void CreateExtendMap()
{
	auto start = chrono::high_resolution_clock::now();
	cout<<"Creating Extend Map..."<<endl;
    int num = allenv->NumRoutes();
    for(int i=0; i<num; i++)
    {
        Route* route1 = allenv->getRoute(i);
        for (int j=0; j<num; j++)
        {
            Route* route2 = allenv->getRoute(j);

            if (isCompatible(route1, route2))
            {
                route1->canExtend(route2);
            }
        }
    }

	auto stop = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> duration = stop - start;
	cout<<"End of Creating Extend Map... "<< duration.count() << " ms" << endl;
};

bool isCompatible(Route* route1, Route* route2)
{
	if(route1->isDepot() && route1->getOrigin() == "Origin"
			&& ( ! route2->isDepot() ) )
	{
		return true;
	}

	if (route2->isDepot() && route2->getOrigin() == "Destination"
			&& ( ! route1->isDepot() ) )
	{
		return true;
	}

    if (route2->getOrigin() == route1->getDest() && route1->getBusType() == route2->getBusType() )
    {
        time_duration minGT = time_duration(hours(1));
        time_duration maxGT = time_duration(hours(30));
        if ( (route2->getDepDT() >= route1->getArrDT() + minGT) &&
        		(route2->getDepDT() <= route1->getArrDT() + maxGT) )
        {
            return true;
        }
    }
    return false;
};


