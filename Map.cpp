#include "Map.h"



Maps::Maps(int level,std::string a, int numLines, sf::Vector2u wb,int l,int b)
{
	mapLevel = level;
	img_file = a + ".png";

	collision_layer_file = a + ".txt";
	
	tileLength = l;
	tileBreadth = b;
	lines = numLines;
	windowBounds = wb;
	moveMapTimermax = 60;
	moveMapTimer = moveMapTimermax;
	count =1;
}
int  Maps::initialize(int level,float a, float b, float lenghtWindow, float bradthWindow) {
	x_ = 1.0f;
	y_ = 1.0f;
	length = lenghtWindow;
	breadth = bradthWindow;
	if (!tex.loadFromFile(img_file)) {
		std::cout << "unable to load the map" << std::endl;
		return EXIT_FAILURE;
	}
	if (!tex1.loadFromFile("maps_f/level1_part2.png"));
	backGround.setTexture(tex);
	backGround.setTextureRect(sf::IntRect(a, b, lenghtWindow, bradthWindow));
	if (level!=1) getTilePositions();

	return 0;
	
}

int Maps::getTilePositions() {

	std::fstream file(collision_layer_file);
	if (!file) {
		std::cout << "Error opening the tile file" << std::endl;
		return EXIT_FAILURE;
	}
	std::string temp;
	int x = 0, y = 0, l = 32, b = 32;
//	std::cout << "no of lines " << lines << std::endl;
	for (int i = 0, j = 0; i<lines; i++)
	{
		x = 0;
		y = 0;
		file >> temp;
		file >> temp;
		file >> temp;
	//	std::cout << "printing the temp value " << temp << std::endl;
		j = 0;
		while (temp[j++] != '"');
		while (temp[j] != '"')x = x * 10 + (int)(temp[j++] - '0');
		j = 0;
		file >> temp;
//		std::cout << temp << std::endl;
		while (temp[j++] != '"');
		while (temp[j] != '"')y = y * 10 + (int)(temp[j++] - '0');
		tilePositions.push_back(sf::Vector2f(x, y));
		forbiddenZones[y/32][x/32] = true;
		std::cout << "y= " << y / 32 << " x=" << x / 32 <<std::endl;
		file >> temp;
		file >> temp;
		file >> temp;
		file >> temp;
		file >> temp;
		file >> temp;
		file >> temp;
		file >> temp;
	}
	file.close();
	return 0;
}
int Maps::checkCollision(sf::Vector2f playerPos, sf::Vector2f direction,float speed) {
	/* Used to check collision with the forbidden zones*/
	sf::Vector2f futurePos;
	sf::Vector2u intfuturePos;
	futurePos = playerPos + (direction * speed);
	intfuturePos.x = futurePos.x / 32;
	intfuturePos.y = (futurePos.y) / 32;
	if (direction==sf::Vector2f(0.f,1.f)) intfuturePos.y = (futurePos.y+90) / 32;
	else if (direction==sf::Vector2f(1.f,0.f)) intfuturePos.x = (futurePos.x+90) / 32;
	else if (direction == sf::Vector2f(0.f, -1.f)) intfuturePos.y = (futurePos.y + 90) / 32;
	std::cout << "int Future position are " << intfuturePos.x << " " << intfuturePos.y << std::endl;
	if (forbiddenZones[intfuturePos.y][intfuturePos.x]==true) {
		std::cout << "hit\n";
		return 1;
	}
	else {
		return 0;
	}
}



int Maps::move_background(sf::Vector2f direction1,sf::Vector2f direction2, float speed1,float speed2, sf::Vector2f hero1Pos, sf::Vector2f hero2Pos) { //hero2Pos needs to move
	float x = x_, y = y_;
	int flag = 0;
	sf::Vector2f fuHero1Pos, fuHero2Pos ;// future points for both players
/*	if (direction == 'u') {
		y = y - speed;
		fuHero1Pos.y += speed;
		fuHero2Pos.y -= speed;
	}
	else if (direction == 'd') {
		y = y + speed;
		fuHero1Pos.y -= speed;
		fuHero2Pos.y += speed;
	}
	else if (direction == 'r') {
		x = x + speed;
		fuHero1Pos.x -= speed;
		fuHero2Pos.x += speed;
	}
	else if (direction == 'l') {
		x = x - speed;
		fuHero1Pos.x += speed;
		fuHero2Pos.x -= speed;
	}
//	if (check_collision_with_boundary(direction, speed, hero2Pos) == 1)return flag;
//	if (isColliding(fuHero2Pos, sf::Vector2f(0, 0), length, breadth) == 1 && isColliding(hero1Pos, sf::Vector2f(0, 0), length, breadth) == 1) {
		flag = 2;	//need to change player position
//	}
/*	if (isColliding(fuHero2Pos + sf::Vector2f(x_, y_),sf::Vector2f( x, y), length, breadth) && isColliding(fuHero1Pos + sf::Vector2f(x_, y_),sf::Vector2f( x, y), length, breadth) && flag == 2) {
		if (x >= 0 && y >= 0 && x + length <= img_len && y + breadth <= img_brd) {
			//move background
			x_ = x;
			y_ = y;
			backGround.setTextureRect(sf::IntRect(x_, y_, length, breadth));
			flag = 1;   //1 when background is changed no need to change position of player sprite
		}
	}`
	std::cout << "flag value " << flag << std::endl;
*/
	fuHero1Pos = hero1Pos + (direction1 * speed1);
	fuHero2Pos = hero2Pos + (direction2 * speed2);
/*	if (mapLevel != 1) {
//		if (fuHero1Pos.x >= windowBounds.x/2 && fuHero2Pos.x >55 || fuHero2Pos.x >= 55 && fuHero1Pos.x >=windowBounds.x / 2){
			std::cout << "moving\n";
			if (x_ + windowBounds.x < 3804) {
				x_ = x_ + 45;
				backGround.setTextureRect(sf::IntRect(x_, y_, windowBounds.x, windowBounds.y));
				std::cout << "moved\n";
				//			}
			}
//		}

	}
	if ( mapLevel == 1 && x_ + windowBounds.x > 3804) {
		std::cout << "changed x_\n";
		x_ = 0;
		if (y_ + windowBounds.y < 3804) {
			y_ += 768;
			std::cout << "changed y_\n";
		
		}
	}
*/	
//	moveMapTimer++;
//	if ()
	if (mapLevel == 1 && (fuHero1Pos.x > length / 2 || fuHero2Pos.x > length / 2) && (fuHero2Pos.x > 55 || fuHero1Pos.x > 55)) {
		if (x_ + windowBounds.x < 3804) {
			x_ = x_ + 4.5f;
			//		y_ = y;
			backGround.setTextureRect(sf::IntRect(x_, y_, windowBounds.x, windowBounds.y));

		}

	}
	return flag;
}
void Maps::renderMap(sf::RenderTarget * target) {

	target->draw(backGround);

}
Maps::~Maps()
{
}