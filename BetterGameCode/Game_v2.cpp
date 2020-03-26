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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Game_v2.h"

void Game::clear(){
	std::cout << std::string(100, '\n');
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up and start game ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game(int ym, int cm){ // initialise money values
	yourmoney = ym;
	computermoney = cm;
}

void Game::start(){ // game steps
	pot = 20; // blind
	deck.shuffle();
	sort();
	deal();
	printyourhand();
	if (round(yourmoney, computermoney)==4){ // this quits the game and returns to main
		return;
	}
	clear();
	std::cout << "\nDealing the flop..." << std::endl;
	Sleep(1000);
	printflop();
	if (round(yourmoney, computermoney)==4){
		return;
	}
	clear();
	std::cout << "\nDealing the turn..." << std::endl;
	Sleep(1000);
	printturn();
	if (round(yourmoney, computermoney)==4){
		return;
	}
	clear();
	std::cout << "\nDealing the river..." << std::endl;
	Sleep(1000);
	printriver();
	if (round(yourmoney, computermoney)==4){
		return;
	}
	clear();
	printriver();
	printyourhand();
	printcomputerhand();
	winner(h1, s1, h2, s2, yourmoney, computermoney);
}

void Game::updatemoney(int &ym, int &cm){ // update money by passing by reference from main
	ym = yourmoney;
	cm = computermoney;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up deck and deal cards //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::sort(){ // get 9 cards from top of deck
	std::cout << "\nShuffling cards..." << std::endl;
	Sleep(1000);
	Card card;
	for (int i=0; i<9; i++){
		card = deck.dealcard();
		cards.push_back(card);
	}
}

void Game::deal(){ // deal cards to players and set flop, turn and river
	std::cout << "\nDealing cards..." << std::endl;
	Sleep(1000);

	// vectors with card values
	h1.push_back(cards[0].getvalue());
	h2.push_back(cards[1].getvalue());
	h1.push_back(cards[2].getvalue());
	h2.push_back(cards[3].getvalue());
	h1.push_back(cards[4].getvalue());
	h2.push_back(cards[4].getvalue());
	h1.push_back(cards[5].getvalue());
	h2.push_back(cards[5].getvalue());
	h1.push_back(cards[6].getvalue());
	h2.push_back(cards[6].getvalue());
	h1.push_back(cards[7].getvalue());
	h2.push_back(cards[7].getvalue());
	h1.push_back(cards[8].getvalue());
	h2.push_back(cards[8].getvalue());

	// vectors with card suits
	s1.push_back(cards[0].getsuit());
	s2.push_back(cards[1].getsuit());
	s1.push_back(cards[2].getsuit());
	s2.push_back(cards[3].getsuit());
	s1.push_back(cards[4].getsuit());
	s2.push_back(cards[4].getsuit());
	s1.push_back(cards[5].getsuit());
	s2.push_back(cards[5].getsuit());
	s1.push_back(cards[6].getsuit());
	s2.push_back(cards[6].getsuit());
	s1.push_back(cards[7].getsuit());
	s2.push_back(cards[7].getsuit());
	s1.push_back(cards[8].getsuit());
	s2.push_back(cards[8].getsuit());

	// sort vector with values 
	std::sort(h1.begin(), h1.end());
	std::sort(h2.begin(), h2.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Print cards, user input /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::printyourhand(){ // print your hand
	std::cout << "\nThese are your cards:" << std::endl;
	Sleep(1000);
	cards[0].printcard();
	Sleep(1000);
	cards[2].printcard();
	Sleep(2000);
}

void Game::printcomputerhand(){ // print computer's hand
	std::cout << "\nThese are my cards:" << std::endl;
	Sleep(1000);
	cards[1].printcard();
	Sleep(1000);
	cards[3].printcard();
	Sleep(2000);
}

int Game::round(int &ym, int &cm){ // ask user for input, update money based on move
	std::cout << "\nThe pot has £" << pot << ". " << "You have £" << ym << " and I have £" << cm
	<< "." << std::endl;
	Sleep(1000);
	std::cout << "Your cards are:" << std::endl;
	cards[0].printcard();
	cards[2].printcard();

	std::cout << "Do you want to fold, call, check, or raise?" << std::endl;
	std::string move;
	for (;;){
		std::cin >> move;
		if (move=="call" || move=="raise" || move=="check" || move=="fold"){
			break;
		}
		std::cout << "I don't understand. Do you want to fold, call, check, or raise?"
		<< std::endl;
	}

	if (move=="call"){
		ym = ym - 10;
		cm = cm - 10;
		pot = pot + 20;
		std::cout << "\nYou call £10. You have £" << ym << " left." << std::endl;
		Sleep(2000);
		std::cout << "I call £10. I have £" << cm << " left." << std::endl;
		Sleep(3000);
		return 1;
	}else if (move=="raise"){
		ym = ym - 20;
		cm = cm - 20;
		pot = pot + 40;
		std::cout << "\nYou raise £20. You have £" << ym << " left." << std::endl;
		Sleep(2000);
		std::cout << "I call £20. I have £" << cm << " left." << std::endl;
		Sleep(3000);
		return 2;
	}else if (move=="check"){
		std::cout << "\nYou check." << std::endl;
		Sleep(2000);
		std::cout << "I check." << std::endl;
		Sleep(3000);
		return 3;
	}else if (move=="fold"){
		cm = cm + pot;
		std::cout << "\nYou fold. I WIN! I now have £" << cm << "." << std::endl;
		Sleep(5000);
		return 4;
	}else{
		return 5;
	}
}

void Game::printflop(){ // print flop
	std::cout << "\nCommunity cards:" << std::endl;
	Sleep(1000);
	for (int i=4; i<7; i++){
		cards[i].printcard();
	}
	Sleep(1000);
}

void Game::printturn(){ // print turn
	std::cout << "\nCommunity cards:" << std::endl;
	Sleep(1000);
	for (int i=4; i<8; i++){
		cards[i].printcard();
	}
	Sleep(1000);
}

void Game::printriver(){ // print river
	std::cout << "\nCommunity cards:" << std::endl;
	Sleep(1000);
	for (int i=4; i<9; i++){
		cards[i].printcard();
	}
	Sleep(1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// High card and score /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

int Game::high(std::vector<int> v){ // determine your high card
	int high1 = v[0];
	int high2 = v[1];
	if (high1>high2){
		return high1;
	}else{
		return high2;
	}
}

int Game::score(std::vector<int> v1, std::vector<std::string> v2){ // calculate your score
	int score = 0;
	if (straightflush(v1, v2)==true){
		score = score + 800;
	}else if (fourkind(v1)==true){
		score = score + 700;
	}else if (fullhouse(v1)==true){
		score = score + 600;
	}else if (flush(v2)==true){
		score = score + 500;
	}else if (straight(v1)==true){
		score = score + 400;
	}else if (threekind(v1)==true){
		score = score + 300;
	}else if (twopair(v1)==true){
		score = score + 200;
	}else if (pair(v1)==true){
		score = score + 100;
	}
	score = score + high(v1);
	return score;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Check hand strength /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::pair(std::vector<int> v){
	bool pair;
	for (int i=0; i<6; i++){
		if (v[i]==v[i+1]){
			pair = true;
		}else{
			pair = false;
		}
	}
	return pair;
}

bool Game::twopair(std::vector<int> v){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (v[i]==v[i+1]){
			m++;
		}
	}
	if (m==2){
		return true;
	}else{
		return false;
	}
}

bool Game::threekind(std::vector<int> v){
	bool threekind;
	for (int i=0; i<5; i++){
		if (v[i]==v[i+1] && v[i+1]==v[i+2]){
			threekind = true;
		}else{
			threekind = false;
		}
	}
	return threekind;
}

bool Game::flush(std::vector<std::string> v){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (v[i]==v[i+1]){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::straight(std::vector<int> v){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (v[i]==v[i+1]-1 || v[i]==v[i+1]-12){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::fullhouse(std::vector<int> v){
	bool pair;
	bool threekind;
	for (int i=0; i<6; i++){
		if (v[i]==v[i+1]){
			pair = true;
		}else{
			pair = false;
		}
	}
	for (int i=0; i<5; i++){
		if (v[i]==v[i+1] && v[i+1]==v[i+2]){
			threekind = true;
		}else{
			threekind = false;
		}
	}
	if (pair==true && threekind==true){
		return true;
	}else{
		return false;
	}
}

bool Game::fourkind(std::vector<int> v){
	bool fourkind;
	for (int i=0; i<4; i++){
		if (v[i]==v[i+1] && v[i+1]==v[i+2] && v[i+2]==v[i+3]){
			fourkind = true;
		}else{
			fourkind = false;
		}
	}
	return fourkind;
}

bool Game::straightflush(std::vector<int> v1, std::vector<std::string> v2){
	bool straight;
	bool flush;
	size_t m1 = 0;
	size_t m2 = 0;
	for (int i=0; i<6; i++){
		if (v2[i]==v2[i+1]){
			m1++;
		}
	}
	if (m1==4){
		flush = true;
	}else{
		flush = false;
	}
	for (int i=0; i<6; i++){
		if (v1[i]==v1[i+1]-1 || v1[i]==v1[i+1]-12){
			m2++;
		}
	}
	if (m2==4){
		straight = true;
	}else{
		straight = false;
	}
	if (straight==true && flush==true){
		return true;
	}else{
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Determine winner ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

int Game::evaluate(std::vector<int> v1, std::vector<std::string> v2, std::vector<int> v3, std::vector<std::string> v4){ // check who has higher score, high card
	if (score(v1, v2)>score(v3, v4)){
		return 1;
	}else if (score(v3, v4)>score(v1, v2)){
		return 2;
	}else{
		return 3;
	}
}

void Game::winner(std::vector<int> v1, std::vector<std::string> v2, std::vector<int> v3, std::vector<std::string> v4, int &ym, int &cm){ // announce winner, hand type, update money
	std::cout << "\nYou have a ";
	if (score(v1, v2)>=800){
		std::cout << "Straight Flush."<< std::endl;
	}else if (score(v1, v2)>=700 && score(v1, v2)<800){
		std::cout << "Four of a Kind." << std::endl;
	}else if (score(v1, v2)>=600 && score(v1, v2)<700){
		std::cout <<"Full House."<< std::endl;
	}else if (score(v1, v2)>=500 && score(v1, v2)<600){
		std::cout << "Flush." << std::endl;
	}else if (score(v1, v2)>=400 && score(v1, v2)<500){
		std::cout << "Straight." << std::endl;
	}else if (score(v1, v2)>=300 && score(v1, v2)<400){
		std::cout << "Three of a Kind." << std::endl;
	}else if (score(v1, v2)>=200 && score(v1, v2)<300){
		std::cout << "Two Pair." << std::endl;
	}else if (score(v1, v2)>=100 && score(v1, v2)<200){
		std::cout << "Pair." << std::endl;
	}else{
		std::cout << "High Card." << std::endl;
	}

	Sleep(2000);

	std::cout << "\nI have a ";
	if (score(v3, v4)>=800){
		std::cout << "Straight Flush."<< std::endl;
	}else if (score(v3, v4)>=700 && score(v3, v4)<800){
		std::cout << "Four of a Kind." << std::endl;
	}else if (score(v3, v4)>=600 && score(v3, v4)<700){
		std::cout <<"Full House."<< std::endl;
	}else if (score(v3, v4)>=500 && score(v3, v4)<600){
		std::cout << "Flush." << std::endl;
	}else if (score(v3, v4)>=400 && score(v3, v4)<500){
		std::cout << "Straight." << std::endl;
	}else if (score(v3, v4)>=300 && score(v3, v4)<400){
		std::cout << "Three of a Kind." << std::endl;
	}else if (score(v3, v4)>=200 && score(v3, v4)<300){
		std::cout << "Two Pair." << std::endl;
	}else if (score(v3, v4)>=100 && score(v3, v4)<200){
		std::cout << "Pair." << std::endl;
	}else{
		std::cout << "High Card." << std::endl;
	}

	Sleep(2000);

	if (evaluate(v1, v2, v3, v4)==1){
		ym = ym + pot;
		std::cout << "\nYOU WIN! You now have £" << ym << " and I have £" << cm << "." << std::endl;
	}else if (evaluate(v1, v2, v3, v4)==2){
		cm = cm + pot;
		std::cout << "\nI WIN! You now have £" << ym << " and I have £" << cm << "." << std::endl;
	}else{
		ym = ym + pot*0.5;
		cm = cm + pot*0.5;
		std::cout << "\nIt's a TIE! You now have £" << ym << " and I have £" << cm << "."
		<< std::endl;
	}

	Sleep(5000);
}