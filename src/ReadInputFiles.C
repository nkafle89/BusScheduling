#include "Utils.h"
#include <string>
#include "AllEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

void ReadInputFiles()
{
    string inputFile = allenv->ScenarioDir() + "/random_schedule.csv";
    cout << "Reading Input From " << inputFile << endl;

    ifstream fin(inputFile);

    if ( !fin )
    {
        cerr << "Missing Input file" <<endl;
    }

    string headerline, line;
    
    getline(fin, headerline); //just flush the header line

    while (getline(fin, line)) //dont do eof() or .good() as a check. Last line may be repeated
    {
        stringstream str_strm(line); // convert the line into stringstream

        string origin, destination, busType, depDateTime, arrDateTime, profit, schType;
        getline(str_strm, origin, ',');
        getline(str_strm, destination, ',');
        getline(str_strm, busType, ',');
        getline(str_strm, depDateTime, ',');
        getline(str_strm, arrDateTime, ',');
        getline(str_strm, profit, ',');
        getline(str_strm, schType, '\n');

        ptime depDT(time_from_string(depDateTime));
        ptime arrDT(time_from_string(arrDateTime));

        Route* route = new Route(origin, destination, busType, depDT, arrDT, profit, schType);
        allenv->AddRoute(route);
    }
}


