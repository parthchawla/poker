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
#include "Game.h"

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
	winner(yourmoney, computermoney);
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

	// find number of each card in hand
	two1 = std::count(h1.begin(), h1.end(), 2);
	three1 = std::count(h1.begin(), h1.end(), 3);
	four1 = std::count(h1.begin(), h1.end(), 4);
	five1 = std::count(h1.begin(), h1.end(), 5);
	six1 = std::count(h1.begin(), h1.end(), 6);
	seven1 = std::count(h1.begin(), h1.end(), 7);
	eight1 = std::count(h1.begin(), h1.end(), 8);
	nine1 = std::count(h1.begin(), h1.end(), 9);
	ten1 = std::count(h1.begin(), h1.end(), 10);
	eleven1 = std::count(h1.begin(), h1.end(), 11);
	twelve1 = std::count(h1.begin(), h1.end(), 12);
	thirteen1 = std::count(h1.begin(), h1.end(), 13);
	fourteen1 = std::count(h1.begin(), h1.end(), 14);
	two2 = std::count(h2.begin(), h2.end(), 2);
	three2 = std::count(h2.begin(), h2.end(), 3);
	four2 = std::count(h2.begin(), h2.end(), 4);
	five2 = std::count(h2.begin(), h2.end(), 5);
	six2 = std::count(h2.begin(), h2.end(), 6);
	seven2 = std::count(h2.begin(), h2.end(), 7);
	eight2 = std::count(h2.begin(), h2.end(), 8);
	nine2 = std::count(h2.begin(), h2.end(), 9);
	ten2 = std::count(h2.begin(), h2.end(), 10);
	eleven2 = std::count(h2.begin(), h2.end(), 11);
	twelve2 = std::count(h2.begin(), h2.end(), 12);
	thirteen2 = std::count(h2.begin(), h2.end(), 13);
	fourteen2 = std::count(h2.begin(), h2.end(), 14);
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

int Game::yourhigh(){ // determine your high card
	int high1 = cards[0].getvalue();
	int high2 = cards[2].getvalue();
	if (high1>high2){
		return high1;
	}else{
		return high2;
	}
}

int Game::computerhigh(){ // determine computer's high card
	int high1 = cards[1].getvalue();
	int high2 = cards[3].getvalue();
	if (high1>high2){
		return high1;
	}else{
		return high2;
	}
}

int Game::yourscore(){ // calculate your score
	int score = 0;
	if (straightflush1()==true){
		score = score + 800;
	}else if (fourkind1()==true){
		score = score + 700;
	}else if (fullhouse1()==true){
		score = score + 600;
	}else if (flush1()==true){
		score = score + 500;
	}else if (straight1()==true){
		score = score + 400;
	}else if (threekind1()==true){
		score = score + 300;
	}else if (twopair1()==true){
		score = score + 200;
	}else if (pair1()==true){
		score = score + 100;
	}
	score = score + yourhigh();
	return score;
}

int Game::computerscore(){ // calculate computer's score
	int score = 0;
	if (straightflush2()==true){
		score = score + 800;
	}else if (fourkind2()==true){
		score = score + 700;
	}else if (fullhouse2()==true){
		score = score + 600;
	}else if (flush2()==true){
		score = score + 500;
	}else if (straight2()==true){
		score = score + 400;
	}else if (threekind2()==true){
		score = score + 300;
	}else if (twopair2()==true){\
		score = score + 200;
	}else if (pair2()==true){
		score = score + 100;
	}
	score = score + computerhigh();
	return score;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Check hand strength /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::pair1(){
	if (two1==2||three1==2||four1==2||five1==2||six1==2||seven1==2||eight1==2||nine1==2||ten1==2||
		eleven1==2||twelve1==2||thirteen1==2||fourteen1==2){
		return true;
	}else{
		return false;
	}
}

bool Game::twopair1(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (h1[i]==h1[i+1]){
			m++;
		}
	}
	if (m==2){
		return true;
	}else{
		return false;
	}
}

bool Game::threekind1(){
	if (two1==3||three1==3||four1==3||five1==3||six1==3||seven1==3||eight1==3||nine1==3||ten1==3||
		eleven1==3||twelve1==3||thirteen1==3||fourteen1==3){
		return true;
	}else{
		return false;
	}
}

