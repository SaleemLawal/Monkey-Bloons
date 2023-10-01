/*****************************************
** File:    Game.cpp
** This file contains the the main game functions call.
**
***********************************************/

#include "Game.h"
// Name: Game() - Default Constructor
// Description: Creates a new Game and populates money, round, and health
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including rounds played
Game::Game(){
	m_curRound = START_ROUND;
	m_curMoney = START_MONEY;
	m_curLife = START_LIFE;
}

// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated in Game
Game::~Game(){
	// deallocates the monkeys and bloons
	for (unsigned int i = 0; i < m_bloons.size(); i++){
		delete m_bloons.at(i);
		m_bloons.at(i) = nullptr;
	}
	for (unsigned int i = 0; i < m_monkeys.size(); i++){
		delete m_monkeys.at(i);
		m_monkeys.at(i) = nullptr;
	}
}

// Name: PrintMap()
// Description: For each location on the path, outputs the bloons and the monkeys (or none)
// Precondition: None
// Postcondition: None
void Game::PrintMap(){
	int counter = 0;
	// loop through each path
	for (int i = 0; i < PATH_LENGTH; i++){
		cout << "**Location " << i + 1 << "**" << endl;
		cout << "--Monkeys--" << endl;
		bool monkeyFound = false;
		// prints monkey at the corresponding location
		for(vector<Monkey*>::iterator it = m_monkeys.begin(); it != m_monkeys.end(); it++){
			Monkey* monkey = *it;
			// if theres a monkey that correspond to that current path, call the operator <<
			if (monkey -> GetLocation() == i){
				cout << counter + 1 << ". " <<*monkey << endl;
				monkeyFound = true;
				counter++;
			}
		}
		if (monkeyFound == false) {
            cout << "None\n";
        }
		// prints bloon at the corressponding at that location
		cout << "<<Bloons>>" << endl;
		bool bloonFound = false;
		for (vector<Bloon*>::iterator it = m_bloons.begin(); it != m_bloons.end(); it++){
			Bloon* bloon = *it;
			if (bloon -> GetLocation() == i){
				cout << *bloon << endl;
				bloonFound = true;
			}
		}
		if (bloonFound == false){
			cout << "None\n";
		}
		counter = 0;
		cout << endl;
	}
}

// Name: ImproveMonkey
// Description: Asks the user which monkey they would like to improve
//              Increases chosen monkey's damage by IMPROVE_VALUE above
// Precondition: Must have monkeys in m_monkeys and have enough money to pay (COST_IMPROVE)
// Postcondition: Monkey's damage is permanently improved
void Game::ImproveMonkey(){
	unsigned int userInput = 0;
	int monkeyDamage = 0;
	// checks if you have monkey available
	if (m_monkeys.size() > 0){
		// keep asking for monkey to improve while input is not within 1 and monkey size
		do{
			cout << "Which monkey would you like to improve (1-" << m_monkeys.size() <<")\n";
			for (unsigned int i = 0; i < m_monkeys.size(); i++){
				cout << i + 1 << ". " <<*m_monkeys.at(i) << endl;
			}
			cin >> userInput;
		} while(userInput <= 0 or userInput > m_monkeys.size());
		// checks if the cost is available
		if (m_curMoney >= COST_IMPROVE){
			m_curMoney -= COST_IMPROVE;
			monkeyDamage = m_monkeys.at(userInput - 1) -> GetDamage();
			m_monkeys.at(userInput - 1) -> SetDamage(monkeyDamage + IMPROVE_VALUE);
			cout << "Bomb in position " << userInput << " improved!\n";
		}else{
			cout << "You dont have enough money for this action\n";
		}
	}else{
		cout << "You dont have any monkeys\n";
	}
}

