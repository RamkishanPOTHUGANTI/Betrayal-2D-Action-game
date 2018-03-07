#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include "threadPool.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "game.h"




int main() {
	sf::RenderWindow *gameWindow=new sf::RenderWindow(sf::VideoMode(1366, 768), "BETRAYAL=>GAME", sf::Style::Fullscreen);
	gameWindow->setKeyRepeatEnabled(false);
	
	Game * game = new Game(10, gameWindow,3,10,"maps_f/level1_part1@maps_f/room2@maps_f/level3@");
	game->displayTitlescreen();
	while (game->running())
	{
		game->handleEvents();
		if (game->gameActive){
			game->update();
			game->render();
		}
		if (game->isgameOver) {
			game -> restart();
		}
	}
		
		return 0;
}


