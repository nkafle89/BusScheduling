#pragma once

class Route;

void ReadInputFiles();
void InitializeScenario(int argc, char* argv[]);
bool isCompatible(Route* route1, Route* route2);
void CreateExtendMap();
