#include "borders.hpp"

/*
* Add options for top-right controls
*/
void drawTitleBar(sf::RenderWindow& window)
{
	sf::Vector2f dimensions(window.getSize().x, 32);
	sf::RectangleShape bar(dimensions);

	sf::Color backgroundColour(8, 27, 203);
	bar.setFillColor(backgroundColour);

	window.draw(bar);

	// Top-left round corner
	sf::RectangleShape mask(sf::Vector2f(10, 10));
	mask.setFillColor(sf::Color::White);
	window.draw(mask);

	sf::CircleShape leftCorner(10);
	leftCorner.setFillColor(backgroundColour);
	window.draw(leftCorner);

	// Top-right round corner
	mask.setPosition(window.getSize().x - 10, 0);
	window.draw(mask); // ?? Can I actually do that ??

	sf::CircleShape rightCorner(10);
	rightCorner.setFillColor(backgroundColour);
	rightCorner.setPosition(window.getSize().x - 2*rightCorner.getRadius(), rightCorner.getPosition().y);
	window.draw(rightCorner);
}

enum BorderPlacement
{
	LEFT,
	RIGHT,
	BOTTOM
};

void drawThinBorder(sf::RenderWindow& window, BorderPlacement placement)
{
	sf::Vector2f dimensions(window.getSize());
	sf::Vector2f position(0, 0);

	switch (placement)
	{
		case LEFT:
			dimensions.x = 4;
			position.y = 32;
			break;

		case RIGHT:
			dimensions.x = 4;
			position.x = window.getSize().x - dimensions.x;
			position.y = 32;
			break;

		default:
			dimensions.y = 4;
			position.y = window.getSize().y - dimensions.y;
	}

	sf::RectangleShape border(dimensions);
	sf::Color backgroundColour(8, 27, 203);
	border.setFillColor(backgroundColour);

	border.setPosition(position);

	window.draw(border);
}

enum ButtonType
{
	CLOSE,
	MAXIMIZE,
	MINIMIZE
};

/**
* Draws cross at the center of a 20x20 square whose top-left corner is at _topLeftCorner_
*/
void drawCloseCrossShape(sf::RenderWindow& window, sf::Vector2f topLeftCorner)
{
	sf::RectangleShape rect(sf::Vector2f(14, 2));
	rect.setFillColor(sf::Color::White);
	rect.setOrigin(sf::Vector2f(7, 1));

	rect.rotate(45);

	sf::Vector2f position(topLeftCorner);
	position.x += 10;
	position.y += 10;
	rect.setPosition(position);

	window.draw(rect);

	rect.rotate(90);
	window.draw(rect);
}

void drawMinimizeShape(sf::RenderWindow& window, sf::Vector2f topLeftCorner)
{
	sf::RectangleShape rect(sf::Vector2f(8, 3));
	rect.setFillColor(sf::Color::White);

	sf::Vector2f position(topLeftCorner);
	position.x += 4;
	position.y += 13;
	rect.setPosition(position);

	window.draw(rect);
}

void drawMaximizeShape(sf::RenderWindow& window, sf::Vector2f topLeftCorner)
{
	sf::RectangleShape top(sf::Vector2f(12, 3));
	top.setFillColor(sf::Color::White);
	top.setOrigin(sf::Vector2f(6, 1.5));

	sf::Vector2f position(topLeftCorner);
	position.x += 10;
	position.y += 5;
	top.setPosition(position);

	window.draw(top);

	sf::RectangleShape side(sf::Vector2f(1, 10));
	side.setFillColor(sf::Color::White);

	position = topLeftCorner;
	position.x += 4;
	position.y += 7;
	side.setPosition(position);
	window.draw(side);

	position.x += 12 - 1;
	side.setPosition(position);
	window.draw(side);


	sf::RectangleShape bottom(sf::Vector2f(10, 1));
	bottom.setFillColor(sf::Color::White);

	position = topLeftCorner;
	position.x += 5;
	position.y += 16;
	bottom.setPosition(position);
	window.draw(bottom);
}

