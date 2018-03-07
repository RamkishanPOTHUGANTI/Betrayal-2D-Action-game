#include "player_1.h"



player_1::player_1(std::string a)
{
	//fr, fl, br, bl, rr, rl, rm,lr,ll,lm
	int i = 0;
	while (a[i] != '@')fr = fr + a[i++];
	i++;
	if (!fr_.loadFromFile(fr))printf("unable to form texturtes");
	while (a[i] != '@')fl = fl + a[i++];
	i++;
	if (!fl_.loadFromFile(fl))printf("unable to form texturtes");
	while (a[i] != '@')br = br + a[i++];
	i++;
	if (!br_.loadFromFile(br))printf("unable to form texturtes");
	while (a[i] != '@')bl = bl + a[i++];
	i++;
	if (!bl_.loadFromFile(bl))printf("unable to form texturtes");
	while (a[i] != '@')rr = rr + a[i++];
	i++;
	if (!rr_.loadFromFile(rr))printf("unable to form texturtes");
	while (a[i] != '@')rl = rl + a[i++];
	i++;
	if (!rl_.loadFromFile(rl))printf("unable to form texturtes");
	while (a[i] != '@')rm = rm + a[i++];
	i++;
	if (!rm_.loadFromFile(rm))printf("unable to form texturtes");
	while (a[i] != '@')lr = lr + a[i++];
	i++;
	if (!lr_.loadFromFile(lr))printf("unable to form texturtes");
	while (a[i] != '@')ll = ll + a[i++];
	i++;
	if (!ll_.loadFromFile(ll))printf("unable to form texturtes");
	while (a[i] != '@')lm = lm + a[i++];
	i++;
	if (!lm_.loadFromFile(lm))printf("unable to form texturtes");
}
int player_1::intialseimage(sf::Vector2f ip) {
	state.setTexture(fr_);
	state.setPosition(ip);
	state.setTextureRect(sf::IntRect(0, 0, 100, 100));
	return 0;
}
void player_1::shift_player(char direction, float speed) {
	if (direction == 'u') {
		state.move(0.0f, -speed);
	}
	else if (direction == 'd') {
		state.move(0.0f, +speed);
	}
	else if (direction == 'r') {
		state.move(speed, 0.0f);
	}
	else if (direction == 'l') {
		state.move(-speed, 0.0f);
	}
}
void player_1::move_player(char direction, float speed) {
	if (direction == 'u') {
		if (is_right)state.setTexture(bl_);
		else state.setTexture(br_);
		state.move(0.0f, -speed);
		is_right = !is_right;
	}
	else if (direction == 'd') {
		if (is_right)state.setTexture(fl_);
		else state.setTexture(fr_);
		state.move(0.0f, speed);
		is_right = !is_right;
	}
	else if (direction == 'r') {
		if (is_side) {
			state.setTexture(rm_);
			is_side = !is_side;
		}
		else {
			if (is_right)state.setTexture(rl_);
			else state.setTexture(rr_);
			is_side = !is_side;
			is_right = !is_right;
		}
		state.move(speed, 0.0f);
	}
	else if (direction == 'l') {
		if (is_side) {
			state.setTexture(lm_);
			is_side = !is_side;
		}
		else {
			if (is_right)state.setTexture(ll_);
			else state.setTexture(lr_);
			is_side = !is_side;
			is_right = !is_right;
		}
		state.move(-speed, 0.0f);
	}
	presentdirection = direction;
	currentpositions = state.getPosition();
}
void player_1::drawplayer(sf::RenderWindow * window_) {
	state.setTextureRect(sf::IntRect(0, 0, 100, 100));
	window_->draw(state);
}
player_1::~player_1()
{
}