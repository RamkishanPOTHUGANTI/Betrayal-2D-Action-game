#include "IntroDisplay.h"
#include <thread>
#include <SFML\Graphics.hpp>

Image_player::Image_player(std::string image, std::string waitTime, int n)	//filenames , sleeptime sepetrated with '@'
{

	num_strings = n;
	str = new std::string[n];
	sleep_time = new int[n];
	
	for (int i = 0, j = 0; i < n; i++) {
		std::string temp = "";
		for (; ; j++)
		{
			if (image[j] == '@')break;
			temp = temp + image[j];
		}
		j = j + 1;
		*(str + i) = temp;
	}
	for (int i = 0, j = 0; i < n; i++) {
		int temp = 0;
		for (;; j++) {
			if (waitTime[j] == '@')break;
			temp = temp * 10 + waitTime[j] - '0';
		}
		j = j + 1;
		*(sleep_time + i) = temp;
	}
}

int Image_player::image_display_function(sf::RenderWindow * window) {
	sf::Vector2f targetSize(window->getSize().x, window->getSize().y);
	for (int i = 0; i < num_strings; i++)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(*(str + i)))return 1;
		sf::Sprite img_f;
		img_f.setTexture(texture);
		img_f.setScale(targetSize.x / img_f.getLocalBounds().width, targetSize.y / img_f.getLocalBounds().height);
		window->draw(img_f);
		window->display();
		std::this_thread::sleep_for(std::chrono::seconds(*(sleep_time + i)));
	}
	return 0;
}

Image_player::~Image_player()
{
	delete[]str;
	delete[]sleep_time;
}