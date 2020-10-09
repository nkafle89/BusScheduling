#pragma once

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

class Route
{
private:
    string _origin;
    string _dest;
    string _busType;
    ptime _depDateTime;
    ptime _arrDateTime;
    double _profit;
    string _schType;

public:
    Route(string& origin, string& destination, string& busType, ptime& depDT, ptime& arrDT, 
            string& profit, string& schType);
    ~Route() {};

    string getOrigin(){return _origin;}
    void setOrigin(string& origin){_origin = origin;}

    string getDest(){return _dest;}
    void setDest(string& dest){_dest = dest;}
    
    string getBusType(){return _busType;}
    void setBusType(string& busType){_busType = busType;}

    ptime getDepDT(){return _depDateTime;}
    void setDepDT(ptime& x){ _depDateTime = x;}

    ptime getArrDT(){return _arrDateTime;}
    void setArrDT(ptime& x){ _arrDateTime = x;}

    double getProfit(){return _profit;}
    void setProfit(double& sn){_profit =sn;}

    string getSchType(){return _schType;}
    void setSchType(string& x){_schType = x;}
};