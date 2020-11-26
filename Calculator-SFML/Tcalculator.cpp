#include "Tcalculator.hpp"
#include <iostream>

using namespace std;

Tcalculator::Tcalculator(sf::RenderWindow* act_window) : window(act_window){
	std::unique_ptr<Button> button_op = std::make_unique<Button>("(", 
		5, 155, 0x292428ff, 162);
	all.push_back(std::move(button_op));

	std::unique_ptr<Button> button_cp = std::make_unique<Button>(")", 
		169, 155, 0x292428ff, 162);
	all.push_back(std::move(button_cp));

	std::unique_ptr<Button> button_ce = std::make_unique<Button>("CE", 
		5, 212, 0x292428ff);
	all.push_back(std::move(button_ce));

	std::unique_ptr<Button> button_c = std::make_unique<Button>("C", 
		87, 212, 0x292428ff);
	all.push_back(std::move(button_c));

	std::unique_ptr<Button> button_back = std::make_unique<Button>("<-", 
		169, 212, 0x292428ff);
	all.push_back(std::move(button_back));

	std::unique_ptr<Button> button_plus = std::make_unique<Button>("+", 
		251, 212, 0x292428ff);
	all.push_back(std::move(button_plus));

	std::unique_ptr<Button> button_one = std::make_unique<Button>("1", 
		5, 269);
	all.push_back(std::move(button_one));

	std::unique_ptr<Button> button_two = std::make_unique<Button>("2", 
		87, 269);
	all.push_back(std::move(button_two));

	std::unique_ptr<Button> button_three = std::make_unique<Button>("3", 
		169, 269);
	all.push_back(std::move(button_three));

	std::unique_ptr<Button> button_minus = std::make_unique<Button>("-", 
		251, 269, 0x292428ff);
	all.push_back(std::move(button_minus));

	std::unique_ptr<Button> button_four = std::make_unique<Button>("4", 
		5, 326);
	all.push_back(std::move(button_four));

	std::unique_ptr<Button> button_five = std::make_unique<Button>("5", 
		87, 326);
	all.push_back(std::move(button_five));

	std::unique_ptr<Button> button_six = std::make_unique<Button>("6", 
		169, 326);
	all.push_back(std::move(button_six));

	std::unique_ptr<Button> button_mply = std::make_unique<Button>("*", 
		251, 326, 0x292428ff);
	all.push_back(std::move(button_mply));

	std::unique_ptr<Button> button_sev = std::make_unique<Button>("7", 
		5, 383);
	all.push_back(std::move(button_sev));

	std::unique_ptr<Button> button_eight = std::make_unique<Button>("8", 
		87, 383);
	all.push_back(std::move(button_eight));

	std::unique_ptr<Button> button_nine = std::make_unique<Button>("9", 
		169, 383);
	all.push_back(std::move(button_nine));

	std::unique_ptr<Button> button_div = std::make_unique<Button>("/", 
		251, 383, 0x292428ff);
	all.push_back(std::move(button_div));

	std::unique_ptr<Button> button_dot = std::make_unique<Button>(".", 
		5, 440, 0x292428ff);
	all.push_back(std::move(button_dot));

	std::unique_ptr<Button> button_zero = std::make_unique<Button>("0", 
		87, 440);
	all.push_back(std::move(button_zero));

	std::unique_ptr<Button> button_eq = std::make_unique<Button>("=", 
		169, 440, 0x2F2D30ff, 162);
	all.push_back(std::move(button_eq));
}

void Tcalculator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mDisplay, states);
	for (auto& i : all) {
		target.draw(*i);
	}
}

void Tcalculator::update(const sf::Event& event) {
	if (ask) {
		listofButtons = mDisplay.askforButtons();
		ask = false;
	}
	for (auto& i : all) {
		i->update(window, listofButtons);
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.key.code == sf::Mouse::Left) {
		for (auto& i : all) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
			if (i->rec.getGlobalBounds().contains(
				sf::Vector2f(mouse_pos.x, mouse_pos.y)
			)) {
				string receivedValue = i->selected();
				mDisplay.addValue(receivedValue);
				if (receivedValue != "") ask = true;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		for (auto& i : all) {
			i->deselected();
		}
	}
}