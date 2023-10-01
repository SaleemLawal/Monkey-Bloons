/*****************************************
** File:    Bloon.cpp
** This file contains the functions Parent class and contains information that the child class could use
**
***********************************************/

#include "Bloon.h"
// Name: Bloon() - Default Constructor
// Description: Abstract class - cannot directly instantiate this class
// Preconditions: None
// Postconditions: Populates variables used in child classes (may not be specifically used)
Bloon::Bloon(){}
// Name: Bloon(int health, int location) - Overloaded Constructor
// Description: Abstract class - cannot directly instantiate this class
// Preconditions: None
// Postconditions: Populates variables used in child classes
Bloon::Bloon(int health, int location){
	m_health = health;
	m_location = location;
}
// Name: virtual ~Bloon - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Bloon::~Bloon(){}
// Name: GetHealth()
// Description: Returns health of bloon
// Preconditions: Bloon has health
// Postconditions: None
int Bloon::GetHealth(){
	return m_health;
}
// Name: SetHealth()
// Description: Sets health of bloon
// Preconditions: None
// Postconditions: Health is set
void Bloon::SetHealth(int health){
	m_health = health;
}
// Name: GetLocation()
// Description: Returns location of bloon
// Preconditions: Bloon has location
// Postconditions: None
int Bloon::GetLocation(){
	return m_location;
}
// Name: SetLocation()
// Description: Sets location of bloon
// Preconditions: None
// Postconditions: Location is set
void Bloon::SetLocation(int location){
	m_location = location;
}
// Name: Overloaded <<
// Description: Prints the details of a bloon
// Preconditions: all variables are set valid
// Postconditions: returns an ostream with output of bloon
ostream& operator<<(ostream& output, Bloon& bloom){
	// rreturn the bloon states when the bloon object is cout
	output << "Bloon: " << bloom.GetColor() << " Health: " << bloom.GetHealth();
	return output;
}