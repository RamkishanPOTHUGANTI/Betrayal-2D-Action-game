#pragma once

#include <SFML\Audio.hpp>
#include "threadPool.h"
#include <SFML\Audio.hpp>
#include "menu.h"
#include "Map.h"
#include "GunBullet.h"
#include "Enemy.h"

class Hero {
public:
	Hero(std::string,std::string,sf::Vector2f,int,int,int,int,int,int,int,int,int,sf::Vector2u);

	~Hero();
	/**	This method is used to load the files necessary for the heroes
	*
	*
	*	It takes no parameters since all the essentials are provided in the constructor
	*
	*	It return 0 to indicate that it finished successfully and return an EXIT_FAILURE code to indicate that error occured.
	*/
	int loadFiles();
	/** This method is used to represent the movement of the hero. 
	*
	*
	*	It takes no parameter
	*
	*	It returns void
	*/
	void movement();
	/** This method is used to update the parameters of the heroes like updating the bullets position etc.
	*
	*
	*	It takes  no parameters 
	*
	*	It return void
	*/

	int update();
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
	/** Function to take damages to reduce the health of the heroes
	*
	*
	*	It takes the parameter damage to reduce the health by that amount
	*
	*	It return integer
	*/

	int takeDamage(int damage);
	inline int setLevel(int level) {
		// Function used to set level of the heroes
		currentLevel = level;
		return 0;
	}
	inline sf::Vector2f getPosition() {
		// Function used to set the position of the enemies

		return sprite.getPosition();
	}
	inline sf::Vector2f getDirection() {
		// Functino to get the direction of the enemiess
		return this->direction;
	}
	inline int setCurrentMap(Maps &newmap) {
		// Function to set the current map

		currentMap = &newmap;
		return 0;
	}
	inline void setEnemies(std::vector<Enemy>& e) {
		// Function to pass the enemies array
		enemies =& e;
		std::cout << "the numer safsadfs " << e.size() << "and "<<enemies->size() << std::endl;
	
	}
	inline std::vector<GunBullet>& getBullets() {
		// Function to return the bullets fired by the hero
		return bullets;
	}
	inline sf::FloatRect getGlobalBounds() {
		//Function to get the global bounds

		return this->sprite.getGlobalBounds();
	}
	inline int getDamage() { return rand() % this->damagemax + this->damage; }

	bool isAlive;
	bool isGuardOn;
	float speed;
	std::vector<GunBullet> bullets;

private:
	std::string fr, fl, br, bl, rr, rl, rm, lr, ll, lm,space; //fr = front side and right leg front similarly all others 
	sf::Texture fr_, fl_, br_, bl_, rr_, rl_, rm_, lr_, ll_, lm_; // Same for the textures as the sprite used only for level 1 and 3
	// Sprite of the hero
	sf::Sprite sprite; 
	// The ground texture
	sf::Texture groundTex;
	// The bullet texture
	sf::Texture bulletTexture;
	sf::Texture spaceTexture;
	// Arrays
	std::vector<Enemy>  *enemies;
	std::vector<sf::Text> playerFollowText;

	bool is_right = 1, is_side = 1;
	int score;
	int xp;
	// Controls of the heroes
	int hControls[5];
	int currentHp;  // current Health
	int maxhp; // max health
	int damage, damagemax;
	float acceleration;
	float maxVelocity;
	// For players position veclocity and its window bounds
	sf::Vector2u windowBounds;
	sf::Vector2f currentVelocity;
	sf::Vector2f initialPos;
	sf::Vector2f currentPos;
	sf::Vector2f nextPos,direction;
	// For player sounds
	sf::SoundBuffer gunBuffer, gunBuffer1, gunBuffer2;
	sf::Sound gunSound;
	sf::Font fontStyle;
	// To load the textures from that path
	std::string imgPath, bulletPath;

	char presentdirection = 'd';
	int currentLevel;

	Maps * currentMap;



};