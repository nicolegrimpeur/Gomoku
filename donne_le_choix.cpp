#include "donne_le_choix.h"
#include "menu.h"
#include "play.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

// constructeur
donne_le_choix::donne_le_choix()
{
	choisi();
}

// affichage du choix du nombre de jouer et / ou de la taille souhaitée
void donne_le_choix::choisi()
{
	// variables
	float taille_case = (((float)taille_hauteur - 120) / (19 - 1));
	float taille_a_gauche = (((float)taille_largeur / 2) - (((float)taille_hauteur - 120) / 2));
	float taille_pion = 14;
	side = 19;
	nb_joueur = 0;
	std::string taille_text = "";
	std::string static_ou_non = "";

	//permet d'ajouter l'anti-aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	// creation de la page en plen ecran
	sf::RenderWindow window(sf::VideoMode(taille_largeur, taille_hauteur), "Le jeu du Gomoku", sf::Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30); // bloque le jeu à 30 FPS pour améliorer les performances
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen())
	{
		// effacement de la fenêtre en noir
		window.clear(sf::Color::Black);

		// creation des textures et de la police
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

		// création d'un bouton menu
		sf::Text _menu;
		_menu.setFont(police_arial);
		_menu.setString("Menu");
		_menu.setCharacterSize(19);
		_menu.setFillColor(sf::Color::Black);
		_menu.setPosition(5, 0.f);
		window.draw(_menu);



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
				// si l'on clique sur le bouton gauche
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= taille_largeur - 66 && event.mouseButton.y <= 20)  // si le clic est sur le texte quitter
					{
						window.close();
					}

					if (event.mouseButton.x <= 53 && event.mouseButton.y <= 20)  // si le clic est sur le texte menu
					{
						window.close();
						menu affichage;
					}

					// si le clic est sur 1 joueur
					if (event.mouseButton.x >= (float)taille_largeur / 6 && event.mouseButton.x <= 2 * (float)taille_largeur / 6 && event.mouseButton.y >= 2 * (float)taille_hauteur / 7 && event.mouseButton.y <= 3 *(float)taille_hauteur / 7) 
					{
						nb_joueur = 1;
						if (mode == 'c')
						{
							window.close();
							play print;
						}
					}

					// si le clic est sur 2 joueur
					if (event.mouseButton.x >= (float)taille_largeur / 6 && event.mouseButton.x <= 2 * (float)taille_largeur / 6 && event.mouseButton.y >= 4 * (float)taille_hauteur / 7 && event.mouseButton.y <= 5 * (float)taille_hauteur / 7) 
					{
						nb_joueur = 2;
						if (mode == 'c')
						{
							window.close();
							play print;
						}
					}

					// si le clic est sur le bouton go
					if (nb_joueur != 0 && event.mouseButton.x >= (float)taille_largeur / 2 - 35 && event.mouseButton.x <= (float)taille_largeur / 2 + 35 && event.mouseButton.y >= (float)taille_hauteur / 2 - 25 && event.mouseButton.y <= (float)taille_hauteur / 2 + 25)
					{
						window.close();
						play print;
					}

					// si le clic est sur oui
					if (event.mouseButton.x >= 5 * (float)taille_largeur / 6 + 5 && event.mouseButton.x <= 5 * (float)taille_largeur / 6 + 10 + 60 && event.mouseButton.y >= 4 * (float)taille_hauteur / 7 && event.mouseButton.y <= 4 * (float)taille_hauteur / 7 + 7 + 40)
					{
						taille_static = true;
					}

					// si le clic est sur non
					if (event.mouseButton.x >= 5 * (float)taille_largeur / 6 + 5 && event.mouseButton.x <= 5 * (float)taille_largeur / 6 + 10 + 60 && event.mouseButton.y >= 5 * (float)taille_hauteur / 7 - 40 - 7 && event.mouseButton.y <= 5 * (float)taille_hauteur / 7 - 40 + 40)
					{
						taille_static = false;
					}
				}
			}

			// permet d'augmenter la taille du tableau grâce à la molette de la souris
			if (event.type == sf::Event::MouseWheelMoved)
			{
				// verifie que la taille est acceptable ou non
				if (side + event.mouseWheel.delta >= 5 && side + event.mouseWheel.delta <= 75)
				{
					//permet d'avoir toujours une taille impaire
					if (event.mouseWheel.delta % 2 == 0)
					{
						side += event.mouseWheel.delta;
					}
					else
					{
						if (event.mouseWheel.delta < 0)
						{
							side += event.mouseWheel.delta - 1;
						}
						else
						{
							side += event.mouseWheel.delta + 1;
						}
						
					}
					
				}
			}
		}


		// permet de creer le tableau 
		for (float i = 60; i <= taille_hauteur - 60; i += taille_case) // ligne horizontal
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

		// bouton 1 jouer
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setSize(sf::Vector2f((float)(taille_largeur) / 6, (float)taille_hauteur / 7));
		rectangle.setPosition((float)taille_largeur / 6, 2 *(float)taille_hauteur / 7);
		rectangle.setFillColor(sf::Color::White);
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color::Black);
		window.draw(rectangle);

		// texte du bouton 1 joueur
		sf::Text texte;
		texte.setFont(police_arial);
		texte.setString("1 joueur");
		texte.setCharacterSize(26);
		texte.setFillColor(sf::Color::Black);
		texte.setPosition((float)taille_largeur / 6 + (float)taille_largeur / (6 * 4), 2 *(float)taille_hauteur / 7 + (float)taille_hauteur / (7 * 2) - 20);
		window.draw(texte);

		// bouton 2 joueur
		sf::RectangleShape rectangle2(sf::Vector2f(120, 50));
		rectangle2.setSize(sf::Vector2f((float)(taille_largeur) / 6, (float)taille_hauteur / 7));
		rectangle2.setPosition((float)taille_largeur / 6, 4 * (float)taille_hauteur / 7);
		rectangle2.setFillColor(sf::Color::White);
		rectangle2.setOutlineThickness(2);
		rectangle2.setOutlineColor(sf::Color::Black);
		window.draw(rectangle2);

		// texte du bouton 2 joueur
		sf::Text texte2;
		texte2.setFont(police_arial);
		texte2.setString("2 joueurs");
		texte2.setCharacterSize(26);
		texte2.setFillColor(sf::Color::Black);
		texte2.setPosition((float)taille_largeur / 6 + (float)taille_largeur / (6 * 4), 4 * (float)taille_hauteur / 7 + (float)taille_hauteur / (7 * 2) - 20);
		window.draw(texte2);

		// si le mode est libre
		if (mode != 'c')
		{
			// bouton pour changer la taille
			sf::RectangleShape rectangle_taille(sf::Vector2f(120, 50));
			rectangle_taille.setSize(sf::Vector2f((float)(taille_largeur) / 6, (float)taille_hauteur / 7));
			rectangle_taille.setPosition(4 * (float)taille_largeur / 6, 2 * (float)taille_hauteur / 7);
			rectangle_taille.setFillColor(sf::Color::White);
			rectangle_taille.setOutlineThickness(2);
			rectangle_taille.setOutlineColor(sf::Color::Black);
			window.draw(rectangle_taille);

			// texte du bouton changer la taille 
			sf::Text texte_taille;
			texte_taille.setFont(police_arial);
			taille_text = std::to_string(side);
			texte_taille.setString("Molette \npour changer \nla taille !   " + taille_text);
			texte_taille.setCharacterSize(26);
			texte_taille.setFillColor(sf::Color::Black);
			texte_taille.setPosition(4 * (float)taille_largeur / 6 + 20, 2 * (float)taille_hauteur / 7 + 7);
			window.draw(texte_taille);

			// bouton pour bloquer la taille 
			sf::RectangleShape rectangle_bloque(sf::Vector2f(120, 50));
			rectangle_bloque.setSize(sf::Vector2f((float)(taille_largeur) / 6, (float)taille_hauteur / 7));
			rectangle_bloque.setPosition(4 * (float)taille_largeur / 6, 4 * (float)taille_hauteur / 7);
			rectangle_bloque.setFillColor(sf::Color::White);
			rectangle_bloque.setOutlineThickness(2);
			rectangle_bloque.setOutlineColor(sf::Color::Black);
			window.draw(rectangle_bloque);

			// texte du bouton pour bloquer la taille
			sf::Text texte_bloque;
			texte_bloque.setFont(police_arial);
			if (taille_static == true)
			{
				static_ou_non = "Oui";
			}
			else
			{
				static_ou_non = "Non";
			}
			texte_bloque.setString("Bloquer \nla taille :\n" + static_ou_non);
			texte_bloque.setCharacterSize(26);
			texte_bloque.setFillColor(sf::Color::Black);
			texte_bloque.setPosition(4 * (float)taille_largeur / 6 + 20, 4 * (float)taille_hauteur / 7 + 7);
			window.draw(texte_bloque);
			
			// texte du bouton oui
			sf::Text texte_oui;
			texte_oui.setFont(police_arial);
			texte_oui.setString("Oui");
			texte_oui.setCharacterSize(26);
			texte_oui.setFillColor(sf::Color::Black);
			texte_oui.setPosition(5 * (float)taille_largeur / 6 + 10, 4 * (float)taille_hauteur / 7 + 7);
			window.draw(texte_oui);

			// texte du bouton non
			sf::Text texte_non;
			texte_non.setFont(police_arial);
			texte_non.setString("Non");
			texte_non.setCharacterSize(26);
			texte_non.setFillColor(sf::Color::Black);
			texte_non.setPosition(5 * (float)taille_largeur / 6 + 10, 5 * (float)taille_hauteur / 7 - 40);
			window.draw(texte_non);

			// si le joueur n'a pas choisi le nombre de joueur
			if (nb_joueur != 0)
			{
				// bouton go
				sf::RectangleShape rectangle_go(sf::Vector2f(120, 50));
				rectangle_go.setSize(sf::Vector2f(70, 50));
				rectangle_go.setPosition((float)taille_largeur / 2 - 35, (float)taille_hauteur / 2 - 25);
				rectangle_go.setFillColor(sf::Color::White);
				rectangle_go.setOutlineThickness(2);
				rectangle_go.setOutlineColor(sf::Color::Black);
				window.draw(rectangle_go);

				// texte du bouton go
				sf::Text go;
				go.setFont(police_arial);
				go.setString("Go !");
				go.setCharacterSize(35);
				go.setFillColor(sf::Color::Black);
				go.setPosition((float)taille_largeur / 2 - 32, (float)taille_hauteur / 2 - 20);
				window.draw(go);
			}
		}

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}
}