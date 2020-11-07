#include "play.h"
#include "menu.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

// utile pour utiliser la fonction rand
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// constructeur
play::play(int nbtour)
{
	// stocke la taille pour une remise a 0
	local_side = side;

	// initialise le tour a 0
	setNbtour(nbtour);

	// initialise le tableau de pions
	initPiontab(-1);

	// lance le jeu
	print();
}

// permet d'initialiser la variable qui gere le nombre de tour effectue 
void play::setNbtour(int _nbtour)
{
	nbtour = _nbtour;
}

// affichage du jeu 
void play::print()
{
	//  variables
	float taille_pion;
	float taille_a_gauche = (((float)taille_largeur / 2) - (((float)taille_hauteur - 120) / 2));
	int x_side = 0;
	int y_side = 0;
	int fin = 0; // 0 en jeu, 1 gagnant, 2 egalite
	bool je_peux_poser_un_pion = false;

	if (mode == 'c')
	{
		side = 19;
	}
	else
	{
		side = local_side;
	}
	float taille_case = (((float)taille_hauteur - 120) / (side - 1));
	if (side <= 30)
	{
		taille_pion = 33 - (float)side;
	}
	else
	{
		taille_pion = 4;
	}

	//permet d'ajouter l'anti-aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	// creation de la fenetre en plein ecran
	sf::RenderWindow window(sf::VideoMode(taille_largeur, taille_hauteur), "Le jeu du Gomoku", sf::Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30); // bloque le jeu à 30 FPS pour améliorer les performances
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen())
	{
		// effacement de la fenêtre en noir
		window.clear(sf::Color::Black);

		// creation de la texture et de la police
		sf::Texture texture;
		if (!texture.loadFromFile("texture/texture_fond.jpg"))
		{
			std::cout << "erreur dans le chargement de la texture\n" << std::endl;
		}
		sf::Sprite fond;
		fond.setTexture(texture);
		fond.setTextureRect(sf::IntRect(10, 10, taille_largeur, taille_hauteur));
		window.draw(fond);

		sf::Font police_arial;
		if (!police_arial.loadFromFile("polices/arial.ttf"))
		{
			std::cout << "erreur dans le chargement des polices" << std::endl;
		}

		// création d'un bouton quitter en haut à droite
		sf::Text quitter;
		quitter.setFont(police_arial);
		quitter.setString("Quitter");
		quitter.setCharacterSize(19);
		quitter.setFillColor(sf::Color::Black);
		quitter.setPosition((float)(taille_largeur - 66), 0.f);
		window.draw(quitter);

		// creation d'un bouton menu
		sf::Text _menu;
		_menu.setFont(police_arial);
		_menu.setString("Menu");
		_menu.setCharacterSize(19);
		_menu.setFillColor(sf::Color::Black);
		_menu.setPosition(5, 0.f);
		window.draw(_menu);

		// si le jeu est fini
		if (fin == 1 || fin == 2)
		{
			// affichage d'un bouton recommencer
			sf::Text recommencer;
			recommencer.setFont(police_arial);
			recommencer.setString("Recommencer");
			recommencer.setCharacterSize(19);
			recommencer.setFillColor(sf::Color::Black);
			recommencer.setPosition((float)taille_largeur / 2 - 65, 0.f);
			window.draw(recommencer);
		} 
		else
		{
			// affichage d'un bouton abandonner
			sf::Text abandonner;
			abandonner.setFont(police_arial);
			abandonner.setString("Abandonner");
			abandonner.setCharacterSize(19);
			abandonner.setFillColor(sf::Color::Black);
			abandonner.setPosition((float)taille_largeur / 2 - 65, 0.f);
			window.draw(abandonner);
		}

		// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed)
				window.close();

			// si un clic est effectue 
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// si l'on clique sur le bouton quitter, on sort
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// test si le clic est dans le tableau 
					if (fin != 1 && !(event.mouseButton.x >= (float)taille_largeur / 2 - 68 && event.mouseButton.x <= (float)taille_largeur / 2 + 68 && event.mouseButton.y <= 20))
					{
						// convertit les valeurs du curseur en entier entre 0 et le nombre de case
						x_side = ((int)(((float)event.mouseButton.x + taille_case / 2 - taille_a_gauche) / taille_case));
						y_side = (int)(((float)event.mouseButton.y - 60 + taille_case / 2) / taille_case);
						
						// test que la case sélectionné est dans le tableau
						if (x_side < side - 0 && y_side < side - 0 && x_side >= 0 && y_side >= 0)  
						{
							// si le mode est classique on teste qu'il y a bien un pion deja autour
							if (mode == 'c')
							{
								je_peux_poser_un_pion = false;
								// test que la case sélectionné est dans le tableau moins les bords
								if (x_side < side - 1 && y_side < side - 1 && x_side >= 1 && y_side >= 1)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1 || pionstab[x_side - 1][y_side - 1] != -1 || pionstab[x_side - 1][y_side + 1] != -1 || pionstab[x_side + 1][y_side] != -1 || pionstab[x_side + 1][y_side - 1] != -1 || pionstab[x_side + 1][y_side + 1] != -1 || pionstab[x_side][y_side + 1] != -1 || pionstab[x_side][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est en haut à gauche
								else if (x_side == 0 && y_side == 0)
								{
									// on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side + 1][y_side] != -1 || pionstab[x_side][y_side + 1] != -1 || pionstab[x_side + 1][y_side + 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est en bas à gauche
								else if (x_side == 0 && y_side == side - 1)
								{
									// on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side + 1][y_side] != -1 || pionstab[x_side][y_side - 1] != -1 || pionstab[x_side + 1][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est en haut à droite
								else if (x_side == side - 1 && y_side == 0)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1 || pionstab[x_side - 1][y_side + 1] != -1 || pionstab[x_side][y_side + 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est en bas à droite
								else if (x_side == side - 1 && y_side == side - 1)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1 || pionstab[x_side - 1][y_side - 1] != -1 || pionstab[x_side][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est sur le bord gauche
								else if (x_side == 0 && y_side < side && y_side >= 0)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side + 1][y_side] != -1 || pionstab[x_side + 1][y_side - 1] != -1 || pionstab[x_side + 1][y_side + 1] != -1 || pionstab[x_side][y_side + 1] != -1 || pionstab[x_side][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est sur le bord droit
								else if (x_side == side - 1 && y_side < side && y_side >= 0)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1 || pionstab[x_side - 1][y_side - 1] != -1 || pionstab[x_side - 1][y_side + 1] != -1 || pionstab[x_side][y_side + 1] != -1 || pionstab[x_side][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est sur le bord haut
								else if (y_side == 0 && x_side < side && x_side >= 0)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1  || pionstab[x_side - 1][y_side + 1] != -1 || pionstab[x_side + 1][y_side] != -1||pionstab[x_side + 1][y_side + 1] != -1 || pionstab[x_side][y_side + 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}

								// test que la case sélectionné est sur le bord bas
								else if (y_side == side - 1 && x_side < side && x_side >= 0)
								{
									// si le mode est classique on teste qu'il y a bien un pion deja autour
									if (pionstab[x_side - 1][y_side] != -1 || pionstab[x_side - 1][y_side - 1] != -1 || pionstab[x_side + 1][y_side] != -1 || pionstab[x_side + 1][y_side - 1] != -1 || pionstab[x_side][y_side - 1] != -1) {
										je_peux_poser_un_pion = true;
									}
								}
								
							}
							else
							{
								// si le mode est libre, alors on peut jouer ou on veut
								je_peux_poser_un_pion = true;
							}

							// modifie le tableua de pions uniquement si l'on peut poser un pion
							if (je_peux_poser_un_pion == true)
							{
								// on test si la case clique est vide
								if (pionstab[x_side][y_side] == -1)
								{
									if (nbtour % 2 == 0) // au noir de jouer 
									{
										pionstab[x_side][y_side] = 1;
										nbtour += 1;
									}
									else if (nbtour % 2 == 1) // au blanc de jouer
									{
										pionstab[x_side][y_side] = 0;
										nbtour += 1;
									}

									// appel de la fonction qui verifie si le pion pose est gagnant
									fin = maybewin(x_side, y_side);

									// permet d'augmenter la taille du plateau
									if (mode != 'c' && side + 2 <= 75)
									{
										// test que la case sélectionné est sur un bord
										if ((x_side == 0 && y_side < side && y_side >= 0 && taille_static == false) || (x_side == side - 1 && y_side < side && y_side >= 0 && taille_static == false) || (y_side == 0 && x_side < side && x_side >= 0 && taille_static == false) || (y_side == side - 1 && x_side < side && x_side >= 0 && taille_static == false))
										{
											// rajoute une ligne sans pion en haut
											pionstab.insert(pionstab.begin(), std::vector<int>(side + 2, -1));

											// rajoute une ligne sans pion a gauche
											for (int i = 1; i <= side; i++)
											{
												pionstab[i].insert(pionstab[i].begin(), -1);
											}

											// rajoute une ligne sans pion a droite
											for (int i = 1; i <= side; i++)
											{
												pionstab[i].push_back(-1);
											}

											// rajoute une ligne sans pion en bas
											pionstab.push_back(std::vector<int>(side + 2, -1));

											// aumgente la taille du tableau
											side += 2;

											// decale les positions 
											++x_side;
											++y_side;
										}
									}
									
									// s'il n'y a qu'un seul joueur on lance la fonction du bot
									if (fin != 1 && nb_joueur == 1)
									{
										bot(x_side, y_side);
									}

									// actualise la taille d'un pion et la taille d'une case
									taille_case = (((float)taille_hauteur - 120) / (side - 1));
									if (side <= 30)
									{
										taille_pion = 33 - (float)side;
									}
									else
									{
										taille_pion = 4;
									}
								}
							}
						}
					}


					if (event.mouseButton.x >= taille_largeur - 66 && event.mouseButton.y <= 20)  // si le clic est sur le texte quitter
					{
						window.close();
					}

					if (event.mouseButton.x <= 53 && event.mouseButton.y <= 20)  // si le clic est sur le texte menu
					{
						window.close();
						menu affichage;
					}

					// si le clic est sur le texte recommencer
					if (event.mouseButton.x >= (float)taille_largeur / 2 - 68 && event.mouseButton.x <= (float)taille_largeur / 2 + 68 && event.mouseButton.y <= 20)  
					{
						// le jour qui a clique sur abandonner est perdant
						if (fin != 1)
						{
							fin = 1;
						}
						// redemarrage du jeu
						else
						{
							// remise a la valeur initial 
							side = local_side;

							// remise a 0 du tableau contenant les poins
							resetPiontab();
							fin = 0;
							nbtour = 1;

							// actualise la taille d'une case et d'un pion
							taille_case = (((float)taille_hauteur - 120) / (side - 1));
							if (side <= 30)
							{
								taille_pion = 33 - (float)side;
							}
							else
							{
								taille_pion = 4;
							}
						}
					}
				}
			}

			// si la souris est deplace
			if (event.type == sf::Event::MouseMoved && fin != 1)
			{
				// convertit les valeurs du curseur en entier entre 0 et le nombre de case
				x_side = ((int)(((float)event.mouseMove.x + taille_case / 2 - taille_a_gauche) / taille_case));
				y_side = (int)(((float)event.mouseMove.y - 60 + taille_case / 2) / taille_case);

				// test que le curseur est dans le tableau
				if (x_side < side && y_side < side && x_side >= 0 && y_side >= 0)
				{
					//permet de creer un cercle vide autour du pion sur lequel est positionne la souris
					sf::CircleShape circle(taille_pion);
					circle.setPosition((float)x_side * taille_case + taille_a_gauche - (float)taille_pion, (float)y_side * taille_case + 60 - (float)taille_pion);
					circle.setFillColor(sf::Color::Transparent);
					circle.setOutlineThickness(2);
					circle.setOutlineColor(sf::Color::Black);
					window.draw(circle);
				}
			}
		}

		
		// permet de creer le tableau
		for (float i = 60; i <= taille_hauteur - 60 + 1; i += taille_case) // ligne horizontal
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((float)taille_a_gauche, (float)i)),
				sf::Vertex(sf::Vector2f((float)(((float)taille_largeur / 2) + (((float)taille_hauteur - 120) / 2)), (float)i))
			};

			line[0].color = sf::Color::Black; // on colorie les lignes en noir (en modifiant la couleur des deux bouts)
			line[1].color = sf::Color::Black;

			window.draw(line, 2, sf::Lines);
		}

		// ligne vertical
		for (float i = ((float)taille_largeur / 2) - (((float)taille_hauteur - 120) / 2); i <= ((float)taille_largeur / 2) + (((float)taille_hauteur - 120) / 2) + 1; i += taille_case) 
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((float)i, 60.f)),
				sf::Vertex(sf::Vector2f((float)i, (float(taille_hauteur - 60))))
			};

			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;

			window.draw(line, 2, sf::Lines);
		}

		// affichage des pions
		// parcours du tableau
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				// s'il y a un pion sur la case
				if (pionstab[j][i] == 0 || pionstab[j][i] == 1)
				{
					// on dessine le pion 
					sf::CircleShape circle(taille_pion);
					circle.setPosition(j * taille_case + taille_a_gauche - (float)taille_pion, i * taille_case + 60 - (float)taille_pion);
					// blanc si le pion est blanc
					if (pionstab[j][i] == 0)
					{
						circle.setFillColor(sf::Color::White);
						circle.setOutlineThickness(1);
						circle.setOutlineColor(sf::Color::Black);
					}
					// noir si le pion est noir
					else if (pionstab[j][i] == 1)
					{
						circle.setFillColor(sf::Color::Black);
						circle.setOutlineThickness(1);
						circle.setOutlineColor(sf::Color::White);
					}
					window.draw(circle);
				}
			}
		}

		// s'il y a un gagnant
		if (fin == 1)
		{
			// creation du rectangle sur lequel sera inscrit le gagnant
			sf::RectangleShape rectanglefin(sf::Vector2f(400, 76));
			rectanglefin.setPosition(((float)taille_largeur / 2) - 200, ((float)taille_hauteur) / 2 - 76 / 2);

			// creation du texte 
			sf::Text textfin;
			textfin.setFont(police_arial); 
			textfin.setCharacterSize(24); 
			textfin.setPosition(((float)taille_largeur / 2) - 110, ((float)taille_hauteur) / 2 - 24);

			// si le blanc a gagne 
			if (nbtour % 2 == 0)
			{
				rectanglefin.setFillColor(sf::Color::White);
				rectanglefin.setOutlineThickness(2);
				rectanglefin.setOutlineColor(sf::Color::Black);

				textfin.setString("Les blancs ont gagné"); 
				textfin.setFillColor(sf::Color::Black);
			}
			// si le noir a gagne
			else
			{
				rectanglefin.setFillColor(sf::Color::Black);
				rectanglefin.setOutlineThickness(2);
				rectanglefin.setOutlineColor(sf::Color::White);

				textfin.setString("Les noirs ont gagné");
				textfin.setFillColor(sf::Color::White);
			}
			window.draw(rectanglefin);
			window.draw(textfin);
		}
		// si l'on a attend 60 pions joues par personne en mode classique ou si tous les tableaux est remplie
		else if ((nbtour / 2 == 60 && mode == 'c') || nbtour == side * side) 
		{
			// creation du rectangle sur lequel sera inscrit qu'il y a egalite 
			sf::RectangleShape rectanglefin(sf::Vector2f(400, 76));
			rectanglefin.setPosition(((float)taille_largeur / 2) - 200, ((float)taille_hauteur) / 2 - 76 / 2);

			// creation du texte qui sera pose sur le rectangle
			sf::Text textfin;
			textfin.setFont(police_arial);
			textfin.setCharacterSize(24); 
			textfin.setPosition(((float)taille_largeur / 2) - 70, ((float)taille_hauteur) / 2 - 24);

			rectanglefin.setFillColor(sf::Color(175, 175, 175));
			rectanglefin.setOutlineThickness(2);
			rectanglefin.setOutlineColor(sf::Color::Black);

			textfin.setString("Il y a égalité !"); 
			textfin.setFillColor(sf::Color::Black);

			window.draw(rectanglefin);
			window.draw(textfin);

			// 2 pour dire qu'il y a egalite
			fin = 2;
		}


		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}
}

