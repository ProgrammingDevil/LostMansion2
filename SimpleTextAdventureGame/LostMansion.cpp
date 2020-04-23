//*************************************************************
// Lost Mansion game
/* A game that takes place in an abandoned mansion. 
The user gets instructions on how to navigate the mansion through commands the user types into the
console.The mansion is very small with only 8 rooms(b1 - basement, 1 - kitchen, 1 - living room, 1 - office,
1 - entrance way, 2 - hallway, 2 - roomA, 2 - roomB).The player wakes up in 2 - RoomA that has a small
backpack to pick up items such as keys to use to unlock stuff like doors.The mission is to escape out of
the mansion through the front door in the entrance way.
*/
//Created by: David Harrison on 02/27/2020
//*************************************************************
// note: need to fixed need to use iterators to cycle through the vectors to fix < signed/unsigned mismatch warning,
//also need to change the enum warning  

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "area.h"
#include "Door.h"
using namespace std;

#pragma region Place Class
//Place class is the blueprint of the the interactable items in the rooms that you can search.
class Place
{
public:// later need to put the string name, item, and letter to be private and create getters for them
	string name;
	string item;
	string letter;
	Place(string nameVal, string itemVal, string letterVal);
	string GetName();
};
//the constructor for the place class 
Place::Place(string nameVal, string itemVal, string letterVal = "")
{
	name = nameVal;
	item = itemVal;
	letter = letterVal;
}
//to get the place name
string Place::GetName()
{
	return name;
}
#pragma endregion

#pragma region Room Class
//Room class is to hold the values of what is in the room and functions that affect the room
class Room
{
	string name ;
	Monster monster;
public://later need to make the vectors private and use setters and getters
	vector<Place> places;
	vector<area> areas;
	vector<int> doors;
	Room(string nameVal, vector<Place> placeVals, vector<int> doorVals);
	Room(string nameVal,vector<Place> placeVals, vector<area> areaVals, vector<int> doorVals);
	void AddMonster(string name, int health, int attack);
	char DisplayRoom(Door doorObjs[], Player &player);
	bool EnterRoom(string option, area &currentLoc, area &prevLoc);
	char AttackMode(Player &player);

};
//constructor for the room class to set up the values when i create a room object
Room::Room(string nameVal, vector<Place> placeVals, vector<int> doorVals)
{
	name = nameVal;
	places = placeVals;
	doors = doorVals;
}
Room::Room(string nameVal,vector<Place> placeVals, vector<area> areaVals, vector<int> doorVals)
{
	name = nameVal;
	places = placeVals;
	areas = areaVals;
	doors = doorVals;
}
void Room::AddMonster(string name, int health, int attack)
{
	monster = Monster(name, health, attack);
}
//display what is in the room
char Room::DisplayRoom(Door doorObjs[], Player &player)
{
	//display the name of the room
	cout << "*********************" << name << "*********************************" << endl;
	player.DisplayHealth();

	//check for Monsters
	if (monster.Exist())
	{
		return AttackMode(player);//attack mode function
	}
		
	//display the room by show places with intrest
	if (places.size() > 0)
	{
		cout <<  "The places you can interact with: ";
		for (int i = 0; i < places.size(); i++)
		{
			cout << " - "<< places[i].GetName();
		}
		cout << endl;
	}
	//display all the areas that player can travel to from this room
	if (areas.size())
	{
		cout <<"The areas you can go to:  ";
		for (int i = 0; i < areas.size(); i++)
		{
			string name;
			switch (areas[i])
			{
			case kitchen:
				name = "kitchen";
				break;
			case livingRoom:
				name = "livingRoom";
				break;
			case entranceWay:
				name = "entranceWay";
				break;
			}
			cout << " - "<< name;
		}
		cout << endl;
	}
	//display any doors the room has
	if (doors.size())
	{
		cout <<"You see these doors: ";

		for (int i = 0; i < doors.size(); i++)
		{
			string s = doorObjs[doors[i]].GetName();
			if (s != "")
			{
				cout << " - "<< s ;
			}
		}
		cout << endl;
	}
	return 'c';
}
//try to change the player location to the room the player typed in
bool Room::EnterRoom(string option, area &currentLoc,area &prevLoc)
{
	//not the best way to do but for now until i figure out how to evlaute the enum name values with a string
	area wanted;
	if (option == "kitchen")
		wanted = kitchen;
	else if (option == "livingRoom")
		wanted = livingRoom;
	else if (option == "entranceWay")
		wanted = entranceWay;
	else
		return false;
	//loop through the areas to make sure the room is connected to the wanted areas
	for (int i = 0; i < areas.size(); i++)
	{
		if (areas[i] == wanted)
		{
			prevLoc = currentLoc;
			currentLoc = wanted;
			return true;
		}
	}
	return false;

	
}
//attack mode only returns w if the player defeats the monster: r if the player decides to run: d if the player dies
char Room::AttackMode(Player &player)
{
	cout << "Look there is a " << monster.GetName() << endl;
	char choice;
	while (true)
	{
		//display player health
		player.DisplayHealth();
		//display monster stats
		monster.DisplayStats();
		// give the player choices
		cout << "enter a to attack or r to run away ";
		cin >> choice;
		if (choice == 'a')
		{//
			monster.TakeDamage(player.Attack());
			if (monster.Exist())
			{
				player.TakeDamage(monster.Attack());
				if (!player.Alive())
					return 'd';
			}
			else
				return 'w';
		}
		else if (choice == 'r')
		{
			cout << "You got away safely" << endl;
			return choice;
		}
		else
			cout << "sorry don't understand that input\n";
	}
}
#pragma endregion

