#pragma once
#include <SFML/Audio.hpp>
#include "prozor.h"
#include "mapa.h"
#include<string>
#include <random>
#include <fstream>
#include <ctime>
#include<time.h>
#include "tekst.h"

enum class smjer { nema, gore, dolje, lijevo, desno };

using namespace std;

class Pacman {

public:
	Pacman();

	friend class Prozor;
	Prozor p;
	

	Prozor* dohvatiProzor() {
		return &p;
	}

	void highscore();
	
	void nacrtajIgru();
	void nacrtajIgruPrviPut();
	void Duhovi_Pocetak();
	void NoviTekst();
	void TekstZivoti();
	void duhovi_pomak();
	void duhovi_pomak_blinky();
	void duhovi_pomak_pinky();
	void duhovi_pomak_inky();
	void duhovi_pomak_clyde();
	void restartSata();
	void izbornik();

	smjer Ulaz();
	void obradiUlaz();
	void score_update(int, int);
	int zivot = 3;
	float vrijemeIteracije=0;
	int koji_duh=0;
	void GameOver();
	bool pauza = false;
	sf::Texture texture;
	void ucitaj_texture();
	sf::Clock sat;
	sf::Clock sat_voce;
	sf::Time vrijeme;
	float brzina = 200;
	sf::Music music;
	bool pacman_tunel = false;
	bool inky_tunel = false;
	bool clyde_tunel = false;
	bool pinky_tunel = false;
	bool blinky_tunel = false;
	bool voce = false;
	int voce_x, voce_y;

private:
	
	sf::Sprite inky, clyde, pinky, pacman, blinky, fruit;
	sf::Texture inky_t, clyde_t, pinky_t, pacman_t, blinky_t, fruit_t;
	mapa put;
	int score=0;
	int h_score = 0;
	int uk_voce = 0;
	bool valjan_pomak(smjer);
	void nacrtajZid(int, int);
	void nacrtajHranu(int, int);
	void nacrtajDuhove(int, int, int);
	void nacrtaj_voce();
	bool sudar_blinky();
	bool sudar_clyde();
	bool sudar_pinky();
	bool sudar_inky();

	smjer duh_sljedeci();
    sf::RectangleShape s;
	sf::CircleShape hrana;
	Textbox t;
	Textbox zivoti;
	int pacman_x = 19;
	int pacman_y = 1;
	int blinky_x = 8, pinky_x=8, clyde_x=8, inky_x=8;
	int blinky_y = 10, pinky_y = 12, clyde_y = 13, inky_y = 11;
	
};


void Pacman::izbornik() {

	Prozor izbornik("MENU", sf::Vector2u(400, 400));
	Textbox izbornik_tekst;
	izbornik_tekst.Postavi(4, 25, 400, sf::Vector2f(100, 100));
	izbornik_tekst.Dodaj("PACMAN");
	izbornik_tekst.Dodaj("Select level:");
	izbornik_tekst.Dodaj("1.EASY");
	izbornik_tekst.Dodaj("2.MEDIUM");
	izbornik_tekst.Dodaj("3.HARD");
	izbornik_tekst.Renderiraj(&izbornik);
	izbornik.prikazi();

	brzina = izbornik.waitEvent();

	izbornik.gotov = true;
	izbornik.Unisti();
	music.openFromFile("pacman.wav");
	music.setLoop(true);
	music.play();
}



void Pacman::ucitaj_texture() {

	texture.loadFromFile("pacman_sprite.png");
}

void Pacman::restartSata() {
	vrijeme += sat.restart();
}

void Pacman::nacrtaj_voce() {

	auto i = 8;

	while (1) {

		if (put.m[11][i] != 5 && put.m[11][i] != -1)
		{
			voce_x = 11;
			voce_y = i;
			break;
		}

		else
			++i;
	}
	
	fruit.setTexture(texture);
	fruit.setTextureRect(sf::IntRect(543, 168, 40, 40));
	fruit.setPosition(voce_y * 32.f, voce_x * 24.f);
	fruit.setScale(0.8f, 0.6f);
	p.ocisti();
	nacrtajIgru();
	p.crtaj(fruit);
	p.prikazi();
	sat_voce.restart();
}


