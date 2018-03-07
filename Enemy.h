#pragma once

#include <SFML\Audio.hpp>
#include "threadPool.h"
#include <SFML\Audio.hpp>
#include "menu.h"
#include "Map.h"
#include "GunBullet.h"

class Enemy{

	public:
		Enemy(int,sf::Texture , sf::Texture, sf::Texture,sf::SoundBuffer, sf::Vector2f, int, int,int,sf::Vector2f,sf::Vector2u);
		/**	This method is used to load the files necessary for the enemies 
		*
		*
		*	It takes no parameters since all the essentials are provided in the constructor
		*
		*	It return 0 to indicate that it finished successfully and return an EXIT_FAILURE code to indicate that error occured.
		*/
		int loadFiles();
		/** This method is used to represent the movement of the enemy. The enemies can either move just to the left or can chase the heroes
		*
		*
		*	It takes parameters the position of the player it has to chase 
		*
		*	It returns void 
		*/
		void movement(sf::Vector2f);
		/** This method is used to update the parameters of the enemies like updating the bullets position etc.
		*
		*
		*	It takes parameters of the players position it is chasing and the player bounds to determine wether collision occured or not
		*
		*	It return void
		*/
		void update(sf::Vector2f,sf::FloatRect);
		/** This method is used to render the enemies on the window
		*
		*
		*	It takes parameter of the render target to draw it on the screen
		*
		*
		*	It return void
		*/
		void draw(sf::RenderTarget *);
		/** This method is used to initialize the players position when the level is restarted 
		*
		*	It takes no parameters
		*
		*	It returns void
		*/
		int initialize();
		/** This method is used to shoot the missiles which chase the players
		*
		*
		*	It takes no parameters
		*	
		*	It returns an integer 
		*/
		int shoot();
		inline int setLevel(int level) {
			// Function used to set level of the enemies
			currentLevel = level;
			return 0;
		}
		inline sf::Vector2f getPosition() {
			// Function used to set the position of the enemies
			return sprite.getPosition();
		}
		inline sf::Vector2f getDirection() {
			// Functino to get the direction of the enemies
			return direction;
		}
		inline int setCurrentMap(Maps newmap) {
			// Function to set the current map
			currentMap = &newmap;
			return 0;
		}
		inline int getHP() const {
			// Function to return the health of the enemies
			return this->hp;
		}
		inline sf::FloatRect getGlobalBound() {
			//Function to get the global bounds
			return sprite.getGlobalBounds();
		}
		inline sf::FloatRect getActiveArea() {
			// Function to get the active area of the enemies under whic it will shoot missiles
			return sf::FloatRect(sf::Vector2f(sprite.getPosition().x-300,sprite.getPosition().y-300),sf::Vector2f(sprite.getGlobalBounds().width *4,sprite.getGlobalBounds().height*4));
		}
		inline int isDead() const {
			// Function to indicate wethre enemy died or not
			return this->hp <= 0;
		}
		/** Function to take damages to reduce the health of the enemies
		*
		*	
		*	It takes the parameter damage to reduce the health by that amount
		*
		*	It return integer
		*/
		int takeDamage(int damage);
		int type;
		/** Function to return the vector length of the vector v
		*
		*
		*	It takes parameter the vector for which length is to be found
		*
		*	it returns float the length of the vector
		*/
		float vectorLength(sf::Vector2f v);
		/** Function used to normalize the vector 
		*
		*
		*	It takes parameter the vector and the lenght 
		*
		*	
		*	It returns a vector which is a normalized vector
		*/
		sf::Vector2f normalize(sf::Vector2f v, float length);
		int playerNr;

	private:
		// The sprite of the enemy
		sf::Sprite sprite;
		// The ground texture
		sf::Texture groundTex;
		// The bullet texture
		sf::Texture bulletTexture;
		sf::Texture spaceTexture;
		sf::Vector2u windowBounds;
		
		std::string enemy1, enemy2;
		// vector holding the bullets fired
		std::vector<GunBullet> bullets;
		// Timer to shoot the bullets
		int bulletTimer;
		// Min damage it can give
		int damageMin;
		// Max damage it can give
		int damageMax;
		// Pointer to the current Map
		Maps * currentMap;
		int currentLevel;
		sf::Vector2f direction;
		// Sound Buffers 
		sf::SoundBuffer gunBuffer;
		sf::Sound gunSound;
		sf::Font fontStyle;
		// The speed of the enemies
		float speed;
		int hp;  // current Health
		int maxhp; // max health
		sf::Vector2f initialPos;
		sf::Vector2f currentPos;
		sf::Vector2f nextPos;
		
		int level;
		// Damage it imparted on the heros
		int damage;


};