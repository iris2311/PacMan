
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "prozor.h"
#include "pacman.h"

using namespace std;

int main() {

    while (1) {

        Pacman pacman;
        pacman.izbornik();
        if (pacman.brzina < 0)
            break;

        else
        {
   
            pacman.nacrtajIgruPrviPut();

            while (!pacman.dohvatiProzor()->jelGotov()) {

                pacman.vrijemeIteracije = 1.0f / pacman.brzina;
                if (pacman.vrijeme.asSeconds() >= pacman.vrijemeIteracije) {

                    if (!pacman.pauza) {
                        pacman.Ulaz();
                        pacman.obradiUlaz();

                        pacman.duhovi_pomak();
                     
                        pacman.vrijeme -= sf::seconds(pacman.vrijemeIteracije);

                    }

                    else {
                        pacman.Ulaz();

                    }

                }

                pacman.restartSata();
            }

            pacman.p.Unisti();

   
        }


    }

    return 0;
}