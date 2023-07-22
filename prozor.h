#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class Prozor {
public:
	Prozor(); 
	Prozor(const std::string&, const sf::Vector2u&);
	
	void ocisti();
	void crtaj(sf::Drawable&);
	void prikazi();
	void update();
	~Prozor();
	bool jelGotov() {
		return gotov;
	}
	bool jelCijeli() {
		return cijeliZaslon;
	}
	sf::Vector2u dohvatiVelicinu() {
		return velicina;
	}
	float waitEvent();
	void Unisti();
	bool gotov;
private:
	void Stvori();
	void Postavi(const std::string&, const sf::Vector2u&);
	sf::RenderWindow prozor;
	sf::Vector2u velicina;
	std::string naslov;

	bool cijeliZaslon;
};

void Prozor::update() {
	sf::Event event;
	while (prozor.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gotov = true;
		
	}
}



Prozor::Prozor(const std::string& n,
	const sf::Vector2u& v) {
	Postavi(n, v);
}

Prozor::Prozor() {
	Postavi("Pacman", sf::Vector2u(800,600));
}

Prozor::~Prozor() {
	Unisti();
}

void Prozor::Postavi(const std::string& n,
	const sf::Vector2u& v) {
	naslov = n;
	velicina = v;
	cijeliZaslon = false;
	gotov = false;
	
	Stvori();
}

void Prozor::Stvori() {
	auto stil = (cijeliZaslon ? sf::Style::Fullscreen
		: sf::Style::Default);
	prozor.create(sf::VideoMode(velicina.x,
		velicina.y, 32), naslov, stil);

}

void Prozor::Unisti() {
	prozor.close();
}

void Prozor::ocisti() {
	prozor.clear(sf::Color(0,0,0,0));
}

void Prozor::crtaj(sf::Drawable& d) {
	prozor.draw(d);
}

void Prozor::prikazi() {
	prozor.display();
}

float Prozor::waitEvent() {

	sf::Event event;
	bool gotovo = false;

	while (prozor.waitEvent(event) && gotovo!=true) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			return 5;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			return 15;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			return 20;
			
		}

		if (event.type == sf::Event::Closed) {
			return -1;

		}
	}

}