bool Pacman::sudar_blinky() {

	if (blinky_x == pacman_x && blinky_y == pacman_y)
		return true;

	return false;
}

bool Pacman::sudar_inky() {

	if (inky_x == pacman_x && inky_y == pacman_y)
		return true;

	return false;
}


bool Pacman::sudar_pinky() {

	if (pinky_x == pacman_x && pinky_y == pacman_y)
		return true;

	return false;
}

bool Pacman::sudar_clyde() {

	if (clyde_x == pacman_x && clyde_y == pacman_y)
		return true;

	return false;
}


void Pacman::GameOver() {

	music.openFromFile("pacman_death.wav");	
	music.setLoop(false);
	music.play();

	Prozor kraj("GAME OVER", sf::Vector2u(400,400));
	p.gotov = true;
	Textbox kraj_tekst;
	kraj_tekst.Postavi(1, 30, 400, sf::Vector2f(100, 100));
	kraj_tekst.Dodaj("GAME OVER!");
	kraj_tekst.Renderiraj(&kraj);
	kraj.prikazi();


	while (!kraj.jelGotov()) {
	
		kraj.update();

	}
	kraj.Unisti();
	p.gotov = true;
}

smjer Pacman::duh_sljedeci() {

	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(0, 3);
	auto tmp = u(e);

	if (tmp == 0)
		return smjer::gore;
	if (tmp == 1)
		return smjer::dolje;
	if (tmp == 2)
		return smjer::lijevo;
	if (tmp == 3)
		return smjer::desno;

}

void Pacman::duhovi_pomak() {
	duhovi_pomak_blinky();
	duhovi_pomak_inky();
	duhovi_pomak_pinky();
	duhovi_pomak_clyde();

	if (sudar_blinky()) {
		zivot--;
		TekstZivoti();
	}

	if (sudar_inky()) {
		zivot--;
		TekstZivoti();
	}

	if (sudar_pinky()) {
		zivot--;
		TekstZivoti();
	}


	if (sudar_clyde()) {
		zivot--;
		TekstZivoti();
	}

	p.ocisti();
	nacrtajIgru();
	if (voce) {
		sf::Time tmp = sf::seconds(10.f);
		sf::Time tmp2 = sat_voce.getElapsedTime();
		if (tmp2 >= tmp)
			voce = false;

		else
		   p.crtaj(fruit);

	}

	p.prikazi();

}

void Pacman::duhovi_pomak_blinky() {

	auto s= duh_sljedeci();
	auto tmp1 = blinky_x;
	auto tmp2 = blinky_y;
	if (s == smjer::gore)
		tmp1--;
	if (s == smjer::lijevo)
		tmp2--;
	if (s == smjer::desno)
		tmp2++;
	if (s == smjer::dolje)
		tmp1++;
	auto kamo = s;
	
	while (1) {

       if (put.m[tmp1][tmp2] == 1 || tmp1 >= 20 || tmp2 >= 24 || tmp1 <= 0 || tmp2 <= 0
			|| put.m[tmp1][tmp2] == 5) {
			tmp1 = blinky_x;
			tmp2 = blinky_y;
			auto m = duh_sljedeci();
			if (m == smjer::gore)
				tmp1--;
			if (m == smjer::lijevo)
				tmp2--;
			if (m == smjer::desno)
				tmp2++;
			if (m == smjer::dolje)
				tmp1++;
			kamo = m;
			
		}
		else
			break;
	}

	put.m[blinky_x][blinky_y] = put.h[blinky_x][blinky_y];



	if (kamo == smjer::gore) {
		blinky.setPosition(blinky.getPosition().x, blinky.getPosition().y - 24);
		blinky_x--;

	}

	if (kamo == smjer::lijevo) {
		blinky.setPosition(blinky.getPosition().x-32, blinky.getPosition().y);
		blinky_y--;
	
	}

	if (kamo == smjer::desno) {
		blinky.setPosition(blinky.getPosition().x+32, blinky.getPosition().y);
		blinky_y++;

	}

	if (kamo == smjer::dolje) {
		blinky.setPosition(blinky.getPosition().x, blinky.getPosition().y + 24);
		blinky_x++;

	}

	put.m[blinky_x][blinky_y] = 5;

}

