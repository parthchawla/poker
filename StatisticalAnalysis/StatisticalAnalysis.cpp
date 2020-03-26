////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016, Parth Chawla, All rights reserved. //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// This creates a sleep function depending on the system of the user ///////////////////////////////
#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include <iostream>
#include <ctime>
#include <string>

int main(){
	std::srand((std::time(0)));
	int wins = 0;
	int loses = 0;
	int ties = 0;
	int r1 = 0;
	int r2 = 0;
	std::string s1 = "0";
	std::string s2 = "0";
	while (r1==r2 && s1==s2){
		std::cout << "\nEnter the rank of your first card (between 2 and 14)." << std::endl;
		std::cin >> r1;
		std::cout << "Enter the suit of your first card (spades, diamonds, clubs or hearts)."
		<< std::endl;
		std::cin >> s1;
		std::cout << "\nEnter the rank of your second card (between 2 and 14)." << std::endl;
		std::cin >> r2;
		std::cout << "Enter the suit of your second card (spades, diamonds, clubs or hearts)."
		<< std::endl;
		std::cin >> s2;
	}
	std::cout << "\nThis program will now simulate 1000 poker games with your hand and determine the number of times you win, lose or tie."
	<< std::endl;
	Sleep(3000);
	for (int i; i<1000; i++){ // find wins, loses and ties for 1000 loops
		Game game(wins, loses, ties, r1, r2, s1, s2);
		game.start();
		game.update(wins, loses, ties);
	}
}