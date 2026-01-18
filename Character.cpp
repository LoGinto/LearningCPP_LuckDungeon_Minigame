#include "Character.h"
#include <iostream>

Character::Character(std::string characterName, int hp, int lk) {
    name = characterName;
    health = hp;
    luck = lk;
}

void Character::showStats() const {
    std::cout << "Character: " << name << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Luck: " << luck << std::endl;
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}