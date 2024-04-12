#pragma once

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

void drawBorders(sf::RenderWindow& window);
bool isMouseInTitleBar(sf::RenderWindow& window, sf::Vector2f mousePosition);
bool isMouseOnCloseButton(sf::RenderWindow& window, sf::Vector2f mousePosition);
void drawRoundedRectangle(sf::RenderWindow& window, int pointsPerCorner);