#include "Monster.h"


void Monster::Death()
{
	cout << " You defeated the " << name << endl;
	name = "Empty";
}
Monster::Monster()
{
	name = "Empty";
	
}
Monster::Monster(string name, int health, int attack) : name(name), health(health), attack(attack)
{
	dead = false;
}
string Monster::GetName()
{
	return name;
}
bool Monster::Exist()
{
	if (name != "Empty")
		return true;
	return false;
}
void Monster::TakeDamage(int attack)
{
	health -= attack;
	if (health <= 0)
		Death();
	else
	{
		cout << name << " took " << attack << " damage " << endl;
	}
}
int Monster::Attack()
{
	return attack;
}
void Monster::DisplayStats()
{
	cout << name << " health: " << health <<endl;
}
