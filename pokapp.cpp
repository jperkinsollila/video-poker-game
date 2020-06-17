//Written by Justin Perkins-Ollila, jperkinsollila@gmail.com

#include <iostream>
#include <ctime>
#include <random>
#include <deque>
#include "pokehead.h"

using namespace std;
int randomizer(int i) { return std::rand() % i; }
string Face[5];
string Suit[5];
int Faceval[5];
int Suitval[5];
string cont;
int bank = 50;
int debt = 0;
int beginning_sequence = 0;
int bet;

void calc_hand() {
	int f[5], s[5];
	for (int i = 0; i < 5; ++i) {
		f[i] = 0;
		s[i] = 0;
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = i; j < 5; ++j) {
			if (Faceval[i] == Faceval[j]) {
				f[i]++;
			}
			if (Suitval[i] == Suitval[j]) {
				s[i]++;
			}
		}
	}
	// loop to correct and set all the duplicate counts to zero
	for (int i = 0; i < 5; ++i) {
		for (int j = i; j < 5; ++j) {
			if (Faceval[i] == Faceval[j]) {
				if (i != j) {
					if (i > j) {
						f[i] = 0;
					}
					if (i < j) {
						f[j] = 0;
					}
					else {}
				}
			}
			if (Suitval[i] == Suitval[j]) {
				if (i != j) {
					if (i > j) {
						s[i] = 0;
					}
					if (i < j) {
						s[j] = 0;
					}
					else {}
				}
			}
		}
	}
	int* max_f[4];
	int* max_s[4];
	int* min_f = min_element(f, f + 5),
		* min_s = min_element(s, s + 5),
		* max_faceval = max_element(Faceval, Faceval + 5),
		* min_faceval = min_element(Faceval, Faceval + 5);

	for (int i = 0; i < 4; ++i) {
		max_f[i] = max_element(f + i, f + 5);
		max_s[i] = max_element(s + i, s + 5);
	}
	//cout << *min_f << *max_f[2];
	bool hand = true; //search for correct hand
	bool straight = false;
	int count = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (*max_faceval >= 12 && *min_faceval <= 0 && (*min_f >= 1)) {
				if (Faceval[i] == (Faceval[j] + 1)) {
					count++;
				}
				if (Faceval[j] == (Faceval[i] + 1)) {
					count++;
				}
				if (count >= 6) {
					straight = true;
				}
			}
			if (*min_f >= 1) {
				if (Faceval[i] == (Faceval[j] + 1)) {
					count++;
				}
				if (Faceval[j] == (Faceval[i] + 1)) {
					count++;
				}
				if (count >= 8) {
					straight = true;
				}
			}
		}
	}


	if ((*max_s[0] >= 5) &&
		(*max_faceval - *min_faceval >= 4 && *max_faceval - *min_faceval <= 4) &&
		*max_f[0] >= 1 && *max_faceval >= 12 && hand) {
		cout << "You got a Royal Flush." << "\n \n";
		hand = false;
		if (bet < 5) {
			bank += bet * 250;
		}
		else {
			bank += bet * 800;
		}
	}

	if (*max_s[0] >= 5 && straight && hand) {
		cout << "You got a Straight Flush." << "\n \n";
		hand = false;
		if (bet < 5) {
			bank += bet * 50;
		}
		else {
			bank += bet * 100;
		}
	}

	if (*max_f[0] >= 4 && hand) {
		cout << "You got a Four of a Kind." << "\n \n";
		hand = false;
		bank += bet * 25;
	}

	if (*max_f[0] >= 3 && (*max_f[1] >= 2 || *max_f[2] >= 2 || *max_f[3] >= 2 || *max_f[4] >= 2) && hand) {
		cout << "You got a Full House." << "\n \n";
		hand = false;
		bank += bet * 9;
	}

	if (*max_s[0] >= 5 && hand) {
		cout << "You got a Flush." << "\n \n";
		hand = false;
		bank += bet * 6;
	}

	if (straight && hand) {
		cout << "You got a Straight." << "\n \n";
		hand = false;
		bank += bet * 4;
	}

	if (*max_f[0] >= 3 && hand) {
		cout << "You got a Three of a Kind." << "\n \n";
		hand = false;
		bank += bet * 3;
	}

	int paircount = 0;

	for (int i = 0; i < 4; ++i) {
		if (f[i] >= 2) {
			paircount++;
		}
	}

	if (paircount >= 2 && hand) {
		cout << "You got a Two Pair." << "\n \n";
		hand = false;
		bank += bet * 2;
	}

	bool jacks_or_better = false;
	int count2 = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (Faceval[i] = Faceval[j] && Faceval[i] >= 9) {
				count2++;
			}
			if (count2 >= 2) {
				jacks_or_better = true;
			}
		}
	}

	if (jacks_or_better && hand) {
		cout << "You got a Pair." << "\n \n";
		hand = false;
		bank += bet * 1;
	}

	if (hand)
	{
		cout << " You got nothing." << "\n \n";
		hand = false;
	}

}

