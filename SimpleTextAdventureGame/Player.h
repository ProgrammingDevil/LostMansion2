#include <iostream>
using namespace std;
class Player
{

private:
	int health;
	int attack;
	bool dead;
	void Death();
public:
	Player(int health=100, int attack= 25);
	bool Alive();
	void TakeDamage(int attack);
	int Attack();
	void DisplayHealth();
	void TakeHealthPotion();
};