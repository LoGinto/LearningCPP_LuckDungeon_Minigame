#pragma once

#include <SFML/Graphics.hpp>

class Renderer {
private:
    sf::RenderWindow window;

    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture coinHeadsTexture;
    sf::Texture coinTailsTexture;

    sf::Sprite playerSprite;
    sf::Sprite enemySprite;
    sf::Sprite coinSprite;

    static sf::Texture loadTexture(const std::string& path);
    void drawHealthBars(int playerHealth, int enemyHealth);
    void drawSingleHealthBar(sf::Vector2f center, float barWidth, int health);
    sf::Color getBarColor(float ratio);

public:
    Renderer();

    bool isOpen() const;
    void processEvents();
    void clear();
    void display();
    void showCoinFlip(bool isHeads, int playerHealth, int enemyHealth);
    void draw(sf::Vector2f playerPosition, sf::Vector2f enemyPosition,
              int playerHealth, int enemyHealth);

    sf::Sprite& getCoinSprite()             { return coinSprite; }
    sf::Texture& getCoinHeadsTexture()      { return coinHeadsTexture; }
    sf::Texture& getCoinTailsTexture()      { return coinTailsTexture; }
    sf::RenderWindow& getWindow()           { return window; }
};