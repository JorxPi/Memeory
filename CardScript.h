#pragma once

#include "Script.h"
#include "GameManager.h"

using namespace std;

class GameManager;

class CardScript : public Script
{

    using Script::Script;

public:

    void tickScript(float deltaTime) override;
    void assignIdAndPos(int cardList, int xpos, int ypos);
    void flipCard();
    void unflipCard();
    int getId() {
        return id;
    }
    bool getFlipped() {
        return flipped;
    }
    void setGameManagerRef(GameManager* gmr);
    void turnVisible(bool visibility);

private:
    int xpos;
    int ypos;
    int id;
    int card_clicked = -1;
    bool flipped = false;
    bool paired = false;
    bool keepUp = false;
    //void assignId(int cardList);

    GameManager* gameRef;

};
