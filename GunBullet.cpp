#include "GunBullet.h"

GunBullet::GunBullet() {

}
GunBullet::GunBullet(int num,int t,sf::Texture tex,const sf::Vector2f pos, char direction) {

	this->texture = tex;
	this->sprite.setTexture(tex);
	this->sprite.setScale(sf::Vector2f(0.5f, 0.05f));
	if (t==1) 	this->sprite.setScale(sf::Vector2f(0.05f, 0.05f));

	this->sprite.setPosition(pos.x+100,pos.y+25 );
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->type = t;
	acceleration = 0.5f;
	speed=1.5f;
	playerFollow = num;
	switch (direction) {
	case 'r':
		this->sprite.setPosition(pos.x + 100, pos.y + 25);
		this->maxVelocity = sf::Vector2f(20.0f, 0.0f);
		this->direction = sf::Vector2f(1.f, 0.0f);
		break;
	case 'l':
		this->sprite.setPosition(pos.x, pos.y + 25);
		this->maxVelocity = sf::Vector2f(-20.0f, 0.0f);
		this->direction = sf::Vector2f(-1.f, 0.0f);
		break;
	case 'u':
		this->sprite.setPosition(pos.x+35, pos.y);
		this->sprite.setRotation(90.f);
		this->maxVelocity = sf::Vector2f(0.0f, -20.0f);
		this->direction = sf::Vector2f(0.0f, -1.0f);
		break;
	case 'd':
		this->sprite.setPosition(pos.x + 35, pos.y+100);
		this->sprite.setRotation(90.f);
		this->maxVelocity = sf::Vector2f(0.0f, 20.0f);
		this->direction = sf::Vector2f(0.0f, 1.0f);
		break;

	}
	this->currentVelocity = sf::Vector2f(1.f * this->direction.x, 1.f * this->direction.y);

}

float GunBullet::vectorLength(sf::Vector2f v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

sf::Vector2f GunBullet::normalize(sf::Vector2f v, float length) {
	return v / length;
}


int GunBullet::movement(sf::Vector2f playerPos) {

	sf::Vector2f fudir;

	if (acceleration > 0.f && this->direction!=sf::Vector2f(-1.f,0.f) && this->direction != sf::Vector2f(0.f, -1.f)) {
		if (currentVelocity.x < this->maxVelocity.x) {
			this->currentVelocity.x += this->acceleration * this->direction.x;
		}
		if (currentVelocity.y < this->maxVelocity.y) {
			this->currentVelocity.y += this->acceleration * this->direction.y;
		}
	}
	else {
		this->currentVelocity = sf::Vector2f(this->maxVelocity.x, this->maxVelocity.y);
	}
	if (type == 1) {
		direction.x = playerPos.x - this->sprite.getPosition().x;
		direction.y = playerPos.y - this->sprite.getPosition().y;

		fudir = normalize(direction, vectorLength(direction));
		this->sprite.setRotation(atan2(fudir.y, fudir.x) * 180 / 3.141592 + 180);
		this->sprite.move(fudir.x * 3.f * this->speed, fudir.y * 3.f * this->speed);

	}
	else this->sprite.move(this->currentVelocity);
	
	return 0;
}

int GunBullet::update(sf::Vector2f playerPos) {
	this->movement(playerPos);
	return 0;
}

void GunBullet::draw(sf::RenderTarget & target) {
	std::cout << "drawing bullets"<<std::endl;
	target.draw(this->sprite);

}

