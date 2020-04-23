#include "player.h"

Player::Player(int health, int attack) :health(health), attack(attack)
{
	dead = false;
}
bool Player::Alive()
{
	return !dead;
}
void Player::TakeDamage(int attack)
{
	cout << "You took " << attack << " damage" << endl;
	health -= attack;
	if (health < 1)
		Death();
	else
		cout << "oww that hurt" <<  endl;
}
int Player::Attack()
{
	return attack;
}
void Player::DisplayHealth()
{
	cout << "Health:" << health << endl << endl;
}
void Player::Death()
{
	dead = true;
	cout << "You have been defeated game over!" << endl;
}
void Player::TakeHealthPotion()
{
	cout << "You drunk a health potion and now feeling a little better" << endl;
	health += 25;
	if (health > 100)
		health = 100;
}