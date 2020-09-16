//============================================================================
// Name        : blackjack.cpp
// Author      : Jackson Xiao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <random>
#include <algorithm>

/*	Basic Rules:
 * 	Payout is 2 to 1, 2.5 to 1 for blackjack
 *	Dealer draws on 16, stand on 17
 * 	6 decks in play
 * 	cannot split hand -> will try to implement after
 */

struct Blackjack_deck {
	std::string suite, card_display;
	int card;

};

class Players {
	public:

		Players (int set_money, std::string set_name) {
			money = set_money;
			name = set_name;
			for (int x = 0; x < 13; x++) {
				cards.push_back(Blackjack_deck());
			}
		}

		int money = 0; //starting money
		std::string name; //player name
		std::vector<Blackjack_deck> cards;
		int bet = 0; //current player bet
		int card_sum = 0;
};

class Cards {
	public:

		Cards () {

			for (int decks = 0; decks < 6; decks++) {
				for (int suite = 0; suite < 4; suite++) {
					for (int num = 0; num < 13; num++) {
						deck.push_back(Blackjack_deck());
						if (suite == 0) {
							deck[decks*52 + suite*13 + num].suite = "Hearts";
						} else if (suite == 1) {
							deck[decks*52 + suite*13 + num].suite = "Diamonds";
						} else if (suite == 2) {
							deck[decks*52 + suite*13 + num].suite = "Spades";
						} else {
							deck[decks*52 + suite*13 + num].suite = "Clubs";
						}
						if (num == 0) {
							deck[decks*52 + suite*13 + num].card_display = "Ace";
							deck[decks*52 + suite*13 + num].card = 1; //need to figure out the 1 or 11
						} else if (num == 1) {
							deck[decks*52 + suite*13 + num].card_display = "2";
							deck[decks*52 + suite*13 + num].card = 2;
						} else if (num == 2) {
							deck[decks*52 + suite*13 + num].card_display = "3";
							deck[decks*52 + suite*13 + num].card = 3;
						} else if (num == 3) {
							deck[decks*52 + suite*13 + num].card_display = "4";
							deck[decks*52 + suite*13 + num].card = 4;
						} else if (num == 4) {
							deck[decks*52 + suite*13 + num].card_display = "5";
							deck[decks*52 + suite*13 + num].card = 5;
						} else if (num == 5) {
							deck[decks*52 + suite*13 + num].card_display = "6";
							deck[decks*52 + suite*13 + num].card = 6;
						} else if (num == 6) {
							deck[decks*52 + suite*13 + num].card_display = "7";
							deck[decks*52 + suite*13 + num].card = 7;
						} else if (num == 7) {
							deck[decks*52 + suite*13 + num].card_display = "8";
							deck[decks*52 + suite*13 + num].card = 8;
						} else if (num == 8) {
							deck[decks*52 + suite*13 + num].card_display = "9";
							deck[decks*52 + suite*13 + num].card = 9;
						} else if (num == 9) {
							deck[decks*52 + suite*13 + num].card_display = "10";
							deck[decks*52 + suite*13 + num].card = 10;
						} else if (num == 10) {
							deck[decks*52 + suite*13 + num].card_display = "Jack";
							deck[decks*52 + suite*13 + num].card = 10;
						} else if (num == 11) {
							deck[decks*52 + suite*13 + num].card_display = "Queen";
							deck[decks*52 + suite*13 + num].card = 10;
						} else if (num == 12) {
							deck[decks*52 + suite*13 + num].card_display = "King";
							deck[decks*52 + suite*13 + num].card = 10;
						}
					}
				}
			}

			auto rng = std::default_random_engine {};
			std::shuffle(std::begin(deck), std::end(deck), rng);

		}

		std::vector<Blackjack_deck> deck;

};

int createNewDeck(int cardCount, Cards oldDeck) {
	if (cardCount == 312) {
		{
			//delete oldDeck; //deletes all content in the vector
		} //when it goes out of scope, the old vector's memory is deallocated
		Cards new_deck; //new card deck is created
		return cardCount = 0; //sets currentcard back to 0
	} else {
		return cardCount; //does not change currentcard
	}
}


