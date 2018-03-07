#pragma once
#pragma once
#include <SFML\Graphics.hpp>
class Image_player
{
private:
	int num_strings, *sleep_time;
	std::string * str;

public:
	Image_player(std::string a, std::string t, int n);
	int image_display_function(sf::RenderWindow *);
	~Image_player();
};