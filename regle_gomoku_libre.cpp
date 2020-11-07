#include "regle_gomoku_libre.h"
#include "menu.h"
#include "play.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// constructeur
regle_gomoku_libre::regle_gomoku_libre()
{
	affichage_gomoku_libre();
}

// permet d'afficher les regles du gomoku libre
void regle_gomoku_libre::affichage_gomoku_libre()
{
	// variables 
	float taille_case = (((float)taille_hauteur - 120) / (19 - 1));
	float taille_a_gauche = (((float)taille_largeur / 2) - (((float)taille_hauteur - 120) / 2));
	float taille_pion = 14;

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

		// creation des polices et de la texture
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
				// si l'on clique sur le bouton quitter, on sort
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
				}
			}
		}

		// affichage du tableau 
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
		
		// creation d'un rectangle sur lequel seront ecrites les regles
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setSize(sf::Vector2f((float)(taille_largeur - ((taille_a_gauche + 5) * 2)), (float)taille_hauteur - 120 - 10));
		rectangle.setPosition((float)taille_a_gauche + 5, (float)(60 + 5));
		rectangle.setFillColor(sf::Color::White);
		window.draw(rectangle);

		// affichage des regles
		sf::Text _regle;
		_regle.setFont(police_arial);
		_regle.setString(regles);
		_regle.setCharacterSize(19);
		_regle.setFillColor(sf::Color::Black);
		_regle.setPosition(taille_a_gauche + 10, 60.f + 10);
		window.draw(_regle);

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}
}