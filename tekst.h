#pragma once
#include<iostream> 
#include<SFML/Graphics.hpp> 
#include<string>

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <deque>
#include "Prozor.h"

class Textbox {
public:
	Textbox();
	Textbox(int, int, float, sf::Vector2f);
	~Textbox();
	void Postavi(int, int, float, sf::Vector2f);
	void Dodaj(std::string);
	void Ocisti();
	void Renderiraj(Prozor*);
private:
	int brLinija;
	std::deque<std::string> poruke;
	sf::RectangleShape pozadina;
	sf::Font font;
	sf::Text tekst;
};

Textbox::Textbox() {
	Postavi(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int brL, int velZn,
	float sirinaPro, sf::Vector2f pozPro) {
	Postavi(brL, velZn, sirinaPro, pozPro);
}

Textbox::~Textbox() {
	Ocisti();
}

void Textbox::Postavi(int brL, int velZn,
	float sirinaPro, sf::Vector2f pozPro) {
	brLinija = brL;
	font.loadFromFile("calibri.ttf");

	tekst.setFont(font);
	tekst.setString(""); 
	tekst.setCharacterSize(velZn);
	tekst.setFillColor(sf::Color::White);
	tekst.setPosition(pozPro + sf::Vector2f(2.0f, 2.0f));

	pozadina.setSize(sf::Vector2f(
		sirinaPro, (brL * (velZn * 1.2f))));
	pozadina.setFillColor(sf::Color::Black);
	pozadina.setPosition(pozPro);
}

void Textbox::Ocisti() {
	poruke.clear();
}

void Textbox::Dodaj(std::string nova) {
	poruke.push_back(nova);
	if (poruke.size() >= 6)
		poruke.pop_front();
}

void Textbox::Renderiraj(Prozor* p) {
	std::string sadrzaj;
	for (auto& it : poruke) {
		sadrzaj.append(it + "\n");
	}
	if (sadrzaj != "") {
		tekst.setString(sadrzaj);
		p->crtaj(pozadina);
		p->crtaj(tekst);
	}
}


