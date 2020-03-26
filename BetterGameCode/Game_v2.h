#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CardDeck.h"

class Game{
public:
	void clear();
	Game(int ym, int cm);
	void start();
	void updatemoney(int &ym, int &cm);

private:
	Deck deck;
	std::vector<Card> cards;
	std::vector<int> h1;
	std::vector<int> h2;
	std::vector<std::string> s1;
	std::vector<std::string> s2;
	void sort();
	void deal();
	void printyourhand();
	void printcomputerhand();
	int round(int &ym, int &cm);
	void printflop();
	void printturn();
	void printriver();
	int high(std::vector<int> v);
	int score(std::vector<int> v1, std::vector<std::string> v2);
	int evaluate(std::vector<int> v1, std::vector<std::string> v2, std::vector<int> v3, std::vector<std::string> v4);
	void winner(std::vector<int> v1, std::vector<std::string> v2, std::vector<int> v3, std::vector<std::string> v4, int &ym, int &cm);
	bool pair(std::vector<int> v);
	bool twopair(std::vector<int> v);
	bool threekind(std::vector<int> v);
	bool straight(std::vector<int> v);
	bool flush(std::vector<std::string> v);
	bool fullhouse(std::vector<int> v);
	bool fourkind(std::vector<int> v);
	bool straightflush(std::vector<int> v1, std::vector<std::string> v2);
	int yourmoney;
	int computermoney;
	int pot;
};

#endif