// Name: BuyMonkey
// Description: Asks the user which monkey they would like to buy
//            Reduces m_curMoney and then calls PlaceMonkey (which creates and places new monkey)
// Precondition: Must have enough money to pay (COST_DART, COST_BOOMERANG, or COST_BOMB)
// Postcondition: Specified monkey is added a chosen location on the path
void Game::BuyMonkey(){
	int monkey_type = 0;
	// keep asking while input isnt within range
	do{
		cout << "What type of monkey would you like to buy?\n1. Dart Monkey\n2. Boomerang Monkey\n3. Bomb Monkey\n4. Cancel\n";
		cin >> monkey_type;
	}while(monkey_type <= 0 or monkey_type >= 5);
	// purchases monkey type based on input
	if (monkey_type == 1 and m_curMoney >= COST_DART){
		m_curMoney -= COST_DART;
		PlaceMonkey(monkey_type);
	} else if (monkey_type == 2 and m_curMoney >= COST_BOOMERANG){
		m_curMoney -= COST_BOOMERANG;
		PlaceMonkey(monkey_type);
	} else if (monkey_type == 3 and m_curMoney >= COST_BOMB){
		m_curMoney -= COST_BOMB;
		PlaceMonkey(monkey_type);
	}else if (monkey_type == 4){
		cout << "Cancelled purchase\n";
	} else{
		cout << "You dont have enough money";
	}
}

// Name: PlaceMonkey(int choice)
// Description: Based on monkey purchased in BuyMonkey, asks user where to place new monkey
//              Dynamically allocates new monkey and populates location and adds to m_monkey
// Preconditions: Successfully purchased new monkey
// Postconditions: New monkey is added to m_monkey at chosen location
void Game::PlaceMonkey(int choice){
	int monkey_location = 0;
	// keeps asking if input is an invalid path
	do{
		cout << "Where would you like to place the new monkey? (1-" << PATH_LENGTH <<")" << endl;
		cin >> monkey_location;
	} while (monkey_location <= 0 or monkey_location > PATH_LENGTH);
	// creates a monkey at that location
	if (choice == 1){
		Monkey* monkey = new Dart("Dart", DAMAGE_DART, monkey_location - 1);
		m_monkeys.push_back(monkey);
		cout <<"New Dart monkey placed in location " << monkey_location << "\n";
	} else if (choice == 2){
		Monkey* monkey = new Boomerang("Boomerang", DAMAGE_BOOM, monkey_location - 1);
		m_monkeys.push_back(monkey);
		cout <<"New Boomerang monkey placed in location " << monkey_location << "\n";
	} else if (choice == 3){
		Monkey* monkey = new Bomb("Bomb", DAMAGE_BOMB, monkey_location - 1);
		m_monkeys.push_back(monkey);
		cout <<"New Bomb monkey placed in location " << monkey_location << "\n";
	}
}

// Name: StartGame()
// Description: Welcomes the player to the game. Continually calls MainMenu until user quits
// Preconditions: None
// Postconditions: Thanks user when quitting
void Game::StartGame(){
	cout << "Welcome to Bloons!\n";
	bool keepPlaying = true;
	while(keepPlaying){
		cout << endl;
		if (MainMenu() == 0){
			keepPlaying = false;
		}
	}
}

// Name: MainMenu()
// Description: Checks to see if player still has life. If m_curLife <= 0, game ends with loss.
//              Display menu (View Map, Buy New Monkey, Improve Existing Monkey
//              Progress Round, Check Stats, or Quit).
//              Calls function related to user choice.
// Preconditions: None
// Postconditions: Game continues until quit or player runs out of life
int Game::MainMenu(){
	int userInput = 0;
	// reask the main prompt if input isnt within the option range
	while (m_curLife >= 1){
		do{
			cout << "What would you like to do?\n1. View Map\n2. Buy New Monkey\n"
					"3. Improve Existing Monkey\n4. Progress Round\n5. Check Stats\n6. Quit\n";
			cin >> userInput;
		} while(userInput < 1 or userInput >= 7);
		switch(userInput){
			case 1:
				PrintMap();
				break;
			case 2:
				BuyMonkey();
				break;
			case 3:
				ImproveMonkey();
				break;
			case 4:
				PlayRound();
				break;
			case 5:
				Stats();
				break;
			case 6:
				cout << "Thanks for playing\n";
				return 0;
				break;
		}
		return 1;
	}
	cout << "Sorry, you have lost the game.\nThanks for playing!\n";
	return 0;
}

// Name: Stats()
// Description: Displays the information about the game
//              (current round, number of monkeys, money, and lives left)
// Preconditions: None
// Postconditions: None
void Game::Stats(){
	cout << "**CURRENT STATS**\n";
	cout << "Current Round: " <<  m_curRound << endl;
	cout << "Monkeys Working: " << m_monkeys.size() << endl;
	cout << "Current Money: " << m_curMoney << endl;
	cout << "Current Life: " << m_curLife << endl;
}

