#pragma once
#include <SFML\Graphics.hpp>

class Tscreen : public sf::Drawable {
public:
	Tscreen();
	void addValue(std::string);
	std::string askforButtons();

	sf::Text expression;
	sf::String exp{};

private:
	sf::RectangleShape display;
	
	sf::Font font;
	sf::Text result;

	int nofop{}; //amount of opening parentheses
	int nofcp{}; //amount of closing parentheses

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(display, states);
		target.draw(expression, states);
		target.draw(result, states);
	}

	bool findDot();
};