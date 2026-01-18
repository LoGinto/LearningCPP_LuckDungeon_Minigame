#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Renderer.h"

class Game {
private:
    Character* player;
    Character* enemy;
    Renderer renderer;

    char coinToss();

public:
    Game(Character* p, Character* e);
    void BattleRound();
    void start();
};

#endif