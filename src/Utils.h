#pragma once

class Route;

void ReadInputFiles();
void InitializeScenario(int argc, char* argv[]);
void CreatePaths();
bool isCompatible(Route* route1, Route* route2);
void CreateExtendMap();