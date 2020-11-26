#pragma once
#include "Tcalculator.hpp"
#include <SFML/Window.hpp>

class Tapplication {
public:
	Tapplication();
	void run();

private:
	sf::RenderWindow window;
	Tcalculator calc;
};