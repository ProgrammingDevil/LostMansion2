#include "Door.h"


//class that makes handling doors in the game much more easier

//default constructor
Door::Door()
{
	name = "";
}
//constructor that set up the door values
Door::Door(string namVal, string keyVal, area room1, area room2)
{
	name = namVal;
	key = keyVal;
	if (key == "")
		locked = false;
	rooms[0] = room1;
	rooms[1] = room2;
}
string Door::GetName()
{
	return name;
}
//unlock method to allow the player to unlock a door by searching the bag for the key
bool Door::Unlocked(vector<string>& bag)
{
	if (key == "")
	{// make it all little bit extra humor
		cout << "You can not use keys on stairs" << endl;
	}
	else if (!locked)// let the player know that the door is already unlocked
	{
		cout << "This door is already unlocked" << endl;
	}
	else
	{   //search the bag to see if it has the door key then unlock it and throw away the key
		for (int i = 0; i < bag.size(); i++)
		{
			if (bag[i] == key)
			{
				locked = false;
				bag.erase(bag.begin() + i);
				cout << name << " is now unlocked and no need to hold this key anymore" << endl;
				return true;
			}
		}
		//if the key was not in the backpack then let the player know
		cout << "Sorry you don't have the door key in your backpack" << endl;
	}
	return false;
}
//Enter to allow you to enter through a door
area Door::Enter(area currentLoc)
{
	//check to make sure the door is not locked
	if (!locked)
	{
		// switch the location with the oppsite side
		if (currentLoc == rooms[0])
			currentLoc = rooms[1];
		else
			currentLoc = rooms[0];
	}
	else// display message saying it is locked
		cout << "Sorry this door is locked you need to unlock the door first" << endl;
	return currentLoc;
}