// fonction qui initialise le tableau contenant les pions
void play::initPiontab(int _color)
{
	for (int i = 0; i < side; i++)
	{
		pionstab.push_back(std::vector<int>(side, _color));
	}

	//rajout du pion du milieu
	pionstab[(int)((side - 1) / 2)][(int)((side - 1) / 2)] = 1;
	nbtour += 1;
}

// permet de remettre le tableau a 0
void play::resetPiontab()
{
	// supprime tout le tableau avant de le recreer
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			pionstab.erase(pionstab.begin(), pionstab.end());
		}
	}
	// reinitialise ensuite le tableau
	initPiontab(-1);
}

// fonction qui teste si nous avons un gagnant
int play::maybewin(int x, int y)
{
	int nbaligne = 0;
	int _color = pionstab[x][y];
	// test des pions autour du pions ajoute sur une distance de 4 pions
	for (int i = x - 4; i <= x + 4; i++)
	{
		// si les coordonnees sont dans le tableau 
		if (i >= 0 && i < side)
		{
			// on regarde de quel couleur est le pion
			if (pionstab[i][y] == _color)
			{
				nbaligne += 1;
			}
			else
			{
				nbaligne = 0;
			}
		}
		
		// si 5 pions sont alignes, on a un gagnant
		if (nbaligne == 5)
		{
			return 1;
		}
	}

	// remise a 0 car changement de direction
	nbaligne = 0;

	for (int i = y - 4; i <= y + 4; i++)
	{
		if (i >= 0 && i < side)
		{
			if (pionstab[x][i] == _color)
			{
				nbaligne += 1;
			}
			else
			{
				nbaligne = 0;
			}
		}

		if (nbaligne == 5)
		{
			return 1;
		}
	}

	nbaligne = 0;

	for (int i = y - 4, j = x - 4; i <= y + 4 && j <= x + 4; i++, j++)
	{
		if (i >= 0 && i < side && j >= 0 && j < side)
		{
			if (pionstab[j][i] == _color)
			{
				nbaligne += 1;
			}
			else
			{
				nbaligne = 0;
			}
		}
		if (nbaligne == 5)
		{
			return 1;
		}
	}

	nbaligne = 0;

	for (int i = y - 4, j = x + 4; i <= y + 4 && j >= x - 4; i++, j--)
	{
		if (i >= 0 && i < side && j >= 0 && j < side)
		{
			if (pionstab[j][i] == _color)
			{
				nbaligne += 1;
			}
			else
			{
				nbaligne = 0;
			}
		}
		if (nbaligne == 5)
		{
			return 1;
		}
	}

	// retourne 0 s'il n'y a pas 5 pions de la meme couleur alignes
	return 0;
}