void Pacman::duhovi_pomak_inky() {

	auto s = duh_sljedeci();
	auto tmp1 = inky_x;
	auto tmp2 = inky_y;
	if (s == smjer::gore)
		tmp1--;
	if (s == smjer::lijevo)
		tmp2--;
	if (s == smjer::desno)
		tmp2++;
	if (s == smjer::dolje)
		tmp1++;
	auto kamo = s;

	while (1) {
		if (put.m[tmp1][tmp2] == 1 || tmp1 >= 20 || tmp2 >= 24 || tmp1 <= 0 
			|| tmp2 < 0 ||put.m[tmp1][tmp2]==5) {
			tmp1 = inky_x;
			tmp2 = inky_y;
			auto m = duh_sljedeci();
			if (m == smjer::gore)
				tmp1--;
			if (m == smjer::lijevo)
				tmp2--;
			if (m == smjer::desno)
				tmp2++;
			if (m == smjer::dolje)
				tmp1++;
			kamo = m;

		}
		else
			break;
	}


	put.m[inky_x][inky_y] = put.h[inky_x][inky_y];



	if (kamo == smjer::gore) {
		inky.setPosition(inky.getPosition().x, inky.getPosition().y - 24);
		inky_x--;

	}

	if (kamo == smjer::lijevo) {
		inky.setPosition(inky.getPosition().x - 32, inky.getPosition().y);
		inky_y--;

	}

	if (kamo == smjer::desno) {
		inky.setPosition(inky.getPosition().x + 32, inky.getPosition().y);
		inky_y++;

	}

	if (kamo == smjer::dolje) {
		inky.setPosition(inky.getPosition().x, inky.getPosition().y + 24);
		inky_x++;

	}

	put.m[inky_x][inky_y] = 5;

}

void Pacman::duhovi_pomak_pinky() {

	auto s = duh_sljedeci();
	auto tmp1 = pinky_x;
	auto tmp2 = pinky_y;
	if (s == smjer::gore)
		tmp1--;
	if (s == smjer::lijevo)
		tmp2--;
	if (s == smjer::desno)
		tmp2++;
	if (s == smjer::dolje)
		tmp1++;
	auto kamo = s;

	while (1) {
		if (put.m[tmp1][tmp2] == 1 || tmp1 >= 20 || tmp2 >= 24 || tmp1 <= 0 || tmp2 <= 0
			||put.m[tmp1][tmp2] == 5) {
			tmp1 = pinky_x;
			tmp2 = pinky_y;
			auto m = duh_sljedeci();
			if (m == smjer::gore)
				tmp1--;
			if (m == smjer::lijevo)
				tmp2--;
			if (m == smjer::desno)
				tmp2++;
			if (m == smjer::dolje)
				tmp1++;
			kamo = m;

		}
		else
			break;
	}


	put.m[pinky_x][pinky_y] = put.h[pinky_x][pinky_y];



	if (kamo == smjer::gore) {
		pinky.setPosition(pinky.getPosition().x, pinky.getPosition().y - 24);
		pinky_x--;

	}

	if (kamo == smjer::lijevo) {
		pinky.setPosition(pinky.getPosition().x - 32, pinky.getPosition().y);
		pinky_y--;

	}

	if (kamo == smjer::desno) {
		pinky.setPosition(pinky.getPosition().x + 32, pinky.getPosition().y);
		pinky_y++;

	}

	if (kamo == smjer::dolje) {
		pinky.setPosition(pinky.getPosition().x, pinky.getPosition().y + 24);
		pinky_x++;

	}

	put.m[pinky_x][pinky_y] = 5;

}

