/*****************************************
** File:    Basic.cpp
** This file contains the functions manages the bloon
**
***********************************************/
#include "Basic.h"
// Name: Basic() - Default Constructor
// Description: Creates a new Basic Monkey
// Preconditions: None
// Postconditions: Can create a Basic Monkey
Basic::Basic(){}

// Name: Basic(int health, int location)
// Description: Creates a new basic bloon with health at a specific location
// if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
// Preconditions: None
// Postconditions: Can create a basic bloon
Basic::Basic(int health, int location):Bloon(health, location){
	// changes the bloon color based on its health
	if (health == red + 1){
		m_color = "red";
	} else if (health == blue + 1){
		m_color = "blue";
	} else if (health == green + 1){
		m_color = "green";
	} else if (health == yellow + 1){
		m_color = "yellow";
	} else if (health == pink + 1){
		m_color = "pink";
	} else if (health >= black + 1){
		m_color = "black";
	}
}

// Name: ~Basic - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Basic::~Basic(){}

// Name: Pop
// Description: Changes the color of the bloon based on how many health it has left
// red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
// Preconditions: None
// Postconditions: Returns number of pops that occurred.
// Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
int Basic::Pop(int damage){
	//sets the health based on the damage passed in
	if (GetHealth() > 0) {
		SetHealth(GetHealth() - damage);
		cout << "The " << m_color << " bloon pops!" << endl;
		// reclassify the bloon color if it is popped
		if (GetHealth() == red + 1) {
			m_color = "red";
		} else if (GetHealth() == blue + 1) {
			m_color = "blue";
		} else if (GetHealth() == green + 1) {
			m_color = "green";
		} else if (GetHealth() == yellow + 1) {
			m_color = "yellow";
		} else if (GetHealth() == pink + 1) {
			m_color = "pink";
		} else if (GetHealth() >= black + 1) {
			m_color = "black";
		}
		
		if (GetHealth() >= 1) {
			cout << "The bloon is now " << m_color << "." << endl;
		}else{
			cout << "The bloon is now gone!" << endl;
		}
		if (damage < GetHealth() + damage) {
			return damage;
		} else {
			return GetHealth() + damage;
		}
	}
	return 0;
}
// Name: GetColor()
// Description: Returns the current color of a bloon
// Preconditions: None
// Postconditions: None
string Basic::GetColor(){
	return m_color;
}