#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include "CardDeck.h"

class Game{
public:
	Game(int w, int l, int t, int r1, int r2, std::string s1, std::string s2);
	void start();
	void update(int &w, int &l, int &t);

private:
	int rank1;
	int rank2;
	std::string suit1;
	std::string suit2;
	int wins;
	int loses;
	int ties;
	Deck deck;
	std::vector<Card> cards;
	std::vector<int> h1;
	std::vector<int> h2;
	std::vector<std::string> s1;
	std::vector<std::string> s2;
	void sort();
	void deal();
	int yourhigh();
	int computerhigh();
	int yourscore();
	int computerscore();
	int evaluate();
	void winner(int &w, int &l, int &t);
	bool pair1();
	bool twopair1();
	bool threekind1();
	bool straight1();
	bool flush1();
	bool fullhouse1();
	bool fourkind1();
	bool straightflush1();
	bool pair2();
	bool twopair2();
	bool threekind2();
	bool straight2();
	bool flush2();
	bool fullhouse2();
	bool fourkind2();
	bool straightflush2();
	int two1;
	int three1;
	int four1;
	int five1;
	int six1;
	int seven1;
	int eight1;
	int nine1;
	int ten1;
	int eleven1;
	int twelve1;
	int thirteen1;
	int fourteen1;
	int two2;
	int three2;
	int four2;
	int five2;
	int six2;
	int seven2;
	int eight2;
	int nine2;
	int ten2;
	int eleven2;
	int twelve2;
	int thirteen2;
	int fourteen2;
};

#endif