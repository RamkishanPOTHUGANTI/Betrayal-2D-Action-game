#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#define NumMenuItems 3
class Menu {

public:
	int displayMenu();
	Menu(sf::RenderWindow * window,int);
	~Menu();
	void moveUp();
	void moveDown();
	int loadMenu();
	int menuSelected;

private:
	enum menuItems
	{
		Play = 0,
		Options,
		Exit,
		LastMenu
	};
	int option;
	sf::Text menuText[NumMenuItems];
	sf::Font fontStyle;
	
	float Menuwidth;
	float MenuHeight;
	sf::RenderWindow * menuWindow;
	sf::Sprite menuImage;
	sf::Texture menuTexture,menuTexture1;





};