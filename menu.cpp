#include "menu.h"
#include "play.h"
#include "regle_vrai_gomoku.h"
#include "regle_gomoku_libre.h"
#include "donne_le_choix.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// constructeur 
menu::menu()
{
	affichage();
}

// permet d'afficher le menu
void menu::affichage()
{
	// variables 
	float taille_case = (((float)taille_hauteur - 120) / (19 - 1));
	float taille_a_gauche = (((float)taille_largeur / 2) - (((float)taille_hauteur - 120) / 2));
	float taille_pion = 14;

	//permet d'ajouter l'anti-aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	// création de la fenetre en mode plein ecran
	sf::RenderWindow window(sf::VideoMode(taille_largeur, taille_hauteur), "Le jeu du Gomoku", sf::Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true); 
	window.setFramerateLimit(30); // bloque le jeu à 30 FPS pour améliorer les performances
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen())
	{
		// effacement de la fenêtre en noir
		window.clear(sf::Color::Black);

		//rajout des textures et de la police
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

		// création d'un bouton vrai_gomoku
		sf::Text vrai_gomoku;
		vrai_gomoku.setFont(police_arial);
		vrai_gomoku.setString("Vrai Gomoku");
		vrai_gomoku.setCharacterSize(35);
		vrai_gomoku.setFillColor(sf::Color::Black);
		vrai_gomoku.setPosition(20.f, (float)taille_hauteur * 2 / 9);
		window.draw(vrai_gomoku);

		// création d'un bouton gomoku_libre
		sf::Text gomoku_libre;
		gomoku_libre.setFont(police_arial);
		gomoku_libre.setString("Gomoku Libre");
		gomoku_libre.setCharacterSize(35);
		gomoku_libre.setFillColor(sf::Color::Black);
		gomoku_libre.setPosition(20.f, (float)taille_hauteur * 4 / 9);
		window.draw(gomoku_libre);

		// création d'un bouton quitter
		sf::Text quitter;
		quitter.setFont(police_arial);
		quitter.setString("Quitter");
		quitter.setCharacterSize(35);
		quitter.setFillColor(sf::Color::Black);
		quitter.setPosition(20.f, (float)taille_hauteur * 6 / 9);
		window.draw(quitter);

		// création d'un bouton regles_vrai_gomoku
		sf::Text regles_vrai_gomoku;
		regles_vrai_gomoku.setFont(police_arial);
		regles_vrai_gomoku.setString("Règles \nVrai Gomoku");
		regles_vrai_gomoku.setCharacterSize(35);
		regles_vrai_gomoku.setFillColor(sf::Color::Black);
		regles_vrai_gomoku.setPosition((float)taille_largeur - 300, (float)taille_hauteur / 4 + 50);
		window.draw(regles_vrai_gomoku);

		// création d'un bouton regles_gomoku_libre
		sf::Text regles_gomoku_libre;
		regles_gomoku_libre.setFont(police_arial);
		regles_gomoku_libre.setString("Règles \nGomoku libre");
		regles_gomoku_libre.setCharacterSize(35);
		regles_gomoku_libre.setFillColor(sf::Color::Black);
		regles_gomoku_libre.setPosition((float)taille_largeur - 300, (float)taille_hauteur * 2 / 4 + 50);
		window.draw(regles_gomoku_libre);

		// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed)
				window.close();

			// lorsque un clic est effectue 
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// si l'on effectue un clic gauche
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// si le clic est sur le texte vrai gomoku
					if (event.mouseButton.x >= 20 && event.mouseButton.x <= 225 && event.mouseButton.y >= (float)taille_hauteur * 2 / 9 && event.mouseButton.y <= 210)
					{
						mode = 'c';
						window.close();
						donne_le_choix choisi;
					}
					// si le clic est sur le texte gomoku libre
					if (event.mouseButton.x >= 20 && event.mouseButton.x <= 240 && event.mouseButton.y >= (float)taille_hauteur * 4 / 9 && event.mouseButton.y <= 380)
					{
						mode = 'l';
						window.close();
						donne_le_choix choisi;

					}
					// si le clic est sur le texte quitter
					if (event.mouseButton.x >= 20 && event.mouseButton.x <= 125 && event.mouseButton.y >= (float)taille_hauteur * 6 / 9 && event.mouseButton.y <= 550)
					{
						window.close();
					}
					// si le clic est sur le texte règle vrai gomoku
					if (event.mouseButton.x >= (float)taille_largeur - 300 && event.mouseButton.x <= taille_largeur - 76 && event.mouseButton.y >= (float)taille_hauteur / 4 + 50 && event.mouseButton.y <= 320)
					{
						window.close();
						regle_vrai_gomoku affichage_vrai_gomoku;
					}
					// si le clic est sur le texte règle gomoku libre
					if (event.mouseButton.x >= (float)taille_largeur - 300 && event.mouseButton.x <= taille_largeur - 71 && event.mouseButton.y >= (float)taille_hauteur * 2 / 4 + 50 && event.mouseButton.y <= 510)
					{
						window.close();
						regle_gomoku_libre affichage_gomoku_libre;
					}
				}
			}
		}

		// creation du tableau 
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

		// création du point central
		sf::CircleShape circle(taille_pion);
		circle.setPosition((int)((19 - 1) / 2) * taille_case + taille_a_gauche - taille_pion, (int)((19 - 1) / 2) * taille_case + 60 - (float)taille_pion);
		circle.setFillColor(sf::Color::Black);
		circle.setOutlineThickness(1);
		circle.setOutlineColor(sf::Color::White);
		window.draw(circle);

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}
}
