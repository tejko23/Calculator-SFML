#include "Button.hpp"
#include <iostream>
//#include <SFML\Window\Mouse.hpp>

using namespace std;

Button::Button(std::string val, float posx, float posy, sf::Uint32 col,
			float sizex, float sizey) : value(val), color(col)
{
	rec.setFillColor(sf::Color(color));
	rec.setSize(sf::Vector2f(sizex, sizey));
	rec.setOrigin(0, 0);
	rec.setPosition(posx, posy);

	recin.setFillColor(sf::Color(color));
	recin.setSize(sf::Vector2f(sizex-4, sizey-4));
	recin.setOrigin(0, 0);
	recin.setPosition(posx+2, posy+2);

	font.loadFromFile("fonts/Digital-Medium.ttf");
	txt.setFont(font);
	txt.setString(value);
	txt.setCharacterSize(30);
	txt.setFillColor(sf::Color::White);
	
	txt.setPosition(sf::Vector2f(posx + (sizex / 2.5), posy + 5));

	shader.loadFromMemory(VertexShader, RadialGradient);
	shader.setParameter("windowHeight", static_cast<float>(500)); // this must be set, but only needs to be set once (or whenever the size of the window changes)
	shader.setParameter("color", sf::Color(170, 170, 170));
	shader.setParameter("radius", 70.f);
	shader.setParameter("expand", 0.f);

	shader2.loadFromMemory(VertexShader, RadialGradient);
	shader2.setParameter("windowHeight", static_cast<float>(500)); // this must be set, but only needs to be set once (or whenever the size of the window changes)
	shader2.setParameter("color", sf::Color(170, 170, 170));
	if (sizex == 162) {
		shader2.setParameter("radius", 180.f);
	}
	else shader2.setParameter("radius", 100.f);
	
	shader2.setParameter("expand", 0.f);

	mouse_pos = sf::Vector2f(0, 0);
}

string Button::selected() {
	if (active) {
		recin.setFillColor(sf::Color(170, 170, 170));
		return value;
	}
	else {
		recin.setFillColor(sf::Color(0x12020cff));
		return "";
	}
	
}

void Button::deselected() {
	recin.setFillColor(sf::Color(color));
}

void Button::update(sf::RenderWindow* win, std::string command) {
	if (!window) {
		window = win;
	}

	if (commandlist != command) {
		commandlist = command;
		size_t pos;
		pos = value.find_first_of(commandlist);
		if (pos != string::npos) active = false;
		else active = true;

		if (value == "<-") active = true;
	}

	if (active) {
		shader.setParameter("color", sf::Color(170, 170, 170));
		shader2.setParameter("color", sf::Color(170, 170, 170));
	}
	else {
		shader.setParameter("color", sf::Color(0xC13236ff));
		shader2.setParameter("color", sf::Color(0x12020cff));
	}

	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window));
	shader.setParameter("center", sf::Vector2f(mouse_pos));
	shader2.setParameter("center", sf::Vector2f(mouse_pos));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rec, &shader);
	if (rec.getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
		target.draw(recin, &shader2);
	}
	else target.draw(recin, states);
	target.draw(txt, states);
}