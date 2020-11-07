#pragma once
#include "ecran.h"

class regle_gomoku_libre : public ecran
{
private:
	// regle du gomoku classique
	std::string regles = "Cette version du gomoku se joue sur un plateau de la taille d�sir�. \n\nLe joueur qui a les pions noirs joue le premier en pla�ant son premier pion \n		sur l'intersection centrale du damier. \n\nLe joueur poss�dant les pions blancs peut ensuite poser son pion \n		o� il le souhaite sur le damier. \n\nLe joueur noir fait la m�me chose, et ainsi de suite, \n		le but du jeu �tant de prendre l'adversaire de vitesse et de r�ussir \n		le premier � aligner 5 pions de sa couleur, \n		dans les trois directions possibles : vertical, horizontal ou diagonal. \n\nIl n'y a pas de limite de pions, la seule limite est la taille du terrain\n		si vous souahitez la bloquer.";

public:
	// constructeur
	regle_gomoku_libre();

	// affichage des regles
	void affichage_gomoku_libre();
};