bool Game::flush1(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (s1[i]==s1[i+1]){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::straight1(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (h1[i]==h1[i+1]-1 || h2[i]==h2[i+1]-12){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::fullhouse1(){
	bool pair;
	bool threekind;
	if (two1==2||three1==2||four1==2||five1==2||six1==2||seven1==2||eight1==2||nine1==2||ten1==2||
		eleven1==2||twelve1==2||thirteen1==2||fourteen1==2){
		pair = true;
	}else{
		pair = false;
	}
	if (two1==3||three1==3||four1==3||five1==3||six1==3||seven1==3||eight1==3||nine1==3||ten1==3||
		eleven1==3||twelve1==3||thirteen1==3||fourteen1==3){
		threekind = true;
	}else{
		threekind = false;
	}
	if (pair==true && threekind==true){
		return true;
	}else{
		return false;
	}
}

bool Game::fourkind1(){
	if (two1==4||three1==4||four1==4||five1==4||six1==4||seven1==4||eight1==4||nine1==4||ten1==4||
		eleven1==4||twelve1==4||thirteen1==4||fourteen1==4){
		return true;
	}else{
		return false;
	}
}

bool Game::straightflush1(){
	bool straight;
	bool flush;
	size_t m1 = 0;
	size_t m2 = 0;
	for (int i=0; i<6; i++){
		if (s1[i]==s1[i+1]){
			m1++;
		}
	}
	if (m1==4){
		flush = true;
	}else{
		flush = false;
	}
	for (int i=0; i<6; i++){
		if (h1[i]==h1[i+1]-1 || h2[i]==h2[i+1]-12){
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

bool Game::pair2(){
	if (two2==2||three2==2||four2==2||five2==2||six2==2||seven2==2||eight2==2||nine2==2||ten2==2||
		eleven2==2||twelve2==2||thirteen2==2||fourteen2==2){
		return true;
	}else{
		return false;
	}
}

bool Game::twopair2(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (h2[i]==h2[i+1]){
			m++;
		}
	}
	if (m==2){
		return true;
	}else{
		return false;
	}
}

bool Game::threekind2(){
	if (two2==3||three2==3||four2==3||five2==3||six2==3||seven2==3||eight2==3||nine2==3||ten2==3||
		eleven2==3||twelve2==3||thirteen2==3||fourteen2==3){
		return true;
	}else{
		return false;
	}
}

bool Game::flush2(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (s2[i]==s2[i+1]){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::straight2(){
	size_t m = 0;
	for (int i=0; i<6; i++){
		if (h2[i]==h2[i+1]-1 || h2[i]==h2[i+1]-12){
			m++;
		}
	}
	if (m==4){
		return true;
	}else{
		return false;
	}
}

bool Game::fullhouse2(){
	bool pair;
	bool threekind;
	if (two2==2||three2==2||four2==2||five2==2||six2==2||seven2==2||eight2==2||nine2==2||ten2==2||
		eleven2==2||twelve2==2||thirteen2==2||fourteen2==2){
		pair = true;
	}else{
		pair = false;
	}
	if (two2==3||three2==3||four2==3||five2==3||six2==3||seven2==3||eight2==3||nine2==3||ten2==3||
		eleven2==3||twelve2==3||thirteen2==3||fourteen2==3){
		threekind = true;
	}else{
		threekind = false;
	}
	if (pair==true && threekind==true){
		return true;
	}else{
		return false;
	}
}

bool Game::fourkind2(){
	if (two2==4||three2==4||four2==4||five2==4||six2==4||seven2==4||eight2==4||nine2==4||ten2==4||
		eleven2==4||twelve2==4||thirteen2==4||fourteen2==4){
		return true;
	}else{
		return false;
	}
}

bool Game::straightflush2(){
	bool straight;
	bool flush;
	size_t m1 = 0;
	size_t m2 = 0;
	for (int i=0; i<6; i++){
		if (s2[i]==s2[i+1]){
			m1++;
		}
	}
	if (m1==4){
		flush = true;
	}else{
		flush = false;
	}
	for (int i=0; i<6; i++){
		if (h2[i]==h2[i+1]-1 || h2[i]==h2[i+1]-12){
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

int Game::evaluate(){ // check who has higher score, high card
	if (yourscore()>computerscore()){
		return 1;
	}else if (computerscore()>yourscore()){
		return 2;
	}else{
		return 3;
	}
}

void Game::winner(int &ym, int &cm){ // announce winner, hand type, update money
	std::cout << "\nYou have a ";
	if (yourscore()>=800){
		std::cout << "Straight Flush."<< std::endl;
	}else if (yourscore()>=700 && yourscore()<800){
		std::cout << "Four of a Kind." << std::endl;
	}else if (yourscore()>=600 && yourscore()<700){
		std::cout <<"Full House."<< std::endl;
	}else if (yourscore()>=500 && yourscore()<600){
		std::cout << "Flush." << std::endl;
	}else if (yourscore()>=400 && yourscore()<500){
		std::cout << "Straight." << std::endl;
	}else if (yourscore()>=300 && yourscore()<400){
		std::cout << "Three of a Kind." << std::endl;
	}else if (yourscore()>=200 && yourscore()<300){
		std::cout << "Two Pair." << std::endl;
	}else if (yourscore()>=100 && yourscore()<200){
		std::cout << "Pair." << std::endl;
	}else{
		std::cout << "High Card." << std::endl;
	}

	Sleep(2000);

	std::cout << "\nI have a ";
	if (computerscore()>=800){
		std::cout << "Straight Flush."<< std::endl;
	}else if (computerscore()>=700 && computerscore()<800){
		std::cout << "Four of a Kind." << std::endl;
	}else if (computerscore()>=600 && computerscore()<700){
		std::cout <<"Full House."<< std::endl;
	}else if (computerscore()>=500 && computerscore()<600){
		std::cout << "Flush." << std::endl;
	}else if (computerscore()>=400 && computerscore()<500){
		std::cout << "Straight." << std::endl;
	}else if (computerscore()>=300 && computerscore()<400){
		std::cout << "Three of a Kind." << std::endl;
	}else if (computerscore()>=200 && computerscore()<300){
		std::cout << "Two Pair." << std::endl;
	}else if (computerscore()>=100 && computerscore()<200){
		std::cout << "Pair." << std::endl;
	}else{
		std::cout << "High Card." << std::endl;
	}

	Sleep(2000);

	if (evaluate()==1){
		ym = ym + pot;
		std::cout << "\nYOU WIN! You now have £" << ym << " and I have £" << cm << "." << std::endl;
	}else if (evaluate()==2){
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