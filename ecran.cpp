#include "ecran.h"

// initialisation des variables globales
int ecran::taille_largeur = sf::VideoMode::getDesktopMode().width;
int ecran::taille_hauteur = sf::VideoMode::getDesktopMode().height;
char ecran::mode = 'c';
int ecran::nb_joueur = 1;
int ecran::side = 19;
bool ecran::taille_static = true;