void Pacman::duhovi_pomak_clyde() {

	auto s = duh_sljedeci();
	auto tmp1 = clyde_x;
	auto tmp2 = clyde_y;
	if (s == smjer::gore)
		tmp1--;
	if (s == smjer::lijevo)
		tmp2--;
	if (s == smjer::desno)
		tmp2++;
	if (s == smjer::dolje)
		tmp1++;
	auto kamo = s;

	while (1) {
		if (put.m[tmp1][tmp2] == 1 || tmp1 >= 20 || tmp2 >= 24 || tmp1 <= 0 || tmp2 <= 0
			|| put.m[tmp1][tmp2] == 5) {
			tmp1 =clyde_x;
			tmp2 = clyde_y;
			auto m = duh_sljedeci();
			if (m == smjer::gore)
				tmp1--;
			if (m == smjer::lijevo)
				tmp2--;
			if (m == smjer::desno)
				tmp2++;
			if (m == smjer::dolje)
				tmp1++;
			kamo = m;

		}
		else
			break;
	}


	put.m[clyde_x][clyde_y] = put.h[clyde_x][clyde_y];



	if (kamo == smjer::gore) {
		clyde.setPosition(clyde.getPosition().x, clyde.getPosition().y - 24);
		clyde_x--;

	}

	if (kamo == smjer::lijevo) {
		clyde.setPosition(clyde.getPosition().x - 32, clyde.getPosition().y);
		clyde_y--;

	}

	if (kamo == smjer::desno) {
		clyde.setPosition(clyde.getPosition().x + 32, clyde.getPosition().y);
		clyde_y++;

	}

	if (kamo == smjer::dolje) {
		clyde.setPosition(clyde.getPosition().x, clyde.getPosition().y + 24);
		clyde_x++;

	}

	put.m[clyde_x][clyde_y] = 5;

}




void Pacman::score_update(int i, int j) {

	if (put.h[i][j] == 3)
		score += 10;

	highscore();
	if (score >= 700 && voce==false && uk_voce==0){
		nacrtaj_voce();
		voce=true;
		++uk_voce;
	}

	if (i == voce_x && j == voce_y && voce==true) {
		score += 700;
		voce_x = -10;
		voce_y = -10;
		voce=false;
	}
}


smjer Pacman::Ulaz() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return smjer::gore;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return smjer::dolje;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return smjer:: lijevo;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return smjer::desno;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) 
		pauza = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		pauza = false;



	return smjer::nema;

}

bool Pacman::valjan_pomak(smjer s) {

	bool moze = true;
	int tmp1, tmp2;
	tmp1 = pacman_x;
	tmp2 = pacman_y;
	if (s == smjer::gore)
		tmp1--;
	if (s == smjer::lijevo)
		tmp2--;
	if (s == smjer::desno)
		tmp2++;
	if (s == smjer::dolje)
		tmp1++;

	if (s == smjer::nema)
		return false;

	if (put.m[tmp1][tmp2] == 1)
		moze = false;

	if (tmp1 > 20 || tmp2 > 24 || tmp1 < 0 || tmp2 < 0) {

		if (tmp1==9) {
			if (tmp2 < 0)
				tmp2 = 24;
			if (tmp2 > 24)
				tmp2 = -24;
			pacman_tunel == true;
			pacman.setPosition(pacman.getPosition().x+tmp2*32, pacman.getPosition().y);
			put.h[pacman_x][pacman_y] = -2;
			if (tmp2 < 0)
				tmp2 = 0;
	
			put.h[pacman_x][pacman_y] = -2;
			pacman_y = tmp2;
			score_update(pacman_x, pacman_y);
			put.m[pacman_x][pacman_y] = -1;
			pacman.setTextureRect(sf::IntRect(750, 469, 40, 40));
			pacman.setScale(0.8f, 0.6f);
		}


		else
			moze = false;

	}
	
	return moze;
}

