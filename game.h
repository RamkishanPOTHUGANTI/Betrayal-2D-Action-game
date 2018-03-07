#pragma once
#include <SFML\Graphics.hpp>
#include "threadPool.h"
#include <future>
#include "menu.h"
#include "IntroDisplay.h"
#include "Hero.h"
#include <SFML\Audio.hpp>
#include "Map.h"
#include "Enemy.h"
/* First create the players using players class then create the game pass the player pointers to the game
   
*/
class Game {
	public:

		Game(int numWorkerThreads,sf::RenderWindow *,int numLevels,int enemies,std::string maps);

		~Game();
		int init();
		void handleEvents();
		void update();
		void render();
		bool gameActive;
		/**	Function is used to display the title screen and at the same time parallerly loading the resources 
		*
		*
		* Function takes no parameters 
		*
		*return integer if sucess
		*/
		int displayTitlescreen();
		/** Function is used to display the game over title screen 
		*
		*
		* Function takes no parameter
		*
		*	return 0 if sucess 
		*/
		int displayGameOver();
		
		inline	sf::RenderWindow * getGameWindow() {
			//Function to get the render window
			return this->gameWindow;   // Can be *this->gameWindow??
		}
		inline bool running() {
			// Function to check if the game is running or not
			if (gameWindow->isOpen()) return true;
			else return false;
		}
		inline void clean() {
	
			gameWindow->close();
		
		}
		Menu * mainMenu,*pauseMenu;
		sf::RenderWindow * gameWindow;
		bool runGame, isgameOver;// if menu active or not
		int restart();

private :
	/*Atrributes for the game class */
	int numEnemies; // num of enemies
	sf::Event event; // to get the events   
	threadPool * workerPool; // pointer to the thread pool
	std::vector<Enemy> enemies; // array for holding the information of the enemies
//	std::vector<sf::Sprite> spriteSheet;
//	std::vector<sf::Sound> sounds;
	std::vector<Maps> gameMaps; // array for holding the maps

	std::string mapPaths;

	Hero *srikanth, *ujjieve; // Pointer to the heroes
	// Songs used in the game
	sf::Music *mainMenuSong;
	sf::Music *storySong;
	sf::Music *openingSong;
	sf::SoundBuffer enemyGunSound,gameOverBuffer,gameLoadedBuffer,enemyMissileBuffer;
	sf::Sound gameOverSound,gameLoadedSound,enemyMissileSound;
	// Enemy textures
	sf::Texture spaceEnemy, groundEnemy,bulletEnemy;
	// Text used in the game
	sf::Text gameOverText,gameLoadedText;
	sf::Font fontStyle;
	// Used for shooting and spawning the enemies
	int enemyspawntimer, enemyspawntimermax,enemyShootTimer,enemyShootTimerMax;
	// To get the current level and the total levels
	int currentLevel, totalLevels;
	int totalenemies; // Stores the total enemies
	
	int isopen;
	bool islevelCompleted; // if level is completed
	bool iskey;
	// To check if main menu or pause menu or spacebar is active or not
	bool isMenuActive, isPauseActive,spacebarInactive;

	/*Methods used by game class*/

	// For displaying purposes
	int displayStory();
	// For updating purposes
	int playersUpdate();
	int mapUpdate();
	int levelUpdate();
	int enemyUpdate();
	// For rendering purposes
	void playerRender();
	void mapRender();
	// For loading purposes
	int loadMenu();
	int loadMaps();
	int loadEnemies();
	int loadSounds();
	int reloadEnemies();

};