// fonction qui permet au bot de jouer 
void play::bot(int x, int y)
{
	// creation d'un tableau des positions qui peuvent bloquer l'adversaire
	std::vector<std::vector<int>> bloque_adversaire;
	// creation d'un tableau des positions avec une case vide
	std::vector<std::vector<int>> place_dispo;

	int nbboucle = 1;

	do
	{
		// on teste les positions autour du point posé
		for (int i = x - nbboucle; i <= x + nbboucle; i += nbboucle * 2)
		{
			// on teste que la coordonnee est bien dans le tableau
			if (i >= 0 && i < side)
			{
				// on teste s'il y a un pion ennemi et que l'on est pas entouré de pions
				if (pionstab[i][y] == 0 && nbboucle == 1)
				{
					// on teste dans quel cas on est
					if (i == x - nbboucle)
					{
						// on teste si la valeur teste est dans le tableau 
						if (x + nbboucle < side)
						{
							// on verifie qu'il n'y a pas deja un pion sur la case
							if (pionstab[x + nbboucle][y] != nbboucle && pionstab[x + nbboucle][y] != 0)
							{
								// on ajoute la coordonnee obtenue au tableau pour bloquer l'adversaire
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x + nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y);
							}
						}
					}
					// deuxieme cas
					else
					{
						// on teste que la coordonnee est bien dans le tableau 
						if (x - nbboucle >= 0)
						{
							// on teste qu'il n'y a pas de pion a cette position 
							if (pionstab[x - nbboucle][y] != nbboucle && pionstab[x - nbboucle][y] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x - nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y);
							}
						}
					}
				}
				// si il n'y a pas de pion ennemi a cette position 
				else
				{
					// on verifie qu'il n'y a pas de pion sur cette position 
					if (pionstab[i][y] == -1)
					{
						// on place la position dans les positions libres
						place_dispo.push_back(std::vector<int>(2));
						place_dispo[place_dispo.size() - 1][0] = i;
						place_dispo[place_dispo.size() - 1][1] = y;
					}
				}
			}
		}

		for (int i = y - nbboucle; i <= y + nbboucle; i += nbboucle * 2)
		{
			if (i >= 0 && i < side)
			{
				if (pionstab[x][i] == 0 && nbboucle == 1)
				{
					if (i == y - nbboucle)
					{
						if (y + nbboucle < side)
						{
							if (pionstab[x][y + nbboucle] != nbboucle && pionstab[x][y + nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y + nbboucle);
							}
						}
					}
					else
					{
						if (y - nbboucle >= 0)
						{
							if (pionstab[x][y - nbboucle] != nbboucle && pionstab[x][y - nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y - nbboucle);
							}
						}
					}
				}
				else
				{
					if (pionstab[x][i] == -1)
					{
						place_dispo.push_back(std::vector<int>(2));
						place_dispo[place_dispo.size() - 1][0] = x;
						place_dispo[place_dispo.size() - 1][1] = i;
					}
				}
			}
		}

		for (int i = y - nbboucle, j = x - nbboucle; i <= y + nbboucle && j <= x + nbboucle; i += nbboucle * 2, j += nbboucle * 2)
		{
			if (i >= 0 && i < side && j >= 0 && j < side)
			{
				if (pionstab[j][i] == 0 && nbboucle == 1)
				{
					if (i == y - nbboucle && j == x - nbboucle)
					{
						if (y + nbboucle < side && x + nbboucle < side)
						{
							if (pionstab[x + nbboucle][y + nbboucle] != nbboucle && pionstab[x + nbboucle][y + nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x + nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y + nbboucle);
							}
						}
					}
					else
					{
						if (y - nbboucle >= 0 && x - nbboucle >= 0)
						{
							if (pionstab[x - nbboucle][y - nbboucle] != nbboucle && pionstab[x - nbboucle][y - nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x - nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y - nbboucle);
							}
						}
					}
				}
				else
				{
					if (pionstab[j][i] == -1)
					{
						place_dispo.push_back(std::vector<int>(2));
						place_dispo[place_dispo.size() - 1][0] = j;
						place_dispo[place_dispo.size() - 1][1] = i;
					}
				}
			}
		}

		for (int i = y - nbboucle, j = x + nbboucle; i <= y + nbboucle && j >= x - nbboucle; i += nbboucle * 2, j -= nbboucle * 2)
		{
			if (i >= 0 && i < side && j >= 0 && j < side)
			{
				if (pionstab[j][i] == 0 && nbboucle == 1)
				{
					if (i == y - nbboucle && j == x + nbboucle)
					{
						if (y + nbboucle < side && x - nbboucle >= 0)
						{
							if (pionstab[x - nbboucle][y + nbboucle] != nbboucle && pionstab[x - nbboucle][y + nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x - nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y + nbboucle);
							}
						}
					}
					else
					{
						if (y - nbboucle >= 0 && x + nbboucle < side)
						{
							if (pionstab[x + nbboucle][y - nbboucle] != nbboucle && pionstab[x + nbboucle][y - nbboucle] != 0)
							{
								bloque_adversaire.push_back(std::vector<int>(2));
								bloque_adversaire[bloque_adversaire.size() - 1][0] = (x + nbboucle);
								bloque_adversaire[bloque_adversaire.size() - 1][1] = (y - nbboucle);
							}
						}
					}
				}
				else
				{
					if (pionstab[j][i] == -1)
					{
						place_dispo.push_back(std::vector<int>(2));
						place_dispo[place_dispo.size() - 1][0] = j;
						place_dispo[place_dispo.size() - 1][1] = i;
					}
				}
			}
		}

		// initialisation de srand
		srand((int)time(NULL));

		// variable qui contiendra la position aleatoire choisi
		int choix;

		// cas ou on a une position ou on peut jouer pour bloquer l'adversaire
		if (bloque_adversaire.size() > 0)
		{

			choix = rand() % bloque_adversaire.size();
			pionstab[bloque_adversaire[choix][0]][bloque_adversaire[choix][1]] = 1;
			nbboucle = 0;

			// permet d'augmenter la taille du tableau si le bot joue sur un bord
			if (mode != 'c' && side + 2 <= 75)
			{
				// test que la case sélectionné est sur un bord
				if ((bloque_adversaire[choix][0] == 0 && bloque_adversaire[choix][1] < side && bloque_adversaire[choix][1] >= 0 && taille_static == false) || (bloque_adversaire[choix][0] == side - 1 && bloque_adversaire[choix][1] < side && bloque_adversaire[choix][1] >= 0 && taille_static == false) || (bloque_adversaire[choix][1] == 0 && bloque_adversaire[choix][0] < side && bloque_adversaire[choix][0] >= 0 && taille_static == false) || (bloque_adversaire[choix][1] == side - 1 && bloque_adversaire[choix][0] < side && bloque_adversaire[choix][0] >= 0 && taille_static == false))
				{
					// rajoute une ligne sans pion en haut
					pionstab.insert(pionstab.begin(), std::vector<int>(side + 2, -1));

					// rajoute une ligne sans pion a gauche
					for (int i = 1; i <= side; i++)
					{
						pionstab[i].insert(pionstab[i].begin(), -1);
					}

					// rajoute une ligne sans pion a droite
					for (int i = 1; i <= side; i++)
					{
						pionstab[i].push_back(-1);
					}

					// rajoute une ligne sans pion en bas
					pionstab.push_back(std::vector<int>(side + 2, -1));

					// aumgente la taille du tableau
					side += 2;
				}
			}
		}

		// cas ou on a une position ou on peut jouer autour de l'adversaire
		else if (place_dispo.size() > 0)
		{
			choix = rand() % place_dispo.size();
			pionstab[place_dispo[choix][0]][place_dispo[choix][1]] = 1;
			nbboucle = 0;

			if (mode != 'c' && side + 2 <= 75)
			{
				// test que la case sélectionné est sur un bord
				if ((place_dispo[choix][0] == 0 && place_dispo[choix][1] < side && place_dispo[choix][1] >= 0 && taille_static == false) || (place_dispo[choix][0] == side - 1 && place_dispo[choix][1] < side && place_dispo[choix][1] >= 0 && taille_static == false) || (place_dispo[choix][1] == 0 && place_dispo[choix][0] < side && place_dispo[choix][0] >= 0 && taille_static == false) || (place_dispo[choix][1] == side - 1 && place_dispo[choix][0] < side && place_dispo[choix][0] >= 0 && taille_static == false))
				{
					// rajoute une ligne sans pion en haut
					pionstab.insert(pionstab.begin(), std::vector<int>(side + 2, -1));

					// rajoute une ligne sans pion a gauche
					for (int i = 1; i <= side; i++)
					{
						pionstab[i].insert(pionstab[i].begin(), -1);
					}

					// rajoute une ligne sans pion a droite
					for (int i = 1; i <= side; i++)
					{
						pionstab[i].push_back(-1);
					}

					// rajoute une ligne sans pion en bas
					pionstab.push_back(std::vector<int>(side + 2, -1));

					// aumgente la taille du tableau
					side += 2;
				}
			}
		}

		// cas ou on n'a aucune position disponible autour de l'adversaire 
		else
		{
			// utile pour relancer la recherche de position lorsque le bot est entouré de pions
			nbboucle += 1;
		}
	} while (nbboucle != 0);
	
	
	nbtour += 1;
}