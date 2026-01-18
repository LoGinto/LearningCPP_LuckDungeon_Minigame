#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#pragma comment(lib, "winmm.lib")

Game::Game(Character* p, Character* e) {
    player = p;
    enemy = e;
}

char Game::coinToss() {
    return (rand() % 2 == 0) ? 'H' : 'T';
}

void Game::BattleRound() {
    char playerBet;

    // Force console window to front and visible
    HWND console = GetConsoleWindow();
    SetForegroundWindow(console);
    ShowWindow(console, SW_RESTORE);

    std::cout << "Choose your bet (H/T): ";
    std::cin >> playerBet;
    playerBet = toupper(playerBet);

    if (playerBet != 'H' && playerBet != 'T') {
        std::cout << "Invalid choice! Please choose H or T." << std::endl;
        return;
    }

    std::cout << "Tossing the coin..." << std::endl;
    std::cout.flush();
    PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);

    char result = coinToss();
    bool isHeads = (result == 'H');

    // Show coin flip result (assuming you have showCoinFlip in Renderer)
    renderer.showCoinFlip(isHeads, player->health, enemy->health);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    if (playerBet == result) {
        std::cout << "You won this round! Enemy takes 1 damage." << std::endl;
        enemy->takeDamage(1);
    } else {
        std::cout << "You lost this round! You take 1 damage." << std::endl;
        player->takeDamage(1);
    }

    std::cout << "\nPlayer stats\n";
    player->showStats();
    std::cout << "\nEnemy stats\n";
    enemy->showStats();
}

void Game::start() {
    while (renderer.isOpen() && player->isAlive() && enemy->isAlive()) {
        renderer.processEvents();
        renderer.clear();
        renderer.draw({300.f, 450.f}, {400.f, 250.f}, player->health, enemy->health);
        BattleRound();
    }

    if (player->isAlive()) {
        std::cout << "Congratulations! You have defeated the enemy!" << std::endl;
    } else {
        std::cout << "You have been defeated. Game Over." << std::endl;
    }
}