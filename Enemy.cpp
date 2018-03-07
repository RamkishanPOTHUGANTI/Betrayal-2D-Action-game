#include "Enemy.h"
#include <thread>
Enemy::Enemy(int num,sf::Texture gtex,sf::Texture stex, sf::Texture bullet,sf::SoundBuffer guns, sf::Vector2f initialPosition, int hp, int dmgValue,int t,sf::Vector2f d,sf::Vector2u wb) {

	
	damageMin = dmgValue;
	level = 1;
//	speed = 3.5f;
	damageMax = 20;
	currentLevel = 0;
	speed = 1.5f;
//	imgPath = path;
//	bulletPath = bullet;
	playerNr = num;
	bulletTexture = bullet;
	spaceTexture = stex;
	groundTex = gtex;
	direction = d;
	maxhp = hp;
	type = t;
	bulletTimer = 0;
	if (type == 1) {
		speed = 2.f;
	}
	initialPos = initialPosition;
	gunBuffer = guns;
	windowBounds = wb;
//	loadFiles();

}
int Enemy::shoot() {
	for (int i = 0; i < 1;i++) {
		bullets.push_back(GunBullet(0,1,bulletTexture, sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y), 'u'));
		bullets.push_back(GunBullet(0,1,bulletTexture, sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y), 'l'));
		bullets.push_back(GunBullet(0,1,bulletTexture, sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y) , 'r'));
		bullets.push_back(GunBullet(0,1,bulletTexture, sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y ), 'd'));
	}
	return 0;
}
int Enemy::initialize() {
	if (currentLevel == 1) {
		sprite.setTexture(spaceTexture);
		sprite.setPosition((rand() % windowBounds.x) + 1640, (rand() % windowBounds.y) + sprite.getGlobalBounds().height);
	}
	else {
		sprite.setTexture(groundTex);
		sprite.setPosition((rand() % windowBounds.x)+ 1590, (rand() % windowBounds.y) + sprite.getGlobalBounds().height);
		//	sprite.setPosition(initialPos);
	}
	return 0;
}
float Enemy::vectorLength(sf::Vector2f v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
sf::Vector2f Enemy::normalize(sf::Vector2f v, float length) {
	return v / length;
}

int Enemy::loadFiles() {
	if (currentLevel!=1) shoot();
	return 0;

}
int Enemy::takeDamage(int damage) {
	this->hp -= damage;
	if (this->hp <= 0) {
		this->hp = 0;
	}
	return 0;
}

void Enemy::movement(sf::Vector2f playerPos) {
	sf::Vector2f fudir;
	
	if (type==1) this->sprite.move(direction * speed);
	else {
		direction.x = playerPos.x - this->sprite.getPosition().x;
		direction.y = playerPos.y - this->sprite.getPosition().y;

		fudir = normalize(direction, vectorLength(direction));
		this->sprite.setRotation(atan2(fudir.y, fudir.x) * 180 / 3.141592 + 180);
		this->sprite.move(fudir.x * 3.f * speed, fudir.y * 3.f * speed);

	}
}
void Enemy::update(sf::Vector2f playerPos,sf::FloatRect playerBounds) {
	bulletTimer++;
	this->movement(playerPos);
	if (currentLevel !=1) {
		for (int i = 0; i < bullets.size(); i++) {
			if (bulletTimer > 50 || bullets[i].getGlobalBounds().intersects(playerBounds)) {
				bullets.erase(bullets.begin() + i);
			}
			else bullets[i].update(playerPos);
		}
		if (bulletTimer > 50) {
			bulletTimer = 0;
		}
	}

}
void Enemy::draw(sf::RenderTarget * target) {
	target->draw(this->sprite);
	if (currentLevel !=1) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].draw(*target);
		}
	}
}


