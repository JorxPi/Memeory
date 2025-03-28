#include "GameManager.h"
#include <algorithm>
#include <random>


GameManager::GameManager() {

}

void GameManager::shuffleCardsId(int arr[], int size) {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(arr, arr + size, g);
}

void GameManager::checkIfPair() {
	if (card1Ref->getId() == card2Ref->getId()) {
		//cout << "ITS A PAIR" << endl;
		totalPairs++;
		if (totalPairs == 8) {
			gameOver();
		}
	}
	else {
		//cout << "ITS NOT A PAIR" << endl;
		notPair = true;
		
	}
}

void GameManager::flipCard(CardScript* cscr) {
	if (cardsFlipped == 0 && notPair) {
		card1Ref->unflipCard();
		card2Ref->unflipCard();
	}

	if (cardsFlipped == 0) {
		notPair = false;
		setCard1ScriptRef(cscr);
		cardsFlipped += 1;
	}
	else {
		setCard2ScriptRef(cscr);
		checkIfPair();
		cardsFlipped = 0;
	}
}

void GameManager::setCard1ScriptRef(CardScript* cscr) {
	card1Ref = cscr;
}

void GameManager::setCard2ScriptRef(CardScript* cscr) {
	card2Ref = cscr;
}

void GameManager::setTextScriptRef(TextScript* wins, TextScript* mems, TextScript* pros) {
	winRef = wins;
	memRef = mems;
	proRef = pros;
}

void GameManager::gameOver() {
	//cout << "You WIN" << endl;
	memRef->turnVisible(false);

	int i = 0;

	while (i < 16) {
		cardsListRef[i]->turnVisible(false);
		i++;
	}

	winRef->turnVisible(true);
	proRef->turnVisible(true);
}

void GameManager::startGame() {
	memRef->turnVisible(true);

	int i = 0;

	while (i<16) {
		cardsListRef[i]->turnVisible(true);
		i++;
	}
}

void GameManager::setCardsScriptListRef(CardScript* cscrl, int place) {
	cardsListRef[place] = cscrl;
}