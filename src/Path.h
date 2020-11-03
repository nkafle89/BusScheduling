#pragma once
#include <vector>
#include "Basic.h"
#include "AllEnv.h"
#include "ortools/linear_solver/linear_solver.h"

class Route;

class Path
{
private:
	std::vector<Route*> _path;
    double _profit;
    int _id;

    operations_research::MPVariable* _var = nullptr;

public:
    Path(int id);
    ~Path() {};
    double getProfit() { return _profit; }
    void incrProfit( double x ){ _profit += x; }
    std::vector<Route*> getPath(){ return _path; }

    Route* getRoute( int n ) { return _path.at(n) ;}
    void addRoute( Route* rtr );
    void makeReverse() { std::reverse( _path.begin(), _path.end() ) ;}

    int getId(){ return _id; }

    void setVar(operations_research::MPVariable* var){ _var=var ;}
    operations_research::MPVariable* getVar(){return _var;}

};
std::ostream& operator<<(std::ostream& os, Path& path);