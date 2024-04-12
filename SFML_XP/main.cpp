#include <iostream>
#include <SFML/Graphics.hpp>

#include "borders.hpp"

int main(int argc, char* argv[])
{
	const int width = 1000;
	const int height = 800;
	bool borderless = true;
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!", borderless ? sf::Style::None : sf::Style::Default);

	sf::Color bg(230, 234, 216);


	bool windowDragged = false;
	sf::Vector2i mousePositionDragged(0, 0);
	sf::Vector2i windowPosition(window.getPosition());
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q)
					window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Check if mouse is on titlebar
					if (isMouseInTitleBar(window, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						windowDragged = true;
						mousePositionDragged.x = event.mouseButton.x;
						mousePositionDragged.y = event.mouseButton.y;
					}

					if (isMouseOnCloseButton(window, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						windowDragged = false;

				}

			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (isMouseOnCloseButton(window, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						window.close();

					// Check if mouse is on titlebar
					if (isMouseInTitleBar(window, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						windowDragged = false;

				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (windowDragged)
				{
					sf::Vector2i mouseCurrentPosition(event.mouseMove.x, event.mouseMove.y);
					windowPosition += mouseCurrentPosition - mousePositionDragged;
					window.setPosition(windowPosition);
				}
			}
		}

		window.clear(bg);
		drawBorders(window);
		drawRoundedRectangle(window, 100);
		window.display();
	}

	return 0;
}