#include "Renderer.h"
#include <iostream>
#include <algorithm>
#include <cmath>

sf::Texture Renderer::loadTexture(const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << "\n";
    }
    return texture;
}

sf::Color Renderer::getBarColor(float ratio) {
    if (ratio <= 0.3f) return sf::Color::Red;
    if (ratio <= 0.6f) return sf::Color(255, 255, 0);
    return sf::Color::Green;
}

Renderer::Renderer()
    : window(sf::VideoMode({800u, 600u}), "Luck Dungeons"),
      playerTexture(loadTexture("Assets/player.png")),
      enemyTexture(loadTexture("Assets/enemy.png")),
      coinHeadsTexture(loadTexture("Assets/coin_heads.png")),
      coinTailsTexture(loadTexture("Assets/coin_tails.png")),
      playerSprite(playerTexture),
      enemySprite(enemyTexture),
      coinSprite(coinHeadsTexture)
{
    if (!playerTexture.loadFromFile("Assets/player.png")) std::cerr << "Player texture fail\n";
    if (!enemyTexture.loadFromFile("Assets/enemy.png")) std::cerr << "Enemy texture fail\n";
    if (!coinHeadsTexture.loadFromFile("Assets/coin_heads.png")) std::cerr << "Heads fail\n";
    if (!coinTailsTexture.loadFromFile("Assets/coin_tails.png")) std::cerr << "Tails fail\n";

    playerSprite.setOrigin({playerSprite.getLocalBounds().size.x / 2.f,
                            playerSprite.getLocalBounds().size.y / 2.f});
    enemySprite.setOrigin({enemySprite.getLocalBounds().size.x / 2.f,
                           enemySprite.getLocalBounds().size.y / 2.f});
    coinSprite.setOrigin({coinSprite.getLocalBounds().size.x / 2.f,
                          coinSprite.getLocalBounds().size.y / 2.f});

    playerSprite.setScale({0.85f, 0.85f});
    enemySprite.setScale({1.25f, 1.25f});
    coinSprite.setScale({0.5f, 0.5f});

    playerSprite.setPosition({300.f, 450.f});
    enemySprite.setPosition({400.f, 250.f});
    coinSprite.setPosition({400.f, 300.f});

    window.setVerticalSyncEnabled(true);
}

bool Renderer::isOpen() const { return window.isOpen(); }

void Renderer::processEvents() {
    while (auto ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) window.close();
    }
}

void Renderer::clear() { window.clear(sf::Color::Black); }

void Renderer::display() { window.display(); }

void Renderer::draw(sf::Vector2f pPos, sf::Vector2f ePos, int pHp, int eHp) {
    playerSprite.setPosition(pPos);
    enemySprite.setPosition(ePos);

    window.draw(playerSprite);
    window.draw(enemySprite);
    drawHealthBars(pHp, eHp);
}

void Renderer::drawHealthBars(int pHealth, int eHealth) {
    drawSingleHealthBar(playerSprite.getPosition(), 80.f, pHealth);
    drawSingleHealthBar(enemySprite.getPosition(), 120.f, eHealth);
}
void Renderer::showCoinFlip(bool isHeads, int playerHealth, int enemyHealth) {
    if (isHeads) {
        coinSprite.setTexture(coinHeadsTexture);
    } else {
        coinSprite.setTexture(coinTailsTexture);
    }

    coinSprite.setPosition({400.f, 300.f});

    clear();
    window.draw(playerSprite);
    window.draw(enemySprite);
    drawHealthBars(playerHealth, enemyHealth);
    window.draw(coinSprite);
    display();
}

void Renderer::drawSingleHealthBar(sf::Vector2f center, float barWidth, int health) {
    const float h = 12.f;
    const float o = 2.f;

    const sf::Sprite& s = (barWidth == 80.f) ? playerSprite : enemySprite;

    auto b = s.getLocalBounds();
    float sy = s.getScale().y;
    float top = center.y - (b.size.y * sy / 2.f);
    float y = top - 30.f;
    float x = center.x - barWidth / 2.f;

    sf::RectangleShape bg({barWidth, h});
    bg.setPosition({x, y});
    bg.setFillColor(sf::Color(40,40,40));
    bg.setOutlineThickness(o);
    bg.setOutlineColor(sf::Color(120,40,40));
    window.draw(bg);

    float r = std::max(0.f, std::min(1.f, static_cast<float>(health) / 3.f));

    if (r > 0.f) {
        sf::Color c = getBarColor(r);
        sf::RectangleShape fg({barWidth * r, h});
        fg.setPosition({x, y});
        fg.setFillColor(c);
        window.draw(fg);
    }
}