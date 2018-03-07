#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class player_1
{
public:
	std::string fr, fl, br, bl, rr, rl, rm, lr, ll, lm; //fr = front side and right leg front similarly all others 
	sf::Vector2f intialpositions; // always intially sprite comes with fornt face rightleg before .. 
	sf::Vector2f currentpositions;
	char presentdirection = 'f';
	sf::Texture fr_, fl_, br_, bl_, rr_, rl_, rm_, lr_, ll_, lm_;
	sf::Sprite state;
	bool is_right = 1, is_side = 1;
	player_1(std::string a);//string a should be in format file name and key for changing it then seperated by , and _
	int intialseimage(sf::Vector2f ip); //displays intial sprite in given position
	void drawplayer(sf::RenderWindow * window_); //draws sprite
	void move_player(char direction, float speed);	//moves sprite ..
	void shift_player(char direction, float speed);
	~player_1();
};
