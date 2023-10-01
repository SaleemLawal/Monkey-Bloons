/*****************************************
** File:    Bomb.cpp
** This file contains the functions of a child class of Monkey
**
***********************************************/

#include "Bomb.h"
// Name: Bomb() - Default Constructor
// Description: Creates a new Bomb Monkey
// Preconditions: None
// Postconditions: Can create a Bomb Monkey
Bomb::Bomb(){}

// Name: Bomb(string type, int damage, int location)
// Description: Creates a new Bomb Monkey
// Preconditions: None
// Postconditions: Can create a Bomb Monkey
Bomb::Bomb(string bomb, int damage, int location): Monkey(bomb, damage, location){}

// Name: ~Bomb - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Bomb::~Bomb(){}

// Name: Attack
// Description: Iterates through all bloons. Hits all bloons in same location as bomb.
//              Returns total bloon health or damage (whichever is less) for earnings (money)
//              EXTRA CREDIT: Only monkey that can pop Lead Bloons.
// Preconditions: Bloons must be in same location as bomb monkey
// Postconditions: Damages each bloon and returns earnings (total pops)
int Bomb::Attack(vector<Bloon*> bloon){
	int damage = 0;
	// loop through the bloon
	for(unsigned int i  = 0; i< bloon.size(); i++){
		Bloon* currBloon = bloon.at(i);
		if (currBloon -> GetHealth() >= 1){
			// checks if it has the same location with the monkey
			if (currBloon -> GetLocation() == GetLocation()){
				cout << "The bomb shooter launches a bomb!\n";
				// get the damage done from pop
				damage += currBloon->Pop(GetDamage());
			}
		}
	}
	return damage;
}