int main() {
	while (cont != "quit") {
		deque<Card> deck;
		for (int i = 0; i < 52; i++) {
			switch (i / 13) {
			case 0: deck.push_back(Card(CLUBS, i % 13)); break;
			case 1: deck.push_back(Card(DIAMONDS, i % 13)); break;
			case 2: deck.push_back(Card(HEARTS, i % 13)); break;
			case 3: deck.push_back(Card(SPADES, i % 13)); break;
			default: cout << "undefined behavior \n"; break;
			}
		}

		srand(unsigned(std::time(0)));
		random_shuffle(deck.begin(), deck.end(), randomizer);

		if (beginning_sequence == 0) {
			cout << "      #                                                          ######                                         ###\n";
			cout << "      #    ##     ####   #    #   ####        ####   #####       #     #  ######  #####  #####  ######  #####   ###\n";
			cout << "      #   #  #   #    #  #   #   #           #    #  #    #      #     #  #         #      #    #       #    #  ###\n";
			cout << "      #  #    #  #       ####     ####       #    #  #    #      ######   #####     #      #    #####   #    #   # \n";
			cout << "#     #  ######  #       #  #         #      #    #  #####       #     #  #         #      #    #       #####      \n";
			cout << "#     #  #    #  #    #  #   #   #    #      #    #  #   #       #     #  #         #      #    #       #   #   ###\n";
			cout << " #####   #    #   ####   #    #   ####        ####   #    #      ######   ######    #      #    ######  #    #  ###" << "\n\n";


			do {
				cout << "Press enter to begin.";
			} while (cin.get() != '\n');
		}

		beginning_sequence++;


		if (bank <= 0) {
			cout << "Here is some money to play with." << endl;
			debt = debt - bank + 50;
			bank = 0;
			cout << "You are now " << debt << " coins in debt." << "\n\n";
		}
	badbet:

		cout << "Please enter your bet and press enter: " << "\n\n";
		cin >> bet;

		if (cin.fail()) {
			cout << "Invalid response." << "\n\n";
			cin.clear(); cin.ignore();
			goto badbet;
		}

		if (bet > bank) {
			cout << "You bet more than your bank.\n";
			cout << "Don't worry I will spot you but you gotta pay me back.\n\n";
		}

		bank = bank - bet;

		cout << "Initial Deal: " << "\n \n";
		for (int i = 0; i < 5; ++i) {
			Face[i] = deck.begin()->getFace();
			Suit[i] = deck.begin()->getSuit();
			Faceval[i] = deck.begin()->getFacevalue();
			Suitval[i] = deck.begin()->getSuitvalue();
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			deck.pop_front();
		}

		bool a, b, c, d, e;
		cout << "Input 5 1s or 0s separated by a space: 1 to hold a card and a 0 to discard."
			<< "\n After you finish entering the values hit enter." << "\n \n";
	badinput:
		cin >> a >> b >> c >> d >> e;
		if (cin.fail()) {
			cout << "Invalid response." << "\n\n";
			cin.clear(); cin.ignore();
			goto badinput;
		}


		if (a == 1) {
			cout << Face[0] << " of " << Suit[0] << "\n \n";
		}
		if (a == 0) {
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			Face[0] = deck.begin()->getFace();
			Suit[0] = deck.begin()->getSuit();
			Faceval[0] = deck.begin()->getFacevalue();
			Suitval[0] = deck.begin()->getSuitvalue();
			deck.pop_front();
		}


		if (b == 1) {
			cout << Face[1] << " of " << Suit[1] << "\n \n";
		}
		if (b == 0) {
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			Face[1] = deck.begin()->getFace();
			Suit[1] = deck.begin()->getSuit();
			Faceval[1] = deck.begin()->getFacevalue();
			Suitval[1] = deck.begin()->getSuitvalue();
			deck.pop_front();
		}

		if (c == 1) {
			cout << Face[2] << " of " << Suit[2] << "\n \n";
		}
		if (c == 0) {
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			Face[2] = deck.begin()->getFace();
			Suit[2] = deck.begin()->getSuit();
			Faceval[2] = deck.begin()->getFacevalue();
			Suitval[2] = deck.begin()->getSuitvalue();
			deck.pop_front();
		}

		if (d == 1) {
			cout << Face[3] << " of " << Suit[3] << "\n \n";
		}
		if (d == 0) {
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			Face[3] = deck.begin()->getFace();
			Suit[3] = deck.begin()->getSuit();
			Faceval[3] = deck.begin()->getFacevalue();
			Suitval[3] = deck.begin()->getSuitvalue();
			deck.pop_front();
		}

		if (e == 1) {
			cout << Face[4] << " of " << Suit[4] << "\n \n";
		}
		if (e == 0) {
			cout << deck.begin()->getFace() << " of " << deck.begin()->getSuit() << "\n \n";
			Face[4] = deck.begin()->getFace();
			Suit[4] = deck.begin()->getSuit();
			Faceval[4] = deck.begin()->getFacevalue();
			Suitval[4] = deck.begin()->getSuitvalue();
			deck.pop_front();
		}

		calc_hand();

		deck.clear();

		cout << "Your current bank is: " << bank << "\n\n";

		cout << "Type 'quit' then hit enter to quit. Hit any other key and enter to continue." << "\n \n";

		cin >> cont;
		cin.clear();


	}
	return 0;
}