void Pacman::obradiUlaz() {

	auto s = Pacman::Ulaz();
	if (valjan_pomak(s) == 1 && !pacman_tunel) {
		if (s == smjer::gore) {
			pacman.setPosition(pacman.getPosition().x, pacman.getPosition().y-24);
			score_update(pacman_x-1, pacman_y);
			put.h[pacman_x][pacman_y] = -2;
			pacman_x--;
			put.m[pacman_x][pacman_y] = -1;
			pacman.setTextureRect(sf::IntRect(750, 469, 40, 40));
			pacman.setScale(0.8f, 0.6f);
		
		}

		if (s == smjer::lijevo) {
			pacman.setPosition(pacman.getPosition().x-32, pacman.getPosition().y );
			score_update(pacman_x, pacman_y-1);
			put.h[pacman_x][pacman_y] = -2;
			pacman_y--;
			put.m[pacman_x][pacman_y] = -1;
			pacman.setTextureRect(sf::IntRect(750, 340, 40, 40));
			pacman.setScale(0.8f, 0.6f);

		
		}

		if (s == smjer::desno) {
			pacman.setPosition(pacman.getPosition().x+32, pacman.getPosition().y );
			score_update(pacman_x, pacman_y+1);
			put.h[pacman_x][pacman_y] = -2;
			pacman_y++;
			put.m[pacman_x][pacman_y] = -1;
			pacman.setTextureRect(sf::IntRect(750, 123, 40, 40));
			pacman.setScale(0.8f, 0.6f);
		
		}

		if (s == smjer::dolje) {
			pacman.setPosition(pacman.getPosition().x, pacman.getPosition().y +24);
			score_update(pacman_x+1, pacman_y);
			put.h[pacman_x][pacman_y] = -2;
			pacman_x++;
			put.m[pacman_x][pacman_y] = -1;
			pacman.setTextureRect(sf::IntRect(750, 205, 40, 40));
			pacman.setScale(0.8f, 0.6f);

			
		}

	}


	p.ocisti();
	nacrtajIgru();
	p.prikazi();
	if (pacman_tunel)
		pacman_tunel = false;
}

Pacman::Pacman() {

	ucitaj_texture();
	

}

void Pacman::NoviTekst() {


	t.Postavi(2, 25, 400, sf::Vector2f(0, 510));
	t.Dodaj("HIGHSCORE: 0 ");
	t.Dodaj("SCORE: 0");
	t.Renderiraj(&p);
	

}

void Pacman::TekstZivoti() {

	zivoti.Postavi(1, 25, 400, sf::Vector2f(400, 510));
	std::string broj = std::to_string(zivot);
	if (zivot <= 0) {
		zivoti.Ocisti();
		zivoti.Dodaj("Lives left: " + '0');
		zivoti.Renderiraj(&p);
		unsigned sleep(1);
		GameOver();
	}

	zivoti.Ocisti();
	zivoti.Dodaj("Lives left: " + broj);
	zivoti.Renderiraj(&p);

}

void Pacman::Duhovi_Pocetak() {

	for (auto i = 0; i < 21; ++i) {
		for (auto j = 0; j < 25; ++j) {
			if (put.m[i][j] == 5) {
				nacrtajDuhove(i, j, koji_duh);
				++koji_duh;     // 0=blinky, 1=clyde, 2=inky, 3=pinky
			}

		}

	}
}


