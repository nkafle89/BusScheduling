#pragma once
#include <vector>

class Route;

class BellManFord
{
private:
	int _id=0;
public:
	BellManFord(){};
	~BellManFord(){};

	void BellManFordSearch(std::vector<Route*>& allroutes, bool remove = false);
	void resetRouteValues(std::vector<Route*>& allroutes, Route* source, bool visitedNode= false);
	Path* backTrackPath(Route* dest );
	void getAllCoveringPaths();
	void Relax(Route* rtr, Route* next, bool& changes, bool& remove);
	void getPositivePaths();
};


