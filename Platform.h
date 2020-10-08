#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform(std::string windowTitle, sf::Vector2u windowSize, sf::Vector2u textureSize);
	~Platform();

	void Update(uint8_t* displayBuffer);
	bool ProcessInput(uint8_t* keypad);

private:
	sf::Texture* InitTexture(sf::Vector2u size);
	sf::Sprite* InitSprite(sf::Texture* baseTexture, sf::Vector2u scale);

	sf::RenderWindow* window{};
	sf::Texture* displayTexture{};
	sf::Sprite* displaySprite{};
};