void Pacman::nacrtajDuhove(int i, int j, int d) {

	if (d == 0) {
		blinky.setTexture(texture);
		blinky.setTextureRect(sf::IntRect(29,40, 40, 40));
		blinky.setPosition(sf::Vector2f( blinky_y* 32.f, blinky_x * 24.f));
		blinky.setScale(0.8f, 0.6f);
		p.crtaj(blinky);
	}

	if (d == 1) {
		clyde.setTexture(texture);
		clyde.setTextureRect(sf::IntRect(160,40, 40, 40));
		clyde.setScale(0.8f, 0.6f);
		clyde.setPosition(sf::Vector2f(clyde_y * 32.f, clyde_x * 24.f));
		p.crtaj(clyde);
	}

	if (d == 2) {
		inky.setTexture(texture);
		inky.setTextureRect(sf::IntRect(115,40, 40, 40));
		inky.setScale(0.8f, 0.6f);
		inky.setPosition(sf::Vector2f(inky_y * 32.f, inky_x * 24.f));
		p.crtaj(inky);
	}

	if (d == 3) {
		pinky.setTexture(texture);
		pinky.setTextureRect(sf::IntRect(72,40, 40, 40));
		pinky.setScale(0.8f, 0.6f);
		pinky.setPosition(sf::Vector2f(pinky_y* 32.f, pinky_x * 24.f));
		p.crtaj(pinky);
	}
	

}




void Pacman::nacrtajIgruPrviPut() {

	for (auto i = 0; i < 21; ++i) {
		for (auto j = 0; j < 25; ++j) {
			if(put.m[i][j]==1)
				nacrtajZid(i, j);
	
			if (put.m[i][j] == 3)
				nacrtajHranu(i, j);
			
		}

	}

	NoviTekst();
	TekstZivoti();
	Duhovi_Pocetak();
	pacman.setTexture(texture);
	pacman.setTextureRect(sf::IntRect(750, 82, 40, 40));
	pacman.setPosition(sf::Vector2f(1 * 32.f, 19* 24.f));
	pacman.setScale(0.8f, 0.6f);
	p.crtaj(pacman);
	
	p.prikazi();
	
	
}

void Pacman::nacrtajIgru() {

	for (auto i = 0; i < 21; ++i) {
		for (auto j = 0; j < 25; ++j) {
			if (put.m[i][j] == 1)
				nacrtajZid(i, j);

			if (put.m[i][j] == 3)
				nacrtajHranu(i, j);
		}

	}

	p.crtaj(pacman);
	p.crtaj(blinky);
	p.crtaj(inky);
	p.crtaj(clyde);
	p.crtaj(pinky);
	t.Renderiraj(&p);
	zivoti.Renderiraj(&p);
}

void Pacman::nacrtajZid(int i, int j) {

	s.setSize(sf::Vector2f(32, 24));
	s.setFillColor(sf::Color::Blue);
	s.setOutlineColor(sf::Color::White);
	s.setOutlineThickness(0.5);
	s.setPosition(sf::Vector2f(j*32.f, i*24.f));
	p.crtaj(s);

}


void Pacman::nacrtajHranu(int i, int j) {

	hrana.setRadius(3);
	hrana.setFillColor(sf::Color::White);
	hrana.setPosition(sf::Vector2f((j + 0.5) * 32.f, (i + 0.5) * 24.f));
	p.crtaj(hrana);

}

void Pacman::highscore() {

	
	std::ifstream file;
	file.open("data.txt");
	int naj;
	file >> naj;
	h_score = naj;

	file.close();
	t.Ocisti();

	if (score > naj)
	{
		//ispis poruke
		std::ofstream file;
		file.open("data.txt");
		file << score;
		file.close();
		std::string br = std::to_string(score);
		t.Dodaj("HIGHSCORE: " + br);
		t.Dodaj("SCORE: " + br);
		h_score = score;
	}

	else
	{
		t.Dodaj("HIGHSCORE: " + std::to_string(h_score));
		t.Dodaj("SCORE: " + std::to_string(score));
		
	}

	t.Renderiraj(&p);


}