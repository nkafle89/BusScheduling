#pragma once

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Path.h"
#include "ortools/linear_solver/linear_solver.h"

class Path;

class Route
{
private:
	int _id;
	std::string _origin;
	std::string _dest;
	std::string _busType;
	boost::posix_time::ptime _depDateTime;
	boost::posix_time::ptime _arrDateTime;
    double _profit;
    std::string _schType;
    int _day;
    std::vector<Route*> _canextend;
    bool _isdepot;

    bool _visited;
    Route* _previous;
    double _spcost;
    double _reducedCost;

    std::vector<Path*> _presentInPath;

    operations_research::MPConstraint* _row = nullptr;

public:
    Route(int id, std::string& origin, std::string& destination, std::string& busType,
    		boost::posix_time::ptime& depDT, boost::posix_time::ptime& arrDT,
    		std::string& profit, std::string& schType, int& day, bool depot = false);
    ~Route() {};

    std::string getOrigin(){return _origin;}
    void setOrigin(std::string& origin){_origin = origin;}

    std::string getDest(){return _dest;}
    void setDest(std::string& dest){_dest = dest;}
    
    std::string getBusType(){return _busType;}
    void setBusType(std::string& busType){_busType = busType;}

    boost::posix_time::ptime& getDepDT(){return _depDateTime;}
    void setDepDT(boost::posix_time::ptime& x){ _depDateTime = x;}

    boost::posix_time::ptime& getArrDT(){return _arrDateTime;}
    void setArrDT(boost::posix_time::ptime& x){ _arrDateTime = x;}

    double getProfit(){return _profit;}
    void setProfit(double& sn){_profit = sn;}

    std::string getSchType(){return _schType;}
    void setSchType(std::string& x){_schType = x;}

    void canExtend(Route* route) {_canextend.push_back(route);}
    std::vector<Route*> GetExtendRoutes(){ return _canextend;}

    int getDay(){ return _day; }
    void setDay(int& x){_day = x;}  
    
    bool& isDepot(){ return _isdepot; }
    void isDepot(bool& x){_isdepot = x;} 

    double spCost(){ return _spcost; }
    void spCost(double x){ _spcost=x; }

    void reducedCost(double x){_reducedCost=x;}
    double reducedCost(){ return _reducedCost; }

    Route* getPreviousRoute(){ return _previous; }
    void setPreviousRoute(Route* rt) {_previous = rt; }

    bool visited() { return _visited;}
    void visited(bool x) { _visited=x; }

    int getId(){return _id;}

    void presentInPath(Path* p) { _presentInPath.push_back(p); }
    std::vector<Path*> presentInPath() { return _presentInPath ;}

    void setRow(operations_research::MPConstraint* row){_row = row;}
    operations_research::MPConstraint* getRow(){return _row; }

};
std::ostream& operator<<(std::ostream& os, Route& rt);



