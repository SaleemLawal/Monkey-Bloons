/*****************************************
** File:    Dart.cpp
** This file contains the functions of a child class of Monkey
**
***********************************************/

#include "Dart.h"

// Name: Dart() - Default Constructor
// Description: Creates a new Dart Monkey
// Preconditions: None
// Postconditions: Can create a Dart Monkey
Dart::Dart(){}

// Name: Dart(string type, int damage, int location)
// Description: Creates a new Dart Monkey
// Preconditions: None
// Postconditions: Can create a Dart Monkey
Dart::Dart(string dart, int damage, int location): Monkey(dart, damage, location){}

// Name: ~Dart - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Dart::~Dart(){}

// Name: Attack
// Description: Iterates through all bloons."Hits first bloon in the same location as dart."
//              Returns total bloon health or damage (whichever is less) for earnings (money)
// Preconditions: Bloon must be in same location as Dart monkey
// Postconditions: Damages one bloon and returns earnings (total pops)
int Dart::Attack(vector<Bloon*> bloon){
	int damage = 0;
	for (unsigned int i =0; i < bloon.size(); i++){
		Bloon* currBloon = bloon.at(i);
		if (currBloon -> GetHealth() >= 1){
			// checks if it has the same location with the monkey
			if (currBloon -> GetLocation() == GetLocation()){
				cout << "The dart monkey throws a dart\n";
				// sets damage as the pop
				damage += currBloon->Pop(GetDamage());
				// return the lowest between the bloon health and the damage done
				if (currBloon -> GetHealth() < damage){
					return currBloon -> GetHealth();
				}else{
					return damage;
				}
			}
		}
	}
	return 0;
}
