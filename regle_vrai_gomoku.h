#pragma once
#include "ecran.h"
#include <string>

class regle_vrai_gomoku : public ecran
{
private:
	// regles du vrai gomoku
	std::string regles = "Le gomoku se joue sur un plateau quadrill� \n		de 19 lignes horizontales et 19 lignes verticales. \n\nChaque joueur poss�de 60 pions � placer, \n		qu'ils posent un � un et � tour de r�le sur les intersections. \n\nLe joueur qui a les pions noirs joue le premier en pla�ant son premier pion \n		sur l'intersection centrale du damier. \n\nLe joueur poss�dant les pions blancs doit alors poser son pion sur l'une \n		des 8 intersections autour du pion noir. \n\nLe joueur noir fait la m�me chose, et ainsi de suite, \n		le but du jeu �tant de prendre l'adversaire de vitesse et de r�ussir \n		le premier � aligner 5 pions de sa couleur, \n		dans les trois directions possibles : vertical, horizontal ou diagonal.";

public:
	//constructeur
	regle_vrai_gomoku();

	// affichage des regles 
	void affichage_vrai_gomoku();
};

