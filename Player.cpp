#include "Player.h"

// fixed settings
namespace PlayerSetting {
	constexpr int init_HP = 1000;
	constexpr int init_coin = 100;
	constexpr int coin_freq = 60;
	constexpr int coin_increase = 5;
	constexpr int fruit_count = 0;
	constexpr int banana_count = 0;
	constexpr int watermelon_count = 0;
};

Player::Player() : HP(PlayerSetting::init_HP), coin(PlayerSetting::init_coin) {
	this->coin_freq = PlayerSetting::coin_freq;
	this->coin_increase = PlayerSetting::coin_increase;
	coin_counter = PlayerSetting::coin_freq;
}

void
Player::update() {
	if(coin_counter) --coin_counter;
	else {
		coin += coin_increase;
		coin_counter = coin_freq;
	}
}