//intialze the doors in the game 
Door doors[6]{ Door("roomA door","roomA key",roomA,hallway),Door("roomB door","roomB key",roomB,hallway),
	Door("front door","frontDoor key",entranceWay,front),Door("office door","office key",office,entranceWay),
	Door("basement door","basement key",basement,kitchen),Door("stairs","",hallway,entranceWay) };
//intialize the areas in the game
Room rooms[8]{ Room("roomA",{Place("backpack", "roomA key"),Place("dresser", "note","I must escape this mansion before I lose who I am.")},{0}),
	Room("roomB",{Place("cabnet", "frontDoor key")},{1}),Room("hallway",{},{0,1,5}),
	Room("entranceWay",{},{livingRoom,kitchen},{5,2,3 }),
	Room("livingRoom",{Place("entertainment center","basement key")},{entranceWay},{}),
	Room("kitchen",{Place("Table","health potion")},{entranceWay},{4}),
	Room("basement", {Place("boiler","office key"), Place("boxes", "health potion")},{4}), 
	Room("office",{Place("desk","roomB key")},{3}) };

void Intro();
bool Enter(area &currentLoc, area &prevLoc, string option, bool found);
bool Unlock(area& currentLoc, string option, bool found, vector<string>* pack);
bool Search(area& currentLoc, string option, bool found, vector<string>* pack, Player &player);
int main()
{
	Player firstPlayer(80);
	//add the monsters in the game
	rooms[roomB].AddMonster("ghost", 150, 15);
	rooms[livingRoom].AddMonster("rat", 100, 5);
	rooms[basement].AddMonster("ghoul", 100, 10);
	//set where the player is at the begining of the game
	area currentLocation = roomA;
	area previousLocation = currentLocation;
	//declare variables for the game
	string command;
	string option;
	const string ESCAPE_KEY = "quit";
	bool won= false;
	vector<string> backpack;
	
	//Play intro story of
	Intro();

	//To display what is in the room that your in
	rooms[currentLocation].DisplayRoom(doors,firstPlayer);
	
	while (!won&& firstPlayer.Alive())
	{
		//players input
		cin >> command;
		getline(cin, option);
		//get rid of the space at the begining of the command
		option.erase(0, 1);
		bool found= false;// set to true if it found what the user is looking for
		if (command == "enter")// to enter through a door or area
		{
			found = Enter(currentLocation,previousLocation, option, found);
			if (!found)// if the door or area was not found display a message to the player 
				cout << "Sorry there is no door or area with that name\n" << endl;
		}
		else if (command == "unlock")// to unlock doors
		{
			found = Unlock(currentLocation,option,found, &backpack);
			if (!found)// if the door was not found display a message to the player notify him there is no place 
				cout << "Sorry there is no door with that name\n" << endl;
		}
		else if (command == "search")//allows the user to search interactable places and keys will go into the backpack
		{
			found = Search(currentLocation, option, found, &backpack, firstPlayer);
			if (!found)// if the place was not found display a message to the player notify him there is no place 
				cout << "Sorry there is no place with that name\n" << endl;
		}
		else if (command == ESCAPE_KEY)//to exit out of the while loop
			break;
		else//no command matches
			cout << "sorry that is an invaild command" << endl;
		//win condition
		if (currentLocation == front)//if the player enters through the front door and prompt the user that he won
		{
			won = true;
			cout << "Congrats you have escaped press any key and press enter";
			cin >> found;
		}
		else// display the room that the user is in
		{
			char result =rooms[currentLocation].DisplayRoom(doors, firstPlayer);//show any updates
			switch (result)
			{
			case 'c'://cleared no monster in this room
				break;
			case 'd'://death
				cin >> found;
				break;
			case 'r'://ran from the battle
				currentLocation = previousLocation;
			case 'w'://won the battle
				rooms[currentLocation].DisplayRoom(doors, firstPlayer);//show any updates
				break;
			}
		}
			
	}
	return 0;
}
void Intro()
{
	//Waking up in the strange room 2 -roomA with no collection of who you are.
	cout << "Man, my head is killing me, where am I and who am I\n";
	//Give the player the commands of how to play the game.
	cout << "It seems like I got to figure out how to get out of here. The only thing I rember how to do is:\n";
	cout << "To search places for items I need to type search [place name] for example search broken closet\n";
	cout << "To unlock doors I need to type unlock [door name] for example unlock roomA door\n";
	cout << "To enter through a door or enter in a room type enter [door/rooom name] for example enter roomA door\n" << endl;
}
bool Enter(area &currentLoc, area &prevLoc, string option, bool found)
{
	//check the doors in the room
	for (int i = 0; i < rooms[currentLoc].doors.size(); i++)
	{
		//get which door number you want to check
		int doorNum = rooms[currentLoc].doors[i];
		//checks to see if any doors matchs to what the user is looking for
		if (doors[doorNum].name == option)
		{   
			prevLoc = currentLoc;
			currentLoc = doors[doorNum].Enter(currentLoc);
			cout << endl;
			found = true;
			break;
		}
	}
	//check the areas next to the room
	if (!found)
	{    //try to see if that area exist and change the players currentLocation to that room
		if (rooms[currentLoc].EnterRoom(option, currentLoc,prevLoc))
		{
			found = true;
		}
	}
	return found;
}
bool Unlock(area& currentLoc, string option, bool found, vector<string>* pack)
{
	//cycle through all the doors in the room
	for (int i = 0; i < rooms[currentLoc].doors.size(); i++)
	{
		//get which door number you want to check
		int doorNum = rooms[currentLoc].doors[i];
		//checks to see if any doors matches to what the user is looking for
		if (doors[doorNum].name == option)
		{   //try to unlock that door
			doors[doorNum].Unlocked(*pack);
			cout << endl;
			found = true;
			break;
		}
	}
	return found;
}
bool Search(area &currentLoc, string option, bool found, vector<string>* pack, Player &player)
{
	//cycle through all the places in the room
	for (int i = 0; i < rooms[currentLoc].places.size(); i++)
	{   //checks to see if the place matchs to what the user is looking for
		if (rooms[currentLoc].places[i].name == option)
		{   //checks if the place has a letter
			if (rooms[currentLoc].places[i].letter != "")
			{ //prints out what the letter says
				cout << "You found a letter that says " << rooms[currentLoc].places[i].letter;
			}
			else//then it must be a key in the place.
			{
				string it = rooms[currentLoc].places[i].item;
				cout << "You found a " << it;
				if (it == "health potion")
					player.TakeHealthPotion();
				else
					(*pack).push_back(it);//put it in the backpack
			}
			//delete the place from the room and flag that the place was found
			rooms[currentLoc].places.erase(rooms[currentLoc].places.begin() + i);
			cout << endl << endl;
			found = true;
			break;
		}
	}
	return found;
}