void drawTitleBarButton(sf::RenderWindow& window, ButtonType type)
{
	sf::Vector2f dimensions(20, 20);

	sf::Vector2f position(window.getSize().x - dimensions.x - 2 * 4, 2 * 4);
	sf::Color fillColor(0, 98, 234);
	void (*drawAppropriateShape)(sf::RenderWindow&, sf::Vector2f) = nullptr;
	switch (type)
	{
		case CLOSE:
			fillColor.r = 255;
			fillColor.g = 0;
			fillColor.b = 0;
			drawAppropriateShape = drawCloseCrossShape;
			break;

		case MAXIMIZE:
			position.x -= 25;
			drawAppropriateShape = drawMaximizeShape;
			break;

		case MINIMIZE:
			position.x -= 2 * 25;
			drawAppropriateShape = drawMinimizeShape;
			break;
	}

	sf::RectangleShape button(dimensions);
	button.setPosition(position);
	button.setFillColor(fillColor);
	button.setOutlineThickness(1);
	button.setOutlineColor(sf::Color::White);

	window.draw(button);
	if (drawAppropriateShape != nullptr)
		drawAppropriateShape(window, position);
}

void drawBorders(sf::RenderWindow& window)
{
	drawTitleBar(window);
	drawThinBorder(window, BorderPlacement::LEFT);
	drawThinBorder(window, BorderPlacement::RIGHT);
	drawThinBorder(window, BorderPlacement::BOTTOM);

	drawTitleBarButton(window, ButtonType::CLOSE);
	drawTitleBarButton(window, ButtonType::MAXIMIZE);
	drawTitleBarButton(window, ButtonType::MINIMIZE);
}

bool isMouseInTitleBar(sf::RenderWindow& window, sf::Vector2f mousePosition)
{
	return mousePosition.y <= 32;
}

bool isMouseOnCloseButton(sf::RenderWindow& window, sf::Vector2f mousePosition)
{
	float topLeftX = window.getSize().x - 20 - 2 * 4;
	float topLeftY = 2 * 4;

	return topLeftX <= mousePosition.x && mousePosition.x <= topLeftX + 20
		&& topLeftY <= mousePosition.y && mousePosition.y <= topLeftY + 20;
}

void drawRoundedRectangle(sf::RenderWindow& window, int pointsPerCorner)
{
	sf::ConvexShape shape;
	//sf::Vector2f position(window.getSize().x / 2, window.getSize().y / 2);
	sf::Vector2f position(200, 200);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Green);

	shape.setPointCount(pointsPerCorner * 4);
	//shape.setPointCount(8);

	float width = 200;
	float height = 100;
	float roundRadius = 10;
	float pi = atan(1) * 4;
	float step = (pi / 2) / pointsPerCorner;
	//std::cout << "step = " << step << std::endl;
	int index = 0;
	//sf::Vector2f shift(roundRadius, -roundRadius);
	sf::Vector2f shift(0, 0);

	// First quarter: t € [pi/2, pi]
	//std::cout << "First quarter" << std::endl;
	for (float t = pi / 2; t <= pi; t += step)
	{
		sf::Vector2f pos = position + sf::Vector2f(roundRadius * cos(t), -roundRadius * sin(t));
		shape.setPoint(index, pos);
		//std::cout << "[Point #" << index << "] x: " << pos.x << ", y: " << pos.y << std::endl;
		index++;
	}

	// Second quarter : t € [pi, 3pi/2]
	//std::cout << "Second quarter" << std::endl;
	for (float t = pi; t <= 3 * pi / 2; t += step)
	{
		sf::Vector2f pos = position + sf::Vector2f(roundRadius * cos(t), height - roundRadius * sin(t));
		shape.setPoint(index, pos);
		//std::cout << "[Point #" << index << "] x: " << pos.x << ", y: " << pos.y << std::endl;
		index++;
	}

	// Third quarter : t € [3pi/2, 2pi]
	//std::cout << "Third quarter" << std::endl;
	for (float t = 3*pi/2; t <= 2 * pi; t += step)
	{
		sf::Vector2f pos = position + sf::Vector2f(width + roundRadius * cos(t), height - roundRadius * sin(t));
		shape.setPoint(index, pos);
		//std::cout << "[Point #" << index << "] x: " << pos.x << ", y: " << pos.y << std::endl;
		index++;
	}

	// Fourth quarter : t € [0, pi/2]
	//std::cout << "Fourth quarter" << std::endl;
	for (float t = 0; t <= pi / 2; t += step)
	{
		sf::Vector2f pos = position + sf::Vector2f(width + roundRadius * cos(t), -roundRadius * sin(t));
		shape.setPoint(index, pos);
		//std::cout << "[Point #" << index << "] x: " << pos.x << ", y: " << pos.y << std::endl;
		index++;
	}

	//std::cout << "index = " << index << std::endl;
	//std::cout << "pointsPerCorner * 4 = " << pointsPerCorner * 4 << std::endl;

	window.draw(shape);
}