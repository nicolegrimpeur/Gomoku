#pragma once
#include "ecran.h"
#include <string>

class regle_vrai_gomoku : public ecran
{
private:
	// regles du vrai gomoku
	std::string regles = "Le gomoku se joue sur un plateau quadrillé \n		de 19 lignes horizontales et 19 lignes verticales. \n\nChaque joueur possède 60 pions à placer, \n		qu'ils posent un à un et à tour de rôle sur les intersections. \n\nLe joueur qui a les pions noirs joue le premier en plaçant son premier pion \n		sur l'intersection centrale du damier. \n\nLe joueur possédant les pions blancs doit alors poser son pion sur l'une \n		des 8 intersections autour du pion noir. \n\nLe joueur noir fait la même chose, et ainsi de suite, \n		le but du jeu étant de prendre l'adversaire de vitesse et de réussir \n		le premier à aligner 5 pions de sa couleur, \n		dans les trois directions possibles : vertical, horizontal ou diagonal.";

public:
	//constructeur
	regle_vrai_gomoku();

	// affichage des regles 
	void affichage_vrai_gomoku();
};

