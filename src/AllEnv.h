#pragma once
#include <vector>
#include <string>
#include "Basic.h"
#include "Route.h"
#include "Vehicle.h"
#include <map>

class Route;
class Vehicle;

using namespace std;
class AllEnv
{
private:
    Route* _route = nullptr;
    Vehicle* _vehicle = nullptr;

    string _scenariodir;
    vector<Route*> _allRoutes;
    vector<Vehicle*> _allVehicle;
    map<Route*, vector<Route*>> _canExtend; //map where the key is a route and value is the vector of routes than can be extended
    
public:
    AllEnv() {}
    ~AllEnv() {}

    void ScenarioDir(string scenarioDir) { _scenariodir = scenarioDir; }
    string ScenarioDir() { return _scenariodir; }

    void AddRoute(Route* route) {_allRoutes.push_back(route); }
    Route* getRoute(int n){return _allRoutes.at(n);}
    int NumRoutes(){return _allRoutes.size();}

    void AddVehicle(Vehicle* vehicle) {_allVehicle.push_back(vehicle); }
    Vehicle* getVehicle(int n){return _allVehicle.at(n);}
    int NumVehicles(){return _allVehicle.size();}

    void AddToExtendable(Route* route1, Route* route2);
    vector<Route*> GetExtendRoutes(Route* route){return _canExtend.find(route)->second;}

};