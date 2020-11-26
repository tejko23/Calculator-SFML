#pragma once

#include "Button.hpp"
#include "Tscreen.hpp"
#include <vector>


class Tcalculator : public sf::Drawable {
public:
	Tscreen mDisplay;
	std::vector <std::unique_ptr<Button>> all;

	Tcalculator(sf::RenderWindow* act_window);
	void update(const sf::Event& event);

private:
	sf::RenderWindow* window;
	bool ask = true;
	std::string listofButtons{};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};