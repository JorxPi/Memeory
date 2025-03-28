#pragma once

#include "Script.h"
#include "CardScript.h"
#include "TextScript.h"

using namespace std;

class CardScript;

class GameManager
{
public:
    GameManager();
    void shuffleCardsId(int arr[], int size);
    void checkIfPair();
    void flipCard(CardScript* cscr);
    void setCard1ScriptRef(CardScript* cscr);
    void setCard2ScriptRef(CardScript* cscr);
    void setTextScriptRef(TextScript* wins, TextScript* mems, TextScript* pros);
    void gameOver();
    void startGame();
    void setCardsScriptListRef(CardScript* cscrl, int place);

private:
    int cardsFlipped = 0;
    int totalPairs = 0;
    bool notPair = false;
    CardScript* card1Ref;
    CardScript* card2Ref;
    TextScript* winRef;
    TextScript* memRef;
    TextScript* proRef;
    CardScript* cardsListRef[16];
};