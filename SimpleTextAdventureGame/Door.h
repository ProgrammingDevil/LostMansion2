#pragma once
#include <iostream>
#include <vector>
#include "area.h"

using namespace std;
class Door
{
	string key;
public:
	area rooms[2];
	bool locked = true;
	string name;
	Door();
	Door(string nameVal, string KeyVal, area room1, area room2);
	string GetName();
	bool Unlocked(vector<string>& bag);
	area Enter(area currentLoc);
};



