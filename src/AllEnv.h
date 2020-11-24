#pragma once
#include <vector>
#include <string>
#include "Basic.h"
#include "Route.h"
#include "Vehicle.h"
#include "Compare.h"
#include "Path.h"
#include "ortools/linear_solver/linear_solver.h"
#include "BellManFord.h"

using namespace operations_research;

class Route;
class Vehicle;
class Path;
class BellManFord;

class AllEnv
{
private:
    Route* _route = nullptr;
    Vehicle* _vehicle = nullptr;

    std::string _scenariodir;

    std::vector<Route*> _allRoutes;
    std::vector<Vehicle*> _allVehicle;

    std::vector<Path*> _allpaths;
    std::multimap<const double, Path*> _profitPathMap;
    MPSolver* const _solver;
    MPConstraint* _capConst = nullptr;
    BellManFord* _bellman = nullptr;
    double _capconstDual= 0;

    int _newcolsStart = 0 ;
public:
    AllEnv(MPSolver* const solver): _solver(solver){}
    ~AllEnv() {}

    void ScenarioDir(std::string scenarioDir) { _scenariodir = scenarioDir; }
    std::string ScenarioDir() { return _scenariodir; }

    void AddRoute(Route* route) {_allRoutes.push_back(route); }
    Route* getRoute(int n){return _allRoutes.at(n);}
    int NumRoutes(){return _allRoutes.size();}
    std::vector<Route*> getAllRoutes(){return _allRoutes;}

    void AddPath(Path* path){ _allpaths.push_back(path); }
    std::vector<Path*> getAllPaths() { return _allpaths; }

    void AddVehicle(Vehicle* vehicle) {_allVehicle.push_back(vehicle); }
    Vehicle* getVehicle(int n){return _allVehicle.at(n);}
    int NumVehicles(){return _allVehicle.size();}

	void dosort() {sort(_allRoutes.begin(), _allRoutes.end(), CompareRoutesByDayTypeShift);}

	operations_research::MPSolver* getSolver(){return _solver ;}
	void createRouteCovConstraint();
	void createPathVariables();
	void createCapConstraint();
	void setObj();
	MPConstraint* getCapConst(){return _capConst ;}

	BellManFord* getBellManFord();

	void setCapcaityDual( double x) { _capconstDual = x; }
	double getCapacityDual(){ return _capconstDual; }

	bool doesPathExists(Path* path);

    int newColsStart() { return _newcolsStart; }
    void newColsStart( int x ) { _newcolsStart = x; }
};
