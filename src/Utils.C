#include <fstream>
#include <iostream>
#include "AllEnv.h"
#include "Basic.h"
#include "Utils.h"
#include <boost/date_time/local_time/local_time.hpp>


void InitializeScenario(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Specify scenario dir" << std::endl;
    }
    allenv->ScenarioDir(argv[1]);
    
    cout<<"Setting Scenario Dir to be: "<<allenv->ScenarioDir() <<endl;
};


void CreatePaths()
{
    
};

void CreateExtendMap()
{
    int num = allenv->NumRoutes();
    for(int i=0; i<num; i++)
    {
        Route* route1 = allenv->getRoute(i);
        for (int j=0; j<num; j++)
        {
            Route* route2 = allenv->getRoute(j);
            if (isCompatible(route1, route2))
            {
                allenv->AddToExtendable(route1, route2);
            }
        }
    }
};

bool isCompatible(Route* route1, Route* route2)
{
    if (route2->getDest() == route1->getOrigin())
    {
        time_duration minGT = time_duration(hours(1));
        if (route2->getDepDT() >= route1->getArrDT() + minGT)
        {
            return true;
        }
    }
    return false;
};