int main() {

	bool newgame;
	int numplayers;
	int initial_money;

	do {	//starts game

		std::cout << "Welcome to Blackjack!" << std::endl << "Enter number of players between 1 and 7: ";

		std::cin >> numplayers; //temporary

		//something isn't working
		/*while (numplayers < 1 || numplayers > 7) {
			std::cout << "Invalid range, please enter a number between 1 and 7: ";
			std::cin >> numplayers;
		}

		while (!(std::cin >> numplayers)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Please enter a number for number of players: ";
		}*/

		std::vector<Players> playerlist;
		//Players *playerlist = new Players[numplayers]; <- attempt to create dynamically created array with dynamically created objects
		//int *playerlist = new int[numplayers]; <- however, if constructor has parameters, this does not work

		std::cout << "Enter starting money for all players: ";
		while (!(std::cin >> initial_money)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Please enter a number for starting money:";
		}

		for (int x = 0; x < numplayers; x++) {
			std::string playername;
			std::cout << "Please enter name for Player " << x+1 << ": ";
			std::cin >> playername;

			playerlist.push_back(Players(initial_money, playername));
			//playerlist[x] = new Players(initial_money, playername); <- follow up to attempt to create object within array
		}

		std::string dealer = "Dealer";
		int dealerMoney = 1000;
		playerlist.push_back(Players(dealerMoney, dealer));

		Cards new_deck;
		//std::cout << new_deck.deck[200].suite << new_deck.deck[200].card;

		int round = 1;
		bool current_game_over = false; //whether the current game is over
		int player_bet;
		int current_card = 0; //current card
		std::string stand_hit;

		while (current_game_over == false) { //starts rounds
			std::cout << "Round " << round << std::endl;

			for (int x = 0; x < numplayers; x++) { //each player enters initial bet
				std::cout << playerlist[x].name << std::endl << "Money: $" << playerlist[x].money << std::endl << "Please enter initial bet: ";
				std::cin >> player_bet;
				playerlist[x].bet = player_bet;

			}

			for (int x = 0; x <= numplayers; x++) { //assigns first card
				playerlist[x].cards[0] = new_deck.deck[current_card];
				current_card++;
				current_card = createNewDeck(current_card, new_deck);
			}

			for (int x = 0; x <= numplayers; x++) { //assigns second card
				playerlist[x].cards[1] = new_deck.deck[current_card];
				current_card++;
				current_card = createNewDeck(current_card, new_deck);
			}

			int turn_validate;

			for (int x = 0; x < numplayers; x++) { //navigate through players for hit or stand

				playerlist[x].card_sum = 0;

				std::cout << playerlist[x].name << ": Please enter " << x << " to begin your round: ";
				std::cin >> turn_validate;
				while (turn_validate != x) {
					std::cout << playerlist[x].name << ": Please enter " << x << " to begin your round: ";
					std::cin >> turn_validate;
				}
				std::cout << "Your cards are: " << std::endl << playerlist[x].cards[0].card_display << " of " << playerlist[x].cards[0].suite << std::endl;
				std::cout << playerlist[x].cards[1].card_display << " of " << playerlist[x].cards[1].suite << std::endl;

				playerlist[x].card_sum = playerlist[x].cards[0].card + playerlist[x].cards[1].card;//finds sum
				std::cout << "Your sum is: " << playerlist[x].card_sum << std::endl; // need to add code for Aces (1 or the other)

				if ((playerlist[x].cards[1].card == 1 && playerlist[x].cards[0].card == 10)|| (playerlist[x].cards[0].card == 1 && playerlist[x].cards[1].card == 10)) {
						std::cout << "Blackjack!" << std::endl; //really janky way of implementing aces, should find workaround
						playerlist[x].card_sum = 21;
				} else {
					std::cout << "Would you like to stand or hit? ";
					std::cin >> stand_hit;

					while (stand_hit != "stand" && stand_hit != "hit") { //makes sure user enters hit or stand
						std::cout << "Please enter 'stand' to stand and 'hit' to hit: ";
						std::cin >> stand_hit;
					}

					for (int y = 0; stand_hit == "hit"; y++) { //keeps looping while user chooses hit
						playerlist[x].cards[y + 2] = new_deck.deck[current_card];
						playerlist[x].card_sum += playerlist[x].cards[y + 2].card;
						current_card++;
						current_card = createNewDeck(current_card, new_deck);
						std::cout << "Your cards are: " << std::endl;
						for (int z = 0; z <= y + 2; z++) { //displays all cards in hand
							std::cout << playerlist[x].cards[z].card_display << " of " << playerlist[x].cards[z].suite << std::endl;
						}

						std::cout << "Your sum is: " << playerlist[x].card_sum << std::endl; // need to add code for Aces

						if (playerlist[x].card_sum > 21) {
							std::cout << "Bust!" << std::endl;
							stand_hit = "stand";
						} else if (playerlist[x].card_sum == 21) {
							std::cout << "Blackjack!" << std::endl;
							stand_hit = "stand";
						} else {
							std::cout << "Would you like to stand or hit? ";
							std::cin >> stand_hit;

							while (stand_hit != "stand" && stand_hit != "hit") { //makes sure user enters hit or stand
								std::cout << "Please enter 'stand' to stand and 'hit' to hit: ";
								std::cin >> stand_hit;
							}
						}
					}

				}


			}

			//dealer code
			bool dealer_hit = true;
			playerlist[numplayers].card_sum = playerlist[numplayers].cards[0].card + playerlist[numplayers].cards[1].card; //calculates dealer sum

			std::cout << "The dealer's hand is: " << std::endl << playerlist[numplayers].cards[0].card << " of " << playerlist[numplayers].cards[0].suite << std::endl
			<< playerlist[numplayers].cards[1].card << " of " << playerlist[numplayers].cards[1].suite << std::endl;


			for (int x = 0; dealer_hit == true; x++){ //while sum < 17, dealer hits

				if (playerlist[numplayers].card_sum < 17) { //dealer hits
					playerlist[numplayers].cards[x + 2] = new_deck.deck[current_card];
					playerlist[numplayers].card_sum += playerlist[numplayers].cards[x + 2].card;
					current_card++;
					current_card = createNewDeck(current_card, new_deck);

					std::cout << playerlist[numplayers].cards[x + 2].card << " of " << playerlist[numplayers].cards[x + 2].suite << std::endl;
					//displays any additional cards the dealer drew
				} else {
					dealer_hit = false;
				}
			}

			std::cout << "The dealer's sum is: " << playerlist[numplayers].card_sum << std::endl;//displays dealer's cards

			for (int x = 0; x < numplayers; x++) { //loops through each player to see if they won/lost
				if (playerlist[numplayers].card_sum <= 21) { //if dealer has < 21

					if (playerlist[x].card_sum > playerlist[numplayers].card_sum && playerlist[x].card_sum <= 21) { //if player has > dealer but <= 21
						playerlist[x].money += playerlist[x].bet; //player gains
						playerlist[numplayers].money -= playerlist[x].bet; //dealer loses
						std::cout << playerlist[x].name << " has won: $" << playerlist[x].bet << std::endl;

					} else if (playerlist[x].card_sum == playerlist[numplayers].card_sum) { //player and dealer ties
						std::cout << playerlist[x].name << " keeps his bet" << std::endl;

					} else { //if player has < dealer or > 21
						std::cout << playerlist[x].name << " has lost: $" << playerlist[x].bet << std::endl;
						playerlist[x].money -= playerlist[x].bet;
						playerlist[numplayers].money += playerlist[x].bet;
					}

				} else { //dealer busts

					if (playerlist[x].card_sum <= 21) { //player <= 21, wins
						playerlist[x].money += playerlist[x].bet; //player gains
						playerlist[numplayers].money -= playerlist[x].bet; //dealer loses
						std::cout << playerlist[x].name << " has won: $" << playerlist[x].bet << std::endl;

					} else { //player > 21, loses
						std::cout << playerlist[x].name << " has lost: $" << playerlist[x].bet << std::endl;
						playerlist[x].money -= playerlist[x].bet;
						playerlist[numplayers].money += playerlist[x].bet;
					}
				}
			} // end of round-based code

			round++;

			//current_game_over = true; //testing

		}

		newgame = false; // testing

	} while (newgame == true);

	return 0;
}
