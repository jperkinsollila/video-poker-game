#include <iostream>
#include <random>
#include <vector>

enum suit_t { CLUBS, DIAMONDS, HEARTS, SPADES };

enum face_t { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

class Card
{
private:
	suit_t suit;
	int face;
public:
	
	
	Card();
	Card(suit_t s, int v) {
		suit = s;
		face = v;
	}
	const int getSuitvalue() const { return suit; }
	const int getFacevalue() const { return face; }
	const char* getSuit() const {
			const char* names[] = { "Clubs","Diamonds", "Hearts","Spades" };
			return names[suit];
	}
	const char* getFace() const {
			const char* names[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" ,"Jack", "Queen", "King" };
			return names[face];
	}
};
