#pragma once
#include <iostream>
using namespace std;

class Monster
{
private:
	string name;
	int health;
	int attack;
	bool dead = false;
	void Death();
public:
	Monster();
	Monster(string name, int health = 50, int attack = 5);
	string GetName();
	bool Exist();
	void TakeDamage(int attack);
	int Attack();
	void DisplayStats();
		
};