// Name: PlayRound()
// Description: Announces beginning and end of round
//              Calls PopulateBloons once then ResolveBattle once.
//              Calls RemovePopped (5 times due to erase function)
//              Calls MoveBloons once then calls CheckPath (5 times due to erase call)
//              Increments curRound
// Preconditions: None
// Postconditions: Round progresses
void Game::PlayRound(){
	cout << "Starting Round " << m_curRound << endl;
	PopulateBloons();
	ResolveBattle();
	for (int i = 0; i < 5; i++){
		RemovePopped();
	}
	MoveBloons();
	cout << "The bloons move along the path\n";
	for (int i = 0; i < 5; i++){
		CheckPath();
	}
	cout << "Round " << m_curRound++ << " Completed\n";
}

// Name: PopulateBloons
// Description: Each round, dynamically allocated bloons added to path in position START_BLOON
//              Bloons have a minimum of 1 health.
//              For each round, the number of new bloons increases matching the round number
//              For example: Round 1 = 1 red bloon (health 1)
//              Round 2 = 1 red bloon (health 1) and 1 blue bloon (health 2)
//              Round 3 = 1 red (health 1) and 1 blue (health 2) and 1 green (health 3)
//              Round 4 = 1 red, 1 blue, 1 green, and 1 yellow (health 4) and so forth
//              Notifies user that a new bloon (with color) has appeared.
// Preconditions: Round is at least 1
// Postconditions: All new bloons populated
void Game::PopulateBloons(){
	for (int i = 1; i <= m_curRound; i++){
		Bloon* bloon = new Basic(i, START_BLOON);
		cout << "A new " << bloon -> GetColor() << " bloon appears!\n";
		m_bloons.push_back(bloon);
	}
}

// Name: ResolveBattle()
// Description: Each monkey attacks the whole bloon vector.
//              For each pop, curMoney is increased.
// Preconditions: Monkeys and bloons exist
// Postconditions: Damage is dealt to bloons
void Game::ResolveBattle(){
	for (unsigned int i = 0; i < m_monkeys.size(); i++){
		// increase money by number of pops
		m_curMoney += m_monkeys.at(i)-> Attack(m_bloons) * EARN_POP;
	}
}

// Name: RemovePopped()
// Description: Iterates through m_bloons and if health is <= 0, bloon is deallocated and
//              removed from m_bloons
//         HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
// Preconditions: Monkeys and bloons exist
// Postconditions: Bloons are removed
void Game::RemovePopped(){
	unsigned int counter = 0;
	while (counter < m_bloons.size()){
		// checks if the health of the current bloon is 0
		if (m_bloons.at(counter) -> GetHealth() <= 0){
			// deletes the bloon and erase it
			delete m_bloons.at(counter);
			m_bloons.erase(m_bloons.begin() + counter);
		}else{
			counter++;
		}
	}
}

// Name: MoveBloons
// Description: For each bloon that still lives, it moves one location down the path
// Preconditions: Monkeys and bloons exist
// Postconditions: Bloons increment their location
void Game::MoveBloons(){
	// move each bloon once when called
	for (unsigned int i = 0; i < m_bloons.size(); i++){
		m_bloons.at(i) -> SetLocation(m_bloons.at(i) -> GetLocation() + 1);
	}
}

// Name: CheckPath
// Description: Iterates over m_bloons to see if location is equal to (or greater than)
//              PATH_LENGTH. If location is equal to PATH_LENGTH, causes damage to player.
//              Damage to player is one per health of bloon.
//              If 10 green bloons (health 3) hit player, player takes 30 damage
//              Bloons that hurt player are deallocated and erased from m_bloons
//              HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
// Preconditions: Monkeys and bloons exist
// Postconditions: Bloons are removed
void Game::CheckPath(){
	int currDamage = 0;
	for (unsigned int i = 0; i < m_bloons.size(); i++){
		// checks if the the bloon is at the ending of the path
		if (m_bloons.at(i)->GetLocation() >= PATH_LENGTH){
			currDamage = m_bloons.at(i)->GetHealth();
			delete m_bloons.at(i);
			m_bloons.erase(m_bloons.begin() + i);
			// deals damage to the player
			m_curLife -= currDamage;
			cout << "A bloon made it to the end of the path and you took " << currDamage <<" damage.\n";
		}
	}

}