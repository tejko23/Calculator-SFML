#include "Tapplication.hpp"

Tapplication::Tapplication() : window(
	sf::VideoMode(336, 500), "SFML Calculator"), calc(&window) {
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
}

void Tapplication::run() {
	sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            calc.update(event);
        }

        window.clear(sf::Color(0x12020cff));

        window.draw(calc);

        window.display();
    }
}