/*****************************************
** File:    Boomerang.cpp
** This file contains the functions of a child class of Monkey
**
***********************************************/

#include "Boomerang.h"
// Name: Boomerang() - Default Constructor
// Description: Creates a new Boomerang Monkey
// Preconditions: None
// Postconditions: Can create a Boomerang Monkey
Boomerang::Boomerang(){}
// Name: Boomerang(string type, int damage, int location)
// Description: Creates a new Boomerang Monkey
// Preconditions: None
// Postconditions: Can create a Boomerang Monkey
Boomerang::Boomerang(string boom, int damage, int location): Monkey(boom, damage, location){}

// Name: ~Boomerang - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Boomerang::~Boomerang(){}
// Name: Attack
// Description: Iterates through all bloons. For "each bloon in the same location as boomerang",
//              "hits each bloon twice" (once out and once back)
//              Returns total bloon health or damage (whichever is less) for earnings (money)
// Preconditions: Bloons must be in same location as Boomerang Monkey
// Postconditions: Damages each bloon and returns earnings (total pops)
int Boomerang::Attack(vector<Bloon*> bloon){
	int damage = 0;
	int count = 0;
	// used to hit bloon twice
	for (int j = 0; j < 2; j++){
		for (unsigned int i = 0; i < bloon.size(); i++) {
			Bloon* currBloon = bloon.at(i);
			if (currBloon ->GetHealth() >= 1) {
				// checks if it has the same location with the monkey sand its the first go around (count = 0)
				if (count == 0 and currBloon ->GetLocation() == GetLocation()){
					cout << "The boomerang monkey throws a boomerang!\n";
				}
				// checks if it has the same location with the monkey
				if (currBloon ->GetLocation() == GetLocation()) {
					damage += currBloon ->Pop(GetDamage());
				}
			}
		}
		count++;
	}
	return damage;
}
