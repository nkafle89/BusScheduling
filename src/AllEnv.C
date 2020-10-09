#include "AllEnv.h"


void AllEnv::AddToExtendable(Route* route1, Route* route2)
{
    map<Route*, vector<Route*>>::iterator itr;

    itr = _canExtend.find(route1);

    if ( itr != _canExtend.end())
    {
        itr->second.push_back(route2);
    }
    else
    {
        vector<Route*> vecrout{route2};
        _canExtend.insert({route1, vecrout});
    }

}