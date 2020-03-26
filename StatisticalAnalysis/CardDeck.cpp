#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CardDeck.h"

const int Deck::values[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14}; // array with values
const std::string Deck::suits[4] = {"spades","diamonds","clubs","hearts"};// array with suits

////////////////////////////////////////////////////////////////////////////////////////////////////
// Card Class methods///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Card::Card(){}

void Card::setcard(int value, std::string suit){ // set value and suit for card
	value_ = value;
	suit_ = suit;
}

int Card::getvalue(){ // get card value
	return value_;
}

std::string Card::getsuit(){ // get card suit
	return suit_;
}

void Card::printcard(){
	if ((value_>=2) && (value_<=10)){
		std::cout << value_;
	}else{
		switch (value_){
			case 11: std::cout << "J"; break;
			case 12: std::cout << "Q"; break;
			case 13: std::cout << "K"; break;
			case 14: std::cout << "A"; break;
		}
	}
	std::cout << " of " << suit_ << std::endl; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Deck Class methods///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Deck::Deck(){ // set up deck of 52 cards
	n = 0;
	for (int i=0; i<13; i++){
		for (int j=0; j<4; j++){
			Card c;
			c.setcard(values[i], suits[j]);
			cards.push_back(c);
			n++;
		}
	}
}

void Deck::shuffle(){ // shuffle cards randomly
	random_shuffle(cards.begin(), cards.end());
}

Card Deck::dealcard(){
	n--;
	return cards[n];
}
