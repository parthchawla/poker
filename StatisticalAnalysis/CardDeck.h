#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include <string>
#include <vector>

class Card{
public:
	Card();
	void setcard(int, std::string);
	int getvalue();
	std::string getsuit();
	void printcard();
private:
	int value_;
	std::string suit_;
};

class Deck{
public:
	Deck();
	void shuffle();
	Card dealcard();
private:
	static const int values[13];
	static const std::string suits[4];
	std::vector<Card> cards;
	int n;
};

#endif