#include "Utils.h"
#include <string>
#include "AllEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/date.hpp>
#include "Compare.h"

using namespace std;
using namespace boost::posix_time;

void ReadInputFiles()
{
    string inputFile = allenv->ScenarioDir() + "/random_schedule3.csv";
    cout << "Reading Input From " << inputFile << endl;

    ifstream fin(inputFile);

    if ( !fin )
    {
        cerr << "Missing Input file" <<endl;
    }
    int counter=0;


    // putting origin at the front
    ptime depotDT(time_from_string("1990-01-01 00:00:00"));
    string profit = "0.0";
    string origin = "Origin";
    string busType= "All";
	string schType = "All";
	int day=0;
	bool depot=true;
	Route* route = new Route(counter++, origin, origin, busType, depotDT, depotDT, profit, schType, day, depot);
	allenv->AddRoute(route);
	//end

    string headerline, line;
    getline(fin, headerline); //just flush the header line
    while ( getline(fin, line) ) //dont do eof() or .good() as a check. Last line may be repeated
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

        auto depDate = depDT.date();
        int day = depDate.day();

        Route* route = new Route( counter++, origin, destination, busType, depDT, arrDT, profit, schType, day);
        allenv->AddRoute(route);
    }
    //add a dest depot to the end
    day = 100;
    origin = "Destination";
    Route* route2 = new Route(counter++, origin, origin, busType, depotDT, depotDT, profit, schType, day, depot);
	allenv->AddRoute(route2);
	cout<<"Finished Reading Input"<<endl;

}
