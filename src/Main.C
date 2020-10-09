#include <iostream>
#include "Utils.h"
#include "AllEnv.h"

using namespace std;


AllEnv* allenv;

int main(int argc, char* argv[])
{
    cout<<"No of args "<<argc<< endl;

    for (int i=0; i<argc; ++i)
    {
        cout<<"i th arg is: " << argv[i] << endl;
    }

    allenv = new AllEnv;
    
    InitializeScenario(argc, argv);
    ReadInputFiles();
    CreateExtendMap();

    cout << "Number of Routes added " << allenv->NumRoutes() << endl;

    cout<< "Solving Bus Routing problem..."<< endl;

}