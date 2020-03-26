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
	int yourmoney = 1000;
	int computermoney = 1000;
	std::cout << "\nWELCOME to my Poker Game." << std::endl;
	Sleep(2000);
	std::cout << "\nBoth of us have £1000. Each game will start with a compulsory bet of £10."
	<< std::endl;
	Sleep(3000);
	std::cout << "You can bet £10 more by calling or £20 more by raising." << std::endl;
	Sleep(3000);
	std::cout << "\nLet's begin." << std::endl;
	Sleep(2000);
	for (;;){ // infinite loop
		if (yourmoney<100 || computermoney<100){ // min £100 to play
			std::cout << "Both of us need at least £100 to play, sorry!" << std::endl;
			break;
		}
		Game game(yourmoney-10, computermoney-10); // pass saved money values to constructor, take £10 for blind
		game.start(); // start game
		game.updatemoney(yourmoney, computermoney); // update saved money values from game
		std::cout << "\n\nWant to play again?" << std::endl;
		std::string play;
		for (;;){
			std::cin >> play;
			if (play=="yes" || play=="no"){
				break;
			}
			std::cout << "I don't understand. Want to play again?" << std::endl;
		}
		if (play=="no"){
			std::cout << "\nYou leave the table with £" << yourmoney << "." << std::endl;
			Sleep(2000);
			std::cout << "\nThanks for playing. Bye!" << std::endl;
			break;
		}else{
			game.clear();
		}
	}
}