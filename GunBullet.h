#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
/** Class for bullets shooted by the players
*/
class GunBullet {

	public:
		GunBullet();
		GunBullet(int,int,sf::Texture tex, const sf::Vector2f position, char direction);
		/** Method for the movement of the bullets
			Function takes player position for which the bullets will chase
		*/
		int movement(sf::Vector2f playerPos);
		/** Method to update the bullets 
			
			Takes a player position to chase the player
		
		*/
		int update(sf::Vector2f playerPos);

		// To get the position of the bulles
		inline sf::Vector2f getPosition() {
			return sprite.getPosition();
		}
		// Checks if the bullets is out of bounds and erases it if yes
		inline bool isOutOfBounds(sf::Vector2u windowBounds) {
			if (sprite.getPosition().x > windowBounds.x || sprite.getPosition().x<0 || sprite.getPosition().y>windowBounds.y || sprite.getPosition().y<0) {
				std::cout << sprite.getPosition().x << "and" << sprite.getPosition().y << std::endl;
				return true;
			}
			else return false;
		}
		// Function to get the global bounds
		inline sf::FloatRect getGlobalBounds() {
			return sprite.getGlobalBounds();
		}

		inline sf::Vector2f getDirection() {
			return this->direction;
		}

		void draw(sf::RenderTarget &target);
		float vectorLength(sf::Vector2f v);

		sf::Vector2f normalize(sf::Vector2f v, float length);

		int playerFollow; // indicating which player to follow
		float acceleration, speed; // the acceleration and the speed

	private:

		int type;
		// Texture of the bullets
		sf::Texture texture;
		// Sprite of the bullets
		sf::Sprite sprite;
		// For velocity 
		sf::Vector2f maxVelocity,direction;
		sf::Vector2f currentVelocity;

};