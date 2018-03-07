
#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <thread>
#include <iostream>
#include <fstream>



class Maps
{
public:

	Maps(int,std::string a, int numLines, sf::Vector2u,int l=32,int b=32);
	int initialize(int level,float a, float b, float c, float d);
	int move_background(sf::Vector2f,sf::Vector2f, float,float, sf::Vector2f hero1Position, sf::Vector2f hero2Position);
	void renderMap(sf::RenderTarget * target);
	int getTilePositions();
	~Maps();
	float x_, y_, length, breadth, scale_x, scale_y, img_len, img_brd;
	int checkCollision(sf::Vector2f, sf::Vector2f,float);
	
private:
	std::vector<sf::Vector2f> tilePositions;
	bool forbiddenZones[30][122];
	bool isColliding(sf::Vector2f player,sf::Vector2f tile,int rectLength,int rectBreadth);
//	void used_in_boundarycollision(sf::Vector2f point, int start, int *result);
	int moveMapTimermax, moveMapTimer;
	sf::Vector2u windowBounds;
	std::string img_file,img_file1, collision_layer_file,collision_layer_file1;
	int lines,lines1;
	int tileLength, tileBreadth;
	sf::Texture tex,tex1;  //background img
	sf::Sprite backGround; // background
	int mapLevel;
	int count;

};