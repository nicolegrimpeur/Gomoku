#pragma once
#include <SFML/Window.hpp>

class ecran
{
protected:
	static int taille_largeur; // taille de la largeur de l'ecran 
	static int taille_hauteur; // taille de la hauteur de l'ecran
	static char mode; // c pour classique ou l pour libre
	static int nb_joueur; // nombre de joueur 
	static int side; // taille du tableau
	static bool taille_static; // permet de dire si le tableau est modifiable ou non
};

